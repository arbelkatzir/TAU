#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for Student
typedef struct Student {
    int ID;
    char name[50];
    int age;
    float GPA;
    struct Student* next;  // Pointer to the next student in the list
} Student;

// Function to create a new student dynamically
Student* createStudent(int ID, const char* name, int age, float GPA) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return NULL; // Return NULL if memory allocation fails
    }

    // Initialize the student's fields
    newStudent->ID = ID;
    strcpy(newStudent->name, name); // Copy the name into the struct
    newStudent->age = age;
    newStudent->GPA = GPA;
    newStudent->next = NULL; // Initialize the next pointer to NULL

    return newStudent; // Return the pointer to the newly created student
}

// Function to check if an ID is unique
int isUniqueID(Student* head, int ID) {
    Student* current = head;
    while (current != NULL) {
        if (current->ID == ID) {
            return 0; // ID is not unique
        }
        current = current->next;
    }
    return 1; // ID is unique
}

// Function to create a linked list of students
Student* createStudentList() {
    int n, ID, age;
    float GPA;
    char name[50];

    printf("Enter number of students: ");
    scanf("%d", &n);
    getchar(); // Clear the newline character from the buffer

    Student* head = NULL;
    Student* temp = NULL;

    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);

        // Ensure ID is unique
        do {
            printf("ID: ");
            scanf("%d", &ID);
            getchar(); // Clear the newline character from the buffer
            if (!isUniqueID(head, ID)) {
                printf("ID already exists. Please enter a unique ID.\n");
            }
        } while (!isUniqueID(head, ID));

        printf("Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove the trailing newline

        printf("Age: ");
        scanf("%d", &age);

        // Ensure GPA is positive
        do {
            printf("GPA: ");
            scanf("%f", &GPA);
            getchar(); // Clear the newline character from the buffer
            if (GPA < 0) {
                printf("GPA must be positive. Please enter a valid GPA.\n");
            }
        } while (GPA < 0);

        Student* newStudent = createStudent(ID, name, age, GPA);
        if (head == NULL) {
            head = newStudent;
        }
        else {
            temp->next = newStudent;
        }
        temp = newStudent;
    }

    return head;
}

// Function to find the student with the highest GPA
Student* findTopStudent(Student* head) {
    if (head == NULL) return NULL;
    Student* topStudent = head;
    Student* current = head;
    while (current != NULL) {
        if ((current->GPA > topStudent->GPA) || ((current->GPA == topStudent->GPA) && strcmp(current->name, topStudent->name) < 0)) {
            topStudent = current;
        }
        current = current->next;
    }
    return topStudent;
}

// Function to delete the student with the lowest GPA
Student* deleteLowestGPA(Student* head) {
    if (head == NULL) return NULL;
    Student* current = head, * prev = NULL, * minPrev = NULL;
    Student* minStudent = head;

    while (current != NULL) {
        if ((current->GPA < minStudent->GPA) ||
            ((current->GPA == minStudent->GPA) && strcmp(current->name, minStudent->name) < 0)) {
            minStudent = current;
            minPrev = prev;
        }
        prev = current;
        current = current->next;
    }

    if (minPrev == NULL) { // If the lowest GPA is at the head
        head = minStudent->next;
    }
    else {
        minPrev->next = minStudent->next;
    }

    free(minStudent);
    return head;
}

// Function to print all students
void printAllStudents(Student* head) {
    if (head == NULL) {
        printf("No students in the list.\n");
        return;
    }

    Student* current = head;
    while (current != NULL) {
        printf("ID: %d\nName: %s\nAge: %d\nGPA: %.2f\n",
            current->ID, current->name, current->age, current->GPA);
        current = current->next;
    }
}
// Function to print a student
void printStudent(Student* student) {

    printf("ID: %d\nName: %s\nAge: %d\nGPA: %.2f\n",
        student->ID, student->name, student->age, student->GPA);
}

// Function to free the memory of the entire student list
void freeStudentList(Student* head) {
    Student* current = head;
    while (current != NULL) {
        Student* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    // Create the student list
    Student* head = createStudentList();

    // Print all students
    printf("\nAll Students:\n");
    printAllStudents(head);

    // Find and print the top student with the highest GPA
    Student* topStudent = findTopStudent(head);
    if (topStudent != NULL) {
        printf("\nTop Student:\n");
        printStudent(topStudent);
    }


    // Delete the student with the lowest GPA and print the updated list
    head = deleteLowestGPA(head);
    printf("\nAfter deleting the student with the lowest GPA:\n");
    printAllStudents(head);

    // Free the memory of the student list
    freeStudentList(head);

    return 0;
}