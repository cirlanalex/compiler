#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "structs.h"

int insertSymbol(char *name, Type type, Type originalType, ReturnType returnType, int ival, double dval, int lowerBound, int upperBound);
int insertSymbolFunction(char *name, Type type, ReturnType returnType, int paramsSize, char **paramsNames, Type *paramsTypes, ReturnType *paramsReturnTypes, int *lowerBounds, int *upperBounds);

int lookupSymbol(char *name);

Type getType(char *name);

Type getOriginalType(char *name);

Type getTypeAtIndex(char *name, int index);

ReturnType getReturnType(char *name);

ReturnType getReturnTypeAtIndex(char *name, int index);

int getScope(char *name);

int getCurrentScope();

int isSet(char *name);
void setSet(char *name);

int getSizeParameters(char *name);
char **getParametersNames(char *name);
Type *getParametersTypes(char *name);
ReturnType *getParametersReturnTypes(char *name);

int getIval(char *name);

double getDval(char *name);

void enterScope();
void exitScope();

void printSymbolTable();

void freeSymbolTable();

int getLowerBound(char *name);
int getUpperBound(char *name);

#endif // SYMTABLE_H