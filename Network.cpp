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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;
using std::cout;  
using std::endl;

bool debug = DEBUG; 

Network::Network() : users {}, posts{}, tags{} {
  // empty containers of vectors already created
  // no implementation is needed here
}

/*
If file could not be opened, throw std::invalid_argument

Refer to the format of User and Post information included in the file. Add users and posts as you read the lines from the 
file by calling addUser() and addPost().
-- If the file content does not match the specified format, throw std::runtime_error. This includes:
• User or Post entry not following the specified format
• Unknown entry (neither User nor Post)

Note: You throw std::invalid_argument only when the file could not be opened. If there are std::invalid_argument thrown 
by add user and post operations, you catch them here and throw std::runtime_error instead.
*/

void Network::loadFromFile(string fileName) {
  // TODO(student): load user and post information from file

    cout << "Debug: " << DEBUG << endl; 

    std::ifstream file(fileName); 
    string currType = ""; 
    int id = -1; 
    string user = ""; 
    string restofline = "";  

    if (file.is_open())
        file >> currType;
    else
        throw std::invalid_argument("File not open"); 

    if (file.is_open()) {
        while (file.good()) { // getline with stringstream with all the 
            // load info 
            try {
                if (currType == "User") {
                    file >> user;
                    if (file.eof() || file.fail() || file.bad())
                        throw std::runtime_error("End of file");
                    addUser(user);
                    // cout << "User added: " << user << endl; 
                }
                else if (currType == "Post") {
                    file >> id;
                    if (file.eof() || file.fail() || file.bad())
                        throw std::runtime_error("End of file");
                    file >> user;
                    if (file.eof() || file.fail() || file.bad())
                        throw std::runtime_error("End of file"); 
                    getline(file, restofline);  
                    if (restofline == "" || file.bad()) 
                        throw std::runtime_error("Empty post");
                    
                    
                    if (debug) {

                        /*cout << "ID post added: " << id << endl;
                        cout << "User of post added: " << user << endl;
                        cout << "Post text added: " << restofline << endl;*/
                    }
                    
                    addPost(id, user, restofline);
                }
                else {
                    if (file.eof() || file.bad())
                        throw std::runtime_error("Unknown type");
                    else
                        break; 
                }
            }
            catch (...) { // catch std::invalid + anything bad with file streams 
                throw std::runtime_error("File stream broke");
            }
            if (file.eof())
                throw std::runtime_error("End of file"); 
            file >> currType; 
        }
    }
    else {
        throw std::invalid_argument("Cannot open file"); 
    }

    
    if (debug) {
        cout << "Usernames:  " << endl;

        for (User* u : users) {
            cout << "Username: " << u->getUserName() << endl; 

            vector <Post*> userPosts123 = u->getUserPosts(); 

            for (Post* p : userPosts123) {
                cout << "   Post: " << p->getPostText() << "  ID: " << p->getPostId() << endl;
            }

        }
        cout << endl << endl << "Posts: " << endl;
        for (Post* p : posts) {
            cout << "Post text: " << p->getPostText() << "  ID: " << p->getPostId() << endl;
        }
        cout << endl << endl;
        for (Tag* t : tags) {
            cout << "Tags: " << t->getTagName() << endl;
        }
    }
    

}

void word_toLower2(string& word) {
    string retString;
    for (char c : word) {
        retString += tolower(c);
    }
    word = retString;
}

void Network::addUser(string userName) {
  // TODO(student): create user and add it to network

    word_toLower2(userName);   

    if (users.size() != 0) {
        for (User* u : users) {
            if (u->getUserName() == userName)
                throw std::invalid_argument("Username already exists");
        }
    }
    
    User* u = new User(userName); 

    users.push_back(u);
    cout << "Added User " << userName << endl; 

}

void Network::addPost(unsigned int postId, string userName, string postText) {
  // TODO(student): create post and add it to network
    bool foundUser = false; 
    

    if (debug) {
        cout << userName << "  ";
        cout << postText << endl << endl;
    }
    

    for (User* u : users) {
        if (u->getUserName() == userName) { 
            foundUser = true; 

            for (Post* p : posts) {
                if (p->getPostId() == postId)
                    throw std::invalid_argument("Same post id found");
            }

            Post* p = new Post(postId, userName, postText);
            posts.push_back(p);  
            u->addUserPost(p); 
            cout << "Added Post " << p->getPostId() << " by " << p->getPostUser() << endl; 
            vector <string> tagPost = p->findTags(); 

            bool foundTag = false; 
            for (string tagInPost : tagPost) { // go thru tags in post 
                foundTag = false;
                for (Tag* tagInNetwork : tags) {
                    if (tagInPost == tagInNetwork->getTagName()) { // go thru tags in network 
                        foundTag = true; 
                        tagInNetwork->addTagPost(p); 
                        break; 
                    }
                } // inner for loop end 

                if (!foundTag) {
                    try {
                        Tag* t = new Tag(tagInPost);
                        if (debug) cout << "Tag we just added: " << t->getTagName() << endl;
                        tags.push_back(t);
                        t->addTagPost(p);
  
                    } 
                    catch (...) {
                        continue; 
                    }
                }

            } // outer for loop end 
        }
    }
    

    if (!foundUser)
        throw std::invalid_argument("User not found"); 

}

vector<Post*> Network::getPostsByUser(string userName) {
  // TODO(student): return posts created by the given user
    vector <Post*> v; 
    bool foundUser = false; 
    for (User* u : users) {
        if (u->getUserName() == userName) {
            foundUser = true; 
            v = u->getUserPosts(); 
        }
    }

    if (!foundUser)
        throw std::invalid_argument("User not found");

    return v; 
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  // TODO(student): return posts containing the given tag
    if (tagName.empty())
        throw std::invalid_argument("Tag is empty"); 

    for (Tag* t : tags) {
        if (t->getTagName() == tagName)
            
            return t->getTagPosts(); 
    }

    throw std::invalid_argument("Cannot find tag"); 
}

vector<string> Network::getMostPopularHashtag() {
  // TODO(student): return the tag occurring in most posts

    vector <string> popTags; 
    unsigned int max = 0; 
    for (Tag* t : tags) {
        if (t->getTagPosts().size() > max) {
            popTags.clear(); 
            max = t->getTagPosts().size();
            popTags.push_back(t->getTagName()); 
        }
        else if (t->getTagPosts().size() == max) {
            popTags.push_back(t->getTagName()); 
        }
    }

    return popTags; 
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}

// main 2 
int main2() {

    Network* n = new Network(); 
    /*n->addUser("NiShi"); 
    n->addPost(12, "nishi", "anknsksk #Hello"); */
    n->loadFromFile("test2.txt"); 
    delete n;

    return 0; 
}