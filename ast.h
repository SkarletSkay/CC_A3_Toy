#ifndef TOY_AST_H
#define TOY_AST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define True 1
#define False 0
typedef char bool;

typedef const char* Identifier;
typedef double Number;

typedef struct _ArrayTail {
	bool is;
} ArrayTail;

ArrayTail* newArrayTail(bool);

typedef struct _IDVal {
	char* val;
} IDVal;

typedef struct _NumVal {
	double val;
} NumVal;

IDVal* newID(Identifier);

NumVal* newNumber(Number);

typedef enum _Staticness_en {
	STATIC_T, NONSTATIC_T
} Staticness_en;

typedef struct _Staticness {
	Staticness_en staticness;
} Staticness;

Staticness* newStaticness(Staticness_en staticness);

typedef enum _Visibility_en {
	PUBLIC_T, PRIVATE_T, NONE
} Visibility_en;


typedef struct _Visibility {
	Visibility_en visibility;
} Visibility;

Visibility* newVisibility(Visibility_en visibility);

typedef enum _Type_en {
	INT_T, REAL_T, INT_ARR, REAL_ARR,
	IDENTIFIER_T, IDENTIFIER_ARR,
	VOID_T
} Type_en;

typedef struct _Type {
	IDVal* identifier;
	Type_en type;
  ArrayTail* arrayTail;
} Type;

Type* newType(Type_en type, IDVal*, ArrayTail*);

typedef struct _NewType {
	IDVal* identifier;
	Type_en type;
} NewType;

typedef enum _NewTypeEn {
	N_INT, N_REAL, N_IDENTIFIER
} NewTypeEn;

NewType* newNewType(Type_en type, IDVal*);

typedef struct _MethodType {
	Type* type;
} MethodType;

MethodType* newMethodType(Type* type);
MethodType* newMethodTypeVoid(Type_en type);

typedef enum _RelationalOperator_en {
	LESS_T, GREATER_T, EQUAL_T, NOT_EQUAL_T
} RelationalOperator_en;


typedef struct _RelationalOperator {
	RelationalOperator_en relationalOperator;
} RelationalOperator;

RelationalOperator* newRelationalOperator(RelationalOperator_en relationalOperator);

typedef enum _AddSign_en {
	PLUS_T, MINUS_T
} AddSign_en;


typedef struct _AddSign{
	AddSign_en addSign;
} AddSign;


AddSign* newAddSign(AddSign_en addSign);

typedef enum _MultSign_en {
	MULTIPLY_T, DIVIDE_T
} MultSign_en;

typedef struct _MultSign{
	MultSign_en multSign;
} MultSign;


MultSign* newMultSign(MultSign_en multSign);

struct _Expression;


typedef struct _CompoundName {
	struct _CompoundName *compoundName;
	IDVal* identifier;
} CompoundName;

CompoundName *newCompoundName(CompoundName *, IDVal*);


typedef struct _LeftPart {
	CompoundName *compoundName;
	struct _Expression *expression;
} LeftPart;

LeftPart *newLeftPart(CompoundName *, struct _Expression *);


typedef struct _Factor {
	NumVal* number;
	LeftPart *leftPart;
	NewType *newType;
	struct _Expression *expression;
  bool isNull;
} Factor;

Factor *newFactorNull();

Factor *newFactorNumber(NumVal*);

Factor *newFactorLeftPart(LeftPart *);

Factor *newFactorNewTypeExpression(NewType *, struct _Expression *);


typedef struct _Factors {
	MultSign* multSign;
	Factor *factor;
	struct _Factors *factors;
} Factors;

Factors *newFactorsNull();

Factors *newFactors(MultSign*, Factor *, Factors *);


typedef struct _Term {
	Factor *factor;
	Factors *factors;
} Term;

Term *newTerm(Factor *, Factors *);


typedef struct _Terms {
	AddSign* addSign;
	Term *term;
	struct _Terms *terms;
} Terms;

Terms *newTermsNull();

Terms *newTerms(AddSign*, Term *, Terms *);


typedef struct _Expression {
	Term *term;
	Terms *terms;
	AddSign* addSign;
} Expression;

Expression *newExpression(Term *, Terms *, AddSign*);


typedef struct _Assignment {
	LeftPart *leftPart;
	Expression *expression;
} Assignment;

Assignment *newAssignment(LeftPart *, Expression *);


typedef struct _Relation {
	Expression *left;
	RelationalOperator* oper;
	Expression *right;
} Relation;

Relation *newRelation(Expression *, RelationalOperator*, Expression *);


typedef struct _Statement {
	struct _Assignment *assignment;
	struct _IfStatement *ifStatement;
	struct _WhileStatement *whileStatement;
	struct _ReturnStatement *returnStatement;
	struct _CallStatement *callStatement;
	struct _PrintStatement *printStatement;
	struct _Block *block;
} Statement;

typedef struct _Statements {
	Statement *statement;
	struct _Statements *statements;
} Statements;

typedef struct _Block {
	Statements *statements;
} Block;

Block *newBlock(Statements *);


typedef struct _PrintStatement {
	Expression *expression;
} PrintStatement;

PrintStatement *newPrintStatement(Expression *);


typedef struct _ArgumentList {
	Expression *expression;
	struct _ArgumentList *argumentList;
} ArgumentList;

ArgumentList *newArgumentList(ArgumentList *, Expression *);


typedef struct _CallStatement {
	CompoundName *compoundName;
	ArgumentList *argumentList;
} CallStatement;

CallStatement *newCallStatement(CompoundName *, ArgumentList *);


typedef struct _ReturnStatement {
	Expression *expression;
} ReturnStatement;

ReturnStatement *newReturnStatement(Expression *);

typedef struct _WhileStatement {
	Relation *relation;
	Statement *statement;
} WhileStatement;

WhileStatement *newWhileStatement(Relation *, Statement *);


typedef struct _IfStatement {
	Relation *relation;
	Statement *ifStatement;
	Statement *elseStatement;
} IfStatement;

IfStatement *newIfStatement(Relation *, Statement *, Statement *);

Statement *newStatement(Assignment *, IfStatement *,
                        WhileStatement *, ReturnStatement *,
                        CallStatement *, PrintStatement *, Block *);

Statements *newStatements(Statements *, Statement *);


typedef struct _Parameter {
	Type* type;
	IDVal* identifier;
} Parameter;

Parameter *newParameter(Type*, IDVal*);


typedef struct _ParameterList {
	Parameter *parameter;
	struct _ParameterList *parameterList;
} ParameterList;

ParameterList *newParameterList(ParameterList *, Parameter *);


typedef struct _Parameters {
	ParameterList *parameterList;
} Parameters;

Parameters *newParametersNull();

Parameters *newParameters(ParameterList *);


typedef struct _LocalDeclaration {
	Type* type;
	IDVal* identifier;
} LocalDeclaration;

LocalDeclaration *newLocalDeclaration(Type*, IDVal*);


typedef struct _LocalDeclarations {
	LocalDeclaration *localDeclaration;
	struct _LocalDeclarations *localDeclarations;
} LocalDeclarations;

LocalDeclarations *newLocalDeclarations(LocalDeclarations *, LocalDeclaration *);


typedef struct _Body {
	LocalDeclarations *localDeclarations;
	Statements *statements;
} Body;

Body *newBody(LocalDeclarations *, Statements *);


typedef struct _MethodDeclaration {
	Visibility* visibility;
	Staticness* staticness;
	MethodType* type;
	IDVal* identifier;
	Parameters *parameters;
	Body *body;
} MethodDeclaration;

MethodDeclaration *newMethodDeclaration(Visibility*, Staticness*,
                                        MethodType*, IDVal*,
                                        Parameters*, Body *);


typedef struct _FieldDeclaration {
	Visibility* visibility;
	Staticness* staticness;
	Type* type;
	IDVal* identifier;
} FieldDeclaration;

FieldDeclaration *newFieldDeclaration(Visibility*, Staticness*, Type*, IDVal*);


typedef struct _ClassMember {
	FieldDeclaration *fieldDeclaration;
	MethodDeclaration *methodDeclaration;
} ClassMember;

ClassMember *newClassMemberField(FieldDeclaration *);

ClassMember *newClassMemberMethod(MethodDeclaration *);


typedef struct _ClassMembers {
	ClassMember *classMember;
	struct _ClassMembers *classMembers;
} ClassMembers;

ClassMembers *newClassMembers(ClassMembers *, ClassMember *);


typedef struct _ClassBody {
	ClassMembers *classMembers;
} ClassBody;

ClassBody *newClassBody(ClassMembers *);


typedef struct _Extension {
	IDVal* identifier;
} Extension;

Extension *newExtension(IDVal*);


typedef struct _ClassDeclaration {
	bool isPublic;
	CompoundName *compoundName;
	Extension *extension;
	ClassBody *classBody;
} ClassDeclaration;

ClassDeclaration *newClassDeclaration(bool, CompoundName *, Extension *, ClassBody *);


typedef struct _ClassDeclarations {
	ClassDeclaration *classDeclaration;
	struct _ClassDeclarations *classDeclarations;
} ClassDeclarations;

ClassDeclarations *newClassDeclarations(ClassDeclarations *, ClassDeclaration *);


typedef struct _Import {
	IDVal* identifier;
} Import;

Import *newImport(IDVal*);


typedef struct _Imports {
	Import *anImport;
	struct _Imports *imports;
} Imports;

Imports *newImports(Imports *, Import *);


typedef struct _CompilationUnit {
	Imports *imports;
	ClassDeclarations *classDeclarations;
} CompilationUnit;


CompilationUnit *newCompilationUnit(Imports *, ClassDeclarations *);
typedef struct {
	FILE          *src;
	CompilationUnit *root;
} root_node;

void print_compilation_unit(CompilationUnit* node, int n);

void print_statement(Statement* node, int n);

void print_statements(Statements* node, int n);

void print_expression(Expression* node, int n);

#endif // TOY_AST_H
