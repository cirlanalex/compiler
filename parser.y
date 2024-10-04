%{
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "messages.h"
  #include "usage.h"
  #include "symtable.h"
  #include "gencode.h"

  void yyerror(char *msg);    /* forward declaration */
  /* exported by the lexer (made with flex) */
  extern int yylex(void);
  extern char *yytext;
  extern void showErrorLine();
  extern void initLexer(FILE *f);
  extern void finalizeLexer();
  extern int warnings;
  FILE *input;
  FILE *output;

%}

%token PROGRAM CONST VAR ARRAY RANGE OF 
       FUNCTION PROCEDURE BEGINTOK ENDTOK ASSIGN IF THEN ELSE WHILE DO
       RELOPLT RELOPLEQ RELOPEQ RELOPNEQ RELOPGEQ RELOPGT INTEGER REAL
       AND OR NOT DIV MOD SKIP READLN WRITELN

%token <ival> INTNUMBER
%token <dval> REALNUMBER
%token <sval> IDENTIFIER

%type <identifiers> IdentifierList
%type <lhsList> LhsList
%type <lhs> Lhs
%type <parameters> PossibleParameters
%type <parameters> Parameters
%type <parameters> ParameterList
%type <parameters> ParamList
%type <returntype> BasicType
%type <number> NumericValue
%type <typeSpec> TypeSpec
%type <arithStruct> ArithExpr
%type <arithExprs> ArithExprList
%type <sval> Relop
%type <sval> BoolAtom
%type <sval> Guard

%left '+' '-'
%left '*' '/' DIV MOD
%left OR
%left AND
%left NOT

%union {
  int ival;     /* used for passing int values from lexer to parser */
  double dval;  /* used for passing double values from lexer to parser */
  char *sval;   /* used for passing string values from lexer to parser */
  ReturnType returntype;
  TypeSpecStruct typeSpec;
  ArithStruct arithStruct;
  NumberStruct number;
  IdentifiersStruct *identifiers;
  ParametersStruct *parameters;
  ArithExprsStruct *arithExprs;
  LhsStruct lhs;
  LhsListStruct *lhsList;
  /* add here anything you may need */
  /*....*/  
}


%%

program            : PROGRAM IDENTIFIER ';' { generateHeader(); free($2); }
                     ConstDecl { generateNewLine(); }
                     VarDecl { generateNewLine(); }
                     FuncProcDecl { generateMain(); }
                     CompoundStatement { generateFunctionEnd(NULL); }
                     '.'
                   ;

ConstDecl          : ConstDecl CONST IDENTIFIER RELOPEQ NumericValue ';'  { constDeclarationCheck($3, $5.returnType, $5.ival, $5.dval); }
                   | %empty
                   ;

NumericValue       : INTNUMBER  { $$.returnType = RETURN_TYPE_INTEGER; $$.ival = $1; }
                   | REALNUMBER { $$.returnType = RETURN_TYPE_REAL; $$.dval = $1; }
                   ;

VarDecl            : VarDecl VAR IdentifierList ':' TypeSpec ';'  { addIdentifiersToSymTable($3, transformTypeToVar($5.type), $5.type, $5.returnType, $5.lowerBound, $5.upperBound); }
                   | %empty
                   ;

IdentifierList     : IDENTIFIER                     { $$ = createIdentifiersStruct($1); }
                   | IdentifierList ',' IDENTIFIER  { $$ = $1; addIdentifier($$, $3); }
                   ;

TypeSpec           : BasicType                                            { $$.type = TYPE_VALUE; $$.returnType = $1; $$.lowerBound = 0; $$.upperBound = 0; }
                   | ARRAY '[' INTNUMBER RANGE INTNUMBER ']' OF BasicType { arrayTypeCheck($3, $5); $$.type = TYPE_ARRAY; $$.returnType = $8; $$.lowerBound = $3; $$.upperBound = $5; }
                   ;

BasicType          : INTEGER  { $$ = RETURN_TYPE_INTEGER; }
                   | REAL     { $$ = RETURN_TYPE_REAL; }
                   ;

FuncProcDecl       : FuncProcDecl SubProgDecl ';' { generateNewLine(); }
                   | %empty
                   ;

SubProgDecl        : SubProgHeading VarDecl CompoundStatement { returnMissingCheck(); exitScope(); }
                   ;

SubProgHeading     : FUNCTION IDENTIFIER { enterScope(); } Parameters ':' BasicType ';' { functionDeclarationCheck($2, $4, $6); }
                   | PROCEDURE IDENTIFIER { enterScope(); } PossibleParameters ';'      { procedureDeclarationCheck($2, $4); }
                   ;

PossibleParameters : Parameters             { $$ = $1; }
                   | %empty                 { $$ = NULL; }
                   ;

Parameters         : '(' ParameterList ')'  { $$ = $2; }
                   ;

ParameterList      : ParamList                    { $$ = $1; }
                   | ParameterList ';' ParamList  { $$ = $1; addParameterList($$, $3); }
                   ;

ParamList          : VAR IdentifierList ':' TypeSpec  { $$ = createParametersStruct($2, transformTypeToVar($4.type), $4.returnType, $4.lowerBound, $4.upperBound); }
                   | IdentifierList ':' TypeSpec      { $$ = createParametersStruct($1, $3.type, $3.returnType, $3.lowerBound, $3.upperBound); }
                   ;                   

CompoundStatement  : BEGINTOK OptionalStatements ENDTOK
                   ;

OptionalStatements : StatementList
                   | %empty
                   ;

StatementList      : Statement
                   | StatementList ';' Statement
                   ;

Statement          : Lhs ASSIGN ArithExpr                   { statementCheck($1, $3); }
                   | SKIP
                   | ProcedureCall
                   | CompoundStatement
                   | IF Guard THEN { $<ival>$ = generateIfLabel($2); } Statement { $<ival>$ = generateElseLabel($<ival>4); } ELSE Statement { generateLabel($<ival>6); }
                   | WHILE { $<ival>$ = generateWhileLabel(); } Guard { generateWhileLabelCheck($3, $<ival>2 + 1); } DO Statement { generateWhileLabelFinal($<ival>2); }
                   ;

LhsList            : Lhs                          { $$ = createLhsListStruct($1); }
                   | LhsList ',' Lhs              { $$ = $1; addLhs($$, $3); }

Lhs                : IDENTIFIER                   { lhsCheck($1); $$.identifier = $1; $$.temp = NULL; }
                   | IDENTIFIER '[' ArithExpr ']' { lhsArrayCheck($1, $3); $$.identifier = $1; $$.temp = $3.temp; }
                   ;

ProcedureCall      : IDENTIFIER                       { procedureCallCheck($1); }
                   | IDENTIFIER '(' ArithExprList ')' { procedureCallWithParametersCheck($1, $3); }
                   | READLN '(' LhsList ')'           { readlnCheck($3); }
                   | WRITELN '(' ArithExprList ')'    { writelnCheck($3); }
                   ;

Guard              : BoolAtom               { $$ = $1; }
                   | NOT Guard              { $$ = generateNot($2); }
                   | Guard OR Guard         { $$ = generateOr($1, $3); }
                   | Guard AND Guard        { $$ = generateAnd($1, $3); }
                   | '(' Guard ')'          { $$ = $2; }
                   ;

BoolAtom           : ArithExpr Relop ArithExpr                    { $$ = boolCheck($1, $2, $3); }
                   ;

Relop              : RELOPLT  { char *operator = malloc(sizeof(char) * 2); strcpy(operator, "<"); $$ = operator; }
                   | RELOPLEQ { char *operator = malloc(sizeof(char) * 3); strcpy(operator, "<="); $$ = operator; }
                   | RELOPEQ  { char *operator = malloc(sizeof(char) * 3); strcpy(operator, "=="); $$ = operator; }
                   | RELOPNEQ { char *operator = malloc(sizeof(char) * 3); strcpy(operator, "!="); $$ = operator; }
                   | RELOPGEQ { char *operator = malloc(sizeof(char) * 3); strcpy(operator, ">="); $$ = operator; }
                   | RELOPGT  { char *operator = malloc(sizeof(char) * 2); strcpy(operator, ">"); $$ = operator; }
                   ;

ArithExprList      : ArithExpr                                    { $$ = createArithExprsStruct($1.type, $1.returnType, $1.temp, $1.lowerBound, $1.upperBound, $1.arrayElement); }
                   | ArithExprList ',' ArithExpr                  { $$ = $1; addArithExpr($$, $3.type, $3.returnType, $3.temp, $3.lowerBound, $3.upperBound, $3.arrayElement); }
                   ;

ArithExpr          : IDENTIFIER                                   { $$ = arithIdentifierCheck($1); }
                   | IDENTIFIER '[' ArithExpr ']'                 { $$ = arithArrayElementCheck($1, $3); }
                   | IDENTIFIER '[' ArithExpr RANGE ArithExpr ']' { $$ = arithArrayTrimCheck($1, $3, $5); }
                   | IDENTIFIER '(' ArithExprList ')'             { $$ = arithFunctionCheck($1, $3); }
                   | INTNUMBER                                    { $$.returnType = RETURN_TYPE_INTEGER; $$.type = TYPE_CONST; $$.ival = $1; $$.temp = generateInteger($1); }
                   | REALNUMBER                                   { $$.returnType = RETURN_TYPE_REAL; $$.type = TYPE_CONST; $$.dval = $1; $$.temp = generateReal($1); }
                   | ArithExpr '+' ArithExpr                      { $$ = arithOperatorCheck($1, $3, '+'); }
                   | ArithExpr '-' ArithExpr                      { $$ = arithOperatorCheck($1, $3, '-'); }
                   | ArithExpr '*' ArithExpr                      { $$ = arithOperatorCheck($1, $3, '*'); }
                   | ArithExpr '/' ArithExpr                      { $$ = arithOperatorCheck($1, $3, '/'); }
                   | ArithExpr DIV ArithExpr                      { $$ = arithOperatorDivModCheck($1, $3, ':'); }
                   | ArithExpr MOD ArithExpr                      { $$ = arithOperatorDivModCheck($1, $3, '%'); }
                   | '-' ArithExpr                                { $$ = arithNegationCheck($2); }
                   | '(' ArithExpr ')'                            { $$ = $2; }
                   ;

%%

void printToken(int token, FILE *f) {
  /* single character tokens */
  if (token < 256) {
    if (token < 33) {
      /* non-printable character */
      fprintf(f, "chr(%d)", token);
    } else {
      fprintf(f, "'%c'", token);
    }
    return;
  }
  /* standard tokens (>255) */
  switch (token) {
    case PROGRAM   : fprintf(f, "PROGRAM"); break;
    case CONST     : fprintf(f, "CONST"); break;
    case IDENTIFIER: fprintf(f, "identifier<%s>", yytext); break;
    case VAR       : fprintf(f, "VAR"); break;
    case ARRAY     : fprintf(f, "ARRAY"); break;
    case RANGE     : fprintf(f, ".."); break;
    case INTNUMBER : fprintf(f, "Integer<%d>", yylval.ival); break;
    case REALNUMBER: fprintf(f, "Real<%lf>", yylval.dval); break;
    case OF        : fprintf(f, "OF"); break;
    case INTEGER   : fprintf(f, "INTEGER"); break;
    case REAL      : fprintf(f, "REAL"); break;
    case FUNCTION  : fprintf(f, "FUNCTION"); break;
    case PROCEDURE : fprintf(f, "PROCEDURE"); break;
    case BEGINTOK  : fprintf(f, "BEGIN"); break;
    case ENDTOK    : fprintf(f, "END"); break;
    case ASSIGN    : fprintf(f, ":="); break;
    case IF        : fprintf(f, "IF"); break;
    case THEN      : fprintf(f, "THEN"); break;
    case ELSE      : fprintf(f, "ELSE"); break;
    case WHILE     : fprintf(f, "WHILE"); break;
    case DO        : fprintf(f, "DO"); break;
    case SKIP      : fprintf(f, "SKIP"); break;
    case READLN    : fprintf(f, "READLN"); break;
    case WRITELN   : fprintf(f, "WRITELN"); break;
  }
}

void freeLexerAndParser() {
  finalizeLexer();
  fclose(input);
  fclose(output);
  // printSymbolTable();
  freeLastFunctionName();
  freeSymbolTable();
}

void error() {
  printf("ERRORS: 1\nWARNINGS: %d\nREJECTED\n", warnings);

  freeLexerAndParser();

  exit(EXIT_SUCCESS);  /* EXIT_SUCCESS because we use Themis */
}

void yyerror (char *msg) {
  showErrorLine();
  fprintf(stderr, "%s (detected at token=", msg);
  printToken(yychar, stderr);
  fprintf(stderr, ").\n");

  error();
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s [pasfile] [outputfile]\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  input = (strcmp(argv[1], "-") == 0) ? stdin : fopen(argv[1], "r");
  if(input == NULL) {
    fprintf(stderr, "Failed to open input file!\n");
    exit(EXIT_FAILURE);
  }

  output = (strcmp(argv[2], "-") == 0) ? stdout : fopen(argv[2], "w");
  if (output == NULL) {
    fprintf(stderr, "Failed to open output file!\n");
    exit(EXIT_FAILURE);
  }

  initLexer(input);
  int result = yyparse();

  // printf("ERRORS: %d\n", 0);
  // printf("WARNINGS: %d\n", warnings);
  // puts(result == 0 ? "ACCEPTED" : "REJECTED");

  freeLexerAndParser();

  return EXIT_SUCCESS;
}