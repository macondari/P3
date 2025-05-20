#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"
#include "illegal_exception.h"
#include "ece250_socket.h"

class Trie {
private:
    Node* root;               // Root of the trie
    int classificationCount;   // Tracks the number of classifications in the trie
    
    // private member functions
    
    //DFS as a part of printing the tree
    void DFS_PrintPaths(Node* node, std::vector<std::string>& path) const;
    
    // Remove a single leading space from a string
    std::string removeSingleLeadingSpace(const std::string& label);
    
    // Check if a string contains any uppercase letters
    bool containsUppercase(const std::string& str);

public:
    // Constructor
    Trie();

    // Destructor
    ~Trie();

    // Get the root node of the trie
    Node* getRoot() const;

    // Load classifications into the trie
    void Load(const std::string& labels);

    // Insert a new classification into the trie
    void Insert(std::string& classification);

    // Erase a classification from the trie
    void Erase(std::string& classification);

    // Check if the trie is empty
    void Empty() const;

    // Print the number of classifications in the trie
    void Size() const;

    // Print all paths in the trie
    void PrintAllPaths() const;

    // Clear the trie
    void Clear();

    // Tentative classify function
    void Classify(std::string& input);
    
   
};

#endif
