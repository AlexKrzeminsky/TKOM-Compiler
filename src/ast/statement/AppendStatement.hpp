#ifndef PARSER_APPENDSTATEMENT_HPP_
#define PARSER_APPENDSTATEMENT_HPP_

#include <list>
#include <memory>
#include "Statement.hpp"
#include "../expression/Expression.hpp"
#include "FunctionDefStatement.hpp"

namespace ast {

class AppendStatement : public Statement {
public:
    explicit AppendStatement(Var& from_, Var& to_) : from(from_), to(to_) {}

    Return run() override {
        std::vector<Var> var;

        for (auto x : from.value) {
            to.value.push_back(x);
        }
        Return ret(Return::None);
        return ret;
    }

private:
    Var& from;
    Var& to;
};

}


#endif