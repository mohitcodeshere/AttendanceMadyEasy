#include <iostream> //contains definitions to object like cout, cin etc
#include <fstream> //to create files, read, and store information in them
#include <conio.h> //to hold the screen
#include <iomanip> // for manipulators
#include <cstring> //to manipulate strings and arrays
#define STUDENT_LENGTH 5
using namespace std;
//making a class here
class student
{
    int rollNo;
    char name[20];
};
class date
{
public:
    char date[12]; //array size 12 because a date can't be longer than this
    bool student[STUDENT_LENGTH]; //we have already defined the length (chance as per the requirements)
};
bool attendenceValidation(char choice) //these are just validations
{
    if (choice == 'P' || choice == 'p' || choice == 'A' || choice == 'a')
        return true;
    else
    {
        return false;
    }
}
void enter()
{
    date d;
    cout << "Enter date in the format DD/MM/YYYY\n";
    cin >> d.date;

    char choice;
    cout << "Enter P for present and A for absent\n";
    for (int i = 0; i < STUDENT_LENGTH; i++)
    {
        cout << "Enter Attendence of Rollno " << i + 1 << " : ";
        cin >> choice;
        while (!attendenceValidation(choice)) //validation to mark Present and Absent only, nothing else
        {
            cout << "Enter Attendence Again : ";
            cin >> choice;
        }
        if (choice == 'P' || choice == 'p')
        {
            d.student[i] = true;
        }
        else
            d.student[i] = false;
    }
    //database file named with extension .db
    ofstream file("dates.db", ios::binary | ios::app); //database file named with extension .db
    file.write((char *)&d, sizeof(d));
    file.close();
}
void view() //to see the records
{
    date d;
    int i = 0;
    ifstream file("dates.db", ios::binary);
    cout << setw(12) << "";
    for (int i = 0; i < STUDENT_LENGTH; i++)
    {
        cout << "Roll " << i + 1 << "  ";
    }
    cout << "\n";
    while (file.read((char *)&d, sizeof(d))) //reading from the file
    {
        cout << setw(10) << d.date; 
        for (int i = 0; i < STUDENT_LENGTH; i++)
        {
            if (d.student[i] == true)
                cout << setw(8) << "P"; //using manipulators to show the results better on the screen
            else
                cout << setw(8) << "A";
        }
        cout << '\n';
    }
    file.close();
}
void modify()
{
    date d;
    int i = 0;
    int roll, index;
    bool found = false;
    char dte[12]; //to modify the attendance
    char choice;
    cout << "Enter the date : ";
    cin >> dte;

    fstream file("dates.db", ios::out | ios::in | ios::ate | ios::binary);
    file.seekg(0);
    while (file.read((char *)&d, sizeof(d)))
    {
        if (strcmp(dte, d.date) == 0)
        {
            index = file.tellg();
            found = true;
            cout << "Enter the roll no to change the attendance :";
            cin >> roll;
            cout << "Enter the Revised Attendence of Rollno " << roll << " : ";
            cin >> choice;
            while (!attendenceValidation(choice)) //again validations to check the choice, if it is as per our requirement or not
            {
                cout << "Enter Attendence Again : ";
                cin >> choice;
            }
            if (choice == 'P' || choice == 'p')
            {
                d.student[roll - 1] = true;
            }
            else
                d.student[roll - 1] = false;
        }
    }
    if (found == false)
    {
        cout << "DATE NOT FOUND !!!\n"; 
    }
    else
    {

        if (file.fail())
            file.clear();
        file.seekg(index - sizeof(d), ios::beg); //using .seek here to set the position of the next character 
        file.write((char *)&d, sizeof(d)); //writing into the file
        cout << "Attendence Updated Sucessfully\n";
    }
    getch();
    file.close();
}
void calculate()
{

    int roll, present = 0, total = 0;
    cout << "Enter the roll no :";
    cin >> roll;
    if (roll < 1 || roll > STUDENT_LENGTH)
    {
        cout << "Roll no not present";
    }
    else
    {
        float per;
        date d;
        ifstream file("dates.db", ios::binary);
        while (file.read((char *)&d, sizeof(d)))
        {
            total++;

            if (d.student[roll - 1] == true)
                present++;
        }
        file.close();
        per = (float(present) / total) * 100;
        if (per < 75 && per > 65) //validations to check the attendance
        {
            cout << "Student ATTENDANCE is between 65-75:" << per << "%" << endl
                 << endl;
        }
        if (per < 65)
        {

            cout << "Student ATTENDANCE is Very Much Low:" << per << "%" << endl
                 << endl;
        }
        if (per > 75)
        {
            cout << "Good Attendace:" << per << "%" << endl
                 << endl;
        }
    }
    getch();
}
void login() //login window for authentication
{
    char username[30];
    char password[30];
    int loop = 1;
    do
    {
        cout << "Username : " << endl;
        cin >> username;
        cout << "Password : " << endl;
        cin >> password;
        if (strcmp(username, "admin") == 0 && strcmp(password, "pass") == 0)
        {
            cout << ("Success : Logging you in...");
            loop = 0;
        }
        else
        {

            cout << "Error : Credentials don't match ";
        }
        getch();
    } while (loop == 1); //END OF ELSE
}

int main() //list of menu items here
{
    login();

    while (1)
    {
        system("cls");
        cout << "1. Mark attendence\n";
        cout << "2. View attendence\n";
        cout << "3. Calculate attendence\n";
        cout << "4. Modify attendence\n";
        cout << "5. Exit\n";
        cout << "\nEnter your Choice : ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            enter();
            break;
        case 2:
            view();
            getch();
            break;
        case 3:
            calculate();
            break;
        case 4:
            modify();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid Choice";
        }
    }
}
