#ifndef GENCODE_H
#define GENCODE_H

void generateHeader();

void generateVarDecl(char *name);

void generateConstDecl(char *name);

void generateMain();

void generateFunction(char *name);

void generateFunctionEnd(char *lastFunctionName);

void generateNewLine();

char *generateInteger(int ival);

char *generateReal(double dval);

char *generateOperation(char *lhs, char *rhs, char operator, ReturnType returnType);

char *generateFunctionCall(char *identifier, ArithExprsStruct *arithExprs);

char *generateArrayElement(char *identifier, char *value);

void generateAssignment(LhsStruct lhs, char *value);

char *generateNegation(char *value, ReturnType returnType);

char *generateCondition(char *lhs, char *operator, char *rhs);

char *generateNot(char *value);

char *generateAnd(char *lhs, char *rhs);

char *generateOr(char *lhs, char *rhs);

int generateIfLabel(char *value);

int generateElseLabel(int label);

void generateLabel(int label);

int generateWhileLabel();

void generateWhileLabelCheck(char *value, int label);

void generateWhileLabelFinal(int label);

void generateWriteLn(ArithExprsStruct *arithExprs);

void generateReadLn(LhsListStruct *lhsListStruct);

void generateProcedureCall(char *identifier);

void generateProcedureCallWithParameters(char *identifier, ArithExprsStruct *arithExprs);

char *generateArrayTrim(char *identifier, char *lowerBound, char *upperBound);

#endif