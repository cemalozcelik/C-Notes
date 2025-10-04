# C Programming Day 17 - Notes

## Arrays - Fundamentals

### Array Declaration Rules

**Valid declarations:**
```c
int a[100];              // 100 element int array
int a[10 * 5 - 3];      // Constant expression (47 elements)
#define SIZE 23
int a[SIZE];            // Using macro
int a[4] = {3, 7, 9, 2,}; // Trailing comma allowed
```

**Invalid declarations:**
```c
int x = 10;
int a[x];               // Variable cannot be used
int a[0];               // Size cannot be 0
int a[-1];              // Size cannot be negative
int a[];                // Size must be specified (unless initialized)
```

**Key Rule:** Array size must be a **constant expression** known at compile-time.

---

## Critical Array Limitations

### 1. Arrays in Functions
```c
// Function parameter - array becomes pointer
void func(int arr[10]);  // Actually: void func(int *arr)
void func(int *arr);     // Real form

// Return type - cannot return array
int[] func();            // Invalid
int* func();             // Return pointer instead
```

**IMPORTANT:** 
- Function parameter **cannot be array** → becomes pointer
- Function **cannot return array** → must return pointer

### 2. Arrays Cannot Be Assigned
```c
int a[5] = {1, 3, 5, 7, 9};
int b[5];

b = a;  // SYNTAX ERROR - Arrays cannot be lvalues
```

**To copy arrays:**
```c
// Using loop
for(int i = 0; i < 5; i++)
    b[i] = a[i];

// Using memcpy
memcpy(b, a, sizeof(a));
```

---

## Array Initialization

### Automatic vs Static Storage
```c
// Automatic (local) - garbage values
int a[4];               // Undefined values - UB if used

// Static storage - zero initialized
static int a[4];        // All elements = 0
```

### Initialization Syntax
```c
int a[10] = {3, 7, 9, 2};     // First 4 set, remaining 6 = 0
int a[10] = {0};              // All elements = 0
int a[10] = {};               // Syntax error in C (valid in C++)
int a[] = {1, 3, 5, 6};       // Size automatically = 4

// Designated initializers
int a[25] = {[5] = 17, [13] = 25};           // Specific indices
int a[] = {[13] = 25, [5] = 17, 60, 70};     // Indices 6,7 = 60,70
```

**Rules:**
- Too many initializers → syntax error
- Too few initializers → remaining elements = 0
- No size + initializer → size determined automatically

---

## Array Indexing and Access

### Zero-Based Indexing
```c
int a[10];

a[0]   // First element (index 0)
a[1]   // Second element (index 1)
a[9]   // Tenth element (index 9)
```

**Important:** "One-indexed element" ≠ "First element"
- `a[1]` → one-indexed element (second element)
- `a[0]` → first element

### Out-of-Bounds Access - DANGEROUS!
```c
int a[10];
a[15] = 30;  // NOT a syntax error!
             // NOT a compile-time error!
             // Runtime Undefined Behavior (UB)
```

**C does NOT check array bounds** - programmer's responsibility!

---

## Array Decay (Array-to-Pointer Conversion)

**Core concept:** When array name is used in expression, it **decays** to pointer to first element.

```c
int a[5] = {1, 3, 5, 7, 9};

// These are equivalent:
scanf("%d", a);          // → scanf("%d", &a[0])
printf("%p", a);         // → printf("%p", &a[0])
```

**Memory layout:** Array elements are stored **contiguously**.
- Array has an address (= address of first element)
- Each element has its own address

---

## Algorithm Complexity (Big O Notation)

### Time Complexity Categories
```c
// O(n) - Linear
for(int i = 0; i < n; i++)
    // Single loop

// O(n²) - Quadratic
for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
        // Nested loops
```

**Common complexities:**
- **Bubble Sort** → O(n²)
- **Quick Sort** → O(n log n) average
- **Binary Search** → O(log n)
- **Linear Search** → O(n)

### Complexity Scenarios
- **Best case** - optimal scenario
- **Worst case** - pessimal scenario
- **Average case** - typical scenario (default assumption)

### Space vs Time
- **Time complexity** - How fast?
- **Space complexity** - How much memory?

---

## Classic Array Algorithms

### 1. Array Traversal
```c
for(int i = 0; i < SIZE; i++)
    printf("%d ", a[i]);
```

### 2. Calculate Average
```c
int sum = 0;
for(int i = 0; i < SIZE; i++)
    sum += a[i];
    
printf("Average: %f\n", (double)sum / SIZE);
```

**Note:** Watch for integer overflow in sum!

### 3. Find Maximum Element (O(n))
```c
int max = a[0];
int max_id = 0;

for(int i = 1; i < SIZE; i++) {
    if(a[i] > max) {
        max = a[i];
        max_id = i;
    }
}
```

### 4. Find Min and Max Together
```c
int max = a[0];
int min = a[0];

for(int i = 1; i < SIZE; i++) {
    if(a[i] > max)
        max = a[i];
    else if(a[i] < min)
        min = a[i];
}
```

### 5. Runner-Up (Second Maximum)
```c
int max = a[0];
int runner_up = a[1];

if(a[1] > a[0]) {
    max = a[1];
    runner_up = a[0];
}

for(int i = 2; i < SIZE; i++) {
    if(a[i] > max) {
        runner_up = max;
        max = a[i];
    }
    else if(a[i] != max && a[i] > runner_up)
        runner_up = a[i];
}
```

### 6. Reverse Array (In-Place)
```c
int temp;
for(int i = 0; i < SIZE/2; i++) {
    temp = a[i];
    a[i] = a[SIZE - 1 - i];
    a[SIZE - 1 - i] = temp;
}
```

**Logic:** Swap elements from both ends moving toward center.
- For SIZE=100: a[0]↔a[99], a[1]↔a[98], ... a[49]↔a[50]

### 7. Linear Search

**Flag approach:**
```c
int flag = 0;
int i;

for(i = 0; i < SIZE; i++) {
    if(a[i] == sval) {
        flag = 1;
        break;
    }
}

if(flag)
    printf("Found at index %d\n", i);
else
    printf("Not found\n");
```

**Professional approach (no flag):**
```c
int i;
for(i = 0; i < SIZE && a[i] != sval; i++)
    ;

if(i < SIZE)
    printf("Found at index %d\n", i);
else
    printf("Not found\n");
```

---

## Sorting Algorithms Overview

### Common Sorting Algorithms
- **Bubble Sort** → O(n²), simple but slow
- **Quick Sort** → O(n log n) average, widely used
- **Merge Sort** → O(n log n), stable
- **Insertion Sort** → O(n²), good for small/nearly sorted
- **Selection Sort** → O(n²)
- **Shell Sort**, **Radix Sort**, **Heap Sort** - specialized uses

### Stable vs Unstable Sort

**Stable:** Preserves relative order of equal elements
```
Before: ahmet-12, mehmet-55, mehmet-30, mehmet-21
After:  ahmet-12, mehmet-55, mehmet-30, mehmet-21
        (mehmet order preserved)
```

**Unstable:** May change relative order of equal elements
```
Before: ahmet-12, mehmet-55, mehmet-30, mehmet-21
After:  ahmet-12, mehmet-21, mehmet-30, mehmet-55
        (mehmet order changed)
```

---

## Utility Functions

### Randomize and Array Setup
```c
void randomize(void) {
    srand((unsigned)time(0));
}

void set_random_array(int* p, int size) {
    for(int i = 0; i < size; i++)
        p[i] = rand() % 1000;
}

void print_array(const int* p, int size) {
    for(int i = 0; i < size; i++) {
        if(i && i % 20 == 0)
            printf("\n");
        printf("%3d ", p[i]);
    }
    printf("\n");
}
```

---

## Key Takeaways

1. **Array size** must be constant expression (compile-time)
2. **Out-of-bounds** access is UB, no compiler error
3. **Array decay:** array name → pointer to first element (`&a[0]`)
4. **Arrays cannot be:**
   - Assigned (`b = a`)
   - Function parameters (becomes pointer)
   - Return types (return pointer instead)
5. **Static arrays** initialize to 0, automatic arrays have garbage
6. **Indexing:** 0-based, `a[0]` is first element
7. **Common algorithms:** Know max, min, reverse, linear search by heart
8. **Complexity:** O(n) for linear, O(n²) for nested loops

---

## Common Pitfalls to Avoid

- Using uninitialized automatic array → UB
- Accessing array out of bounds → UB
- Integer overflow in sum calculations → UB (signed types)
- Division by zero when calculating averages
- Forgetting arrays are 0-indexed
- Trying to assign arrays directly (`b = a`)