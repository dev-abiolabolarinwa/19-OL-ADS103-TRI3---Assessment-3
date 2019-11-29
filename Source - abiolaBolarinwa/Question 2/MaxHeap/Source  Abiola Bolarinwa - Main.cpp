/*
* Name: Max Heaps
* Purpose: Exploring the creation of max Heaps.
*
* @author Abiola Bolarinwa
* @version 1.1 26/11/19
* @Github https://github.com/dev-abiolabolarinwa/19-OL-ADS103-TRI3---Assessment-3/tree/master/Source%20-%20abiolaBolarinwa/Question%202
*/

#include "pch.h"
#include "MaxHeap.h"

#include <string>
#include <climits>
#include <fstream>
#include <iostream>
#include <iostream>

using namespace std;

string stored_filename;

// Determines the number of elements to be in the array by
// converting the string into an integer.
int convert_size(string const file[]) {
	return atoi(file[0].c_str());
}

// Loads a new file to be sorted.
void load_new_file () {
	string stored_filename;

	std::cout << "Enter the name of the Heap File: ";
	getline(std::cin, stored_filename);

	::stored_filename = stored_filename;
}

// Function takes in two values, first being the string of elements
// that is to be converted into a numerical value and then placed into
// an array. The second being the size of the heap.
int * heap_elements_array(string elements_array, int heap_size) {
	int element_size = heap_size;
	int * elements;

	while (!elements_array.empty()) {
		elements = new int[heap_size];

		for (int i = 0; i < heap_size; i++) {
			int temp_wspace = elements_array.find(" ");
			string temp_single_element = elements_array.substr(0, temp_wspace);

			elements[i] = atol(temp_single_element.c_str());
			elements_array.erase(0, temp_wspace + 1);

		}
		return elements;

	}
	return nullptr;
}

int main()
{
	ifstream ifs;
	ofstream ofs;
	
	int heap_length;	
	int* heap_elements;

	string file_filereader[2];
	string file_heap_elements;

	bool choice_checker = true;
	bool terminate_program = false;

	do {
		if (choice_checker) {
			choice_checker = false;
			load_new_file();			
		}

		if (!ifs.is_open()) {
			ifs.open(::stored_filename);
		}

		if (ifs.is_open()) {

			ifs >> file_filereader[0];
			heap_length = convert_size(file_filereader);

			MaxHeap heap = MaxHeap(heap_length, ::stored_filename);

			while (getline(ifs, file_heap_elements)) {
				string temp_element = file_heap_elements;
				file_heap_elements = temp_element;
			}

			if (file_filereader[1].empty()) {
				terminate_program = true;
			}

			if (choice_checker) {
				heap.~MaxHeap();
				ifs.close();

			}

			file_filereader[1] = file_heap_elements;
			heap_elements = new int[heap_length];
			heap_elements = heap_elements_array(file_filereader[1], heap_length);


			for (int i = 0; i < heap_length; i++) {
				heap.insert_new_element(heap_elements[i]);
			}


			system("CLS");
			std::cout << "[ System Message ] [ Success ]" << "[ File has been save! ]" << endl;
			//system("pause");
			system("exit");

		} else {
			std::cout << "[ System Message ]" << "[ Could not locate the file -> ]" << stored_filename << endl;
			choice_checker = true;
			system("CLS");
		}

		
	} while (!terminate_program);

	return 0;
}