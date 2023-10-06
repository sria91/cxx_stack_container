# (A case for) Creating a stack-allocated Stack container in C++

I've always looked inside the C++ STL and wondered why the library provided stack container is not allocated on the stack section but is actually allocated on the heap.

A container which is allocated on stack would be handy in embedded systems where the resource is constrained and the heap is costly.

So, can we really create a container that is allocated on the stack?

If you are also wondering the same, then this article is for you.

First, let's get some of the basics straight:

1. A stack is a data structure that follows the last-in-first-out (LIFO) principle, meaning the last item to get into a stack will be the first to get out of the stack. Think of it as a stack of plates - you add or remove the plates from the top of the stack.
    
2. When we create a stack of items we are going to specify the `capacity` of the stack, i.e., the number of items it can hold, which will be a static value. We will be specifying the capacity of the stack without losing the generalization capability of the container.
    
3. We are going to call the operation of adding an item to the stack as `enstack()`ing.
    
4. The operation of removing an item is going to be called `destack()`ing.
    
5. Other operations are:
    
    i. `top()` for accessing the topmost item.
        
    ii. `height()` will calculate the height of the stack.
        
    iii. `is_empty()` will tell whether the stack is empty.
        
    iv. `is_full()` will tell whether the stack is full.
        
    v. `clear()` will remove everything from the stack.
        

With the above priming, let's get started with some code.

You will generally tend to create a Stack container with fields like this:

```cpp
#include <cstddef>

template<typename T>
class Stack {
private:
    T* _dynamic_array;
    std::size_t _capacity;
    std::size_t _top;
};
```

This is loosely similar to the `std::stack` in the C++ STL and hence needs to allocate the `dynamic_array` pointer on the heap.

How can we make the Stack stack-allocated and hence defined at compile-time?

One might write the code similar to the following to represent a stack-allocated stack container with the following fields.

```cpp
#include <cstddef>

template<typename T>
class Stack {
private:
    static const std::size_t _CAPACITY = 100;
    T _static_array[_CAPACITY];
    std::size_t _top;
};
```

Here the capacity is hard coded within the container itself, which is not such a good idea. What if we want to have different stacks with different capacities? This approach is not going to help.

We want to make the capacity as configurable as the item type that the Stack can hold. The solution is to make the capacity a template argument.

```cpp
#include <cstddef>

template<typename T, std::size_t capacity>
class Stack {
private:
    T _stack[capacity];
    std::size_t _top = 0;
};
```

Now we can create a stack-allocated `Stack` data structure holding items of type `int` with capacity 100 as follows:

```cpp
Stack<int, 100> s;
```

But one problem remains. One could still create a heap-allocated `Stack` data structure by using the new operator as follows:

```cpp
auto *s = new Stack<int, 100>;
```

Can we completely prevent one from allocating an object on heap? Yes, we can do this by making the new operator private as follows:

```cpp
#include <cstddef>

template<typename T, std::size_t capacity>
class Stack {
private:
    T _stack[capacity];
    std::size_t _top = 0;

    static void * operator new(std::size_t); // To prevent heap allocation of scalar objects
    static void * operator new [] (std::size_t); // To prevent heap allocation of array of objects

public:
    // Implement all the earlier mentioned operations here
};
```

The complete code for this Stack container with all the earlier mentioned operations implemented is available [here](https://github.com/sria91/cxx_stack_container).

[Try online in a new Codespace](https://codespace.new/sria91/cxx_stack_container)
