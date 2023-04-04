#ifndef CS236_PROJECT1_T2K_SCANNER_H
#define CS236_PROJECT1_T2K_SCANNER_H

#include <cctype>
#include <queue>
#include <vector>
#include <fstream>
#include "Token.h"

class Scanner
{
public:
    Scanner(const std::string &_inputString) : inputString(_inputString), reachedEOF(false), currentLine(1){};

    void scanTokensInto(std::vector<Token> &tokens);

private:
    std::string inputString;
    bool reachedEOF;
    int currentLine;

    void scanNextTokenInto(std::vector<Token> &tokens);

    Token scanNextToken();
    bool hasNextToken() const;

    MaybeToken scanForWordTokens(); // ID, SCHEMES, FACTS, RULES, and QUERIES tokens

    MaybeToken scanForCharTokens();  // COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, ADD, and MULTIPLY tokens
    MaybeToken scanForColonTokens(); // COLON and COLON_DASH tokens

    MaybeToken scanForEOFToken();     // END_OF_FILE token
    MaybeToken scanForStringToken();  // STRING token
    MaybeToken scanForCommentToken(); // COMMENT token
    MaybeToken scanBlockComment();

    void removeWhitespaceFromInput();
};

#endif
