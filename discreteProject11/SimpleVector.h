#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H

template <typename T>
class SimpleVector {
private:
    T* data;
    int capacity;
    int currentSize;

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    SimpleVector() : data(nullptr), capacity(0), currentSize(0) {}

    // Copy constructor (Essential for managing data correctly without STL)
    SimpleVector(const SimpleVector& other) {
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            data[i] = other.data[i];
        }
    }

    ~SimpleVector() {
        if (data) delete[] data;
    }

    void push_back(const T& element) {
        if (currentSize == capacity) {
            resize();
        }
        data[currentSize++] = element;
    }

    void remove(int index) {
        if (index < 0 || index >= currentSize) return;
        for (int i = index; i < currentSize - 1; i++) {
            data[i] = data[i + 1];
        }
        currentSize--;
    }

    int getSize() const { return currentSize; }
    T& operator[](int index) { return data[index]; }
};

#endif