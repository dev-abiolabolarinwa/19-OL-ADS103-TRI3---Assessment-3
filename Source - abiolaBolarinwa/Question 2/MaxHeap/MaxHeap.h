#pragma once

#include <iostream>
using namespace std;

class MaxHeap {
private:
	string file_filename;

	int size, max_size;	

	const int base_r = 0;

public:
	int* element_array;
	MaxHeap(int size_limit, string n_file);

	int get_maximum();
	int extract_max();

	int parent_node(int _integer);
	void printArray(int arr[], int n);
	
	void swap_values(int * x, int * y);
	void max_heapify(int index_element);
	void insert_new_element(int element);
	void remove_and_swap_element(int index_at, int value);
	void delete_element(int element_at);

	void string_print_to_file();

	~MaxHeap();
};