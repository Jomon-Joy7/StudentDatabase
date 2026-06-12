#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;
//=========LOAD STUDENT=============
void loadStudents(Student students[], int& count)
{
    ifstream input("Students90.txt");

    if (!input)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    count = 0;

    while (count < STUDENT_MAX)
    {
        input >> students[count].firstName
            >> students[count].lastName
            >> students[count].id;

        if (input.fail())
            break;

        for (int i = 0; i < NUM_ASSIGNMENTS; i++)
        {
            input >> students[count].assignments[i];
        }

        input >> students[count].average;

        for (int i = 0; i < NUM_COURSES; i++)
        {
            input >> students[count].courses[i];
        }

        count++;
    }

    input.close();
}

// ================= DISPLAY =================
void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].assignments[j] << "\t";

        cout << students[i].average << "\t";

        for (int j = 0; j < NUM_COURSES; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
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

