#ifndef EVALUATION_H_
#define EVALUATION_H_

#include"Types.h"
#include"Validation.h"

std::shared_ptr<MalToken> eval_ast (std::shared_ptr<MalToken> ast, MalEnv& repl_env);
std::shared_ptr<MalToken> eval(std::shared_ptr<MalToken>, MalEnv& repl_env);
std::shared_ptr<MalToken> addFunction(MalArgs args, MalArgs end);
std::shared_ptr<MalToken> subFunction(MalArgs args, MalArgs end);
std::shared_ptr<MalToken> mulFunction(MalArgs args, MalArgs end);
std::shared_ptr<MalToken> divFunction(MalArgs args, MalArgs end);

#endif // EVALUATION_H_

