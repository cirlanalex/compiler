#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

IdentifiersStruct *createIdentifiersStruct(char *name) {
    IdentifiersStruct *identifiersStruct = malloc(sizeof(IdentifiersStruct));
    identifiersStruct->names = malloc(sizeof(char *));
    identifiersStruct->names[0] = name;
    identifiersStruct->size = 1;
    return identifiersStruct;
}

void addIdentifier(IdentifiersStruct *identifiersStruct, char *name) {
    identifiersStruct->names = realloc(identifiersStruct->names, sizeof(char *) * (identifiersStruct->size + 1));
    identifiersStruct->names[identifiersStruct->size] = name;
    identifiersStruct->size++;
}

void freeIdentifiersStruct(IdentifiersStruct *identifiersStruct) {
    for (int i = 0; i < identifiersStruct->size; i++) {
        free(identifiersStruct->names[i]);
    }
    free(identifiersStruct->names);
    free(identifiersStruct);
}

ParametersStruct *createParametersStruct(IdentifiersStruct *identifiers, Type type, ReturnType returnType, int lowerBound, int upperBound) {
    ParametersStruct *parametersStruct = malloc(sizeof(ParametersStruct));
    parametersStruct->paramsNames = identifiers->names;
    parametersStruct->paramsTypes = malloc(sizeof(Type) * identifiers->size);
    parametersStruct->paramsReturnTypes = malloc(sizeof(ReturnType) * identifiers->size);
    parametersStruct->lowerBounds = malloc(sizeof(int) * identifiers->size);
    parametersStruct->upperBounds = malloc(sizeof(int) * identifiers->size);
    for (int i = 0; i < identifiers->size; i++) {
        parametersStruct->paramsTypes[i] = type;
        parametersStruct->paramsReturnTypes[i] = returnType;
        parametersStruct->lowerBounds[i] = lowerBound;
        parametersStruct->upperBounds[i] = upperBound;
    }
    parametersStruct->size = identifiers->size;
    free(identifiers);
    return parametersStruct;
}

void freeParametersStructWithoutNames(ParametersStruct *parametersStruct) {
    free(parametersStruct->paramsNames);
    free(parametersStruct->paramsTypes);
    free(parametersStruct->paramsReturnTypes);
    free(parametersStruct->lowerBounds);
    free(parametersStruct->upperBounds);
    free(parametersStruct);
}

void freeParametersStruct(ParametersStruct *parametersStruct) {
    for (int i = 0; i < parametersStruct->size; i++) {
        free(parametersStruct->paramsNames[i]);
    }
    freeParametersStructWithoutNames(parametersStruct);
}

void freeParametersStructWithoutTypes(ParametersStruct *parametersStruct) {
    for (int i = 0; i < parametersStruct->size; i++) {
        free(parametersStruct->paramsNames[i]);
    }
    free(parametersStruct->paramsNames);
    free(parametersStruct);
}

void addParameterList(ParametersStruct *parametersStruct, ParametersStruct *parametersStruct2) {
    parametersStruct->paramsNames = realloc(parametersStruct->paramsNames, sizeof(char *) * (parametersStruct->size + parametersStruct2->size));
    parametersStruct->paramsTypes = realloc(parametersStruct->paramsTypes, sizeof(Type) * (parametersStruct->size + parametersStruct2->size));
    parametersStruct->paramsReturnTypes = realloc(parametersStruct->paramsReturnTypes, sizeof(ReturnType) * (parametersStruct->size + parametersStruct2->size));
    parametersStruct->lowerBounds = realloc(parametersStruct->lowerBounds, sizeof(int) * (parametersStruct->size + parametersStruct2->size));
    parametersStruct->upperBounds = realloc(parametersStruct->upperBounds, sizeof(int) * (parametersStruct->size + parametersStruct2->size));
    for (int i = 0; i < parametersStruct2->size; i++) {
        parametersStruct->paramsNames[parametersStruct->size + i] = parametersStruct2->paramsNames[i];
        parametersStruct->paramsTypes[parametersStruct->size + i] = parametersStruct2->paramsTypes[i];
        parametersStruct->paramsReturnTypes[parametersStruct->size + i] = parametersStruct2->paramsReturnTypes[i];
        parametersStruct->lowerBounds[parametersStruct->size + i] = parametersStruct2->lowerBounds[i];
        parametersStruct->upperBounds[parametersStruct->size + i] = parametersStruct2->upperBounds[i];
    }
    parametersStruct->size += parametersStruct2->size;
    freeParametersStructWithoutNames(parametersStruct2);
}

ArithExprsStruct *createArithExprsStruct(Type type, ReturnType returnType, char *temp, char *lowerBound, char *upperBound, int arrayElement) {
    ArithExprsStruct *arithExprsStruct = malloc(sizeof(ArithExprsStruct));
    arithExprsStruct->types = malloc(sizeof(Type));
    arithExprsStruct->returnTypes = malloc(sizeof(ReturnType));
    arithExprsStruct->temps = malloc(sizeof(char *));
    arithExprsStruct->lowerBounds = malloc(sizeof(char *));
    arithExprsStruct->upperBounds = malloc(sizeof(char *));
    arithExprsStruct->arrayElements = malloc(sizeof(int));
    arithExprsStruct->types[0] = type;
    arithExprsStruct->returnTypes[0] = returnType;
    arithExprsStruct->temps[0] = temp;
    arithExprsStruct->lowerBounds[0] = lowerBound;
    arithExprsStruct->upperBounds[0] = upperBound;
    arithExprsStruct->arrayElements[0] = arrayElement;
    arithExprsStruct->size = 1;
    return arithExprsStruct;
}

void addArithExpr(ArithExprsStruct *arithExprsStruct, Type type, ReturnType returnType, char *temp, char *lowerBound, char *upperBound, int arrayElement) {
    arithExprsStruct->types = realloc(arithExprsStruct->types, sizeof(Type) * (arithExprsStruct->size + 1));
    arithExprsStruct->returnTypes = realloc(arithExprsStruct->returnTypes, sizeof(ReturnType) * (arithExprsStruct->size + 1));
    arithExprsStruct->temps = realloc(arithExprsStruct->temps, sizeof(char *) * (arithExprsStruct->size + 1));
    arithExprsStruct->lowerBounds = realloc(arithExprsStruct->lowerBounds, sizeof(char *) * (arithExprsStruct->size + 1));
    arithExprsStruct->upperBounds = realloc(arithExprsStruct->upperBounds, sizeof(char *) * (arithExprsStruct->size + 1));
    arithExprsStruct->arrayElements = realloc(arithExprsStruct->arrayElements, sizeof(int) * (arithExprsStruct->size + 1));
    arithExprsStruct->types[arithExprsStruct->size] = type;
    arithExprsStruct->returnTypes[arithExprsStruct->size] = returnType;
    arithExprsStruct->temps[arithExprsStruct->size] = temp;
    arithExprsStruct->lowerBounds[arithExprsStruct->size] = lowerBound;
    arithExprsStruct->upperBounds[arithExprsStruct->size] = upperBound;
    arithExprsStruct->arrayElements[arithExprsStruct->size] = arrayElement;
    arithExprsStruct->size++;
}

void freeArithExprsStruct(ArithExprsStruct *arithExprsStruct) {
    free(arithExprsStruct->types);
    free(arithExprsStruct->returnTypes);
    free(arithExprsStruct->arrayElements);
    for (int i = 0; i < arithExprsStruct->size; i++) {
        free(arithExprsStruct->lowerBounds[i]);
        free(arithExprsStruct->upperBounds[i]);
        free(arithExprsStruct->temps[i]);
    }
    free(arithExprsStruct->lowerBounds);
    free(arithExprsStruct->upperBounds);
    free(arithExprsStruct->temps);
    free(arithExprsStruct);
}

LhsListStruct *createLhsListStruct(LhsStruct lhsStruct) {
    LhsListStruct *lhsListStruct = malloc(sizeof(LhsListStruct));
    lhsListStruct->lhsStructs = malloc(sizeof(LhsStruct));
    lhsListStruct->lhsStructs[0] = lhsStruct;
    lhsListStruct->size = 1;
    return lhsListStruct;
}

void addLhs(LhsListStruct *lhsListStruct, LhsStruct lhsStruct) {
    lhsListStruct->lhsStructs = realloc(lhsListStruct->lhsStructs, sizeof(LhsStruct) * (lhsListStruct->size + 1));
    lhsListStruct->lhsStructs[lhsListStruct->size] = lhsStruct;
    lhsListStruct->size++;
}

void freeLhsListStruct(LhsListStruct *lhsListStruct) {
    for (int i = 0; i < lhsListStruct->size; i++) {
        free(lhsListStruct->lhsStructs[i].identifier);
        free(lhsListStruct->lhsStructs[i].temp);
    }
    free(lhsListStruct->lhsStructs);
    free(lhsListStruct);
}