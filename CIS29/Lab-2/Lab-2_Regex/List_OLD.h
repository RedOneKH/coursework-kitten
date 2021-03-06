/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the abstract List class. It will serve as the
base class for XmlNodeList and LinkedList.
*/

#ifndef LIST_H_
#define LIST_H_

template<class T>
class List
{
protected:
	int listSize;
public:
	// constructor and destructor
	List() { listSize = 0; }
	virtual ~List() {}
	// getter
	int size() const { return listSize; }
	virtual const T & getItemAt(int position) const = 0;
	// insertion and deletion methods
	virtual bool insert(const T &newEntry, int position = 1) = 0;
	virtual bool remove(int position) = 0;
	// other methods
	bool isEmpty() const { return (listSize == 0); }
};

#endif // LIST_H_