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

std::string Parser::tokenStr()
{
    return tokens->at(u_location).getValue();
}

void Parser::advanceToken()
{
    u_location++;
    u_max_location = u_location > u_max_location ? u_location : u_max_location;
}

void Parser::throwError()
{
    std::cerr << "Error: invalid Datalog syntax on token " << tokens->at(u_location).toString() << std::endl;
    throw;
}

void Parser::match(TokenType type)
{
    if (tokenType() == type)
    {
        std::cout << "[" << Token::typeName(type) << "] ";
        advanceToken();
    }
    else
    {
        std::cerr << "Error: mismatched token types. Expected " << Token::typeName(type)
                  << " but found " << tokens->at(u_location).toString() << std::endl;
        throw tokens->at(u_location);
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
        Token finalToken = tokens->at(u_max_location);
        std::cout << "Failure!" << std::endl
                  << "  " << finalToken.toString() << std::endl;
    }
}

// Recursive descent grammar functions

/* Datalog Grammar:

datalogProgram	->	SCHEMES COLON scheme schemeList
                    FACTS   COLON factList
                    RULES   COLON ruleList
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

void Parser::schemeList() //? Done
{
    // schemeList -> scheme schemeList | lambda
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

void Parser::factList() //? Done
{
    // factList -> fact factList | lambda
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

void Parser::ruleList() //? Done
{
    // ruleList -> rule ruleList | lambda
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

void Parser::queryList() //? Done
{
    // queryList -> query queryList | lambda
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

void Parser::scheme() //? Done
{
    std::cout << "scheme ";
    // scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN

    Predicate currentScheme(tokenStr()); // Predicate ID
    match(ID);

    match(LEFT_PAREN);

    Parameter param1(tokenStr(), true); // First parameter
    currentScheme.addParam(param1);
    match(ID);

    idList(currentScheme); // Remaining parameters

    match(RIGHT_PAREN);
    program->addScheme(currentScheme);
}

void Parser::fact() //? Done
{
    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    std::cout << "fact ";

    Predicate currentFact(tokenStr()); // Predicate ID
    match(ID);

    match(LEFT_PAREN);

    Parameter param1(tokenStr(), false); // First parameter
    currentFact.addParam(param1);
    match(STRING);

    stringList(currentFact); // Remaining parameters

    match(RIGHT_PAREN);
    match(PERIOD);
    program->addFact(currentFact);
}

void Parser::rule() //? Done
{
    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD
    std::cout << "rule ";

    Rule currentRule(headPredicate()); // Rule head

    match(COLON_DASH);

    Predicate pred1 = predicate(); // First predicate
    currentRule.addPredicate(pred1);

    predicateList(currentRule); // Remaining predicates

    match(PERIOD);
    program->addRule(currentRule);
}

void Parser::query() // Done.
{
    // query -> predicate Q_MARK
    std::cout << "query ";

    Predicate currentQuery = predicate();
    match(Q_MARK);
    program->addQuery(currentQuery);
}

Predicate Parser::headPredicate() //? Done
{
    // headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN
    std::cout << "headPredicate ";

    Predicate currentPred(tokenStr()); // Predicate id
    match(ID);

    match(LEFT_PAREN);

    Parameter param1(tokenStr()); // First parameter
    match(ID);
    currentPred.addParam(param1);

    idList(currentPred); // Remaining parameters

    match(RIGHT_PAREN);
    return currentPred;
}

Predicate Parser::predicate() //? Done
{
    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    std::cout << "predicate ";

    Predicate currentPred(tokenStr()); // Predicate id
    match(ID);

    match(LEFT_PAREN);

    Parameter param1 = parameter(); // First parameter
    currentPred.addParam(param1);

    parameterList(currentPred); // Remaining parameters

    match(RIGHT_PAREN);
    return currentPred;
}

void Parser::predicateList(Rule &currentRule) //? Done
{
    // predicateList -> COMMA predicate predicateList | lambda
    std::cout << "predicatelist ";

    saveLoc();

    try
    {
        match(COMMA);

        Predicate pred = predicate();
        currentRule.addPredicate(pred); // Add predicate

        // try
        // {
        predicateList(currentRule);
        // }
        // catch (Token t)
        // {
        //     Should be unreachable, because predicateList can go to lambda
        //     currentRule.erasePredicate();
        //     throw t;
        // }
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::parameterList(Predicate &currentPredicate) //? Done
{
    // parameterList -> COMMA parameter parameterList | lambda
    std::cout << "parameterlist ";

    saveLoc();
    try
    {
        match(COMMA);

        Parameter param = parameter();
        currentPredicate.addParam(param);

        parameterList(currentPredicate);
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::stringList(Predicate &currentPredicate) //? Done
{
    // stringList -> COMMA STRING stringList | lambda
    std::cout << "strlist ";

    saveLoc();
    try
    {
        match(COMMA);

        Parameter param(tokenStr(), false);
        match(STRING);
        currentPredicate.addParam(param);

        stringList(currentPredicate);
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::idList(Predicate &currentPredicate) //? Done
{
    std::cout << "idlist ";

    // idList -> COMMA ID idList | lambda

    saveLoc();
    try
    {
        match(COMMA);

        Parameter param(tokenStr(), true);
        match(ID);
        currentPredicate.addParam(param);

        idList(currentPredicate);
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

Parameter Parser::parameter() //? Done
{
    // parameter -> STRING | ID
    std::cout << "parameter ";

    Parameter param(tokenStr());
    if (tokenType() == STRING)
    {
        match(STRING);
        param.setIsVariable(false);
    }
    else
    {
        match(ID);
        param.setIsVariable(true);
    }
    return param;
}

#endif
