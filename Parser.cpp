#ifndef T2K_236PROJECT_PARSER_CPP
#define T2K_236PROJECT_PARSER_CPP

#include "Parser.h"

void Parser::saveLoc()
{
    savedLocs.push(u_location);
}

void Parser::restoreLoc()
{
    if (savedLocs.empty())
    {
        std::cerr << "Error: tried to call restoreLoc(), but with no saved locations." << std::endl;
        throw;
    }
    u_location = savedLocs.top();
    savedLocs.pop();
}

TokenType Parser::tokenType()
{
    return tokens->at(u_location).getType();
}

void Parser::advanceToken()
{
    u_location++;
}

void Parser::throwError()
{
    std::cerr << "Error: invalid Datalog syntax on token " << tokens->at(u_location).toString() << std::endl;
    throw;
}

void Parser::match(TokenType t)
{
    if (tokenType() == t)
    {
        advanceToken();
    }
    else
    {
        std::cerr << "Error: mismatched token types. Expected " << Token::typeName(t)
                  << " but found " << tokens->at(u_location).toString() << std::endl;
        throw;
    }
}

/**
 * Parse this Parser's DatalogProgram using recursive descent.
 */
void Parser::parse()
{

    try
    {
        datalogProgram();

        std::cout << "Success!" << std::endl;
        std::cout << program->toString();
    }
    catch (Token token)
    {
        std::cout << "Failure!" << std::endl
                  << "  " << token.toString() << std::endl;
    }
}

// Recursive descent grammar functions

/* Datalog Grammar:

datalogProgram	->	SCHEMES COLON scheme schemeList
                    FACTS COLON factList
                    RULES COLON ruleList
                    QUERIES COLON query queryList
                    EOF

schemeList	->	scheme schemeList | lambda
factList	->	fact factList | lambda
ruleList	->	rule ruleList | lambda
queryList	->	query queryList | lambda

scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
query	        ->      predicate Q_MARK

headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN

predicateList	->	COMMA predicate predicateList | lambda
parameterList	-> 	COMMA parameter parameterList | lambda
stringList	-> 	COMMA STRING stringList | lambda
idList  	-> 	COMMA ID idList | lambda

parameter	->	STRING | ID
*/

void Parser::datalogProgram()
{
    /*
    datalogProgram	->	SCHEMES COLON scheme schemeList
                        FACTS COLON factList
                        RULES COLON ruleList
                        QUERIES COLON query queryList
                        EOF
    */
    // TODO test

    std::cout << "dlp ";

    match(SCHEMES);
    match(COLON);
    scheme();
    schemeList();
    match(FACTS);
    match(COLON);
    factList();
    match(RULES);
    match(COLON);
    ruleList();
    match(QUERIES);
    match(COLON);
    query();
    queryList();
    match(END_OF_FILE);
}

void Parser::schemeList()
{
    // schemeList -> scheme schemeList | lambda
    // TODO
    std::cout << "schemelist ";

    saveLoc();
    try
    {
        scheme();
        schemeList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::factList()
{
    // factList -> fact factList | lambda
    // TODO
    std::cout << "factlist ";

    saveLoc();
    try
    {
        fact();
        factList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::ruleList()
{
    // ruleList -> rule ruleList | lambda
    // TODO

    std::cout << "rulelist ";

    saveLoc();
    try
    {
        rule();
        ruleList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::queryList()
{
    // queryList -> query queryList | lambda
    // TODO
    std::cout << "querylist ";

    saveLoc();
    try
    {
        query();
        queryList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::scheme()
{
    std::cout << "scheme ";

    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN

    match(ID);
    match(LEFT_PAREN);
    match(ID);
    idList();
    match(RIGHT_PAREN);
}

void Parser::fact()
{
    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    // TODO

    std::cout << "fact ";

    match(ID);
    match(LEFT_PAREN);
    match(STRING);
    stringList();
    match(RIGHT_PAREN);
    match(PERIOD);
}

void Parser::rule()
{
    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    // TODO

    std::cout << "rule ";

    headPredicate();
    match(COLON_DASH);
    predicate();
    predicateList();
    match(PERIOD);
}

void Parser::query()
{
    // query -> predicate Q_MARK
    // TODO

    std::cout << "query ";

    predicate();
    match(Q_MARK);
}

void Parser::headPredicate()
{
    // headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN
    // TODO
    std::cout << "headPredicate ";

    match(ID);
    match(LEFT_PAREN);
    match(ID);
    idList();
    match(RIGHT_PAREN);
}

void Parser::predicate()
{
    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    // TODO

    std::cout << "predicate ";

    match(ID);
    match(LEFT_PAREN);
    parameter();
    parameterList();
    match(RIGHT_PAREN);
}

void Parser::predicateList()
{
    // predicateList -> COMMA predicate predicateList | lambda
    // TODO
    std::cout << "predicatelist ";

    saveLoc();
    try
    {
        match(COMMA);
        predicate();
        predicateList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::parameterList()
{
    std::cout << "parameterlist ";

    // parameterList -> COMMA parameter parameterList | lambda
    // TODO

    saveLoc();
    try
    {
        match(COMMA);
        parameter();
        parameterList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::stringList()
{
    std::cout << "strlist ";

    // stringList -> COMMA STRING stringList | lambda
    // TODO

    saveLoc();
    try
    {
        match(COMMA);
        match(STRING);
        stringList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::idList()
{
    std::cout << "idlist ";

    // idList -> COMMA ID idList | lambda

    saveLoc();
    try
    {
        match(COMMA);
        match(ID);
        idList();
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::parameter()
{
    std::cout << "parameter ";

    // parameter -> STRING | ID
    // TODO
    if (tokenType() == STRING)
    {
        match(STRING);
    }
    else
    {
        match(ID);
    }
}

#endif
