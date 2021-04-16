// Generated by Bisonc++ V6.03.00 on Tue, 10 Nov 2020 00:20:23 +0000

#ifndef zptURITokenizer_h_included
#define zptURITokenizer_h_included

// $insert baseclass
#include "URITokenizerbase.h"
// $insert scanner.h
#include "URILexer.h"

// $insert namespace-open
namespace zpt {

#undef URITokenizer
// CAVEAT: between the baseclass-include directive and the
// #undef directive in the previous line references to URITokenizer
// are read as URITokenizerBase.
// If you need to include additional headers in this file
// you should do so after these comment-lines.

class URITokenizer : public URITokenizerBase {
    // $insert scannerobject
    URIScanner d_scanner;

  public:
    URITokenizer() = default;
    int parse();

  private:
    void error(); // called on (syntax) errors
    int lex();    // returns the next token from the
                  // lexical scanner.
    void print(); // use, e.g., d_token, d_loc
    void exceptionHandler(std::exception const& exc);

    // support functions for parse():
    void executeAction_(int ruleNr);
    void errorRecovery_();
    void nextCycle_();
    void nextToken_();
    void print_();
};

// $insert namespace-close
}

#endif