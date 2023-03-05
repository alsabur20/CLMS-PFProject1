#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

//////////////////////////////////
// Gloabal Data
string masterUsername = "CLMS"; // Master Username for Admin SignUp
string masterPassword = "CLMS"; // Master Password
bool mainLoop = true;           // mainLoop condition
const int arrSize = 10;         // Array Size
const int membersSize = 10;     // Number of Members of the Library

/////////////////////////////////
// Login and SignIn Data
string userNames[arrSize];     // Usernames
string userPasswords[arrSize]; // Passwords
string roles[arrSize];         // Roles
int userIndex = 0;             // count of users

//////////////////////////////////////////
// Library Data
int counterOfLateBooksOfUser = 0;
int indexbook = 0;                     // count of books
int StudentIndex;                      // Index of student that has logged in
int bookIds[arrSize];                  // Book Ids
string books[arrSize];                 // Book Names
string authors[arrSize];               // Book Authors
string status[arrSize];                // Book Statuses
string genres[arrSize];                // Book Genres
bool isBookIssued[arrSize];            // check if a book is issued
string issuedStudentNames[arrSize];    // Student who have issued the books
string issueDates[arrSize];            // Issue dates of issued books
string dueInDates[arrSize];            // Returning dates of issued books
bool isIssuedBookLate[arrSize];        // check if issued book is late
string studentRollNumber[membersSize]; // RollNumbers of Students
string students[membersSize];          // Members of the Library
string studentsClass[membersSize];     // Classes of Students
int studentIds[membersSize];           // ID of students
int studentIdGenerator = 1;            // automated student id generator
int bookIdGenerator = 1;               // automated book id generator
////////////////////////////////////////////
// Loading and Storing Data into Files
string parseData(string line, int field); //
void loadMembersDataToArrays();           //
void storeMembersDataToFile();            //
void loadBooksDataToArrays();             //
void storeBooksDataToFile();              //
void loadIssuedBooksDataToArrays();       //
void storeIssuedBooksDataToFile();        //

/////////////////////////////////////////////////////
// General Functions Prototypes
void clearScreen();                                                                                        // clears screen and prints header again
void pHeader();                                                                                            // prints header on the screen
void loginScreen();                                                                                        // prints login options
int roleCheck(string username1, string password1);                                                         // returns the user's role index
bool isPresent(string username, string password);                                                          // check if the user has already signed up
void signUp(string username, string password, string role1, string name, string rollnumber, string grade); // proces signup data
int validatedInput(int choice);                                                                            // validates choice
string checkRollNumber(string rollnumber);                                                                 // check if rollnumber already exists
bool checkStudentFromMembers(string stuname);                                                              // check if student is present among members of library
string isNumber(string input);                                                                             // validate number input
string isAlpha(string input);                                                                              // validate strings
string systemDate();                                                                                       // return system date in dd/mm/yyyy format
string parseDate(string Time, int field);                                                                  // parse system date and time to get date only
string changeMonthToNumber(string month);                                                                  // change month to number
int convertDateToDays(string date);                                                                        // covert date to days for calculation
string todayDate = systemDate();                                                                           // return system date
string setcolor(unsigned short color);                                                                     // change color of a specific line
void printBookByIndex(int idx);                                                                            // prints book from an index
void printBookByString(string name);                                                                       // prints book by name,author,status,genre
void halt();                                                                                               // stops and asks for a key to continue

///////////////////////////////////////////////////////////////////////////////////////////////////
// Admin Functions Prototypes
void printAdminMenu();                                                                              //
void addBook();                                                                                     //
void deleteBook(int idx);                                                                           //
void viewBooks();                                                                                   //
void modifyBook(int choice, int idx);                                                               //
void modifyBookSubMenu();                                                                           //
void viewIssuedBooks();                                                                             //
void IssueBook(int idx, string studentName, string dueDate);                                        //
bool issueanceCheck(int idx);                                                                       //
void returnBook(int idx);                                                                           //
bool isLate(string currentDate, string expiryDate);                                                 //
bool checkIfStudentIssuedBook(int index);                                                           //
int returnIndex(string name1);                                                                      //
int returnIndexForIssue(string id);                                                                 //                                                            //
void viewStudents();                                                                                //
void addStudent(string student, string grade, string username, string password, string rollnumber); //
void removeStudent(int index);                                                                      //

//////////////////////////////////////////////////////
// Student Functions Prototypes
void printStuMenu();                            //
void checkStatusSubMenu();                      //
void searchBookSubMenu();                       //
void IssueBookStudent(int idx, string dueDate); //
void countLateBooks();                          //
void viewNotifications();                       //
void checkLateBooks();                          //

/////////////////////////////////////////////////////
// Users Main Function Prototypes
void adminMenu();   // Main handler for the Admin  //
void studentMenu(); // Main handler for the Student//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    loadMembersDataToArrays();
    loadBooksDataToArrays();
    loadIssuedBooksDataToArrays();
    checkLateBooks();
    countLateBooks();
    int choice;
    string masterUser, masterPass, username, password, role1, username1, password1, name, rollnumber, grade;
    while (mainLoop)
    {
        clearScreen();
        loginScreen();
        choice = validatedInput(choice);
        if (choice == 1)
        {
            clearScreen();
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            bool usercheck = isPresent(username, password);
            if (usercheck == 0)
            {
                cout << "Enter Full Name: ";
                name = isAlpha(name);
                cout << "Enter rollnumber: ";
                rollnumber = checkRollNumber(rollnumber);
                cout << "Enter class: ";
                grade = isNumber(grade);
                cout << "Enter role: ";
                cin >> role1;
                if (role1 == "Admin" || role1 == "admin" || role1 == "student" || role1 == "Student")
                {
                    if (role1 == "admin" || role1 == "Admin")
                    {
                        cout << "Enter Master UserName: ";
                        cin >> masterUser;
                        cout << "Enter Master Password: ";
                        cin >> masterPass;
                        if (masterUser == masterUsername && masterPass == masterPassword)
                        {
                            signUp(username, password, role1, name, rollnumber, grade);
                            storeMembersDataToFile();
                            cout << "You have Signed Up Successfully as an Admin!!" << endl;
                        }
                        else
                        {
                            cout << "You do not have access!!" << endl;
                        }
                    }
                    else
                    {
                        signUp(username, password, role1, name, rollnumber, grade);
                        storeMembersDataToFile();
                        cout << "You have Signed Up Successfully as an Student!!" << endl;
                    }
                    halt();
                }
                else
                {
                    cout << "Enter correct role!!" << endl;
                    halt();
                }
            }
            else
            {
                cout << "User already exists!!" << endl;
                cout << " Login Please!!" << endl;
                halt();
            }
        }
        else if (choice == 2)
        {
            clearScreen();
            cout << "Enter username: ";
            cin >> username1;
            cout << "Enter password: ";
            cin >> password1;
            int role = roleCheck(username1, password1);
            if (roles[role] == "admin" || roles[role] == "Admin")
            {
                clearScreen();
                adminMenu();
            }
            else if (roles[role] == "student" || roles[role] == "Student")
            {
                clearScreen();
                StudentIndex = role;
                countLateBooks();
                studentMenu();
            }
            else if (role == -1)
            {
                cout << "Incorrect Password!!" << endl;
                halt();
            }
        }
        else if (choice == 3)
        {
            mainLoop = false;
        }
        else if (choice > 3)
        {
            cout << "Enter Correct Choice!!!" << endl;
            halt();
        }
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// User Menu Functionalities
void printAdminMenu()
{
    cout << "|----------------->> CLMS > Admin <<-------------------|" << endl
         << endl;
    cout << "1.  Add a new Book" << endl;
    cout << "2.  Delete a Book" << endl;
    cout << "3.  View Books" << endl;
    cout << "4.  Modify Book" << endl;
    cout << "5.  Search Book" << endl;
    cout << "6.  View Issued Books" << endl;
    cout << "7.  Issue Book" << endl;
    cout << "8.  Return Book" << endl;
    cout << "9.  View Students" << endl;
    cout << "10. Add New Student" << endl;
    cout << "11. Remove a Student" << endl;
    cout << "12. Logout" << endl;
    cout << "Enter choice: ";
}
void adminMenu()
{
    int choice;
    bool admin = true;
    while (admin)
    {
        clearScreen();
        printAdminMenu();
        choice = validatedInput(choice);
        if (choice == 1)
        {
            clearScreen();
            addBook();
        }
        else if (choice == 2)
        {
            clearScreen();
            string name1;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin >> ws, name1);
            int i = returnIndex(name1);
            if (i != -1)
            {
                // bool x = issueanceCheck(i);
                if (isBookIssued[i] == false)
                {
                    deleteBook(i);
                    cout << "Book Deleted Succeccflly!!" << endl;
                }
                else
                {
                    cout << "Unable to Delete Book!!" << endl;
                }
            }
            else
            {
                cout << "Book not Found!!" << endl;
            }
            halt();
        }
        else if (choice == 3)
        {
            clearScreen();
            viewBooks();
        }
        else if (choice == 4)
        {
            clearScreen();
            string name;
            int choice;
            cout << "Enter Book Name: ";
            cin.clear();
            cin.sync();
            getline(cin >> ws, name);
            int index = returnIndex(name);
            if (index != -1)
            {
                modifyBookSubMenu();
                cin >> choice;
                modifyBook(choice, index);
            }
            else
            {
                cout << "Book not found!!" << endl;
            }
            halt();
        }
        else if (choice == 5)
        {
            clearScreen();
            string name;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin >> ws, name);
            int idx = returnIndex(name);
            printBookByIndex(idx);
        }
        else if (choice == 6)
        {
            clearScreen();
            viewIssuedBooks();
        }
        else if (choice == 7)
        {
            clearScreen();
            string bname, stuname, dueDate;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin >> ws, bname);
            int idx = returnIndex(bname);
            if (idx != -1)
            {
                bool x = isBookIssued[idx];
                if (x == false)
                {
                    cout << "Enter Student Name: ";
                    // cin.ignore();
                    // cin.clear();
                    // cin.sync();
                    // getline(cin, stuname);
                    stuname = isAlpha(stuname);
                    bool y = checkStudentFromMembers(stuname);
                    if (y == true)
                    {
                        cout << "Enter Due Date (dd/mm/yyyy): ";
                        cin >> dueDate;
                        IssueBook(idx, stuname, dueDate);
                        cout << "Book Issued!!" << endl;
                    }
                    else
                    {
                        cout << "Student Not Found" << endl;
                    }
                }
                else
                {
                    cout << "Book Already Issued!!" << endl;
                }
            }
            else
            {
                cout << "Book not found!!" << endl;
            }
            halt();
        }
        else if (choice == 8)
        {
            clearScreen();
            int idx;
            string bname;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin >> ws, bname);
            idx = returnIndex(bname);
            if (idx != -1)
            {
                bool x = isBookIssued[idx];
                if (x == true)
                {
                    returnBook(idx);
                    cout << "Book Returned Successfully!!" << endl;
                }
            }
            else
            {
                cout << "Book not found!!" << endl;
            }
            halt();
        }
        else if (choice == 9)
        {
            clearScreen();
            viewStudents();
        }
        else if (choice == 10)
        {
            string student, username, password, rollnumber;
            string grade;
            clearScreen();
            cout << "Enter Student Name: ";
            // cin.ignore();
            // getline(cin, student);
            student = isAlpha(student);
            bool x = checkStudentFromMembers(student);
            if (x == false)
            {
                cout << "Enter Student's Class: ";
                // cin >> grade;
                grade = isNumber(grade);
                cout << "Enter Student's Roll Number: ";
                // cin >> rollnumber;
                // rollnumber = isNumber(rollnumber);
                rollnumber = checkRollNumber(rollnumber);
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;
                addStudent(student, grade, username, password, rollnumber);
                cout << "Student Added Successfully!!" << endl;
                storeMembersDataToFile();
            }
            else
            {
                cout << "Student Already Exists!!" << endl;
            }
            halt();
        }
        else if (choice == 11)
        {
            string name, rollnumber;
            clearScreen();
            cout << "Enter Student Name: ";
            // cin.ignore();
            // getline(cin, name);
            name = isAlpha(name);
            cout << "Enter RollNumber: ";
            // cin >> rollnumber;
            rollnumber = isNumber(rollnumber);
            int index = returnIndex(rollnumber);
            if (index != -1)
            {
                if (checkIfStudentIssuedBook(index) == true)
                {
                    cout << "Unable to Remove Student!!" << endl;
                }
                else
                {
                    removeStudent(index);
                    cout << "Student Removed Succeccflly!!" << endl;
                    storeMembersDataToFile();
                }
            }
            else
            {
                cout << "Student not Found!!" << endl;
            }
            halt();
        }
        else if (choice == 12)
        {
            admin = false;
        }
        else if (choice > 12)
        {
            cout << "Enter Correct Choice!!!" << endl;
            halt();
        }
    }
}
void printStuMenu()
{
    cout << "|---------------->> CLMS > Student <<------------------|" << endl
         << endl;
    cout << "1. Search Book" << endl;
    cout << "2. View Books" << endl;
    cout << "3. Check Status of a Book" << endl;
    cout << "4. Issue Book" << endl;
    cout << "5. Return Book" << endl;
    cout << "6. My Books" << endl;
    if (counterOfLateBooksOfUser != 0)
    {
        cout << "7. Notifications" << endl;
        cout << "8. Logout" << endl;
        cout << "Enter choice: ";
    }
    else
    {
        cout << "7. Logout" << endl;
        cout << "Enter choice: ";
    }
}
void studentMenu()
{
    bool stu = true;
    int choice, choice1, choice2;

    while (stu)
    {
        clearScreen();
        printStuMenu();
        choice = validatedInput(choice);
        if (choice == 1)
        {

            clearScreen();
            searchBookSubMenu();
            choice1 = validatedInput(choice1);
            if (choice1 == 1)
            {
                clearScreen();
                string bname;
                cout << "Enter Book Name: ";
                cin.ignore();
                getline(cin >> ws, bname);
                int index = returnIndex(bname);
                if (index != -1)
                {
                    printBookByString(bname);
                    // int index = returnIndex(bname);
                    // printBook(index);
                }
                else
                {
                    cout << "Book Not Found!!" << endl;
                    halt();
                }
            }
            else if (choice1 == 2)
            {
                clearScreen();
                string author;
                cout << "Enter Book Author: ";
                // cin.ignore();
                // getline(cin, author);
                author = isAlpha(author);
                int index = returnIndex(author);
                if (index != -1)
                {
                    printBookByString(author);
                    // printBook(index);
                }
                else
                {
                    cout << "Book Not Found!!" << endl;
                    halt();
                }
            }
            else if (choice1 == 3)
            {
                clearScreen();
                string genre;
                cout << "Enter Book Genre: ";
                // cin.ignore();
                // getline(cin, genre);
                genre = isAlpha(genre);
                int index = returnIndex(genre);
                if (index != -1)
                {
                    printBookByString(genre);
                    // printBook(index);
                }
                else
                {
                    cout << "Book Not Found" << endl;
                    halt();
                }
            }
        }
        else if (choice == 2)
        {
            clearScreen();
            viewBooks();
        }
        else if (choice == 3)
        {

            clearScreen();
            checkStatusSubMenu();
            choice2 = validatedInput(choice2);
            if (choice2 == 1)
            {
                string bname;
                clearScreen();
                cout << "Enter Book Name: ";
                cin.ignore();
                getline(cin >> ws, bname);
                int index = returnIndex(bname);
                if (status[index] == "Available")
                {
                    cout << "Book Status: " << status[index] << endl;
                }
                else
                {
                    cout << "Book Status: " << status[index] << endl;
                }
                halt();
            }
            else if (choice2 == 2)
            {
                clearScreen();
                string statusOfBook = "Available";
                cout << "Available Books List" << endl;
                printBookByString(statusOfBook);
                // checkstatus1(statusOfBook);
            }
            else if (choice2 == 3)
            {
                clearScreen();
                string statusOfBook = "Unavailable";
                cout << "Unavailable Books List" << endl;
                printBookByString(statusOfBook);
                // checkstatus1(statusOfBook);
            }
        }
        else if (choice == 4)
        {
            clearScreen();
            string bname, dueDate;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin >> ws, bname);
            int idx = returnIndex(bname);
            if (idx != -1)
            {
                bool x = isBookIssued[idx];
                if (x == false)
                {
                    cout << "Enter Due Date (dd/mm/yyyy): ";
                    cin >> dueDate;
                    IssueBookStudent(idx, dueDate);
                    cout << "Book Issued!!" << endl;
                }
                else
                {
                    cout << "Book Already Issued!!" << endl;
                }
            }
            else
            {
                cout << "Book not found!!" << endl;
            }
            halt();
        }
        else if (choice == 5)
        {
            clearScreen();
            int idx;
            string bname;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin >> ws, bname);
            idx = returnIndex(bname);
            if (idx != -1)
            {
                bool x = isBookIssued[idx];
                if (x == true)
                {
                    returnBook(idx);
                    cout << "Book Returned Successfully!!" << endl;
                }
            }
            else
            {
                cout << "Book not found!!" << endl;
            }
            halt();
        }
        else if (choice == 6)
        {
            clearScreen();
            printBookByString(students[StudentIndex]);
        }
        if (counterOfLateBooksOfUser != 0)
        {
            if (choice == 7)
            {
                clearScreen();
                viewNotifications();
            }
            else if (choice == 8)
            {
                stu = false;
            }
            else if (choice > 8)
            {
                cout << "Enter Correct Choice!!" << endl;
                halt();
            }
        }
        else
        {
            if (choice == 7)
            {
                stu = false;
            }
            else if (choice > 7)
            {
                cout << "Enter Correct Choice!!" << endl;
                halt();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function Definitions

void pHeader()
{
    // setcolor(8);
    cout << "   ______      ____                   __    _ __                                                      " << endl;
    cout << "  / ____/___  / / /__  ____ ____     / /   (_) /_  _________ ________  __                             " << endl;
    cout << " / /   / __ \\/ / / _ \\/ __ `/ _ \\   / /   / / __ \\/ ___/ __ `/ ___/ / / /                             " << endl;
    cout << "/ /___/ /_/ / / /  __/ /_/ /  __/  / /___/ / /_/ / /  / /_/ / /  / /_/ /                              " << endl;
    cout << "\\____/\\____/_/_/\\___/\\__, /\\___/  /_____/_/_.___/_/   \\__,_/_/   \\__, /                               " << endl;
    cout << "    __  ___         /____/                                   __ /____/___            __               " << endl;
    cout << "   /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_   / ___/__  _______/ /____  ____ ___ " << endl;
    cout << "  / /|_/ / __ `/ __ \\/ __ `/ __ `/ _ \\/ __ `__ \\/ _ \\/ __ \\/ __/   \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\" << endl;
    cout << " / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_    ___/ / /_/ (__  ) /_/  __/ / / / / /" << endl;
    cout << "/_/  /_/\\__,_/_/ /_/\\__,_/\\__, /\\___/_/ /_/ /_/\\___/_/ /_/\\__/   /____/\\__, /____/\\__/\\___/_/ /_/ /_/ " << endl;
    cout << "                         /____/                                       /____/                          " << endl;
    // cout << "********************************************************" << endl;
    // cout << "********   College Library Management System  **********" << endl;
    // cout << "********************************************************" << endl;
    // cout << "--------------------------------------------------------" << endl;
    // setcolor(15);
}
void loginScreen()
{
    cout << "|-------------->> CLMS > Login Screen <<---------------|" << endl
         << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice: ";
}
bool isPresent(string username, string password)
{
    for (int i = 0; i < userIndex; i++)
    {
        if (username == userNames[i] && password == userPasswords[i])
        {
            return 1;
        }
    }
    return 0;
}
void signUp(string username, string password, string role1, string name, string rollnumber, string grade)
{
    userNames[userIndex] = username;
    userPasswords[userIndex] = password;
    roles[userIndex] = role1;
    students[userIndex] = name;
    studentRollNumber[userIndex] = rollnumber;
    studentsClass[userIndex] = grade;
    studentIds[userIndex] = studentIdGenerator;
    userIndex++;
    studentIdGenerator++;
}
int roleCheck(string username1, string password1)
{
    int role = -1;
    for (int i = 0; i < userIndex; i++)
    {
        if (username1 == userNames[i])
        {
            if (password1 == userPasswords[i])
            {
                role = i;
            }
        }
    }
    return role;
}
void clearScreen()
{
    system("cls");
    pHeader();
    cout << endl;
}
void addBook()
{
    // cout << "Enter Book Id: ";
    // cin >> bookIds[indexbook];
    bookIds[indexbook] = bookIdGenerator;
    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin >> ws, books[indexbook]);
    cout << "Enter Author Name: ";
    // getline(cin, authors[indexbook]);
    authors[indexbook] = isAlpha(authors[indexbook]);
    cout << "Enter Book Genre: ";
    // getline(cin, genres[indexbook]);
    genres[indexbook] = isAlpha(genres[indexbook]);
    status[indexbook] = "Available";
    isBookIssued[indexbook] = false;
    issuedStudentNames[indexbook] = "";
    indexbook++;
    bookIdGenerator++;
    cout << "Book has been added!" << endl;
    storeBooksDataToFile();
    storeIssuedBooksDataToFile();
    halt();
}
void deleteBook(int idx)
{
    for (int j = idx; j <= indexbook - 1; j++)
    {
        bookIds[j] = bookIds[j + 1];
        books[j] = books[j + 1];
        authors[j] = authors[j + 1];
        status[j] = status[j + 1];
        bookIds[j] = bookIds[j + 1];
        genres[j] = genres[j + 1];
        issueDates[j] = issueDates[j + 1];
        dueInDates[j] = dueInDates[j + 1];
        issuedStudentNames[j] = issuedStudentNames[j + 1];
        isBookIssued[j] = isBookIssued[j + 1];
    }
    indexbook--;
    storeBooksDataToFile();
    storeIssuedBooksDataToFile();
}
void viewBooks()
{

    cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "Issue Date" << setw(20) << "DueInDate" << endl
         << endl;
    for (int i = 0; i < indexbook; i++)
    {
        // if (books[i] == "")
        // {
        //     continue;
        // }
        cout << left << setw(20) << bookIds[i] << setw(20) << genres[i] << setw(20) << books[i] << setw(20) << authors[i];

        if (status[i] == "Unavailable")
        {
            setcolor(12);
            cout << setw(20) << status[i];
            setcolor(15);
            cout << setw(20) << issuedStudentNames[i] << setw(20) << issueDates[i] << setw(20) << dueInDates[i] << endl;
        }
        else
        {
            cout << setw(20) << status[i] << setw(20) << issuedStudentNames[i] << setw(20) << issueDates[i] << setw(20) << dueInDates[i] << endl;
        }
        cout << endl;
    }
    cout << endl;
    halt();
}
void modifyBookSubMenu()
{
    clearScreen();
    cout << endl;
    cout << "1. Change Book Status: " << endl;
    cout << "2. Change Book's Due In Date: " << endl;
    cout << "Enter choice: ";
}
void modifyBook(int choice, int idx)
{

    if (choice == 1)
    {
        clearScreen();
        cout << "Enter Book Status: ";
        // cin >> status[idx];
        status[idx] = isAlpha(status[idx]);
        if (status[idx] == "Available")
        {
            isBookIssued[idx] = false;
            issuedStudentNames[idx] = "";
            issueDates[idx] = "";
            dueInDates[idx] = "";
        }
        cout << endl
             << "Book Status has been changed successfully!" << endl;
        storeBooksDataToFile();
        storeIssuedBooksDataToFile();
    }
    else if (choice == 2)
    {
        if (isBookIssued[idx] == true)
        {
            clearScreen();
            cout << "Enter Date(dd/mm/yyyy): ";
            cin >> dueInDates[idx];
            cout << endl
                 << "Book dueIn date has been changed successfully!" << endl;
        }
        storeBooksDataToFile();
        storeIssuedBooksDataToFile();
    }
}
void viewIssuedBooks()
{
    cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "Issue Date" << setw(20) << "DueInDate" << endl
         << endl;
    for (int i = 0; i < arrSize; i++)
    {
        if (status[i] == "Unavailable")
        {
            cout << left << setw(20) << bookIds[i] << setw(20) << genres[i] << setw(20) << books[i] << setw(20) << authors[i];
            setcolor(12);
            cout << setw(20) << status[i];
            setcolor(15);
            cout << setw(20) << issuedStudentNames[i] << setw(20) << issueDates[i] << setw(20) << dueInDates[i] << endl;
        }
    }
    halt();
}
void IssueBook(int idx, string studentName, string dueDate)
{
    issuedStudentNames[idx] = studentName;
    issueDates[idx] = systemDate();
    dueInDates[idx] = dueDate;
    status[idx] = "Unavailable";
    isBookIssued[idx] = true;
    storeBooksDataToFile();
    storeIssuedBooksDataToFile();
}
void IssueBookStudent(int idx, string dueDate)
{
    issuedStudentNames[idx] = students[StudentIndex];
    issueDates[idx] = systemDate();
    dueInDates[idx] = dueDate;
    status[idx] = "Unavailable";
    isBookIssued[idx] = true;
    storeBooksDataToFile();
    storeIssuedBooksDataToFile();
}
bool issueanceCheck(int idx)
{
    if (isBookIssued[idx] == false)
    {
        return true;
    }

    return false;
}
void returnBook(int idx)
{
    issueDates[idx] = "";
    issuedStudentNames[idx] = "";
    dueInDates[idx] = "";
    status[idx] = "Available";
    isBookIssued[idx] = false;
    storeBooksDataToFile();
    storeIssuedBooksDataToFile();
}
void viewStudents()
{
    cout << "List of Members of Library" << endl
         << endl;
    cout << left << setw(20) << "Student ID" << setw(20) << "Student Names" << setw(20) << "Class" << setw(20) << "RollNumber" << endl;
    for (int i = 0; i < userIndex; i++)
    {
        if (roles[i] == "student" || roles[i] == "Student")
        {
            cout << left << setw(20) << studentIds[i] << setw(20) << students[i] << setw(20) << studentsClass[i] << setw(20) << studentRollNumber[i] << endl;
        }
    }
    cout << endl;
    halt();
}
void addStudent(string student, string grade, string username, string password, string rollnumber)
{
    studentIds[userIndex] = studentIdGenerator;
    students[userIndex] = student;
    studentsClass[userIndex] = grade;
    userNames[userIndex] = username;
    userPasswords[userIndex] = password;
    studentRollNumber[userIndex] = rollnumber;
    roles[userIndex] = "student";
    userIndex++;
    studentIdGenerator++;
}
void removeStudent(int index)
{
    for (int j = index; j <= userIndex - 1; j++)
    {
        studentIds[j] = studentIds[j + 1];
        students[j] = students[j + 1];
        studentsClass[j] = studentsClass[j + 1];
        userPasswords[j] = userPasswords[j + 1];
        userNames[j] = userNames[j + 1];
        studentRollNumber[j] = studentRollNumber[j + 1];
        roles[j] = roles[j + 1];
    }
    userIndex--;
}
void searchBookSubMenu()
{
    cout << "1. Search Book by Name" << endl;
    cout << "2. Search Book by Author" << endl;
    cout << "3. Search Book by Genre" << endl;
    cout << "Enter choice: ";
}
void checkStatusSubMenu()
{
    cout << "1. Check Status by Book Name" << endl;
    cout << "2. View Available Books" << endl;
    cout << "3. View Unavailable Books" << endl;
    cout << "Enter choice: " << endl;
}
void printBookByIndex(int idx)
{
    if (idx != -1)
    {
        cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "Issue Date" << setw(20) << "DueInDate" << endl
             << endl;
        cout << left << setw(20) << bookIds[idx] << setw(20) << genres[idx] << setw(20) << books[idx] << setw(20) << authors[idx];
        if (status[idx] == "Unavailable")
        {
            setcolor(12);
            cout << setw(20) << status[idx];
            setcolor(15);
        }
        else
        {
            cout << setw(20) << status[idx];
        }
        cout << setw(20) << issuedStudentNames[idx] << setw(20) << issueDates[idx] << setw(20) << dueInDates[idx] << endl;
    }
    else
    {
        cout << "Book Not Found!!!" << endl;
    }
    cout << endl;
    halt();
}
void printBookByString(string name)
{
    cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "Issue Date" << setw(20) << "DueInDate" << endl
         << endl;
    for (int i = 0; i < indexbook; i++)
    {
        if (name == genres[i] || name == books[i] || name == authors[i] || name == status[i] || name == issuedStudentNames[i])
        {

            cout << left << setw(20) << bookIds[i] << setw(20) << genres[i] << setw(20) << books[i] << setw(20) << authors[i];
            if (status[i] == "Unavailable")
            {
                if (status[i] == "Unavailable")
                {
                    setcolor(12);
                    cout << setw(20) << status[i];
                    setcolor(15);
                }
            }
            cout << setw(20) << status[i] << setw(20) << issuedStudentNames[i] << setw(20) << issueDates[i] << setw(20) << dueInDates[i] << endl
                 << endl;
        }
    }
    cout << endl;
    halt();
}
void viewNotifications()
{
    cout << "You have " << counterOfLateBooksOfUser << " number of books late!! Kindly return the book and contact the accounts office for payment of fine." << endl;
    halt();
}
int returnIndex(string name1)
{
    int idx = -1;
    for (int i = 0; i < indexbook; i++)
    {
        if (name1 == books[i] || name1 == authors[i] || name1 == genres[i] || name1 == status[i] || name1 == students[i] || name1 == studentRollNumber[i])
        {
            idx = i;
            break;
        }
    }
    return idx;
}
int returnIndexForIssue(string id)
{
    int index = -1;
    int bId = stoi(id);
    for (int i = 0; i < indexbook; i++)
    {
        if (bId == bookIds[i])
        {
            index = i;
            break;
        }
    }
    return index;
}
bool checkStudentFromMembers(string stuname)
{
    bool y;
    for (int i = 0; i < userIndex; i++)
    {
        if (stuname == students[i])
        {
            y = true;
        }
    }
    return y;
}
bool checkIfStudentIssuedBook(int index)
{
    for (int i = 0; i < indexbook; i++)
    {
        if (students[index] == issuedStudentNames[i])
        {
            return true;
        }
    }
    return false;
}
void halt()
{
    cout << "Press any key to continue.. ";
    getch();
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
string isAlpha(string input)
{
    cin.clear();
    cin.sync();
    getline(cin >> ws, input);
    bool x;
    int check;
    while (true)
    {
        int size = input.length();
        for (int i = 0; i < size; i++)
        {

            check = int(input[i]);
            if ((check >= 65 && check <= 90) || (check >= 97 && check <= 122) || input[i] == ' ')
            {
                x = true;
            }
            else
            {
                x = false;
                break;
            }
        }
        if (x == 1)
        {
            return input;
        }
        else
        {
            cout << "Wrong Input!!" << endl;
            cout << "Enter Correct Name: ";
            cin.clear();
            cin.sync();
            getline(cin >> ws, input);
        }
    }
}
string isNumber(string input)
{
    cin.clear();
    cin.sync();
    getline(cin >> ws, input);
    bool x;
    int check;
    while (true)
    {
        int size = input.length();
        for (int i = 0; i < size; i++)
        {

            check = int(input[i]);
            if ((check >= 48 && check <= 57))
            {
                x = true;
            }
            else
            {
                x = false;
                break;
            }
        }
        if (x == 1)
        {
            return input;
        }
        else
        {
            cout << "Wrong Input!!" << endl;
            cout << "Enter Correct Input: ";
            cin.clear();
            cin.sync();
            getline(cin >> ws, input);
        }
    }
}
int validatedInput(int choice)
{
    cin >> choice;
    while (true)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Entered Wrong Input!!" << endl;
            cout << "Enter Correct Input: ";
            cin >> choice;
        }
        if (!cin.fail())
        {

            break;
        }
    }
    return choice;
}
string parseData(string line, int field)
{
    string item;
    int commaCount = 1;
    int length = line.length();
    for (int i = 0; i < length; i++)
    {
        if (line[i] == ',')
        {
            commaCount++;
        }
        else if (field == commaCount)
        {
            item = item + line[i];
        }
    }
    return item;
}
void loadMembersDataToArrays()
{
    string line;
    fstream file;
    file.open("membersData.txt", ios::in);
    while (getline(file, line))
    {
        if (line != "")
        {
            string sId = parseData(line, 1);
            string name = parseData(line, 2);
            string rollnumber = parseData(line, 3);
            string grade = parseData(line, 4);
            string userName = parseData(line, 5);
            string userPassword = parseData(line, 6);
            string role = parseData(line, 7);
            userNames[userIndex] = userName;
            userPasswords[userIndex] = userPassword;
            roles[userIndex] = role;
            studentRollNumber[userIndex] = rollnumber;
            students[userIndex] = name;
            studentsClass[userIndex] = grade;
            studentIds[userIndex] = stoi(sId);
            userIndex++;
            studentIdGenerator++;
        }
    }
    file.close();
}
void storeMembersDataToFile()
{
    fstream file;
    file.open("membersData.txt", ios::out);
    for (int i = 0; i < userIndex; i++)
    {
        file << studentIds[i] << "," << students[i] << "," << studentRollNumber[i] << "," << studentsClass[i] << "," << userNames[i] << "," << userPasswords[i] << "," << roles[i] << endl;
    }
    file.close();
}
void loadIssuedBooksDataToArrays()
{
    string line;
    fstream file;
    file.open("issuedBooksData.txt", ios::in);
    while (getline(file, line))
    {
        if (line != "")
        {
            string id = parseData(line, 1);
            string availability = parseData(line, 2);
            string issuedStudenName = parseData(line, 3);
            string issueDate = parseData(line, 4);
            string dueInDate = parseData(line, 5);
            int index = returnIndexForIssue(id);
            status[index] = availability;
            if (availability == "Available")
            {
                isBookIssued[index] = false;
            }
            else if (availability == "Unavailable")
            {
                isBookIssued[index] = true;
            }
            issuedStudentNames[index] = issuedStudenName;
            issueDates[index] = issueDate;
            dueInDates[index] = dueInDate;
        }
    }
    file.close();
}
void storeIssuedBooksDataToFile()
{
    fstream file;
    file.open("issuedBooksData.txt", ios::out);
    for (int i = 0; i < indexbook; i++)
    {
        file << bookIds[i] << "," << status[i] << "," << issuedStudentNames[i] << "," << issueDates[i] << "," << dueInDates[i] << endl;
    }
    file.close();
}
void loadBooksDataToArrays()
{
    string line;
    fstream file;
    file.open("booksData.txt", ios::in);
    while (getline(file, line))
    {
        if (line != "")
        {
            string id = parseData(line, 1);
            int bookId = stoi(id);
            string book = parseData(line, 2);
            string author = parseData(line, 3);
            string genre = parseData(line, 4);
            bookIds[indexbook] = bookId;
            books[indexbook] = book;
            authors[indexbook] = author;
            genres[indexbook] = genre;
            indexbook++;
            bookIdGenerator++;
        }
    }
    file.close();
}
void storeBooksDataToFile()
{
    fstream file;
    file.open("booksData.txt", ios::out);
    for (int i = 0; i < indexbook; i++)
    {
        file << bookIds[i] << "," << books[i] << "," << authors[i] << "," << genres[i] << endl;
    }
    file.close();
}
string systemDate()
{
    time_t ct = time(0);
    string Time = ctime(&ct);
    string s = parseDate(Time, 3) + "/" + changeMonthToNumber(parseDate(Time, 2)) + "/" + parseDate(Time, 5);
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.cend());
    return s;
}
string changeMonthToNumber(string month)
{
    string mahina;
    if (month == "Jan")
    {
        mahina = "01";
    }
    else if (month == "Feb")
    {
        mahina = "02";
    }
    else if (month == "Mar")
    {
        mahina = "03";
    }
    else if (month == "Apr")
    {
        mahina = "04";
    }
    else if (month == "May")
    {
        mahina = "05";
    }
    else if (month == "Jun")
    {
        mahina = "06";
    }
    else if (month == "Jul")
    {
        mahina = "07";
    }
    else if (month == "Aug")
    {
        mahina = "08";
    }
    else if (month == "Sep")
    {
        mahina = "09";
    }
    else if (month == "Oct")
    {
        mahina = "10";
    }
    else if (month == "Nov")
    {
        mahina = "11";
    }
    else if (month == "Dec")
    {
        mahina = "12";
    }
    return mahina;
}
string parseDate(string Time, int field)
{
    string item;
    int spaceCount = 1;
    int length = Time.length();
    for (int i = 0; i < length; i++)
    {
        if (Time[i] == ' ')
        {
            spaceCount++;
        }
        else if (field == spaceCount)
        {
            item = item + Time[i];
        }
    }

    return item;
}
bool isLate(string currentDate, string expiryDate)
{
    int currentDays = convertDateToDays(currentDate);
    int expiryDays = convertDateToDays(expiryDate);
    return (currentDays > expiryDays);
}
int convertDateToDays(string date)
{
    // 22-10-2022
    string dateDays = {date[0], date[1], '\0'};
    string dateMonths = {date[3], date[4], '\0'};
    string dateYears = {date[6], date[7], date[8], date[9], '\0'};
    return stoi(dateDays) + stoi(dateMonths) * 30 + (stoi(dateYears) - 2000) * 365;
}
void checkLateBooks()
{
    for (int i = 0; i < indexbook; i++)
    {
        if (isBookIssued[i] == true)
        {
            if (isLate(todayDate, dueInDates[i]))
            {
                isIssuedBookLate[i] = true;
            }
            else
            {
                isIssuedBookLate[i] = false;
            }
        }
    }
}
void countLateBooks()
{
    for (int i = 0; i < indexbook; i++)
    {
        if (students[StudentIndex] == issuedStudentNames[i])
        {
            if (isIssuedBookLate[i] == true)
            {
                counterOfLateBooksOfUser++;
            }
        }
    }
}
string checkRollNumber(string rollnumber)
{
    cin >> rollnumber;

    for (int i = 0; i < userIndex; i++)
    {
        if (rollnumber == studentRollNumber[i])
        {
            cout << "Roll Number Already Exists!!" << endl;
            cout << "RollNumber: ";
            cin >> rollnumber;
        }
        else
        {
            continue;
        }
    }

    return rollnumber;
}
