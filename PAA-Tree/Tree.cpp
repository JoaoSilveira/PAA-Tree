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
