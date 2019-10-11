#include "ast.h"

IDVal* newID(Identifier identifier){
  IDVal* res = malloc(sizeof(IDVal));
  res->val = (char *) malloc(strlen( identifier) + 1);
  strcpy(res->val, identifier);   
  return res;
}


NumVal* newNumber(Number number){
  NumVal* res = malloc(sizeof(NumVal));
  res->val = number;
  return res;
}


ArrayTail* newArrayTail(bool b){
  ArrayTail *result = malloc(sizeof(ArrayTail));
  result->is = b;
  return result;
}

RelationalOperator* newRelationalOperator(RelationalOperator_en relationalOperator) {
  RelationalOperator* result =  malloc(sizeof(RelationalOperator));
  result->relationalOperator = relationalOperator;
	return result;
}

Type* newType(Type_en type, IDVal* identifier, ArrayTail* arrayTail) {
	Type *result = malloc(sizeof(Type ));
  result->type = type;
  result->arrayTail = arrayTail;
  if(type == IDENTIFIER_T){
    result->identifier =  identifier;
  }
	return result;
}

Visibility* newVisibility(Visibility_en visibility) {
  Visibility *res = malloc(sizeof(Visibility));
  res->visibility = visibility;
	return res;
}

Staticness* newStaticness(Staticness_en staticness) {
  Staticness *res = malloc(sizeof(Staticness));
  res->staticness = staticness;
	return res;
}

AddSign* newAddSign(AddSign_en addSign) {
  AddSign* result = malloc(sizeof(AddSign));
  result->addSign = addSign;
	return result;
}

MultSign* newMultSign(MultSign_en multSign) {
  MultSign* result = malloc(sizeof(MultSign));
  result->multSign = multSign;
	return result;
}

NewType* newNewType(Type_en newType, IDVal* identifier) {
  NewType *result = malloc(sizeof(NewType ));
  result->type = newType;
  result->identifier = identifier;
	return result;
}

MethodType* newMethodType(Type* type) {
	MethodType* result = malloc(sizeof(MethodType));
	result->type = type;
	return result;
}

MethodType* newMethodTypeVoid(Type_en type) {
	MethodType* result = malloc(sizeof(MethodType));
	result->type = newType(type, NULL, NULL);
	return result;
}

CompoundName *newCompoundName(CompoundName *compoundName, IDVal* identifier) {
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
  result->isNull = 1;
	return result;
}

Factor *newFactorNumber(NumVal* number) {
	Factor *result = malloc(sizeof(Factor));
	result->number = number;
  result->isNull = 0;
	return result;
}

Factor *newFactorLeftPart(LeftPart *leftPart) {
	Factor *result = malloc(sizeof(Factor));
  result->isNull = 0;
	result->leftPart = leftPart;
	return result;
}

Factor *newFactorNewTypeExpression(NewType *newType, Expression *expression) {
	Factor *result = malloc(sizeof(Factor));
  result->isNull = 0;
	result->newType = newType;
	result->expression = expression;
	return result;
}

Factors *newFactorsNull() {
	Factors *result = malloc(sizeof(Factors));
	return result;
}

Factors *newFactors(MultSign* multSign, Factor *factor, Factors *factors) {
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

Terms *newTerms(AddSign* addSign, Term *term, Terms *terms) {
	Terms *result = malloc(sizeof(Terms));
	result->addSign = addSign;
	result->term = term;
	result->terms = terms;
	return result;
}

Expression *newExpression(Term *term, Terms *terms, AddSign* addSign) {
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

Relation *newRelation(Expression *left, RelationalOperator* relationalOperator, Expression *right) {
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

Parameter *newParameter(Type* type, IDVal* identifier) {
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

LocalDeclaration *newLocalDeclaration(Type *type, IDVal* identifier) {
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

MethodDeclaration *newMethodDeclaration(Visibility* visibility, Staticness* staticness,
                                        MethodType* type, IDVal* identifier,
                                        Parameters *parameters, Body *body) {
	MethodDeclaration *result = malloc(sizeof(MethodDeclaration));
	result->visibility = visibility;
	result->staticness = staticness;
	result->type = type;
	result->identifier = identifier;
	result->parameters= parameters;
	result->body = body;
	return result;
}

FieldDeclaration *newFieldDeclaration(Visibility* visibility, Staticness* staticness,
                                      Type* type, IDVal* identifier) {
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

Extension *newExtension(IDVal* identifier) {
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

Import *newImport(IDVal* identifier) {
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

void make_dist(int n){
  for(int i = 0; i < n; i++){
    printf("   ");  
  }
}

void print_array_tail(ArrayTail* node, int n){
  make_dist(n);
  printf("Array Tail: ");
  printf("[]");
  printf("\n");
}

void print_type(Type* node, int n){
  make_dist(n);
  printf("Type: { \n");
  if(node->type == IDENTIFIER_T){
    make_dist(n+1);
    printf("Identifier %s", node->identifier->val);
    printf("\n");
  }else if(node->type == INT_T){
    make_dist(n+1);
    printf("INT");
    printf("\n");
  }else if(node->type == REAL_T){
    make_dist(n+1);
    printf("REAL");
    printf("\n");
  }
  if(node->arrayTail != NULL){
    print_array_tail(node->arrayTail, n+1);
  }
  make_dist(n);
  printf(" }\n");
}

void print_new_type(NewType* node, int n){
  make_dist(n);
  printf("New Type: {");
  if(node->type == IDENTIFIER_T){
    printf("Identifier %s", node->identifier->val);
  }else if(node->type == INT_T){
    printf("INT");
  }else if(node->type == REAL_T){
    printf("REAL");
  }
  printf(" }\n");
}

void print_add_sign(AddSign* node, int n){
  make_dist(n);
  printf("Add: { ");
  if(node->addSign == PLUS_T){
    printf("+");
  }else if(node->addSign == MINUS_T ){
    printf("-");
  }
  printf(" }\n");
}

void print_factor(Factor* node, int n){
  make_dist(n);
  printf("Factor: { \n");
  if(node->leftPart != NULL){
  
  }else if(node->isNull){
    make_dist(n+1);
    printf("NULL\n");
  }else if(node->newType != NULL){
    print_new_type(node->newType, n+1);
    if(node->expression != NULL){
      print_expression(node->expression, n+1);
    }
  }else{
    make_dist(n+1);
    printf("%f", (node->number->val));
    printf("\n");
  }
  make_dist(n);
  printf(" }\n");
}

void print_mult_sign(MultSign* node, int n){
  make_dist(n);
  printf("Mult: { ");
  if(node->multSign == MULTIPLY_T){
    printf("*");
  }else if(node->multSign == DIVIDE_T ){
    printf("/");
  }
  make_dist(n);
  printf(" }\n");
}

void print_factors(Factors* node, int n){
  make_dist(n);
  printf("Factors: { \n");
  print_mult_sign(node->multSign, n+1);
  print_factor(node->factor, n+1);
  if(node->factors != NULL){
    print_factors(node->factors, n+1);
  }
  make_dist(n);
  printf(" }\n");
}

void print_term(Term* node, int n){
  make_dist(n);
  printf("Term: { \n");
  print_factor(node->factor, n+1);
  if(node->factors != NULL){
    print_factors(node->factors, n+1);
  }
  make_dist(n);
  printf(" }\n");
}

void print_terms(Terms* node, int n){
  make_dist(n);
  printf("Terms: { \n");
  print_add_sign(node->addSign, n+1);
  print_term(node->term, n+1);
  if(node->terms != NULL){
    print_terms(node->terms, n+1);
  }
  make_dist(n);
  printf(" }\n");
}

void print_expression(Expression* node, int n){
  make_dist(n);
  printf("Expression: { \n");
  if(node->addSign != NULL){
    print_add_sign(node->addSign, n+1);
  }
  print_term(node->term, n+1);
  if(node->terms != NULL){
    print_terms(node->terms, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_relational_operator(RelationalOperator* node, int n){
  make_dist(n);
  printf("Relational Operator: {");
  if(node->relationalOperator == LESS_T){
    printf(" < ");
  }else if(node->relationalOperator == GREATER_T){
    printf(" > ");
  }else if(node->relationalOperator == EQUAL_T){
    printf(" = ");
  }else if(node->relationalOperator == NOT_EQUAL_T){
    printf(" != ");
  }

  printf("}\n");
}

void print_relation(Relation* node, int n){
  make_dist(n);
  printf("Relation: {\n");
  print_expression(node->left, n+1);
  if(node->oper != NULL){
    print_relational_operator(node->oper, n+1);
  } 
  if(node->right != NULL){
    print_expression(node->right, n+1);
  } 
  make_dist(n);
  printf("}\n");
}

void print_block(Block* node, int n){
  make_dist(n);
  printf("Block: {");
  if(node->statements != NULL){
    printf("\n");
    print_statements(node->statements, n+1);
    make_dist(n);
  } 
  printf("}\n");
}

void print_print_statement(PrintStatement* node, int n){
  make_dist(n);
  printf("Print: {\n");
  print_expression(node->expression, n+1);
  make_dist(n);
  printf("}\n");
}

void print_argument_list(ArgumentList* node, int n){
  make_dist(n);
  printf("Arguments: {\n");
  print_expression(node->expression, n+1);
  if(node->argumentList != NULL){
    print_argument_list(node->argumentList , n+1);
  } 
  make_dist(n);
  printf("}\n");
}

void print_compound_name(CompoundName* node, int n){
  make_dist(n);
  printf("Compound Name: {\n");
  if(node->compoundName != NULL){
    print_compound_name(node->compoundName, n+1);
  } 
  make_dist(n+1);
  printf("Identifier %s", node->identifier->val);
  printf("\n");
  make_dist(n);
  printf("}\n");
}

void print_call_statement(CallStatement* node, int n){
  make_dist(n);
  printf("Call: {\n");
  print_compound_name(node->compoundName, n+1);
  if(node->argumentList != NULL){
    print_argument_list(node->argumentList , n+1);
  } 
  make_dist(n);
  printf("}\n");
}

void print_return_statement(ReturnStatement* node, int n){
  make_dist(n);
  printf("Return: {");
  if(node->expression != NULL){
    printf("\n");
    print_expression(node->expression, n+1);
    make_dist(n);
  } 
  printf("}\n");
}

void print_while_statement(WhileStatement* node, int n){
  make_dist(n);
  printf("While: {\n");
  print_relation(node->relation, n+1);
  print_statement(node->statement, n+1);
  make_dist(n);
  printf("}\n");
}

void print_if_statement(IfStatement* node, int n){
  make_dist(n);
  printf("If: {\n");
  print_relation(node->relation, n+1);
  print_statement(node->ifStatement, n+1);
  if(node->elseStatement != NULL){
    print_statement(node->elseStatement, n+1);
  } 
  make_dist(n);
  printf("}\n");
}

void print_left_part(LeftPart* node, int n){
  make_dist(n);
  printf("Left Part: {\n");
  print_compound_name(node->compoundName, n+1);
  if(node->expression != NULL){
    print_expression(node->expression, n+1);
  }  
  make_dist(n);
  printf("}\n");
}

void print_assignment(Assignment* node, int n){
  make_dist(n);
  printf("Assign: {\n");
  print_left_part(node->leftPart, n+1);
  print_expression(node->expression, n+1);
  make_dist(n);
  printf("}\n");
}

void print_statement(Statement* node, int n){
  make_dist(n);
  printf("Statement: {\n");
  if(node->assignment != NULL){
    print_assignment(node->assignment, n+1);
  }else if(node->ifStatement != NULL){
    print_if_statement(node->ifStatement, n+1);
  }else if(node->whileStatement != NULL){
    print_while_statement(node->whileStatement, n+1);
  }else if(node->returnStatement != NULL){
    print_return_statement(node->returnStatement, n+1);
  }else if(node->callStatement != NULL){
    print_call_statement(node->callStatement, n+1);
  }else if(node->printStatement != NULL){
    print_print_statement(node->printStatement, n+1);
  }else if(node->block != NULL){
    print_block(node->block, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_statements(Statements* node, int n){
  make_dist(n);
  printf("Statements: {\n");
  print_statement(node->statement, n+1);
  if(node->statements != NULL){
     print_statements(node->statements, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_local_declaration(LocalDeclaration* node, int n){
  make_dist(n);
  printf("Local Declaration: {\n");
  print_type(node->type, n+1);
  make_dist(n+1);
  printf("Identifier %s", node->identifier->val);
  printf("\n");
  make_dist(n);
  printf("}\n");
}

void print_local_declarations(LocalDeclarations* node, int n){
  make_dist(n);
  printf("Local Declarations: {\n");
  print_local_declaration(node->localDeclaration, n+1);
  if(node->localDeclarations != NULL){
     print_local_declarations(node->localDeclarations, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_body(Body* node, int n){
  make_dist(n);
  printf("Body: {\n");
  print_local_declarations(node->localDeclarations, n+1);
  print_statements(node->statements, n+1);
  make_dist(n);
  printf("}\n");
}

void print_method_type(MethodType* node, int n){
  make_dist(n);
  printf("Method Type: {");
  if(node->type->type == VOID_T){
    printf("VOID");
  }else{
    printf("\n");
    print_type(node->type, n+1);     
    make_dist(n); 
  }
  printf("}\n");
}

void print_parameter(Parameter* node, int n){
  make_dist(n);
  printf("Parameter: {\n");
  print_type(node->type, n+1);
  make_dist(n+1);
  printf("%s",node->identifier->val);
  printf("\n");
  make_dist(n);
  printf("}\n");
}

void print_parameter_list(ParameterList* node, int n){
  make_dist(n);
  printf("Parameter List: {\n");
  print_parameter(node->parameter, n+1);
  if(node->parameterList != NULL ){
    print_parameter_list(node->parameterList, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_parameters(Parameters* node, int n){
  make_dist(n);
  printf("Parameters: {");
  if(node->parameterList != NULL ){
    printf("\n");
    print_parameter_list(node->parameterList, n+1);
     make_dist(n);
  }
  printf("}\n");
}
void print_visibility(Visibility* node, int n){
  make_dist(n);
  printf("Visibility: { ");
  if(node->visibility == PUBLIC_T ){
    printf("PUBLIC");
  }else if(node->visibility == PRIVATE_T ){
    printf("PRIVATE");
  }
  printf(" }\n");
}

void print_staticness(Staticness* node, int n){
  make_dist(n);
  printf("Staticness: { ");
  if(node->staticness == STATIC_T ){
    printf("STATIC");
  }
  printf(" }\n");
}

void print_method_declaration(MethodDeclaration* node, int n){
  make_dist(n);
  printf("Method Declaration: {\n");
  if(node->visibility->visibility != NONE){
    print_visibility(node->visibility, n+1);
  }
  if(node->staticness->staticness != NONSTATIC_T){
    print_staticness(node->staticness, n+1);
  }
  print_method_type(node->type, n+1);
  make_dist(n+1);
  printf("Identifier %s",node->identifier->val);
  printf("\n");
  print_parameters(node->parameters, n+1);
  print_body(node->body, n+1);
  make_dist(n);
  printf("}\n");
}


void print_field_declaration(FieldDeclaration* node, int n){
  make_dist(n);
  printf("Field Declaration: {\n");
  if(node->visibility->visibility != NONE){
    print_visibility(node->visibility, n+1);
  }
  if(node->staticness->staticness != NONSTATIC_T){
    print_staticness(node->staticness, n+1);
  }
  print_type(node->type, n+1);
  make_dist(n+1);
  printf("Identifier %s", node->identifier->val);
  printf("\n");
  make_dist(n);
  printf("}\n");
}

void print_class_member(ClassMember* node, int n){
  make_dist(n);
  printf("Class Member: {\n");
  if(node->fieldDeclaration != NULL){
    print_field_declaration(node->fieldDeclaration, n+1);
  }else if (node->methodDeclaration != NULL){
    print_method_declaration(node->methodDeclaration, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_class_members(ClassMembers* node, int n){
  make_dist(n);
  printf("Class Members: {\n");
  print_class_member(node->classMember, n+1);
  if(node->classMembers != NULL){
    print_class_members(node->classMembers, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_class_body(ClassBody* node, int n){
  make_dist(n);
  printf("Class Body: {");
  if(node->classMembers != NULL){
    printf("\n");
    print_class_members(node->classMembers, n+1);
    make_dist(n);
  }
  printf("}\n");
}

void print_extension(Extension* node, int n){
  make_dist(n);
  printf("Extension: {");
  printf("Identifier %s", node->identifier->val);
  printf("}\n");
}

void print_class_declaration(ClassDeclaration* node, int n){
  make_dist(n);
  printf("Class Declaration: {\n");
  if(node->isPublic){
    make_dist(n+1);
    printf("Public\n");
  }

  print_compound_name(node->compoundName, n+1);
  if(node->extension != NULL){
    print_extension(node->extension, n+1);
  }
  print_class_body(node->classBody, n+1);
  make_dist(n);
  printf("}\n");
}

void print_class_declarations(ClassDeclarations* node, int n){
  make_dist(n);
  printf("Class Declarations: {\n");
  print_class_declaration(node->classDeclaration, n+1);
  if(node->classDeclarations != NULL){
     print_class_declarations(node->classDeclarations, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_import(Import* node, int n){
  make_dist(n);
  printf("Import: {");
  printf("Identifier %s",node->identifier->val);
  printf("}\n");
}

void print_imports(Imports* node, int n){
  make_dist(n);
  printf("Imports: {\n");
  print_import(node->anImport, n+1);
  if(node->imports != NULL){
     print_imports(node->imports, n+1);
  }
  make_dist(n);
  printf("}\n");
}

void print_compilation_unit(CompilationUnit* node, int n){  
  make_dist(n);
  printf("Compilation Unit: {");
  if(node->imports != NULL){
     printf("\n");
     print_imports(node->imports, n+1);
  }
  if(node->classDeclarations != NULL){
    printf("\n");
    print_class_declarations(node->classDeclarations, n+1);
  }
  make_dist(n);
  printf("}\n");
}
