#include "pch.h"
#include "MaxHeap.h"
#include <fstream>
#include <iostream>

using namespace std;

MaxHeap::MaxHeap(int size_limit, string n_file) {
	this->file_filename = n_file;
	this->size = 0;
	this->max_size = size_limit;
	this->element_array = new int[this->max_size];
	
}

// Finds and then returns the maximum value.
int MaxHeap::get_maximum() {
	return element_array[0];

}

// Extracting and removes the root node.
int MaxHeap::extract_max() {
	if (this->size <= this->base_r) {
		return INT_MIN;
	}

	if (this->size == 1) {
		this->size--;
		return this->element_array[0];
	}

	int base_root = this->element_array[this->base_r];
	this->element_array[this->base_r] = this->element_array[this->size - 1];
	this->size--;

	max_heapify(this->base_r);

	return base_root;
}

// Calculates and then returns the index of the parent node.
int MaxHeap::parent_node(int _integer) {
	return (_integer - 1) / 2;

}

// Calculates and then returns the index of the right child.
int MaxHeap::right_child_node(int _integer) {
	return ((2 * _integer) + 2);

}

// Calculates and then returns the index of the left child.
int MaxHeap::left_child_node(int _integer) {
	return ((2 * _integer) + 1);

}

void MaxHeap::printArray(int arr[], int n) {
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

// Function gets two values and swaps both values,
// by changing the values at specified memory.
void MaxHeap::swap_values(int * x, int * y) {
	int stored_temp = *y;
	*y = *x;
	*x = stored_temp;
}

// Function Calls the max_heap to sort the heap amd loops
// through the elements list to sort.
void MaxHeap::sort_elements_heap(int heap_array[]) {
	int size = this->max_size;
	for (int i = 0; i < size; i++) {
		element_array[i] = heap_array[i];
	}
	
	for (int i = size / 2 - 1; i >= 0; i--) {
		max_heapify(i);
	}

	for (int i = size - 1; i >= 0; i--) {
		swap_values(&element_array[0], &element_array[i]);
		max_heapify(i);
	}
}

// Function will recursively call rearrange the heap
// using a both left and right child properties, form
// the specified element node index.
void MaxHeap::max_heapify(int element_at) {
	int max_value = element_at;
	
	int right_branch = right_child_node(element_at);
	int left_branch = left_child_node(element_at);

	if (left_branch < this->max_size && element_array[left_branch] > element_array[max_value]) {
		max_value = left_branch;
	}

	if (right_branch < this->max_size && element_array[right_branch] > element_array[max_value]) {
		max_value = right_branch;
	}

	if (max_value != element_at) {
		swap_values(&element_array[element_at], &element_array[max_value]);
		max_heapify(max_value);
	}
}

// Function inserts a element into a new node. Function will
// then repeatedly order the nodes, via the use a while loop,
// somewhat functioning like a recursive function.
void MaxHeap::insert_new_element(int element) {
	if (this->size == this->max_size) {
		cout << "[ System ] [ Error ][ Heap Overflow! ]" << endl;
		return;
	}

	int position;

	this->size++;
	position = this->size - 1;

	element_array[position] = element;


	stringtoPrint();
	stringtoString();
	while (this->element_array[parent_node(position)] < this->element_array[position] && position != 0) {
		swap_values(&this->element_array[parent_node(position)], & this->element_array[position]);
		position = parent_node(position);
	}
	stringtoString();
}

// Parses throught the elements and removes the element at a
// certain index, which will then be swapped with the value that
// has been passed through.
void MaxHeap::remove_and_swap_element(int index_at, int value) {
	this->element_array[index_at] = value;
	while (this->element_array[parent_node(index_at)] < this->element_array[index_at] && index_at != 0) {
		swap_values(&this->element_array[index_at], &this->element_array[parent_node(index_at)]);
		index_at = parent_node(index_at);
	}
}

// Deletes a node(leaf) at a certain index.
void MaxHeap::delete_element(int index) {
	remove_and_swap_element(index, INT_MAX);
	extract_max();
}

// Prints to the variables in order(Breadth-first-search) to a
// file.
void MaxHeap::stringtoPrint() {
	ofstream of;

	of.open("output_" + this->file_filename, ofstream::out | ofstream::app);

	for (int i = 0; i < this->size; i++) {
		of << this->element_array[i] << " ";
	}

	of << endl;
	of.close();
}

// Prints the variables in order to the screen.
void MaxHeap::stringtoString() {
	for (int i = 0; i < this->size; ++i) {
		cout << this->element_array[i] << " ";
	}
	cout << endl;
}



// Desctructor.
MaxHeap::~MaxHeap() { }