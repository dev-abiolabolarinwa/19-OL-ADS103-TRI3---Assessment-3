#pragma once

#include <iostream>
using namespace std;

class MaxHeap {
private:
	string file_filename;

	int size, max_size;	
	int * element_array;
	
	const int base_r = 0;

public:
	MaxHeap();
	MaxHeap(int size_limit, string n_file);

	int get_maximum();
	int extract_root();

	int parent_node(int _integer);
	int right_child_node(int _integer);
	int left_child_node(int _integer);
	
	void swap(int * x, int * y);
	void max_heapify(int index_element);
	void insert_new_element(int element);
	void remove_and_swap_element(int index_at, int value);
	void delete_element(int element_at);

	void stringtoPrint();
	void stringtoString();

	~MaxHeap();
};