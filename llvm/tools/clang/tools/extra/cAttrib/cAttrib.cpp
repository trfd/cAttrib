//
//  main.cpp
//  cAttrib
//
//  Created by Baptiste Dupy on 05/09/14.
//  Copyright (c) 2014 TRFD. All rights reserved.
//



#include <iostream>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>


#include <llvm/Support/CommandLine.h>

#include "AttributeMatcher.h"

using namespace clang::tooling;
using namespace llvm;

static llvm::cl::OptionCategory s_cAttribOptionCategory("cAttrib Options");

static cl::extrahelp s_commonHelp(CommonOptionsParser::HelpMessage);

static cl::extrahelp s_moreHelp("\n... More Help");

int main(int argc, const char * argv[])
{
    
    CommonOptionsParser optionsParser(argc,argv, s_cAttribOptionCategory);
    
    ClangTool tool(optionsParser.getCompilations(),
                   optionsParser.getSourcePathList());
    
    AttributePrinter attribPrinter;
    MatchFinder finder;
    
    finder.addMatcher(AttribMatcher, &attribPrinter);
    
    return tool.run(newFrontendActionFactory(&finder).get());
}

