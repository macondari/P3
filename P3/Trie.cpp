#include "Trie.h"

Trie::Trie() {
    root = new Node("");  // Root
    classificationCount = 0;  // Initialize classificationCount to zero
}

Trie::~Trie() 
{
    delete root;
}

Node* Trie::getRoot() const 
{
    return root;
}

void Trie::Load(const std::string& labels) // load strings from a file in main
{
    Node* currentNode = root;// used to traverse trie
    std::istringstream stream(labels);
    std::string label;

    while (std::getline(stream, label, ',')) // splitline
    {
        bool found = false;
        for (Node* child : currentNode->getChildren()) 
        {
            if (child != nullptr && child->getClassification() == label)                 {
                if (currentNode->isTerminal()) 
                {
                    currentNode->setTerminal(false); // undo terminal to prepare to insert another node
                }
                currentNode = child;
                found = true; // set found to true, indicates label in tree
                break;
            }
        }
        if (!found) //if not found means we need to insert
        {
            Node* newChild = new Node(label);
            currentNode->setTerminal(false);
            currentNode->addChild(newChild);
            currentNode = newChild;
            classificationCount += 1;  // Update counter
        }
    }
    currentNode->setTerminal(true);//set very last node of traversal to terminal, edge case if we insert multiple nodes in one loop.
}

void Trie::Insert(std::string& classification) 
{
    try {
        if (containsUppercase(classification)) 
        {
            throw illegal_exception();
        }
        // insertion method follows similar to LOAD above this
        classification = removeSingleLeadingSpace(classification); // remove space
        Node* currentNode = root;
        std::istringstream stream(classification);
        std::string label;
        bool isNewInsertion = false;

        while (std::getline(stream, label, ',')) 
        {
            bool found = false;
            for (Node* child : currentNode->getChildren()) 
            {
                if (child != nullptr && child->getClassification() == label) 
                {
                    if (currentNode->isTerminal()) 
                    {
                        currentNode->setTerminal(false);
                    }
                    currentNode = child;
                    found = true;
                    break;
                }
            }
            if (!found) 
            {
                Node* newChild = new Node(label);// create new child
                currentNode->setTerminal(false);
                currentNode->addChild(newChild);
                currentNode = newChild;
                isNewInsertion = true;
                classificationCount += 1;// update count
            }
        }
        if (isNewInsertion) 
        {
            currentNode->setTerminal(true);
            std::cout << "success" << std::endl; // new insertion print success
        } else {
            std::cout << "failure" << std::endl;// no insetion print failure
        }
    } catch (const illegal_exception& e) 
    {
        std::cout << e.illegal() << std::endl;
    }
}

void Trie::Erase(std::string& classification) 
{
    try {
        if (containsUppercase(classification)) 
        {
            throw illegal_exception();
        }

        Node* currentNode = root;
        Node* parentNode = nullptr;
        //instantiate two pointers for double traversal
        classification = removeSingleLeadingSpace(classification);
        std::istringstream stream(classification);
        std::string label;

        while (std::getline(stream, label, ',')) //splitline 
        {
            bool found = false;
            for (Node* child : currentNode->getChildren()) // check if children match input
            {
                if (child != nullptr && child->getClassification() == label) 
                {
                    parentNode = currentNode;
                    currentNode = child;
                    found = true;// if found a match break the loop
                    break;
                }
            }
            if (!found) 
            {
                std::cout << "failure" << std::endl; // no match found
                return;
            }
        }
/*
CITATION:
This code was modified by chat.openai.com with the prompt:
"Fix my code so it will not cause segfaults anymore."
Chat GPT introduced the use of the 'auto' keyword for iterating
over the children of the parent node, simplifying the code and
reducing the risk of segmentation faults caused by incorrect
pointer handling.
*/
        if (currentNode->isTerminal())  //Check if the currentNode is a terminal node, meaning it marks the end of a classification path.
        {
            if (parentNode != nullptr) 
            {
                auto& children = parentNode->getChildren();
                for (Node*& child : children) 
                {
                    if (child == currentNode) 
                    {
                        parentNode->removeChild(currentNode);
                        break;
                    }
                }
                classificationCount -= 1;
            }

            delete currentNode;
            std::cout << "success" << std::endl;
            if (parentNode && parentNode->getNumChildren() == 0) //If the parent node has no other children after the deletion, mark it as a terminal node to indicate the end of the classification path.
            {
                parentNode->setTerminal(true);
            }
        } else 
        {
            std::cout << "failure" << std::endl;
        }
    } catch (const illegal_exception& e) 
    {
        std::cout << e.illegal() << std::endl;
    }
}

/*
CITATION:
This code was generated by chat.openai.com with the prompt:
"How can I detect if there is a capital letter in a word without 
using the STL?"
The AI tool suggested using ASCII values to check if a character 
is uppercase by comparing it to the range 'A' (65) to 'Z' (90), 
providing a solution that avoids STL usage.
*/

bool Trie::containsUppercase(const std::string& str) // use ascii to check if uppercase
{
    for (char ch : str) //iterate through the string of chars
    {
        if (ch >= 65 && ch <= 90) 
        {
            return true;
        }
    }
    return false;
}

void Trie::Empty() const 
{
    if (root->getNumChildren() == 0) //determine if tree is empty based on size
    {
        std::cout << "empty 1" << std::endl;
    } else {
        std::cout << "empty 0" << std::endl;
    }
}

void Trie::Size() const 
{
    std::cout << "number of classifications is " << classificationCount << std::endl;
}

void Trie::DFS_PrintPaths(Node* node, std::vector<std::string>& path) const 
{
    if (node == nullptr) // Base case; if the node is null, return
    {
        return;
    }

    path.push_back(node->getClassification()); // Add the current nodes classification to the path

    if (node->isTerminal()) 
    {
        std::cout << path[1]; // print first node for formatting, start at index 1 to avoid printing root
        for (size_t i = 2; i < path.size(); ++i) 
        {
            std::cout << "," << path[i];
        }
        std::cout << "_";
    }

    for (Node* child : node->getChildren()) // Recursively call DFS_PrintPaths for each child of the current node
    {
        DFS_PrintPaths(child, path);
    }

    path.pop_back(); // Backtrack by removing from path
}
void Trie::PrintAllPaths() const //function used to start recursive call to DFS_PrintPaths if needed
{
    std::vector<std::string> path;
    if (root->getNumChildren() == 0) 
    {
        std::cout << "trie is empty" << std::endl;
        return;
    }

    DFS_PrintPaths(root, path);
    std::cout << std::endl;
}


void Trie::Clear() 
{
    delete root;//delete root and start over
    root = new Node("");
    classificationCount = 0;
    std::cout << "success" << std::endl;
}

std::string Trie::removeSingleLeadingSpace(const std::string& label) // remove leading space from a label
{
    if (!label.empty() && label[0] == ' ') //check if first index holds a space
    {
        return label.substr(1); // if yes, return substring with everything after space
    }
    return label;
}

void Trie::Classify(std::string& input) 
{
    try {
        Node* currentNode = root;// setup for a trie traversal
        std::vector<std::string> path;
        input = removeSingleLeadingSpace(input);
        if (containsUppercase(input)) 
        {
            throw illegal_exception();
        }

        while (true) // runs until a break, return or throw
        {
            bool found = false;
            std::string labelString = "";// clears label to prepare for new children to be passed to it
            for (Node* child : currentNode->getChildren()) 
            {
                if (child != nullptr) {
                    if (!labelString.empty()) {
                        labelString += ",";
                    }
                    labelString += child->getClassification();// holds classification options to be sent to LLM
                }
            }
            if (containsUppercase(labelString)) // if uppercase return
            {
                throw illegal_exception();
            }
            if (labelString.empty()) // if no children return
            {
                return;
            }

            std::string classificationResult = labelText(input, labelString);// if labelstring is valid, gets sent to LLM
            if (classificationResult.empty()) 
            {
                return;
            }

            for (Node* child : currentNode->getChildren()) 
            {
                if (child != nullptr && child->getClassification() == classificationResult) // if the classification the LLM outputs matches a valid child it gets pushed back onto path
                {
                    currentNode = child;
                    path.push_back(classificationResult);
                    found = true;
                    break;
                }
            }
            if (!found) 
            {
                return;
            }
            if (currentNode->isTerminal()) // loop exits when reach terminal node
            {
                break;
            }
        }

        if (currentNode->isTerminal()) // once we reach terminal node, print classification path
        {
            std::cout << path[0];// print this first for formatting
            for (size_t i = 1; i < path.size(); ++i) 
            {
                std::cout << "," << path[i];
            }
            std::cout << std::endl;
        }
    } catch (const illegal_exception& e) 
    {
        std::cout << e.illegal() << std::endl;
    }
}


