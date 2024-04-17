#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <conio.h>  // Include this for _getch() function

using namespace std;

// Define Question structure for quizzes
struct Question {
    string definition;
    vector<string> options;
    int correctOption;
};


    string red = "\033[1;31m";   // Red color
    string cyan = "\033[1;36m"; // Cyan color 
    string RESET = "\033[0m";  
    string yellow =  "\033[33m" ; // yellow color
    string green = "\033[32m"; // green color
         
class WelcomePattern
{
    int i,j;
    public:
    WelcomePattern()
    {i =0;
    j=0;}
    
    void init(int i, int j)
    {this-> i=i;
        this-> j=j;
    }
    public:
    void pattern(int i,int j)
    {
        //  string red = "\033[1;31m";   // Red color
        //  string cyan = "\033[1;36m"; // Cyan color
        //w pattern and e pattern
for(i=1;i<=5;i++){
    //space before welcome 
    for(j=1;j<=35;j++)
    {cout<<" ";}
    for(j=1;j<=11;j++){
        if(i!=4&&j==2 || i!=3&&j==3 || i!=4 && j==4 || i%2==0 && j>7 && j<=11 || j%6==0) {
        cout<<" ";}
        else 
            {cout<<cyan<<"#";}
    }
    //L pattern 
    for(j=12;j<=17;j++){
        if(i==5 || j ==13){
     cout<<"#";}
        else 
        {cout<<" ";}
        if( j%6==0){cout<<" ";}
       
    }
    // c pattern
     for(j=18;j<=23;j++){
        if(i==1||i==5||j==19){
            cout<<"#";
        }
         else
         {cout<<" ";}
         if( j%6==0){cout<<" ";}
         
     }
     //o pattern 
     for(j=24;j<=29;j++){
        if(i==1 || j==25 || i==5 ||j ==29 )
        {cout<<"#";}
        else{cout<<" ";}
        if( j%6==0){cout<<" ";}
    }
    // M pattern 
    for(j=30;j<=35;j++){
        if(i!=2&&j==32 || i!=3&&j==33 || i!=2 && j==34 || j%6==0){
        cout<<" ";}
        else
        {cout<<"#";}
    if( j%6==0){cout<<" ";}}
    //E pattern 
     for(j=36;j<=41;j++){
            if(i%2==0 && j>37 || j==36 )
            {cout<<" ";}
            else{
                cout<<"#";
            }
        if( j%6==0){cout<<" ";}}
        
    cout<<endl<<RESET;}
    cout<<endl;}
    
void Traingle(int i, int j)
{
   for (i = 1; i <= 5; i++) {
        for (j = 1; j <= i; j++) {
            cout<<yellow<<"* "<<RESET;
        }cout<<endl;}
}
    
};

// Define Course class
class Course {
public:
    string name;
    vector<string> chapters;
    map<string, vector<Question>> chapterQuizzes; // Chapter -> List of Questions
    map<string, string> chapterDefinitions;       // Chapter -> Chapter Definition
};

// Define User class
class User {
public:
    string username;
    string password;
    vector<Course> enrolledCourses;
    int score;

    User(const string& u, const string& p) : username(u), password(p), score(0) {}
};

vector<User> users;
vector<Course> courses;
User* currentUser = nullptr;
bool loggedIn = false;

void printBorder() {
    cout << "******************************************************" << endl;
}

void saveUserDataToFile() {
    ofstream file("user_data.txt");
    for (const User& user : users) {
        file << user.username << " " << user.password << " " << user.score << endl;
    }
    file.close();
}

void loadUserDataFromFile() {
    ifstream file("user_data.txt");
    if (!file) {
        cout <<yellow<< "Welcome to the Learning App!" <<RESET<< endl;
        return;
    }
    while (!file.eof()) {
        string username, password;
        int score;
        file >> username >> password >> score;
        users.push_back(User(username, password));
        users.back().score = score;
    }
    file.close();
}

bool isUsernameUnique(const string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return false;
        }
    }
    return true;
}

bool isPasswordUnique(const string& password) {
    for (const User& user : users) {
        if (user.password == password) {
            return false;
        }
    }
    return true;
}

// Function to register a new user
void Register() {
    printBorder();
    cout << setw(40) << "Registration" << endl;
    printBorder();

     string username, password;

    while (true) {
        cout << "Enter username: ";
        cin >> username;

        if (isUsernameUnique(username)) {
            break;
        } else {
            cout <<red<< "Username already exists. Please choose a different username." <<RESET<< endl;
        }
    }

    while (true) {
        cout << "Enter password: ";
        char ch;
        password = "";
        while ((ch = _getch()) != '\r') {  // '\r' is the Enter key
            cout << '*';  // Display '*' for each character entered
            password += ch;
        }
        cout << endl;

        if (isPasswordUnique(password) && username != password) {
            break;
        } else if (!isPasswordUnique(password)) {
            cout <<red<< "Password already exists. Please choose a different password." <<RESET<< endl;
        } else {
            cout<<red<< "Username and password cannot be the same. Please try again." <<RESET<< endl;
        }
    }

    users.push_back(User(username, password));
    saveUserDataToFile();
    cout << "\n";
    cout <<green<< "Registration successful." <<RESET<< endl;
}

User* loginUser() {
    printBorder();
    cout << setw(40) << "Login" << endl;
    printBorder();

    string username, password;
    
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    char ch;
    password = "";
    while ((ch = _getch()) != '\r') {
        cout << '*';  // Display '*' for each character entered
        password += ch;
    }
    cout << endl;

    for (User& user : users) {
        if (user.username == username && user.password == password) {
            cout << "\n";
            cout <<green<< "Login successful." <<RESET<< endl;
            return &user;
        }
    }

    cout <<red<< "Login failed. Incorrect username or password." <<RESET<< endl;
    return nullptr;
}

// Function to enroll in a course
void EnrollInCourse() {
    if (!loggedIn) {
        cout << "You need to be logged in to enroll in a course." << endl;
        return;
    }

    printBorder();
    cout << setw(40) << "Available Courses" << endl;
    printBorder();

    for (int i = 0; i < courses.size(); ++i) {
        cout << i + 1 << ". " << courses[i].name << endl;
    }

    int choice;
    cout << "Enter the course number to enroll: ";
    cin >> choice;

    if (choice >= 1 && choice <= courses.size()) {
        currentUser->enrolledCourses.push_back(courses[choice - 1]);
        cout<<green<< "Enrollment successful!" <<RESET<< endl;
    } else {
        cout <<red<< "Invalid course selection." <<RESET<< endl;
    }
}

// Function to display a quiz with borders
void displayQuiz(const vector<Question>& quiz) {
    printBorder();
    cout << setw(40) << "Quiz" << endl;
    printBorder();

    for (int i = 0; i < quiz.size(); i++) {
        cout << "Question " << (i + 1) << ": " << quiz[i].definition << endl;
        for (const string& option : quiz[i].options) {
            cout << "  - " << option << endl;
        }
        cout << "------------------------------------------------------" << endl;
    }
}

// Function to take a quiz
int takeQuiz(const vector<Question>& quiz) {
    int score = 0;
    for (int i = 0; i < quiz.size(); i++) {
        cout << "Enter your choice for question " << (i + 1) << " (1-" << quiz[i].options.size() << "): ";
        int userAnswer;
        cin >> userAnswer;
        if (userAnswer == quiz[i].correctOption) {
            cout <<green<< "Correct!" <<RESET<< endl;
            score++;
        } else {
            cout <<red<< "Incorrect. The correct answer is: "<<RESET<< quiz[i].options[quiz[i].correctOption - 1] << endl;
        }
    }
    currentUser->score += score;
    saveUserDataToFile();
    return score;
}

// Function to start a chapter with improved formatting
void StartChapter() {
    if (!loggedIn) {
        cout<<yellow<< "You need to be logged in to start a chapter."<<RESET<< endl;
        return;
    }

    if (currentUser->enrolledCourses.empty()) {
        cout <<red<< "You are not enrolled in any courses yet. Please enroll in a course first."<<RESET<< endl;
        return;
    }

    printBorder();
    cout << setw(40) << "Enrolled Courses" << endl;
    printBorder();

    for (int i = 0; i < currentUser->enrolledCourses.size(); ++i) {
        cout << i + 1 << ". " << currentUser->enrolledCourses[i].name << endl;
    }

    int courseChoice;
    cout << "Enter the course number to start learning: ";
    cin >> courseChoice;

    if (courseChoice >= 1 && courseChoice <= currentUser->enrolledCourses.size()) {
        Course& selectedCourse = currentUser->enrolledCourses[courseChoice - 1];

        printBorder();
        cout << setw(40) << "Course: " + selectedCourse.name << endl;
        printBorder();

        // Display chapters
        printBorder();
        cout << setw(40) << "Chapters" << endl;
        printBorder();

        for (int i = 0; i < selectedCourse.chapters.size(); ++i) {
            cout << i + 1 << ". " << selectedCourse.chapters[i] << endl;
        }

        int chapterChoice;
        cout << "Enter the chapter number to start: ";
        cin >> chapterChoice;

        if (chapterChoice >= 1 && chapterChoice <= selectedCourse.chapters.size()) {
            string selectedChapterName = selectedCourse.chapters[chapterChoice - 1];
            vector<Question>& selectedChapter = selectedCourse.chapterQuizzes[selectedChapterName];
            string chapterDefinition = selectedCourse.chapterDefinitions[selectedChapterName];

            printBorder();
            cout << setw(40) << "Chapter: " + selectedChapterName << endl;
            printBorder();

            // Display chapter definition
            cout <<yellow<< "C++ is a general-purpose programming language and is widely used nowadays for competitive programming. "<<RESET << chapterDefinition << endl;

            // Take quiz for this chapter
            printBorder();
            cout << setw(40) <<cyan<< "Starting quiz for this chapter"<<RESET << endl;
            printBorder();

            displayQuiz(selectedChapter);

            int score = takeQuiz(selectedChapter);
            cout << "Your score for this chapter: " << score << " out of " << selectedChapter.size() << endl;
        } else {
            cout <<red<< "Invalid chapter selection."<<RESET << endl;
        }
    } else {
        cout <<red<< "Invalid course selection."<<RESET<< endl;
    }
}

int main() {
    //welcome pattern call 
     int i,j;
    WelcomePattern WP;
    WP.pattern( i, j);
   WP.Traingle(i,j);
    loadUserDataFromFile();

    // Add courses details
    Course c1;
    c1.name = "C++ Programming";
    c1.chapters = { "Introduction to C++", "Variables and Data types in C++", "Input/Output in C++", "Operators in C++", "Conditional Statements and loops", "Functions in C++", "Pointers and memory allocation", "Arrays", "Strings", "Object-oriented programming (OOPS)", "Exception handling", "STL in C++" };
    courses.push_back(c1);

    // Define the quiz questions for "Introduction to C++"
    vector<Question> introToCppQuiz;
    Question q1;
    q1.definition = "What is C++?";
    q1.options = { "A programming language","A type of coffee","An animal" };
    q1.correctOption = 1;
    introToCppQuiz.push_back(q1);

    Question q2;
    q2.definition = "When was C++ first developed?";
    q2.options = { "1980","1995","2005" };
    q2.correctOption = 1;
    introToCppQuiz.push_back(q2);

    // Add the quiz questions to the corresponding chapter and set chapter definition
    courses[0].chapterQuizzes["Introduction to C++"] = introToCppQuiz;
    //courses[0].chapterDefinitions["Introduction to C++"] = "C++ is a general-purpose programming language and is widely used nowadays for competitive programming.";

    Course c2;
    c2.name = "Java Programming";
    c2.chapters = { "Introduction to Java", "Variables in Java" };
    courses.push_back(c2);

    while (true) {
        if (loggedIn) {
            printBorder();
            cout << "1. Enroll in a Course" << endl;
            cout << "2. Start Learning a Chapter" << endl;
            cout << "3. View Score" << endl;
            cout << "4. Logout" << endl;
            cout << "5. Quit" << endl;
            printBorder();
        } else {
            printBorder();
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Quit" << endl;
            printBorder();
        }

        int choice;
        cin >> choice;

        if (loggedIn) {
            switch (choice) {
                case 1:
                    EnrollInCourse();
                    break;
                case 2:
                    StartChapter();
                    break;
                case 3:
                    printBorder();
                    cout << "Your total score: " << currentUser->score << endl;
                    printBorder();
                    break;
                case 4:
                    loggedIn = false;
                    currentUser = nullptr;
                    break;
                case 5:
                    saveUserDataToFile();
                    return 0;
                default:
                    cout <<red<< "Invalid choice."<<RESET<< endl;
            }
        } else {
            switch (choice) {
                case 1:
                    Register();
                    break;
                case 2:
                    currentUser = loginUser();
                    if (currentUser != nullptr) {
                        loggedIn = true;
                    }
                    break;
                case 3:
                    saveUserDataToFile();
                    return 0;
                default:
                    cout <<red<< "Invalid choice."<<RESET<< endl;
            }
        }
    }

    return 0;
}


