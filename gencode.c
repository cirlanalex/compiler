#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "symtable.h"

extern FILE *output;
int quadCount = 0;
int labelCount = 0;
int indentation = 0;

void printIndentation() {
    for (int i = 0; i < indentation; i++) {
        fprintf(output, "\t");
    }
}

void generateHeader() {
    fprintf(output, "#include <stdio.h>\n");
    fprintf(output, "#include <stdlib.h>\n");
    fprintf(output, "#include <string.h>\n");
    fprintf(output, "\n");
}

void generateConstDecl(char *name) {
    ReturnType returnType = getReturnType(name);
    if (returnType == RETURN_TYPE_INTEGER) {
        fprintf(output, "const int %s = %d;\n", name, getIval(name));
    } else if (returnType == RETURN_TYPE_REAL) {
        fprintf(output, "const double %s = %lf;\n", name, getDval(name));
    }
}

void generateVarDecl(char *name) {
    Type type = getType(name);
    ReturnType returnType = getReturnType(name);
    printIndentation();
    if (type == TYPE_VAR_ARRAY) {
        if (returnType == RETURN_TYPE_INTEGER) {
            fprintf(output, "int %s[%d];\n", name, getUpperBound(name) - getLowerBound(name) + 1);
        } else if (returnType == RETURN_TYPE_REAL) {
            fprintf(output, "double %s[%d];\n", name, getUpperBound(name) - getLowerBound(name) + 1);
        }
    } else {
        if (returnType == RETURN_TYPE_INTEGER) {
            fprintf(output, "int %s;\n", name);
        } else if (returnType == RETURN_TYPE_REAL) {
            fprintf(output, "double %s;\n", name);
        }
    }
}

void generateMain() {
    fprintf(output, "int main() {\n");
    quadCount = 0;
    indentation = 1;
}

void generateFunction(char *name) {
    Type type = getType(name);
    ReturnType returnType = getReturnType(name);
    int paramsSize = getSizeParameters(name);

    if (type == TYPE_FUNCTION) {
        if (returnType == RETURN_TYPE_INTEGER) {
            fprintf(output, "int %s(", name);
        } else if (returnType == RETURN_TYPE_REAL) {
            fprintf(output, "double %s(", name);
        }
    } else if (type == TYPE_PROCEDURE) {
        fprintf(output, "void %s(", name);
    }

    if (paramsSize > 0) {
        Type *paramsTypes = getParametersTypes(name);
        ReturnType *paramsReturnTypes = getParametersReturnTypes(name);
        char **paramsNames = getParametersNames(name);
        
        for (int i = 0; i < paramsSize; i++) {
            char *paramName = paramsNames[i];
            Type paramType = paramsTypes[i];
            ReturnType paramReturnType = paramsReturnTypes[i];

            if (paramType == TYPE_VAR) {
                if (paramReturnType == RETURN_TYPE_INTEGER) {
                    fprintf(output, "int *%s", paramName);
                } else if (paramReturnType == RETURN_TYPE_REAL) {
                    fprintf(output, "double *%s", paramName);
                }
            } else if (paramType == TYPE_VAR_ARRAY) {
                if (paramReturnType == RETURN_TYPE_INTEGER) {
                    fprintf(output, "int *%s", paramName);
                } else if (paramReturnType == RETURN_TYPE_REAL) {
                    fprintf(output, "double *%s", paramName);
                }
            } else if (paramType == TYPE_ARRAY) {
                if (paramReturnType == RETURN_TYPE_INTEGER) {
                    fprintf(output, "int *%s", paramName);
                } else if (paramReturnType == RETURN_TYPE_REAL) {
                    fprintf(output, "double *%s", paramName);
                }
            } else if (paramType == TYPE_VALUE) {
                if (paramReturnType == RETURN_TYPE_INTEGER) {
                    fprintf(output, "int %s", paramName);
                } else if (paramReturnType == RETURN_TYPE_REAL) {
                    fprintf(output, "double %s", paramName);
                }
            }

            if (i < paramsSize - 1) {
                fprintf(output, ", ");
            }
        }
    }

    fprintf(output, ") {\n");
    quadCount = 0;
    indentation = 1;
    if (type == TYPE_FUNCTION) {
        printIndentation();
        fprintf(output, "%s _return;\n", returnType == RETURN_TYPE_INTEGER ? "int" : "double");
    }
}

void generateFunctionEnd(char *lastFunctionName) {
    if (lastFunctionName != NULL) {
        printIndentation();
        fprintf(output, "return _return;\n");
    }
    fprintf(output, "}\n");
    indentation = 0;
}

void generateNewLine() {
    fprintf(output, "\n");
}

char *generateInteger(int ival) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %d;\n", temp, ival);
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}

char *generateReal(double dval) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "double _t%d = %lf;\n", temp, dval);
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}

char *generateOperation(char *lhs, char *rhs, char operator, ReturnType returnType) {
    int temp = quadCount++;
    printIndentation();
    if (returnType == RETURN_TYPE_INTEGER) {
        fprintf(output, "int _t%d = ", temp);
    } else if (returnType == RETURN_TYPE_REAL) {
        fprintf(output, "double _t%d = ", temp);
        if (operator == '/') {
            fprintf(output, "(double)");
        }
    }
    if (lhs[0] != '_' && getOriginalType(lhs) == TYPE_VAR && getScope(lhs) != 0) {
        fprintf(output, "*");
    }
    fprintf(output, "%s %c ", lhs, operator);
    if (rhs[0] != '_' && getOriginalType(rhs) == TYPE_VAR && getScope(rhs) != 0) {
        fprintf(output, "*");
    }
    fprintf(output, "%s;\n", rhs);
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}

char *generateFunctionCall(char *identifier, ArithExprsStruct *arithExprs) {
    ReturnType returnType = getReturnType(identifier);

    Type *types = getParametersTypes(identifier);

    for (int i = 0; i < arithExprs->size; i++) {
        char *tempStr = arithExprs->temps[i];
        Type type = types[i];
        Type typeTemp = getType(tempStr);
        if ((type == TYPE_ARRAY && tempStr[0] == '_')) {
            ReturnType returnTypeTemp = arithExprs->returnTypes[i];
            char *lowerBound = arithExprs->lowerBounds[i];
            char *upperBound = arithExprs->upperBounds[i];
            int sizeWithoutOne = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = %s - %s;\n", sizeWithoutOne, upperBound, lowerBound);
            int size = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = _t%d + 1;\n", size, sizeWithoutOne);
            int sizeInBytes = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", sizeInBytes, size, returnTypeTemp == RETURN_TYPE_INTEGER ? "int" : "double");
            int tempIndex = quadCount++;
            printIndentation();
            if (returnTypeTemp == RETURN_TYPE_INTEGER) {
                fprintf(output, "int *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            } else if (returnTypeTemp == RETURN_TYPE_REAL) {
                fprintf(output, "double *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            }
            printIndentation();
            fprintf(output, "memcpy(_t%d, %s, _t%d);\n", tempIndex, tempStr, sizeInBytes);
            free(tempStr);
            tempStr = malloc(sizeof(char) * (3 + tempIndex / 10 + 1));
            sprintf(tempStr, "_t%d", tempIndex);
            arithExprs->temps[i] = tempStr;
        }
        if ((type == TYPE_ARRAY) && (typeTemp == TYPE_ARRAY || typeTemp == TYPE_VAR_ARRAY)) {
            ReturnType returnTypeTemp = getReturnType(tempStr);
            int lowerBound = getLowerBound(tempStr);
            int upperBound = getUpperBound(tempStr);
            int size = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = %d;\n", size, upperBound - lowerBound + 1);
            int sizeInBytes = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", sizeInBytes, size, returnTypeTemp == RETURN_TYPE_INTEGER ? "int" : "double");
            int tempIndex = quadCount++;
            printIndentation();
            if (returnTypeTemp == RETURN_TYPE_INTEGER) {
                fprintf(output, "int *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            } else if (returnTypeTemp == RETURN_TYPE_REAL) {
                fprintf(output, "double *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            }
            printIndentation();
            fprintf(output, "memcpy(_t%d, %s, _t%d);\n", tempIndex, tempStr, sizeInBytes);
            free(tempStr);
            tempStr = malloc(sizeof(char) * (3 + tempIndex / 10 + 1));
            sprintf(tempStr, "_t%d", tempIndex);
            arithExprs->temps[i] = tempStr;
        }
    }

    int temp = quadCount++;
    printIndentation();
    if (returnType == RETURN_TYPE_INTEGER) {
        fprintf(output, "int _t%d = %s(", temp, identifier);
    } else if (returnType == RETURN_TYPE_REAL) {
        fprintf(output, "double _t%d = %s(", temp, identifier);
    }

    for (int i = 0; i < arithExprs->size; i++) {
        char *tempStr = arithExprs->temps[i];
        Type type = types[i];
        if ((type == TYPE_VAR) && (getOriginalType(tempStr) != TYPE_VAR && arithExprs->arrayElements[i] == 0)) {
            fprintf(output, "&%s", tempStr);
        } else if (type == TYPE_VAR && arithExprs->arrayElements[i] == 1) {
            int idx = strtoul(tempStr + 2, NULL, 10) - 1;
            ReturnType returnType = arithExprs->returnTypes[i];
            if (returnType == RETURN_TYPE_INTEGER) {
                fprintf(output, "(int *)_t%d", idx);
            } else if (returnType == RETURN_TYPE_REAL) {
                fprintf(output, "(double *)_t%d", idx);
            }
        } else {
            if (getOriginalType(tempStr) == TYPE_VAR && getScope(tempStr) != 0) {
                fprintf(output, "*%s", tempStr);
            } else {
                fprintf(output, "%s", tempStr);
            }
        }
        if (i < arithExprs->size - 1) {
            fprintf(output, ", ");
        }
    }

    fprintf(output, ");\n");

    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}

char *generateArrayElement(char *identifier, char *value) {
    ReturnType returnType = getReturnType(identifier);
    int lowerBound = getLowerBound(identifier);
    int tempIndex = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %s - %d;\n", tempIndex, value, lowerBound);
    int tempFromBytes = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", tempFromBytes, tempIndex, returnType == RETURN_TYPE_INTEGER ? "int" : "double");
    int tempArray = quadCount++;
    printIndentation();
    fprintf(output, "char *_t%d = (char *)%s;\n", tempArray, identifier);
    int tempPointer = quadCount++;
    printIndentation();
    fprintf(output, "char *_t%d = _t%d + _t%d;\n", tempPointer, tempArray, tempFromBytes);
    int temp = quadCount++;
    printIndentation();
    if (returnType == RETURN_TYPE_INTEGER) {
        fprintf(output, "int _t%d = *((int *)_t%d);\n", temp, tempPointer);
    } else if (returnType == RETURN_TYPE_REAL) {
        fprintf(output, "double _t%d = *((double *)_t%d);\n", temp, tempPointer);
    }
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}

void generateAssignment(LhsStruct lhs, char *value) {
    Type type = getType(lhs.identifier);
    printIndentation();
    if (type == TYPE_FUNCTION) {
        fprintf(output, "_return = %s;\n", value);
        return;
    }
    if (type == TYPE_VAR_ARRAY) {
        int lowerBound = getLowerBound(lhs.identifier);
        int tempIndex = quadCount++;
        fprintf(output, "int _t%d = %s - %d;\n", tempIndex, lhs.temp, lowerBound);
        int tempFromBytes = quadCount++;
        printIndentation();
        fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", tempFromBytes, tempIndex, getReturnType(lhs.identifier) == RETURN_TYPE_INTEGER ? "int" : "double");
        int tempArray = quadCount++;
        printIndentation();
        fprintf(output, "char *_t%d = (char *)%s;\n", tempArray, lhs.identifier);
        int tempPointer = quadCount++;
        printIndentation();
        fprintf(output, "char *_t%d = _t%d + _t%d;\n", tempPointer, tempArray, tempFromBytes);
        if (getReturnType(lhs.identifier) == RETURN_TYPE_INTEGER) {
            printIndentation();
            fprintf(output, "*((int *)_t%d) = %s;\n", tempPointer, value);
        } else if (getReturnType(lhs.identifier) == RETURN_TYPE_REAL) {
            printIndentation();
            fprintf(output, "*((double *)_t%d) = %s;\n", tempPointer, value);
        }
        return;
    }
    if (getOriginalType(lhs.identifier) == TYPE_VAR && getScope(lhs.identifier) != 0) {
        fprintf(output, "*%s = %s;\n", lhs.identifier, value);
        return;
    }
    fprintf(output, "%s = %s;\n", lhs.identifier, value);
}

char *generateNegation(char *value, ReturnType returnType) {
    int temp = quadCount++;
    printIndentation();
    if (returnType == RETURN_TYPE_INTEGER) {
        fprintf(output, "int _t%d = -%s;\n", temp, value);
    } else if (returnType == RETURN_TYPE_REAL) {
        fprintf(output, "double _t%d = -%s;\n", temp, value);
    }
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}

char *generateCondition(char *lhs, char *operator, char *rhs) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %s %s %s;\n", temp, lhs, operator, rhs);
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}

char *generateNot(char *value) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = !%s;\n", temp, value);
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    free(value);
    return tempStr;
}

char *generateAnd(char *lhs, char *rhs) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %s && %s;\n", temp, lhs, rhs);
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    free(lhs);
    free(rhs);
    return tempStr;
}

char *generateOr(char *lhs, char *rhs) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %s || %s;\n", temp, lhs, rhs);
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    free(lhs);
    free(rhs);
    return tempStr;
}

int generateIfLabel(char *value) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %s != 0;\n", temp, value);
    int tempLabel = labelCount++;
    printIndentation();
    fprintf(output, "if (!_t%d) goto _lb%d;\n", temp, tempLabel);
    free(value);
    labelCount++;
    return tempLabel;
}

void generateLabel(int label) {
    printIndentation();
    fprintf(output, "_lb%d: ;\n", label);
    // indentation++;
}

int generateElseLabel(int label) {
    printIndentation();
    fprintf(output, "goto _lb%d;\n", label + 1);
    generateLabel(label);
    return label + 1;
}

int generateWhileLabel() {
    int tempLabel = labelCount++;
    generateLabel(tempLabel);
    labelCount++;
    return tempLabel;
}

void generateWhileLabelCheck(char *value, int label) {
    int temp = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %s != 0;\n", temp, value);
    printIndentation();
    fprintf(output, "if (!_t%d) goto _lb%d;\n", temp, label);
    free(value);
}

void generateWhileLabelFinal(int label) {
    printIndentation();
    fprintf(output, "goto _lb%d;\n", label);
    generateLabel(label + 1);
}

void generateWriteLn(ArithExprsStruct *arithExprs) {
    printIndentation();
    fprintf(output, "printf(\"");
    for (int i = 0; i < arithExprs->size; i++) {
        ReturnType returnType = arithExprs->returnTypes[i];
        if (returnType == RETURN_TYPE_INTEGER) {
            fprintf(output, "%%d");
        } else if (returnType == RETURN_TYPE_REAL) {
            fprintf(output, "%%lf");
        }
        if (i < arithExprs->size - 1) {
            fprintf(output, " ");
        }
    }
    fprintf(output, "\\n\"");

    for (int i = 0; i < arithExprs->size; i++) {
        char *tempStr = arithExprs->temps[i];
        Type originalType = getOriginalType(tempStr);
        if ((originalType == TYPE_VAR)) {
            fprintf(output, ", *%s", tempStr);
        } else {
            fprintf(output, ", %s", tempStr);
        }
    }

    fprintf(output, ");\n");
}

void generateReadLn(LhsListStruct *lhsListStruct) {
    for (int i = 0; i < lhsListStruct->size; i++) {
        Type type = getType(lhsListStruct->lhsStructs[i].identifier);
        if (type == TYPE_VAR_ARRAY || type == TYPE_ARRAY) {
            int lowerBound = getLowerBound(lhsListStruct->lhsStructs[i].identifier);
            int temp = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = %s - %d;\n", temp, lhsListStruct->lhsStructs[i].temp, lowerBound);
            int tempFromBytes = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", tempFromBytes, temp, getReturnType(lhsListStruct->lhsStructs[i].identifier) == RETURN_TYPE_INTEGER ? "int" : "double");
            int tempArray = quadCount++;
            printIndentation();
            fprintf(output, "char *_t%d = (char *)%s;\n", tempArray, lhsListStruct->lhsStructs[i].identifier);
            int tempPointer = quadCount++;
            printIndentation();
            fprintf(output, "char *_t%d = _t%d + _t%d;\n", tempPointer, tempArray, tempFromBytes);
            free(lhsListStruct->lhsStructs[i].temp);
            lhsListStruct->lhsStructs[i].temp = malloc(sizeof(char) * (3 + tempPointer / 10 + 1));
            sprintf(lhsListStruct->lhsStructs[i].temp, "_t%d", tempPointer);
        }
    }
    printIndentation();
    fprintf(output, "scanf(\"");
    for (int i = 0; i < lhsListStruct->size; i++) {
        ReturnType returnType = getReturnType(lhsListStruct->lhsStructs[i].identifier);
        if (returnType == RETURN_TYPE_INTEGER) {
            fprintf(output, "%%d");
        } else if (returnType == RETURN_TYPE_REAL) {
            fprintf(output, "%%lf");
        }
        if (i < lhsListStruct->size - 1) {
            fprintf(output, " ");
        }
    }

    fprintf(output, "\"");

    for (int i = 0; i < lhsListStruct->size; i++) {
        char *identifier = lhsListStruct->lhsStructs[i].identifier;
        Type type = getType(identifier);
        if (type == TYPE_VAR_ARRAY || type == TYPE_ARRAY) {
            ReturnType returnType = getReturnType(identifier);
            if (returnType == RETURN_TYPE_INTEGER) {
                fprintf(output, ", (int *)%s", lhsListStruct->lhsStructs[i].temp);
            } else if (returnType == RETURN_TYPE_REAL) {
                fprintf(output, ", (double *)%s", lhsListStruct->lhsStructs[i].temp);
            }
        } else {
            if (getOriginalType(identifier) == TYPE_VAR && getScope(identifier) != 0) {
                fprintf(output, ", %s", identifier);
            } else {
                fprintf(output, ", &%s", identifier);
            }
        }
    }

    fprintf(output, ");\n");
}

void generateProcedureCall(char *identifier) {
    printIndentation();
    fprintf(output, "%s();\n", identifier);
}

void generateProcedureCallWithParameters(char *identifier, ArithExprsStruct *arithExprs) {
    Type *types = getParametersTypes(identifier);

    for (int i = 0; i < arithExprs->size; i++) {
        char *tempStr = arithExprs->temps[i];
        Type type = types[i];
        Type typeTemp = getType(tempStr);
        if ((type == TYPE_ARRAY && tempStr[0] == '_')) {
            ReturnType returnTypeTemp = arithExprs->returnTypes[i];
            char *lowerBound = arithExprs->lowerBounds[i];
            char *upperBound = arithExprs->upperBounds[i];
            int sizeWithoutOne = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = %s - %s;\n", sizeWithoutOne, upperBound, lowerBound);
            int size = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = _t%d + 1;\n", size, sizeWithoutOne);
            int sizeInBytes = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", sizeInBytes, size, returnTypeTemp == RETURN_TYPE_INTEGER ? "int" : "double");
            int tempIndex = quadCount++;
            printIndentation();
            if (returnTypeTemp == RETURN_TYPE_INTEGER) {
                fprintf(output, "int *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            } else if (returnTypeTemp == RETURN_TYPE_REAL) {
                fprintf(output, "double *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            }
            printIndentation();
            fprintf(output, "memcpy(_t%d, %s, _t%d);\n", tempIndex, tempStr, sizeInBytes);
            free(tempStr);
            tempStr = malloc(sizeof(char) * (3 + tempIndex / 10 + 1));
            sprintf(tempStr, "_t%d", tempIndex);
            arithExprs->temps[i] = tempStr;
        }
        if ((type == TYPE_ARRAY) && (typeTemp == TYPE_ARRAY || typeTemp == TYPE_VAR_ARRAY)) {
            ReturnType returnTypeTemp = getReturnType(tempStr);
            int lowerBound = getLowerBound(tempStr);
            int upperBound = getUpperBound(tempStr);
            int size = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = %d;\n", size, upperBound - lowerBound + 1);
            int sizeInBytes = quadCount++;
            printIndentation();
            fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", sizeInBytes, size, returnTypeTemp == RETURN_TYPE_INTEGER ? "int" : "double");
            int tempIndex = quadCount++;
            printIndentation();
            if (returnTypeTemp == RETURN_TYPE_INTEGER) {
                fprintf(output, "int *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            } else if (returnTypeTemp == RETURN_TYPE_REAL) {
                fprintf(output, "double *_t%d = alloca(_t%d);\n", tempIndex, sizeInBytes);
            }
            printIndentation();
            fprintf(output, "memcpy(_t%d, %s, _t%d);\n", tempIndex, tempStr, sizeInBytes);
            free(tempStr);
            tempStr = malloc(sizeof(char) * (3 + tempIndex / 10 + 1));
            sprintf(tempStr, "_t%d", tempIndex);
            arithExprs->temps[i] = tempStr;
        }
    }

    printIndentation();
    fprintf(output, "%s(", identifier);
    for (int i = 0; i < arithExprs->size; i++) {
        char *tempStr = arithExprs->temps[i];
        Type type = types[i];
        Type originalType = getOriginalType(tempStr);
        if ((type == TYPE_VAR) && (getOriginalType(tempStr) != TYPE_VAR && arithExprs->arrayElements[i] == 0)) {
            fprintf(output, "&%s", tempStr);
        } else if (type == TYPE_VAR && arithExprs->arrayElements[i] == 1) {
            int idx = strtoul(tempStr + 2, NULL, 10) - 1;
            ReturnType returnType = arithExprs->returnTypes[i];
            if (returnType == RETURN_TYPE_INTEGER) {
                fprintf(output, "(int *)_t%d", idx);
            } else if (returnType == RETURN_TYPE_REAL) {
                fprintf(output, "(double *)_t%d", idx);
            }
        } else {
            if (type != TYPE_VAR && getOriginalType(tempStr) == TYPE_VAR && getScope(tempStr) != 0) {
                fprintf(output, "*%s", tempStr);
            } else {
                fprintf(output, "%s", tempStr);
            }
        }
        if (i < arithExprs->size - 1) {
            fprintf(output, ", ");
        }
    }
    fprintf(output, ");\n");
}

char *generateArrayTrim(char *identifier, char *lowerBound, char *upperBound) {
    ReturnType returnType = getReturnType(identifier);
    // int tempSize = quadCount++;
    // printIndentation();
    // fprintf(output, "int _t%d = %s - %s + 1;\n", tempSize, upperBound, lowerBound);
    // int tempSizeInBytes = quadCount++;
    // printIndentation();
    // fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", tempSizeInBytes, tempSize, returnType == RETURN_TYPE_INTEGER ? "int" : "double");
    // int temp = quadCount++;
    // printIndentation();
    // if (returnType == RETURN_TYPE_INTEGER) {
    //     fprintf(output, "int **_t%d = alloca(_t%d);\n", temp, tempSizeInBytes);
    // } else if (returnType == RETURN_TYPE_REAL) {
    //     fprintf(output, "double **_t%d = alloca(_t%d);\n", temp, tempSizeInBytes);
    // }
    // int start = quadCount++;
    // printIndentation();
    // fprintf(output, "int _t%d = %s - %d;\n", start, lowerBound, getLowerBound(identifier));
    // printIndentation();
    // fprintf(output, "for (int _i = 0; _i < _t%d; _i++) {\n", tempSize);
    // indentation++;
    // printIndentation();
    // fprintf(output, "_t%d[_i] = &%s[_t%d];\n", temp, identifier, start);
    // printIndentation();
    // fprintf(output, "_t%d = _t%d + 1;\n", start, start);
    // indentation--;
    // printIndentation();
    // fprintf(output, "}\n");
    // printIndentation();
    // int tempFinal = quadCount++;
    // if (returnType == RETURN_TYPE_INTEGER) {
    //     fprintf(output, "int *_t%d = *_t%d;\n", tempFinal, temp);
    // } else if (returnType == RETURN_TYPE_REAL) {
    //     fprintf(output, "double *_t%d = *_t%d;\n", tempFinal, temp);
    // }
    int start = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = %s - %d;\n", start, lowerBound, getLowerBound(identifier));
    int startBytes = quadCount++;
    printIndentation();
    fprintf(output, "int _t%d = _t%d * sizeof(%s);\n", startBytes, start, returnType == RETURN_TYPE_INTEGER ? "int" : "double");
    int tempArray = quadCount++;
    printIndentation();
    fprintf(output, "char *_t%d = (char *)%s;\n", tempArray, identifier);
    int tempPointer = quadCount++;
    printIndentation();
    fprintf(output, "char *_t%d = _t%d + _t%d;\n", tempPointer, tempArray, startBytes);
    int temp = quadCount++;
    printIndentation();
    if (returnType == RETURN_TYPE_INTEGER) {
        fprintf(output, "int *_t%d = (int *)_t%d;\n", temp, tempPointer);
    } else if (returnType == RETURN_TYPE_REAL) {
        fprintf(output, "double *_t%d = (double *)_t%d;\n", temp, tempPointer);
    }
    char *tempStr = malloc(sizeof(char) * (3 + temp / 10 + 1));
    sprintf(tempStr, "_t%d", temp);
    return tempStr;
}