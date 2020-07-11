#ifndef EVALUATION_H_
#define EVALUATION_H_

#include<memory>
#include<string>

#include"Types.h"
#include"Validation.h"
#include "Environment.h"

std::shared_ptr<AstToken> eval_ast (std::shared_ptr<AstToken> ast, std::shared_ptr<MalEnv> repl_env);
std::shared_ptr<AstToken> eval(std::shared_ptr<AstToken>, std::shared_ptr<MalEnv> repl_env);

#endif // EVALUATION_H_

