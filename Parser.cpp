#ifndef T2K_236PROJECT_PARSER_CPP
#define T2K_236PROJECT_PARSER_CPP

#include "Parser.h"

void Parser::saveLoc()
{
    savedLocs.push(location);
}

void Parser::restoreLoc()
{
    if (savedLocs.empty())
    {
        std::string msg = "Error: tried to restoreLoc, but with no saved locations.";
        std::cout << msg << std::endl;
        throw;
    }
    location = savedLocs.top();
    savedLocs.pop();
}

TokenType Parser::tokenType()
{
    return tokens->at(location).getType();
}

void Parser::advanceToken()
{
    location++;
}

void Parser::throwError()
{
    std::cout << "Error: invalid Datalog syntax on token " << tokens->at(location).toString() << std::endl;
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
        std::cout << "Error: mismatched token types. Expected " << Token::typeName(t)
                  << " but found " << tokens->at(location).toString() << std::endl;
        throw;
    }
}

/**
 * Parse this Parser's DatalogProgram using recursive descent.
 */
void Parser::parse()
{
    // TODO

    bool accepted = datalogProgram();
    if (accepted)
    {
        const std::vector<Predicate> *schemes = program->getSchemes();
        const std::vector<Predicate> *facts = program->getFacts();
        const std::vector<Predicate> *queries = program->getQueries();
        const std::vector<Rule> *rules = program->getRules();

        std::cout << "Success!" << std::endl;
        std::cout << program->toString();
    }
    else
    {
        // TODO print failure msg
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
    return false;
}

bool Parser::schemeList() const
{
    // schemeList -> scheme schemeList | lambda
    // TODO
    return false;
}

bool Parser::factList() const
{
    // factList -> fact factList | lambda
    // TODO
    return false;
}

bool Parser::ruleList() const
{
    // ruleList -> rule ruleList | lambda
    // TODO
    return false;
}

bool Parser::queryList() const
{
    // queryList -> query queryList | lambda
    // TODO
    return false;
}

bool Parser::scheme() const
{
    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    // TODO
    return false;
}

bool Parser::fact() const
{
    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    // TODO
    return false;
}

bool Parser::rule() const
{
    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    // TODO
    return false;
}

bool Parser::query() const
{
    // query -> predicate Q_MARK
    // TODO
    return false;
}

bool Parser::headPredicate() const
{
    // headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN
    // TODO
    return false;
}

bool Parser::predicate() const
{
    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    // TODO
    return false;
}

bool Parser::predicateList() const
{
    // predicateList -> COMMA predicate predicateList | lambda
    // TODO
    return false;
}

bool Parser::parameterList() const
{
    // parameterList -> COMMA parameter parameterList | lambda
    // TODO
    return false;
}

bool Parser::stringList() const
{
    // stringList -> COMMA STRING stringList | lambda
    // TODO
    return false;
}

bool Parser::idList() const
{
    // idList -> COMMA ID idList | lambda
    // TODO
    return false;
}

bool Parser::parameter() const
{
    // parameter -> STRING | ID
    // TODO
    return false;
}

#endif
