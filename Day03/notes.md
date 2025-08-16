# Day 3 C Programming Notes

## Arrays and Loops
## Arrays
### What is an Array?
An array is a collection of elements of the same data type stored in contiguous memory locations.

### Array Declaration and Initialization
```c
// Method 1: Declare with size
int numbers[5];

// Method 2: Declare and initialize
int numbers[5] = {10, 20, 30, 40, 50};

// Method 3: Let compiler determine size
int grades[] = {85, 92, 78, 96, 88}; // Size = 5

// Method 4: Partial initialization
int arr[5] = {1, 2}; // Rest will be 0: {1, 2, 0, 0, 0}
```

### Key Array Concepts
- **Zero-indexed**: First element is at index 0
- **Fixed size**: Size must be known at compile time
- **Homogeneous**: All elements must be same type
- **Contiguous memory**: Elements stored next to each other

### Array Access
```c
int arr[5] = {10, 20, 30, 40, 50};
printf("%d", arr[0]);  // Prints 10 (first element)
printf("%d", arr[4]);  // Prints 50 (last element)
arr[2] = 100;         // Modify third element
```

### Array Bounds
**Important**: C doesn't check array bounds!
```c
int arr[5];
arr[10] = 100; // Dangerous! May crash or corrupt memory
```

---

## Loops

### 1. For Loop
Best for: When we know how many iterations we need
```c
for (initialization; condition; increment) {
    // Code to execute
}

// Example:
for (int i = 0; i < 5; i++) {
    printf("%d ", i);
}
// Output: 0 1 2 3 4
```

### 2. While Loop
Best for: When condition is checked before each iteration
```c
while (condition) {
    // Code to execute
    // Update condition variable!
}

// Example:
int i = 0;
while (i < 5) {
    printf("%d ", i);
    i++;
}
// Output: 0 1 2 3 4
```

### 3. Do-While Loop
Best for: When we need at least one iteration
```c
do {
    // Code to execute
} while (condition);

// Example:
int i = 0;
do {
    printf("%d ", i);
    i++;
} while (i < 5);
// Output: 0 1 2 3 4
```

### Loop Control Statements
- **break**: Exit loop immediately
- **continue**: Skip rest of current iteration

---

## Common Array Operations

### 1. Printing an Array
```c
int arr[5] = {1, 2, 3, 4, 5};
for (int i = 0; i < 5; i++) {
    printf("%d ", arr[i]);
}
```

### 2. Finding Maximum/Minimum
```c
int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
```

### 3. Calculating Average
```c
double calculate_average(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;  // Cast to double for decimal result
}
```

### 4. Linear Search
```c
int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}
```

### 5. Reversing an Array
```c
void reverse_array(int arr[], int size) {
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}
```

---

## Sorting Algorithms

### Bubble Sort
Simple sorting algorithm
```c
void bubble_sort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
```

**How it works:**
1. Compare adjacent elements
2. Swap if they're in wrong order
3. Repeat until no swaps needed
4. Time Complexity: O(n²)

---

## Arrays and Functions

### Passing Arrays to Functions
```c
// Array is passed by reference (address)
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

// Alternative syntax (same meaning)
void print_array(int *arr, int size) {
    // Same implementation
}
```

### Important Notes:
- Arrays are always passed by reference
- You cannot return arrays from functions (use pointers)
- Size must be passed separately

---

### Getting User Input for Arrays
```c
int size;
printf("Enter size: ");
scanf("%d", &size);

int arr[100];  // Fixed size array
for (int i = 0; i < size; i++) {
    printf("Element %d: ", i + 1);
    scanf("%d", &arr[i]);
}
```

### Input Validation
```c
if (size > 100 || size <= 0) {
    printf("Invalid size! Using default.\n");
    size = 5;
}
```

---

## Memory Concepts

### Array Memory Layout
```c
int arr[4] = {10, 20, 30, 40};
```
Memory looks like:
```
Address: 1000  1004  1008  1012
Value:   10    20    30    40
Index:   [0]   [1]   [2]   [3]
```

### Array Name as Pointer
```c
int arr[5] = {1, 2, 3, 4, 5};
printf("%p", arr);     // Prints address of first element
printf("%p", &arr[0]); // Same as above
```

---

### Tips
1. **Off-by-one errors**: Using `<=` instead of `<` in loops
2. **Uninitialized arrays**: Contains garbage values
3. **Array bounds**: Accessing arr[n] when size is n
4. **Forgetting to pass size**: Functions need to know array size
