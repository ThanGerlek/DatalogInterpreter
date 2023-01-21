#ifndef PROJECT1_T2K_SCANNER_H
#define PROJECT1_T2K_SCANNER_H

#include <cctype>
#include <vector>
#include "Token.h"

class Scanner
{
private:
    std::string input;
    std::vector<Token> tokens;

public:
    int currentLine;
    Scanner(const std::string &input) : input(input), currentLine(0){};
    Token scanToken();
    void removeWhitespace();
    bool hasNext();

    // MaybeToken scanForIdToken(); // ID token

    // MaybeToken scanForKeywordTokens(TokenType type, std::string &value); // Used for SCHEMES, FACTS, RULES, and QUERIES tokens

    // MaybeToken scanForSchemesToken(); // SCHEMES token
    // MaybeToken scanForFactsToken();   // FACTS token
    // MaybeToken scanForRulesToken();   // RULES token
    // MaybeToken scanForQueriesToken(); // QUERIES token

    MaybeToken scanForWordTokens(); // ID, SCHEMES, FACTS, RULES, and QUERIES tokens

    MaybeToken scanForCharTokens();  // COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, ADD, and MULTIPLY tokens
    MaybeToken scanForColonTokens(); // COLON and COLON_DASH tokens

    MaybeToken scanForEOFToken();     // END_OF_FILE token
    MaybeToken scanForStringToken();  // STRING token
    MaybeToken scanForCommentToken(); // COMMENT token
    MaybeToken scanBlockComment();
};

#endif
