# C Programming Day 21 - Pointers Continued

## Overview
This lesson dives deeper into pointers, covering pointer operators, dereferencing, and the crucial distinction between **call by value** and **call by reference**. Understanding these concepts is fundamental to C programming.

---

## Table of Contents
1. [Pointer Basics Review](#pointer-basics-review)
2. [Pointer Declaration Syntax](#pointer-declaration-syntax)
3. [The Four Pointer Operators](#the-four-pointer-operators)
4. [Address Operator (&)](#address-operator-)
5. [Dereferencing Operator (*)](#dereferencing-operator-)
6. [Call by Value vs Call by Reference](#call-by-value-vs-call-by-reference)
7. [Why Use Call by Reference](#why-use-call-by-reference)
8. [Practical Examples](#practical-examples)

---

## Pointer Basics Review

### What is a Pointer?
**Pointer = Address = Gösterici = İşaretçi**

Pointers store memory addresses of objects at runtime.

### Pointer Types
```c
int *ptr;      // pointer to int
double *dptr;  // pointer to double
char *cptr;    // pointer to char
```

**Key Point:** All pointer types occupy the same memory size (4 bytes on 32-bit, 8 bytes on 64-bit systems), regardless of what they point to.

### Two Categories of Pointers
1. **Object pointers** - Point to variables/objects
2. **Function pointers** - Point to functions

### Pointer Storage Duration
Pointers can have different lifetimes:
```c
int *global_ptr;           // Global (static storage)

void func() {
    int *local_ptr;         // Automatic (local)
    static int *static_ptr; // Static (persistent)
}
```

---

## Pointer Declaration Syntax

### Multiple Variable Declarations
**IMPORTANT:** The `*` token only applies to the identifier it precedes!

```c
int *p1, p2;    // p1 is pointer, p2 is int (NOT pointer!)
```

This is actually:
```c
int *p1;        // p1 is pointer to int
int p2;         // p2 is int
```

### Correct Multiple Pointer Declaration
```c
int *p1, *p2;   // Both are pointers

// Or more complex:
int x, *p, a[10], *q;
```

Equivalent to:
```c
int x;          // integer variable
int *p;         // pointer to int
int a[10];      // array of 10 ints
int *q;         // pointer to int
```

### Uninitialized Pointers
```c
int *ptr;       // Contains garbage value (Indetermined)
                // Using it = Undefined Behavior!

static int *ptr; // Static = NULL pointer (safe but points nowhere)
```

**NEVER use an uninitialized pointer!**

---

## The Four Pointer Operators

| Operator | Name | Precedence | Description |
|----------|------|------------|-------------|
| `&` | Address-of | Level 2 | Gets address of variable |
| `*` | Dereferencing/Indirection | Level 2 | Accesses value at address |
| `[]` | Subscript/Index | Level 1 | Array element access |
| `->` | Member selection (Arrow) | Level 1 | Structure member access |

**Note:** Precedence Level 2 is right-to-left associative.

### Operator Overloading Context
- `&` as **binary infix** → Bitwise AND
- `&` as **unary prefix** → Address-of operator
- `*` as **binary infix** → Multiplication
- `*` as **unary prefix** → Dereferencing operator
- `+` as **unary** → Sign operator
- `+` as **binary** → Addition

---

## Address Operator (&)

### Rules
1. **Operand MUST be an L-value expression**
2. Returns the memory address of the operand
3. Result is an R-value expression (cannot be assigned to)

### Examples
```c
int x = 10;
&x;           // Valid: x is L-value, type is int*

&5;           // ERROR: 5 is R-value

double y = 3.14;
&y;           // Valid: type is double*
```

### Type of Address Expression
```c
int x = 10;
// Type of &x is int*

double y = 3.14;
// Type of &y is double*

char c = 'A';
// Type of &c is char*
```

### Basic Pointer Assignment
```c
int x = 10;
int y = 20;

int *ptr = &x;  // Initialization: ptr points to x
ptr = &y;       // Assignment: now ptr points to y
```

**Terminology:**
```c
int *ptr = &x;
// "ptr points to x"
// "ptr holds the address of x"
// "The value of ptr is the address of x"
```

### Address Operator is R-value
```c
int x = 10;
&x = 123;     // ERROR: Cannot assign to address
              // &x is R-value expression
```

**Important Concept:** In C/C++, addresses of objects NEVER change during their lifetime.

### Double Address Operator?
```c
int x = 10;
&&x;          // ERROR: Syntax error!
              // Address-of requires L-value operand
              // &x is R-value
```

**However:**
```c
int x = 10;
int *ptr = &x;

&x;           // Address of x (int*)
ptr;          // Holds address of x (same value as &x)
&ptr;         // Address of ptr itself (int**)
```

### Printing Addresses
```c
int x = 10;
int *ptr = &x;

printf("&x   = %p\n", (void*)&x);    // Address of x
printf("ptr  = %p\n", (void*)ptr);   // Same: ptr holds &x
printf("&ptr = %p\n", (void*)&ptr);  // Address of ptr itself
```

**Note:** `%p` is the conversion specifier for pointers. Addresses are printed in hexadecimal.

### Array Decay
**Important Concept:** Array name converts to pointer to first element (except in 2 cases).

```c
int a[5] = {1, 2, 3, 4, 5};

a;            // Decays to &a[0]
&a[0];        // Address of first element
```

These are equivalent:
```c
printf("a      = %p\n", a);
printf("&a[0]  = %p\n", &a[0]);
```

### Two Exceptions to Array Decay
**1. sizeof operator:**
```c
int a[5] = {0};
int b[10] = {0};

sizeof(a);        // 20 bytes (entire array)
sizeof(&a[0]);    // 4 or 8 bytes (just the pointer)
```

**2. Address-of operator on array:**
```c
&a;               // Type: int(*)[5] (pointer to array)
```

### Common Pointer Assignments
```c
int x = 10;
int a[10];

int *p = &x;      // p points to x
int *q = p;       // q points to same place as p
int *pa = a;      // pa points to first element of a
```

### Complex Declaration (Valid but Confusing)
```c
int x = 10, *p = &x, a[] = {1, 3, 5}, *q = a;
```

Same as:
```c
int x = 10;
int *p = &x;
int a[] = {1, 3, 5};
int *q = a;
```

---

## Dereferencing Operator (*)

### Purpose
**Accesses the value at the address stored in a pointer.**

Also called:
- Dereferencing operator
- Indirection operator
- Contents operator (İçerik Operatörü)

### Rules
1. **Operand MUST be an address expression**
2. Precedence Level 2 (right-to-left)
3. As **unary prefix** → dereferencing
4. As **binary infix** → multiplication

### Valid Dereferencing
```c
int x = 10;
int *ptr = &x;
int a[] = {1, 4, 5, 6, 7};

*ptr;         // Valid: ptr is pointer
*a;           // Valid: a decays to pointer
*&x;          // Valid: &x is address
```

### Invalid Dereferencing
```c
*234;         // ERROR: 234 is not an address
*x;           // ERROR: x is int, not pointer
```

### Dereferencing Examples

#### Example 1: Basic Usage
```c
int x = 10;
int *ptr = &x;

*ptr = 98;    // x is now 98
              // "Assign 98 to what ptr points to"
```

#### Example 2: Self-Cancellation
```c
int x = 10;
*&x = 45;     // Same as: x = 45
              // & gets address, * dereferences it
```

Even this works (but don't do it!):
```c
++*&*&*&*&*&*&x;  // Same as: ++x
```

#### Example 3: Array Access
```c
int a[] = {7, 24, 55};

*a = 44;      // Same as: a[0] = 44
              // Array decay: a → &a[0]
```

### Pointer Terminology
```c
int x = 1;
int *p = &x;

// p     → "pointer"
// x     → "pointee" (what is pointed to)
// *p    → "the value pointed to" (same as x)
```

### Assignment Rules
```c
int x = 10;
int *p = &x;

p = ...;      // Right side must be an address
*p = ...;     // Right side must be a value assignable to x
```

### Multiple Pointers to Same Object
```c
int x = 10;
int *p1 = &x, *p2 = p1, *p3 = p2;

++*p1;        // x becomes 11
++*p2;        // x becomes 12
++*p3;        // x becomes 13

// All three point to x
// All three can modify x
```

**Remember Precedence:** Level 2 operators are right-to-left!
```c
++*p1 → ++(*(p1))
```

---

## Call by Value vs Call by Reference

### Call by Value (Default in C)
**Function receives a COPY of the argument.**

```c
void func(int a) {
    a = 23;
}

int main() {
    int x = 10;
    func(x);
    printf("x = %d\n", x);  // Output: x = 10 (unchanged!)
}
```

**Why doesn't x change?**
- `a` and `x` are **different objects** in different memory locations
- Modifying `a` doesn't affect `x`

**Proof with Addresses:**
```c
void func(int a) {
    a = 23;
    printf("Address of a: %p\n", (void*)&a);
}

int main() {
    int x = 10;
    func(x);
    printf("Address of x: %p\n", (void*)&x);  // Different address!
}
```

### Call by Reference
**Function receives the ADDRESS of the argument and can modify the original.**

```c
void func(int *ptr) {
    *ptr = 100;   // Modifies the original variable
}

int main() {
    int x = 10;
    func(&x);     // Pass address of x
    printf("x = %d\n", x);  // Output: x = 100 (changed!)
}
```

**How it works:**
1. `&x` passes x's address to function
2. `ptr` stores x's address
3. `*ptr = 100` writes 100 to x's location
4. x is modified in main

---

## Why Use Call by Reference?

### Reason 1: Modify Multiple Variables
**Functions normally return ONE value, but sometimes we need to modify MULTIPLE variables.**

#### Example: Swap Function

**Incorrect (Call by Value):**
```c
void swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
    // Only swaps LOCAL copies, not original variables!
}

int main() {
    int a = 10, b = 20;
    swap(a, b);
    printf("a = %d, b = %d\n", a, b);  // Output: a = 10, b = 20 (no change!)
}
```

**Correct (Call by Reference):**
```c
void swap(int *pa, int *pb) {
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
    // Swaps actual variables!
}

int main() {
    int a = 10, b = 20;
    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);  // Output: a = 20, b = 10 (swapped!)
}
```

**Can also pass pointers:**
```c
int x = 10, y = 56;
int *px = &x, *py = &y;
swap(px, py);  // Also works!
```

### Reason 2: Efficiency (Large Data)
**When objects are large, passing by reference avoids expensive copying.**

#### Call by Value Cost
```c
struct BigData {
    char buffer[1608];  // 1608 bytes
};

struct BigData get_data() {
    struct BigData result;
    // ... fill result ...
    return result;      // Copies 1608 bytes to temporary
}

int main() {
    struct BigData x = get_data();  // Another 1608 byte copy!
    // Total: 2 copies of 1608 bytes = 3216 bytes copied
}
```

**What happens at assembly level:**
1. Return value copied to temporary object (1608 bytes)
2. Temporary copied to `x` (1608 bytes)
3. Temporary destroyed

#### Call by Reference Efficiency
```c
void get_data(struct BigData *result) {
    // Write directly to caller's memory
    // No copying!
}

int main() {
    struct BigData x;
    get_data(&x);  // Only passes 4 or 8 byte address!
}
```

**Cost comparison:**
- Call by value: 3216 bytes copied
- Call by reference: 4-8 bytes passed

**Massive difference for large structures!**

### Reason 3: scanf and Similar Functions
**Functions like `scanf` need to modify variables.**

```c
int x, y, z;
scanf("%d%d%d", &x, &y, &z);  // Must pass addresses!
// scanf modifies x, y, and z
```

---

## Practical Examples

### Example 1: Custom Integer Input
```c
void scan_int(int *ptr) {
    int c;
    *ptr = 0;
    
    while ((c = getchar()) != '\n') {
        *ptr = *ptr * 10 + (c - '0');  // Build number from digits
    }
}

int main() {
    int sum;
    printf("Enter an integer: ");
    scan_int(&sum);
    printf("sum = %d\n", sum);
}
```

### Example 2: Circle Area (Call by Value)
```c
double get_circle_area(double radius) {
    return 3.14159 * radius * radius;
}

int main() {
    double r = 23.4242;
    double area = get_circle_area(r);
    printf("Area = %.2f\n", area);
}
```

### Example 3: Circle Area (Call by Reference)
```c
void get_circle_area(double radius, double *p_area) {
    *p_area = 3.14159 * radius * radius;
}

int main() {
    double r = 23.4242;
    double area;
    get_circle_area(r, &area);
    printf("Area = %.2f\n", area);
}
```

**Which to use?**
- For **simple types** (int, double, char): Call by value is cleaner
- For **large structures**: Call by reference is much more efficient
- When **modifying multiple values**: Must use call by reference

### Example 4: Multiple Output Parameters
```c
void calculate(int a, int b, int *sum, int *diff, int *prod) {
    *sum = a + b;
    *diff = a - b;
    *prod = a * b;
}

int main() {
    int x = 10, y = 5;
    int s, d, p;
    
    calculate(x, y, &s, &d, &p);
    
    printf("Sum = %d\n", s);      // 15
    printf("Diff = %d\n", d);     // 5
    printf("Product = %d\n", p);  // 50
}
```

---

## Key Takeaways

### Pointer Operators
1. **`&` (Address-of)** - Gets address of L-value, returns R-value
2. **`*` (Dereferencing)** - Accesses value at address
3. **`[]` (Subscript)** - Array element access (syntactic sugar for pointer arithmetic)
4. **`->` (Arrow)** - Structure member access through pointer

### Important Rules
1. **Array decay**: Array name → pointer to first element (except with `sizeof` and `&`)
2. **Pointer size**: All pointers same size (4 or 8 bytes)
3. **Uninitialized pointers**: Contain garbage, NEVER use before assignment
4. **`*&x` cancellation**: Equals `x`

### Call by Value vs Reference
| Feature | Call by Value | Call by Reference |
|---------|---------------|-------------------|
| Passes | Copy of value | Address |
| Can modify original | No | Yes |
| Efficiency (large data) | Poor (copies data) | Excellent (4-8 bytes) |
| Safety | Safer (no side effects) | Riskier (side effects) |
| Use for | Simple types, read-only | Multiple outputs, large data |

### When to Use Call by Reference
1. Need to modify multiple variables
2. Working with large structures (avoid copying overhead)
3. Implementing functions like `scanf` that modify inputs
4. Performance-critical code with large data

### Common Mistakes
```c
// WRONG: Passing value instead of address
int *ptr = x;           // Should be: int *ptr = &x;

// WRONG: Type mismatch
double x = 1.0;
int *ptr = &x;          // Warning/Error: int* = double*

// WRONG: Uninitialized pointer
int *ptr;
*ptr = 10;              // Undefined behavior!

// CORRECT
int x = 10;
int *ptr = &x;
*ptr = 20;              // x is now 20
```

---

## Summary

Day 21 focused on:
1. **Pointer operators** and their correct usage
2. **Dereferencing** to access values through pointers
3. **Call by value** vs **call by reference** semantics
4. **Practical applications** of pointers for efficiency and multiple outputs

**Next Steps:**
- Practice pointer manipulation
- Implement functions using call by reference
- Study pointer arithmetic (coming in next lessons)
- Work with arrays and pointers together

---

## Additional Notes

### Code Readability
**Reading code is actually HARDER than writing it.**
- Different programmers use different styles
- Must understand ALL conventions and patterns
- Practice reading various coding styles

### Memory Safety
**Always initialize pointers before use:**
```c
int *ptr = NULL;  // Safe: explicitly NULL
// Check before use:
if (ptr != NULL) {
    *ptr = 10;
}
```