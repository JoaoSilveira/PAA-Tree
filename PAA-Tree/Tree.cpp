#include "stdafx.h"
#include "Tree.h"
#include <sstream>
#include <iostream>
#include <functional>
#include <stack>

binary_tree::~binary_tree()
{
	if (root_ == nullptr)
		return;

	std::stack<node*> nodes;

	nodes.push(root_);

	while (!nodes.empty())
	{
		auto top = nodes.top();

		if (top->left() != nullptr)
		{
			nodes.push(top->left());
			top->left() = nullptr;
			continue;
		}

		if (top->right() != nullptr)
		{
			nodes.push(top->right());
			top->right() = nullptr;
			continue;
		}

		delete top;
		nodes.pop();
	}
}

node* binary_tree::add(int value, node* father)
{
	return nullptr;
}


void binary_tree::add(int value)
{
	if (root_ == nullptr)
	{
		root_ = new node(value);
		return;
	}

	auto node = root_;

	while (true)
	{
		if (value < node->value())
		{
			if (node->left() != nullptr)
			{
				node = node->left();
				++comparisons_;

				continue;
			}

			node->left() = new ::node(value);
			break;
		}

		if (node->right() != nullptr)
		{
			node = node->right();
			++comparisons_;

			continue;
		}

		node->right() = new ::node(value);
		break;
	}
}

void binary_tree::print()
{
	std::function<void(node*, std::string)> func = [&func](node* node, std::string tabs)
	{
		if (node == nullptr)
			return;

		std::cout << tabs << node->to_string() << std::endl;
		func(node->left(), tabs + "  ");
		func(node->right(), tabs + "  ");
	};

	func(root_, "");
}

bool binary_tree::search(int value)
{
	auto node = root_;

	while (node != nullptr && node->value() != value)
	{
		if (value < node->value())
			node = node->left();
		else
			node = node->right();

		++comparisons_;
	}
	++comparisons_;

	return node != nullptr;
}


void avl_tree::add(int value)
{
	if (root_ == nullptr)
	{
		root_ = new avl_node(value);
		return;
	}

	const auto new_root = add(value, root_);

	if (new_root != nullptr)
		root_ = new_root;
}

node* avl_tree::add(int value, node* node)
{
	static int balancing;
	avl_node* new_child;
	auto father = static_cast<avl_node*>(node);

	if (value < father->value())
	{
		if (father->left() != nullptr)
		{
			new_child = static_cast<avl_node*>(add(value, father->left()));
			++comparisons_;
		}
		else
		{
			father->left() = new avl_node(value);

			father->balance() -= 1;
			balancing = father->balance();

			return nullptr;
		}
	}
	else
	{
		if (father->right() != nullptr)
		{
			new_child = static_cast<avl_node*>(add(value, father->right()));
			++comparisons_;
		}
		else
		{
			father->right() = new avl_node(value);

			father->balance() += 1;
			balancing = father->balance();

			return nullptr;
		}
	}

	if (new_child != nullptr)
	{
		father->change_child(new_child);
		return nullptr;
	}

	if (balancing == 0)
		return nullptr;

	balancing = value < father->value() ? -1 : 1;
	father->balance() += balancing;

	if (father->balance() == 0)
	{
		balancing = 0;
		return nullptr;
	}

	if (father->balance() == 1 || father->balance() == -1)
		return nullptr;

	balancing = 0;

	if (father->balance() == -2 && static_cast<avl_node*>(father->left())->balance() == -1)
		return avl_node::simple_right_rotation(father);

	if (father->balance() == -2 && static_cast<avl_node*>(father->left())->balance() == 1)
		return avl_node::left_right_rotation(father);

	if (father->balance() == 2 && static_cast<avl_node*>(father->right())->balance() == 1)
		return avl_node::simple_left_rotation(father);

	if (father->balance() == 2 && static_cast<avl_node*>(father->right())->balance() == -1)
		return avl_node::right_left_rotation(father);

	throw std::exception("Something went wrong");
}

void avl_tree::print_balance(avl_node* node) const
{
	if (node == nullptr)
		return;

	print_balance(static_cast<avl_node*>(node->left()));
	std::cout << node->balance() << " ";
	print_balance(static_cast<avl_node*>(node->right()));
}


std::string node::to_string()
{
	std::stringstream stream;

	stream << '<' << value() << '>';

	return stream.str();
}

std::string avl_node::to_string()
{
	std::stringstream stream;

	stream << '<' << value() << " [" << balance() << ']' << '>';

	return stream.str();
}

node* avl_node::simple_right_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->left_);

	node1->left_ = node2->right_;
	node2->right_ = node1;

	node1->balance_ = 0;
	node2->balance_ = 0;

	return node2;
}

node* avl_node::simple_left_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->right_);

	node1->right_ = node2->left_;
	node2->left_ = node1;

	node1->balance_ = 0;
	node2->balance_ = 0;

	return node2;
}

node* avl_node::left_right_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->left_);
	const auto node3 = static_cast<avl_node*>(node2->right_);

	node2->right_ = node3->left_;
	node3->left_ = node2;
	node1->left_ = node3->right_;
	node3->right_ = node1;

	node1->balance_ = node3->balance_ == -1 ? 1 : 0;
	node2->balance_ = node3->balance_ == 1 ? -1 : 0;
	node3->balance_ = 0;

	return node3;
}

node* avl_node::right_left_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->right_);
	const auto node3 = static_cast<avl_node*>(node2->left_);

	node2->left_ = node3->right_;
	node3->right_ = node2;
	node1->right_ = node3->left_;
	node3->left_ = node1;

	node1->balance_ = node3->balance_ == 1 ? -1 : 0;
	node2->balance_ = node3->balance_ == -1 ? 1 : 0;
	node3->balance_ = 0;

	return node3;
}

void avl_node::change_child(node* new_child)
{
	if (new_child->value() < value_)
		left_ = new_child;
	else
		right_ = new_child;
}