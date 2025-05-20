#include "Node.h"

// Constructor
Node::Node(const std::string& class_label)
    : classification(class_label), terminalFlag(false) {}

// Destructor
Node::~Node() {
    for (Node* child : children) {
        delete child;
    }
}

// Accessor for classification
const std::string& Node::getClassification() const {
    return classification;
}

// Delete a child from parent node
void Node::removeChild(Node* child) {
    for (int i = 0; i < children.size(); ++i) {
        if (children[i] == child) {
            children.erase(children.begin() + i);
            break;  // Exit the loop once the child is removed
        }
    }
}

// Accessor for children
std::vector<Node*>& Node::getChildren() {
    return children;
}

// Add a child node
void Node::addChild(Node* child) {
    children.push_back(child);
}

// Check if the node is terminal
bool Node::isTerminal() const {
    return terminalFlag;
}

// Set node as terminal
void Node::setTerminal(bool is_terminal) {
    terminalFlag = is_terminal;
}

// Get number of children
int Node::getNumChildren() const {
    return children.size();
}
