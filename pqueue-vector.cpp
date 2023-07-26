/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	
	return vec.size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return vec.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	vec.add(value);
}

string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	int ret = find();
	return vec[ret];
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	int min = find();
	string res = vec[min];
	vec.remove(min);
	return res;
}

int VectorPriorityQueue::find(){
	int res = 0;
	for(int i = 1; i < vec.size(); i++){
		if(vec[res] > vec[i]){
			res = i;
		}
	}
	return res;
}