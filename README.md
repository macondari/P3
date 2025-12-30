# Project 3 - Trie Class Design and Runtime Overview

## Class Design

### Node Class
- **Private variables:**
  - `classification` (string): Label for this node.
  - `children` (vector<Node*>): List of child nodes, dynamically sized.
  - `terminalFlag` (bool): Marks if the node ends a classification path.
  
- **Purpose:**  
  Represents a single node in the trie. Manages its label, children, and terminal status.

- **Key methods:**  
  - Getters: `getClassification()`, `getChildren()`, `isTerminal()`, `getNumChildren()`  
  - Modifiers: `addChild()`, `removeChild()`, `setTerminal()`  
  - Destructor cleans up child nodes to prevent memory leaks.

---

### Trie Class
- **Private variables:**  
  - `root` (Node*): Root node of the trie.  
  - `classificationCount` (int): Number of classifications stored.

- **Private methods:**  
  - `DFS_PrintPaths`: Recursively prints all classification paths.  
  - `removeSingleLeadingSpace`: Removes leading spaces in input.  
  - `containsUppercase`: Checks for uppercase letters (used for input validation).

- **Public methods:**  
  - `Load`: Loads classification paths from strings.  
  - `Insert`: Adds new classifications, rejects invalid inputs.  
  - `Erase`: Removes classifications safely, updating the trie structure.  
  - `PrintAllPaths`: Prints all stored classification paths.  
  - `Classify`: Matches input against classifications and prints results.  
  - Utilities: `Clear`, `Size`, `Empty`.

- **Design notes:**  
  - String splitting done internally for encapsulation.  
  - DFS used for printing to keep memory use low.  
  - Parent nodes marked terminal if they lose all children after erase.

---

## Runtime Summary

| Operation   | Complexity  | Notes                                           |
|-------------|-------------|------------------------------------------------|
| **PRINT**   | O(n)        | n = number of classifications (DFS traversal)  |
| **INSERT**  | O(m)        | m = labels in classification; children capped  |
| **EMPTY**   | O(1)        | Checks if trie has children                      |
| **SIZE**    | O(1)        | Prints classification count                      |
| **CLEAR**   | O(N)        | N = total nodes; deletes all nodes              |
| **CLASSIFY**| O(m)        | m = classification length; limited children     |
| **ERASE**   | O(m)        | Traverses and removes classification safely     |

---

## Summary

This trie efficiently stores hierarchical classifications with controlled insertion, deletion, and querying. It ensures memory safety, input validation, and uses simple, clear recursion for printing all classification paths.
