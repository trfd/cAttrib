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
    
    enum Error
    {
        WRONG_ARG_COUNT,
        ARG_SYNTAX,
        INCORRECT_ARG_VALUE
    };
    
    typedef std::function<Error(CAttribAttr*,Decl*)> SubAttrCallback;
    
    #pragma region Static Members
    
    // \brief Command line options for cAttrib
    static llvm::cl::OptionCategory optionCategory;
    
    // \brief
    static cl::extrahelp commonHelp;
    
    static cl::extrahelp moreHelp;
    
    static DeclarationMatcher matcher;
    
    #pragma endregion
    
    #pragma region Constructor/Destructor
    
    CAttrib();
    
    #pragma endregion
    
    #pragma region CAttrib API
    
    void registerSubAttr(const std::string& str_,const SubAttrCallback& clbk_);
    
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
    
    // \brief Check if attributes match any of
    // the registred sub-cattributes
    // \see registerSubAttr
    void checkSubAttr(CAttribAttr* attr_);
    
    #pragma region Private Data Members
    
    AttrMatchCallback m_attrCallback;
    
    std::map<std::string,SubAttrCallback> m_subAttrCallbackMap;
    
    #pragma endregion
};

#endif
