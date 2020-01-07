#ifndef PARSER_PARSER_HPP_
#define PARSER_PARSER_HPP_

#include <memory>

#include "../scanner/Scanner.hpp"
#include "../scanner/TokenType.hpp"
#include "../scanner/Token.hpp"
#include "../ast/Var.hpp"
#include "../ast/VarType.hpp"
#include "../ast/Program.hpp"
#include "../ast/statement/ReturnStatement.hpp"
#include "../ast/statement/AssignStatement.hpp"
#include "../ast/statement/IfStatement.hpp"
#include "../ast/statement/WhileStatement.hpp"
#include "../ast/statement/FunctionCallStatement.hpp"
#include "../ast/statement/FunctionDefStatement.hpp"
#include "../ast/statement/BlockStatement.hpp"
#include "../ast/statement/Statement.hpp"
#include "../ast/expression/Expression.hpp"
#include "../ast/expression/OrExpr.hpp"
#include "../ast/expression/RelationalExpr.hpp"

using namespace ast;
using namespace scanner;
namespace parser
{

class Parser
{
public:

    Parser() = default;
    explicit Parser(Scanner* scr_) {scr = scr_;}

    void setScr(Scanner* scr_);

    void parse() {
        scr->scan(); 
        parseProgram();
    }

    void move() {
        current = next;
        next = scr->scan();
    }

private:
    Scanner* scr;
    Program program;
    BlockStatement* block = nullptr;
    Token current;
    Token next;

    void parseProgram();
    bool accept(TokenType type, bool doThrow = false);
    void parseFunction();
    void parseArgs(FunctionDefinition &fun);
    void parseStmtBlock(BlockStatement &newBlock);
    std::unique_ptr<Statement> parseInitStatement();
    std::unique_ptr<Statement> parseAssignOrFunCall();
    std::unique_ptr<Statement> parseAssignStatement(Var &variable);
    std::unique_ptr<Statement> parseFunCall();
    std::unique_ptr<Statement> parseReturnStatement();
    std::unique_ptr<Statement> parseIfStatement();
    std::unique_ptr<Statement> parseWhileStatement();
    std::unique_ptr<Expression> parseOrExpr();
    std::unique_ptr<Expression> parseAndExpr();
    std::unique_ptr<Expression> parseRelExpr();
    std::unique_ptr<Expression> parseBaseLogicExpr();
    std::unique_ptr<Expression> parseAddExpr();
    std::unique_ptr<Expression> parseMultExpr();
    std::unique_ptr<Expression> parseBaseMathExpr();
    Var parseVectorLiteral();
    bool existVariable();
};

}


#endif