/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	// TODO: Fill this in!
	head = tail = NULL;
	length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	// TODO: Fill this in!
	while(head != NULL){
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

int LinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	Cell* c = new Cell;
	c->val = value;
	Cell* prev = NULL;	
	if(head == NULL){
		c ->next = NULL;
		head=tail=c;
	}else{
		c->next = head;
		while(value > c -> next -> val){
		  prev = c -> next;

		  if(c->next == tail){
			tail = c;
			tail->next = NULL;
			break;
		  }

		  c->next = c->next->next;
		}
		if(prev != NULL) prev->next = c;
		else head = c;
	}
	length++;
}

string LinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if(isEmpty()) error("Wrong");
	return head->val;
}

string LinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (isEmpty()) error("No elements");
	string val = head->val;
	Cell* next = head->next;
	delete head;
	length--;
	head = next;
	return val;
}

