#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>

using namespace std;

// Gloabal Data

string fixedSpace = "\t\t\t";
string masterUsername = "CLMS"; // Master Username for Admin SignUp
string masterPassword = "CLMS"; // MAster Password

const int arrSize = 10;     // Array Size
const int membersSize = 10; // Number of Members of the Library
bool mainLoop = true;       // mainLoop condition

// Login and SignIn Data

string userNames[arrSize] = {"admin", "sabur"}; // Usernames
string userPass[arrSize] = {"123", "000"};      // Passwords
string roles[arrSize] = {"Admin", "student"};   // Roles

// Library Data

int memberCount = 6;
int userIndex = 2;                                                                                                                // count of users
int indexbook = 5;                                                                                                                // count of books
int indexstudent = 5;                                                                                                             // count of users
int bookId[arrSize] = {1, 2, 3, 4, 5};                                                                                            // Book Ids
string books[arrSize] = {"Book1", "Book2", "Book3", "Book4", "Book5"};                                                            // Book Names
string authors[arrSize] = {"Author1", "Author1", "Author3", "Author3", "Author5"};                                                // Book Authors
string status[arrSize] = {"Available", "Unavailable", "Available", "Unavailable", "Available"};                                   // Book Statuses
string genres[arrSize] = {"English", "Maths", "English", "Maths", "English"};                                                     // Book Genres
string issuedStudentNames[arrSize] = {"", "Abdul Sabur", "", "Anas Mustafa", ""};                                                 // Student who have issued the books
string students[membersSize] = {"Abdul Sabur", "Anas Mustafa", "Wali Ahmad", "Abdul Rehman", "Maryam Waseem", "Rameen Ihtasham"}; // Members of the Library
int studentsClass[membersSize] = {10, 11, 12, 9, 8, 7, 5};                                                                        // Classes of Students
string dueInDates[arrSize] = {"", "22/02/2023", "", "25/02/2023"};                                                                // Returning dates of issued books

// General Functions Prototypes
int validatedInput(int choice);                    // validates choice
string setcolor(unsigned short color);             // change color of a specific line
bool isPresent(string username, string password);  // check if the user has already signed up
string roleReturn();                               // return the roles of users
void pHeader();                                    // prints header on the screen
void loginScreen();                                // prints login options
void clearScreen();                                // clears screen and prints header again
int roleCheck(string username1, string password1); // returns the user's role index
void printBookByIndex(int idx);                    // prints book from an index
void printBookByString(string name);               // prints book by name,author,status,genre
bool isAlpha(string input);                        // returns true if input is string
void halt();                                       // stops and asks for a key to continue

// Users Main Function Prototypes
void adminMenu();   // Main handler for the Admin
void studentMenu(); // Main handler for the Student

// Admin Functions Prototypes
void printAdminMenu();
void addBook();
void deleteBook(int idx);
void viewBooks();
void modifyBook(int choice, int idx);
void searchBook(string name);
void modifyBookSubMenu();
void viewIssuedBooks();
void IssueBook(int idx, string studentName, string dueDate);
bool issueanceCheck(int idx);
void returnBook(int idx);
int returnBookIndex(string name1);
void viewStudents();
void addStudent(string student, int grade);
void removeStudent(int index);
int returnIndex(string name);
bool checkStudentFromMembers(string stuname);

// Student Functions Prototypes
void printStuMenu();
void searchBookSubMenu();
void checkStatusSubMenu();

int main()
{
    int choice;
    string masterUser, masterPass, username, password, role1, username1, password1;
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
                            userNames[userIndex] = username;
                            userPass[userIndex] = password;
                            roles[userIndex] = role1;
                            cout << "You have Signed Up Successfully as an Admin!!" << endl;
                            userIndex++;
                        }
                        else
                        {
                            cout << "You do not have access!!" << endl;
                        }
                    }
                    else
                    {
                        userNames[userIndex] = username;
                        userPass[userIndex] = password;
                        roles[userIndex] = role1;
                        cout << "You have Signed Up Successfully!!" << endl;
                        userIndex++;
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
            else if (roles[role] == "student" || roles[role] == "student")
            {
                clearScreen();
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

// User Menu Functionalities
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
            getline(cin, name1);
            int i = returnBookIndex(name1);
            if (i != -1)
            {
                // bool x = issueanceCheck(i);
                if (status[i] == "Available")
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
            cin.ignore();
            getline(cin, name);
            int index = returnBookIndex(name);
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
            getline(cin, name);
            int idx = returnBookIndex(name);
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
            getline(cin, bname);
            int idx = returnBookIndex(bname);
            if (idx != -1)
            {
                bool x = issueanceCheck(idx);
                if (x == true)
                {
                    cout << "Enter Student Name: ";
                    cin.ignore();
                    cin.clear();
                    cin.sync();
                    getline(cin, stuname);
                    bool y = checkStudentFromMembers(stuname);
                    if (y == true)
                    {
                        cout << "Enter Due Date: ";
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
            getline(cin, bname);
            idx = returnBookIndex(bname);
            if (idx != -1)
            {
                bool x = issueanceCheck(idx);
                if (x == false)
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
            string student;
            int grade;
            clearScreen();
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, student);
            bool x = checkStudentFromMembers(student);
            if (x == true)
            {
                cout << "Enter Student's Class: ";
                cin >> grade;
                addStudent(student, grade);
                cout << "Student Added Successfully!!" << endl;
            }
            else
            {
                cout << "Student Already Exists!!" << endl;
            }
            halt();
        }
        else if (choice == 11)
        {
            string name;
            clearScreen();
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, name);
            int index = returnIndex(name);
            if (index != -1)
            {
                removeStudent(index);
                cout << "Student Removed Succeccflly!!" << endl;
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
void printStuMenu()
{
    cout << "|---------------->> CLMS > Student <<------------------|" << endl
         << endl;
    cout << "1. Search Book" << endl;
    cout << "2. View Books" << endl;
    cout << "3. Check Status of a Book" << endl;
    cout << "4. Issue Book" << endl;
    cout << "5. Return Book" << endl;
    cout << "6. Logout" << endl;
    cout << "Enter choice: ";
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
                getline(cin, bname);
                int index = returnBookIndex(bname);
                if (index != -1)
                {
                    printBookByString(bname);
                    // int index = returnBookIndex(bname);
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
                cin.ignore();
                getline(cin, author);
                int index = returnBookIndex(author);
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
                cin.ignore();
                getline(cin, genre);
                int index = returnBookIndex(genre);
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
                getline(cin, bname);
                int index = returnBookIndex(bname);
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
            string bname, stuname, dueDate;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, bname);
            int idx = returnBookIndex(bname);
            if (idx != -1)
            {
                bool x = issueanceCheck(idx);
                if (x == true)
                {
                    cout << "Enter Student Name: ";
                    cin.ignore();
                    getline(cin, stuname);
                    bool y = checkStudentFromMembers(stuname);
                    if (y == true)
                    {
                        cout << "Enter Due Date: ";
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
        else if (choice == 5)
        {
            clearScreen();
            int idx;
            string bname;
            cout << "Enter Book Name: ";
            cin.ignore();
            getline(cin, bname);
            idx = returnBookIndex(bname);
            if (idx != -1)
            {
                bool x = issueanceCheck(idx);
                if (x == false)
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
            stu = false;
        }
        else if (choice > 6)
        {
            cout << "Enter Correct Choice!!" << endl;
            halt();
        }
    }
}
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
        if (username == userNames[i] && password == userPass[i])
        {
            return 1;
        }
    }
    return 0;
}
int roleCheck(string username1, string password1)
{
    int role = -1;
    for (int i = 0; i < userIndex; i++)
    {
        if (username1 == userNames[i])
        {
            if (password1 == userPass[i])
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
    cout << "Enter Book Id: ";
    cin >> bookId[indexbook];
    cin.ignore();
    cout << "Enter Book Name: ";
    getline(cin, books[indexbook]);
    cout << "Enter Author Name: ";
    getline(cin, authors[indexbook]);
    cout << "Enter Book Genre: ";
    getline(cin, genres[indexbook]);
    status[indexbook] = "Available";
    issuedStudentNames[indexbook] = "";
    indexbook++;
    cout << "Book has been added!" << endl;
    halt();
}
void deleteBook(int idx)
{
    for (int j = idx; j <= indexbook - 1; j++)
    {
        books[j] = books[j + 1];
        authors[j] = authors[j + 1];
        status[j] = status[j + 1];
        bookId[j] = bookId[j + 1];
        genres[j] = genres[j + 1];
        dueInDates[j] = dueInDates[j + 1];
        issuedStudentNames[j] = issuedStudentNames[j + 1];
    }

    indexbook--;
}
void viewBooks()
{

    cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "DueInDate" << endl
         << endl;
    for (int i = 0; i < indexbook; i++)
    {
        // if (books[i] == "")
        // {
        //     continue;
        // }
        cout << left << setw(20) << bookId[i] << setw(20) << genres[i] << setw(20) << books[i] << setw(20) << authors[i];

        if (status[i] == "Unavailable")
        {
            setcolor(12);
            cout << setw(20) << status[i];
            setcolor(15);
            cout << setw(20) << issuedStudentNames[i] << setw(20) << dueInDates[i] << endl;
        }
        else
        {
            cout << setw(20) << status[i] << setw(20) << issuedStudentNames[i] << setw(20) << dueInDates[i] << endl;
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
        cin >> status[idx];
        cout << endl
             << "Book Status has been changed successfully!" << endl;
    }
    else if (choice == 2)
    {
        clearScreen();
        cout << "Enter Date: ";
        cin >> dueInDates[idx];
        cout << endl
             << "Book dueIn date has been changed successfully!" << endl;
    }
}
void viewIssuedBooks()
{
    cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "DueInDate" << endl
         << endl;
    for (int i = 0; i < arrSize; i++)
    {
        if (status[i] == "Unavailable")
        {
            cout << left << setw(20) << bookId[i] << setw(20) << genres[i] << setw(20) << books[i] << setw(20) << authors[i] << setw(20) << status[i] << setw(20) << issuedStudentNames[i] << setw(20) << dueInDates[i] << endl;
        }
    }
    halt();
}
void IssueBook(int idx, string studentName, string dueDate)
{
    issuedStudentNames[idx] = studentName;
    dueInDates[idx] = dueDate;
    status[idx] = "Unavailable";
}
bool issueanceCheck(int idx)
{
    if (status[idx] == "Available")
    {
        return true;
    }

    return false;
}
void returnBook(int idx)
{
    issuedStudentNames[idx] = "";
    dueInDates[idx] = "";
    status[idx] = "Available";
}
void viewStudents()
{
    cout << "List of Members of Library" << endl
         << endl;
    cout << left << setw(20) << "Student Names" << setw(20) << "Class" << endl;
    for (int i = 0; i < memberCount; i++)
    {
        cout << left << setw(20) << students[i] << setw(20) << studentsClass[i] << endl;
    }
    cout << endl;
    halt();
}
void addStudent(string student, int grade)
{
    students[memberCount] = student;
    studentsClass[memberCount] = grade;
    memberCount++;
}
int returnIndex(string name1)
{
    int idx = -1;
    for (int i = 0; i < arrSize; i++)
    {
        if (name1 == books[i] || name1 == authors[i] || name1 == genres[i] || name1 == students[i])
        {
            idx = i;
            break;
        }
    }
    return idx;
}
void removeStudent(int index)
{
    for (int j = index; j <= indexstudent - 1; j++)
    {
        students[j] = students[j + 1];
        studentsClass[j] = studentsClass[j + 1];
    }
    indexstudent--;
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
        cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "DueInDate" << endl
             << endl;
        cout << left << setw(20) << bookId[idx] << setw(20) << genres[idx] << setw(20) << books[idx] << setw(20) << authors[idx];
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
        cout << setw(20) << issuedStudentNames[idx] << setw(20) << dueInDates[idx] << endl;
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
    cout << left << setw(20) << "Book ID" << setw(20) << "Genre" << setw(20) << "Book Name" << setw(20) << "Author" << setw(20) << "Status" << setw(20) << "StudentName" << setw(20) << "DueInDate" << endl
         << endl;
    for (int i = 0; i < indexbook; i++)
    {
        if (name == genres[i] || name == books[i] || name == authors[i] || name == status[i])
        {

            cout << left << setw(20) << bookId[i] << setw(20) << genres[i] << setw(20) << books[i] << setw(20) << authors[i];
            if (status[i] == "Unavailable")
            {
                if (status[i] == "Unavailable")
                {
                    setcolor(12);
                    cout << setw(20) << status[i];
                    setcolor(15);
                }
                else
                {
                    cout << setw(20) << status[i];
                }
            }
            cout << setw(20) << issuedStudentNames[i] << setw(20) << dueInDates[i] << endl
                 << endl;
        }
    }
    cout << endl;
    halt();
}
int returnBookIndex(string name1)
{
    int idx = -1;
    for (int i = 0; i < indexbook; i++)
    {
        if (name1 == books[i] || name1 == authors[i] || name1 == genres[i] || name1 == status[i])
        {
            idx = i;
            break;
        }
    }
    return idx;
}
bool checkStudentFromMembers(string stuname)
{
    bool y;
    for (int i = 0; i < indexstudent; i++)
    {
        if (stuname == students[i])
        {
            y = true;
        }
    }
    return y;
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
bool isAlpha(string input)
{
    bool x;
    int check;
    int size = input.length();
    for (int i = 0; i < size; i++)
    {
        if (input[i] != ' ')
        {
            check = int(input[i]);
            if ((check >= 65 && check <= 90) || (check >= 97 && check <= 122))
            {
                x = true;
            }
            else
            {
                return false;
            }
        }
    }
    return x;
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