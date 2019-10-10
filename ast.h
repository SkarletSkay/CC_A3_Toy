#ifndef TOY_AST_H
#define TOY_AST_H

typedef enum {
	STATIC, NONE
} Staticness;

typedef enum {
	PUBLIC, PRIVATE, NONE
} Visibility;

typedef enum {
	INT, REAL, INT_ARR, REAL_ARR,
	IDENTIFIER, IDENTIFIER_ARR
} Type;

typedef enum {
	INT, REAL, INT_ARR, REAL_ARR,
	IDENTIFIER, IDENTIFIER_ARR,
	VOID
} MethodType;

typedef struct _ParameterList {

} ParameterList;

typedef struct _MethodDeclaration {
	Visibility visibility;
	Staticness staticness;
	MethodType type;
	const char *identifier;
	ParameterList parametes;
	// Body body;
} MethodDeclaration;

typedef struct _FieldDeclaration {

} FieldDeclaration;

typedef struct _ClassMember {

} ClassMember;

typedef struct _ClassMembers {

} ClassMembers;

typedef struct _ClassBody {

} ClassBody;

typedef struct _Extension {

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