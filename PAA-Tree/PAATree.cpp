// PAATree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tree.h"
#include <iostream>
#include <sstream>


int main()
{
	avl_tree tree;

	std::stringstream stream;

	stream.str(" 61  88  86  51  82  76  35  11  32   7  17  48   5  12  55  93  74  33  34  38  99  98  26  39   4  13  91  23  24  56  36  18  60  15  85 100  30  79  43  73  16  62  96  42  37  41  89  63  20  72  71  10  21  54  78  87  84  31  46  77  81  65  47  28  67  92  83  22  80  70  95   6   2   9  25  58  69   3  97  53  66  14  45  52  64  40  27  50  57   8  59  29  49  94   1  19  90  68  44  75");

	while (!stream.eof())
	{
		int aux;

		stream >> aux;

		tree.add(aux);
	}

	tree.print();
    return 0;
}

