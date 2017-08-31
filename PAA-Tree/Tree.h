#pragma once

class node
{
protected:
	int value_;
	node* left_;
	node* right_;

public:
	virtual ~node() = default;
	node() : value_(0), left_(nullptr), right_(nullptr) {}
	explicit node(int value) : value_(value), left_(nullptr), right_(nullptr) {}
	node(int value, node* left, node* right) : value_(value), left_(left), right_(right) {}
	node*& left() { return left_; }
	node*& right() { return right_; }
	int& value() { return value_; }
	virtual void add(int value);
};

class avl_node : node
{
public:
	avl_node() : node(), balance_(0) {}
	explicit avl_node(int value) : node(value), balance_(0) {}
	avl_node(int value, node* left, node* right) : node(value, left, right), balance_(0) {}
	avl_node(int value, node* left, node* right, int balance) : node(value, left, right), balance_(balance) {}

	int& balance() { return balance_; }
private:
	int balance_;
};

class arvore_binaria
{
private:
	node* root_;

public:
	virtual ~arvore_binaria() = default;
	arvore_binaria() : root_(nullptr) {}
	virtual void add(int value);
};