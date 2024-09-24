//
// Created by benja on 2021-03-22.
//

#include "Node.h"

Node::Node(char l) {
    _letter = l;
    _terminal = false;
}

char Node::getLetter() const {
     return _letter;
}

bool Node::getTerminal() const {
    return _terminal;
}

void Node::setTerminal(bool t) {
    _terminal = t;
}
