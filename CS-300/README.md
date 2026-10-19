# CS-300: Data Structures and Algorithms
Project Course Advising System - Binary Search Tree and Algorithm Analysis

## Project Summary

For this course, I analyzed data structures and developed a course advising assistance program for ABCU. In Project One, I evaluated the performance and memory tradeoffs of Vectors, Hash Tables, and Binary Search Trees (BST) for handling course catalogs. In Project Two, I implemented the final program in C++ using a Binary Search Tree. The program reads a CSV file containing course numbers, course titles, and prerequisite lists, validates that prerequisites exist within the catalog, stores the courses in a binary search tree, and allows academic advisors to print the full course list in alphanumeric order or search for specific course details.

## Reflection

### Problem Solved Across the Projects
The problem I solved was building an efficient course advising program for academic advisors at ABCU. Advisors needed a reliable way to load course data from a file, view all available courses sorted alphanumerically so students could easily find them, and look up individual courses to see their titles and any required prerequisites. The system also had to validate the input data so that missing course numbers, malformed lines, or invalid prerequisite references would not break the program or mislead an advisor.

### Approaching the Problem and the Importance of Data Structures
I approached the problem by comparing different data structures to see which one best fit the requirements. In Project One, I evaluated vectors, hash tables, and binary search trees:
- Vectors were simple to set up and fast to load, but searching took linear time O(n), and printing courses in alphanumeric order required sorting the entire vector first.
- Hash tables offered near O(1) constant time lookup, but the data remained completely unsorted. Printing courses alphabetically meant copying all entries into an array and sorting them, which used extra time and memory.
- A Binary Search Tree provided a balanced approach. It gave average O(log n) search times and allowed natural in-order traversal (left, root, right) to print all courses in alphabetical order without needing extra sorting steps.

Understanding data structures is important because each structure has specific tradeoffs in memory, search speed, insertion speed, and ordering. Picking the right data structure from the start makes the whole program simpler and more efficient instead of trying to patch around weaknesses later.

### Roadblocks and How I Overcame Them
One roadblock I ran into was parsing the CSV file and validating prerequisites. Some lines had varying numbers of prerequisites, while others could reference course numbers that did not exist in the curriculum. I solved this by using a two-pass approach. In the first pass, I verified the basic formatting of each line and collected all valid course numbers. In the second pass, I verified that every prerequisite listed was actually an existing course before inserting the course into the tree.

Another challenge was managing pointer logic and memory in C++. When inserting nodes recursively, I had to be careful with null checks so the program would not crash when traversing left and right child pointers. I also implemented a recursive post-order destructor (destroyTree) to properly delete dynamically allocated nodes when the program exits, preventing memory leaks.

### Expanding My Approach to Software Design
Working on these projects expanded how I design software by teaching me to think about Big-O complexity and memory usage before writing code. Earlier in my programming experience, I usually picked whatever data structure felt easiest to implement. Now, I consider how the program will scale with larger datasets. I look at whether data needs to be sorted, how often searches will happen compared to insertions, and how much memory pointers or bucket arrays will consume.

I also learned the value of separating data structure logic from the user interface. Keeping the BinarySearchTree class focused only on managing nodes and tree traversal made the menu loop in main() much cleaner and easier to debug.

### Writing Maintainable, Readable, and Adaptable Programs
My work evolved the way I write maintainable and adaptable code in several ways:
- Clear Structure: I defined distinct structs for Course and Node, keeping data attributes separate from tree pointers.
- Modular Functions: I broke complex tasks into small, single-purpose functions like addNode, inOrder, search, and loadCourses.
- Defensive Validation: I added input checks for menu choices and file reading so that invalid user input or broken lines produce helpful messages rather than crashing the program.
- In-Order Traversal: Using recursive in-order traversal kept the printing logic clean and adaptable. If the formatting of the output ever needs to change, it only requires updating the display logic inside inOrder without touching the tree structure itself.
