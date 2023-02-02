#ifndef T2K_236PROJECT_PARSER_CPP
#define T2K_236PROJECT_PARSER_CPP

#include "Parser.h"

void Parser::saveLoc()
{
    // TODO
}

void Parser::restoreLoc()
{
    // TODO
}

/**
 * Parse this Parser's DatalogProgram using recursive descent.
 * Throws an error if the program is invalid.
 */
void Parser::parse()
{
    // TODO
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

bool Parser::datalogProgram() const
{
    /*
    datalogProgram	->	SCHEMES COLON scheme schemeList
                        FACTS COLON factList
                        RULES COLON ruleList
                        QUERIES COLON query queryList
                        EOF
    */
    // TODO
}

bool Parser::schemeList() const
{
    // schemeList -> scheme schemeList | lambda
    // TODO
}

bool Parser::factList() const
{
    // factList -> fact factList | lambda
    // TODO
}

bool Parser::ruleList() const
{
    // ruleList -> rule ruleList | lambda
    // TODO
}

bool Parser::queryList() const
{
    // queryList -> query queryList | lambda
    // TODO
}

bool Parser::scheme() const
{
    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    // TODO
}

bool Parser::fact() const
{
    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    // TODO
}

bool Parser::rule() const
{
    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    // TODO
}

bool Parser::query() const
{
    // query -> predicate Q_MARK
    // TODO
}

bool Parser::headPredicate() const
{
    // headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN
    // TODO
}

bool Parser::predicate() const
{
    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    // TODO
}

bool Parser::predicateList() const
{
    // predicateList -> COMMA predicate predicateList | lambda
    // TODO
}

bool Parser::parameterList() const
{
    // parameterList -> COMMA parameter parameterList | lambda
    // TODO
}

bool Parser::stringList() const
{
    // stringList -> COMMA STRING stringList | lambda
    // TODO
}

bool Parser::idList() const
{
    // idList -> COMMA ID idList | lambda
    // TODO
}

bool Parser::parameter() const
{
    // parameter -> STRING | ID
    // TODO
}

#endif
