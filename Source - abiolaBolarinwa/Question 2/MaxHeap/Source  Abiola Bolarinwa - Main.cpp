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

// Determines the number of elements to be in the array by
// converting the string into an integer.
int convert_size(string const file[]) {
	return atoi(file[0].c_str());
}

// Function will display menu options to the screen,
// will also get return users input.
int main_menu() {
	int get_input;

	std::cout << endl << "Please select one of the following" << endl << endl;
	std::cout << "1. Delete from index" << endl;
	std::cout << "2. Close current file" << endl;
	std::cout << "Please select from one of the choices (1 or 2): ";
	std::cin >> get_input;

	if (get_input == 1 || get_input == 2) {
		return get_input;
	}

	while (!cin) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "[ System Message ][ Incorrect entry! ] \n" << endl << endl;
		std::cout << "1. Delete from index" << endl;
		std::cout << "2. Close current file" << endl << endl;
		std::cout << "Please enter one of the following: ";
		std::cin >> get_input;

	}
	std::cout << endl;

	return get_input;
}

// Function gets value given from main_menu() then uses a switch loop
// to determine next actions.
// Case 1 - A recursive case that deletes element from a the heap;
// Case 2 - Asks user whether they want to quit and checks that the user
//			is sure, if sure will proceed to terminate the program.
// Defualt Case - recursively calls the menu_action() function.
bool menu_action(MaxHeap max_heap, string file_filename, int user_input, bool quit_checker) {
	int input_value;
	switch (user_input) {
		case 1:
			std::cout << "Please enter the index at which you want to remove: ";
			std::cin >> input_value;
			std::cout << endl;
			max_heap.delete_element(input_value);
			max_heap.stringtoString();
			main_menu();
			return menu_action(max_heap, file_filename, user_input, quit_checker);
		case 2:
			char yes_or_no;

			cout << "[ System Message ][ Would you like to quit or continue? (y / n) ] :";
			cin >> yes_or_no;

			while (yes_or_no != 'y' || yes_or_no != 'n' && !cin) {
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "[ System Message ][ User Failed to entered correct value! ] \n" << endl;
				std::cout << "Please re-enter a char value, Y or N || Y or n: ";
				std::cin >> yes_or_no;
			}

			if (yes_or_no == 'y' || yes_or_no == 'Y') {
				quit_checker = true;
			} else if (yes_or_no == 'N' || yes_or_no == 'n') {
				quit_checker = false;
			}

			return quit_checker;
		default:
			return menu_action(max_heap, file_filename, user_input, quit_checker);
	}

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

	int* heap_elements;

	int user_input;
	int heap_length;	

	string stored_filename;
	string file_filereader[2];
	string file_heap_elements;

	bool choice_checker = true;
	bool terminate_program = false;

	do {
		if (choice_checker) {
			choice_checker = false;

			std::cout << "Enter the name of the Heap File: ";
			getline(std::cin, stored_filename);
		}

		if (!ifs.is_open()) {
			ifs.open(stored_filename);
		}

		if (ifs.is_open()) {

			ifs >> file_filereader[0];
			heap_length = convert_size(file_filereader);

			MaxHeap heap = MaxHeap(heap_length, stored_filename);

			while (getline(ifs, file_heap_elements)) {
				string temp_element = file_heap_elements;
				file_heap_elements = temp_element;
			}

			if (file_filereader[1].empty()) {
				terminate_program = true;
			}

			if (choice_checker == true) {
				heap.~MaxHeap();
				ifs.close();

			}

			file_filereader[1] = file_heap_elements;
			heap_elements = new int[heap_length];
			heap_elements = heap_elements_array(file_filereader[1], heap_length);


			for (int i = 0; i < heap_length; i++) {
				heap.insert_new_element(heap_elements[i]);
			}

			std::cout << endl;
			std::cout << endl;

			heap.printArray(heap.element_array, heap_length);

			std::cout << endl;
			std::cout << endl;

			for (int i = 0; i < heap_length; i++) {
				std::cout << heap.extract_max() << " ";
			}
			

			user_input = main_menu();
			choice_checker = menu_action(heap, stored_filename, user_input, choice_checker);


			if (choice_checker) {
				heap.~MaxHeap();
				ifs.close();
			}

			std::cout << endl << endl << endl;
		} else {
			std::cout << "[ System Message ]" << "[ Could not locate the file -> ]" << stored_filename << endl;
			choice_checker = true;
			system("CLS");
		}
		std::cin.clear();
		std::cin.ignore(100, '\n');

	} while (!terminate_program);

	return 0;
}