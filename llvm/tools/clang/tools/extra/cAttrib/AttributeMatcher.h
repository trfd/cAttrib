//
//  AttributeMatcher.h
//  
//
//  Created by Baptiste Dupy on 05/09/14.
//
//

#ifndef _AttributeMatcher_h
#define _AttributeMatcher_h

#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

using namespace clang;
using namespace clang::ast_matchers;

DeclarationMatcher AttribMatcher = decl().bind("forAttrib");

class AttributePrinter : public MatchFinder::MatchCallback
{
public:
    
    virtual void run(const MatchFinder::MatchResult &Result)
    {
        
        if (const Decl *FS = Result.Nodes.getNodeAs<clang::Decl>("forAttrib"))
        {
            FS->dump();
            std::cout<<std::boolalpha<<"|| Has Attrib: "<<FS->hasAttrs()<<"\n";
            
            for(Decl::attr_iterator it = FS->attr_begin() ; it != FS->attr_end() ; ++it)
            {
                if((*it)->getKind() != clang::attr::CAttrib)
                    continue;
                
                std::cout<<"----|| Size:"<<static_cast<CAttribAttr*>(*it)->args_size()<<"\n";
            }
        }
    
    }
};

#endif
