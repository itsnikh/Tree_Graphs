# Tree and Graphs
>> Implementation of different Tree and Graphs.

>> Here, In this Repository, We have implemented Insert/Delete/Search Methods in a Binary Search Tree, Insert/Search in AVL and RED BLACK Tree.

>> Also, Prims Algorithm for Minimum Spanning Tree and Dijkstra's Algorithm for finding the Single Source Shortest Path in the Graph.

# Execution Procedure
>> In each Method, there are 3 folders, namely,

            include : Contains the Header .h file which needs to be included in the .c files.
            src     : Contains the source Code for each method being implemented.
            make    : Contains the makefile and the make library files.
  
>> To make the Executable:

            1. Go inside the make folder.
            2. Open terminal form this folder.
            3. Run the make command to create the executable.

# Implementations of Trees
>> This is a menu driven program. The menu apprears as follows:

                                    ---MENU---
                        1. Insert Node
                        2. Search Node
                        3. Display Tree
                        0. Exit
                        
                        Enter your choice: 

>> In the src of the Trees each method has the following functions:

            insert_tree(void *, int) // Declaration to receive tree in (void *) format and int to get the data which needs to be inserted.
            search_tree(void *, int) // Declaration to receive tree in (void *) format and int to get the data which needs to be searched.
            display()                // Function will display the tree whenever called.
            
