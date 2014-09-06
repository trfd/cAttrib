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

#include "cAttrib.h"

#pragma region CAttrib Implementation

llvm::cl::OptionCategory CAttrib::optionCategory("cAttrib Options");

static cl::extrahelp CAttrib::commonHelp(CommonOptionsParser::HelpMessage);

static cl::extrahelp CAttrib::moreHelp("\n... More Help");

static DeclarationMatcher CAttrib::matcher = decl(hasAttr(clang::attr::CAttrib)).bind("CAttrib");

inline void CAttrib::setVerbose(bool verb_)
{
    m_attrCallback._verbose = verb_;
}

int CAttrib::run(int argc, const char * argv[])
{
    CommonOptionsParser optionsParser(argc,argv, optionCategory);
    
    ClangTool tool(optionsParser.getCompilations(),
                   optionsParser.getSourcePathList());
    
    MatchFinder finder;
    
    finder.addMatcher(matcher, &m_attrCallback);
    
    return tool.run(newFrontendActionFactory(&finder).get());
}

#pragma region AttrMatchCallback Implementation

CAttrib::AttrMatchCallback::AttrMatchCallback(CAttrib& p_)
: _parent(p_)
{}

void CAttrib::AttrMatchCallback::run(const MatchFinder::MatchResult &Result)
{
    if (const Decl *attrDecl = Result.Nodes.getNodeAs<clang::Decl>("CAttrib"))
    {
        if(_verbose)
            attrDecl->dump();
        
        for(Decl::attr_iterator it = attrDecl->attr_begin() ;
            it != attrDecl->attr_end() ; ++it)
        {
            if((*it)->getKind() != clang::attr::CAttrib)
                continue;
            
            std::cout<<"----|| Size:"<<static_cast<CAttribAttr*>(*it)->args_size()<<"\n";
        }
    }
}

#pragma endregion

#pragma endregion

#pragma region Test

int main(int argc, const char * argv[])
{
    return CAttrib().run(argc,argv);
}

#pragma endregion