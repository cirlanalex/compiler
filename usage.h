#ifndef USAGE_H
#define USAGE_H

#include "structs.h"

Type transformTypeToVar(Type type);

Type transformTypeToNormal(Type type);

void setAllIdentifiers(IdentifiersStruct *indetifiersStruct);

int checkIfIdentifierExists(char *identifier);

int checkIfIdentifierExistsInCurrentScope(char *identifier);

int checkIfIdentifierMatchesType(char *identifier, Type type);

void addIdentifiersToSymTable(IdentifiersStruct *identifiers, Type type, Type originalType, ReturnType returnType, int lowerBound, int upperBound);

void constDeclarationCheck(char *identifier, ReturnType returnType, int ival, double dval);

void functionDeclarationCheck(char *identifier, ParametersStruct *parameters, ReturnType returnType);

void procedureDeclarationCheck(char *identifier, ParametersStruct *parameters);

void returnMissingCheck();

void arrayTypeCheck(int start, int end);

void statementCheck(LhsStruct lhs, ArithStruct value);

void lhsCheck(char *identifier);

void lhsArrayCheck(char *identifier, ArithStruct value);

void procedureCallCheck(char *identifier);

void procedureCallWithParametersCheck(char *identifier, ArithExprsStruct *arithExprs);

void readlnCheck(LhsListStruct *lhs);

void writelnCheck(ArithExprsStruct *arithExprs);

char *boolCheck(ArithStruct lhs, char* operator, ArithStruct rhs);

ArithStruct arithIdentifierCheck(char *identifier);

ArithStruct arithFunctionCheck(char *identifier, ArithExprsStruct *arithExprs);

ArithStruct arithArrayElementCheck(char *identifier, ArithStruct value);

ArithStruct arithArrayTrimCheck(char *identifier, ArithStruct from, ArithStruct to);

ArithStruct arithOperatorCheck(ArithStruct lhs, ArithStruct rhs, char operator);

ArithStruct arithOperatorDivModCheck(ArithStruct lhs, ArithStruct rhs, char operator);

ArithStruct arithNegationCheck(ArithStruct value);

void freeLastFunctionName();

#endif // USAGE_H