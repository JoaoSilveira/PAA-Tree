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

public:
	avl_node() : node(), balance_(0) {}
	explicit avl_node(int value) : node(value), balance_(0) {}
	avl_node(int value, node* left, node* right) : node(value, left, right), balance_(0) {}
	avl_node(int value, node* left, node* right, int balance) : node(value, left, right), balance_(balance) {}

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
	virtual bool search(int value);
};

class avl_tree : public binary_tree
{
	node* add(int value, node* node) override;
	void print_balance(avl_node* node) const;
public:
	void add(int value) override;
	void print_balance() const { print_balance(static_cast<avl_node*>(root_)); }
};