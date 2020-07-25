#ifndef _CORE_H_
#define _CORE_H_

#include<algorithm>
#include<fstream>
#include<iostream>
#include<iterator>
#include<memory>
#include<string>

#include"Types.h"
#include"Validation.h"
#include"Environment.h"
#include"Printer.h"
#include"Reader.h"
#include"Evaluation.h"

extern std::shared_ptr<MalEnv> outer_env;

void start_outer_env(std::shared_ptr<MalEnv> repl_env);
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
std::shared_ptr<AstToken> evalOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> atomOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> atomqOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> derefOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> resetOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> swapOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> consOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> concatOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> nthOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> firstOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> restOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> throwOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> applyOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> mapOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> symbolqOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> falseqOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> trueqOperator(MalArgs args, MalArgs end);
std::shared_ptr<AstToken> nilqOperator(MalArgs args, MalArgs end);

std::shared_ptr<AstToken> symbolOperator(MalArgs args, MalArgs end);

#endif //_CORE_H_
