#pragma once
#include<string>

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
	virtual std::string to_string();
};

class avl_node : public node
{
	int balance_;
	avl_node* father_;

public:
	avl_node() : node(), balance_(0), father_(nullptr) {}
	explicit avl_node(int value) : node(value), balance_(0), father_(nullptr) {}
	avl_node(int value, avl_node* father) : node(value), balance_(0), father_(father) {}
	avl_node(int value, node* left, node* right) : node(value, left, right), balance_(0), father_(nullptr) {}
	avl_node(int value, node* left, node* right, int balance) : node(value, left, right), balance_(balance), father_(nullptr) {}

	int& balance() { return balance_; }
	std::string to_string() override;

	void change_child(node* new_child);

	static node* simple_left_rotation(avl_node* node1);
	static node* simple_right_rotation(avl_node* node1);
	static node* left_right_rotation(avl_node* node1);
	static node* right_left_rotation(avl_node* node1);
};

class binary_tree
{
protected:
	node* root_;
	virtual node* add(int value, node* father);

public:
	virtual ~binary_tree() = default;
	binary_tree() : root_(nullptr) {}
	virtual void add(int value);
	virtual void print();
};

class avl_tree : public binary_tree
{
	node* add(int value, node* node) override;
public:
	void add(int value) override;
};