#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

extern void error();
extern void showErrorLine();

char *getTypeString(Type type) {
    switch (type) {
        case TYPE_VALUE:
            return "VALUE";
        case TYPE_VAR:
            return "VAR";
        case TYPE_ARRAY:
            return "ARRAY";
        case TYPE_VAR_ARRAY:
            return "VAR_ARRAY";
        case TYPE_FUNCTION:
            return "FUNCTION";
        case TYPE_PROCEDURE:
            return "PROCEDURE";
        default:
            return "unknown";
    }
}

char *getReturnTypeString(ReturnType returnType) {
    switch (returnType) {
        case RETURN_TYPE_VOID:
            return "VOID";
        case RETURN_TYPE_INTEGER:
            return "INTEGER";
        case RETURN_TYPE_REAL:
            return "REAL";
        default:
            return "unknown";
    }
}

void printIdentifierDoesNotExist(char *identifier) {
  showErrorLine();
  fprintf(stderr, "Error: Identifier '%s' was not declared.\n", identifier);
  free(identifier);
  error();
}

void printIdentifierAlreadyExists(char *identifier) {
  showErrorLine();
  fprintf(stderr, "Error: Identifier '%s' was already declared.\n", identifier);
  free(identifier);
  error();
}

void printIdentifierDoesNotMatchType(char *identifier, Type type) {
  showErrorLine();
  fprintf(stderr, "Error: Identifier '%s' does not match type '%s'.\n", identifier, getTypeString(type));
  free(identifier);
  error();
}

void printInvalidOperandTypes(char operator) {
  showErrorLine();
  fprintf(stderr, "Error: Invalid operand types for operator '%c'.\n", operator);
  error();
}

void printIncorrectRange() {
  showErrorLine();
  fprintf(stderr, "Error: Lower bound of range is greater than upper bound.\n");
  error();
}

void printIncorrectNumberOfParameters() {
  showErrorLine();
  fprintf(stderr, "Error: Incorrect number of parameters.\n");
  error();
}

void printInvalidBoolExpression() {
  showErrorLine();
  fprintf(stderr, "Error: Invalid boolean expression.\n");
  error();
}

void printSameNameAsFunction(char *identifier) {
  showErrorLine();
  fprintf(stderr, "Error: Identifier '%s' has the same name as the function it is in.\n", identifier);
  free(identifier);
  error();
}

void printWrongWriteLnArgument() {
  showErrorLine();
  fprintf(stderr, "Error: Wrong argument for WRITELN.\n");
  error();
}

void printMissingReturnStatement(char *identifier) {
  showErrorLine();
  fprintf(stderr, "Error: Missing return statement for function '%s'.\n", identifier);
  error();
}

void printIdentifierIsNotSet(char *identifier) {
  showErrorLine();
  fprintf(stderr, "Error: Identifier '%s' is not set.\n", identifier);
  free(identifier);
  error();
}

void printDivisionByZero() {
  showErrorLine();
  fprintf(stderr, "Error: Division by zero.\n");
  error();
}

void printTruncationWarning() {
  showErrorLine();
  fprintf(stderr, "Warning: Truncation of real value.\n");
}