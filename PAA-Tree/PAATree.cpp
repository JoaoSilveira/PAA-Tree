// PAATree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <iostream>


int main()
{
	avl_tree tree;

	tree.add(2);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(65);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(68);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(88);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(30);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(83);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(39);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(31);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(69);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(20);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(26);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(47);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(91);
	tree.print();
	std::cout << std::endl << std::endl;
	tree.add(80);
	tree.print();

    return 0;
}

