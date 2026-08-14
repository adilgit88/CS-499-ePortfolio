//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Adil
// Course      : CS 300 - Data Structures and Algorithms
// Description : ABCU Advising Assistance Program
//               Reads course data from a CSV file into a Binary Search Tree,
//               then supports alphanumeric course listing and individual
//               course lookups with prerequisites.
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;
    Node* insertNode(Node* node, Course course);
    void inOrder(Node* node) const;
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(Course course);
    void printAlphanumericList() const;
    Course* search(const string& courseNumber);
};

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

Node* BinarySearchTree::insertNode(Node* node, Course course) {
    if (node == nullptr) {
        return new Node(course);
    }
    if (course.courseNumber < node->course.courseNumber) {
        node->left = insertNode(node->left, course);
    }
    else if (course.courseNumber > node->course.courseNumber) {
        node->right = insertNode(node->right, course);
    }
    return node;
}

void BinarySearchTree::insert(Course course) {
    root = insertNode(root, course);
}

void BinarySearchTree::inOrder(Node* node) const {
    if (node == nullptr) return;
    inOrder(node->left);
    cout << node->course.courseNumber << ", " << node->course.name << endl;
    inOrder(node->right);
}

void BinarySearchTree::printAlphanumericList() const {
    cout << "\nHere is a sample schedule:\n" << endl;
    inOrder(root);
    cout << endl;
}

Course* BinarySearchTree::search(const string& courseNumber) {
    Node* current = root;
    while (current != nullptr) {
        if (courseNumber == current->course.courseNumber) {
            return &current->course;
        }
        else if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

bool loadCourses(const string& filename, BinarySearchTree& bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'. "
            << "Please check the filename and try again." << endl;
        return false;
    }

    vector<string> validCourseNumbers;
    vector<vector<string>> rows;

    string line;
    int lineNum = 0;
    while (getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty()) continue;

        istringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2 || tokens[0].empty() || tokens[1].empty()) {
            cout << "Warning: Line " << lineNum
                << " is malformed and will be skipped." << endl;
            continue;
        }

        validCourseNumbers.push_back(toUpperCase(tokens[0]));
        rows.push_back(tokens);
    }
    file.close();

    if (rows.empty()) {
        cout << "Error: No valid course data found in '" << filename << "'." << endl;
        return false;
    }

    int loaded = 0;
    for (const auto& tokens : rows) {
        Course course;
        course.courseNumber = toUpperCase(tokens[0]);
        course.name = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            string prereq = toUpperCase(tokens[i]);
            if (prereq.empty()) continue;

            bool found = false;
            for (const auto& num : validCourseNumbers) {
                if (num == prereq) { found = true; break; }
            }
            if (found) {
                course.prerequisites.push_back(prereq);
            }
            else {
                cout << "Warning: Prerequisite '" << prereq
                    << "' for course '" << course.courseNumber
                    << "' is not in the course list and will be skipped." << endl;
            }
        }

        bst.insert(course);
        ++loaded;
    }

    cout << loaded << " course(s) loaded successfully." << endl;
    return true;
}

void printCourseList(const BinarySearchTree& bst, bool dataLoaded) {
    if (!dataLoaded) {
        cout << "Please load the data structure first (Option 1)." << endl;
        return;
    }
    bst.printAlphanumericList();
}

void printCourseInfo(BinarySearchTree& bst, bool dataLoaded) {
    if (!dataLoaded) {
        cout << "Please load the data structure first (Option 1)." << endl;
        return;
    }

    string input;
    cout << "What course do you want to know about? ";
    cin >> input;

    string courseNumber = toUpperCase(input);
    Course* course = bst.search(courseNumber);

    if (course == nullptr) {
        cout << "Course '" << courseNumber << "' not found." << endl;
        return;
    }

    cout << course->courseNumber << ", " << course->name << endl;

    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course->prerequisites.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << course->prerequisites[i];
        }
        cout << endl;
    }
}

int main() {
    BinarySearchTree bst;
    bool dataLoaded = false;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << "\n   1. Load Data Structure." << endl;
        cout << "   2. Print Course List." << endl;
        cout << "   3. Print Course." << endl;
        cout << "   9. Exit" << endl;
        cout << "\nWhat would you like to do? ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
        case 1: {
            string filename;
            cout << "Enter the file name to load: ";
            cin >> filename;

            bst.~BinarySearchTree();
            new (&bst) BinarySearchTree();
            dataLoaded = false;

            dataLoaded = loadCourses(filename, bst);
            break;
        }
        case 2:
            printCourseList(bst, dataLoaded);
            break;

        case 3:
            printCourseInfo(bst, dataLoaded);
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
