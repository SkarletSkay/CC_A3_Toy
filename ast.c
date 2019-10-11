#include "ast.h"

RelationalOperator newRelationalOperator(RelationalOperator relationalOperator) {
	return relationalOperator;
}

Type newType(Type type) {
	return type;
}

Visibility newVisibility(Visibility visibility) {
	return visibility;
}

Staticness newStaticness(Staticness staticness) {
	return staticness;
}

AddSign newAddSign(AddSign addSign) {
	return addSign;
}

MultSign newMultSign(MultSign multSign) {
	return multSign;
}

NewType newNewType(NewType newType) {
	return newType;
}

MethodType newMethodType(Type type) {
	MethodType result;
	result.type = type;
	return result;
}

CompoundName *newCompoundName(CompoundName *compoundName, Identifier identifier) {
	CompoundName *result = malloc(sizeof(CompoundName));
	result->compoundName = compoundName;
	result->identifier = identifier;
	return result;
}

LeftPart *newLeftPart(CompoundName *compoundName, struct _Expression *expression) {
	LeftPart *result = malloc(sizeof(LeftPart));
	result->compoundName = compoundName;
	result->expression = expression;
	return result;
}

Factor *newFactorNull() {
	Factor *result = malloc(sizeof(Factor));
	return result;
}

Factor *newFactorNumber(Number number) {
	Factor *result = malloc(sizeof(Factor));
	result->number = number;
	return result;
}

Factor *newFactorLeftPart(LeftPart *leftPart) {
	Factor *result = malloc(sizeof(Factor));
	result->leftPart = leftPart;
	return result;
}

Factor *newFactorNewTypeExpression(NewType *newType, Expression *expression) {
	Factor *result = malloc(sizeof(Factor));
	result->newType = newType;
	result->expression = expression;
	return result;
}

Factors *newFactorsNull() {
	Factors *result = malloc(sizeof(Factors));
	return result;
}

Factors *newFactors(MultSign multSign, Factor *factor, Factors *factors) {
	Factors *result = malloc(sizeof(Factors));
	result->multSign = multSign;
	result->factor = factor;
	result->factors = factors;
	return result;
}

Term *newTerm(Factor *factor, Factors *factors) {
	Term *result = malloc(sizeof(Term));
	result->factor = factor;
	result->factors = factors;
	return result;
}

Terms *newTermsNull() {
	Terms *result = malloc(sizeof(Terms));
	return result;
}

Terms *newTerms(AddSign addSign, Term *term, Terms *terms) {
	Terms *result = malloc(sizeof(Terms));
	result->addSign = addSign;
	result->term = term;
	result->terms = terms;
	return result;
}

Expression *newExpression(Term *term, Terms *terms, AddSign addSign) {
	Expression *result = malloc(sizeof(Expression));
	result->term = term;
	result->terms = terms;
	result->addSign = addSign;
	return result;
}

Assignment *newAssignment(LeftPart *leftPart, Expression *expression) {
	Assignment *result = malloc(sizeof(Assignment));
	result->leftPart = leftPart;
	result->expression = expression;
	return result;
}

Relation *newRelation(Expression *left, RelationalOperator relationalOperator, Expression *right) {
	Relation *result = malloc(sizeof(Relation));
	result->left = left;
	result->oper = relationalOperator;
	result->right = right;
	return result;
}

Block *newBlock(Statements *statements) {
	Block *result = malloc(sizeof(Block));
	result->statements = statements;
	return result;
}

PrintStatement *newPrintStatement(Expression *expression) {
	PrintStatement *result = malloc(sizeof(PrintStatement));
	result->expression = expression;
	return result;
}

ArgumentList *newArgumentList(ArgumentList *argumentList, Expression *expression) {
	ArgumentList *result = malloc(sizeof(ArgumentList));
	result->argumentList = argumentList;
	result->expression = expression;
	return result;
}

CallStatement *newCallStatement(CompoundName *compoundName, ArgumentList *argumentList) {
	CallStatement *result = malloc(sizeof(CallStatement));
	result->compoundName = compoundName;
	result->argumentList = argumentList;
	return result;
}

ReturnStatement *newReturnStatement(Expression *expression) {
	ReturnStatement *result = malloc(sizeof(ReturnStatement));
	result->expression = expression;
	return result;
}

WhileStatement *newWhileStatement(Relation *relation, Statement *statement) {
	WhileStatement *result = malloc(sizeof(WhileStatement));
	result->relation = relation;
	result->statement = statement;
	return result;
}

IfStatement *newIfStatement(Relation *relation, Statement *ifStatement, Statement *elseStatement) {
	IfStatement *result = malloc(sizeof(IfStatement));
	result->relation = relation;
	result->ifStatement = ifStatement;
	result->elseStatement = elseStatement;
	return result;
}

Statement *newStatement(Assignment *assignment, IfStatement *ifStatement, WhileStatement *whileStatement,
                        ReturnStatement *returnStatement, CallStatement *callStatement, PrintStatement *printStatement,
                        Block *block) {
	Statement *result = malloc(sizeof(Statement));
	result->assignment = assignment;
	result->ifStatement = ifStatement;
	result->whileStatement = whileStatement;
	result->returnStatement = returnStatement;
	result->callStatement = callStatement;
	result->printStatement = printStatement;
	result->block = block;
	return result;
}

Statements *newStatements(Statements *statements, Statement *statement) {
	Statements *result = malloc(sizeof(Statements));
	result->statements = statements;
	result->statement = statement;
	return result;
}

Parameter *newParameter(Type type, Identifier identifier) {
	Parameter *result = malloc(sizeof(Parameter));
	result->type = type;
	result->identifier = identifier;
	return result;
}

ParameterList *newParameterList(ParameterList *parameterList, Parameter *parameter) {
	ParameterList *result = malloc(sizeof(ParameterList));
	result->parameterList = parameterList;
	result->parameter = parameter;
	return result;
}

Parameters *newParametersNull() {
	Parameters *result = malloc(sizeof(Parameters));
	return result;
}

Parameters *newParameters(ParameterList *parameterList) {
	Parameters *result = malloc(sizeof(Parameters));
	result->parameterList = parameterList;
	return result;
}

LocalDeclaration *newLocalDeclaration(Type type, Identifier identifier) {
	LocalDeclaration *result = malloc(sizeof(LocalDeclaration));
	result->type = type;
	result->identifier = identifier;
	return result;
}

LocalDeclarations *newLocalDeclarations(LocalDeclarations *localDeclarations, LocalDeclaration *localDeclaration) {
	LocalDeclarations *result = malloc(sizeof(LocalDeclarations));
	result->localDeclarations = localDeclarations;
	result->localDeclaration = localDeclaration;
	return result;
}

Body *newBody(LocalDeclarations *localDeclarations, Statements *statements) {
	Body *result = malloc(sizeof(Body));
	result->localDeclarations = localDeclarations;
	result->statements = statements;
	return result;
}

MethodDeclaration *newMethodDeclaration(Visibility visibility, Staticness staticness,
                                        Type type, Identifier identifier,
                                        ParameterList *parameterList, Body *body) {
	MethodDeclaration *result = malloc(sizeof(MethodDeclaration));
	result->visibility = visibility;
	result->staticness = staticness;
	result->type = type;
	result->identifier = identifier;
	result->parameterList = parameterList;
	result->body = body;
	return result;
}

FieldDeclaration *newFieldDeclaration(Visibility visibility, Staticness staticness,
                                      Type type, Identifier identifier) {
	FieldDeclaration *result = malloc(sizeof(FieldDeclaration));
	result->visibility = visibility;
	result->staticness = staticness;
	result->type = type;
	result->identifier = identifier;
	return result;
}

ClassMember *newClassMemberField(FieldDeclaration *fieldDeclaration) {
	ClassMember *result = malloc(sizeof(ClassMember));
	result->fieldDeclaration = fieldDeclaration;
	return result;
}

ClassMember *newClassMemberMethod(MethodDeclaration *methodDeclaration) {
	ClassMember *result = malloc(sizeof(ClassMember));
	result->methodDeclaration = methodDeclaration;
	return result;
}

ClassMembers *newClassMembers(ClassMembers *classMembers, ClassMember *classMember) {
	ClassMembers *result = malloc(sizeof(ClassMembers));
	result->classMembers = classMembers;
	result->classMember = classMember;
	return result;
}

ClassBody *newClassBody(ClassMembers *classMembers) {
	ClassBody *result = malloc(sizeof(ClassBody));
	result->classMembers = classMembers;
	return result;
}

Extension *newExtension(Identifier identifier) {
	Extension *result = malloc(sizeof(Extension));
	result->identifier = identifier;
	return result;
}

ClassDeclaration *
newClassDeclaration(bool bool, CompoundName *compoundName, Extension *extension, ClassBody *classBody) {
	ClassDeclaration *result = malloc(sizeof(ClassDeclaration));
	result->isPublic = bool;
	result->compoundName = compoundName;
	result->extension = extension;
	result->classBody = classBody;
	return result;
}

ClassDeclarations *newClassDeclarations(ClassDeclarations *classDeclarations, ClassDeclaration *classDeclaration) {
	ClassDeclarations *result = malloc(sizeof(ClassDeclarations));
	result->classDeclarations = classDeclarations;
	result->classDeclaration = classDeclaration;
	return result;
}

Import *newImport(Identifier identifier) {
	Import *result = malloc(sizeof(Import));
	result->identifier = identifier;
	return result;
}

Imports *newImports(Imports *imports, Import *import) {
	Imports *result = malloc(sizeof(Imports));
	result->imports = imports;
	result->anImport = import;
	return result;
}

CompilationUnit *newCompilationUnit(Imports *imports, ClassDeclarations *classDeclarations) {
	CompilationUnit *result = malloc(sizeof(CompilationUnit));
	result->imports = imports;
	result->classDeclarations = classDeclarations;
	return result;
}
