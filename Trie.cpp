#include <iostream>
#include <string>
#include "Trie.h"
#include "illegal_exception.h"

//Trie initialization
Trie::Trie() {
    _size = 0;
    _biggestWord = 0;
    _root = new Node(' ');
}

//Called after a clear, deletes remaining root node.
Trie::~Trie() {
    clear(_root);
    delete _root;
    _root = nullptr;
}

void Trie::insertWord(Node *root, const std::string& w, int pos) {
    //Ascii math. Ex: a=0, b=1, etc.
    int index = w[pos] - 97;

    //At end of word, set node as terminal.
    //Increase trie size by 1 word.
    if (pos == w.length()) {
        root->setTerminal(true);
        ++_size;
        return;
    }

    //Recursively insert nodes.
    //If next is nullptr create new node and insert.
    //Otherwise, use currently existing node.
    if (root->next[index] == nullptr) {
        root->next[index] = new Node(w[pos]);
    }
    insertWord(root->next[index], w, ++pos);
}

bool Trie::eraseWord(Node *root, const std::string& w, int pos) {
    //Ascii math. Ex: a=0, b=1, etc.
    int index = w[pos] - 97;

    //traverse until end of word, then start deleting
    //iff node has no children.
    //if does have children, remove terminal attribute
    if (pos == w.length()) {
        if (!hasChildren(root)) {
            delete root;
            --_size;
            return true;
        }
        root->setTerminal(false);
        --_size;
        return false;
    }

    //Keeps calling this until end of word, then starts returning true/false.
    //if deleted is false, stop erasing. (means that its a terminal or has children)
    //if deleted is true, update next index to nullptr.
    //then check if the node is not a terminal, has no children, or not main root, delete if true.
    bool deleted = (eraseWord(root->next[index], w, ++pos));
    if (deleted) {
        root->next[index] = nullptr;
    }

    if (deleted && !root->getTerminal() && !hasChildren(root) && (_root != root)) {
        delete root;
        return true;
    }
    else {
        return false;
    }
}

bool Trie::searchWord(Node *root, const std::string& w, int pos) {
    //Ascii math. Ex: a=0, b=1, etc.
    int index = w[pos] - 97;

    //if at end of word and its a terminal, word found
    if (pos == w.length()) {
        if (root->getTerminal()) {
            return true;
        }
        return false;
    }

    //Recursively search nodes.
    //If next node not nullptr, search that node.
    //Otherwise, word not found.
    if (root->next[index] != nullptr) {
        return searchWord(root->next[index], w, ++pos);
    }
    else {
        return false;
    }
}

void Trie::print(Node *root, std::string *wConcat, int pos) {

    //if sees terminal node, add everything in array to _wConcat string + space
    //if it has children, start searching that node next
    //else return
    if (root->getTerminal()) {
        for (unsigned int i{0}; i < pos; ++i) {
            _wConcat += wConcat[i];
        }
        _wConcat += " ";
        if (!hasChildren(root)) {
            return;
        }
    }

    //recursively checks every child of every node, A-Z
    //once a word is done and returns, if theres any more children at that node,
    //it continues on another word from that point. If no more children, returns
    //to last node and checks again for more children from that point.
    for (unsigned int i{0}; i < 26; ++i) {
        if (root->next[i] != nullptr) {
            wConcat[pos] = root->next[i]->getLetter();
            print(root->next[i], wConcat, ++pos);
            --pos;
        }
    }
}

void Trie::autoComplete(Node *root, const std::string& w, int pos) {
    //Ascii math. Ex: a=0, b=1, etc.
    int index = w[pos] - 97;

    //when at end of word, do a print to show suggestions.
    //word is moved in new bigger array to accommodate concatenation
    if (pos == w.length()) {
        std::string wConcat[_biggestWord];
        for (unsigned int i{0}; i < w.length(); ++i) {
            wConcat[i] = w[i];
        }
        print(root, wConcat, pos);
        std::cout << _wConcat.substr(0, _wConcat.length() - 1) << std::endl;
        return;
    }

    //recursively iterates until end of word.
    autoComplete(root->next[index], w, ++pos);
}

bool Trie::empty() const {
    if (_size == 0) {
        return true;
    }
    return false;
}

void Trie::clear(Node *root) {

    //starts at bottom of every subtree and checks if nodes have children,
    //as we go back up the tree recursively.
    for (unsigned int i{0}; i < 26; ++i) {
        if (root->next[i] != nullptr) {
            clear(root->next[i]);
            root->next[i] = nullptr;
        }
    }

    //If finished checking node
    if (root != _root) {
        delete root;
    }
}

unsigned int Trie::size() const {
    return _size;
}

Node* Trie::getRoot() const{
    return _root;
}

unsigned int Trie::getBiggestWord() const {
    return _biggestWord;
}

bool Trie::invalidInput(const std::string& w) {

    //Checking for illegal characters
    try {
        for (unsigned int i{0}; i < w.length(); ++i) {
            int ascii{w[i] - 97};
            if (!((ascii) >= 0 && (ascii) < 26)) {
                throw illegal_exception();
            }
        }
    }
    catch (illegal_exception e) {
        return true;
    }

    return false;
}

void Trie::setBiggestWord(unsigned int s) {
    _biggestWord = s;
}

bool Trie::hasChildren(const Node *node) {
    //Checks if node has children
    for (unsigned int i{0}; i < 26; ++i) {
        if (node->next[i] != nullptr) {
            return true;
        }
    }
    return false;
}

bool Trie::searchWordAC(Node *root, const std::string& w, int pos) {
    //Ascii math. Ex: a=0, b=1, etc.
    int index = w[pos] - 97;

    //if at end of word, prefix found
    if ((pos == w.length()) && !empty()) {
        return true;
    }

    //Recursively search nodes.
    //If next node not nullptr, search that node.
    //Otherwise, word not found.
    if (root->next[index] != nullptr) {
        return searchWordAC(root->next[index], w, ++pos);
    }
    else {
        return false;
    }
}

std::string Trie::getwConcat() const {
    return _wConcat;
}

void Trie::setwConcat(const std::string& s) {
    _wConcat = s;
}
