#include "stdafx.h"
#include "Tree.h"

void node::add(int value)
{
	if (value < value_)
	{
		if (left_ != nullptr)
			left_->add(value);
		else
			left_ = new node(value);
	}
	else
	{
		if (right_ != nullptr)
			right_->add(value);
		else
			right_ = new node(value);
	}
}

void arvore_binaria::add(int value)
{
	if (root_ != nullptr)
		root_->add(value);
	else
		root_ = new node(value);
}

void avl_node::simple_right_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->left_);

	node1->left_ = node2->right_;
	node2->right_ = node1;
	node1->father_->change_child(node1, node2);
}

void avl_node::simple_left_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->right_);

	node1->right_ = node2->left_;
	node2->left_ = node1;
	node1->father_->change_child(node1, node2);
}

void avl_node::left_right_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->left_);
	const auto node3 = static_cast<avl_node*>(node2->right_);

	node2->right_ = node3->left_;
	node3->left_ = node2;
	node1->left_ = node3->right_;
	node3->right_ = node1;

	node1->change_child(node1, node3);
}

void avl_node::right_left_rotation(avl_node* node1)
{
	const auto node2 = static_cast<avl_node*>(node1->right_);
	const auto node3 = static_cast<avl_node*>(node2->left_);

	node2->left_ = node3->right_;
	node3->right_ = node2;
	node1->right_ = node3->left_;
	node3->left_ = node1;

	node1->change_child(node1, node3);
}


void avl_node::change_child(avl_node* old_child, avl_node* new_child)
{
	if (left_ == old_child)
		left_ = new_child;
	else
		right_ = new_child;
}
