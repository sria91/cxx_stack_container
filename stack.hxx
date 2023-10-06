#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename T, std::size_t capacity>
class Stack {
    T _stack[capacity];
    std::size_t _top = 0;

    static void * operator new(std::size_t); // To prevent heap allocation of scalar objects
    static void * operator new [] (std::size_t); // To prevent heap allocation of array of objects

public:
    void enstack(T data) {
        if (_top < capacity) {
            _stack[_top++] = data;
        } else {
            throw std::runtime_error("Stack is full");
        }
    }

    void destack() {
        if (_top) {
            --_top;
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }

    T top() const {
        if (_top) {
            return _stack[_top - 1];
        } else {
            throw std::runtime_error("Stack is empty");
        }
    }

    std::size_t height() const {
        return _top;
    }

    bool is_empty() const {
        return _top == 0;
    }

    bool is_full() const {
        return _top == capacity;
    }

    void clear() {
        _top = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& s) {
        if (s._top == 0) {
            os << '_';
            return os;
        }
        os << '_' << std::endl;
        for (std::size_t i = s._top; i > 1; --i) {
            os << s._stack[i - 1] << std::endl;
        }
        os << s._stack[0];
        return os;
    }
};
