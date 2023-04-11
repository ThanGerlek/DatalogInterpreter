#ifndef T2K_236PROJECT_PARSER_CPP
#define T2K_236PROJECT_PARSER_CPP

#include "Parser.h"

/**
 * @brief Save to the stack the current location in the input.
 */
void Parser::saveLocation()
{
    savedLocations.push(nextTokenIndex);
}

/**
 * @brief Pop from the stack a location in the input.
 */
void Parser::restoreLocation()
{
    if (savedLocations.empty())
    {
        std::cerr << "[ERROR] Tried to call restoreLocation(), but with no saved locations." << std::endl;
        throw;
    }
    nextTokenIndex = savedLocations.top();
    savedLocations.pop();
}

/**
 * @brief Get the TokenType of the current Token.
 *
 * @return TokenType
 */
TokenType Parser::tokenType()
{
    return tokens->at(nextTokenIndex).getType();
}

/**
 * @brief Get the string value of the current Token.
 *
 * @return std::string
 */
std::string Parser::tokenStr()
{
    return tokens->at(nextTokenIndex).getValue();
}

/**
 * @brief Advance the location in the input to the next Token.
 */
void Parser::advanceToken()
{
    nextTokenIndex++;
    max_nextTokenIndex = nextTokenIndex > max_nextTokenIndex ? nextTokenIndex : max_nextTokenIndex;
}

void Parser::throwError()
{
    throw tokens->at(nextTokenIndex);
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
void Parser::parseTokensIntoDatalogProgram()
{
    try
    {
        datalogProgram();
    }
    catch (Token token)
    {
        Token finalToken = tokens->at(max_nextTokenIndex);
        std::cerr << "[ERROR] Failed to parse program. Ended on Token: " << std::endl
                  << "  " << finalToken.toString() << std::endl;
        throw token;
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

    saveLocation();
    try
    {
        scheme();
        schemeList();
    }
    catch (Token)
    {
        restoreLocation();
        // lambda
    }
}

void Parser::factList()
{
    // factList -> fact factList | lambda

    saveLocation();
    try
    {
        fact();
        factList();
    }
    catch (Token)
    {
        restoreLocation();
        // lambda
    }
}

void Parser::ruleList()
{
    // ruleList -> rule ruleList | lambda

    saveLocation();
    try
    {
        rule();
        ruleList();
    }
    catch (Token)
    {
        restoreLocation();
        // lambda
    }
}

void Parser::queryList()
{
    // queryList -> query queryList | lambda

    saveLocation();
    try
    {
        query();
        queryList();
    }
    catch (Token)
    {
        restoreLocation();
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
    currentRule.addBodyPredicate(pred1);

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

    saveLocation();
    try
    {
        match(COMMA);

        Predicate pred = predicate();
        currentRule.addBodyPredicate(pred);
        predicateList(currentRule);
    }
    catch (Token)
    {
        restoreLocation();
        // lambda
    }
}

void Parser::parameterList(Predicate &currentPredicate)
{
    // parameterList -> COMMA parameter parameterList | lambda

    saveLocation();
    try
    {
        match(COMMA);

        Parameter param = parameter();
        currentPredicate.addParam(param);

        parameterList(currentPredicate);
    }
    catch (Token)
    {
        restoreLocation();
        // lambda
    }
}

void Parser::stringList(Predicate &currentPredicate)
{
    // stringList -> COMMA STRING stringList | lambda

    saveLocation();
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
        restoreLocation();
        // lambda
    }
}

void Parser::idList(Predicate &currentPredicate)
{
    // idList -> COMMA ID idList | lambda

    saveLocation();
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
        restoreLocation();
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
