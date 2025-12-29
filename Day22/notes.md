# Day 22 Notes - const Keyword & Pointer Arithmetic

## const Keyword - Super Important!

One of the 3 most important keywords according to instructor.

### Basic const Usage

```c
const int x = 10;  // Oxymoron expression - "constant variable"
// x is born with 10 and keeps that value - ReadOnly
// x = 20;  // SYNTAX ERROR
// ++x;     // SYNTAX ERROR
```

**Arrays with const:**
```c
const int a[] = {1, 5, 4, 3, 7, 8};
// a[2] = 43;  // SYNTAX ERROR - can't modify
```

**Two ways to write it:**
```c
const int a;    // Same as below
int const a;    // Same as above
```

For basic types, position doesn't matter. But with pointers, it matters a lot!

---

## Why Use const in Function Parameters?

Example with Matrix:
```c
typedef struct {
    int row, col;
    int a[20][20];
} Matrix;

void add_matrix(Matrix *presult, const Matrix *p1, const Matrix *p2)
// result will change, but p1 and p2 won't
// p1 and p2 are read-only

Matrix x, y, z;
add_matrix(&z, &x, &y);  // z = x + y
```

**Why const here?** We only want to READ x and y, not modify them.

---

## 4 Reasons to Use Call by Reference

1. **Instead of return value** - Send address, calculate, write to that address
2. **Efficiency for large data** - If sizeof is high, copying is expensive. Use const if just reading.
3. **Multiple return values** - Modify multiple variables
4. **Passing arrays** - Only way to pass array is via pointer. Arrays can't be parameters or return values directly.

---

## const Correctness

Using const keyword correctly = **const correctness**

### Benefits:
1. **Code readability** - Makes code easier to understand
2. **Intent declaration**:
   - `int a[]` → mutable array (can write)
   - `const int a[]` → immutable array (read-only)
3. **Optimization** - Helps compiler generate better code (not guaranteed, but enables it)

### Example: Prime Numbers
```c
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
// These shouldn't change - modifying them is logical error
```

---

## const with Pointers - CRITICAL!

Position of `const` matters with pointers!

### Case 1: Pointer to const int (Low-Level const)
```c
const int *ptr = &x;    // Same as below
int const *ptr = &x;    // Same as above

// "pointer to const int"
// ptr can change (can point to different things)
// BUT *ptr cannot change (can't modify what it points to)

*ptr = 20;   // SYNTAX ERROR
ptr = &y;    // OK
```

### Case 2: const Pointer to int (Top-Level const)
```c
int * const ptr = &x;

// "const pointer to int"
// ptr cannot change (always points to x)
// BUT *ptr can change (can modify x)

*ptr = 25;   // OK
ptr = &y;    // SYNTAX ERROR
```

### Case 3: const Pointer to const int
```c
const int * const ptr = &x;

// "const pointer to const int"
// Nothing can change! :D

*ptr = 20;   // SYNTAX ERROR
ptr = &y;    // SYNTAX ERROR
```

**Quick rule:** 
- `const` before `*` → can't change what's pointed to
- `const` after `*` → can't change pointer itself

---

## Setter vs Getter Functions

```c
void func(int *ptr)           // SET function (setter/mutator)
                              // Can modify *ptr

void func(const int *ptr)     // GET function (getter)
                              // Can't modify *ptr
```

### Standard Library Examples:
```c
strlen()    // const char *  - just reading, calculating length
_strrev()   // char *        - modifying, reversing string
strcmp()    // const char *, const char *  - comparing, not modifying
```

**Why use const parameters?**
If data shouldn't change, const gives syntax error when you try to change it.
Also helps code readers understand intent.

---

## Undefined Behavior with const

```c
const int x = 10;
int *p = &x;      // C++ = SYNTAX ERROR, C = OK (warning)
*p = 98;          // UNDEFINED BEHAVIOR

printf("%d", x);  // Might show 98, but it's UB!
```

Never do this!

---

## Pointer Arithmetic

In C:
- address + integer
- integer + address
- address - integer
- integer - address (NOT ALLOWED)
- address - address (result is signed integer)
- address + address (NOT ALLOWED)

### Example:
```c
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

for (int i = 0; i < 10; i++) {
    printf("%p  %p  %p\n", &a[i], a + i, i + a);
}
```

All three print same addresses!
Gap between elements = sizeof(int) = 4 bytes
If double → 8 bytes
If char → 1 byte

### Key Identity:
```c
&a[n]  ==  a + n    // Same thing!
```

### Dereferencing with Arithmetic:
```c
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

for (int i = 0; i < 10; i++) {
    printf("%d  %d  %d\n", a[i], *(a + i), *(i + a));
    // All print same value!
}
```

### Pointer Increment:
```c
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *p = a;

printf("%d", *p);    // 0
p++;                 // Move to next element (or p = p+1 or p+=1)
printf("%d", *p);    // 1
```

---

## Subscript Operator [] - Important!

**IMPORTANT NOTE:**
```c
i[a]  ==  a[i]    // These are SAME!
```

**Why?** Because `[]` operator converts `a[i]` to `*(a+i)`

So:
```c
a[i]  =  *(a + i)
i[a]  =  *(i + a)
// Same thing because addition is commutative!
```

### Subtracting Addresses:
```c
int a[] = {5, 6, 7, 8, 9, 3, 2, 1, 1, 2, 3, 4};
int *p1 = &a[5];
int *p2 = &a[8];

printf("p1 - p2 = %d\n", p1 - p2);  // -3
printf("p2 - p1 = %d\n", p2 - p1);  // 3
```

Result is signed integer!
Address - address ≠ address
Result tells you distance between elements

**IMPORTANT:** Subtracting addresses from different arrays is meaningless!
```c
int x[10] = {0};
int y[10] = {0};

&x - &y;  // No syntax error, but meaningless!
// Only makes sense for same array
```

---

## More Subscript Examples:

```c
int x = 10;       // Think of it as 1-element array
++(&x)[0];        // x = 11
++*(&x + 0);      // x = 12
```

### Pointer Indexing:
```c
int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *ptr = a + 5;

printf("%d\n", *ptr);       // 5
printf("%d\n", ptr[0]);     // 5
printf("%d\n", ptr[3]);     // 8
printf("%d\n", ptr[-2]);    // 3
printf("%d\n", *(ptr - 2)); // 3

// ptr[-15]  // No syntax error but UNDEFINED BEHAVIOR!
```

**If you overflow array bounds = UB**

---

## Finding Array Index from Pointer:

If `ptr` points to element of array `a`:
- **Index of element ptr points to:** `ptr - a`

If you want ptr to point to index 5 of array a:
- `ptr = a + 5`

---

## Passing Arrays to Functions

Only possible by sending address!

### Method 1: Less preferred
```c
void print_array(const int *ptr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n--------------------------\n");
}
```

### Method 2: More preferred
```c
void print_array(const int *ptr, int size) {
    while (size--) {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n--------------------------\n");
}
```

### Usage:
```c
int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_array(a, 10);
}
```

**ATTENTION! VERY IMPORTANT FOR INTERVIEWS:**
Pointer parameter MUST be qualified with `const` keyword if not modifying!
Big mistake if you don't do this!

### Flexible Array Printing:
```c
print_array(a, 5);           // First 5 elements
print_array(a + 5, 3);       // Elements 5, 6, 7
print_array(a + SIZE - 5, 5);  // Last 5 elements (SIZE = array size macro)
```

---

## Sum Array Example

### Method 1:
```c
int sum_array(const int *ptr, int size) {
    int sum = 0;
    while (size--) {
        sum += *ptr;
        ptr++;
    }
    return sum;
}
```

### Method 2:
```c
int sum_array(const int *a, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += a[i];
    
    return sum;
}
```

### Using it:
```c
randomize();
set_random_array(a, SIZE);

printf("sum = %d\n", sum_array(a, SIZE));
```

---

## Function Calling Another Function

Functions can pass their parameters to other functions!

```c
// Takes parameters and passes them to sum_array
double get_mean(const int *ptr, int size) {
    return (double)sum_array(ptr, size) / size;
}
```

This calculates average by:
1. Calling sum_array with same parameters
2. Dividing result by size
3. Casting to double for decimal result

---

### const Pointer Syntax:
```c
const int *p;         // Can't change *p, can change p
int const *p;         // Same as above
int * const p;        // Can't change p, can change *p
const int * const p;  // Can't change anything
```

### Pointer Arithmetic:
```c
a[i]  ==  *(a + i)  ==  i[a]  ==  *(i + a)
&a[i]  ==  a + i
ptr - a  ==  index of element ptr points to
```

### Array Functions:
- ALWAYS use `const` if not modifying!
- Pass address and size
- Can pass partial arrays: `func(a + offset, size)`

