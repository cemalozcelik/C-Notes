# C Programming Day 14 Notes

## Function-like Macros

### Why Use Function-like Macros?

Function-like macros perform a **"trick"**:
- Look like function calls but no actual function exists
- Preprocessor takes function-call-like code and performs **replacement**
- **Goal:** Eliminate the function entirely

### Advantages:
1. **Cost:** Function entry/exit overhead eliminated
2. **Optimization:** Compiler can optimize better across larger code blocks
3. **Functions are "black boxes"** for compiler - cannot optimize through them

### Critical Parentheses Rules

From Day 13, we know parentheses are vital:

```c
// WRONG - No parentheses
#define SQUARE(a) a * a
int y = SQUARE(x + 1);  // Becomes: x + 1 * x + 1 = WRONG!

// BETTER - Parameter parentheses
#define SQUARE(a) (a) * (a)
int y = SQUARE(x + 1);  // Becomes: (x + 1) * (x + 1) = Better

// STILL WRONG - Division precedence issue
int y = 100 / SQUARE(x);  // Becomes: 100 / (x) * (x) = WRONG!

// CORRECT - Full expression parentheses
#define SQUARE(a) ((a) * (a))
int y = 100 / SQUARE(x);  // Becomes: 100 / ((x) * (x)) = CORRECT!
```

### Macro Side Effects - DANGEROUS!

```c
#define square(a) ((a) * (a))

int a = 9;
int b = square(a++);  // Becomes: ((a++) * (a++)) -> UNDEFINED BEHAVIOR!
```

**Rule:** Never use side-effect parameters with macros!

### Macro vs Function Priority

```c
int square(int x) {
    printf("function called\n");
    return x * x;
}

#define square(x) ((x) * (x))

int main() {
    int b = square(a);      // MACRO wins (preprocessor runs first)
    int c = (square)(a);    // FUNCTION called (macro name in parentheses)
}
```

### Function Definition Protection
```c
#define square(x) ((x) * (x))

// WRONG - Macro will corrupt function definition
int square(int x) { ... }  // Becomes: int ((x) * (x))(int x)

// CORRECT - Protect function name
int (square)(int x) { ... }  // Function name in parentheses
```

## Preprocessor Operators - Advanced

### 1. `#` - Stringification Operator
**Unary prefix operator** - converts parameter to string:

```c
#define str(x) #x

int main() {
    printf(str(HELLO));  // printf("HELLO");
    return 0;
}
```

### Practical Debug Usage:
```c
#define iprint(x) printf(#x " = %d\n", x);

int main() {
    int value = 42;
    iprint(value);         // Output: value = 42
    iprint(value * 2);     // Output: value * 2 = 84
    iprint(value + 100);   // Output: value + 100 = 142
}
```

This is excellent! Macro prints both variable name and value.

### 2. `##` - Token Pasting Operator
**a ## b → ab**

```c
#define concat(x,y) x##y

int main() {
    int value = 0;
    ++concat(val, ue);  // Becomes: ++value
    printf("value = %d\n", value);  // Output: value = 1
}
```

### Creating Function Templates:

Manual approach vs macro approach:

```c
// Manual writing:
int func_int(int a, int b) {
    int c = a*b + 258;
    int d = c * 3 / 5;        
    return c*d/2;
}

double func_double(double a, double b) {
    double c = a*b + 258;
    double d = c * 3 / 5;        
    return c*d/2;
}

// Macro approach - much more practical:
#define make_func(t) t func_##t(t a, t b) \
{ \
    t c = a * b + 258; \
    t d = c * 3 / 5;  \
    return c * d / 2; \
}

make_func(int)    // Creates func_int function
make_func(long)   // Creates func_long function  
make_func(double) // Creates func_double function

int main() {
    int x = func_int(12, 24);
    double y = func_double(2.5, 7.5);
}
```

### Do-While Trick (From Day 13):

```c
// Wrong usage - breaks if-else
#define swap(a,b) {int temp = a; a = b; b = temp;}

int main() {
    int x = 10, y = 45;
    if (x > y)
        swap(x, y); // Syntax error! ; breaks if-else structure
    else
        ++x;
}

// Correct usage - do-while solution
#define swap(a,b) do {int temp = a; a = b; b = temp;} while(0)

int main() {
    int x = 10, y = 45;
    if (x > y)
        swap(x, y); // Now safe
    else
        ++x;
}
```

**Why do-while(0)?**
- do-while loop ends with `;` after while
- We leave it empty in macro so code's `;` completes it without syntax error

### Strange-Looking Examples:

```c
#define isupper(c) ((c) >= 'A' && (c) <= 'Z')

int main() {
    int c = 'A';
    if isupper(c)   // No parentheses! Macro already has them
    {               // Weirdness: Normally if statement needs parentheses
        printf("ok");
    }
}
```

## Conditional Compilation - Introduction

Allows different code to be compiled under different conditions:

- **Hardware-dependent** compilation
- **OS-dependent** compilation  
- **Compiler-dependent** compilation
- **Version-dependent** compilation
- **Region/country-dependent** compilation
- **Language-dependent** compilation

### Basic Commands:
```c
#if      // Preprocessor expression (integer constant expressions only)
#endif
#else
#elif
#ifdef   // if defined - is macro defined?
#ifndef  // if not defined - is macro not defined?
#undef   // remove macro definition
```

### Important: Preprocessor Expression
- **Only integer constant expressions**
- **No real numbers!**

```c
#define SIZE 100
#define PRC 3.1234    

#if SIZE > 10        // Correct - integer comparison
    typedef int Word;
#endif

#if PRC > 4.23123    // ERROR! - real number comparison
    // This line won't work
#endif
```

### Examples:

#### 1. Simple Condition:
```c
#define SIZE 100

// If this if is entered, gives codes to compiler; if not, doesn't
#if SIZE > 10
    #include "utility.h"
    typedef int Word;
    Word a[10];
#else
    #include "futility.h"
    typedef unsigned int Word;
    Word a[20];
#endif
```

#### 2. ifdef/ifndef Usage:
```c
#define DEBUG  // Defines DEBUG (value doesn't matter)

#ifdef DEBUG   // If DEBUG is defined, enters here
    #include "utility.h"
    typedef int Word;
    Word a[10];
#else         // If DEBUG is not defined, goes to else
    #include "futility.h"
    typedef unsigned int Word;
    Word a[20];
#endif
```

**ifndef** = if not defined:
```c
#ifndef DEBUG      // If DEBUG is NOT defined, enters
    enum Colors {Blue, Red};
#else             // If DEBUG is defined, comes here
    enum Colors {White, Yellow};
#endif
```

#### 3. elif Ladder:
Using elif instead of nested if is cleaner:

```c
#define EUR 0
#define USD 1
#define GBP 2
#define JPY 3

#define CURRENCY EUR

#if CURRENCY == EUR
    const char *currency = "Euro";
#elif CURRENCY == USD
    const char *currency = "Dollar";
#elif CURRENCY == GBP
    const char *currency = "Pound";
#elif CURRENCY == JPY
    const char *currency = "Yen";
#endif
```

### `defined` Operator:

**Preprocessor operator** - checks if macro is defined:

```c
#define DEBUG
#define RELEASE

// These are the same:
#ifdef DEBUG
#if defined DEBUG

// These are the same:
#ifndef DEBUG  
#if !defined DEBUG

// defined's advantage - multiple checks:
#if defined DEBUG && defined RELEASE
    int a = 0;
#endif

// Single ifdef can't do this - would need nesting:
#ifdef DEBUG
    #ifdef RELEASE  // Must nest
        typedef int Word;
    #endif
#endif
```

## Multiple Inclusion Guard

> **Very Important!** A header file should not be included multiple times.

### Problem:
```c
// utility.h
struct Data {
    int x, y, z;
};

// umut.h
#include "utility.h"

// mehmet.h  
#include "utility.h"

// main.c
#include "umut.h"
#include "mehmet.h"    // struct Data included twice!
```

**Result:** `struct type redefinition` error!

### Solution 1: Manual Guard (Classic Method)
```c
// utility.h
#ifndef UTILITY_H      // If UTILITY_H not defined, enter
#define UTILITY_H      // Define UTILITY_H

struct Data {          // First include compiles this part
    int x, y, z;       
};                     // Second include skips this part because
                       // UTILITY_H is already defined
#endif
```

### Rule:
```c
#ifndef MODULE_H    // Macro name matching file name
#define MODULE_H

// Code here

#endif
```

### Solution 2: Pragma Once (Modern)
```c
// utility.h
#pragma once       // Compiler adds this automatically

struct Data {
    int x, y, z;
};
```

**Advantage:** Single line, cleaner
**Disadvantage:** Not all compilers may support

## #undef Usage

> **Removes macro definition**

### Why Use It?

#### 1. Macro Redefinition Error (Undefined Behavior):
```c
#define SIZE 100
#define SIZE 600    // ERROR! Macro redefinition - Undefined Behavior
```

To prevent this:
```c
#include "ali.h"     // SIZE might be defined
#include "veli.h"    // SIZE might be defined  
#include "kudret.h"  // SIZE might be defined

#undef SIZE          // Safe cleanup (no error if not defined)
#define SIZE 1000    // Safe redefinition
```

#### 2. Giving Scope to Macros:
```c
void func() {
    #define SIZE 1000
    
    // SIZE macro starts from where this command is located
    // Including files will replace SIZE with 1000
    // Our goal is to make it effective only in this function
    
    int array[SIZE];  // SIZE used here
    
    #undef SIZE       // We gave "scope" to the macro
}
// Now SIZE is not defined

#define max(x,y) (a > b ? a : b)
// After function usage
#undef max  // Cleanup
```

### Important Note:
```c
int main() {
    #if MAX > 0      // MAX is not defined
        typedef unsigned char type;
    #endif
}
```

**Rule:** Undefined macros take **value 0** in if statements!
- If MAX is not defined, MAX = 0 is seen
- That's why it doesn't enter the if

## Predefined Symbolic Constants

> **FROM HERE ON PREDEFINED SYMBOLIC CONSTANTS will be seen** *(from our notes)*

There are macros that have no **define command**! By language rules, preprocessor puts these into replacement operation.

We can use many macros **without including** anything:

| Macro | Description | Example Value |
|-------|-------------|---------------|
| `__LINE__` | Line number | 42 |
| `__FILE__` | File name | "main.c" |
| `__DATE__` | Compilation date | "Oct 15 2024" |
| `__TIME__` | Compilation time | "14:30:25" |
| `__STDC__` | Standard C compliance | 1 |
| `__func__` | Function name (C99) | "main" |

### Practical Usage:

```c
int main() {
    printf("Line number: %d\n", __LINE__);  // Output: Line number: 2
    printf("File name: %s\n", __FILE__);    // Output: File name: main.c
    return 0;
}
```

### Perfect for Debug:
```c
void func(int x) {
    if (x == 0) {
        printf("ERROR: Division by zero in %s function at line %d in file %s!\n", 
               __func__, __LINE__, __FILE__);
        abort();
    }
    
    int y = 5;
    y /= x;
}

int main() {
    func(0);  // ERROR: Division by zero in func function at line 3 in file main.c!
}
```

## When to Use Function-like Macros

**Advantages:**
- No function call overhead
- Better performance for simple operations
- Critical in embedded programming

**Use When:**
- Code is simple (one-liner)
- Called frequently
- Performance is critical
- Low computational cost

**Avoid When:**
- Complex logic
- Side effects possible
- Debugging needed (macros hard to debug)

## Summary

**Preprocessor** is a powerful tool but must be used carefully:

- **Text processing** before compiler
- **Macros** provide performance advantage but carry security risk
- **Preprocessor operators** (`#`, `##`) are powerful code generation tools
- **Conditional compilation** enables platform-independent code
- **Multiple inclusion guard** is critical for header file safety
- **Predefined macros** are useful for debug and meta-programming

**Most Important Rules:**
1. Put macro parameters in parentheses
2. Use header guards
3. Avoid side effects
