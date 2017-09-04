// PAATree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <iomanip>

using namespace std;

const string ordenations[] = { "a", "o", "p" };
const int sizes[] = { 100, 200, 500, 1000, 2000, 5000, 7500, 10000, 15000, 20000, 30000, 50000, 70000, 75000, 100000, 500000, 750000, 1000000, 1250000, 1500000, 2000000, 5000000, 7500000, 10000000 };

const int* read_file(const string& order, const int& size)
{
	ifstream file;

	file.open(order + to_string(size) + ".txt", ifstream::in);

	if (!file.is_open())
		throw exception(string("Error trying to open '" + order + to_string(size) + ".txt'").c_str());

	const auto arr = new int[size];

	for (auto i = 0; i < size; i++)
	{
		file >> arr[i];
	}

	file.close();

	return arr;
}

binary_tree* build_tree(binary_tree* tree, const int* arr, const string& prefix, const string& order, const int& size)
{
	auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm aux;
	localtime_s(&aux, &time);
	cout << "Started at " << put_time(&aux, "%F %T") << endl;

	const auto start = chrono::system_clock::now();

	for (auto i = 0; i < size; i++, arr++)
	{
		tree->add(*arr);
	}

	auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);

	ofstream file;

	file.open(prefix + order + to_string(size) + ".txt", ofstream::out | ofstream::trunc);

	if (!file.is_open())
		throw exception(string("Error trying to open 'bb" + order + to_string(size) + ".txt'").c_str());

	file << tree->comparisons() << endl << duration.count();

	tree->comparisons() = 0;

	file.close();

	return tree;
}

binary_tree* build_binary_tree(const int* arr, const string& order, const int& size)
{
	auto tree = new binary_tree();

	cout << order << " Binary Tree (" << size << ") Construction ";

	return build_tree(tree, arr, "bb", order, size);
}

binary_tree* build_avl_tree(const int* arr, const string& order, const int size)
{
	auto tree = new avl_tree();

	cout << order << " AVL Tree (" << size << ") Construction ";

	return build_tree(tree, arr, "ab", order, size);
}

void search_tree(binary_tree* tree, const int* arr, const string& prefix, const string& order, const int size)
{
	auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	tm aux;
	localtime_s(&aux, &time);
	cout << "Search Started at " << put_time(&aux, "%F %T") << endl;

	const auto start = chrono::system_clock::now();

	for (auto i = 0; i < size; i++, arr++)
	{
		tree->search(*arr);
	}

	auto duration = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start);

	ofstream file;

	file.open(prefix + order + to_string(size) + ".txt", ofstream::out | ofstream::trunc);

	if (!file.is_open())
		throw exception(string("Falha ao abrir o arquivo 'bb" + order + to_string(size) + ".txt'").c_str());

	file << tree->comparisons() << endl << duration.count();

	tree->comparisons() = 0;

	file.close();
}

int main(int argc, char** argv)
{
	auto i = 0;
	auto j = 0;

	if (argc == 3)
	{
		while (strcmp(argv[1], ordenations[i].c_str()) != 0 && i < 3)
			i++;

		const auto value = atoi(argv[2]);

		while (value != sizes[j] && j < 24)
			j++;

		if (i == 3 || j == 24)
			return 0;
	}

	if(!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS))
	{
		cout << "Failed to enter High Priority" << endl;
	}

	for (; i < 3; i++)
	{
		for (; j < 24; j++)
		{
			const auto search_array = read_file("b", sizes[j]);
			const auto tree_array = read_file(ordenations[i], sizes[j]);
			auto tree = build_binary_tree(tree_array, ordenations[i], sizes[j]);

			search_tree(tree, search_array, "bs", ordenations[i], sizes[j]);
			delete tree;

			tree = build_avl_tree(tree_array, ordenations[i], sizes[j]);
			search_tree(tree, search_array, "as", ordenations[i], sizes[j]);

			delete tree;
			delete[] search_array;
			delete[] tree_array;
		}
	}

	return 0;
}
