#include <iostream>
#include <string>
#include "Trie.h"

int main() {

    std::string cmdLine;
    Trie trie;

    //loop waits for user input
    while (1) {
        std::getline(std::cin, cmdLine);

        int pos = cmdLine.find(' ');
        std::string command = cmdLine.substr(0, pos);

        //Insert
        if (command == "i") {
            std::string word = cmdLine.substr(2, cmdLine.length());

            //records longest word
            if (word.length() > trie.getBiggestWord()) {
                trie.setBiggestWord(word.length());
            }

            //Checking for illegal characters
            if (Trie::invalidInput(word)) {
                std::cout << "illegal argument" << std::endl;
            }
            //output failure if entire word was there
            else if (trie.searchWord(trie.getRoot(), word, 0)) {
                std::cout << "failure" << std::endl;
            }
            //otherwise, insert word normally
            else {
                trie.insertWord(trie.getRoot(), word, 0);
                std::cout << "success" << std::endl;
            }
        }

        //Erase
        if (command == "e") {
            std::string word = cmdLine.substr(2, cmdLine.length());

            //Checking for illegal characters
            if (Trie::invalidInput(word)) {
                std::cout << "illegal argument" << std::endl;
            }
            //output failure if word not there or trie is empty
            else if (!trie.searchWord(trie.getRoot(), word, 0) or trie.empty()) {
                std::cout << "failure" << std::endl;
            }
            //otherwise, delete word normally
            else {
                trie.eraseWord(trie.getRoot(), word, 0);
                std::cout << "success" << std::endl;
            }
        }

        //Search
        if (command == "s") {
            std::string word = cmdLine.substr(2, cmdLine.length());

            //Checking for illegal characters
            if (Trie::invalidInput(word)) {
                std::cout << "illegal argument" << std::endl;
            }
            //found if search returns true.
            else if (trie.searchWord(trie.getRoot(), word, 0)) {
                std::cout << "found " << word << std::endl;
            }
            //otherwise, word does not exist
            else {
                std::cout << "not found" << std::endl;
            }
        }

        //Cout words alphabetically
        if (command == "print") {
            if (!trie.empty()) {
                trie.setwConcat("");
                std::string wConcat[trie.getBiggestWord()];
                trie.print(trie.getRoot(), wConcat, 0);
                std::cout << trie.getwConcat().substr(0, trie.getwConcat().length() - 1) << std::endl;
            }
        }

        //gives word suggestions based on input if prefix is found
        if (command == "autocomplete") {
            std::string word = cmdLine.substr(13, cmdLine.length() - 14);

            if (trie.searchWordAC(trie.getRoot(), word, 0)) {
                trie.setwConcat("");
                trie.autoComplete(trie.getRoot(), word, 0);
            }
        }

        //is empty if 1, else 0
        if (command == "empty") {
            if (trie.empty()) {
                std::cout << "empty 1" << std::endl;
            }
            else {
                std::cout << "empty 0" << std::endl;
            }
        }

        //removes all words from tree
        if (command == "clear") {
            trie.clear(trie.getRoot());
            std::cout << "success" << std::endl;
        }

        //returns amount of words in trie
        if (command == "size") {
            std::cout << "number of words is " << trie.size() << std::endl;
        }

        //ends program
        if (command == "exit") {
            break;
        }
    }
    return 0;
}
