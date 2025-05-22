# AP1400-2 Homework 3 - Binary Search Tree

## Build & Run Commands
- Build project: `mkdir -p build && cd build && cmake .. && make`
- Run all tests: `cd build && ./main`
- Run single test: `cd build && ./main --gtest_filter=HW3Test.TEST<num>` (e.g., `./main --gtest_filter=HW3Test.TEST1`)
- Debug mode: Change `if (false)` to `if (true)` in main.cpp and add code to the debug section

## Code Style Guidelines
- Class members: snake_case (e.g., `find_node`, `add_node`)
- Variables: snake_case (e.g., `int test_value`)
- No using namespace in header files (except specific using declarations)
- Include proper memory management (destructors, copy/move constructors, assignment operators)
- Always check if a node exists before dereferencing pointers
- Return nullptr for function failures rather than using exceptions
- When implementing BST operations, follow BST properties (left < node < right)
- Use std::function for passing callbacks (as in bfs function)
- Format output with proper spacing and alignment as shown in test cases