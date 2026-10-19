//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Adalberto Flores
// Version     : 1.0
// Description : CS 300 Project Two - ABCU Course Advising Assistance Program
//               Implemented using a Binary Search Tree (BST)
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Data Structure Definitions
// ============================================================================

/**
 * Course structure holding the course number, title, and prerequisites.
 */
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

/**
 * Node structure for the Binary Search Tree.
 */
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Overloaded constructor initializing node with course data
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

/**
 * Binary Search Tree class for storing and managing Course objects.
 */
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* currentNode, Course aCourse);
    void inOrder(Node* node);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course aCourse);
    void PrintSampleCourseList();
    Course Search(string courseNumber);
    bool IsEmpty();
};

/**
 * Default constructor initializing root to nullptr.
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor to free dynamically allocated tree nodes.
 */
BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

/**
 * Recursive post-order helper to delete tree nodes and prevent memory leaks.
 */
void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

/**
 * Checks whether the BST contains any course nodes.
 */
bool BinarySearchTree::IsEmpty() {
    return root == nullptr;
}

/**
 * Insert course into the BST.
 */
void BinarySearchTree::Insert(Course aCourse) {
    if (root == nullptr) {
        root = new Node(aCourse);
    } else {
        this->addNode(root, aCourse);
    }
}

/**
 * Method 1 from Pseudocode: Recursive Node Insertion.
 */
void BinarySearchTree::addNode(Node* currentNode, Course aCourse) {
    // Traverse left if courseNumber is smaller
    if (aCourse.courseNumber.compare(currentNode->course.courseNumber) < 0) {
        if (currentNode->left == nullptr) {
            currentNode->left = new Node(aCourse);
        } else {
            this->addNode(currentNode->left, aCourse);
        }
    }
    // Otherwise traverse right
    else {
        if (currentNode->right == nullptr) {
            currentNode->right = new Node(aCourse);
        } else {
            this->addNode(currentNode->right, aCourse);
        }
    }
}

/**
 * Method 3 from Pseudocode: In-Order Traversal.
 * Prints courses in alphanumeric order.
 */
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        inOrder(node->right);
    }
}

/**
 * Public wrapper for in-order traversal display.
 */
void BinarySearchTree::PrintSampleCourseList() {
    this->inOrder(root);
}

/**
 * Method 4 from Pseudocode: Search Course in BST.
 */
Course BinarySearchTree::Search(string courseNumber) {
    Node* currentNode = root;

    while (currentNode != nullptr) {
        if (currentNode->course.courseNumber.compare(courseNumber) == 0) {
            return currentNode->course;
        } else if (courseNumber.compare(currentNode->course.courseNumber) < 0) {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }
    }

    // Return empty course object if not found
    Course emptyCourse;
    emptyCourse.courseNumber = "";
    emptyCourse.title = "";
    return emptyCourse;
}

// ============================================================================
// Helper Utilities & File Processing
// ============================================================================

/**
 * Trims leading and trailing whitespace and carriage returns (\r).
 */
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

/**
 * Converts string characters to uppercase for case-insensitive course lookups.
 */
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/**
 * Method 5 from Pseudocode: Load Courses & Validate Prerequisites.
 * Implements the two-pass validation algorithm from Project One.
 */
bool loadCourses(string filename, BinarySearchTree* bst) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: File could not be opened: " << filename << endl;
        return false;
    }

    vector<string> validCourseIds;
    vector<string> rawFileLines;
    string line;

    // ------------------------------------------------------------------------
    // Pass 1: Syntax check and collect valid course IDs
    // ------------------------------------------------------------------------
    while (getline(file, line)) {
        string cleanedLine = trim(line);
        if (cleanedLine.empty()) {
            continue;
        }

        stringstream ss(cleanedLine);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            cout << "Error: Line does not have enough parameters: " << cleanedLine << endl;
            continue;
        }

        validCourseIds.push_back(tokens[0]);
        rawFileLines.push_back(cleanedLine);
    }

    file.close();

    // ------------------------------------------------------------------------
    // Pass 2: Verify prerequisites and insert valid courses into the BST
    // ------------------------------------------------------------------------
    for (size_t i = 0; i < rawFileLines.size(); ++i) {
        stringstream ss(rawFileLines[i]);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        Course newCourse;
        newCourse.courseNumber = tokens[0];
        newCourse.title = tokens[1];
        bool isValid = true;

        for (size_t index = 2; index < tokens.size(); ++index) {
            string prereq = tokens[index];
            // Skip empty trailing tokens caused by trailing commas in CSV
            if (prereq.empty()) {
                continue;
            }

            bool prereqFound = false;
            for (size_t j = 0; j < validCourseIds.size(); ++j) {
                if (validCourseIds[j] == prereq) {
                    prereqFound = true;
                    break;
                }
            }

            if (!prereqFound) {
                cout << "Error: Prerequisite " << prereq << " does not exist in file for course "
                     << newCourse.courseNumber << endl;
                isValid = false;
            } else {
                newCourse.prerequisites.push_back(prereq);
            }
        }

        // Only insert if all prerequisites exist; skip otherwise
        if (isValid) {
            bst->Insert(newCourse);
        } else {
            cout << "Skipping course " << newCourse.courseNumber << " due to missing prerequisites." << endl;
        }
    }

    return true;
}

/**
 * Method 6 from Pseudocode: Print Single Course Details.
 */
void printCourseDetails(BinarySearchTree* bst, string courseNumber) {
    Course course = bst->Search(courseNumber);

    if (course.courseNumber.empty()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    cout << course.courseNumber << ", " << course.title << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i + 1 < course.prerequisites.size()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// ============================================================================
// Main Application Routine (Matches Milestone Three Main & Sample Output)
// ============================================================================

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    bool isLoaded = false;
    string inputLine;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl << endl;
        cout << "What would you like to do? ";

        // Read entire user input line to handle spaces safely
        getline(cin, inputLine);
        inputLine = trim(inputLine);

        if (inputLine.empty()) {
            continue;
        }

        // Validate numeric choice
        try {
            choice = stoi(inputLine);
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter the file name to load: ";
            getline(cin, filename);
            filename = trim(filename);
            isLoaded = loadCourses(filename, bst);
            break;
        }
        case 2:
            if (isLoaded && !bst->IsEmpty()) {
                cout << "Here is a sample schedule:" << endl << endl;
                bst->PrintSampleCourseList();
            } else {
                cout << "Please load the course data first." << endl;
            }
            break;

        case 3:
            if (isLoaded && !bst->IsEmpty()) {
                string targetCourse;
                cout << "What course do you want to know about? ";
                getline(cin, targetCourse);
                targetCourse = toUpper(trim(targetCourse));
                printCourseDetails(bst, targetCourse);
            } else {
                cout << "Please load the course data first." << endl;
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << inputLine << " is not a valid option." << endl;
            break;
        }
    }

    // Clean up allocated heap memory
    delete bst;
    return 0;
}