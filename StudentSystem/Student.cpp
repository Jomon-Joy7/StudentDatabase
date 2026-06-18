#include "Student.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//=========LOAD STUDENT=============
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
void searchByCourse(Student students[], int count)
{
    string course;

    cout << "Enter Course: ";
    cin >> course;

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < NUM_COURSES; j++)
        {
            if (students[i].courses[j] == course)
            {
                cout << students[i].id << " "
                    << students[i].firstName << " "
                    << students[i].lastName << endl;

                break;
            }
        }
    }
}

//============SHOW ASSIGNMENT AVERAGE=============
void showAssignmentAverage(Student students[], int count)
{
    for (int a = 0; a < NUM_ASSIGNMENTS; a++)
    {
        double sum = 0;

        for (int i = 0; i < count; i++)
        {
            sum += students[i].assignments[a];
        }

        cout << "A" << a + 1
            << ": "
            << sum / count
            << endl;
    }
}

//===========SHOW HARDEST ASSIGNMENT===========
void showHardestAssignment(Student students[], int count)
{
    double averages[NUM_ASSIGNMENTS];

    for (int a = 0; a < NUM_ASSIGNMENTS; a++)
    {
        double sum = 0;

        for (int i = 0; i < count; i++)
        {
            sum += students[i].assignments[a];
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
void courseEnrollment(Student students[], int count)
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

        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < NUM_COURSES; j++)
            {
                if (students[i].courses[j] == courseList[c])
                {
                    total++;
                }
            }
        }

        cout << courseList[c]
            << ": "
            << total
            << endl;
    }
}

//=============AT RISK STUDENTS=============
void atRiskStudents(Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        bool lowMark = false;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            if (students[i].assignments[j] < 50)
            {
                lowMark = true;
            }
        }

        if (lowMark &&
            students[i].average >= 50 &&
            students[i].average <= 59)
        {
            cout << students[i].id << " "
                << students[i].firstName << " "
                << students[i].lastName << " "
                << students[i].average
                << endl;
        }
    }
}

//==========SORT BY AVERAGE===============
void sortByAverage(Student students[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (students[j].average > students[i].average)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

//============ADD STUDENT==========

void addStudent(Student students[], int& count)
{
    if (count >= STUDENT_MAX)
    {
        cout << "Database Full!" << endl;
        return;
    }

    cout << "First Name: ";
    cin >> students[count].firstName;

    cout << "Last Name: ";
    cin >> students[count].lastName;

    cout << "ID: ";
    cin >> students[count].id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++)
    {
        cout << "Assignment " << i + 1 << ": ";
        cin >> students[count].assignments[i];
    }

    for (int i = 0; i < NUM_COURSES; i++)
    {
        cout << "Course " << i + 1 << ": ";
        cin >> students[count].courses[i];
    }

    calculateAverage(&students[count]);

    count++;

    cout << "Student Added!" << endl;
}

//=============SAVE STUDENTS=============
void saveStudents(Student students[], int count)
{
    ofstream output("Students90.txt");

    for (int i = 0; i < count; i++)
    {
        output << students[i].firstName << " "
            << students[i].lastName << " "
            << students[i].id << " ";

        // assignments
        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        {
            output << students[i].assignments[j] << " ";
        }

        output << students[i].average << " ";

        // courses
        for (int j = 0; j < NUM_COURSES; j++)
        {
            output << students[i].courses[j] << " ";
        }

        output << endl;
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
void calculateAllAverages(Student students[], int count)
{
    for (int i = 0; i < count; i++)
    {
        calculateAverage(&students[i]);
    }
}

