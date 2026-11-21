%{
#include "parser.tab.hh"
#include <string>

#define YY_DECL yy::parser::symbol_type yylex()
%}

%option yylineno
%option noyywrap


%%

"==" return yy::parser::make_EQ();
"<" return yy::parser::make_LT();
"<=" return yy::parser::make_LTE();
">" return yy::parser::make_GT();
">=" return yy::parser::make_GTE();
"=" return yy::parser::make_ASSIGNMENT();
"input()" return yy::parser::make_INPUT();
"print" return yy::parser::make_PRINT();
"+" return yy::parser::make_ADD();
"-" return yy::parser::make_SUB();
"*" return yy::parser::make_MUL();
"/" return yy::parser::make_DIV();
"if" return yy::parser::make_IF();
"while" return yy::parser::make_WHILE();
"(" return yy::parser::make_OPEN_R_BRACKET();
")" return yy::parser::make_CLOSE_R_BRACKET();
"{" return yy::parser::make_OPEN_C_BRACKET();
"}" return yy::parser::make_CLOSE_C_BRACKET();

[0-9]+ return yy::parser::make_NUM(std::stoi(yytext));
[A-Za-z][A-Za-z0-9]* return yy::parser::make_VAR(std::string(yytext));

[ \t\n\r]+ {
  /* skip whitespaces */
}

/*
. {

  }
*/

%%


