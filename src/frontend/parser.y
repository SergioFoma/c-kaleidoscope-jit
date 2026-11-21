%language "c++"

%define api.value.type variant    // include c++ type
%define api.value.automove        // automatic wrapper std::move()
%define api.token.constructor     //

%code requires {
  #include <ast.hpp>
  #include <iostream>
  #include <string>
}

%code provides {
  yy::parser::symbol_type yylex();
}

%parse-param { std::unique_ptr<ast::AstNode>& root };  // add field in constructor

%token EQ "=="
%token LT "<"
%token LTE "<="
%token GT ">"
%token GTE ">="
%token ASSIGNMENT "="
%token <int> NUM
%token <std::string> VAR
%token INPUT "input()"
%token PRINT "print"
%token ADD "+"
%token SUB "-"
%token MUL "*"
%token DIV "/"
%token IF "if"
%token WHILE "while"
%token OPEN_R_BRACKET "("
%token CLOSE_R_BRACKET ")"
%token OPEN_C_BRACKET "{"
%token CLOSE_C_BRACKET "}"

%nterm <std::unique_ptr<ast::BlockNode>> program
%nterm <std::unique_ptr<ast::ExprNode>> expr
%nterm <std::unique_ptr<ast::PrExprNode>> pr_expr
%nterm <std::unique_ptr<ast::StmtNode>> stmt
%nterm <std::unique_ptr<ast::BlockNode>> block
%nterm <std::unique_ptr<ast::ArithNode>> arith
%nterm <std::unique_ptr<ast::TermNode>> term
%nterm <std::unique_ptr<ast::AtomNode>> atom
%nterm <std::unique_ptr<ast::NumNode>> num
%nterm <std::unique_ptr<ast::VarNode>> var

%%

program:
  block { root = $1; }

block:
  %empty { $$ = nullptr; }
  | stmt block { $$ = std::make_unique<ast::BlockNode>($1, $2); }

expr:
  arith "==" arith { $$ = std::make_unique<ast::EqNode>($1, $3); }
  | arith "<" arith { $$ = std::make_unique<ast::LtNode>($1, $3); }
  | arith "<=" arith { $$ = std::make_unique<ast::LteNode>($1, $3); }
  | arith ">" arith { $$ = std::make_unique<ast::GtNode>($1, $3); }
  | arith ">=" arith { $$ = std::make_unique<ast::GteNode>($1, $3); }
  | arith { $$ = $1; }

stmt:
  "if" "(" expr ")" "{" block "}" { $$ = std::make_unique<ast::IfNode>($3, $6); }
  | "while" "(" expr ")" "{" block "}" { $$ = std::make_unique<ast::WhileNode>($3, $6); }
  | "print" "(" expr ")" { $$ = std::make_unique<ast::PrintNode>($3); }
  | var "=" expr { $$ = std::make_unique<ast::AssignmentNode>($1, $3); }

arith:
  arith "+" term { $$ = std::make_unique<ast::AddNode>($1, $3); }
  | arith "-" term { $$ = std::make_unique<ast::SubNode>($1, $3); }
  | term { $$ = $1; }

term:
  term "*" atom { $$ = std::make_unique<ast::MulNode>($1, $3); }
  | term "/" atom { $$ = std::make_unique<ast::DivNode>($1, $3); }
  | atom { $$ = $1; }

atom:
  pr_expr { $$ = $1; }
  | num { $$ = $1; }
  | var { $$ = $1; }
  | INPUT { $$ = std::make_unique<ast::InputNode>(); }

pr_expr:
  "(" expr ")" { $$ = std::make_unique<ast::PrExprNode>($2); }

num:
  NUM { $$ = std::make_unique<ast::NumNode>($1); }

var:
  VAR { $$ = std::make_unique<ast::VarNode>($1); }

%%

void yy::parser::error(const std::string& msg) {
  std::cout << "error: " << msg << '\n';
}




