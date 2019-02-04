#ifndef LIST_H
#define LIST_H

/*
 * List is a list of integers
 */
class List {
public:
	/* creates an empty list */
	List();
	
	/* destroys this list */
	~List();
	
	/* returns true if d is in the list */
	bool exists(int d) const;
	
	/* returns the size of the list */
	int size() const;
	
	/* returns true if the list is empty */
	bool empty() const;
	
	/* inserts d into this list as the first element */
	void insertFirst(int d);
	
	/* removes the first element less than/equal to/greater than d,
	 depending on the value of df. Does nothing if there is no value
	 to remove. The enum values are accessed with List::DeleteFlag::LESS,
	 ..., outside the class */
	enum class DeleteFlag { LESS, EQUAL, GREATER };
	void remove(int d, DeleteFlag df = DeleteFlag::EQUAL);
	
	/* prints the contents of this list */
	void print() const;
	
	/* forbid copying of lists */
	List(const List&) = delete;
	List& operator=(const List&) = delete;
private:
	/* a list node */
	struct Node {
		int value;  // the node value
		Node* next; // pointer to the next node, nullptr in the last node
		Node(int v, Node* n) : value(v), next(n) {}
	};
	
	Node* first; // pointer to the first node
};

#endif
