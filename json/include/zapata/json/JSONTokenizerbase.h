// Generated by Bisonc++ V4.13.01 on Fri, 28 Oct 2016 20:27:35 +0100

#ifndef zptJSONTokenizerBase_h_included
#define zptJSONTokenizerBase_h_included

#include <exception>
#include <vector>
#include <iostream>

// $insert preincludes
#include "JSONinc.h"

namespace // anonymous
{
    struct PI__;
}

// $insert namespace-open
namespace zpt
{


class JSONTokenizerBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        STRING = 257,
        BOOLEAN,
        INTEGER,
        DOUBLE,
        NIL,
        LAMBDA,
        LCB,
        RCB,
        LB,
        RB,
        COMMA,
        COLON,
    };

// $insert STYPE
typedef int STYPE__;

    private:
        int d_stackIdx__;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_debug__;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_val__;
        STYPE__     d_nextVal__;

        JSONTokenizerBase();

        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
}; 

inline bool JSONTokenizerBase::debug() const
{
    return d_debug__;
}

inline void JSONTokenizerBase::setDebug(bool mode)
{
    d_debug__ = mode;
}

inline void JSONTokenizerBase::ABORT() const
{
    throw PARSE_ABORT__;
}

inline void JSONTokenizerBase::ACCEPT() const
{
    throw PARSE_ACCEPT__;
}

inline void JSONTokenizerBase::ERROR() const
{
    throw UNEXPECTED_TOKEN__;
}


// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define JSONTokenizer JSONTokenizerBase

// $insert namespace-close
}

#endif


