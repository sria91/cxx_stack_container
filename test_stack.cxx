#include <cassert>
#include "stack.hxx"

int main() {
    Stack<int, 3> stack;

    // Test empty stack
    assert(stack.is_empty());
    assert(stack.height() == 0);
    std::cout << stack << std::endl; 

    // Test enstack
    stack.enstack(1);
    std::cout << stack << std::endl; 
    assert(!stack.is_empty());
    assert(stack.height() == 1);
    assert(stack.top() == 1);

    // Test enstack full stack
    stack.enstack(2);
    stack.enstack(3);
    assert(stack.height() == 3);
    std::cout << stack << std::endl;
    try {
        stack.enstack(4);
    } catch (std::runtime_error &e) {
        assert(std::string(e.what()) == "Stack is full");
        assert(stack.is_full());
    }

    // Test destack
    stack.destack();
    std::cout << stack << std::endl; 
    assert(stack.height() == 2);
    assert(stack.top() == 2);

    // Test destack empty stack
    stack.destack();
    stack.destack();
    std::cout << stack << std::endl; 
    try {
        stack.destack();
    } catch (std::runtime_error &e) {
        assert(std::string(e.what()) == "Stack is empty");
    }

    // Test clear
    stack.enstack(1);
    stack.enstack(2);
    stack.enstack(3);
    std::cout << stack << std::endl; 
    stack.clear();
    std::cout << stack << std::endl; 
    assert(stack.is_empty());
    assert(stack.height() == 0);

    return 0;
}
