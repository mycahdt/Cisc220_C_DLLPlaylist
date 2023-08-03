//Partners: Karl Antonio & Mycah Detorres
#include "DNode.hpp"
#include "Song.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DNode::DNode(){
	song = new Song();
	prev = NULL;
	next = NULL;
}

DNode::DNode(string s, string a, int lenmin, int lensec){
	song = new Song(s, a, lenmin, lensec);
	prev = NULL;
	next = NULL;

}
