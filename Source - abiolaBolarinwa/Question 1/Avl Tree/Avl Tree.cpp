// Avl Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
* Name: Avl Trees
* Purpose: Exploring the creation of Avl trees
*
* @author Abiola Bolarinwa
* @version 1.1 24/11/19
* @github https://github.com/dev-abiolabolarinwa/19-OL-ADS103-TRI3---Assessment-3/tree/master/Source%20-%20abiolaBolarinwa/AbiolaBolarinwa
*/

// All necessary lib includes.
#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Global Variables.
int * elements;
int count = 0;
int counter = 0;

// Class of type node.
class Node {
	public:
		int value;
		Node* left;
		Node* right;
		int height;
};

// Calculates which of the two numbers is of Larger values,
// then returns larger value the via the ternary operator.
int max(int valueA, int valueB) {
	return (valueA > valueB) ? valueA : valueB;
}

// Checks for the current depth(height) of the trees, then
// returns the current height.
int get_height(Node* node) {
	if (NULL == node) { return 0; }

	return node->height;
};

// Creates a new node (creates a new AVL Tree) in the tree
// if the tree empty.
Node* new_node(int nValue) {
	Node* node = new Node();
	node->value = nValue;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
};

// Will rotate the left-hand side of the tree,
// with the pivot point being the x_value.
Node* l_rotate(Node* xValue) {
	if (xValue == NULL) { return xValue; }

	Node* yValue = xValue->right;
	if (yValue == NULL) { return xValue; }

	Node* T2 = yValue->left;

	// Sets the x-value to the y-value to perform the rotation.
	yValue->left = xValue;
	xValue->right = T2;

	// Finds the height of the left and right tree then updates both heights.
	xValue->height = max(get_height(xValue->left), get_height(xValue->right)) + 1;
	yValue->height = max(get_height(yValue->left), get_height(yValue->right)) + 1;

	return yValue;
};

// Will rotate the right-hand side of the tree,
// with the pivot point being the y_value.
Node* r_rotate(Node* yValue) {
	if (yValue == NULL) { return yValue; }

	Node* xValue = yValue->left;
	if (xValue == NULL) { return yValue; }

	Node* T2 = xValue->right;

	// Sets the x-value to the y-value to perform the rotation.
	xValue->right = yValue;
	yValue->left = T2;

	// Finds the height of the left and right tree then updates both heights.
	yValue->height = max(get_height(yValue->left), get_height(yValue->right)) + 1;
	xValue->height = max(get_height(xValue->left), get_height(xValue->right)) + 1;

	return xValue;
};

// Calculates and returns the balance factor of the tree.
int find_balance_factor(Node* node) {
	if (NULL == node) { return 0; }

	return get_height(node->left) - get_height(node->right);
};

// A Function that will recursively insert a value into the tree.
Node* insert(Node* node, int value) {
	// Checks if the tree is null, if it is null it will create a
	// new node.
	if (node == NULL) {
		return(new_node(value));
	}

	// Will start with a Binary Search Tree insertion.
	if (value < node->value) {
		node->left = insert(node->left, value);
	} else if (value > node->value) {
		node->right = insert(node->right, value);
	} else {
		return node;
	}

	// Will update the current height to a new height.
	node->height = 1 + max(get_height(node->left), get_height(node->right));

	// Calls the find_balance_factor function to get the current balance.
	int balance = find_balance_factor(node);

	// Checks whether the tree has become unbalance, then rotates the tree
	// left or right using the four statements stated below.
	if (balance > 1 && value < node->left->value) {
		return r_rotate(node);
	}

	if (balance < -1 && value > node->right->value) {
		return l_rotate(node);
	}

	if (balance > 1 && value > node->left->value) {
		node->left = l_rotate(node->left);

		return r_rotate(node);
	}

	if (balance < -1 && value < node->right->value) {
		node->right = r_rotate(node->right);

		return l_rotate(node);
	}

	return node;
};

// Prints out the tree into the file that is then saved
int * pre_order(Node* root) {
	if (root != NULL) {
		
		if (::count < ::counter) {
			::elements[::count] = root->value;
			::count++;
		}
		pre_order(root->left);
		pre_order(root->right);
	}
	return elements;	
};


int get_array_size(string const arraysize[]);
int get_depth_number(int tree_length);
int get_largest_number_position(int base_node, int check_elements);
int* convert_into_element_array(string elements_array, int elements_size);

int main()
{
	ifstream ifs;
	ofstream ofs;

	string file_filename;
	string file_read_lines[2];
	string file_g_elements;

	Node* root = NULL;

	int elements_length;
	int* elements_tree_values;
	int* preordered_elements;

	

	do {
		// Asks the user to enter the file name, and catches the input
		// and stores it into the filename variable.
		std::cout << "Please enter the name of the file: ";
		getline(cin, file_filename);

		// Uses the the ifstream variable to open the file with the exact name
		// as indicated by the user.
		ifs.open(file_filename);

		if (!ifs.is_open()) {
			system("CLS");
			std::cout << "[  SYSTEM  ][ No such file with name: " << file_filename << " ]" << std::endl << std::endl;
		}

	} while (!ifs.is_open());

	// Checks if the file is opened.
	if (ifs.is_open()) {
		// Makes sure that the code to be runned is being runned
		// whilst the file is open.
		while (ifs.is_open()) {
			// Gets the first line of the document, then calls the 
			// function get_size() to transform the string variable
			// into a integer.
			ifs >> file_read_lines[0];
			elements_length = get_array_size(file_read_lines);
			::counter = elements_length;
			::elements = new int[::counter];

			int depth = get_depth_number(elements_length);
			int max_depth = 6;


			// Will parse through the second line of the document and
			// add the numbers to the the g_elements array.
			while (getline(ifs, file_g_elements)) {
				string temp_element = file_g_elements;
				file_g_elements = temp_element;
			}

			file_read_lines[1] = file_g_elements;
			elements_tree_values = convert_into_element_array(file_read_lines[1], elements_length);

			// Inserts the tree values that were read from the file into
			// the tree.
			for (int i = 0; i < elements_length; i++) {
				root = insert(root, elements_tree_values[i]);
			}

			// Calls the a function that orders the tree.
			preordered_elements = pre_order(root);

			int largest_number;
			int position_largest_number;
			
			// For loop parses through all the elements in the array and
			// to find the largest number that is closest to the first element.
			for (int i = 2; i < elements_length; i++) {
				largest_number = get_largest_number_position(::elements[0], ::elements[i]);

				if (largest_number > elements[0]) {
					position_largest_number = i;
					break;
				}
			}

			// Variables used in parsing of the array elements.
			bool right_done = false;
			int elements_count = 0;
			int print_count = 1;

			// Creates a new output file and opens the file for writing.
			ofs.open("output." + file_filename);

			// Logic that prints the Avl Tree.
			for (int i = 0; i <= depth; i++) {
				if (i == 0) {
					ofs << i << ": " << ::elements[i];
					elements_count++;
				}
				else {
					ofs << i << ": ";
					for (int k = 0; k < (i * 2); k++) {
						if (i == 1) {
							ofs << ::elements[i] << " " << ::elements[position_largest_number];
							elements_count++;
							if (elements_count == (elements_length - 1)) {
								break;
							}
							break;
						}
						else if (right_done) {
							for (int j = 1; j <= i; j++) {
								ofs << ::elements[position_largest_number + j] << " ";
								elements_count++;
								if (elements_count == (elements_length - 1)) {
									break;
								}
							}
							right_done = false;
							break;
						}
						else {
							if (::elements[1 + print_count] == ::elements[position_largest_number]) {
								break;
							}
							if (elements_count == (elements_length - 1)) {
								break;
							}
							ofs << ::elements[1 + print_count] << " ";
							elements_count++;
							print_count++;
							if (print_count != (i * 2)) {
								if (print_count == (i * 2) / 2) {
									for (int j = 1; j < i; j++) {
										ofs << ::elements[j + print_count] << " ";
										print_count++;
										elements_count++;
										if (elements_count == (elements_length - 1)) {
											break;
										}
									}
									right_done = true;
								}
							}
						}
					}
				}
				ofs << std::endl;
			}
			ofs.close();

			system("CLS");
			std::cout << std::endl << "[  SYSTEM  ][ Operation Successfully completed! ]" << std::endl;
			std::cout << std::endl << "[  SYSTEM  ][ Output File: output." << file_filename << "! ]" << std::endl;
			break;
		}
	}
	ifs.close();
}

// Converts the string into an integer, then finds and returns the size of
// the of the array that needs to be initialised.
int get_array_size(string const arraysize[]) {
	return atoi(arraysize[0].c_str());
}

// Calculates which number is larger then sends it index at which it is at.
int get_largest_number_position(int base_node, int check_elements) {
	return (base_node < check_elements) ? check_elements : base_node;
}

// Finds the max depth of the Avl tree.
int get_depth_number(int tree_length) {
	int inputLevel = 100;
	int depth{}, dvalue{};
	int temp_v = 0;

	int value = 4;
	int i = 1;
	while (i < inputLevel) {
		temp_v = value - 1;

		if (temp_v >= tree_length) {
			depth = i;
			dvalue = temp_v;
			break;
		}

		value = (value * 2);
		
		i++;
	}
	return depth;
}

// Converts the string on line two into intergers that 
// are then stored into an array.
int* convert_into_element_array(string elements_array, int elements_size) {
	int element_size = elements_size;
	int* elements;

	while (!elements_array.empty()) {
		elements = new int[elements_size];

		for (int i = 0; i < elements_size; i++) {
			int temp_wspace = elements_array.find(" ");
			string temp_single_element = elements_array.substr(0, temp_wspace);

			elements[i] = atol(temp_single_element.c_str());
			elements_array.erase(0, temp_wspace + 1);

		}
		return elements;

	}
	return nullptr;
}