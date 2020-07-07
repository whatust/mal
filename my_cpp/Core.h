#ifndef _CORE_H_
#define _CORE_H_

#include<fstream>

#include"Types.h"
#include"Validation.h"
#include"Environment.h"
#include"Printer.h"
#include"Reader.h"

void start_outer_env(MalEnv & repl_env);
std::shared_ptr<AstToken> addOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> subOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> mulOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> divOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> eqOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> ltOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> lteOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> gtOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> gteOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> listOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> listqOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> emptyOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> countOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> prnOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> strOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> prstrOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> printlnOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> readstrOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> slurpOperator(MalArgs args, MalArgs end);

#endif //_CORE_H_
