// Erik Slack
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "player.h"
using namespace std;

template <typename ItemType>
class List
{
private:
	struct Node {
	// DATA
		ItemType item;
		Node* next;
		Node* prev;

		//~Node;
	};

	int count;
	Node* head;
	Node* tail;

public:
	// CONSTRUCTORS
	List() {
		count = 0;
		head = NULL;
		tail = NULL;
	}

	~List() {
		clear();
	}

	// ANALYZERS
	int size() {
		return count;
	}
	
	int find(string query) {
		int index_out = -1;
		int current_index = 0;
		bool item_found = false;

		Node* item_search = NULL;
		item_search = head;

		while (item_search != NULL && item_found == false) {
			if (item_search->item->getName() == query) {
				item_found = true;
				index_out = current_index;
				break;
			}
			item_search = item_search->next;
			current_index++;
		}

		return index_out;
	}

	Node* get_byIndex(string index_query) {
		Node* node_search;
		int query_converted = atoi(index_query.c_str());

		if (query_converted < (count / 2)) {
			int current_index = 0;
			node_search = head;
			while (current_index != query_converted) {
				node_search = node_search->next;
				if (current_index == query_converted) {
					break;
				}
				current_index++;
			}
		} else {
			int current_index = count - 1;
			node_search = tail;
			while (current_index != query_converted) {
				if (current_index == query_converted) {
					break;
				}
				
				node_search = node_search->prev;
				current_index--;
			}
		}
		
		return node_search;
	}
	
	ItemType at(string index_in, int addition, int subtraction) {
		ItemType item_out;
		int index_converted = atoi(index_in.c_str()) + addition - subtraction;

		if (count <= 0 || index_converted > count - 1) {
			// nothing happens
		} else if (index_converted == 0 && head != NULL) { // remove first item of list 
			Node* temp = head; // makes a second pointer to item already pointed to by head
			item_out = temp->item; // extracts the item so later we can Return what item was removed
		} else if (index_converted == count - 1 && count > 1) { // remove last item of list 
			Node* temp = tail; // makes a second pointer to item already pointed to by list
			item_out = temp->item; // extracts the item so later it can Return what item was removed
		} else { // find at middle of list 
			Node* node_search = get_byIndex(index_in);
			item_out = node_search->item; // extracts the item so later we can Return what item was removed
		}
		
		return item_out;
	}

	// MUTATORS
	void clear() {
		while (head != NULL) {
			Node* temp_node = head;
			head = head->next;
			delete temp_node;
		}
		
		tail = NULL;
		count = 0;
	}

	void insert(const ItemType& item_in, string index_in) {
		int index_converted = atoi(index_in.c_str());
		Node* n = new Node();
		n->item = item_in;
		//cout << endl << "count = " << count << endl;
		//cout << "index_in = " << index_in << endl;
		
		if (count == 0) { // add premeire item of list
			head = n;
			tail = n;
			n->next = NULL;
			n->prev = NULL;
		} else if (index_converted == 0) { // add at beginning of list
			n->next = head;
			n->prev = NULL;
			head->prev = n;
			head = n;
		} else if (index_converted == count) { // append to list
			n->next = NULL;
			n->prev = tail;
			tail->next = n;
			tail = n;
		} else if (index_converted > count) { // index is greater than size of list
			// nothing happens
		} else { // add to middle of list
			Node* node_search = get_byIndex(index_in);
			n->next = node_search;
			n->prev = node_search->prev;
			node_search->prev->next = n;
			node_search->prev = n;
		}
		
		count++;
		//cout << endl << "count = " << count << endl;
	}
	
	void removeSubSection() {
		if (count > 1) { // this should only happen if there is more than one item in the list
			head = head->next; // sets head to point at second item in list
			head->prev = NULL; // sets the new head's prev to NULL
		} else if (count == 1) { // remove only item left in list
			head = NULL;
			tail = NULL;
		}
	}

	ItemType remove(string index_in) {
		ItemType item_out;
		int index_converted = atoi(index_in.c_str());

		if (count <= 0 || index_converted > count - 1) {
			// nothing happens
		} else if (index_converted == 0 && head != NULL) { // remove first item of list 
			Node* temp = head; // makes a second pointer to item already pointed to by head
			
			removeSubSection();
			
			item_out = temp->item; // extracts the item so later we can Return what item was removed
			delete temp; // deletes what used to be the head item from memory
			count--;
		} else if (index_converted == count - 1 && count > 1) { // remove last item of list 
			Node* temp = tail; // makes a second pointer to item already pointed to by list
			tail = temp->prev; // sets tail to point at second to last item in list
			tail->next = NULL; // sets the new tail's next to NULL
			item_out = temp->item; // extracts the item so later we can Return what item was removed
			delete temp; // deletes what used to be the tail item from memory
			count--;
		} else { // removed from middle of list 
			Node* node_search = get_byIndex(index_in);
			node_search->prev->next = node_search->next;
			node_search->next->prev = node_search->prev;
			node_search->next = NULL;
			node_search->prev = NULL;
			item_out = node_search->item; // extracts the item so later we can Return what item was removed
			delete node_search;
			count--;
		}
		
		return item_out;
	}

	// PRINTERS
	string print() {
		stringstream ss;
		Node* current_node = head;
		int current_index = 0;
		string currentName;

		while (current_node != NULL) {
			currentName = current_node->item->getName();
			ss << current_index << ": " << currentName << endl;
			current_index++;
			current_node = current_node->next;
		}

		return ss.str();
	}
	
	string printMore() {
		stringstream ss;
		Node* current_node = head;
		int current_index = 0;
		string currentName;
		int currentStrength;
		int currentSpeed;

		while (current_node != NULL) {
			currentName = current_node->item->getName();
			currentStrength = current_node->item->getStrength();
			currentSpeed = current_node->item->getSpeed();
			ss << "\t" << currentName << " " << currentStrength << " " << currentSpeed << endl;
			current_index++;
			current_node = current_node->next;
		}

		return ss.str();
	}
	
	string printInLine() {
		stringstream ss;
		Node* current_node = head;
		int current_index = 0;
		string currentName;
		int currentStrength;
		int currentSpeed;

		while (current_node != NULL) {
			currentName = current_node->item->getName();
			currentStrength = current_node->item->getStrength();
			currentSpeed = current_node->item->getSpeed();
			ss << currentName;
			if (current_index < count - 1){
				ss << ", ";
			}
			current_index++;
			current_node = current_node->next;
		}
		ss << endl;
		return ss.str();
	}
};
