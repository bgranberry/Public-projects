//Binary tree node class from souce code for Data Structures and Other Objects
//using C++ by Michael Main and Walter Savitch, Chapter 10. This version has 
//been heavily edited.

// FILE: bintree.h (part of the namespace main_savitch_10)
// PROVIDES: A template class for a node in a binary tree and functions for 
// manipulating binary trees. The template parameter is the type of data in
// each node.

#ifndef BINTREE_H
#define BINTREE_H
#include <cstdlib>  // Provides NULL and size_t
#include <vector>

using namespace std;

namespace main_savitch_10
{

	template <class Item>
	class binary_tree_node
	{
	public:
		// TYPEDEF
		typedef Item value_type;
		// ARRAY SIZE CONSTANT
		//static const int MAX_TAGS = 500;
		// CONSTRUCTOR
		binary_tree_node(
			const Item& init_data = Item(),
			binary_tree_node* init_left = NULL,
			binary_tree_node* init_right = NULL
			)
		{
			data_field = init_data;
			left_field = init_left;
			right_field = init_right;
		}
		// MODIFICATION MEMBER FUNCTIONS
		Item& data() { return data_field; }
		binary_tree_node*& left() { return left_field; }
		binary_tree_node*& right() { return right_field; }
		vector<int> &tags() { return tags_field; }
		vector<int> &Ltags() { return Ltags_field; }
		vector<int> &Rtags() { return Rtags_field; }
		void set_data(const Item& new_data) { data_field = new_data; }
		void set_left(binary_tree_node *new_left) { left_field = new_left; }
		void set_right(binary_tree_node *new_right) { right_field = new_right; }
		void set_tags(binary_tree_node<Item> *currentPtr);
		void set_Ltags(binary_tree_node<Item> *currentPtr);
		void set_Rtags(binary_tree_node<Item> *currentPtr);
		void combine_tags(binary_tree_node<Item> *currentPtr);
		// CONST MEMBER FUNCTIONS
		const Item& data() const { return data_field; }
		const binary_tree_node* left() const { return left_field; }
		const binary_tree_node* right() const { return right_field; }
		bool is_leaf() const
		{
			return (left_field == NULL) && (right_field == NULL);
		}


	private:
		vector<int> tags_field;
		vector<int> Ltags_field;
		vector<int> Rtags_field;
		Item data_field;
		binary_tree_node *left_field;
		binary_tree_node *right_field;
	};


}

// FILE: bintree.template
// IMPLEMENTS: The binary_tree node class (see bintree.h for documentation). 
#include <cassert>    // Provides assert
#include <cstdlib>   // Provides NULL, std::size_t
#include <iomanip>    // Provides std::setw
#include <iostream>   // Provides std::cout
#include <string>

namespace main_savitch_10
{
	template <class Item>
	void binary_tree_node<Item>::set_tags(binary_tree_node *currentPtr)
	{

		if (currentPtr->tags_field.empty())
		{
			if (currentPtr->left()->is_leaf())
				set_Ltags(currentPtr);
			else
			{
				set_tags(currentPtr->left());
				set_Ltags(currentPtr);
			}

			if (currentPtr->right()->is_leaf())
				set_Rtags(currentPtr);
			else
			{
				set_tags(currentPtr->right());
				set_Rtags(currentPtr);
			}
			combine_tags(currentPtr);
		}

	}

	template <class Item>
	void binary_tree_node<Item>::combine_tags(binary_tree_node *currentPtr)
	{
		bool found;

		currentPtr->tags_field = currentPtr->Ltags_field;
		for (unsigned i = 0; i < currentPtr->Rtags_field.size(); i++)
		{
			found = false;

			for (unsigned j = 0; j < currentPtr->tags_field.size(); j++)
			{
				if (currentPtr->Rtags_field[i] == currentPtr->tags_field[j])
					found = true;
			}
			if (found == false)
				currentPtr->tags_field.push_back(currentPtr->Rtags_field[i]);
		}
	}

	template <class Item>
	void binary_tree_node<Item>::set_Ltags(binary_tree_node *currentPtr)
	{
		currentPtr->Ltags_field = currentPtr->left()->tags_field;
	}


	template <class Item>
	void binary_tree_node<Item>::set_Rtags(binary_tree_node *currentPtr)
	{
		currentPtr->Rtags_field = currentPtr->right()->tags_field;
	}
}
#endif
