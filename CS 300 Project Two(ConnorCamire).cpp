// These are all the nessary includes for the program to function
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;  // utilized for inputs and outputs 

struct Course {  // This is a Structure that holds all information that will be used for the courses
    string courseNumber; // Course identifying key  
    string courseTitle;
    vector<string> prerequisites;
};

unordered_map<string, Course> courseTable; // this is the hash table that will store the info from the CSV file

void LoadFileData(const string& fileName) { // This function will load the data from the CSV file into the hash table
    ifstream file(fileName); // opens  the file based on fileName's value 

    if (!file.is_open()) { // cheaks if the file could not be open 
        cout << "Error: could not open file " << fileName << endl; // if the file could not be found 
        return;
    }

    courseTable.clear(); // clears the hasg table to stop loading multiple files at once

    string line; // varible line
    int courseCount = 0; // counts number of courses 

    while (getline(file, line)) {  // reads each line
        stringstream ss(line); 
        string token;
        Course course;

        getline(ss, token, ',');  // ss short hand for string stream and token holds the lines information ',' is what will be seperated 
        course.courseNumber = token; // gets the course number

        getline(ss, token, ','); // ss short hand for string stream and token holds the lines information ',' is what will be seperated 
        course.courseTitle = token; // gets the course title

        while (getline(ss, token, ',')) { // ss short hand for string stream and token holds the lines information ',' is what will be seperated  
            if (!token.empty()) { 
                course.prerequisites.push_back(token); // used to add prerequisites to the back of the list
            }
        }

        courseTable[course.courseNumber] = course; // this addes the course to the hash table
        ++courseCount; // Adds to the total count
    }

    file.close(); // close the file
    cout << "Loaded " << courseCount << " courses into the table.\n"; // shows how many courses were added to the hash table 
}

void PrintCourses() {  // prints each of the courses from the Hash table
    if (courseTable.empty()) {  // checks if the table is empty 
        cout << "No courses loaded. Please load a file first.\n";
        return;
    }

    vector<Course> courseList;  // makes a vector to hold the information from the hash table since we can not order one. 

    for (const auto& pair : courseTable) { // copys the courses from hash tabkes
        courseList.push_back(pair.second);
    }

    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) { // takes from the hash table and adds them to vector
        return a.courseNumber < b.courseNumber;
    });

    for (const Course& course : courseList) { // This prints each of the courses 
        cout << course.courseNumber << ", " << course.courseTitle << endl; 

        if (!course.prerequisites.empty()) {
            cout << "  Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i]; // This prints the prerequisits
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

void PrintSearchedCourse() {  // lets the user search for a course by searching for a course number 
    if (courseTable.empty()) { // checks if courses have been loaded
        cout << "No courses loaded. Please load a file first.\n";
        return;
    }

    string courseNumber;  // this will hold the course ID
    cout << "Enter the course number (example, CSCI101): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove any new lines 
    getline(cin, courseNumber); // Reads the line

    auto it = courseTable.find(courseNumber); // searches from the course number from course table 
    if (it == courseTable.end()) {
        cout << "Course not found.\n";
        return;
    }

    Course course = it->second; // gets the course from the table

    cout << course.courseNumber << ", " << course.courseTitle << endl;

    if (course.prerequisites.empty()) { // if the course has no prerequisites
        cout << "Prerequisites: None\n";
    } else {
        cout << "Prerequisites: ";
        for (const string& prereq : course.prerequisites) { // if the course has prerequisites
            cout << prereq << " ";
        }
        cout << "\n";
    }
}

int main() { // The maine function handles the menu
    int choice = 0; // used for the choice 

    while (choice != 9) { // 9 is used to exit the loop
        cout << " 1: Load data from file.\n";
        cout << " 2: Print sorted list.\n";
        cout << " 3: Search for prerequisites by course number.\n";
        cout << " 9: Exit\n";
        cout << "Please Enter a number.\n";
        cin >> choice;

        switch (choice) {
        case 1: {    // get a file name from the user, and calls the load function passing the file name 
            string fileName;
            cout << "Enter the file name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, fileName);
            LoadFileData(fileName);
            break;
        }
        case 2:
            PrintCourses();  // calls the print courses function
            break;
        case 3:
            PrintSearchedCourse(); // calls the search and print function 
            break;
        case 9:
            cout << "Exiting program...\n";
            break; // ends the program
        default:
            cout << "Please enter a valid number, try again \n";
            cin.clear(); // clears the error flag when a incorrect input is given
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove the input that causes the error
            break; 
        }
    }

    return 0;
}
