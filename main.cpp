#include <iostream>
#include <string>
#include <iomanip>  // for designing
using namespace std;

// Structure to represent a task
struct Task {
    int id;
    string name;
    int timeLeft;
    Task* next;  // pointer to the next task (for circular queue)
};

// Global pointers to manage the circular queue
Task *front1 = 0, *rear = 0, *nn, *temp, *loc;

// Aesthetic separators for output
const string separator = "=============================================================";
const string line = "-------------------------------------------------------------";

// Function to print colored headers
void printHeader(string title) {
    cout << "\n\033[1;36m" << separator << "\033[0m" << endl;
    cout << "\033[1;33m" << setw(45) << right << title << "\033[0m" << endl;
    cout << "\033[1;36m" << separator << "\033[0m" << endl;
}

// Function to insert a task into the circular queue
void insertion(int id, string name, int totalTime) {
    nn = new Task;
    nn->id = id;
    nn->name = name;
    nn->timeLeft = totalTime;

    // If the queue is empty
    if (rear == 0) {
        front1 = rear = nn;
        nn->next = front1;  // make it circular
    } else {
        // Insert at the end and update rear
        rear->next = nn;
        nn->next = front1;
        rear = nn;
    }
}

// Function to display all remaining tasks
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

    // Loop through the circular queue
    do {
        cout << left << setw(10) << temp->id
             << setw(25) << temp->name
             << setw(15) << temp->timeLeft << endl;
        temp = temp->next;
    } while (temp != front1);
    cout << separator << "\n";
}

// Round Robin execution logic
void roundRobin(int tq) {
    if (front1 == 0) {
        cout << "\n\033[1;31mNo tasks to execute.\033[0m\n";
        return;
    }

    Task *curr = front1;  // current task pointer
    Task *prev = rear;    // to keep track of previous task (important for deletion)

    printHeader("Round Robin Execution");
    cout << "\033[1;35mTime Quantum: " << tq << "\033[0m\n\n";
    cout << "Execution Sequence:\n";

    // Continue until all tasks are completed
    while (front1 != 0) {
        // CASE 1: Task will finish in this round
        if (curr->timeLeft <= tq) {
            cout << "\033[1;32mTask ID " << curr->id << " (" << curr->name
                 << ") ran for " << curr->timeLeft << " [Completed]\033[0m\n";

            // CASE 1.1: Only one task in queue
            if (curr == curr->next) {
                delete curr;
                front1 = rear = 0;
                break;
            } else {
                // CASE 1.2: More than one task
                loc = curr;          // store current task for deletion
                curr = curr->next;   // move to next task
                prev->next = curr;   // skip 'loc' in the queue

                // Update front and rear if needed
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

    roundRobin(tq);  // Core function to simulate round robin scheduling

    printHeader("Task List After Execution");
    traverse();

    cout << "\n\033[1;32mThank you for using the Task Scheduler!\033[0m\n";
    return 0;
}
