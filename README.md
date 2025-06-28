# TimeSlice-Scheduler
A Round Robin Task Scheduler using Circular Queue in C++
# TimeSlice – Round Robin Task Scheduling System

This project simulates a CPU task scheduler using a Circular Queue and Round Robin logic, implemented in C++.

## 🔧 Features
- Add tasks with ID, name, and time
- Execute tasks using time-slicing (Round Robin)
- Automatically remove completed tasks
- Console display with colored output and formatted data

## 👨‍💻 Developed By
- Abhishek Shukla – Core Execution Logic & Output Design
- Ayush – Task Insertion and Input Handling
- Rohit – Task Structure & Debugging

## 🖥️ Technologies
- Language: C++
- Concept: Data Structures (Circular Queue)
- Interface: Console I/O (with ANSI formatting)


#include <iostream>
#include <string>
#include <iomanip> 
using namespace std;


struct Task {
    int id;
    string name;
    int timeLeft;
    Task* next;  
};


Task *front1 = 0, *rear = 0, *nn, *temp, *loc;


const string separator = "=============================================================";
const string line = "-------------------------------------------------------------";


void printHeader(string title) {
    cout << "\n\033[1;36m" << separator << "\033[0m" << endl;
    cout << "\033[1;33m" << setw(45) << right << title << "\033[0m" << endl;
    cout << "\033[1;36m" << separator << "\033[0m" << endl;
}


void insertion(int id, string name, int totalTime) {
    nn = new Task;
    nn->id = id;
    nn->name = name;
    nn->timeLeft = totalTime;

  
    if (rear == 0) {
        front1 = rear = nn;
        nn->next = front1;  // make it circular
    } else {
       
        rear->next = nn;
        nn->next = front1;
        rear = nn;
    }
}


void traverse() {
    if (front1 == 0) {
        cout << "\n\033[1;31mNo tasks remaining.\033[0m\n";
        return;
    }

    temp = front1;
    printHeader("Remaining Tasks");

    cout << left << setw(10) << "Task ID"
         << setw(25) << "Task Name"
         << setw(15) << "Time Left" << endl;
    cout << line << endl;

   
    do {
        cout << left << setw(10) << temp->id
             << setw(25) << temp->name
             << setw(15) << temp->timeLeft << endl;
        temp = temp->next;
    } while (temp != front1);
    cout << separator << "\n";
}


void roundRobin(int tq) {
    if (front1 == 0) {
        cout << "\n\033[1;31mNo tasks to execute.\033[0m\n";
        return;
    }

    Task *curr = front1;  
    Task *prev = rear;    
    printHeader("Round Robin Execution");
    cout << "\033[1;35mTime Quantum: " << tq << "\033[0m\n\n";
    cout << "Execution Sequence:\n";

 
    while (front1 != 0) {
      
        
        if (curr->timeLeft <= tq) {
            cout << "\033[1;32mTask ID " << curr->id << " (" << curr->name
                 << ") ran for " << curr->timeLeft << " [Completed]\033[0m\n";

          
            if (curr == curr->next) {
                delete curr;
                front1 = rear = 0;
                break;
            } else {
               
                loc = curr;         
                curr = curr->next;   
                prev->next = curr;   
                
              
                if (loc == front1) front1 = curr;
                if (loc == rear) rear = prev;

                delete loc;
            }
        }

        // CASE 2: Task not finished, reduce time and move it to back
        else {
            cout << "\033[1;34mTask ID " << curr->id << " (" << curr->name
                 << ") ran for " << tq << "\033[0m\n";
            curr->timeLeft -= tq;  // decrease remaining time
            prev = curr;           // move prev forward
            curr = curr->next;     // move curr forward
        }
    }

    cout << separator << "\n";
}

int main() {
    int n, id, time, tq;
    string name;

    printHeader("Task Scheduler - Round Robin");
    cout << "Enter number of tasks: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Task ID: ";
        cin >> id;
        cout << "Enter Task Name: ";
        cin >> name;
        cout << "Enter Total Time: ";
        cin >> time;
        insertion(id, name, time);
    }

    cout << "\nEnter Time Quantum: ";
    cin >> tq;

    printHeader("Task List Before Execution");
    traverse();

    roundRobin(tq);  
    printHeader("Task List After Execution");
    traverse();

    cout << "\n\033[1;32mThank you for using the Task Scheduler!\033[0m\n";
    return 0;
}
