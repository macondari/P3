#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
private:
    std::string classification;  // Classification label for this node
    std::vector<Node*> children; // Vector of child pointers
    bool terminalFlag;           // Flag to indicate if this node is a terminal classification

public:
    // Constructor
    Node(const std::string& class_label);

    // Destructor
    ~Node();

    // Accessor for classification
    const std::string& getClassification() const;

    // Delete a child from parent node
    void removeChild(Node* child);

    // Accessor for children
    std::vector<Node*>& getChildren();

    // Add a child node
    void addChild(Node* child);

    // Check if the node is terminal
    bool isTerminal() const;

    // Set node as terminal
    void setTerminal(bool is_terminal);

    // Get number of children
    int getNumChildren() const;
};

#endif // NODE_H
