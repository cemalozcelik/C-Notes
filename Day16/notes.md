# C Programming Day 16 - Notes

## Multiple Inclusion Guard

First thing to do in any header file - prevent multiple inclusions of the same declaration.

```c
#ifndef CUTILITY_H
#define CUTILITY_H

// header content here

#endif
```

**Alternative (compiler-specific):**
```c
#pragma once  // not 100% portable but widely supported
```

## Header File Organization

### cutility.h (Header File)
- Contains function declarations
- Contains macro definitions  
- Uses inclusion guard
- No implementation details

### cutility.c (Implementation File)
```c
#include "cutility.h"  // Always include your own header
#include <Windows.h>
#include <stdio.h>
```

**Why include your own header in .c file:**
1. Macros need to be expanded
2. Multiple inclusion guard protection
3. Forward declarations for functions calling each other

## Static vs External Linkage

### External (Public)
- Functions/variables accessible from other files
- Default behavior for global scope items

### Static (Private) 
- Functions/variables only accessible within current file
- Use `static` keyword at global scope:

```c
static int private_var = 10;        // file-private variable
static void helper_function() { }   // file-private function
```

**Note:** In local scope, `static` means different thing - static storage duration (variable lives for entire program).

---

## Type Conversions

Two main categories:
1. **Implicit** (automatic) - compiler does it automatically
2. **Explicit** (manual) - we do it with cast operators

### Arithmetic Conversions (Implicit)

**Type Rank Hierarchy (highest to lowest):**
```
Floating Point:
- long double
- double  
- float

Integer:
- long long
- long
- int

Sub-integer (all promote to int):
- short
- char
- _Bool
```

### Conversion Rules

1. **Different types in expression:** Convert to higher rank
2. **Sub-integer types:** Always promote to `int` first (integral promotion)
3. **Mixed signed/unsigned:** Convert to unsigned if same rank

```c
char c1 = 5, c2 = 10;
// c1 + c2 has type 'int' (integral promotion)

int x = 4;
unsigned int y = 0;
// x + y has type 'unsigned int'
```

### Dangerous Conversions

#### Signed/Unsigned Mix:
```c
int x = -1;           // binary: 1111 1111 1111 1111
unsigned int y = 2;   
// x converts to unsigned: 4,294,967,295
if (x < y)            // FALSE! (4 billion > 2)
    printf("true");
else 
    printf("false");  // This executes
```

#### Data Loss in Assignment:
```c
int i = 987;     // hex: 3DB
char c = i;      // keeps only DB part: 1101 1011
                 // = -37 (two's complement)
printf("%d", c); // prints -37
```

**Proper way (explicit cast):**
```c
c = (char)i;     // Shows intent, no warning
```

### Overflow Behavior

#### Signed Integer Overflow = Undefined Behavior
```c
int x = 1000, y = 1000;  // if int is 2 bytes
int result = x * y;      // UNDEFINED BEHAVIOR!
```

**Solution:**
```c
long result = x * 20L;   // force long arithmetic
```

#### Unsigned Overflow = Well-defined (wraps around)
```c
unsigned int x = UINT_MAX;
x + 1;  // equals 0 (wraps around)
x + 2;  // equals 1
// Behavior: (value) % (UINT_MAX + 1)
```

### Assignment Conversions

**Target type determines conversion:**
```c
double d = 10 / 3;    // Result: 3.0 (integer division first)
double d = 10 / 3.0;  // Result: 3.333... (double division)
```

### Character Conversions

```c
char c = 178;        // 178 > 127, so becomes negative
if (c == 178) {      // FALSE!
    printf("equal");
} else {
    printf("not equal"); // This executes
}
```

**Why?** 
- 178 in binary: `1011 0010`
- Interpreted as signed char: -78 (two's complement)
- -78 ≠ 178

**Correct way:**
```c
if (c == (char)178) {  // Explicit cast, no warning
    // code
}
```

---

## Key Takeaways

1. **Always use inclusion guards** in header files
2. **Include your own header** in implementation files
3. **Use static** for file-private functions/variables
4. **Be careful with signed/unsigned** comparisons
5. **Signed integer overflow** is undefined behavior
6. **Use explicit casts** when conversion is intentional
7. **Zero warnings** should be the goal before commit

## Common Warnings to Fix

- `signed/unsigned mismatch`
- `conversion from 'int' to 'char', possible loss of data`
- `truncation from 'double' to 'float'`

## Example Functions

```c
// Check if number is prime
int isprime(int val) {
    if (val == 0 || val == 1) return 0;
    if (val % 2 == 0) return val == 2;
    if (val % 3 == 0) return val == 3;
    if (val % 5 == 0) return val == 5;
    
    for (int i = 7; i * i <= val; i += 2) {
        if (val % i == 0) return 0;
    }
    return 1;
}

// Count digits in number  
int ndigit(int val) {
    if (val == 0) return 1;
    
    int count = 0;
    while (val) {
        ++count;
        val /= 10;
    }
    return count;
}
```