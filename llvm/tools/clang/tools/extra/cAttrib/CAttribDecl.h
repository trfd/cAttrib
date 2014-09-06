//
//  AttributeMatcher.h
//  
//
//  Created by Baptiste Dupy on 05/09/14.
//
//

#ifndef _CAttribDecl_h
#define _CAttribDecl_h

#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

using namespace clang;
using namespace clang::ast_matchers;

struct CAttribDecl
{
    static void processAttr(Sema &S, Decl *D, const AttributeList &Attr)
    {
    }
};

#endif
