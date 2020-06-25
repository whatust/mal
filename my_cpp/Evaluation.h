#ifndef EVALUATION_H_
#define EVALUATION_H_

#include"Types.h"
#include"Validation.h"
#include "Environment.h"

std::shared_ptr<AstToken> eval_ast (std::shared_ptr<AstToken> ast, MalEnv& repl_env);
std::shared_ptr<AstToken> eval(std::shared_ptr<AstToken>, MalEnv& repl_env);
std::shared_ptr<AstToken> addFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> subFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> mulFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> divFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> eqFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> ltFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> lteFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> gtFunction(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> gteFunction(MalArgs args, MalArgs end);

#endif // EVALUATION_H_

