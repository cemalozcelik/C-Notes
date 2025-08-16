# Day 11 - Functions and Modular Programming in C

## Comments in C Programming

### Types of Comments
- **Single-line comments**: `//` (introduced in C99)
- **Multi-line comments**: `/* */` (traditional C style)

### Good Commenting Practices
- Avoid unnecessary comments - good variable and function names eliminate the need for many comments
- Best comment is no comment at all
- Many comments are written because of poor code quality
- Code that should be converted to functions often gets commented instead
- **Comment out**: Making code inactive by turning it into comments
- Commented-out code should not remain in production

### Example Comment Structure
```c
/*************************************************
*   file: is_prime.c
*   description: returns prime numbers
*   author: Ali Veli
*   copyright: Dell Inc.
*   last update: 12.07.1998
***************************************************/
```

## Function Concepts

### Three Main Operations with Functions
1. **Define** a function
2. **Call** a function  
3. **Declare** a function

### Function Declarations vs Definitions
- **Declaration**: Tells compiler about function's existence, return type, and parameters
- **Definition**: Contains the actual implementation of the function
- Functions can be called even if not defined in same file (backward compatibility)
- C++ requires proper declarations, C is more lenient

### Function Declaration Syntax
```c
int func(int x);        // with parameter type
int func(int);          // parameter name optional
int func();             // no parameter information given
int func(void);         // explicitly no parameters
```

### External References and Linking
- Compiler creates special names in object files for function calls
- These are called **external references**
- Linker combines object files and resolves these references
- Function code doesn't need to be in same source file

## C Module Structure

### Two-File System
Every C module consists of two files:
1. **Implementation file** (`.c` extension)
   - Contains global variables
   - Contains function definitions
   - Example: `file1.c`

2. **Header file** (`.h` extension)
   - Contains function declarations
   - Contains global variable declarations
   - Contains preprocessor commands
   - Contains macro definitions
   - Example: `file1.h`

### Using Modules
- To use functions from another module: `#include "module.h"`
- Header files provide interface to the module
- Standard library functions (like `printf`) work the same way
- `stdio.h` contains declaration for `printf`

### Header File Contents
1. Function declarations
2. Global variable declarations
3. Preprocessor directives
4. Macro definitions
5. Type definitions
6. Constants

## Practical Examples

### Module Organization Example
```
math_utils.h    // declarations
math_utils.c    // implementations
main.c          // uses the module
```

### Function Declaration Examples
```c
// In header file
int is_prime(int number);
int calculate_sum(int a, int b);
void print_array(int arr[], int size);
double get_average(void);
```

### Compilation Process
1. Preprocessor processes `#include` directives
2. Compiler generates object files with external references
3. Linker combines object files and resolves references
4. Executable is created

## Assignment Topics

### Perfect Numbers
- A positive integer equal to sum of its proper positive divisors
- Examples: 6 (1+2+3), 28 (1+2+4+7+14)
- First few: 6, 28, 496, 8128

### Armstrong Numbers
- Number equal to sum of its digits raised to power of number of digits
- Examples: 
  - 153 = 1³ + 5³ + 3³
  - 9474 = 9⁴ + 4⁴ + 7⁴ + 4⁴
