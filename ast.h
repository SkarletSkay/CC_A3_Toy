#ifndef TOY_AST_H
#define TOY_AST_H

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

typedef struct _Number {
	union {
		double realVal;
		int intVal;
	};
} Number;

typedef struct _CompoundName {
	struct _CompoundName *compoundName;
	Identifier identifier;
} CompoundName;

typedef struct _LeftPart {
	CompoundName *compoundName;
	struct _Expression *expression;
} LeftPart;

typedef struct _Factor {
	Number *number;
	LeftPart *leftPart;
	NewType *newType;
	struct _Expression *expression;
} Factor;

typedef struct _Factors {
	MultSign multSign;
	Factor *factor;
	struct _Factors *factors;
} Factors;

typedef struct _Term {
	Factor *factor;
	Factors *factors;
} Term;

typedef struct _Terms {
	AddSign addSign;
	Term *term;
	struct _Terms *terms;
} Terms;

typedef struct _Expression {
	Term *term;
	Terms *terms;
	AddSign addSign;
} Expression;

typedef struct _Assignment {
	LeftPart *leftPart;
	Expression *expression;
} Assignment;

typedef struct _Relation {
	Expression *left;
	RelationalOperator oper;
	Expression *right;
} Relation;

struct _Statement;

typedef struct _Block {
	struct _Statement **statements;
} Block;

typedef struct _PrintSatement {
	Expression *expression;
} PrintStatement;

typedef struct _ArgumentList {
	struct _ArgumentList *argumentList;
	Expression *expression;
} ArgumentList;

typedef struct _CallStatement {
	CompoundName *compoundName;
	ArgumentList *argumentList;
} CallStatement;

typedef struct _ReturnStatement {
	Expression *expression;
} ReturnStatement;

typedef struct _WhileStatement {
	Relation *relation;
	struct _Statement *statement;
} WhileStatement;

typedef struct _IfStatement {
	Relation *relation;
	struct _Statement *ifStatement;
	struct _Statement *elseStatement;
} IfStatement;

typedef struct _Statement {
	Assignment *assignment;
	IfStatement *ifStatement;
	WhileStatement *whileStatement;
	ReturnStatement *returnStatement;
	CallStatement *callStatement;
	PrintStatement *printStatement;
	Block *block;
} Statement;

typedef struct _Statements {
	struct _Statements *statements;
	Statement *statement;
} Statements;

typedef struct _Parameter {
	Type type;
	Identifier identifier;
} Parameter;

typedef struct _ParameterList {
	struct _ParameterList *parameterList;
	Parameter *parameter;
} ParameterList;

typedef struct _LocalDeclaration {
	Type type;
	Identifier identifier;
} LocalDeclaration;

typedef struct _LocalDeclarations {
	LocalDeclaration *localDeclaration;
	struct _LocalDeclarations *localDeclarations;
} LocalDeclarations;

typedef struct _Body {
	LocalDeclarations *localDeclarations;
	Statements *statements;
} Body;

typedef struct _MethodDeclaration {
	Visibility visibility;
	Staticness staticness;
	Type type;
	const char *identifier;
	ParameterList *parametes;
	Body *body;
} MethodDeclaration;

typedef struct _FieldDeclaration {
	Visibility visibility;
	Staticness staticness;
	Type type;
	Identifier identifier;
} FieldDeclaration;

typedef struct _ClassMember {
	FieldDeclaration *fieldDeclaration;
	MethodDeclaration *methodDeclaration;
} ClassMember;

typedef struct _ClassMembers {
	struct _ClassMembers *classMembers;
	ClassMember *classMember;
} ClassMembers;

typedef struct _ClassBody {
	ClassMembers *classMembers;
} ClassBody;

typedef struct _Extension {
	Identifier identifier;
} Extension;

typedef struct _ClassDeclaration {
	
} ClassDeclaration;

typedef struct _ClassDeclarations {

} ClassDeclarations;

typedef struct _Import {

} Import;

typedef struct _Imports {

} Imports;

typedef struct _CompilationUnit {
	Imports imports;
	ClassDeclarations classDeclarations;
} CompilationUnit;


#endif // TOY_AST_H