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

using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

// \brief Main class of cAttrib library
// This class manages matching of "cattrib"s
class CAttrib
{
public:
    
    #pragma region Static Members
    
    // \brief Command line options for cAttrib
    static llvm::cl::OptionCategory optionCategory;
    
    // \brief
    static cl::extrahelp commonHelp;
    
    static cl::extrahelp moreHelp;
    
    static DeclarationMatcher matcher;
    
    #pragma endregion
    
    #pragma region CAttrib API
    
    int run(int argc, const char * argv[]);
    
    inline void setVerbose(bool verb_ = true);
    
private:
    
    struct AttrMatchCallback : public MatchFinder::MatchCallback
    {
        AttrMatchCallback(CAttrib& p_);
        
        virtual void run(const MatchFinder::MatchResult &Result) override;
        
        CAttrib& _parent;
        bool _verbose = false;
    };
    
    #pragma region Private Data Members
    
    AttrMatchCallback m_attrCallback;
    
    #pragma endregion
};

#endif
