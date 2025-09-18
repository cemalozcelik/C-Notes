# C Programming Day 13 Notes

## Function Declaration and Default extern

- Functions have **default extern** linkage - they are visible across translation units
- Need to revisit **static** keyword - it's important for controlling visibility
- **Translation unit** = preprocessor output that becomes compiler input

## Static Keyword - Function and Variable Scope

### Static Functions (Private Functions)
```c
static int func(void) {  // Private to this source file only
    // implementation
}
```

### Static Global Variables
```c
static int a = 10;  // Private to this source file
```

### Static Local Variables (Different meaning)
```c
int main() {
    static int a = 10;  // Lifetime extension, NOT privacy
}
```

**Key Point**: Static has different meanings:
- **Global scope**: Makes function/variable private to source file
- **Local scope**: Extends variable lifetime (like other languages' static)

## Include Mechanism

`#include` is copy-paste operation by preprocessor:
- **Nested includes** are possible
- Include can complete partial code from another file
- **Translation unit** = final code after preprocessing

## Default Function Declaration (AVOID!)

```c
// DON'T DO THIS - undefined behavior
int main() {
    func(12);  // Compiler assumes: int func();
}
```

- Compiler creates implicit declaration for backward compatibility
- Gives warnings/errors after compilation
- **Rule: Never use this!**

## PREPROCESSOR (Önişlemci)

Text processing program that runs before compiler:
- Commands start with `#`
- No semicolon at end of directives

### Preprocessor Directives
```c
#         // null directive
#include
#define
#undef
#if / #elif / #else / #endif
#ifdef / #ifndef
#line
#error
#pragma
```

### Processing Order
1. Comment removal
2. Preprocessor directives
3. Translation unit creation
4. Compiler input

## Include Variants

### `<>` vs `""`
- **`<filename>`**: Searches in default/system directories
- **`"filename"`**: Searches in current directory first

### Usage Convention
- `<>` for standard headers: `stdio.h`, `windows.h`
- `""` for custom/third-party headers: `"utility.h"`, `"myheader.h"`

## Conditional Compilation
```c
#if
#else
#elif
#ifdef    // if defined
#ifndef   // if not defined
```

## #define - Macros

### Object-like Macros (Symbolic Constants)
```c
#define MAX 1000
#define SIZE (100 + 40)  // Use parentheses!
```

**Macro Rules:**
1. **Case sensitive**: `MAX` ≠ `max`
2. **Must be defined before use**
3. **Not replaced if**:
   - Part of another token
   - Inside string literal
   - Case doesn't match

### Macro Gotchas
```c
#define SIZE 100 + 40
int x = SIZE * 5;  // Becomes: 100 + 40 * 5 = 300 (NOT 700!)

#define SIZE (100 + 40)  // Fixed version
int x = SIZE * 5;  // Becomes: (100 + 40) * 5 = 700
```

### Multi-line Macros
```c
#define MAX 200 + 300 + \
            500
```

### Semicolon Problem
```c
#define SIZE 100;  // DON'T add semicolon!

if (x == SIZE)  // Becomes: if (x == 100;) - ERROR!
    x++;
```

## Macro Usage Patterns

### 1. Named Constants
```c
#define NO_BOOKS 100
int x = NO_BOOKS;
```

### 2. Type Aliases
```c
#define BYTE unsigned char
BYTE x = 12;
```

### 3. Derived Macros
```c
#define MIN 100
#define MAX 500
#define MEAN ((MAX + MIN) / 2)
```

### 4. Portability (limits.h)
```c
#define INT_MAX  // Platform-specific max int value
#define LONG_MIN // Platform-specific min long value
int x = INT_MAX;  // Works on 16-bit and 32-bit systems
```

## Standard Library Macros

### Math Constants (Need _USE_MATH_DEFINES before math.h)
```c
#define _USE_MATH_DEFINES
#include <math.h>

double val = M_PI;      // π
double val = M_SQRT2;   // √2
double val = M_SQRT1_2; // 1/√2
```

### Other Standard Macros
```c
fseek(f, 0L, SEEK_SET);  // SEEK_SET is macro
exit(EXIT_FAILURE);      // EXIT_FAILURE is macro
```

## Function-like Macros

### Basic Syntax
```c
#define MAX(a,b) (a > b ? a : b)
int max = MAX(x, y);  // Expands to: (x > y ? x : y)
```

### Parentheses Rules - CRITICAL!
```c
// WRONG - No parentheses
#define SQUARE(a) a * a
int y = SQUARE(x + 1);  // Becomes: x + 1 * x + 1 = WRONG!

// BETTER - Parameter parentheses
#define SQUARE(a) (a) * (a)
int y = SQUARE(x + 1);  // Becomes: (x + 1) * (x + 1) = Better

// STILL WRONG - Division precedence
int y = 100 / SQUARE(x);  // Becomes: 100 / (x) * (x) = WRONG!

// CORRECT - Full expression parentheses
#define SQUARE(a) ((a) * (a))
int y = 100 / SQUARE(x);  // Becomes: 100 / ((x) * (x)) = CORRECT!
```

### Practical Examples
```c
#define isleap(x) ((x) % 4 == 0 && ((x) % 100 != 0 || (x) % 400 == 0))
#define isupper(c) ((c) >= 'A' && (c) <= 'Z')
#define tolower(c) (((c) >= 'A' && (c) <= 'Z') ? (c) - 'A' + 'a' : (c))
```

## Macro Side Effects - DANGEROUS!
```c
#define square(a) ((a) * (a))

int a = 9;
int b = square(a++);  // Becomes: ((a++) * (a++))
// UNDEFINED BEHAVIOR - multiple unsequenced modifications!
```

## Macro vs Function Priority

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