#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

typedef struct {
    Type type;
    Type originalType;
    ReturnType returntype;
    int scope;
    int set;
    int paramsSize;
    char **paramsNames;
    Type *paramsTypes;
    ReturnType *paramsReturnTypes;
    int *paramsLowerBounds;
    int *paramsUpperBounds;
    int ival;
    double dval;
    int lowerBound;
    int upperBound;
} StackEntry;

typedef struct SymbolEntry SymbolEntry;

struct SymbolEntry {
    char *name;
    StackEntry *stack;
    int stackSize;
    struct SymbolEntry *next;
};

static SymbolEntry **symbolTable = NULL;
static int symbolTableCapacity = 0;
static int currentScope = 0;
static int initialized = 0;

void initSymbolTable() {
    symbolTableCapacity = 100;
    symbolTable = malloc(sizeof(SymbolEntry *) * symbolTableCapacity);
    for (int i = 0; i < symbolTableCapacity; i++) {
        symbolTable[i] = NULL;
    }
    initialized = 1;
}

static unsigned int hashFunction(const char *s) {
    unsigned int hash = 0;
    while (*s) {
        hash = 101 * hash + *s++;
    }
    return hash;
}

int insertSymbolPrivate(const char *name, Type type, Type originalType, ReturnType returntype, int scope, int paramsSize, char **paramsNames, Type *paramsTypes, ReturnType *paramsReturnTypes, int* paramsLowerBounds, int *paramsUpperBounds, int ival, double dval, int lowerBound, int upperBound) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            if (entry->stack[entry->stackSize - 1].scope != scope) {
                entry->stack = realloc(entry->stack, sizeof(StackEntry) * (entry->stackSize + 1));
                entry->stack[entry->stackSize].scope = scope;
                entry->stack[entry->stackSize].type = type;
                entry->stack[entry->stackSize].originalType = originalType;
                entry->stack[entry->stackSize].returntype = returntype;
                entry->stack[entry->stackSize].set = 0;
                entry->stack[entry->stackSize].paramsSize = paramsSize;
                entry->stack[entry->stackSize].paramsNames = paramsNames;
                entry->stack[entry->stackSize].paramsTypes = paramsTypes;
                entry->stack[entry->stackSize].paramsReturnTypes = paramsReturnTypes;
                entry->stack[entry->stackSize].paramsLowerBounds = paramsLowerBounds;
                entry->stack[entry->stackSize].paramsUpperBounds = paramsUpperBounds;
                entry->stack[entry->stackSize].ival = ival;
                entry->stack[entry->stackSize].dval = dval;
                entry->stack[entry->stackSize].lowerBound = lowerBound;
                entry->stack[entry->stackSize].upperBound = upperBound;
                entry->stackSize++;
            } else {
                return -1;
            }
            return index;
        }
        entry = entry->next;
    }

    entry = malloc(sizeof(SymbolEntry));
    entry->name = malloc(strlen(name) + 1);
    strcpy(entry->name, name);
    entry->stack = malloc(sizeof(StackEntry));
    entry->stack[0].scope = scope;
    entry->stack[0].type = type;
    entry->stack[0].originalType = originalType;
    entry->stack[0].returntype = returntype;
    entry->stack[0].set = 0;
    entry->stack[0].paramsSize = paramsSize;
    entry->stack[0].paramsNames = paramsNames;
    entry->stack[0].paramsTypes = paramsTypes;
    entry->stack[0].paramsReturnTypes = paramsReturnTypes;
    entry->stack[0].paramsLowerBounds = paramsLowerBounds;
    entry->stack[0].paramsUpperBounds = paramsUpperBounds;
    entry->stack[0].ival = ival;
    entry->stack[0].dval = dval;
    entry->stack[0].lowerBound = lowerBound;
    entry->stack[0].upperBound = upperBound;
    entry->stackSize = 1;
    entry->next = symbolTable[index];
    symbolTable[index] = entry;

    return index;
}

void setSet(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            entry->stack[entry->stackSize - 1].set = 1;
            return;
        }
        entry = entry->next;
    }
}

int insertSymbol(char *name, Type type, Type originalType, ReturnType returntype, int ival, double dval, int lowerBound, int upperBound) {
    return insertSymbolPrivate(name, type, originalType, returntype, currentScope, 0, NULL, NULL, NULL, NULL, NULL, ival, dval, lowerBound, upperBound);
}

char **copyNames(int paramsSize, char **paramsNames) {
    char **names = malloc(sizeof(char *) * paramsSize);
    for (int i = 0; i < paramsSize; i++) {
        names[i] = malloc(strlen(paramsNames[i]) + 1);
        strcpy(names[i], paramsNames[i]);
    }
    return names;
}

int insertSymbolFunction(char *name, Type type, ReturnType returntype, int paramsSize, char **paramsNames, Type *paramsTypes, ReturnType *paramsReturnTypes, int *paramsLowerBounds, int *paramsUpperBounds) {
    char **names = copyNames(paramsSize, paramsNames);
    return insertSymbolPrivate(name, type, type, returntype, currentScope - 1, paramsSize, names, paramsTypes, paramsReturnTypes, paramsLowerBounds, paramsUpperBounds, 0, 0, 0, 0);
}

int lookupSymbol(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return index;
        }
        entry = entry->next;
    }

    return -1;
}

Type getType(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].type;
        }
        entry = entry->next;
    }

    return -1;
}

Type getOriginalType(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];
    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].originalType;
        }
        entry = entry->next;
    }

    return -1;
}

Type getTypeAtIndex(char *name, int index) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].paramsTypes[index];
        }
        entry = entry->next;
    }

    return -1;
}

ReturnType getReturnType(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].returntype;
        }
        entry = entry->next;
    }

    return -1;
}

ReturnType getReturnTypeAtIndex(char *name, int index) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].paramsReturnTypes[index];
        }
        entry = entry->next;
    }

    return -1;
}

int getScope(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].scope;
        }
        entry = entry->next;
    }

    return -1;
}

int getCurrentScope() {
    return currentScope;
}

int isSet(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].set;
        }
        entry = entry->next;
    }

    return -1;
}

int getSizeParameters(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].paramsSize;
        }
        entry = entry->next;
    }

    return -1;
}

Type *getParametersTypes(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].paramsTypes;
        }
        entry = entry->next;
    }

    return NULL;
}

ReturnType *getParametersReturnTypes(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].paramsReturnTypes;
        }
        entry = entry->next;
    }

    return NULL;
}

int getIval(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].ival;
        }
        entry = entry->next;
    }

    return -1;
}

double getDval(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int index = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].dval;
        }
        entry = entry->next;
    }

    return -1;
}

void enterScope() {
    currentScope++;
}

void exitScope() {
    if (currentScope == 0) {
        return;
    }

    if (!initialized) {
        initSymbolTable();
    }

    for (int i = 0; i < symbolTableCapacity; i++) {
        SymbolEntry *entry = symbolTable[i];
        if (entry && entry->stackSize > 0 && entry->stack[entry->stackSize - 1].scope == currentScope) {
            entry->stackSize--;
            if (entry->stackSize == 0) {
                SymbolEntry *next = entry->next;
                free(entry->stack->paramsTypes);
                free(entry->stack->paramsReturnTypes);
                free(entry->stack);
                free(entry->name);
                free(entry);
                if (next) {
                    symbolTable[i] = next;
                } else {
                    symbolTable[i] = NULL;
                }
            }
        }
    }
    currentScope--;
}

int getLowerBound(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].lowerBound;
        }
        entry = entry->next;
    }

    return -1;
}

int getUpperBound(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry->stack[entry->stackSize - 1].upperBound;
        }
        entry = entry->next;
    }

    return -1;
}

char **getParametersNames(char *name) {
    if (!initialized) {
        initSymbolTable();
    }

    unsigned int hash = hashFunction(name);
    int i = hash % symbolTableCapacity;
    SymbolEntry *entry = symbolTable[i];

    while (entry) {
        if (strcmp(entry->name, name) == 0 && entry->stackSize > 0) {
            return entry->stack[entry->stackSize - 1].paramsNames;
        }
        entry = entry->next;
    }

    return NULL;
}

void printSymbolTable() {
    if (!initialized) {
        initSymbolTable();
    }

    printf("Symbol table:\n");
    for (int i = 0; i < symbolTableCapacity; i++) {
        SymbolEntry *entry = symbolTable[i];
        while (entry) {
            printf("Name: %s\n", entry->name);
            for (int j = 0; j < entry->stackSize; j++) {
                printf("  Scope: %d\n", entry->stack[j].scope);
                printf("  Type: %d\n", entry->stack[j].type);
                printf("  OriginalType: %d\n", entry->stack[j].originalType);
                printf("  ReturnType: %d\n", entry->stack[j].returntype);
                printf("  Set: %d\n", entry->stack[j].set);
                printf("  ParamsSize: %d\n", entry->stack[j].paramsSize);
                printf("  ParamsNames: ");
                for (int k = 0; k < entry->stack[j].paramsSize; k++) {
                    printf("%s ", entry->stack[j].paramsNames[k]);
                }
                printf("\n");
                printf("  ParamsType: ");
                for (int k = 0; k < entry->stack[j].paramsSize; k++) {
                    printf("%d ", entry->stack[j].paramsTypes[k]);
                }
                printf("\n");
                printf("  ParamsReturnType: ");
                for (int k = 0; k < entry->stack[j].paramsSize; k++) {
                    printf("%d ", entry->stack[j].paramsReturnTypes[k]);
                }
                printf("\n");
            }
            printf("\n");
            entry = entry->next;
        }
    }
}

void freeSymbolTable() {
    if (!initialized) {
        return;
    }

    for (int i = 0; i < symbolTableCapacity; i++) {
        SymbolEntry *entry = symbolTable[i];
        while (entry) {
            SymbolEntry *next = entry->next;
            for (int j = 0; j < entry->stack->paramsSize; j++) {
                free(entry->stack->paramsNames[j]);
            }
            free(entry->stack->paramsNames);
            free(entry->stack->paramsTypes);
            free(entry->stack->paramsReturnTypes);
            free(entry->stack->paramsLowerBounds);
            free(entry->stack->paramsUpperBounds);
            free(entry->stack);
            free(entry->name);
            free(entry);
            entry = next;
        }
    }
    free(symbolTable);
}