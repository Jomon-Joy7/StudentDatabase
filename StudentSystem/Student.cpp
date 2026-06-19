#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

//=========LOAD STUDENT============

void loadStudents(StudentNode*& head)
{
    ifstream file("Students90.txt");

    Student tempStudent;

    while (file >> tempStudent.firstName
        >> tempStudent.lastName
        >> tempStudent.id)
    {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            file >> tempStudent.assignments[j];

        file >> tempStudent.average;

        for (int j = 0; j < NUM_COURSES; j++)
            file >> tempStudent.courses[j];

        StudentNode* newNode = new StudentNode();
        
        newNode->data = tempStudent;

        newNode->next = head;

        head = newNode;
    }

    file.close();
}

// ================= DISPLAY =================

void displayStudents(StudentNode* head)
{
    cout << "\n"
        << setw(8) << "ID"
        << setw(15) << "LName"
        << setw(15) << "FName";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << setw(6) << ("A" + to_string(j + 1));

    cout << setw(8) << "AVG"
        << setw(10) << "C1"
        << setw(10) << "C2"
        << setw(10) << "C3"
        << endl;

    StudentNode* current = head;

    while (current != nullptr)
    {
        cout << setw(8) << current->data.id
            << setw(15) << current->data.lastName
            << setw(15) << current->data.firstName;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << setw(6) << current->data.assignments[j];

        cout << setw(8) << current->data.average;

        for (int j = 0; j < NUM_COURSES; j++)
            cout << setw(10) << current->data.courses[j];

        cout << endl;

        current = current->next;
    }
}


//===========SEARCH BY COURSE================
void searchByCourse(StudentNode* head)
{
    string course;

    cout << "Enter Course: ";
    cin >> course;

    StudentNode* current = head;

    while (current != nullptr)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (current->data.courses[j] == course)
            {
                cout << current->data.id << " "
                    << current->data.firstName << " "
                    << current->data.lastName << endl;
                break;
            }
        }

        current = current->next;
    }
}

//============SHOW ASSIGNMENT AVERAGE=============
void showAssignmentAverage(StudentNode* head)
{
    for (int a = 0; a < NUM_ASSIGNMENTS; a++)
    {
        double sum = 0;
        int count = 0;

        StudentNode* current = head;

        while (current != nullptr)
        {
            sum += current->data.assignments[a];
            count++;

            current = current->next;
        }

        cout << "A" << a + 1
            << ": "
            << sum / count
            << endl;
    }
}

//===========SHOW HARDEST ASSIGNMENT===========
void showHardestAssignment(StudentNode* head)
{
    double averages[NUM_ASSIGNMENTS];

    for (int a = 0; a < NUM_ASSIGNMENTS; a++)
    {
        double sum = 0;
        int count = 0;

        StudentNode* current = head;

        while (current != nullptr)
        {
            sum += current->data.assignments[a];
            count++;

            current = current->next;
        }

        averages[a] = sum / count;
    }

    int hardest = 0;

    for (int i = 1; i < NUM_ASSIGNMENTS; i++)
    {
        if (averages[i] < averages[hardest])
        {
            hardest = i;
        }
    }

    cout << "Hardest Assignment: A"
        << hardest + 1
        << " ("
        << averages[hardest]
        << ")"
        << endl;
}


//===========COURSE ENROLLMENT==============
void courseEnrollment(StudentNode* head)
{
    string courseList[] =
    {
        "COMP220",
        "MATH102",
        "STAT110",
        "HIST210",
        "ENGL150",
        "BIOL120",
        "CSCI101"
    };

    for (int c = 0; c < 7; c++)
    {
        int total = 0;

        StudentNode* current = head;

        while (current != nullptr)
        {
            for (int j = 0; j < NUM_COURSES; j++)
            {
                if (current->data.courses[j] == courseList[c])
                {
                    total++;
                }
            }

            current = current->next;
        }

        cout << courseList[c]
            << ": "
            << total
            << endl;
    }
}

//=============AT RISK STUDENTS=============

void atRiskStudents(StudentNode* head)
{
    StudentNode* current = head;

    while (current != nullptr)
    {
        bool lowMark = false;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            if (current->data.assignments[j] < 50)
            {
                lowMark = true;
            }
        }

        if (lowMark &&
            current->data.average >= 50 &&
            current->data.average <= 59)
        {
            cout << current->data.id << " "
                << current->data.firstName << " "
                << current->data.lastName << " "
                << current->data.average
                << endl;
        }

        current = current->next;
    }
}

//==========SORT BY AVERAGE===============

void sortByAverage(StudentNode* head)
{
    StudentNode* current;
    StudentNode* nextNode;

    for (current = head; current != nullptr; current = current->next)
    {
        for (nextNode = current->next;
            nextNode != nullptr;
            nextNode = nextNode->next)
        {
            if (nextNode->data.average > current->data.average)
            {
                Student temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
        }
    }
}

//============ADD STUDENT==========

void addStudent(StudentNode*& head)
{
    StudentNode* newNode = new StudentNode();

    cout << "First Name: ";
    cin >> newNode->data.firstName;

    cout << "Last Name: ";
    cin >> newNode->data.lastName;

    cout << "ID: ";
    cin >> newNode->data.id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Assignment " << i + 1 << ": ";
        cin >> newNode->data.assignments[i];
    }

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Course " << i + 1 << ": ";
        cin >> newNode->data.courses[i];
    }

    calculateAverage(&newNode->data);

    newNode->next = head;
    head = newNode;

    cout << "Student Added!" << endl;
}

//=============SAVE STUDENTS=============
void saveStudents(StudentNode* head)
{
    ofstream output("Students90.txt");

    StudentNode* current = head;

    while (current != nullptr)
    {
        output << current->data.firstName << " "
            << current->data.lastName << " "
            << current->data.id << " ";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            output << current->data.assignments[j] << " ";
        }

        output << current->data.average << " ";

        for (int j = 0; j < NUM_COURSES; j++)
        {
            output << current->data.courses[j] << " ";
        }

        output << endl;

        current = current->next;
    }

    output.close();

    cout << "Data saved successfully!" << endl;
}

//=============CALCULATE AVERAGE=============
void calculateAverage(Student* s)
{
    double sum = 0;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        sum += s->assignments[i];
    }

    s->average = sum / NUM_ASSIGNMENTS;
}

//=============CALCULATE ALL AVERAGE==========

void calculateAllAverages(StudentNode* head)
{
    StudentNode* current = head;

    while (current != nullptr)
    {
        calculateAverage(&current->data);
        current = current->next;
    }
}   

//===============DELETE LIST=============
void deleteList(StudentNode*& head)
{
    while (head != nullptr)
    {
        StudentNode* temp = head;

        head = head->next;

        delete temp;
    }
}
