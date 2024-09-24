#include <iostream>
#include <string>

using namespace std;

// Class to represent a single task node
class TaskNode {
public:
    int task_id;                // Unique identifier for the task
    string description;         // Description of the task
    int priority;               // Priority level of the task (higher means more important)
    TaskNode* next;             // Pointer to the next task node

    // Constructor to initialize a new task node
    TaskNode(int id, const string& desc, int prio)
        : task_id(id), description(desc), priority(prio), next(nullptr) {}
};

// Class to manage the task list
class TaskManagementSystem {
private:
    TaskNode* head;             // Pointer to the head of the linked list

public:
    // Constructor to initialize the task management system
    TaskManagementSystem() : head(nullptr) {}

    // Function to add a new task in the correct position based on priority
    void addTask(int task_id, const string& description, int priority) {
        TaskNode* newTask = new TaskNode(task_id, description, priority);

        // If the list is empty or the new task has higher priority than the head
        if (!head || priority > head->priority) {
            newTask->next = head;  // Link new task to current head
            head = newTask;        // Update head to new task
            return;
        }

        // Otherwise, find the correct position to insert the new task
        TaskNode* current = head;
        while (current->next && current->next->priority >= priority) {
            current = current->next; // Traverse the list
        }

        newTask->next = current->next; // Link new task to the next node
        current->next = newTask;        // Link current node to the new task
    }

    // Function to remove the highest priority task (at the head)
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove." << endl;
            return;
        }
        TaskNode* removedTask = head; // Store the task to be removed
        head = head->next;             // Move head to the next task
        cout << "Removed task: ID " << removedTask->task_id
             << ", Description: " << removedTask->description
             << ", Priority: " << removedTask->priority << endl;
        delete removedTask;            // Free memory
    }

    // Function to remove a specific task using its task ID
    void removeTaskById(int task_id) {
        if (!head) {
            cout << "No tasks to remove." << endl;
            return;
        }

        // If the task to remove is the head
        if (head->task_id == task_id) {
            TaskNode* removedTask = head;
            head = head->next;         // Update head to next task
            cout << "Removed task with ID " << task_id << endl;
            delete removedTask;        // Free memory
            return;
        }

        // Search for the task in the list
        TaskNode* current = head;
        while (current->next) {
            if (current->next->task_id == task_id) {
                TaskNode* removedTask = current->next;
                current->next = current->next->next; // Remove the task
                cout << "Removed task with ID " << task_id << endl;
                delete removedTask; // Free memory
                return;
            }
            current = current->next; // Move to the next task
        }

        cout << "Task with ID " << task_id << " not found." << endl; // Not found
    }

    // Function to view all tasks in the list
    void viewTasks() {
        if (!head) {
            cout << "No tasks available." << endl;
            return;
        }

        TaskNode* current = head;
        cout << "Tasks:" << endl;
        while (current) {
            cout << "ID: " << current->task_id
                 << ", Description: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next; // Move to the next task
        }
    }

    // Destructor to clean up the linked list
    ~TaskManagementSystem() {
        while (head) {
            TaskNode* temp = head;
            head = head->next;
            delete temp; // Free memory for each node
        }
    }
};

// Main function to run the task management system
int main() {
    TaskManagementSystem tms; // Create an instance of the task management system

    while (true) {
        // Display menu options
        cout << "\nTask Management System" << endl;
        cout << "1. Add a new task" << endl;
        cout << "2. View all tasks" << endl;
        cout << "3. Remove highest priority task" << endl;
        cout << "4. Remove a task by ID" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Choose an option: ";
        cin >> choice; // Get user choice

        switch (choice) {
            case 1: {
                int task_id, priority;
                string description;

                // Adding a new task
                cout << "Enter task ID: ";
                cin >> task_id;
                cout << "Enter task description: ";
                cin.ignore(); // Clear newline character from input buffer
                getline(cin, description); // Get full description
                cout << "Enter task priority (higher number means higher priority): ";
                cin >> priority;

                tms.addTask(task_id, description, priority); // Add the new task
                break;
            }
            case 2:
                // Viewing all tasks
                tms.viewTasks(); // Display all tasks
                break;
            case 3:
                // Removing the highest priority task
                tms.removeHighestPriorityTask(); // Remove and display the highest priority task
                break;
            case 4: {
                int task_id;
                // Removing a task by ID
                cout << "Enter task ID to remove: ";
                cin >> task_id;
                tms.removeTaskById(task_id); // Remove the specified task
                break;
            }
            case 5:
                // Exit the program
                cout << "Exiting the Task Management System." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl; // Handle invalid input
                break;
        }
    }

    return 0; // End of the program
}
