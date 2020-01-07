#include "Parser.hpp"

using namespace parser;
using namespace scanner;
using namespace ast;

#include <iostream>

const bool THROW = true;
const bool NOTHROW = false;

void Parser::setScr(Scanner* scr_) {
    scr = scr_;
}

bool Parser::accept(const TokenType type, bool doThrow) {
    if (scr->getToken().getType() == type) {
        move();
        return true;
    }
    return doThrow ? throw std::runtime_error("Wrong token") : false;
}

void Parser::parseProgram() {
    while (scr->getToken().getType() != TokenType::T_EOF) {
        if (accept(TokenType::K_Fun, NOTHROW)) {
            parseFunction();
        }
        if (accept(TokenType::T_EOF, THROW)) {
            return;
        }
    }
}

void Parser::parseFunction() {
    std::unique_ptr<FunctionDefinition> fun;
    accept(TokenType::I_Identifier, THROW);
    fun = std::make_unique<FunctionDefinition>(current.getString());
    accept(TokenType::T_OpenParen, THROW);
    parseArgs(*fun);

    FunctionDefinition* func = fun.get();
    program.addFunction(std::move(fun));
    accept(TokenType::T_OpenBrace, THROW);
    parseStmtBlock(func->getFunctionBlock());
}

void Parser::parseArgs(FunctionDefinition &fun) {
    if (accept(TokenType::I_Identifier, NOTHROW)) {
        while (accept(TokenType::T_Comma, NOTHROW)) {
            accept(TokenType::I_Identifier, THROW);
            fun.addParam(current.getString());
        }
    }
    accept(TokenType::T_CloseParen, THROW);
}

void Parser::parseStmtBlock(BlockStatement &newBlock) {
    block = &newBlock;
    std::unique_ptr<BlockStatement> newNewBlock;
    TokenType tokenType;

    while (!accept(TokenType::T_CloseBrace, NOTHROW)) {
        move();
        tokenType = current.getType();
        switch(tokenType) 
        {
            case TokenType::K_If:
                block->addStatement(std::move(parseIfStatement())); break;
            case TokenType::K_While:
                block->addStatement(std::move(parseWhileStatement())); break;
            case TokenType::I_Identifier:
                block->addStatement(std::move(parseAssignOrFunCall())); break;
            case TokenType::K_Var:
                block->addStatement(std::move(parseInitStatement())); break;
            case TokenType::K_Return:
                block->addStatement(std::move(parseReturnStatement())); break;
            case TokenType::T_OpenBrace:
                newNewBlock = std::move(std::make_unique<BlockStatement>(block));
                parseStmtBlock(*newNewBlock);
                block->addStatement(std::move(newNewBlock));
                break;
            default:
                throw std::runtime_error("Block parse invalid");
        }
        
    }

    block = const_cast<BlockStatement *>(newBlock.getParent());
}

std::unique_ptr<Statement> Parser::parseInitStatement() {

    accept(TokenType::I_Identifier, THROW);

    std::string id = current.getString();

    if (block->existVariable(id))
        throw std::runtime_error("Variable already initialized");

    block->addVariable(id, Var());
    std::unique_ptr<Expression> expr = std::make_unique<BaseMathExpr>(new Var());

    if (accept(TokenType::T_Equal, NOTHROW)) {
        expr = std::move(parseOrExpr());
    }

    accept(TokenType::T_Semicolon, THROW);

    return std::make_unique<AssignStatement>(block->findVariable(id), std::move(expr));
}

std::unique_ptr<Statement> Parser::parseAssignOrFunCall() {
    std::unique_ptr<Statement> statement;

    if (accept(TokenType::T_OpenParen, NOTHROW)) {
        statement = std::move(parseFunCall());
        accept(TokenType::T_Semicolon, THROW);
    } else {
        existVariable();
        statement = std::move(parseAssignStatement(block->findVariable(current.getString())));
    }
    return std::move(statement);
}

std::unique_ptr<Statement> Parser::parseAssignStatement(Var &variable) {
    std::unique_ptr<AssignStatement> assignStatement;
    std::unique_ptr<Expression> logicExpr;

    accept(TokenType::T_Equal, THROW);
    if (accept(TokenType::T_OpenBracket, NOTHROW)) 
        logicExpr = std::make_unique<BaseMathExpr>(parseVectorLiteral(), false);
    else logicExpr = std::make_unique<OrExpr>(parseOrExpr());
    accept(TokenType::T_Semicolon, THROW);

    assignStatement = std::make_unique<AssignStatement>(variable, std::move(logicExpr));

    return std::move(assignStatement);
}

std::unique_ptr<Statement> Parser::parseFunCall() {
    if (!program.existFunction(current.getString())) {
        throw std::runtime_error(
                "Function not found: " + current.getString());
    }

    FunctionDefinition &functionDef = program.findFunction(current.getString());
    auto functionCall = std::make_unique<FunctionCall>(functionDef);

    if (!accept(TokenType::T_CloseParen, NOTHROW)) {
        functionCall->addExpression(parseOrExpr());
        while (!accept(TokenType::T_CloseParen, NOTHROW)) {
            accept(TokenType::T_Comma, THROW);
            functionCall->addExpression(parseOrExpr());
        }
    }

    if (functionDef.size() != functionCall->size()) {
        throw std::runtime_error(
            "Wrong number of parameters in functionCall");
    }

    return std::move(functionCall);
}


std::unique_ptr<Statement> Parser::parseReturnStatement() {
    std::unique_ptr<ReturnStatement>returnStatement = 
        std::make_unique<ReturnStatement>(std::move(parseOrExpr()));
    accept(TokenType::T_Semicolon, THROW);
    return std::move(returnStatement);
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
    std::unique_ptr<Expression> expression;
    std::unique_ptr<BlockStatement> ifBlock;
    std::unique_ptr<BlockStatement> elseBlock;

    accept(TokenType::T_OpenParen, THROW);
    expression = std::move(parseOrExpr());
    accept(TokenType::T_CloseParen, THROW);

    accept(TokenType::T_OpenBrace, THROW);
    ifBlock = std::make_unique<BlockStatement>(block);
    parseStmtBlock(*ifBlock);

    if (accept(TokenType::K_Else), NOTHROW) {
        accept(TokenType::T_OpenBrace, THROW);
        elseBlock = std::make_unique<BlockStatement>(block);
        parseStmtBlock(*elseBlock);
    }

    return std::make_unique<IfStatement>(std::move(expression),
                                         std::move(ifBlock),
                                         std::move(elseBlock));
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
    std::unique_ptr<WhileStatement> whileStatement;
    std::unique_ptr<Expression> expression;
    std::unique_ptr<BlockStatement> whileBlock;

    accept(TokenType::T_OpenParen, THROW);
    expression = std::move(parseOrExpr());
    accept(TokenType::T_CloseParen, THROW);

    accept(TokenType::T_OpenBrace, THROW);
    whileBlock = std::make_unique<BlockStatement>(block);
    parseStmtBlock(*whileBlock);

    whileStatement = std::make_unique<WhileStatement>(std::move(expression),
                                                      std::move(whileBlock));

    return std::move(whileStatement);
}

std::unique_ptr<Expression> Parser::parseOrExpr() {
    std::unique_ptr<OrExpr> logicExpr = std::make_unique<OrExpr>(std::move(parseAndExpr()));

    while (accept(TokenType::T_Bar2, NOTHROW)) {
        logicExpr->addOr(std::move(parseAndExpr()));
    }

    //logicExpr->print();

    return std::move(logicExpr);
}

std::unique_ptr<Expression> Parser::parseAndExpr() {
    std::unique_ptr<AndExpr> andExpr = std::make_unique<AndExpr>(std::move(parseRelExpr()));

    while (accept(TokenType::T_Ampersand2, NOTHROW)) {
        andExpr->addAnd(std::move(parseRelExpr()));
    }

    return std::move(andExpr);
}

std::unique_ptr<Expression> Parser::parseRelExpr() {
    std::unique_ptr<RelationExpr> relationalExpr = std::make_unique<RelationExpr>(std::move(parseBaseLogicExpr()));

    TokenType tokenType = next.getType();

    switch (tokenType) {
        case TokenType::T_Equal2:
            move(); relationalExpr->addEqual(std::move(parseBaseLogicExpr())); break;
        case TokenType::T_NotEqual:
            move(); relationalExpr->addNotEqual(std::move(parseBaseLogicExpr())); break;
        case TokenType::T_LessThan: 
            move(); relationalExpr->addLessThan(std::move(parseBaseLogicExpr())); break;
        case TokenType::T_LeEqThan:
            move(); relationalExpr->addLessEqual(std::move(parseBaseLogicExpr())); break;
        case TokenType::T_GreaterThan:
            move(); relationalExpr->addGreaterThan(std::move(parseBaseLogicExpr())); break;
        case TokenType::T_GrEqThan:
            move(); relationalExpr->addGreaterEqual(std::move(parseBaseLogicExpr())); break;
        default:
            return std::move(relationalExpr);
    }

    

    return std::move(relationalExpr);
}

std::unique_ptr<Expression> Parser::parseBaseLogicExpr() {
    if (accept(TokenType::T_Exclamation)) {
        return std::make_unique<BaseLogicExpr>(std::move(parseAddExpr()), true);
    } else {
        return std::make_unique<BaseLogicExpr>(std::move(parseAddExpr()));
    }
}

std::unique_ptr<Expression> Parser::parseAddExpr() {
    std::unique_ptr<AddExpr> mathExpr = std::make_unique<AddExpr>(std::move(parseMultExpr()));
    TokenType tokenType;

    while (true) {
        tokenType = next.getType();

        if (tokenType == TokenType::T_Plus) { move(); mathExpr->addPlus(std::move(parseMultExpr())); }
        else if (tokenType == TokenType::T_Minus) { move(); mathExpr->addMinus(std::move(parseMultExpr())); }
        else break;
    }

    return std::move(mathExpr);
}

std::unique_ptr<Expression> Parser::parseMultExpr() {
    std::unique_ptr<MultiExpr> multiExpr = std::make_unique<MultiExpr>(std::move(parseBaseMathExpr()));
    TokenType tokenType;

    while (true) {
        tokenType = next.getType();

        if (tokenType == TokenType::T_Asterisk) { move(); multiExpr->addMultiply(std::move(parseBaseMathExpr())); }
        else if (tokenType == TokenType::T_Slash) { move(); multiExpr->addDivide(std::move(parseBaseMathExpr())); }
        else break;
    }

    return std::move(multiExpr);
}

std::unique_ptr<Expression> Parser::parseBaseMathExpr() {
    std::unique_ptr<BaseMathExpr> baseMathExpr;
    bool unary = accept(TokenType::T_Minus, NOTHROW);

    if (accept(TokenType::L_Numeric, NOTHROW)) {
        baseMathExpr = std::make_unique<BaseMathExpr>(new Var(VarType::INT, {current.getInteger()}), unary);

    } else if (accept(TokenType::T_OpenParen)) {
        baseMathExpr = std::make_unique<BaseMathExpr>(std::move(parseOrExpr()), unary);
        accept(TokenType::T_CloseParen, THROW);

    } else if (accept(TokenType::I_Identifier)) {

        if (accept(TokenType::T_OpenParen)) {
            baseMathExpr = std::make_unique<BaseMathExpr>(std::move(parseFunCall()), unary);
        } else {
            existVariable();
            if (accept(TokenType::T_OpenBracket, NOTHROW)) {
                accept(TokenType::L_Numeric, THROW);
                Token tk = current;
                accept(TokenType::T_CloseBracket, THROW);

                baseMathExpr = std::make_unique<BaseMathExpr>(block->findVariable(tk.getString()), tk.getInteger(), unary);
            } else {
                baseMathExpr = std::make_unique<BaseMathExpr>(block->findVariable(current.getString()), unary);
            }
        }
    } else {
        throw std::runtime_error("Unknown math expression");
    }

    return std::move(baseMathExpr);
}

Var Parser::parseVectorLiteral() {
    valueVec variables;
    if(accept(TokenType::L_Numeric, THROW)) variables.push_back(current.getInteger());
    while(accept(TokenType::T_Comma, NOTHROW)) {
        accept(TokenType::L_Numeric, THROW);
    }
    accept(TokenType::T_CloseBracket, THROW);

    return Var(VarType::LIST, variables);
}

bool Parser::existVariable() {
    if (!block->existVariable(current.getString())) {
        throw std::runtime_error(
                "Variable not found: " + current.getString());
    }
    return true;
}