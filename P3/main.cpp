#include "ece250_socket.h"
#include <iostream>
#include <fstream>
#include <sstream> // New include for stringstream
#include <string>
#include "Trie.h"

using namespace std;

int main() {
    string cmd;
    Trie trie;  // Create an instance of the Trie class

    while (cin >> cmd) 
    {
        if (cmd == "LOAD") 
		  {
            std::string filename;
            std::cin >> filename;  // Read the filename to load  

            std::ifstream file(filename);  // Open the file
            std::string line;

            while (std::getline(file, line)) 
			      {  // Read each line from the file
                trie.Load(line);  // Call Load method of the Trie to process the line
            }

            std::cout << "success" << std::endl; // Indicate success after processing the line
            file.close();  // Close the file
        }
        
        if (cmd == "INSERT")
     
          {
            std::string classification;
            
            std::getline(std::cin, classification);  // Read the full line of classification input
      
            trie.Insert(classification);
        }
        if (cmd == "CLASSIFY")
     
          {
            std::string input;
            
            std::getline(std::cin, input);  // Read the full line of classification input
      
            trie.Classify(input);
              
		      }
        if (cmd == "ERASE")
     
          {
            std::string classification;
            
            std::getline(std::cin, classification);  // Read the full line of classification input
      
            trie.Erase(classification);
		      }
        if (cmd == "PRINT")
     
          {
            trie.PrintAllPaths();
		      }
        if (cmd == "CLEAR")
     
          {
            trie.Clear();
		      }
        if (cmd == "SIZE")
     
          {
            trie.Size();
		      }
          if (cmd == "EMPTY")
     
          {
            // CALL DESTRUCTORS AND CLEAR MEMORY
            trie.Empty();
		      }      
        if (cmd == "EXIT")
     
          {
            // CALL DESTRUCTORS AND CLEAR MEMORY
            
            return 0;
		      }
        
    }
    


    return 0;
}
