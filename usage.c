#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "symtable.h"
#include "messages.h"
#include "gencode.h"

int isFunction = 0;
int warnings = 0;
char *lastFunctionName = NULL;

Type transformTypeToVar(Type type) {
    if (type == TYPE_VALUE) {
        return TYPE_VAR;
    }
    if (type == TYPE_ARRAY) {
        return TYPE_VAR_ARRAY;
    }
    return type;
}

Type transformTypeToNormal(Type type) {
    if (type == TYPE_VAR) {
        return TYPE_VALUE;
    }
    if (type == TYPE_VAR_ARRAY) {
        return TYPE_ARRAY;
    }
    return type;
}

void freeLastFunctionName() {
    if (lastFunctionName) {
        free(lastFunctionName);
        lastFunctionName = NULL;
    }
}

void setAllIdentifiers(LhsListStruct *lhsList) {
    for (int i = 0; i < lhsList->size; i++) {
        setSet(lhsList->lhsStructs[i].identifier);
    }
}

int checkIfIdentifierExists(char *identifier) {
    if (lookupSymbol(identifier) == -1) {
        return 0;
    }
    return 1;
}

int checkIfIdentifierExistsInCurrentScope(char *identifier) {
    if (getScope(identifier) != getCurrentScope()) {
        return 0;
    }
    return 1;
}

int checkIfIdentifierMatchesType(char *identifier, Type type) {
    Type identifierType = getType(identifier);
    if ((identifierType == TYPE_ARRAY || identifierType == TYPE_VAR_ARRAY) && (type == TYPE_ARRAY || type == TYPE_VAR_ARRAY)) {
        return 1;
    }
    if ((identifierType == TYPE_VALUE || identifierType == TYPE_VAR || identifierType == TYPE_CONST) && (type == TYPE_VALUE || type == TYPE_VAR || identifierType == TYPE_CONST)) {
        return 1;
    }
    if (identifierType == type) {
        return 1;
    }
    return 0;
}

void addIdentifiersToSymTable(IdentifiersStruct *identifiers, Type type, Type originalType, ReturnType returnType, int lowerBound, int upperBound) {
    for (int i = 0; i < identifiers->size; i++) {
        if (isFunction && strcmp(identifiers->names[i], lastFunctionName) == 0) {
            char *identifier = strdup(identifiers->names[i]);
            freeIdentifiersStruct(identifiers);
            printSameNameAsFunction(identifier);
        }
        if (insertSymbol(identifiers->names[i], type, originalType, returnType, 0, 0, lowerBound, upperBound) == -1) {
            char *identifier = strdup(identifiers->names[i]);
            freeIdentifiersStruct(identifiers);
            printIdentifierAlreadyExists(identifier);
        }
        setSet(identifiers->names[i]);
        generateVarDecl(identifiers->names[i]);
    }
    freeIdentifiersStruct(identifiers);
}

void constDeclarationCheck(char *identifier, ReturnType returnType, int ival, double dval) {
    if (insertSymbol(identifier, TYPE_CONST, TYPE_CONST, returnType, ival, dval, 0, 0) == -1) {
        printIdentifierAlreadyExists(identifier);
    }
    setSet(identifier);
    generateConstDecl(identifier);
    free(identifier);
}

void functionDeclarationCheck(char *identifier, ParametersStruct *parameters, ReturnType returnType) {
    if (insertSymbolFunction(identifier, TYPE_FUNCTION, returnType, parameters->size, parameters->paramsNames, parameters->paramsTypes, parameters->paramsReturnTypes, parameters->lowerBounds, parameters->upperBounds) == -1) {
        freeParametersStruct(parameters);
        printIdentifierAlreadyExists(identifier);
    }
    for (int i = 0; i < parameters->size; i++) {
        if (strcmp(parameters->paramsNames[i], identifier) == 0) {
            for (int j = 0; j < parameters->size; j++) {
                free(parameters->paramsNames[j]);
            }
            free(parameters->paramsNames);
            free(parameters);
            printSameNameAsFunction(identifier);
        }
        if (insertSymbol(parameters->paramsNames[i], transformTypeToVar(parameters->paramsTypes[i]), parameters->paramsTypes[i], parameters->paramsReturnTypes[i], 0, 0, parameters->lowerBounds[i], parameters->upperBounds[i]) == -1) {
            free(identifier);
            identifier = strdup(parameters->paramsNames[i]);
            for (int j = 0; j < parameters->size; j++) {
                free(parameters->paramsNames[j]);
            }
            free(parameters->paramsNames);
            free(parameters);
            printIdentifierAlreadyExists(identifier);
        }
        setSet(parameters->paramsNames[i]);
    }
    freeLastFunctionName();
    isFunction = 1;
    lastFunctionName = strdup(identifier);
    for (int i = 0; i < parameters->size; i++) {
        free(parameters->paramsNames[i]);
    }
    free(parameters->paramsNames);
    free(parameters);
    generateFunction(identifier);
    free(identifier);
}

void procedureDeclarationCheck(char *identifier, ParametersStruct *parameters) {
    if (parameters) {
        if (insertSymbolFunction(identifier, TYPE_PROCEDURE, RETURN_TYPE_VOID, parameters->size, parameters->paramsNames, parameters->paramsTypes, parameters->paramsReturnTypes, parameters->lowerBounds, parameters->upperBounds) == -1) {
            freeParametersStruct(parameters);
            printIdentifierAlreadyExists(identifier);
        }
        for (int i = 0; i < parameters->size; i++) {
            if (insertSymbol(parameters->paramsNames[i], transformTypeToVar(parameters->paramsTypes[i]), parameters->paramsTypes[i], parameters->paramsReturnTypes[i], 0, 0, parameters->lowerBounds[i], parameters->upperBounds[i]) == -1) {
                free(identifier);
                identifier = strdup(parameters->paramsNames[i]);
                for (int j = 0; j < parameters->size; j++) {
                    free(parameters->paramsNames[j]);
                }
                free(parameters->paramsNames);
                free(parameters);
                printIdentifierAlreadyExists(identifier);
            }
            setSet(parameters->paramsNames[i]);
        }
        for (int i = 0; i < parameters->size; i++) {
            free(parameters->paramsNames[i]);
        }
        free(parameters->paramsNames);
        free(parameters);
    } else {
        if (insertSymbolFunction(identifier, TYPE_PROCEDURE, RETURN_TYPE_VOID, 0, NULL, NULL, NULL, NULL, NULL) == -1) {
            printIdentifierAlreadyExists(identifier);
        }
    }
    freeLastFunctionName();
    isFunction = 0;
    generateFunction(identifier);
    free(identifier);
}

void arrayTypeCheck(int start, int end) {
    if (start > end) {
        printIncorrectRange();
    }
}

void statementCheck(LhsStruct lhs, ArithStruct value) {
    if (getReturnType(lhs.identifier) == RETURN_TYPE_INTEGER && value.returnType == RETURN_TYPE_REAL) {
        warnings++;
        printTruncationWarning();
    }
    if (getType(lhs.identifier) == TYPE_FUNCTION && strcmp(lhs.identifier, lastFunctionName) != 0) {
        printSameNameAsFunction(lhs.identifier);
    }
    if (value.type == TYPE_ARRAY || value.type == TYPE_VAR_ARRAY) {
        printIdentifierDoesNotMatchType(lhs.identifier, TYPE_VALUE);
    }
    setSet(lhs.identifier);
    generateAssignment(lhs, value.temp);
    free(value.temp);
    free(lhs.identifier);
    free(lhs.temp);
}

void returnMissingCheck() {
    if (isFunction && !isSet(lastFunctionName)) {
        printMissingReturnStatement(lastFunctionName);
    }
    generateFunctionEnd(lastFunctionName);
}

void lhsCheck(char *identifier) {
    if (!checkIfIdentifierExists(identifier)) {
        printIdentifierDoesNotExist(identifier);
    }
    Type type = getType(identifier);
    if (type == TYPE_CONST || type == TYPE_PROCEDURE || type == TYPE_ARRAY || type == TYPE_VAR_ARRAY) {
        printIdentifierDoesNotMatchType(identifier, TYPE_VALUE);
    }
}

void lhsArrayCheck(char *identifier, ArithStruct index) {
    if (!checkIfIdentifierExists(identifier)) {
        printIdentifierDoesNotExist(identifier);
    }
    if (!checkIfIdentifierMatchesType(identifier, TYPE_ARRAY)) {
        printIdentifierDoesNotMatchType(identifier, TYPE_ARRAY);
    }
    if (index.returnType != RETURN_TYPE_INTEGER) {
        printIdentifierDoesNotMatchType(identifier, TYPE_VALUE);
    }
    if (index.type != TYPE_VALUE && index.type != TYPE_VAR && index.type != TYPE_CONST) {
        printIdentifierDoesNotMatchType(identifier, TYPE_VALUE);
    }
}

void procedureCallCheck(char *identifier) {
    if (!checkIfIdentifierExists(identifier)) {
        printIdentifierDoesNotExist(identifier);
    }
    if (!checkIfIdentifierMatchesType(identifier, TYPE_PROCEDURE)) {
        printIdentifierDoesNotMatchType(identifier, TYPE_PROCEDURE);
    }
    if (getSizeParameters(identifier) != 0) {
        printIncorrectNumberOfParameters();
    }
    generateProcedureCall(identifier);
    free(identifier);
}

void procedureCallWithParametersCheck(char *identifier, ArithExprsStruct *arithExprs) {
    if (!checkIfIdentifierExists(identifier)) {
        freeArithExprsStruct(arithExprs);
        printIdentifierDoesNotExist(identifier);
    }
    if (!checkIfIdentifierMatchesType(identifier, TYPE_PROCEDURE)) {
        freeArithExprsStruct(arithExprs);
        printIdentifierDoesNotMatchType(identifier, TYPE_PROCEDURE);
    }
    if (getSizeParameters(identifier) != arithExprs->size) {
        freeArithExprsStruct(arithExprs);
        free(identifier);
        printIncorrectNumberOfParameters();
    }
    for (int i = 0; i < arithExprs->size; i++) {
        Type type = arithExprs->types[i];
        Type type2 = getTypeAtIndex(identifier, i);
        if (type2 == TYPE_FUNCTION || type2 == TYPE_PROCEDURE) {
            freeArithExprsStruct(arithExprs);
            free(identifier);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if ((type2 == TYPE_VAR || type2 == TYPE_VAR_ARRAY) && type != type2) {
            freeArithExprsStruct(arithExprs);
            free(identifier);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if (type2 == TYPE_VALUE && type != TYPE_VALUE && type != TYPE_VAR && type != TYPE_CONST) {
            freeArithExprsStruct(arithExprs);
            free(identifier);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if (type2 == TYPE_ARRAY && type != TYPE_ARRAY && type != TYPE_VAR_ARRAY) {
            freeArithExprsStruct(arithExprs);
            free(identifier);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if (getReturnTypeAtIndex(identifier, i) == RETURN_TYPE_INTEGER && arithExprs->returnTypes[i] == RETURN_TYPE_REAL) {
            warnings++;
            printTruncationWarning();
        }
    }
    generateProcedureCallWithParameters(identifier, arithExprs);
    freeArithExprsStruct(arithExprs);
    free(identifier);
}

void readlnCheck(LhsListStruct *lhs) {
    for (int i = 0; i < lhs->size; i++) {
        Type type = getType(lhs->lhsStructs[i].identifier);
        if (type != TYPE_VAR && type != TYPE_VAR_ARRAY) {
            printIdentifierDoesNotMatchType(lhs->lhsStructs[i].identifier, TYPE_VAR);
            freeLhsListStruct(lhs);
        }
    }
    setAllIdentifiers(lhs);
    generateReadLn(lhs);
    freeLhsListStruct(lhs);
}

void writelnCheck(ArithExprsStruct *arithExprs) {
    for (int i = 0; i < arithExprs->size; i++) {
        Type type = arithExprs->types[i];
        if (type != TYPE_VAR && type != TYPE_VALUE && type != TYPE_CONST) {
            freeArithExprsStruct(arithExprs);
            printWrongWriteLnArgument();
        }
    }
    generateWriteLn(arithExprs);
    freeArithExprsStruct(arithExprs);
}

char *boolCheck(ArithStruct lhs, char *operator, ArithStruct rhs) {
    if (lhs.type != TYPE_VALUE && lhs.type != TYPE_VAR && lhs.type != TYPE_CONST && lhs.type != TYPE_FUNCTION) {
        printInvalidBoolExpression();
    }
    if (rhs.type != TYPE_VALUE && rhs.type != TYPE_VAR && rhs.type != TYPE_CONST && rhs.type != TYPE_FUNCTION) {
        printInvalidBoolExpression();
    }
    char *temp = generateCondition(lhs.temp, operator, rhs.temp);
    free(lhs.temp);
    free(rhs.temp);
    free(operator);
    return temp;
}

ArithStruct arithIdentifierCheck(char *identifier) {
    if (!checkIfIdentifierExists(identifier)) {
        printIdentifierDoesNotExist(identifier);
    }
    Type type = getType(identifier);
    if ((type == TYPE_VAR || type == TYPE_VALUE) && !isSet(identifier)) {
        printIdentifierIsNotSet(identifier);
    }
    // removed type function
    if (type == TYPE_PROCEDURE) {
        printIdentifierDoesNotMatchType(identifier, TYPE_VALUE);
    }
    ArithStruct arithStruct;
    arithStruct.type = type;
    arithStruct.returnType = getReturnType(identifier);
    if (type == TYPE_CONST) {
        if (arithStruct.returnType == RETURN_TYPE_REAL) {
            arithStruct.dval = getDval(identifier);
        } else {
            arithStruct.ival = getIval(identifier);
        }
    }
    if (type == TYPE_FUNCTION) {
        arithStruct.temp = malloc(sizeof(char) * (7 + 1));
        arithStruct.temp[0] = '_';
        strcpy(arithStruct.temp + 1, "return");
    } else {
        arithStruct.temp = strdup(identifier);
    }
    free(identifier);
    return arithStruct;
}

ArithStruct arithFunctionCheck(char *identifier, ArithExprsStruct *arithExprs) {
    if (!checkIfIdentifierExists(identifier)) {
        freeArithExprsStruct(arithExprs);
        printIdentifierDoesNotExist(identifier);
    }
    if (!checkIfIdentifierMatchesType(identifier, TYPE_FUNCTION)) {
        freeArithExprsStruct(arithExprs);
        printIdentifierDoesNotMatchType(identifier, TYPE_FUNCTION);
    }
    if (getSizeParameters(identifier) != arithExprs->size) {
        freeArithExprsStruct(arithExprs);
        free(identifier);
        printIncorrectNumberOfParameters();
    }
    for (int i = 0; i < arithExprs->size; i++) {
        Type type = arithExprs->types[i];
        Type type2 = getTypeAtIndex(identifier, i);
        if (type2 == TYPE_FUNCTION || type2 == TYPE_PROCEDURE) {
            freeArithExprsStruct(arithExprs);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if ((type2 == TYPE_VAR || type2 == TYPE_VAR_ARRAY) && type != type2) {
            freeArithExprsStruct(arithExprs);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if (type2 == TYPE_VALUE && type != TYPE_VALUE && type != TYPE_VAR && type != TYPE_CONST) {
            freeArithExprsStruct(arithExprs);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if (type2 == TYPE_ARRAY && type != TYPE_ARRAY && type != TYPE_VAR_ARRAY) {
            freeArithExprsStruct(arithExprs);
            printIdentifierDoesNotMatchType(identifier, type2);
        }
        if (getReturnTypeAtIndex(identifier, i) == RETURN_TYPE_INTEGER && arithExprs->returnTypes[i] == RETURN_TYPE_REAL) {
            warnings++;
            printTruncationWarning();
        }
    }
    ArithStruct arithStruct;
    arithStruct.temp = generateFunctionCall(identifier, arithExprs);
    freeArithExprsStruct(arithExprs);
    arithStruct.type = TYPE_VALUE;
    arithStruct.returnType = getReturnType(identifier);
    free(identifier);
    return arithStruct;
}

ArithStruct arithArrayElementCheck(char *identifier, ArithStruct value) {
    if (!checkIfIdentifierExists(identifier)) {
        printIdentifierDoesNotExist(identifier);
    }
    if (!isSet(identifier)) {
        printIdentifierIsNotSet(identifier);
    }
    if (!checkIfIdentifierMatchesType(identifier, TYPE_ARRAY)) {
        printIdentifierDoesNotMatchType(identifier, TYPE_ARRAY);
    }
    if (value.returnType != RETURN_TYPE_INTEGER) {
        printIdentifierDoesNotMatchType(identifier, TYPE_VALUE);
    }
    ArithStruct arithStruct;
    arithStruct.type = TYPE_VAR;
    arithStruct.returnType = getReturnType(identifier);
    arithStruct.temp = generateArrayElement(identifier, value.temp);
    arithStruct.arrayElement = 1;
    free(value.temp);
    free(identifier);
    return arithStruct;
}

ArithStruct arithArrayTrimCheck(char *identifier, ArithStruct from, ArithStruct to) {
    if (!checkIfIdentifierExists(identifier)) {
        printIdentifierDoesNotExist(identifier);
    }
    if (!checkIfIdentifierMatchesType(identifier, TYPE_ARRAY)) {
        printIdentifierDoesNotMatchType(identifier, TYPE_ARRAY);
    }
    if (from.returnType != RETURN_TYPE_INTEGER || to.returnType != RETURN_TYPE_INTEGER) {
        printIdentifierDoesNotMatchType(identifier, TYPE_VALUE);
    }
    if (from.ival > to.ival) {
        printIncorrectRange();
    }
    ArithStruct arithStruct;
    arithStruct.type = TYPE_VAR_ARRAY;
    arithStruct.returnType = getReturnType(identifier);
    arithStruct.temp = generateArrayTrim(identifier, from.temp, to.temp);
    arithStruct.lowerBound = from.temp;
    arithStruct.upperBound = to.temp;
    free(identifier);
    return arithStruct;
}

ArithStruct arithOperatorCheck(ArithStruct lhs, ArithStruct rhs, char operator) {
    if (lhs.type == TYPE_ARRAY || lhs.type == TYPE_VAR_ARRAY || rhs.type == TYPE_ARRAY || rhs.type == TYPE_VAR_ARRAY) {
        printInvalidOperandTypes(operator);
    }
    ArithStruct arithStruct;
    if (lhs.returnType == RETURN_TYPE_REAL || rhs.returnType == RETURN_TYPE_REAL || operator == '/') {
        arithStruct.returnType = RETURN_TYPE_REAL;
    } else {
        arithStruct.returnType = RETURN_TYPE_INTEGER;
    }
    if (lhs.type == TYPE_CONST && rhs.type == TYPE_CONST) {
        if (lhs.returnType == RETURN_TYPE_REAL) {
            if (rhs.returnType == RETURN_TYPE_REAL) {
                if (operator == '+') {
                    arithStruct.dval = lhs.dval + rhs.dval;
                } else if (operator == '-') {
                    arithStruct.dval = lhs.dval - rhs.dval;
                } else if (operator == '*') {
                    arithStruct.dval = lhs.dval * rhs.dval;
                } else if (operator == '/') {
                    if (rhs.dval == 0) {
                        printDivisionByZero();
                    }
                    arithStruct.dval = lhs.dval / rhs.dval;
                }
            } else {
                if (operator == '+') {
                    arithStruct.dval = lhs.dval + rhs.ival;
                } else if (operator == '-') {
                    arithStruct.dval = lhs.dval - rhs.ival;
                } else if (operator == '*') {
                    arithStruct.dval = lhs.dval * rhs.ival;
                } else if (operator == '/') {
                    if (rhs.ival == 0) {
                        printDivisionByZero();
                    }
                    arithStruct.dval = lhs.dval / rhs.ival;
                }
            }
        } else {
            if (rhs.returnType == RETURN_TYPE_REAL) {
                if (operator == '+') {
                    arithStruct.dval = lhs.ival + rhs.dval;
                } else if (operator == '-') {
                    arithStruct.dval = lhs.ival - rhs.dval;
                } else if (operator == '*') {
                    arithStruct.dval = lhs.ival * rhs.dval;
                } else if (operator == '/') {
                    if (rhs.dval == 0) {
                        printDivisionByZero();
                    }
                    arithStruct.dval = lhs.ival / rhs.dval;
                }
            } else {
                if (operator == '+') {
                    arithStruct.ival = lhs.ival + rhs.ival;
                } else if (operator == '-') {
                    arithStruct.ival = lhs.ival - rhs.ival;
                } else if (operator == '*') {
                    arithStruct.ival = lhs.ival * rhs.ival;
                } else if (operator == '/') {
                    if (rhs.ival == 0) {
                        printDivisionByZero();
                    }
                    arithStruct.ival = lhs.ival / rhs.ival;
                }
            }
        }
        arithStruct.type = TYPE_CONST;
        arithStruct.temp = generateOperation(lhs.temp, rhs.temp, operator, arithStruct.returnType);
        free(lhs.temp);
        free(rhs.temp);
        return arithStruct;
    }
    arithStruct.type = TYPE_VALUE;
    arithStruct.temp = generateOperation(lhs.temp, rhs.temp, operator, arithStruct.returnType);
    free(lhs.temp);
    free(rhs.temp);
    return arithStruct;
}

ArithStruct arithOperatorDivModCheck(ArithStruct lhs, ArithStruct rhs, char operator) {
    if (lhs.returnType == RETURN_TYPE_REAL || rhs.returnType == RETURN_TYPE_REAL || lhs.type == TYPE_ARRAY || lhs.type == TYPE_VAR_ARRAY || rhs.type == TYPE_ARRAY || rhs.type == TYPE_VAR_ARRAY) {
        printInvalidOperandTypes(operator);
    }
    ArithStruct arithStruct;
    arithStruct.returnType = RETURN_TYPE_INTEGER;
    if (lhs.type == TYPE_CONST && rhs.type == TYPE_CONST) {
        if (rhs.ival == 0) {
            printDivisionByZero();
        }
        if (operator == ':') {
            arithStruct.ival = lhs.ival / rhs.ival;
        } else {
            arithStruct.ival = lhs.ival % rhs.ival;
        }
        arithStruct.type = TYPE_CONST;
        if (operator == ':') {
            arithStruct.temp = generateOperation(lhs.temp, rhs.temp, '/', arithStruct.returnType);
        } else {
            arithStruct.temp = generateOperation(lhs.temp, rhs.temp, '%', arithStruct.returnType);
        }
        free(lhs.temp);
        free(rhs.temp);
        return arithStruct;
    }
    arithStruct.type = TYPE_VALUE;
    if (operator == ':') {
        arithStruct.temp = generateOperation(lhs.temp, rhs.temp, '/', arithStruct.returnType);
    } else {
        arithStruct.temp = generateOperation(lhs.temp, rhs.temp, '%', arithStruct.returnType);
    }
    free(lhs.temp);
    free(rhs.temp);
    return arithStruct;
}

ArithStruct arithNegationCheck(ArithStruct value) {
    if (value.type == TYPE_ARRAY || value.type == TYPE_VAR_ARRAY) {
        printInvalidOperandTypes('-');
    }
    ArithStruct arithStruct;
    arithStruct.returnType = value.returnType;
    if (value.type == TYPE_CONST) {
        if (value.returnType == RETURN_TYPE_REAL) {
            arithStruct.dval = -value.dval;
        } else {
            arithStruct.ival = -value.ival;
        }
        arithStruct.type = TYPE_CONST;
        arithStruct.temp = generateNegation(value.temp, arithStruct.returnType);
        free(value.temp);
        return arithStruct;
    }
    arithStruct.type = TYPE_VALUE;
    arithStruct.temp = generateNegation(value.temp, arithStruct.returnType);
    free(value.temp);
    return arithStruct;
}