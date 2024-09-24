//
// Created by benja on 2021-03-22.
//

#ifndef PROJECT2_TRIE_H
#define PROJECT2_TRIE_H

#include "Node.h"
#include <string>

class Trie {

private:

    unsigned int _size;
    unsigned int _biggestWord;
    std::string _wConcat;
    Node *_root;

public:

    Trie();
    ~Trie();
    void insertWord(Node *root, const std::string& w, int pos);
    bool eraseWord(Node *root, const std::string& w, int pos);
    bool searchWord(Node *root, const std::string& w, int pos);
    void print(Node *root, std::string *wConcat, int pos);
    void autoComplete(Node *root, const std::string& w, int pos);
    bool empty() const;
    void clear(Node *root);
    unsigned int size() const;

    Node* getRoot() const;
    unsigned int getBiggestWord() const;
    void setBiggestWord(unsigned int s);
    static bool invalidInput(std::string const& w) ;
    static bool hasChildren(const Node *node) ;
    bool searchWordAC(Node *root, const std::string& w, int pos);
    std::string getwConcat() const;
    void setwConcat(const std::string& s);
};


#endif //PROJECT2_TRIE_H
