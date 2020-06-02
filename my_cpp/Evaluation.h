#ifndef EVALUATION_H_
#define EVALUATION_H_

#include"Types.h"
#include"Validation.h"

std::shared_ptr<MalToken> eval_ast (std::shared_ptr<MalToken> ast, MalEnv& repl_env);
std::shared_ptr<MalToken> eval(std::shared_ptr<MalToken>, MalEnv& repl_env);
std::shared_ptr<MalToken> addFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args);
std::shared_ptr<MalToken> subFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args);
std::shared_ptr<MalToken> mulFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args);
std::shared_ptr<MalToken> divFunction(std::vector<std::shared_ptr<MalToken>>::const_iterator args);

#endif // EVALUATION_H_

