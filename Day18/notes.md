# C Programming Day 18 - Notes

## Bubble Sort

### Basic Bubble Sort Implementation
```c
for (int i = 0; i < SIZE - 1; i++) {
    for (int j = 0; j < SIZE - 1 - i; j++) {
        if (a[j] > a[j + 1]) {  // Ascending order
            int temp = a[j];
            a[j] = a[j + 1];
            a[j + 1] = temp;
        }
    }
}
```

**Time Complexity:** O(n²)
- Outer loop: n-1 iterations
- Inner loop: (n-1) × (n-1) comparisons total

**For descending order:** Change condition to `a[j] < a[j + 1]`

### Bubble Sort vs Quick Sort Performance

**Performance comparison (10,000 elements):**
- **Bubble Sort:** ~20 seconds
- **Quick Sort:** ~0.02 seconds (1000x faster!)

**At 100,000 elements:**
- **Bubble Sort:** Hours or days
- **Quick Sort:** Still seconds

**Key insight:** O(n²) vs O(n log n) difference becomes massive with scale.

### Using stdlib qsort
```c
#include <stdlib.h>

// Comparison function
static int icmp(const void* vp1, const void* vp2) {
    return *(const int*)vp1 - *(const int*)vp2;
}

// Usage
qsort(array, SIZE, sizeof(int), icmp);
```

---

## Advanced Bubble Sort - Custom Sorting Criteria

### Problem: Sort Odds First, Then Evens (Both Sorted)

**Challenge:** Write condition that produces: `[1, 3, 5, 7, 2, 4, 6, 8]`

**Solution:**
```c
for (int i = 0; i < SIZE - 1; i++) {
    for (int j = 0; j < SIZE - 1 - i; j++) {
        // Swap if: current is odd AND next is even
        //       OR: both same parity AND current > next
        if (a[j] % 2 != 0 && a[j + 1] % 2 == 0 || 
            (a[j] % 2 == a[j + 1] % 2) && (a[j] > a[j + 1])) {
            int temp = a[j];
            a[j] = a[j + 1];
            a[j + 1] = temp;
        }
    }
}
```

**Logic breakdown:**
1. `a[j] % 2 != 0 && a[j + 1] % 2 == 0` → Swap odd with even (moves odds left)
2. `(a[j] % 2 == a[j + 1] % 2) && (a[j] > a[j + 1])` → Sort within same parity

**Key concept:** Sorting criterion vs sorting algorithm are different things!

---

## Stable vs Unstable Sorting

### Stable Sort
Preserves relative order of equal elements.

**Example:** If there are 3 people named "Umut" with different ages, after sorting by name, their age order remains the same.

### Unstable Sort
May change relative order of equal elements.

**Note:** Bubble sort is **stable** by nature.

---

## Unique Random Number Generator

### Implementation with Static Array
```c
#define URAND_MAX 10

int urand(void) {
    static int a[URAND_MAX] = {0};  // Track generated numbers
    static int count = 0;            // How many generated
    int val;
    
    if (count == URAND_MAX)
        return -1;  // All numbers generated
    
    // Find ungenerated number
    for (;;) {
        val = rand() % URAND_MAX;
        if (a[val] == 0)
            break;
    }
    
    a[val] = 1;  // Mark as generated
    count++;
    return val;
}
```

**Why static?**
- Values must persist between function calls
- Alternative: global scope (but less secure)
- Static provides encapsulation

**Usage:**
```c
for (int i = 0; i < URAND_MAX; i++)
    printf("%d ", urand());  // Prints 0-9 in random order

printf("%d", urand());  // Prints -1 (exhausted)
```

---

## sizeof Operator

### Key Characteristics
- **Only keyword that's an operator**
- **Operator precedence:** 2nd position (very high)
- **Compile-time operator** - evaluated at compile time
- **Returns:** `size_t` (unsigned integer type)
- Creates a **constant expression**

### Basic Usage
```c
// With types (parentheses required)
sizeof(char)    // 1
sizeof(int)     // 4 (typically)
sizeof(double)  // 8 (typically)

// With expressions (parentheses optional)
int x = 10;
sizeof x        // 4
sizeof(x)       // 4
sizeof(x + 5)   // 4
```

### Unevaluated Context ⚠️

**CRITICAL:** sizeof operand is **not evaluated** - no code generated!

```c
int x = 5;
printf("%zu\n", sizeof(x++));  // Prints 4
printf("%d\n", x);              // Prints 5 (NOT 6!)
// x++ was NEVER executed!

// Even undefined behavior doesn't execute
int uninit;
sizeof(uninit + 1.2);  // No UB - not evaluated!
```

**Sequence point is cancelled** - the expression is not executed.

### sizeof with Arrays

**Special case:** No array decay with sizeof!

```c
int a[10] = {0};

sizeof a           // 40 (10 * 4) - whole array
sizeof a[0]        // 4 - first element
sizeof a / sizeof a[0]  // 10 - number of elements ✅
```

**Common idiom - Array element count:**
```c
int arr[300];
int count = sizeof arr / sizeof arr[0];  // 300

// Loop using sizeof
for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    printf("%d ", arr[i]);
```

### asize Macro (Utility)
```c
#define asize(a) (sizeof(a) / sizeof((a)[0]))

int arr[] = {4, 5, 67, 8, 76};
for (int i = 0; i < asize(arr); i++)
    printf("%d ", arr[i]);
```

### sizeof Pitfalls

#### Signed/Unsigned Comparison
```c
int arr[] = {4, 6, 2, 6, 1, 5, 9, 7, 8};

// WRONG - Dangerous!
for (int i = -2; i < asize(arr) - 2; i++)
    printf("%d ", arr[i+2]);

// Problem: asize returns size_t (unsigned)
// i (-2) gets converted to unsigned: 4,294,967,294
// Loop never executes!
```

**Solution:** Cast to signed or use different approach.

#### sizeof with Constants
```c
sizeof 'A'      // 4 (char promoted to int)
sizeof('A' + 5) // 4 (int arithmetic)
```

#### No Evaluation in sizeof
```c
int x = 5, y = 5;
sizeof(++x + ++y);  // Result: 4 (int size)
// ++x and ++y are NOT executed!
printf("%d %d", x, y);  // Prints: 5 5
```

### Using sizeof for Array Declaration
```c
int a[] = {4, 6, 2, 6, 1, 5, 9, 7, 8};

// Declare arrays based on other array sizes
int b[asize(a) * 2] = {0};      // Double size
int c[asize(a) * 3 / 2] = {0};  // 1.5x size
```

---

## Merge Algorithm (Sorted Array Merge)

### Problem
Merge two sorted arrays into one sorted array.

**Time Complexity:** O(n) - linear, very efficient!

### Implementation
```c
#define SIZE 10

int a[SIZE], b[SIZE];
int merged[2 * SIZE];

// Assume a and b are already sorted
int idx_a = 0;
int idx_b = 0;

for (int i = 0; i < 2 * SIZE; i++) {
    if (idx_a == SIZE)
        merged[i] = b[idx_b++];
    
    else if (idx_b == SIZE)
        merged[i] = a[idx_a++];
    
    else if (a[idx_a] < b[idx_b])
        merged[i] = a[idx_a++];
    
    else
        merged[i] = b[idx_b++];
}
```

### Algorithm Logic
1. **If array A exhausted:** Copy from B
2. **If array B exhausted:** Copy from A
3. **Otherwise:** Compare and take smaller element
4. Increment appropriate index

**Why O(n)?** Each element processed exactly once.

---

## Interesting C Quirk: Array Indexing

### Surprising Syntax
```c
int a[10] = {5, 3, 2, 5, 6, 7, 1, 9, 7, 8};

// These are equivalent!
a[i]    // Normal
i[a]    // ✅ Also legal!

for (int i = 0; i < 10; i++)
    printf("%d ", i[a]);  // Works! (explained with pointers later)
```

**Why it works:** Will be explained in pointer arithmetic section.

---

## Memory Management (Preview)

### Dynamic Memory Allocation
```c
#define SIZE 10000

// Allocate memory at runtime
int* p = (int*)malloc(SIZE * sizeof(int));

// Check allocation
if (!p) {
    fprintf(stderr, "Memory allocation failed!\n");
    return 1;
}

// Use the array
set_random_array(p, SIZE);

// Free when done
free(p);
```

**Note:** Detailed coverage in later lessons.

---

## Key Takeaways

1. **Bubble Sort** is O(n²) - good for learning, not production
2. **Quick Sort** is O(n log n) - use for large datasets
3. **Sorting criterion** ≠ **sorting algorithm**
4. **Static local variables** retain values between function calls
5. **sizeof** is compile-time, doesn't evaluate its operand
6. **sizeof array** gives total bytes, not element count
7. **Merge algorithm** is O(n) - very efficient for sorted arrays
8. **Array decay** doesn't happen with sizeof
9. Always watch for **signed/unsigned** comparisons with sizeof
10. **`a[i]` ≡ `i[a]`** (pointer arithmetic quirk)

---

## Common Patterns to Memorize

### Array Element Count
```c
sizeof(array) / sizeof(array[0])
```

### Bubble Sort Template
```c
for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++)
        if (condition)
            swap(a[j], a[j+1]);
```

### Merge Two Sorted Arrays
```c
while (both arrays have elements)
    take smaller element
handle remaining elements in either array
```

---

## Performance Notes

**Advice from instructor:** 
- Learn Bubble Sort by heart (for understanding)
- Use Quick Sort in practice (for performance)
- The difference matters enormously at scale:
  - 10K elements: 1000x difference
  - 100K elements: Could be hours vs seconds
  - 1M elements: Could be days vs minutes