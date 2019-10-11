%{
#include "parser.tab.h"
%}

%option reentrant bison-bridge noyywrap

%%

[ \t]+   ;
[\n]+      ;

"("        return LPAREN;
")"        return RPAREN;
"import"   return IMPORT;
"class"    return CLASS;
"public"   return PUBLIC;
"private"  return PRIVATE;
"static"   return STATIC;
"void"     return VOID;
"if"       return IF;
"else"     return ELSE;
"while"    return WHILE;
"loop"     return LOOP;
"return"   return RETURN;
"print"    return PRINT;
"null"     return NULLVAL;
"new"      return NEW;
((([0-9]+)((e|E)(\+|-)?[0-9]+))|(([0-9]*\.[0-9]+)|([0-9]+\.))((e|E)(\+|-)?[0-9]+)?)(f|F|l|L)? return REAL;

"{"        return LBRACE;
"}"        return RBRACE;
"["        return LBRACKET;
"]"        return RBRACKET;
","        return COMMA;
"."        return DOT;
";"        return SEMICOLON;


"=="  return EQUAL;
"<"   return LESS;
">"   return GREATER;
"="   return ASSIGN;
"!="  return NOT_EQUAL;
"+"   return PLUS;
"-"   return MINUS;
"*"   return MULTIPLY;
"/"   return DIVIDE;

[0-9]+      { yylval->INT = atol(yytext); return INT; }

[a-zA-Z][a-zA-Z_0-9]*       { yylval->IDENTIFIER = yytext; return IDENTIFIER; }

<<EOF>>    return TOK_EOF;
