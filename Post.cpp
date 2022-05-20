/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Post.h"

using std::string;
using std::vector;
using std::istringstream; 
using std::cout, std::endl;  

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

/*
Return a vector containing unique candidate tags extracted from postText
• Tags are words within postText that begin with a ‘#’.
• Tags are not case-sensitive.
• Remove punctuations(‘!’, ‘, ’, ‘.’, ‘ ? ’) at the end of each extracted tag, if any.
• As an example, the following need to be treated as the same, and need to be added as the lowercase version(#happy) to the vector :
 #happy   #Happy    #HaPpY      #HAPPY      #happy!     #happy!!

When finding tags, this function returns all candidate strings beginning
with ‘#’.
• Note : The function does NOT filter out invalid Tags, such as #, #1a23, or #!happy.
*/

void word_toLower(string& word) {
    string retString; 
    for (char c : word) {
        retString += tolower(c); 
    }
    word = retString; 
}

bool isPunctuation(char c) {
    if (c == '.' || c == '!' || c == ',' || c == '?')
        return true;
    return false; 
}

vector<string> Post::findTags() {
    // TODO(student): extracts candidate tags based on occurrences of # in the post
      // in postText find #words 
    vector <string> postList;
    bool debug = 0; 

    if(debug) cout << "In the find tags function" << endl; 

    if (!postText.empty()) {
        std::istringstream ss (postText); // std::istringstream inSS(num); 

        string currPost = "";
        int end = -1;

        if (debug) cout << "Post is not empty" << endl; 

        // make them lowercase  
        while (ss.good()) {
            ss >> currPost;

            if (debug) cout << "Current word: " << currPost << endl;

            if (currPost.at(0) == '#') {
                if (debug) cout << "   This one has a # " << endl;
                end = currPost.size() - 1;
                while (isPunctuation(currPost.at(end))) {
                    end--;
                }
                // fiRe! 
                currPost = currPost.substr(0, end + 1); // if size of 5, end = 3, length = 4 
                word_toLower(currPost); 

                if (debug) cout << "Word to push_back() : " << currPost << endl;

                postList.push_back(currPost);
            }
            else {
                continue;
            }
        }

        if (postList.size() > 1) {
            // remove duplicates in list 
            for (unsigned int outer = 0; outer < postList.size(); outer++) {
                for (unsigned int inner = 0; inner < postList.size(); inner++) {
                    if (postList.at(inner) == postList.at(outer) && (inner != outer)) {
                        if (debug) cout << "Element gone: " << postList.at(inner) << endl;
                        postList.erase(postList.begin() + inner); // element at inner is now gone  /// --------------this was changed !! 
                        
                        inner--; // decrement to offset the comparison thing 
                    }
                }
            }
        }
        

        
    }

    return postList; // in the case it is empty, it will straight return an empty vector which is good 

}

//main 3 
int main3() {
    // 42412212 ajitjain When deallocating #dynamic arrays, use delete[].
    Post p = { 42412212, "ajitjain", "When #dynamic deallocating #dynamic arrays, #use delete[]" }; 

    cout << "Post ID: " << p.getPostId() << endl; 

    cout << "Post name: " << p.getPostUser() << endl; 

    vector <string> v = p.findTags(); 

    cout << "Vector: " << endl; 
    for (string s : v)
        cout << s << endl; 
    return 0;
}
