#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H

template <typename T>
class SimpleVector {
private:
    T* data;
    int capacity;
    int currentSize;

    // size adjust karnay wala function
    void resize() {
        // check if capacity is 0
        if (capacity == 0) {
            capacity = 1;
        }
        else {
            capacity = capacity * 2;
        }

        T* newData = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    // constructor
    SimpleVector() : data(nullptr), capacity(0), currentSize(0) {}

    // copy constructor for data management
    SimpleVector(const SimpleVector& other) {
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            data[i] = other.data[i];
        }
    }

    // destructor
    ~SimpleVector() {
        if (data) delete[] data;
    }

    // element add karnay wala function
    void push_back(const T& element) {
        if (currentSize == capacity) {
            resize();
        }
        data[currentSize++] = element;
    }

    // element remove karnay wala function
    void remove(int index) {
        if (index < 0 || index >= currentSize) return;
        for (int i = index; i < currentSize - 1; i++) {
            data[i] = data[i + 1];
        }
        currentSize--;
    }

    // getters
    int getSize() const { return currentSize; }
    T& operator[](int index) { return data[index]; }
};

#endif