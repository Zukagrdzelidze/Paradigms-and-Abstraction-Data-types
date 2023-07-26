/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	head = tail = NULL;
	length = 0;

}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	while(length > 0){
		length--;
		Cell* tmp = head->next;
		delete head;
		head = tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return (size() == 0);
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	Cell* newCell = new Cell;
	newCell->val = value;
	newCell->next = NULL;
	if(length == 0){
		newCell->prev = NULL;
		head = tail = newCell;
	}else{
		newCell->prev = tail;
		tail->next = newCell;
		tail = newCell;
	}
	length++;
}

string DoublyLinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if(isEmpty()) error("There are no elements");
	string minVal = head->val;
	for(Cell* tmp = head; tmp != NULL ; tmp = tmp->next){
		if(tmp->val < minVal) minVal = tmp->val;
	}
	return minVal;
	
	
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if(isEmpty()) error("There are no elements");
	Cell* min = head;
	for(Cell* tmp = head; tmp != NULL ; tmp=tmp->next){
		if(tmp->val < min->val) min = tmp;
	} 
	string ret = min->val;
	if(min == tail || min == head){
		if(size() != 1){
			if(min == tail){
				min->prev->next = NULL;
				tail = min->prev;
			}else{
				min->next->prev = NULL;
				head = min->next;
			}
		}else head=tail=min;
	}else{
		min->next->prev = min->prev;
		min->prev->next = min->next;
	}
	delete min;
	length--;
	return ret;
}

