#ifndef TOY_AST_H
#define TOY_AST_H

#define True 1
#define False 0
typedef char bool;


typedef enum _Staticness {
	STATIC, NONSTATIC
} Staticness;

typedef enum _Visibility {
	PUBLIC, PRIVATE, NONE
} Visibility;

typedef enum _Type {
	INT, REAL, INT_ARR, REAL_ARR,
	IDENTIFIER, IDENTIFIER_ARR,
	VOID
} Type;

typedef enum _RelationalOperator {
	LESS, GREATER, EQUAL, NOT_EQUAL
} RelationalOperator;

typedef enum _AddSign {
	PLUS, MINUS
} AddSign;

typedef enum _MultSign {
	MULTIPLY, DIVIDE
} MultSign;

typedef const char *Identifier;

struct _Expression;

typedef struct _NewType {
	const char *identifier;
	Type type;
	union {
		double realVal;
		int intVal;
	};
} NewType;

typedef union _Number {
	double realVal;
	int intVal;
} Number;


typedef struct _CompoundName {
	struct _CompoundName *compoundName;
	Identifier identifier;
} CompoundName;

CompoundName *newCompoundName(CompoundName *, Identifier);


typedef struct _LeftPart {
	CompoundName *compoundName;
	struct _Expression *expression;
} LeftPart;

LeftPart *newLeftPart(CompoundName *, struct _Expression *);


typedef struct _Factor {
	Number number;
	LeftPart *leftPart;
	NewType *newType;
	struct _Expression *expression;
} Factor;

Factor *newFactorNumber(Number);

Factor *newFactorLeftPart(LeftPart *);


typedef struct _Factors {
	MultSign multSign;
	Factor *factor;
	struct _Factors *factors;
} Factors;

Factors *newFactorsNull();

Factors *newFactors(MultSign, Factor *, Factors *);


typedef struct _Term {
	Factor *factor;
	Factors *factors;
} Term;

Term *newTerm(Factor *, Factors *);


typedef struct _Terms {
	AddSign addSign;
	Term *term;
	struct _Terms *terms;
} Terms;

Terms *newTermsNull();

Terms *newTerms(AddSign, Term *, Terms *);


typedef struct _Expression {
	Term *term;
	Terms *terms;
	AddSign addSign;
} Expression;

Expression *newExpression(Term *, Terms *, AddSign);


typedef struct _Assignment {
	LeftPart *leftPart;
	Expression *expression;
} Assignment;

Assignment *newAssignment(LeftPart *, Expression *);


typedef struct _Relation {
	Expression *left;
	RelationalOperator oper;
	Expression *right;
} Relation;

Relation *newRelation(Expression *, RelationalOperator, Expression *);


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
	Statement **statements;
} Block;

Block *newBlock(Statements *);


typedef struct _PrintSatement {
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
	Type type;
	Identifier identifier;
} Parameter;

Parameter *newParameter(Type *, Identifier *);


typedef struct _ParameterList {
	Parameter *parameter;
	struct _ParameterList *parameterList;
} ParameterList;

ParameterList *newParameterList(ParameterList *, Parameter *);


typedef struct _LocalDeclaration {
	Type type;
	Identifier identifier;
} LocalDeclaration;

LocalDeclaration *newLocalDeclaration(Type *, Identifier *);


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
	Visibility visibility;
	Staticness staticness;
	Type type;
	const char *identifier;
	ParameterList *parametes;
	Body *body;
} MethodDeclaration;

MethodDeclaration *newMethodDeclaration(Visibility *, Staticness *,
                                        Type *, Identifier *,
                                        ParameterList *, Body *);


typedef struct _FieldDeclaration {
	Visibility visibility;
	Staticness staticness;
	Type type;
	Identifier identifier;
} FieldDeclaration;

FieldDeclaration *newFieldDeclaration(Visibility *, Staticness *, Type *, Identifier *);


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
	Identifier identifier;
} Extension;

Extension *newExtension(Identifier);


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
	Identifier identifier;
} Import;

Import *newImport(Identifier);


typedef struct _Imports {
	Import *anImport;
	struct _Imports *imports;
} Imports;

Imports *newImports(Imports *, Import *);


typedef struct _CompilationUnit {
	Imports imports;
	ClassDeclarations classDeclarations;
} CompilationUnit;

CompilationUnit *newCompilationUnit(Imports *, ClassDeclarations *);


#endif // TOY_AST_H