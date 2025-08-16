# C Programming Notes - Day 10

##  Table of Contents
1. [Character Testing Functions](#character-testing-functions)
2. [Character Conversion Functions](#character-conversion-functions)
3. [Ternary Operator (Conditional Operator)](#ternary-operator-conditional-operator)
4. [Practical Algorithms](#practical-algorithms)
5. [Armstrong Numbers](#armstrong-numbers)
6. [Important Tips and Pitfalls](#important-tips-and-pitfalls)

---

## Character Testing Functions

### General Information
- **Header file**: `<ctype.h>`
- These functions work on ASCII character set (0-127)
- Take `int` as parameter, return `int`
- Work with true/false logic (0 = false, non-zero = true)

###  Basic Functions

| Function | Description | Example |
|----------|-------------|---------|
| `islower(c)` | Tests for lowercase letter (a-z) | `islower('a')` → true |
| `isupper(c)` | Tests for uppercase letter (A-Z) | `isupper('A')` → true |
| `isdigit(c)` | Tests for digit (0-9) | `isdigit('5')` → true |
| `isalpha(c)` | Tests for alphabetic character (a-z, A-Z) | `isalpha('K')` → true |
| `isalnum(c)` | Tests for alphanumeric (letter + digit) | `isalnum('7')` → true |
| `isxdigit(c)` | Tests for hexadecimal digit (0-9, A-F, a-f) | `isxdigit('F')` → true |
| `ispunct(c)` | Tests for punctuation character | `ispunct('!')` → true |
| `isspace(c)` | Tests for whitespace characters | `isspace(' ')` → true |
| `isblank(c)` | Tests for tab and space | `isblank('\t')` → true |
| `isprint(c)` | Tests for printable character | `isprint('A')` → true |
| `iscntrl(c)` | Tests for control character | `iscntrl('\n')` → true |
| `isgraph(c)` | Tests for graphic character (printable except space) | `isgraph('*')` → true |

###  Example Usage
```c
#include <stdio.h>
#include <ctype.h>

int main() {
    int ch = getchar();
    
    if (islower(ch))
        printf("Lowercase letter: %c\n", ch);
    
    if (isdigit(ch))
        printf("Digit: %c\n", ch);
    
    if (ispunct(ch))
        printf("Punctuation: %c\n", ch);
    
    return 0;
}
```

###  Character Categories in ASCII Table

**Punctuation characters (ispunct):**
```
!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
```

**Hexadecimal characters (isxdigit):**
```
0123456789ABCDEFabcdef
```

**Space characters (isspace) - ASCII codes:**
```
9 (tab), 10 (newline), 11 (vertical tab), 12 (form feed), 13 (carriage return), 32 (space)
```

**Control characters (iscntrl) - ASCII codes:**
```
0-31 and 127
```

---

## Character Conversion Functions

###  Basic Conversion Functions

| Function | Description | Example |
|----------|-------------|---------|
| `toupper(c)` | Converts lowercase to uppercase | `toupper('a')` → 'A' |
| `tolower(c)` | Converts uppercase to lowercase | `tolower('A')` → 'a' |

###  Important Notes
- If character is already in appropriate format, no change is made
- Non-alphabetic characters are not affected
- In ASCII table: `'A' = 65`, `'a' = 97`, difference = 32

### Practical Usage Examples

#### Case-Insensitive Character Comparison
```c
char c1, c2;
printf("Enter two characters: ");
c1 = getchar();
c2 = getchar();

if (toupper(c1) == toupper(c2)) {
    printf("%c and %c are the same characters (ignoring case)\n", c1, c2);
}
```

#### Manual tolower() Implementation
```c
// This code is an alternative to toupper() function
char c = 'O';
char result = (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
printf("%c", result); // output: 'o'
```

---

## Ternary Operator (Conditional Operator)

###  General Structure
```c
condition ? value_if_true : value_if_false
```

###  Operator Properties
- **Precedence**: 13th level (low precedence)
- **Associativity**: Right to left
- **Number of operands**: 3 (only ternary operator)
- **Side effect**: `?` is a sequence point

###  Basic Usage Examples

#### Finding Maximum
```c
int x = 15, y = 23;
int max = x > y ? x : y;
printf("Maximum: %d\n", max); // Output: 23
```

#### Finding Minimum
```c
int min = a < b ? a : b;
```

#### As Function Parameter
```c
printf("Result: %d\n", calculate(a > 10 ? x : y));
```

#### In Return Statement
```c
int get_max(int a, int b) {
    return a > b ? a : b;
}
```

###  Chaining Usage

#### Equivalent of If-Else If-Else Structure
```c
// Traditional method
int y;
if (x == 5)
    y = 13;
else if (x == 7)
    y = 29;
else
    y = 67;

// With ternary operator
int y = x == 5 ? 13 :
        x == 7 ? 29 : 67;
```

#### Multiple Condition Example
```c
char grade = score >= 90 ? 'A' :
             score >= 80 ? 'B' :
             score >= 70 ? 'C' :
             score >= 60 ? 'D' : 'F';
```

###  Things to Watch Out For

#### 1. Don't Use for Side Effects Only
```c
// WRONG - using only for side effect
a > 0 ? printf("Positive") : printf("Negative");

// CORRECT - use if-else
if (a > 0)
    printf("Positive");
else
    printf("Negative");
```

#### 2. L-Value Problem
```c
// ERROR in C - works in C++
x > 10 ? a : b = 0;

// CORRECT method in C
*(x > 10 ? &a : &b) = 0;
```

#### 3. Readability
```c
// Complex - avoid
result = (a > b) ? (c > d ? e : f) : (g > h ? i : (j > k ? l : m));

// More readable
if (a > b) {
    result = (c > d) ? e : f;
} else {
    if (g > h) 
        result = i;
    else
        result = (j > k) ? l : m;
}
```

###  Creative Usage Examples

#### Absolute Value
```c
int abs_value = x >= 0 ? x : -x;
```

#### Sign Determination
```c
int sign = x > 0 ? 1 : (x < 0 ? -1 : 0);
```

#### Array Index Safety
```c
int safe_index = index >= 0 && index < SIZE ? index : 0;
```

---

## Practical Algorithms

###  Digit Sum Algorithm

#### Algorithm Logic
1. Get the last digit of the number (`val % 10`)
2. Add this digit to sum
3. Divide the number by 10 (`val /= 10`)
4. Repeat until number becomes 0

```c
int sum_digit(int val) {
    int sum = 0;
    while (val != 0) {
        sum += val % 10;  // Add last digit
        val /= 10;        // Remove last digit
    }
    return sum;
}
```

#### Usage Examples
```c
printf("%d\n", sum_digit(4235));   // Output: 14 (4+2+3+5)
printf("%d\n", sum_digit(987678)); // Output: 49 (9+8+7+6+7+8)
```

###  Digit Count Algorithm

#### Algorithm Logic
1. Special case: if number is 0, return 1 digit
2. Divide by 10 until number becomes 0
3. Increment counter for each division

```c
int ndigit_count(int val) {
    int digit_count = 0;
    
    if (val == 0) {
        return 1;  // Number 0 has 1 digit
    }
    
    // For negative numbers, take absolute value
    if (val < 0) {
        val = -val;
    }
    
    while (val) {
        ++digit_count;
        val /= 10;
    }
    
    return digit_count;
}
```

#### Usage Examples
```c
printf("%d\n", ndigit_count(54897));  // Output: 5
printf("%d\n", ndigit_count(9857));   // Output: 4
printf("%d\n", ndigit_count(0));      // Output: 1
```

###  Digit Extraction Techniques

#### 4-Digit Number Example
```c
int number = 1234;

int ones = number % 10;           // 4
int tens = (number / 10) % 10;    // 3  
int hundreds = (number / 100) % 10; // 2
int thousands = number / 1000;    // 1
```

#### General Formula
```c
// To find the digit at position n (counting from right, 0 = ones place)
int nth_digit = (number / (int)pow(10, n)) % 10;
```

---

## Armstrong Numbers

###  Definition
An Armstrong number (or Narcissistic number) is a number that equals the sum of its digits each raised to the power of the number of digits.

###  Examples
- **3-digit**: 153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153
- **4-digit**: 1634 = 1⁴ + 6⁴ + 3⁴ + 4⁴ = 1 + 1296 + 81 + 256 = 1634
- **4-digit**: 8208 = 8⁴ + 2⁴ + 0⁴ + 8⁴ = 4096 + 16 + 0 + 4096 = 8208

###  Code to Find 4-Digit Armstrong Numbers
```c
void find_4digit_armstrong() {
    printf("4-digit Armstrong numbers:\n");
    
    for (int i = 1000; i < 10000; i++) {
        // Extract digits
        int d1 = i / 1000;           // Thousands place
        int d2 = (i / 100) % 10;     // Hundreds place  
        int d3 = (i / 10) % 10;      // Tens place
        int d4 = i % 10;             // Ones place
        
        // Sum of 4th powers
        int sum = (d1*d1*d1*d1) + (d2*d2*d2*d2) + (d3*d3*d3*d3) + (d4*d4*d4*d4);
        
        if (i == sum) {
            printf("%d\n", i);
        }
    }
}
```

###  General Armstrong Check Function
```c
#include <math.h>

int is_armstrong(int num) {
    int original = num;
    int digit_count = ndigit_count(num);  // Function defined above
    int sum = 0;
    
    while (num > 0) {
        int digit = num % 10;
        sum += (int)pow(digit, digit_count);
        num /= 10;
    }
    
    return sum == original;
}
```

### 📊 Known Armstrong Numbers
- **1-digit**: 1, 2, 3, 4, 5, 6, 7, 8, 9
- **3-digit**: 153, 370, 371, 407
- **4-digit**: 1634, 8208, 9474
- **5-digit**: 54748, 92727, 93084

---

## Important Tips and Pitfalls

###  Boolean Expression Comparisons

####  Problem: Different Return Values
```c
// WRONG - Different true values might not be equal
if (isprime(x) == isprime(y)) {
    // Even if isprime(x) = 5 and isprime(y) = 1, both are true
    // But 5 == 1 returns false!
}
```

####  Solution: Convert to Logical Values
```c
// CORRECT - Compare logical values
if (!!exp1 == !!exp2) {
    // !! operator produces logical value (0 or 1)
}

// Alternative solutions
if ((exp1 != 0) == (exp2 != 0))    // Explicit comparison
if ((!exp1) == (!exp2))            // Using negation
```

###  Logical Value Conversion Techniques
```c
int x = 42;
int y = -17;
int z = 0;

// Original values
printf("x = %d, y = %d, z = %d\n", x, y, z);  // 42, -17, 0

// Logical values
printf("!x = %d, !y = %d, !z = %d\n", !x, !y, !z);      // 0, 0, 1
printf("!!x = %d, !!y = %d, !!z = %d\n", !!x, !!y, !!z);  // 1, 1, 0
```

###  Safe Coding Practices

#### Input Validation
```c
int safe_getchar() {
    int ch = getchar();
    if (ch == EOF) {
        printf("Error: Could not read input!\n");
        return -1;
    }
    return ch;
}
```

#### Buffer Clearing
```c
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Clear the buffer
    }
}
```

###  Performance Tips

#### Character Checks
```c
// Fast custom implementations
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')
#define TO_UPPER(c) (IS_LOWER(c) ? (c) - 32 : (c))
#define TO_LOWER(c) (IS_UPPER(c) ? (c) + 32 : (c))
```

###  Common Mistakes and Solutions

#### 1. Sequence Point Errors
```c
// ERROR - Undefined behavior
int i = 5;
int result = i++ + ++i;  // Undefined!

// CORRECT
int i = 5;
i++;
int result = i + (++i);  // Still undefined!

// SAFEST
int i = 5;
i++;
i++;
int result = i + i;  // Safe
```

#### 2. Character vs Integer Confusion
```c
// ERROR - Confusing character with ASCII value
if (isdigit(ch)) {
    int value = ch;  // Gets ASCII value (e.g., '5' → 53)
}

// CORRECT
if (isdigit(ch)) {
    int value = ch - '0';  // Gets digit value (e.g., '5' → 5)
}
```

#### 3. Ternary Operator Precedence Errors
```c
// ERROR - Precedence confusion
int result = a + b > c ? d : e + f;  // (a + b > c) ? d : (e + f)

// Clearer
int result = (a + b > c) ? d : (e + f);
```

---
