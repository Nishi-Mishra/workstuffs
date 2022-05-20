/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include "Tag.h"

using std::string;
using std::vector;
using std::endl;
using std::cout; 

bool isPunctuation1(char c) {
	if (c == '.' || c == '!' || c == ',' || c == '?')
		return true;
	return false;
}

//Throw std::invalid_argument if any of the following are true:
//• tagName length is less than 2
//• the first character of tagName is not ‘#’
//• the second character in tagName is not from ‘a’ - ‘z’
//• tagName contains uppercase letters ‘A’ - ‘Z  (In other words it should be all lowercase letters)
//• there is one or more consecutive punctuations at the end of the
//tagName(e.g., #happy!, #happy!? , etc.), where a punctuation is
//one of the following : ('!', ',', '.', '?')

Tag::Tag(string tagName) {
  // TODO(student): implement constructor checks

	// cout << "In constructor tag size: " << tagName.size() << endl;

	if (tagName.empty())
		throw std::invalid_argument("Empty ");
	if (tagName.at(0) != '#')
		throw std::invalid_argument("Doesn't begin with '#'");

	if (tagName.size() < 2)
		throw std::invalid_argument("Too short");

	
	
	unsigned int i = 1; 
	while (i < tagName.size()) { // needs redoing !! 

		if (!islower(tagName.at(i))) // cannot be lowercase and must be a letter 
			throw std::invalid_argument("Letter in tag is uppercase");

		// if (!isalpha(tagName.at(i))) // as soon as we find a not letter, break and see how much more of the string is left, 
		//	break;					// if more than one letter throw invalid arg 
		i++; 
	}
	
	if (isPunctuation1(tagName.at(tagName.size() - 1)))
		throw std::invalid_argument("Is punctuation"); 
	// if we are already at i = tagName.size() it is done and life is good -- no need for a check here 

	//if (i == (tagName.size() - 1)) { // on the last letter then check is that one letter valid punctuation, if not return 
	//	if (tagName.at(i) != '!' && tagName.at(i) != ',' && tagName.at(i) != '.' && tagName.at(i) != '?')
	//		throw std::invalid_argument("Last letter is not valid punctuation"); 
	//}
	//else if (i < (tagName.size() - 1)) {
	//	throw std::invalid_argument("Is not a letter and there are multiple characters afterword"); 
	//}

	this->tagName = tagName;  

}

string Tag::getTagName() {
  // TODO(student): implement getter
	return tagName; 
}

vector<Post*>& Tag::getTagPosts() {
  // TODO(student): implement getter
	return tagPosts; 
}

void Tag::addTagPost(Post* post) {
  // TODO(student): add post to tag posts

	if (post == nullptr)
		throw std::invalid_argument("Post was nullptr"); 

	tagPosts.push_back(post); 
}

// main1()
int main1() {

	Tag* t = new Tag("#1ray");
	cout << "Tagname: " << t->getTagName() << endl;
	delete t; 

	return 0; 
}