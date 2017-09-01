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

class avl_node : protected node
{
	int balance_;
	avl_node* father_;

	static void simple_left_rotation(avl_node* node1);
	static void simple_right_rotation(avl_node* node1);
	static void left_right_rotation(avl_node* node1);
	static void right_left_rotation(avl_node* node1);

	void change_child(avl_node* old_, avl_node* new_);

public:
	avl_node() : node(), balance_(0), father_(nullptr) {}
	explicit avl_node(int value) : node(value), balance_(0), father_(nullptr) {}
	avl_node(int value, avl_node* father) : node(value), balance_(0), father_(father) {}
	avl_node(int value, node* left, node* right) : node(value, left, right), balance_(0), father_(nullptr) {}
	avl_node(int value, node* left, node* right, int balance) : node(value, left, right), balance_(balance), father_(nullptr) {}

	int& balance() { return balance_; }
};

class arvore_binaria
{
	node* root_;

public:
	virtual ~arvore_binaria() = default;
	arvore_binaria() : root_(nullptr) {}
	virtual void add(int value);
};