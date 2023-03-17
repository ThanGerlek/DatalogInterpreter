#ifndef T2K_236PROJECT_PARSER_CPP
#define T2K_236PROJECT_PARSER_CPP

#include "Parser.h"

/**
 * @brief Save to the stack the current location in the input.
 */
void Parser::saveLoc()
{
    savedLocs.push(u_location);
}

/**
 * @brief Pop from the stack a location in the input.
 */
void Parser::restoreLoc()
{
    if (savedLocs.empty())
    {
        std::cerr << "[ERROR] Tried to call restoreLoc(), but with no saved locations." << std::endl;
        throw;
    }
    u_location = savedLocs.top();
    savedLocs.pop();
}

/**
 * @brief Get the TokenType of the current Token.
 * 
 * @return TokenType 
 */
TokenType Parser::tokenType()
{
    return tokens->at(u_location).getType();
}

/**
 * @brief Get the string value of the current Token.
 * 
 * @return std::string 
 */
std::string Parser::tokenStr()
{
    return tokens->at(u_location).getValue();
}

/**
 * @brief Advance the location in the input to the next Token.
 */
void Parser::advanceToken()
{
    u_location++;
    u_max_location = u_location > u_max_location ? u_location : u_max_location;
}

void Parser::throwError()
{
    throw tokens->at(u_location);
}

/**
 * @brief Advance the input if the current Token matches the given type; otherwise throw an error.
 *
 * @param type
 */
void Parser::match(TokenType type)
{
    if (tokenType() == type)
    {
        advanceToken();
    }
    else
    {
        throwError();
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
    }
    catch (Token token)
    {
        Token finalToken = tokens->at(u_max_location);
        std::cerr << "[ERROR] Failed to parse program. Ended on Token: " << std::endl
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

void Parser::fact()
{
    // fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD

    Predicate currentFact(tokenStr()); // Predicate ID
    match(ID);

    match(LEFT_PAREN);

    Parameter param1(tokenStr(), false); // First parameter
    currentFact.addParam(param1);
    match(STRING);
    program->addToDomain(param1.toString());

    stringList(currentFact); // Remaining parameters

    match(RIGHT_PAREN);
    match(PERIOD);
    program->addFact(currentFact);
}

void Parser::rule()
{
    // rule -> headPredicate COLON_DASH predicate predicateList PERIOD

    Rule currentRule(headPredicate()); // Rule head

    match(COLON_DASH);

    Predicate pred1 = predicate(); // First predicate
    currentRule.addPredicate(pred1);

    predicateList(currentRule); // Remaining predicates

    match(PERIOD);
    program->addRule(currentRule);
}

void Parser::query()
{
    // query -> predicate Q_MARK

    Predicate currentQuery = predicate();
    match(Q_MARK);
    program->addQuery(currentQuery);
}

Predicate Parser::headPredicate()
{
    // headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN

    Predicate currentPred(tokenStr()); // Predicate id
    match(ID);

    match(LEFT_PAREN);
    Parameter param1(tokenStr(), tokenType() != STRING); // First parameter
    match(ID);
    currentPred.addParam(param1);

    idList(currentPred); // Remaining parameters

    match(RIGHT_PAREN);
    return currentPred;
}

Predicate Parser::predicate()
{
    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN

    Predicate currentPred(tokenStr()); // Predicate id
    match(ID);

    match(LEFT_PAREN);

    Parameter param1 = parameter(); // First parameter
    currentPred.addParam(param1);

    parameterList(currentPred); // Remaining parameters

    match(RIGHT_PAREN);
    return currentPred;
}

void Parser::predicateList(Rule &currentRule)
{
    // predicateList -> COMMA predicate predicateList | lambda

    saveLoc();
    try
    {
        match(COMMA);

        Predicate pred = predicate();
        currentRule.addPredicate(pred);
        predicateList(currentRule);
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::parameterList(Predicate &currentPredicate)
{
    // parameterList -> COMMA parameter parameterList | lambda

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

void Parser::stringList(Predicate &currentPredicate)
{
    // stringList -> COMMA STRING stringList | lambda

    saveLoc();
    try
    {
        match(COMMA);

        Parameter param(tokenStr(), false);
        match(STRING);
        currentPredicate.addParam(param);
        program->addToDomain(param.toString());

        stringList(currentPredicate);
    }
    catch (Token)
    {
        restoreLoc();
        // lambda
    }
}

void Parser::idList(Predicate &currentPredicate)
{
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

Parameter Parser::parameter()
{
    // parameter -> STRING | ID

    Parameter param(tokenStr(), true);
    if (tokenType() == STRING)
    {
        match(STRING);
        param.setIsVariable(false);
    }
    else
    {
        match(ID);
    }
    return param;
}

#endif
