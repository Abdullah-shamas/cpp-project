#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <stack>
using namespace std;

void clearScreen() {
    
    system("CLS");
    
}

struct Node {
    char letter;
    Node* next;
};

struct User {
    string name;
    int age;
    int score;
    int wpm;
    int correctWords;
    int totalWords;
    User* next;
    User(string n, int a) {
        name = n;
        age = a;
        score = 0;
        wpm = 0;
        correctWords = 0;
        totalWords = 0;
        next = NULL;
    }
};

struct LessonNode {
    string lesson;
    LessonNode* next;
    LessonNode(string l) {
        lesson = l;
        next = NULL;
    }
};

class TypingTutorial {
    struct LessonHistory {
        LessonNode* head;

        LessonHistory(){
        	head=NULL;
		}

        void addLesson(const string& lesson) {
            LessonNode* newNode = new LessonNode(lesson);
            newNode->next = head;
            head = newNode;
        }

        void viewHistory() {
            if (!head) {
                cout << "No lessons completed yet.\n";
                return;
            }
            LessonNode* temp = head;
            cout << "Lesson History:\n";
            while (temp) {
                cout << "- " << temp->lesson << endl;
                temp = temp->next;
            }
        }
    } lessonHistory;

    User* head;
    User* current;
    int userCount;

    string lessons[5][5] = {
        {"The quick brown fox jumps over the lazy dog.",
         "The rain in Spain falls mainly on the plain.",
         "A journey of a thousand miles begins with a single step.",
         "To be or not to be, that is the question.",
         "All that glitters is not gold."},
        {"The pen is mightier than the sword.",
         "Knowledge is power.",
         "Do not go gentle into that good night.",
         "Ask not what your country can do for you, ask what you can do for your country.",
         "I think, therefore I am."},
        {"That which we call a rose by any other name would smell as sweet.",
         "In the end, we will remember not the words of our enemies, but the silence of our friends.",
         "Two things are infinite: the universe and human stupidity; and I'm not sure about the universe.",
         "I have not failed. I’ve just found 10,000 ways that won’t work.",
         "Success is not final, failure is not fatal: It is the courage to continue that counts."},
        {"The best way to predict the future is to invent it.",
         "Success usually comes to those who are too busy to be looking for it.",
         "Don’t watch the clock; do what it does. Keep going.",
         "You miss 100% of the shots you don’t take.",
         "Hardships often prepare ordinary people for an extraordinary destiny."},
        {"The only limit to our realization of tomorrow is our doubts of today.",
         "It does not matter how slowly you go as long as you do not stop.",
         "Act as if what you do makes a difference. It does.",
         "Success is how high you bounce when you hit bottom.",
         "What you get by achieving your goals is not as important as what you become by achieving your goals."}
    };

public:
    TypingTutorial() {
	 head=NULL; 
	 current=NULL;
	  userCount=0;
	   }

    void addUser(const string& name, int age) {
        if (userCount >= 5) {
            cout << "User limit reached. Cannot add more users.\n";
            return;
        }
        if (age < 8) {
            cout << "User age must be at least 8.\n";
            return;
        }

        User* newUser = new User(name, age);
        if (!head) {
            head = newUser;
        } else {
            User* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newUser;
        }
        userCount++;
    }

    void addPredefinedUsers() {
        addUser("Abdullah", 10);
        addUser("Faisal", 15);
        addUser("Zain", 25);
    }

    void listUsers() {
        if (!head) {
            cout << "No users available.\n";
            return;
        }
        User* temp = head;
        int count = 1;
        while (temp) {
            cout << count++ << ". Name: " << temp->name << ", Age: " << temp->age << endl;
            temp = temp->next;
        }
    }

    void selectUser() {
        listUsers();
        int choice;
        cout << "Select user by number: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        User* temp = head;
        int count = 1;
        while (temp) {
            if (count == choice) {
                current = temp;
                cout << "User " << current->name << " selected.\n";
                return;
            }
            temp = temp->next;
            count++;
        }
        cout << "Invalid selection.\n";
    }

    void startSession() {
        if (!current) {
            cout << "No user selected. Please select a user first.\n";
            return;
        }

        int category;
        if (current->age >= 8 && current->age <= 10) {
            category = 0;
        } else if (current->age > 10 && current->age <= 20) {
            category = 1;
        } else if (current->age > 20 && current->age <= 25) {
            category = 2;
        }else if (current->age > 25 && current->age <= 30) {
            category = 3;
        }else {
            category = 4;
        }

        cout << "Available lessons for user: " << current->name << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << lessons[category][i] << endl;
        }

        int choice;
        cout << "Choose a lesson (1-5): ";
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 5: ";
        }

        string selectedLesson = lessons[category][choice - 1];
        lessonHistory.addLesson(selectedLesson);

        string userInput;
        cout << "Type this: " << selectedLesson << endl;
        cout << "Start typing: ";
        cin.ignore();
        getline(cin, userInput);

        int accuracy = calculateAccuracy(userInput, selectedLesson);
        cout << "Accuracy: " << accuracy << "%\n";

        current->score += accuracy;
        current->correctWords++;
    }

    int calculateAccuracy(const string& typedText, const string& target) {
        int correct = 0;
        for (size_t i = 0; i < typedText.size() && i < target.size(); i++) {
            if (typedText[i] == target[i]) {
                correct++;
            }
        }
        return (correct * 100) / target.size();
    }

    void viewLessonHistory() {
        lessonHistory.viewHistory();
    }

    void startTypingGame() {
        string letters = "abcdefghijklmnopqrstuvwxyz";
        Node* head = new Node{letters[0], NULL};
        Node* current = head;

        for (size_t i = 1; i < letters.size(); i++) {
            current->next = new Node{letters[i], NULL};
            current = current->next;
        }
        current->next = head;

        int score = 0;
        clock_t startTime, endTime;

        cout << "\nTyping Game: Press the correct key in sequence!\n";
        current = head;
        do {
            cout << current->letter << " ";
            current = current->next;
        } while (current != head);
        cout << endl;

        cout << "\nGame starts now! Press the correct keys in order.\n";
        startTime = clock();

        current = head;
        stack<char> progressStack; 
        while (true) {
            char input;
            cin >> input;
            if (input == current->letter) {
                cout << "Correct: " << input << endl;
                progressStack.push(input); 
                current = current->next;
                score++;
            } else {
                cout << "Wrong key! Game over.\n";
                break;
            }
            if (score == 26) {
                cout << "\nYou completed all letters! Congratulations!\n";
                break;
            }
        }

        endTime = clock();
        double timeTaken = double(endTime - startTime) / CLOCKS_PER_SEC;
        double wpm = (score / 5.0) / (timeTaken / 60.0);
        cout << "\nYour score: " << score << " out of 26\n";
        cout << "Time taken: " << timeTaken << " seconds\n";
        cout << "WPM: " << wpm << endl;

        
        cout << "\nYour progress during the game:\n";
        while (!progressStack.empty()) {
            cout << progressStack.top() << " ";
            progressStack.pop();
        }
        cout << endl;

        current = head;
        Node* nextNode;
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
    }
};

void menu() {
    TypingTutorial tutorial;
    tutorial.addPredefinedUsers();

    int choice;
    do {
        clearScreen();
		cout<<endl;  
        cout<<"                                       *********TYPING TUTORIAL*"<<endl;
        cout <<"\n1. Add User\n2. Select User\n3. Start Lesson\n4. View Lesson History\n5. Start Typing Game\n6. Exit\nEnter choice: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        switch (choice) {
            case 1: {
                clearScreen(); 
                string name;
                int age;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter age: ";
                while (!(cin >> age) || age < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid age: ";
                }
                tutorial.addUser(name, age);
                break;
            }
            case 2:
                clearScreen();  
                tutorial.selectUser();
                break;
            case 3:
                clearScreen();  
                tutorial.startSession();
                break;
            case 4:
                clearScreen(); 
                tutorial.viewLessonHistory();
                break;
            case 5:
                clearScreen();  
                tutorial.startTypingGame();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();  
        }

    } while (choice != 6);
}

int main(){
	menu();
}
