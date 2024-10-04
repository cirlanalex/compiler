#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum Type {
    TYPE_VALUE,
    TYPE_VAR,
    TYPE_CONST,
    TYPE_ARRAY,
    TYPE_VAR_ARRAY,
    TYPE_FUNCTION,
    TYPE_PROCEDURE
} Type;

typedef enum ReturnType {
    RETURN_TYPE_INTEGER,
    RETURN_TYPE_REAL,
    RETURN_TYPE_VOID
} ReturnType;

typedef struct IdentifiersStruct {
    char **names;
    int size;
} IdentifiersStruct;

typedef struct ParametersStruct {
    char **paramsNames;
    Type *paramsTypes;
    ReturnType *paramsReturnTypes;
    int *lowerBounds;
    int *upperBounds;
    int size;
} ParametersStruct;

typedef struct TypeSpecStruct {
    Type type;
    ReturnType returnType;
    int lowerBound;
    int upperBound;
} TypeSpecStruct;

typedef struct ArithStruct {
    Type type;
    ReturnType returnType;
    int ival;
    double dval;
    char *lowerBound;
    char *upperBound;
    char *temp;
    int arrayElement;
} ArithStruct;

typedef struct ArithExprsStruct {
    Type *types;
    ReturnType *returnTypes;
    char **lowerBounds;
    char **upperBounds;
    int size;
    char **temps;
    int *arrayElements;
} ArithExprsStruct;

typedef struct NumberStruct {
    ReturnType returnType;
    int ival;
    double dval;
} NumberStruct;

typedef struct LhsStruct {
    char *identifier;
    char *temp;
} LhsStruct;

typedef struct LhsListStruct {
    LhsStruct *lhsStructs;
    int size;
} LhsListStruct;

IdentifiersStruct *createIdentifiersStruct(char *name);
void addIdentifier(IdentifiersStruct *identifiersStruct, char *name);
void freeIdentifiersStruct(IdentifiersStruct *identifiersStruct);

ParametersStruct *createParametersStruct(IdentifiersStruct *identifiers, Type type, ReturnType returnType, int lowerBound, int upperBound);
void addParameterList(ParametersStruct *parametersStruct, ParametersStruct *parametersStruct2);
void freeParametersStruct(ParametersStruct *parametersStruct);

ArithExprsStruct *createArithExprsStruct(Type type, ReturnType returnType, char *temp, char *lowerBound, char *upperBound, int arrayElement);
void addArithExpr(ArithExprsStruct *arithExprsStruct, Type type, ReturnType returnType, char *temp, char *lowerBound, char *upperBound, int arrayElement);
void freeArithExprsStruct(ArithExprsStruct *arithExprsStruct);

LhsListStruct *createLhsListStruct(LhsStruct lhsStruct);
void addLhs(LhsListStruct *lhsListStruct, LhsStruct lhsStruct);
void freeLhsListStruct(LhsListStruct *lhsListStruct);

#endif // STRUCTS_H