#include "parser.tab.h"
#include "lex.h"
#include "ast.h"
#include <stdio.h>
int
main(int argc, char **argv) 
{
  root_node *r = (root_node *) malloc(sizeof(root_node));
  r->src = fopen("test.txt", "r");
  yyscan_t sc;


	yylex_init(&sc);
	yyset_in(r->src, sc);
	int number = yyparse(sc, r);
	yylex_destroy(sc);
  
  print_compilation_unit(r->root, 0);
	fclose(r->src);
	return 0;
}
