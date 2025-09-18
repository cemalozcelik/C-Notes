# Day 12 - Loops and Recursion in C

## Loop Idioms and Patterns

### The "Goes-To" Operator
```c
int n = 30;
while(n --> 0)  // n-- > 0, cool trick that decrements and checks
    printf("test\n");
```

### Suppressing Warnings
```c
(void)scanf("%d", &x);  // cast to void to suppress unused return value warning
```

### Infinite Loops - Three Reasons
1. **Programming error** - accidental infinite loop
2. **Intentional** - especially in embedded programming
3. **Exit through other means** - break, return, goto, exit, abort

## Break Statement
- Only works inside `switch` statements or loops
- Exits the nearest enclosing loop or switch
- Causes syntax error if used elsewhere

## Practical Loop Example - Number Statistics
```c
int c, ival, cnt = 0, sum = 0, max, min;

while (1) {
    printf("Continue (y) - Stop (n)\n");
    while ((c = _getch()) != 'y' && c != 'n')
        ;  // wait for valid input
    
    if (c == 'n') break;
    
    // Generate random number (instead of scanf for speed)
    ival = (rand() % 2 ? 1 : -1) * rand();
    
    if (cnt == 0)
        max = min = ival;
    else if (ival > max)
        max = ival;
    else if (ival < min)
        min = ival;
    
    cnt++;
    sum += ival;
}

// Display statistics if any numbers were processed
if (cnt != 0) {
    printf("Total numbers: %d\n", cnt);
    printf("Average: %f\n", (double)sum / cnt);
    printf("Min: %d, Max: %d\n", min, max);
}
```

## Do-While Loop

### Equivalence Pattern
```c
// These are equivalent:

// Pattern 1: while with break
while(1) {
    statement1;
    statement2;
    if(!condition) break;
}

// Pattern 2: do-while
do {
    statement1;
    statement2;
} while(condition);
```

### Practical Use Case
```c
int x;
do {
    printf("Enter number (0-100): ");
    scanf("%d", &x);
} while(x < 0 || x > 100);  // repeat until valid input
```

### Continue in Do-While
```c
do {
    printf("%d", i);
    i++;
    if(i < 15)
        continue;  // jumps to while condition
} while(condition);
```

## For Loop Variations

### Standard Form
```c
for(initialization; condition; update) {
    // body
}
```

### Flexible Syntax
```c
// All expressions are optional
for(;;)  // infinite loop (middle condition defaults to true)

// Initialization outside
i = 0;
for(; i < 10; i++)

// Update inside body
for(; i < 10;) {
    // body
    i++;
}

// Complex initialization and update
for(int i = 10, k = 20; i + k < 1000; ++i, k += i)
```

### Variable Scope (C++ vs C)
```c
for(int i = 0; i < 10; i++) {
    int i = 20;  // Different variable in inner scope
    printf("%d", i);  // Prints 20 each time
}
// In C++: syntax error
// In C: legal, creates new scope for inner i
```

## Recursion

### Factorial Function
```c
int factorial(int x) {
    return x < 2 ? 1 : x * factorial(x - 1);
}
```

### Important Notes
- **13!** doesn't fit in 4-byte int (overflow)
- **21!** doesn't fit in 8-byte long long
- **Signed overflow** is undefined behavior
- Better to use **lookup tables** for large factorials

### Lookup Table Alternative
```c
const int factorials[] = {
    1,    // 0!
    1,    // 1!
    2,    // 2!
    6,    // 3!
    24,   // 4!
    120,  // 5!
    // ... up to safe limit
};
```

## Mathematical Series - Pi Approximation

### Leibniz Formula for π/4
```c
int n;
double sum = 0;

printf("How many terms to sum? ");
scanf("%d", &n);

for (int i = 0; i < n; i++) {
    if (i % 2 == 0)
        sum += 1.0 / (2 * i + 1);    // positive terms
    else
        sum -= 1.0 / (2 * i + 1);    // negative terms
}

printf("Pi approximation: %.12f\n", 4.0 * sum);
```

**Formula**: π/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - ...

## Key Programming Concepts

### Loop Choice Guidelines
- **No loop is inherently better** than others
- Choose the most **natural and readable** for your specific task
- **For loops** are compact for counter-based iterations
- **While loops** are natural for condition-based iterations
- **Do-while** ensures at least one execution

### Common Patterns
- **Input validation loops** with do-while
- **Menu-driven programs** with infinite loops and break
- **Statistical calculations** with running totals
- **Series approximations** with for loops

## Important Warnings
- **Integer overflow** in factorial calculations
- **Infinite loops** due to logic errors
- **Off-by-one errors** in loop conditions
- **Scope issues** with loop variables