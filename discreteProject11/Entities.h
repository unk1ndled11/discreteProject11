#ifndef ENTITIES_H
#define ENTITIES_H

#include <iostream>
#include <cstring>
#include "SimpleVector.h"

using namespace std;

// student structure
struct Student {
    int id;
    char name[100];
    int semester;

    Student() : id(0), semester(0) { name[0] = '\0'; }
    Student(int i, const char* n, int s) : id(i), semester(s) {
        int len = 0;
        while (n[len] != '\0' && len < 99) { name[len] = n[len]; len++; }
        name[len] = '\0';
    }
};

// course structure
struct Course {
    int id;
    char code[50];
    char title[100];
    int credits;

    // graph node implementation
    // stores ids of prereqs
    SimpleVector<int> prerequisiteIDs;

    Course() : id(0), credits(0) { code[0] = '\0'; title[0] = '\0'; }
    Course(int i, const char* c, const char* t, int cr) : id(i), credits(cr) {
        int len = 0;
        while (c[len] != '\0' && len < 49) { code[len] = c[len]; len++; }
        code[len] = '\0';

        len = 0;
        while (t[len] != '\0' && len < 99) { title[len] = t[len]; len++; }
        title[len] = '\0';
    }
};

// faculty structure
struct Faculty {
    int id;
    char name[100];
    char department[50];

    Faculty() : id(0) { name[0] = '\0'; department[0] = '\0'; }
    Faculty(int i, const char* n, const char* d) : id(i) {
        int len = 0;
        while (n[len] != '\0' && len < 99) { name[len] = n[len]; len++; }
        name[len] = '\0';

        len = 0;
        while (d[len] != '\0' && len < 49) { department[len] = d[len]; len++; }
        department[len] = '\0';
    }
};

// room structure
struct Room {
    int id;
    char code[50];
    int capacity;

    Room() : id(0), capacity(0) { code[0] = '\0'; }
    Room(int i, const char* c, int cap) : id(i), capacity(cap) {
        int len = 0;
        while (c[len] != '\0' && len < 49) { code[len] = c[len]; len++; }
        code[len] = '\0';
    }
};

#endif