//Partners: Karl Antonio & Mycah Detorres
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DLL::DLL() { // constructor - initializes an empty list
	last = NULL;
	first = NULL;
	numSongs = 0;
}
DLL::DLL(string t, string l, int m, int s) { // constructor, initializes a list with one new node with data x
	DNode *n = new DNode(t, l, m, s);
	first = n;
	last = n;
	numSongs = 1;
}

void DLL::push(string t, string a, int m, int s) {
	DNode *n = new DNode(t, a, m, s);
	if (numSongs == 0) {
		first = n;
	} else {
		last->next = n;
		n->prev = last;
	}
	last = n;
	numSongs++;
}

Song* DLL::pop() {
	if (numSongs == 1) { //This pops the last node off the list.  If there is only one node on the list, it resets first and last to NULL and the numSongs field to 0.  It returns a song object.
		first = NULL;
		DNode *tmp = last;
		Song *song = tmp->song;
		delete tmp;
		last = NULL;
		return song;
	} else {
		DNode *tmp = last;
		Song *song = tmp->song;
		last = last->prev; //setting last song to the previous song bc going to delete last song
		delete tmp;
		last->next = NULL;
		return song;
	}

	numSongs--;

}

void DLL::printList() {
	DNode *tmp = first;
	while (tmp != NULL) {
		tmp->song->printSong();
		tmp = tmp->next;
	}
	cout << endl;
}

int DLL::remove(string t) {
	if (numSongs == 0) { //Checking if List is empty or not
		cout << "List is Empty. Nothing to Remove" << endl;
		return 1;
	}
	if (last->song->title == t) { //Checking if user wants to delete the last song on list
		cout << "Removing: ";
		last->song->printSong();
		pop();
		return 1;
	}
	DNode *tmp = first;
	if (tmp->song->title == t) { //Checking if user wants to delete the first song on list
		cout << "Removing: ";
		tmp->song->printSong();
		tmp->next->prev = tmp->prev;
		first = tmp->next;
		delete tmp;
		numSongs--; //for ~
		return 1;
	}
	while (tmp->next != NULL) { //Checking if user wants to delete any of the songs in the middle
		tmp = tmp->next;
		if (tmp->song->title == t) {
			cout << "Removing: ";
			tmp->song->printSong();
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			delete tmp;
			numSongs--;
			return 1;
		}
	}
	cout << "That song is not on the list" << endl;
	return 1;

}

void DLL::moveUp(string t) {
	if (numSongs == 0) { //Checks if there is a song on the list
		cout << "List is Empty" << endl;
	} else { //Everything under will run if there is at least 1 song on the list
		DNode *tmp = first;
		while (tmp != NULL) {
			if (tmp->song->title == t) {
				if (tmp->prev == NULL) { //IF user chooses to move first song so the top song will go bottom
					first = tmp->next;
					first->prev = NULL; //first song is now null
					last->next = tmp; //the next of the last song is now the 1st song
					tmp->prev = last;
					last = tmp;
					last->next = NULL;
					break;
				} else if (tmp->prev->prev == NULL) { //if the user chooses 2nd song to move up
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					tmp->prev->prev = tmp;
					tmp->next = tmp->prev;
					tmp->prev = NULL;
					first = tmp;
					break;
				} else if (tmp->next == NULL) { //if user chooses last song to move up
					tmp->prev->prev->next = tmp;
					last = tmp->prev;
					tmp->prev->next = NULL;
					tmp->next = tmp->prev;
					tmp->prev = tmp->next->prev;
					tmp->next->prev = tmp;
					break;
				} else { //if user chooses song middle of 2 - last
					tmp->prev->prev->next = tmp; //if tmp is 4 then its prev is 3 and 3's prev is 2 but 2's next used to be 3 but we setting to tmp which is 4
					//temp's next's previous
					tmp->next->prev = tmp->prev; //changing 5's prev to 3
					tmp->prev->next = tmp->next;
					tmp->next = tmp->prev; //4's next is now 3
					tmp->prev = tmp->prev->prev;
					tmp->next->prev = tmp;
					break;
				}
			}
			tmp = tmp->next;
		}
	}
}

void DLL::moveDown(string t) {
	if (numSongs == 0) {
		cout << "Nothing to do, list is empty" << endl;
	} else {
		DNode *tmp = first;
		while (tmp != NULL) {
			if (tmp->song->title == t) {
				if (tmp->prev == NULL) { //first song moving down
					tmp->next->next->prev = tmp;
					first = tmp->next;
					first->prev = NULL;
					tmp->next = first->next;
					first->next = tmp;
					tmp->prev = first;
				} else if (tmp->next == NULL) { //last song becoming first
					first->prev = tmp;
					tmp->next = first;
					first = tmp;
					last = tmp->prev;
					last->next = NULL;
					tmp->prev = NULL;
				} else if (tmp->next->next == NULL) { //second to the last song being last
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					tmp->next->next = tmp;
					tmp->prev = tmp->next;
					last = tmp;
					tmp->next = NULL;
				} else {
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					tmp->next = tmp->next->next;
					tmp->prev = tmp->next->prev;
					tmp->next->prev->next = tmp;
					tmp->next->prev = tmp;
				}
			}
			tmp = tmp->next;
		}
	}
}

void DLL::makeRandom() {
	int counter;
	int shift;
	Song *song;
	for (int i = 0; i < 2 * numSongs; i++) {
		shift = rand() % (2 * numSongs) + 1;
		int c = rand() % 2;
		counter = 0;
		song = first->song;
		while (counter < shift) {
			if (c == 0) {
				moveUp(song->title);

			} else {
				moveDown(song->title);
			}
			counter++;
		}
	}
}

void DLL::listDuration(int *tm, int *ts) {
	if (numSongs >= 1) {
		DNode *tmp = first;
		while (tmp != NULL) {
			*tm += tmp->song->min;
			*ts += tmp->song->sec;
			tmp = tmp->next;
		}
	} else {
		*tm = 0;
		*ts = 0;
	}
}

DLL::~DLL() {
	DNode *tmp = first;
	while (numSongs != 0) {
		cout << "Deleting: " << tmp->song->title << endl;
		remove(tmp->song->title);
		tmp = tmp->next;
	}

	first = NULL;
	last = NULL;
}
