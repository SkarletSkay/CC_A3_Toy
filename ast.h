#ifndef TOY_AST_H
#define TOY_AST_H

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