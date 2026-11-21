#pragma once

#include <memory>
#include <string>

namespace ast {
/**
 * Basic class for AST node;
*/
class AstNode {
 public:
  virtual ~AstNode() = default;
};

/**
 * Basic class for expression AST node: eq, lt, lte, gt, gte, arith
*/
class ExprNode: public AstNode {};

/**
 * Basic class for statement AST node: if, while, assignment, print
*/
class StmtNode: public AstNode {};

/**
 * Basic class for arithmetic AST node: sum, sub, term
*/
class ArithNode: public ExprNode {};

/**
 * Basic class for term AST node: mul, div, atom
*/
class TermNode: public ArithNode {};

/**
 * Basic class for atom AST node: primary_expr, input, number , var
*/
class AtomNode: public TermNode {};

/*
 * Class for blocks: {}
 * When BlockNode have only stmt, right is nullptr
*/
class BlockNode: public AstNode {
 public:
  BlockNode(std::unique_ptr<StmtNode> left, std::unique_ptr<BlockNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<StmtNode> left_;
  std::unique_ptr<BlockNode> right_;
};

// ================================ Expressions ===============================

class EqNode: public ExprNode {
 public:
  EqNode(std::unique_ptr<ArithNode> left, std::unique_ptr<ArithNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<ArithNode> right_;
};

class LtNode: public ExprNode {
 public:
  LtNode(std::unique_ptr<ArithNode> left, std::unique_ptr<ArithNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<ArithNode> right_;
};

class LteNode: public ExprNode {
 public:
  LteNode(std::unique_ptr<ArithNode> left, std::unique_ptr<ArithNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<ArithNode> right_;
};

class GtNode: public ExprNode {
 public:
  GtNode(std::unique_ptr<ArithNode> left, std::unique_ptr<ArithNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<ArithNode> right_;
};

class GteNode: public ExprNode {
 public:
  GteNode(std::unique_ptr<ArithNode> left, std::unique_ptr<ArithNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<ArithNode> right_;
};

// ================================ Atoms =====================================


class PrExprNode: public AtomNode {
 public:
  PrExprNode(std::unique_ptr<ExprNode> expr)
    : expr_(std::move(expr)) {}

 private:
  std::unique_ptr<ExprNode> expr_;
};

class NumNode: public AtomNode {
 public:
  NumNode(int val): val_(val) {}

 private:
  int val_;
};

class VarNode: public AtomNode {
 public:
  VarNode(std::string name): name_(std::move(name)) {}

 private:
  std::string name_;
};

class InputNode: public AtomNode {};

// ================================ Arithmetics ===============================

class AddNode: public ArithNode {
 public:
  AddNode(std::unique_ptr<ArithNode> left, std::unique_ptr<TermNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<TermNode> right_;
};

class SubNode: public ArithNode {
 public:
  SubNode(std::unique_ptr<ArithNode> left, std::unique_ptr<TermNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ArithNode> left_;
  std::unique_ptr<TermNode> right_;
};

// ================================ Terms =====================================

class MulNode: public TermNode {
 public:
  MulNode(std::unique_ptr<TermNode> left, std::unique_ptr<AtomNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<TermNode> left_;
  std::unique_ptr<AtomNode> right_;
};

class DivNode: public TermNode {
 public:
  DivNode(std::unique_ptr<TermNode> left, std::unique_ptr<AtomNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<TermNode> left_;
  std::unique_ptr<AtomNode> right_;
};

// ================================ Statements ================================

class IfNode: public StmtNode {
 public:
  IfNode(std::unique_ptr<ExprNode> left, std::unique_ptr<BlockNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ExprNode> left_;
  std::unique_ptr<BlockNode> right_;
};

class WhileNode: public StmtNode {
 public:
  WhileNode(std::unique_ptr<ExprNode> left, std::unique_ptr<BlockNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<ExprNode> left_;
  std::unique_ptr<BlockNode> right_;
};

class PrintNode: public StmtNode {
 public:
  PrintNode(std::unique_ptr<ExprNode> arg):
    arg_(std::move(arg)) {}

 private:
  std::unique_ptr<ExprNode> arg_;
};

class AssignmentNode: public StmtNode {
 public:
  AssignmentNode(std::unique_ptr<VarNode> left, std::unique_ptr<ExprNode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

 private:
  std::unique_ptr<VarNode> left_;
  std::unique_ptr<ExprNode> right_;
};
} // namespace ast
