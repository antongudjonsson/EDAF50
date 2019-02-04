#include <iostream>
#include "list.h"

using std::cout;
using std::endl;

int main() {
	List list;
	cout << std::boolalpha;
	cout << "Is empty: " << list.empty() << endl;
	cout << "Print empty list: ";
	list.print();
	cout << endl;
	
	for (int i = 10; i >= 0; i -= 2) {
		list.insertFirst(i);
	}
	cout << "List with " << list.size() << " even numbers: ";
	list.print();
	cout << endl;
	
	cout << "0 exists:  " << list.exists(0) << endl;
	cout << "4 exists:  " << list.exists(4) << endl;
	cout << "10 exists: " << list.exists(10) << endl;
	cout << "7 exists:  " << list.exists(7) << endl;
	
	list.remove(5, List::DeleteFlag::EQUAL);
	cout << "After remove = 5: ";
	list.print();
	cout << endl;
	list.remove(5, List::DeleteFlag::GREATER);
	cout << "After remove > 5: ";
	list.print();
	cout << endl;
	list.remove(5, List::DeleteFlag::LESS);
	cout << "After remove < 5: ";
	list.print();
	cout << endl;
	
	cout << "Is empty: " << list.empty() << endl;
}
