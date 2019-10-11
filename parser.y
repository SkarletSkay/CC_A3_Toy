%define api.pure full
%lex-param {void *lex}
%parse-param {void *lex}{root_node *r}

%define parse.trace
%define parse.error verbose

%{
#include <stdio.h>
#include "ast.h"
#include "parser.tab.h"
#include "lex.h"

void yyerror (yyscan_t *locp, root_node *r, char const *msg);
%}

%code requires
{
#include "ast.h"
}

%define api.value.type union
%token <long>           NUMBER     "number"
%token <const char *>   IDENTIFIER "identifier"

%token TOK_EOF 0 "end of file"

// Keywords
%token IMPORT
%token CLASS
%token EXTENDS
%token PRIVATE
%token PUBLIC
%token STATIC
%token VOID
%token IF
%token ELSE
%token WHILE
%token LOOP
%token RETURN
%token PRINT
%token NULLVAL
%token NEW
// Delimiters

%token LBRACE      //  {
%token RBRACE      //  }
%token LPAREN      //  (
%token RPAREN      //  )
%token LBRACKET    //  [
%token RBRACKET    //  ]
%token COMMA       //  ,
%token DOT         //  .
%token SEMICOLON   //  ;

// Operator signs
%token ASSIGN      //  =
%token LESS        //  <
%token GREATER     //  >
%token EQUAL       //  ==
%token NOT_EQUAL   //  !=
%token PLUS        //  +
%token MINUS       //  -
%token MULTIPLY    //  *
%token DIVIDE      //  /
%token REAL
%token INT

%type <CompilationUnit*> ComilationUnit
%type <Imports*> Imports
%type <Import*> Import
%type <ClassDeclarations*> ClassDeclarations
%type <ClassDeclaration*> ClassDeclaration
%type <Extension*> Extension
%type <ClassBody*> ClassBody
%type <ClassMembers*> ClassMembers
%type <ClassMember*> ClassMember
%type <FieldDeclaration*> FieldDeclaration
%type <Visibility*> Visibility
%type <Staticness*> Staticness
%type <MethodDeclaration*> MethodDeclaration
%type <Parameters*> Parameters
%type <ParameterList*> ParameterList
%type <Parameter*> Parameter
%type <MethodType*> MethodType
%type <Body*> Body
%type <LocalDeclarations*> LocalDeclarations
%type <LocalDeclaration*> LocalDeclaration
%type <Statements*> Statements
%type <Statement*> Statement
%type <Assignment*> Assignment
%type <LeftPart*> LeftPart
%type <CompoundName*> CompoundName
%type <IfStatement*> IfStatement
%type <WhileStatement*> WhileStatement
%type <ReturnStatement*> ReturnStatement
%type <CallStatement*> CallStatement
%type <ReturnStatement*> ReturnStatement
%type <ArgumentList*> ArgumentList
%type <ReturnStatement*> ReturnStatement
%type <PrintStatement*> PrintStatement
%type <Block*> Block
%type <Relation*> Relation
%type <RelationOperator*> RelationalOperator
%type <Expression*> Expression
%type <AddSign*> AddSign
%type <Terms*> Terms
%type <Term*> Term
%type <Factors*> Factors
%type <MultSignr*> MultSign
%type <Factor*> Factor
%type <NewType*> NewType
%type <Type*> Type
%type <ArrayTail*> ArrayTail
%%

%start CompilationUnit;


CompilationUnit
       : Imports ClassDeclarations { r->root = newCompilationUnit($1, $2); }
       ;

Imports
       :  /* empty */   { $$ = NULL; }
       | Import Imports { $$ = newImports($2, $1); }
       ;

Import
       : IMPORT IDENTIFIER SEMICOLON { $$ = newImport($2); }
       ;

ClassDeclarations
       : /* empty */ { $$ = NULL; }
       | ClassDeclaration ClassDeclarations {$$ = newClassDeclarations($2, $1); }
       ;

ClassDeclaration
       : CLASS CompoundName Extension SEMICOLON ClassBody {$$ = newClassDeclaration(0, $2, $3, $5); }
       | PUBLIC CLASS CompoundName Extension SEMICOLON ClassBody {$$ = newClassDeclaration(1 , $2, $3, $5); }
       ;

Extension
       : /* empty */ {$$ = NULL; } 
       | EXTENDS IDENTIFIER {$$ = newExtension($2); }
       ;

ClassBody
       : LBRACE              RBRACE {$$ = newClassBody(NULL); }
       | LBRACE ClassMembers RBRACE {$$ = newClassBody($2); }
       ;

ClassMembers
       :              ClassMember {$$ = newСlassMembers(NULL, $1); }
       | ClassMembers ClassMember {$$ = newClassMembers($1, $2); }
       ;

ClassMember
       : FieldDeclaration {$$ = newClassMemberField($1); }
       | MethodDeclaration {$$ = newClassMemberMethod($1); }
       ;

FieldDeclaration
       : Visibility Staticness Type IDENTIFIER SEMICOLON {$$ = newFieldDeclaration($1, $2, $3, $4); }
       ;

Visibility
       : /* empty */ {$$ = newVisibility(NULL); }
       | PRIVATE  {$$ = newVisibility(PRIVATE); }
       | PUBLIC {$$ = newVisibility(PUBLIC); }
       ;

Staticness
       : /* empty */ {$$ = NULL; }
       | STATIC {$$ = newStaticness($1); }
       ;

MethodDeclaration
       : Visibility Staticness MethodType IDENTIFIER Parameters
            Body {$$ = newMethodDeclaration($1, $2, $3, $4, $5; $6); }
       ;

Parameters
       : LPAREN               RPAREN {$$ = newParameters(NULL); }
       | LPAREN ParameterList RPAREN {$$ = newParameters($1); }
       ;

ParameterList
       :                     Parameter {$$ = newParameterList(NULL, $1); }
       | ParameterList COMMA Parameter {$$ = newParameterList($1, $2); }
       ;

Parameter
       : Type IDENTIFIER  {$$ = newParameter($1, $2); }
       ;

MethodType
       : Type {$$ = newMethodType($1); }
       | VOID {$$ = newMethodType(VOID); }
       ;

Body
       : LBRACE LocalDeclarations Statements RBRACE {$$ = newBody($1, $2); }
       ;

LocalDeclarations
       :                   LocalDeclaration {$$ = newLocalDeclarations(NULL, $1); }
       | LocalDeclarations LocalDeclaration {$$ = newLocalDeclarations($1, $2); }
       ;

LocalDeclaration
       : Type IDENTIFIER SEMICOLON {$$ = newLocalDeclaration($1, $2); }
       ;

Statements
       :            Statement {$$ = newStatements(NULL, $1); }
       | Statements Statement {$$ = newStatements($1, $2); }
       ;

Statement
       : Assignment {$$ = newStatement($1, NULL, NULL, NULL, NULL, NULL, NULL); }
       | IfStatement {$$ = newStatement(NULL, $1, NULL, NULL, NULL, NULL, NULL,); }
       | WhileStatement {$$ = newStatement(NULL, NULL, $1, NULL, NULL, NULL, NULL); }
       | ReturnStatement {$$ = newStatement(NULL, NULL, NULL, $1, NULL, NULL, NULL); }
       | CallStatement {$$ = newStatement(NULL, NULL, NULL, NULL, $1, NULL, NULL); }
       | PrintStatement {$$ = newStatement(NULL, NULL, NULL, NULL, NULL, $1, NULL); }
       | Block {$$ = newStatement(NULL, NULL, NULL, NULL, NULL, NULL, $1); }
       ;

Assignment
       : LeftPart ASSIGN Expression SEMICOLON  {$$ = newAssignment($1,$3); }
       ;

LeftPart
       : CompoundName                               {$$ = newLeftPart($1, NULL); }
       | CompoundName LBRACKET Expression RBRACKET  {$$ = newLeftPart($1, $2); }
       ;

CompoundName
       :                  IDENTIFIER {$$ =newCompoundName( NULL,$1); }
       | CompoundName DOT IDENTIFIER {$$ = newCompoundName($1, $2); }
       ;

IfStatement
       : IF LPAREN Relation RPAREN Statement                  {$$ = newIfStatement($1, $2, NULL); }
       | IF LPAREN Relation RPAREN Statement ELSE Statement   {$$ = newIfStatement($1, $2, $3); }
       ;

WhileStatement
       : WHILE Relation LOOP Statement SEMICOLON {$$ = newWhileStatement($1, $2); }
       ;

ReturnStatement
       : RETURN            SEMICOLON  {$$ = newReturnStatement(NULL); }
       | RETURN Expression SEMICOLON  {$$ = newReturnStatement($1); }
       ;

CallStatement
       : CompoundName LPAREN              RPAREN SEMICOLON  {$$ = newCallStatement($1, NULL); }
       | CompoundName LPAREN ArgumentList RPAREN SEMICOLON  {$$ = newCallStatement($1, $2); }
       ;

ArgumentList
       :                    Expression  {$$ = newArgumentList(NULL, $1); }
       | ArgumentList COMMA Expression  {$$ = newArgumentList($1, $2); }
       ;

PrintStatement
       : PRINT Expression SEMICOLON  {$$ = newPrintStatement($1); }
       ;

Block
       : LBRACE            RBRACE {$$ = newBlock(NULL); }
       | LBRACE Statements RBRACE {$$ = newBlock($1); }
       ;

Relation
       : Expression                                 {$$ = newRelation($1, NULL, NULL); }
       | Expression RelationalOperator Expression   {$$ = newRelation($1, $2, $3); }
       ;

RelationalOperator
       : LESS       {$$ = newRelationOperator(LESS); }
       | GREATER    {$$ = newRelationOperator(GREATER); }
       | EQUAL      {$$ = newRelationOperator(EQUAL); }
       | NOT_EQUAL  {$$ = newRelationOperator(NOT_EQUAL); }
       ;

Expression
       : Term Terms           {$$ = newExpression($1, $2, NULL); }
       | AddSign Term Terms   {$$ = newExpression($2, $3, $1); }
       ;

AddSign
       : PLUS     {$$ = newAddSign(PLUS); }
       | MINUS    {$$ = newAddSign(MINUS); }
       ;

Terms
       : /* empty */          {$$ = NULL; }
       | AddSign Term Terms   {$$ = newTerms($1, $2, $3); }
       ;

Term
       : Factor Factors {$$ = newTerm($1, $2); }
       ;

Factors
       : /* empty */              {$$ = NULL; }
       | MultSign Factor Factors  {$$ = newFactors($1, $2, $3); }
       ;

MultSign
       : MULTIPLY   {$$ = newMultiSign(MULTIPLY); }
       | DIVIDE     {$$ = newMultiSign(DIVIDE); }
       ;

Factor
       : NUMBER                                       {$$ = new_factor($1, NULL); }
       | LeftPart                                     {$$ = new_factor($1, NULL); }
       | NULLVAL                                      {$$ = new_factor(NULLVALL); }
       | NEW NewType                                  {$$ = new_factor($1, NULL); }
       | NEW NewType LBRACKET Expression RBRACKET     {$$ = new_factor($1, $2); }
       ;

NewType
       : INT          {$$ = newNewType(INT, $1); }
       | REAL         {$$ = newNewType(REAL, $1); }
       | IDENTIFIER   {$$ = newNewType(IDENTIFIER, $1); }
       ;

Type
       : INT        ArrayTail  {$$ = newType(INT, $1); }
       | REAL       ArrayTail  {$$ = newType(REAL, $1); }
       | IDENTIFIER ArrayTail  {$$ = newType(IDENTIFIER, $1); }
       ;

ArrayTail
       : /* empty */       {$$ = NULL; 
       | LBRACKET RBRACKET {$$ = newArrayTail(ARRAYTAIL); 
       ;

%%

void yyerror (yyscan_t *locp, root_node *r, char const *msg) {
	fprintf(stderr, "--> %s\n", msg);
}

