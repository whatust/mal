#ifndef EVALUATION_H_
#define EVALUATION_H_

#include"Types.h"
#include"Validation.h"
#include "Environment.h"

std::shared_ptr<AstToken> eval_ast (std::shared_ptr<AstToken> ast, MalEnv& repl_env);
std::shared_ptr<AstToken> eval(std::shared_ptr<AstToken>, MalEnv& repl_env);

#endif // EVALUATION_H_

