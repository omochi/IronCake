#pragma once

namespace ick{
	template <typename T> class LinkedList;
	template <typename T> class LinkedListNode;
	
	template <typename T>
	LinkedListNode<T> * LinkedListFind(const LinkedList<T> & list, const T & value);
}
