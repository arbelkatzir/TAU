#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure Definitions
typedef struct point {
    double x, y, z;
} Point;

typedef struct triangle {
    Point p, q, r;
} Triangle;

// Function to compute the Euclidean distance between two points in 3D space
double distance(Point a, Point b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

// Function to calculate the perimeter of a triangle in 3D
double perimeter(const Triangle* t) {
    return distance(t->p, t->q) + distance(t->p, t->r) + distance(t->q, t->r);
}

// Function to calculate the area of a triangle in 3D
double area(const Triangle* t) {
    // Calculate vectors
    double ux = t->q.x - t->p.x;
    double uy = t->q.y - t->p.y;
    double uz = t->q.z - t->p.z;

    double vx = t->r.x - t->p.x;
    double vy = t->r.y - t->p.y;
    double vz = t->r.z - t->p.z;

    // Cross product (u x v)
    double crossX = uy * vz - uz * vy;
    double crossY = uz * vx - ux * vz;
    double crossZ = ux * vy - uy * vx;

    // Area = 0.5 * |u x v|
    double crossLength = sqrt(crossX * crossX + crossY * crossY + crossZ * crossZ);
    return 0.5 * crossLength;
}

// Function to dynamically allocate and initialize a Triangle
Triangle* calculateTriangle() {
    // Allocate memory for the Triangle
    Triangle* t = (Triangle*)malloc(sizeof(Triangle));
    if (t == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Prompt the user for input
    printf("Enter the coordinates of the 3 points of the triangle (x, y, z) format:\n");
    printf("Point 1 (x y z): ");
    scanf("%lf %lf %lf", &t->p.x, &t->p.y, &t->p.z);

    printf("Point 2 (x y z): ");
    scanf("%lf %lf %lf", &t->q.x, &t->q.y, &t->q.z);

    printf("Point 3 (x y z): ");
    scanf("%lf %lf %lf", &t->r.x, &t->r.y, &t->r.z);

    return t;
}

int main() {
    // Dynamically allocate and initialize the Triangle
    Triangle* t = calculateTriangle();
    double triangle_perimeter = perimeter(t);
    double triangle_area = area(t);

    // Print the results
    printf("Perimeter: %.6f\n", triangle_perimeter);
    printf("Area: %.6f\n", triangle_area);

    // Free the dynamically allocated memory
    free(t);

    return 0;
}