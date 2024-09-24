//
// Created by benja on 2021-03-22.
//

#ifndef PROJECT2_NODE_H
#define PROJECT2_NODE_H

class Node {

private:
    char _letter;
    bool _terminal;

public:
    explicit Node(char l);

    Node *next[26]{nullptr};
    char getLetter() const;
    bool getTerminal() const;
    void setTerminal(bool t);
};


#endif //PROJECT2_NODE_H
