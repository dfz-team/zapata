// Generated by Bisonc++ V6.03.00 on Wed, 16 Sep 2020 17:20:23 -44452020

// base/comment

// $insert class.ih
#include <zapata/http/HTTPTokenizerimpl.h>

// The FIRST element of SR arrays shown below uses `d_type', defining the
// state's type, and `d_lastIdx' containing the last element's index. If
// d_lastIdx contains the REQ_TOKEN bitflag (see below) then the state needs
// a token: if in this state d_token is Reserved_::UNDETERMINED_, nextToken() will be
// called

// The LAST element of SR arrays uses `d_token' containing the last retrieved
// token to speed up the (linear) seach.  Except for the first element of SR
// arrays, the field `d_action' is used to determine what to do next. If
// positive, it represents the next state (used with SHIFT); if zero, it
// indicates `ACCEPT', if negative, -d_action represents the number of the
// rule to reduce to.

// `lookup()' tries to find d_token in the current SR array. If it fails, and
// there is no default reduction UNEXPECTED_TOKEN_ is thrown, which is then
// caught by the error-recovery function.

// The error-recovery function will pop elements off the stack until a state
// having bit flag ERR_ITEM is found. This state has a transition on errTok_
// which is applied. In this errTok_ state, while the current token is not a
// proper continuation, new tokens are obtained by nextToken(). If such a
// token is found, error recovery is successful and the token is
// handled according to the error state's SR table and parsing continues.
// During error recovery semantic actions are ignored.

// A state flagged with the DEF_RED flag will perform a default
// reduction if no other continuations are available for the current token.

// The ACCEPT STATE never shows a default reduction: when it is reached the
// parser returns ACCEPT(). During the grammar
// analysis phase a default reduction may have been defined, but it is
// removed during the state-definition phase.

// So:
//      s_x[] =
//      {
//                  [_field_1_]         [_field_2_]
//
// First element:   {state-type,        idx of last element},
// Other elements:  {required token,    action to perform},
//                                      ( < 0: reduce,
//                                          0: ACCEPT,
//                                        > 0: next state)
//      }

// base/declarations

namespace // anonymous
{
char const author[] = "Frank B. Brokken (f.b.brokken@rug.nl)";

enum Reserved_ { UNDETERMINED_ = -2, EOF_ = -1, errTok_ = 256 };
enum StateType // modify statetype/data.cc when this enum changes
{ NORMAL,
  ERR_ITEM,
  REQ_TOKEN,
  ERR_REQ,    // ERR_ITEM | REQ_TOKEN
  DEF_RED,    // state having default reduction
  ERR_DEF,    // ERR_ITEM | DEF_RED
  REQ_DEF,    // REQ_TOKEN | DEF_RED
  ERR_REQ_DEF // ERR_ITEM | REQ_TOKEN | DEF_RED
};
inline bool operator&(StateType lhs, StateType rhs) {
    return (static_cast<int>(lhs) & rhs) != 0;
}
enum StateTransition {
    ACCEPT_ = 0, // `ACCEPT' TRANSITION
};

struct PI_ // Production Info
{
    size_t d_nonTerm; // identification number of this production's
                      // non-terminal
    size_t d_size;    // number of elements in this production
};

struct SR_ // Shift Reduce info, see its description above
{
    union {
        int _field_1_; // initializer, allowing initializations
                       // of the SR s_[] arrays
        StateType d_type;
        int d_token;
    };
    union {
        int _field_2_;

        int d_lastIdx; // if negative, the state uses SHIFT
        int d_action;  // may be negative (reduce),
                       // postive (shift), or 0 (accept)
    };
};

// $insert staticdata

enum // size to expand the state-stack with when
{    // full
    STACK_EXPANSION_ = 10
};

// Productions Info Records:
PI_ const s_productionInfo[] = {
    { 0, 0 },    // not used: reduction values are negative
    { 269, 11 }, // 1: exp (METHOD) ->  METHOD #0001 SPACE URL #0002 params SPACE HTTP_VERSION #0003
                 // headers rest
    { 270, 0 },  // 2: #0001 ->  <empty>
    { 272, 0 },  // 3: #0002 ->  <empty>
    { 274, 0 },  // 4: #0003 ->  <empty>
    { 269, 8 },  // 5: exp (HTTP_VERSION) ->  HTTP_VERSION #0004 SPACE STATUS #0005
                 // status_description headers rest
    { 276, 0 },  // 6: #0004 ->  <empty>
    { 278, 0 },  // 7: #0005 ->  <empty>
    { 271, 0 },  // 8: params ->  <empty>
    { 271, 2 },  // 9: params (QMARK) ->  QMARK paramslist
    { 279, 4 },  // 10: paramslist (STRING) ->  STRING #0006 EQ paramvalue
    { 280, 0 },  // 11: #0006 ->  <empty>
    { 279, 6 },  // 12: paramslist (E) ->  paramslist E STRING #0007 EQ paramvalue
    { 282, 0 },  // 13: #0007 ->  <empty>
    { 281, 0 },  // 14: paramvalue ->  <empty>
    { 281, 1 },  // 15: paramvalue (STRING) ->  STRING
    { 277, 0 },  // 16: status_description ->  <empty>
    { 277, 2 },  // 17: status_description (SPACE) ->  SPACE STRING
    { 273, 3 },  // 18: headers (CR_LF) ->  CR_LF headerslist CR_LF
    { 273, 2 },  // 19: headers (CR_LF) ->  CR_LF headerslist
    { 283, 4 },  // 20: headerslist (STRING) ->  STRING #0008 COLON STRING
    { 284, 0 },  // 21: #0008 ->  <empty>
    { 283, 6 },  // 22: headerslist (CR_LF) ->  headerslist CR_LF STRING #0009 COLON STRING
    { 285, 0 },  // 23: #0009 ->  <empty>
    { 275, 1 },  // 24: rest (BODY) ->  BODY
    { 275, 0 },  // 25: rest ->  <empty>
    { 286, 1 },  // 26: exp_$ ->  exp
};

// State info and SR_ transitions for each state.

SR_ const s_0[] = {
    { { REQ_TOKEN }, { 4 } }, { { 269 }, { 1 } }, // exp
    { { 257 }, { 2 } },                           // METHOD
    { { 258 }, { 3 } },                           // HTTP_VERSION
    { { 0 }, { 0 } },
};

SR_ const s_1[] = {
    { { REQ_TOKEN }, { 2 } },
    { { EOF_ }, { ACCEPT_ } },
    { { 0 }, { 0 } },
};

SR_ const s_2[] = {
    { { DEF_RED }, { 2 } },
    { { 270 }, { 4 } }, // #0001
    { { 0 }, { -2 } },
};

SR_ const s_3[] = {
    { { DEF_RED }, { 2 } },
    { { 276 }, { 5 } }, // #0004
    { { 0 }, { -6 } },
};

SR_ const s_4[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 264 }, { 6 } }, // SPACE
    { { 0 }, { 0 } },
};

SR_ const s_5[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 264 }, { 7 } }, // SPACE
    { { 0 }, { 0 } },
};

SR_ const s_6[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 259 }, { 8 } }, // URL
    { { 0 }, { 0 } },
};

SR_ const s_7[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 260 }, { 9 } }, // STATUS
    { { 0 }, { 0 } },
};

SR_ const s_8[] = {
    { { DEF_RED }, { 2 } },
    { { 272 }, { 10 } }, // #0002
    { { 0 }, { -3 } },
};

SR_ const s_9[] = {
    { { DEF_RED }, { 2 } },
    { { 278 }, { 11 } }, // #0005
    { { 0 }, { -7 } },
};

SR_ const s_10[] = {
    { { REQ_DEF }, { 3 } },
    { { 271 }, { 12 } }, // params
    { { 266 }, { 13 } }, // QMARK
    { { 0 }, { -8 } },
};

SR_ const s_11[] = {
    { { REQ_DEF }, { 3 } },
    { { 277 }, { 14 } }, // status_description
    { { 264 }, { 15 } }, // SPACE
    { { 0 }, { -16 } },
};

SR_ const s_12[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 264 }, { 16 } }, // SPACE
    { { 0 }, { 0 } },
};

SR_ const s_13[] = {
    { { REQ_TOKEN }, { 3 } },
    { { 279 }, { 17 } }, // paramslist
    { { 263 }, { 18 } }, // STRING
    { { 0 }, { 0 } },
};

SR_ const s_14[] = {
    { { REQ_TOKEN }, { 3 } },
    { { 273 }, { 19 } }, // headers
    { { 261 }, { 20 } }, // CR_LF
    { { 0 }, { 0 } },
};

SR_ const s_15[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 263 }, { 21 } }, // STRING
    { { 0 }, { 0 } },
};

SR_ const s_16[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 258 }, { 22 } }, // HTTP_VERSION
    { { 0 }, { 0 } },
};

SR_ const s_17[] = {
    { { REQ_DEF }, { 2 } },
    { { 268 }, { 23 } }, // E
    { { 0 }, { -9 } },
};

SR_ const s_18[] = {
    { { DEF_RED }, { 2 } },
    { { 280 }, { 24 } }, // #0006
    { { 0 }, { -11 } },
};

SR_ const s_19[] = {
    { { REQ_DEF }, { 3 } },
    { { 275 }, { 25 } }, // rest
    { { 265 }, { 26 } }, // BODY
    { { 0 }, { -25 } },
};

SR_ const s_20[] = {
    { { REQ_TOKEN }, { 3 } },
    { { 283 }, { 27 } }, // headerslist
    { { 263 }, { 28 } }, // STRING
    { { 0 }, { 0 } },
};

SR_ const s_21[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -17 } },
};

SR_ const s_22[] = {
    { { DEF_RED }, { 2 } },
    { { 274 }, { 29 } }, // #0003
    { { 0 }, { -4 } },
};

SR_ const s_23[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 263 }, { 30 } }, // STRING
    { { 0 }, { 0 } },
};

SR_ const s_24[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 267 }, { 31 } }, // EQ
    { { 0 }, { 0 } },
};

SR_ const s_25[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -5 } },
};

SR_ const s_26[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -24 } },
};

SR_ const s_27[] = {
    { { REQ_DEF }, { 2 } },
    { { 261 }, { 32 } }, // CR_LF
    { { 0 }, { -19 } },
};

SR_ const s_28[] = {
    { { DEF_RED }, { 2 } },
    { { 284 }, { 33 } }, // #0008
    { { 0 }, { -21 } },
};

SR_ const s_29[] = {
    { { REQ_TOKEN }, { 3 } },
    { { 273 }, { 34 } }, // headers
    { { 261 }, { 20 } }, // CR_LF
    { { 0 }, { 0 } },
};

SR_ const s_30[] = {
    { { DEF_RED }, { 2 } },
    { { 282 }, { 35 } }, // #0007
    { { 0 }, { -13 } },
};

SR_ const s_31[] = {
    { { REQ_DEF }, { 3 } },
    { { 281 }, { 36 } }, // paramvalue
    { { 263 }, { 37 } }, // STRING
    { { 0 }, { -14 } },
};

SR_ const s_32[] = {
    { { REQ_DEF }, { 2 } },
    { { 263 }, { 38 } }, // STRING
    { { 0 }, { -18 } },
};

SR_ const s_33[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 262 }, { 39 } }, // COLON
    { { 0 }, { 0 } },
};

SR_ const s_34[] = {
    { { REQ_DEF }, { 3 } },
    { { 275 }, { 40 } }, // rest
    { { 265 }, { 26 } }, // BODY
    { { 0 }, { -25 } },
};

SR_ const s_35[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 267 }, { 41 } }, // EQ
    { { 0 }, { 0 } },
};

SR_ const s_36[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -10 } },
};

SR_ const s_37[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -15 } },
};

SR_ const s_38[] = {
    { { DEF_RED }, { 2 } },
    { { 285 }, { 42 } }, // #0009
    { { 0 }, { -23 } },
};

SR_ const s_39[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 263 }, { 43 } }, // STRING
    { { 0 }, { 0 } },
};

SR_ const s_40[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -1 } },
};

SR_ const s_41[] = {
    { { REQ_DEF }, { 3 } },
    { { 281 }, { 44 } }, // paramvalue
    { { 263 }, { 37 } }, // STRING
    { { 0 }, { -14 } },
};

SR_ const s_42[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 262 }, { 45 } }, // COLON
    { { 0 }, { 0 } },
};

SR_ const s_43[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -20 } },
};

SR_ const s_44[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -12 } },
};

SR_ const s_45[] = {
    { { REQ_TOKEN }, { 2 } },
    { { 263 }, { 46 } }, // STRING
    { { 0 }, { 0 } },
};

SR_ const s_46[] = {
    { { DEF_RED }, { 1 } },
    { { 0 }, { -22 } },
};

// State array:
SR_ const* s_state[] = {
    s_0,  s_1,  s_2,  s_3,  s_4,  s_5,  s_6,  s_7,  s_8,  s_9,  s_10, s_11, s_12, s_13, s_14, s_15,
    s_16, s_17, s_18, s_19, s_20, s_21, s_22, s_23, s_24, s_25, s_26, s_27, s_28, s_29, s_30, s_31,
    s_32, s_33, s_34, s_35, s_36, s_37, s_38, s_39, s_40, s_41, s_42, s_43, s_44, s_45, s_46,
};

} // anonymous namespace ends

// $insert namespace-open
namespace zpt {

// If the parsing function call (i.e., parse()' needs arguments, then provide
// an overloaded function.  The code below doesn't rely on parameters, so no
// arguments are required.  Furthermore, parse uses a function try block to
// allow us to do ACCEPT and ABORT from anywhere, even from within members
// called by actions, simply throwing the appropriate exceptions.

// base/base1
HTTPTokenizerBase::HTTPTokenizerBase()
  : d_token(Reserved_::UNDETERMINED_)
  ,
  // $insert baseclasscode
  d_requiredTokens_(0) {}

// base/clearin
void
HTTPTokenizerBase::clearin_() {
    d_nErrors_ = 0;
    d_stackIdx = -1;
    d_stateStack.clear();
    d_token = Reserved_::UNDETERMINED_;
    d_next = TokenPair{ Reserved_::UNDETERMINED_, STYPE_{} };
    d_recovery = false;
    d_acceptedTokens_ = d_requiredTokens_;
    d_val_ = STYPE_{};

    push_(0);
}

// base/debugfunctions

void
HTTPTokenizerBase::setDebug(bool mode) {
    d_actionCases_ = false;
    d_debug_ = mode;
}

void
HTTPTokenizerBase::setDebug(DebugMode_ mode) {
    d_actionCases_ = mode & ACTIONCASES;
    d_debug_ = mode & ON;
}

// base/lex
void
HTTPTokenizerBase::lex_(int token) {
    d_token = token;

    if (d_token <= 0)
        d_token = Reserved_::EOF_;

    d_terminalToken = true;
}

// base/lookup
int
HTTPTokenizerBase::lookup_() const {
    // if the final transition is negative, then we should reduce by the rule
    // given by its positive value.

    SR_ const* sr = s_state[d_state];
    SR_ const* last = sr + sr->d_lastIdx;

    for (; ++sr != last;) // visit all but the last SR entries
    {
        if (sr->d_token == d_token)
            return sr->d_action;
    }

    if (sr == last) // reached the last element
    {
        if (sr->d_action < 0) // default reduction
        {
            return sr->d_action;
        }

        // No default reduction, so token not found, so error.
        throw UNEXPECTED_TOKEN_;
    }

    // not at the last element: inspect the nature of the action
    // (< 0: reduce, 0: ACCEPT, > 0: shift)

    int action = sr->d_action;

    return action;
}

// base/pop
void
HTTPTokenizerBase::pop_(size_t count) {
    if (d_stackIdx < static_cast<int>(count)) {
        ABORT();
    }

    d_stackIdx -= count;
    d_state = d_stateStack[d_stackIdx].first;
    d_vsp = &d_stateStack[d_stackIdx];
}

// base/poptoken
void
HTTPTokenizerBase::popToken_() {
    d_token = d_next.first;
    d_val_ = std::move(d_next.second);

    d_next.first = Reserved_::UNDETERMINED_;
}

// base/push
void
HTTPTokenizerBase::push_(size_t state) {
    size_t currentSize = d_stateStack.size();
    if (stackSize_() == currentSize) {
        size_t newSize = currentSize + STACK_EXPANSION_;
        d_stateStack.resize(newSize);
    }

    ++d_stackIdx;
    d_stateStack[d_stackIdx] = StatePair{ d_state = state, std::move(d_val_) };

    d_vsp = &d_stateStack[d_stackIdx];

    if (d_stackIdx == 0) {
    }
    else {
    }
}

// base/pushtoken
void
HTTPTokenizerBase::pushToken_(int token) {
    d_next = TokenPair{ d_token, std::move(d_val_) };
    d_token = token;
}

// base/redotoken
void
HTTPTokenizerBase::redoToken_() {
    if (d_token != Reserved_::UNDETERMINED_)
        pushToken_(d_token);
}

// base/reduce
void
HTTPTokenizerBase::reduce_(int rule) {
    PI_ const& pi = s_productionInfo[rule];

    d_token = pi.d_nonTerm;
    pop_(pi.d_size);

    d_terminalToken = false;
}

// base/shift
void
HTTPTokenizerBase::shift_(int action) {
    push_(action);
    popToken_(); // token processed

    if (d_recovery and d_terminalToken) {
        d_recovery = false;
        d_acceptedTokens_ = 0;
    }
}

// base/startrecovery
void
HTTPTokenizerBase::startRecovery_() {
    int lastToken = d_token; // give the unexpected token a
                             // chance to be processed
                             // again.

    pushToken_(Reserved_::errTok_); // specify errTok_ as next token
    push_(lookup_());               // push the error state

    d_token = lastToken; // reactivate the unexpected
                         // token (we're now in an
                         // ERROR state).

    d_recovery = true;
}

// base/top
inline size_t
HTTPTokenizerBase::top_() const {
    return d_stateStack[d_stackIdx].first;
}

// derived/errorrecovery
void
HTTPTokenizer::errorRecovery_() {
    // When an error has occurred, pop elements off the stack until the top
    // state has an error-item. If none is found, the default recovery
    // mode (which is to abort) is activated.
    //
    // If EOF is encountered without being appropriate for the current state,
    // then the error recovery will fall back to the default recovery mode.
    // (i.e., parsing terminates)

    if (d_acceptedTokens_ >= d_requiredTokens_) // only generate an error-
    {                                           // message if enough tokens
        ++d_nErrors_;                           // were accepted. Otherwise
        error();                                // simply skip input
    }

    // get the error state
    while (not(s_state[top_()][0].d_type & ERR_ITEM)) {
        pop_();
    }

    // In the error state, looking up a token allows us to proceed.
    // Continuation may be require multiple reductions, but eventually a
    // terminal-token shift is used. See nextCycle_ for details.

    startRecovery_();
}

// derived/executeaction
void
HTTPTokenizer::executeAction_(int production) try {
    if (token_() != Reserved_::UNDETERMINED_)
        pushToken_(token_()); // save an already available token
    switch (production) {
            // $insert actioncases

        case 1: {
            if (d_scanner.d_content_length != 0) {
                d_scanner.body();
                d_scanner.d_content_length = 0;
            }
            else if (d_scanner.d_chunked.length() != 0) {
                d_scanner.body();
                d_scanner.d_chunked_length = -1;
                d_scanner.d_chunked.assign("");
            }
        } break;

        case 2: {
            d_scanner.d_content_length = 0;
            d_scanner.init(zpt::http::message_type::request);
        } break;

        case 3: {
            d_scanner.url();
        } break;

        case 4: {
            d_scanner.version();
        } break;

        case 5: {
            if (d_scanner.d_content_length != 0) {
                d_scanner.body();
                d_scanner.d_content_length = 0;
            }
            else if (d_scanner.d_chunked.length() != 0) {
                d_scanner.body();
                d_scanner.d_chunked_length = -1;
                d_scanner.d_chunked.assign("");
            }
        } break;

        case 6: {
            d_scanner.d_content_length = 0;
            d_scanner.init(zpt::http::message_type::reply);
            d_scanner.version();
        } break;

        case 7: {
            d_scanner.status();
        } break;

        case 9: {
            d_val_ = vs_(-1);
        } break;

        case 10: {
            d_scanner.value();
        } break;

        case 11: {
            d_scanner.name();
        } break;

        case 12: {
            d_scanner.value();
        } break;

        case 13: {
            d_scanner.name();
        } break;

        case 15: {
            d_val_ = vs_(0);
        } break;

        case 17: {
            d_val_ = vs_(-1);
        } break;

        case 18: {
            d_val_ = vs_(-2);
        } break;

        case 19: {
            d_val_ = vs_(-1);
        } break;

        case 20: {
            d_scanner.add();
        } break;

        case 21: {
            d_scanner.add();
        } break;

        case 22: {
            d_scanner.add();
        } break;

        case 23: {
            d_scanner.add();
        } break;

        case 24: {
            d_scanner.body();
            d_scanner.d_content_length = 0;
            d_scanner.d_chunked_length = -1;
            d_scanner.d_chunked.assign("");
        } break;
    }
}
catch (std::exception const& exc) {
    exceptionHandler(exc);
}

// derived/nextcycle
void
HTTPTokenizer::nextCycle_() try {
    if (s_state[state_()]->d_type & REQ_TOKEN)
        nextToken_(); // obtain next token

    int action = lookup_(); // lookup d_token in d_state

    if (action > 0) // SHIFT: push a new state
    {
        shift_(action);
        return;
    }

    if (action < 0) // REDUCE: execute and pop.
    {

        if (recovery_())
            redoToken_();
        else
            executeAction_(-action);
        // next token is the rule's LHS
        reduce_(-action);
        return;
    }

    if (recovery_())
        ABORT();
    else
        ACCEPT();
}
catch (ErrorRecovery_) {
    if (not recovery_())
        errorRecovery_();
    else {
        if (token_() == Reserved_::EOF_)
            ABORT();
        popToken_(); // skip the failing token
    }
}

// derived/nexttoken
void
HTTPTokenizer::nextToken_() {
    // If d_token is Reserved_::UNDETERMINED_ then if savedToken_() is
    // Reserved_::UNDETERMINED_ another token is obtained from lex(). Then
    // savedToken_() is assigned to d_token.

    // no need for a token: got one already
    if (token_() != Reserved_::UNDETERMINED_) {
        return;
    }

    if (savedToken_() != Reserved_::UNDETERMINED_) {
        popToken_(); // consume pending token
    }
    else {
        ++d_acceptedTokens_; // accept another token (see
                             // errorRecover())
        lex_(lex());
        print_();
    }
    print();
}

// derived/print
void
HTTPTokenizer::print_() {
    // $insert print
}

// derived/parse
int
HTTPTokenizer::parse() try {
    // The parsing algorithm:
    // Initially, state 0 is pushed on the stack, and all relevant variables
    // are initialized by Base::clearin_.
    //
    // Then, in an eternal loop:
    //
    //  1. If a state is a REQ_TOKEN type, then the next token is obtained
    //     from nextToken().  This may very well be the currently available
    //     token. When retrieving a terminal token d_terminal is set to true.
    //
    //  2. lookup() is called, d_token is looked up in the current state's
    //     SR_ array.
    //
    //  4. Depending on the result of the lookup() function the next state is
    //     shifted on the parser's stack, a reduction by some rule is applied,
    //     or the parsing function returns ACCEPT(). When a reduction is
    //     called for, any action that may have been defined for that
    //     reduction is executed.
    //
    //  5. An error occurs if d_token is not found, and the state has no
    //     default reduction.

    clearin_(); // initialize, push(0)

    while (true) {
        // $insert prompt
        nextCycle_();
    }
}
catch (Return_ retValue) {
    return retValue or d_nErrors_;
}

// derived/tail

// $insert namespace-close
}
