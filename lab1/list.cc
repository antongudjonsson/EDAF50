#include <iostream>
#include "list.h"

using std::cout;
using std::endl;

List::List() {
	first = nullptr;
}

List::~List() {
	if(!empty()){
	Node* prev = first;
	Node* curr = first->next;
	while(curr != nullptr){
		delete prev;
		prev = curr;
		curr = curr->next;
	}
	delete prev;
	}
}

bool List::exists(int d) const {
	if(empty()){
		return false;
	}else{
		Node* temp = first;
		while(temp != nullptr){
			if(temp->value == d){
				return true;
			}
			temp = temp->next;
		}
		return false;
	}
}

int List::size() const {
	Node* temp = first;
	int count = 0;
	while(temp != nullptr){
		count++;
		temp = temp->next;
	}
	return count;
}

bool List::empty() const {
	if(first == nullptr){
		return true;
	}else{
		return false;
	}
}

void List::insertFirst(int d) {
	Node* myNode = new Node(d, first);
	first = myNode;
}

void List::remove(int d, DeleteFlag df) {
	Node* thisNode = first;
	Node* prevNode = nullptr;
	switch (df)
	{
		case List::DeleteFlag::EQUAL:
			while(thisNode->next != nullptr){
				if(thisNode->value == d){
					if(prevNode == nullptr){
						first = thisNode->next;
					}else{
						prevNode->next = thisNode->next;
					}
					delete thisNode;
					break;
				}
				prevNode = thisNode;
				thisNode = thisNode->next;
			}
			break;
		
		case List::DeleteFlag::GREATER:
			while(thisNode->next != nullptr){
				if(thisNode->value > d){
					if(prevNode == nullptr){
						first = thisNode->next;
					}else{
						prevNode->next = thisNode->next;
					}
					delete thisNode;
					break;
				}
				prevNode = thisNode;
				thisNode = thisNode->next;
			}
			break;

		case List::DeleteFlag::LESS:
			while(thisNode->next != nullptr){
				if(thisNode->value < d){
					if(prevNode == nullptr){
						first = thisNode->next;
					}else{
						prevNode->next = thisNode->next;
					}
					delete thisNode;
					break;
				}
				prevNode = thisNode;
				thisNode = thisNode->next;
			}
			break;

		default:
			cout << "Not valid delete flag" << endl;
	}

}

void List::print() const {
	if(!empty()){
		Node* myNode = first;
		std::cout << std::endl << "[";
		while(myNode != nullptr){
			std::cout << myNode->value << ",";
			myNode = myNode->next;
		}
		std::cout << "\b]" << std::endl;
	}else{
		std::cout << "\nList is empty" << std::endl;
	}
}

