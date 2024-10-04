#ifndef MESSAGES_H
#define MESSAGES_H

#include "structs.h"

char *getTypeString(Type type);

char *getReturnTypeString(ReturnType returnType);

void printIdentifierDoesNotExist(char *identifier);
void printIdentifierAlreadyExists(char *identifier);
void printIdentifierDoesNotMatchType(char *identifier, Type type);
void printInvalidOperandTypes(char operator);
void printIncorrectRange();
void printIncorrectNumberOfParameters();
void printInvalidBoolExpression();
void printSameNameAsFunction(char *identifier);
void printMissingReturnStatement(char *identifier);
void printWrongWriteLnArgument();
void printIdentifierIsNotSet(char *identifier);
void printDivisionByZero();
void printTruncationWarning();

#endif