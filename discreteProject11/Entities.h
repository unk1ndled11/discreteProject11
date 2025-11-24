#ifndef ENTITIES_H
#define ENTITIES_H

#include "SimpleVector.h" // Include your custom vector

// Basic String Helper to avoid <string> if you want strict "no STL"
// But for simplicity in structs, we will use char arrays as seen in your main.cpp
#include <string.h>

struct Student {
    int id;
    char name[100];
    int semester;

    Student() : id(0), semester(0) { name[0] = '\0'; }
    Student(int i, const char* n, int s) : id(i), semester(s) {
        strcpy_s(name, 100, n); // strcpy_s is safer for Visual Studio
    }
};

struct Course {
    int id;
    char code[50];
    char title[100];
    int credits;

    Course() : id(0), credits(0) { code[0] = '\0'; title[0] = '\0'; }
    Course(int i, const char* c, const char* t, int cr) : id(i), credits(cr) {
        strcpy_s(code, 50, c);
        strcpy_s(title, 100, t);
    }
};

struct Faculty {
    int id;
    char name[100];
    char department[50];

    Faculty() : id(0) { name[0] = '\0'; department[0] = '\0'; }
    Faculty(int i, const char* n, const char* d) : id(i) {
        strcpy_s(name, 100, n);
        strcpy_s(department, 50, d);
    }
};

struct Room {
    int id;
    char code[50];
    int capacity;

    Room() : id(0), capacity(0) { code[0] = '\0'; }
    Room(int i, const char* c, int cap) : id(i), capacity(cap) {
        strcpy_s(code, 50, c);
    }
};

#endif