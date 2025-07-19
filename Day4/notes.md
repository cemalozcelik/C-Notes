# Day 4 C Programming Notes

## Number Systems and Constants
*Building on Day 3: Arrays and Loops*

### Number System Representations in C

C supports multiple number systems for integer literals:

```c
int decimal = 41;        // Decimal (base 10)
int octal = 041;         // Octal (base 8) - starts with 0
int hexadecimal = 0x41;  // Hexadecimal (base 16) - starts with 0x
int binary = 0b110111;   // Binary (base 2) - compiler extension
```

**Value Conversions:**
- `41` (decimal) = `51` (octal) = `65` (hex) = `1000001` (binary)
- `041` (octal) = `33` (decimal)
- `0x41` (hex) = `65` (decimal)
- `0b110111` (binary) = `55` (decimal)

### Integer Type Hierarchy and Overflow

When integer literals exceed the range of `int`, C follows a specific hierarchy:

#### For Decimal Numbers (base 10):
```
int → long → unsigned long → long long → unsigned long long
```

#### For Octal (base 8) and Hexadecimal (base 16):
```
int → unsigned int → long → unsigned long → long long → unsigned long long
```

**Important Note:** The key difference is that octal and hexadecimal include `unsigned int` in the hierarchy, while decimal skips it.

### Integer Overflow Behavior

```c
int x = 2147483647;  // Maximum int value (if int is 4 bytes)
int y = 2147483650;  // Exceeds int range - promotes to long

// DANGEROUS: Signed integer overflow is Undefined Behavior (UB)
int overflow = 2147483647 + 1;  // UB if this overflows int
```

**Key Rules:**
- **Signed overflow**: Undefined Behavior
- **Unsigned overflow**: Well-defined (wraps around)
- **Mixed operations**: `signed + unsigned` → result is `unsigned`

### Integer Literal Suffixes

```c
// Unsigned suffixes
642u;    // unsigned int
642U;    // unsigned int
0x12u;   // unsigned int (hex)

// Long suffixes
45L;     // long
39l;     // long (lowercase L - avoid, looks like 1)
0x65L;   // long (hex)
0145L;   // long (octal)

// Combined suffixes
54LU;    // unsigned long
57UL;    // unsigned long
54LLU;   // unsigned long long
45ULL;   // unsigned long long
45llu;   // unsigned long long (mixed case)

// Long long suffixes
5LL;     // long long
4578LL;  // long long

// Special case - zero
0;       // int
0u;      // unsigned int
0LU;     // unsigned long
0LL;     // long long
```

---

## Floating-Point Numbers

### Float Representations

```c
// Double (default for floating literals)
34.0;
34.;     // Same as 34.0
0.52;
.51;     // Same as 0.51

// Float (with f/F suffix)
34.3F;
0.5f;

// Long double (with l/L suffix)
7.5L;
7.L;

// Scientific notation
2.8e8;    // 2.8 × 10^8 = 280,000,000
3.6E7;    // 3.6 × 10^7 = 36,000,000
4123e-5;  // 4123 × 10^-5 = 0.04123
```

### Floating-Point Precision Issues

```c
float f = 1.4;
if (f == 1.4) {          // This will likely be FALSE!
    printf("Equal\n");
} else {
    printf("Not equal\n"); // This will probably execute
}
```

**Why this happens:**
- `1.4` is a `double` literal
- `f` is a `float` with less precision
- The comparison compares different precision values

**Better approach:**
```c
float f = 1.4f;  // Use float literal
if (f == 1.4f) {
    printf("Equal\n");  // This will work
}
```

---

## Character Constants and Escape Sequences

### Character Representations

```c
// Regular character
char c = 'A';

// Escape sequences
'\a';     // Bell (alert)
'\n';     // Newline
'\t';     // Tab
'\\';     // Backslash
'\'';     // Single quote
'\"';     // Double quote

// Numeric representations
'\x41';   // Hexadecimal (A)
'\105';   // Octal (A)
' ';      // Space character
```

### Numeric Character Codes

```c
// All these represent the same character 'A' (ASCII 65)
char a1 = 'A';
char a2 = 65;      // Decimal
char a3 = '\x41';  // Hexadecimal
char a4 = '\101';  // Octal

// Examples from your code
printf("\x42URS\x41\n");           // Prints: BURSA
printf("\102\101\102\101\012");    // Prints: BABA (with newline)
```

---

## File I/O Operations

### Basic File Operations

```c
#include <stdio.h>

// Opening a file
FILE* file = fopen("filename.txt", "mode");

// Always check if file opened successfully
if (!file) {
    fprintf(stderr, "Cannot open file\n");
    return;
}

// Don't forget to close the file
fclose(file);
```

### File Opening Modes

```c
fopen("file.txt", "r");   // Read only
fopen("file.txt", "w");   // Write only (overwrites existing)
fopen("file.txt", "a");   // Append only
fopen("file.txt", "r+");  // Read and write
fopen("file.txt", "w+");  // Read and write (overwrites)
fopen("file.txt", "a+");  // Read and append
```

### Writing to Files

```c
void create_ascii_table() {
    FILE* file = fopen("ascii.txt", "w");
    if (!file) {
        fprintf(stderr, "Cannot create file\n");
        return;
    }
    
    for (int i = 0; i < 128; i++) {
        if (iscntrl(i)) {
            fprintf(file, "%-3d    %2X   CONTROL CHARACTER\n", i, i);
        } else {
            fprintf(file, "%-3d    %2X   %c\n", i, i, i);
        }
    }
    
    fclose(file);
}
```

### Format Specifiers in fprintf

```c
fprintf(file, "%-3d", number);    // Left-aligned, minimum 3 digits
fprintf(file, "%2X", number);     // Hexadecimal, minimum 2 digits, uppercase
fprintf(file, "%c", character);   // Character
fprintf(file, "%s", string);      // String
fprintf(file, "%f", float_num);   // Float
fprintf(file, "%.2f", float_num); // Float with 2 decimal places
```

---

## Character Classification Functions

Include `<ctype.h>` for these functions:

```c
#include <ctype.h>

// Character testing functions
iscntrl(c);   // Is control character?
isdigit(c);   // Is digit (0-9)?
isalpha(c);   // Is letter (a-z, A-Z)?
isalnum(c);   // Is alphanumeric?
isspace(c);   // Is whitespace?
isupper(c);   // Is uppercase letter?
islower(c);   // Is lowercase letter?
ispunct(c);   // Is punctuation?

// Character conversion functions
toupper(c);   // Convert to uppercase
tolower(c);   // Convert to lowercase
```

### Example: Analyzing Characters

```c
void analyze_character(char c) {
    printf("Character: '%c' (ASCII: %d)\n", c, c);
    
    if (iscntrl(c))
        printf("  - Control character\n");
    if (isdigit(c))
        printf("  - Digit\n");
    if (isalpha(c))
        printf("  - Letter\n");
    if (isspace(c))
        printf("  - Whitespace\n");
    if (ispunct(c))
        printf("  - Punctuation\n");
}
```

---

## Preprocessor Directives

### Common Preprocessor Directives

```c
#define _CRT_SECURE_NO_WARNINGS  // Disable MSVC security warnings
#include <stdio.h>               // Include header file
#include <ctype.h>               // Include character functions

// Define constants
#define PI 3.14159
#define MAX_SIZE 100
#define SQUARE(x) ((x) * (x))    // Function-like macro
```

### Why _CRT_SECURE_NO_WARNINGS?

This directive disables Microsoft Visual C++ warnings about "unsafe" functions like `scanf`, `strcpy`, etc. Microsoft recommends their "secure" versions (`scanf_s`, `strcpy_s`), but the standard C functions are perfectly safe when used correctly.

---

## Practical Examples

### Example 1: Number Base Converter

```c
void print_number_bases(int num) {
    printf("Number: %d\n", num);
    printf("Octal: %o\n", num);
    printf("Hexadecimal: %x (lowercase)\n", num);
    printf("Hexadecimal: %X (uppercase)\n", num);
    printf("Character (if printable): ");
    
    if (num >= 32 && num <= 126) {
        printf("'%c'\n", num);
    } else {
        printf("Non-printable\n");
    }
}
```

### Example 2: File Processing with Arrays

```c
void save_array_to_file(int arr[], int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Cannot create file: %s\n", filename);
        return;
    }
    
    fprintf(file, "Array size: %d\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(file, "arr[%d] = %d\n", i, arr[i]);
    }
    
    fclose(file);
    printf("Array saved to %s\n", filename);
}
```

### Example 3: Character Frequency Counter

```c
void count_character_types(const char* text) {
    int digits = 0, letters = 0, spaces = 0, others = 0;
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isdigit(text[i]))
            digits++;
        else if (isalpha(text[i]))
            letters++;
        else if (isspace(text[i]))
            spaces++;
        else
            others++;
    }
    
    printf("Digits: %d, Letters: %d, Spaces: %d, Others: %d\n",
           digits, letters, spaces, others);
}
```

---

## Important Notes and Best Practices

### 1. Integer Literal Best Practices
```c
// Good
int x = 42;
unsigned int y = 42u;
long z = 42L;

// Avoid (confusing)
long bad = 42l;  // lowercase 'l' looks like '1'
```

### 2. Floating-Point Comparisons
```c
// Bad
if (f == 1.4) { ... }

// Good
if (fabs(f - 1.4) < 0.0001) { ... }
// or use float literal
if (f == 1.4f) { ... }
```

### 3. File Handling
```c
// Always check file operations
FILE* file = fopen("data.txt", "r");
if (!file) {
    // Handle error
    return -1;
}

// Always close files
fclose(file);
```

### 4. Character Constants
```c
// Use meaningful escape sequences
printf("Hello\n");           // Good
printf("Hello\x0A");         // Less readable
printf("Hello\012");         // Even less readable
```

---

## Connection to Day 3 (Arrays and Loops)

### Combining Arrays with File I/O

```c
void save_grades_to_file(int grades[], int count) {
    FILE* file = fopen("grades.txt", "w");
    if (!file) return;
    
    // Calculate statistics
    int sum = 0, max = grades[0], min = grades[0];
    for (int i = 0; i < count; i++) {
        sum += grades[i];
        if (grades[i] > max) max = grades[i];
        if (grades[i] < min) min = grades[i];
    }
    
    // Write to file
    fprintf(file, "Grade Report\n");
    fprintf(file, "============\n");
    fprintf(file, "Total students: %d\n", count);
    fprintf(file, "Average: %.2f\n", (double)sum / count);
    fprintf(file, "Highest: %d\n", max);
    fprintf(file, "Lowest: %d\n", min);
    fprintf(file, "\nIndividual grades:\n");
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "Student %d: %d\n", i + 1, grades[i]);
    }
    
    fclose(file);
}
```

### Processing Character Arrays

```c
void analyze_text_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    
    int char_count[256] = {0};  // Array to count each ASCII character
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        char_count[c]++;
    }
    
    fclose(file);
    
    // Print statistics
    printf("Character frequency analysis:\n");
    for (int i = 0; i < 256; i++) {
        if (char_count[i] > 0) {
            if (isprint(i)) {
                printf("'%c': %d times\n", i, char_count[i]);
            } else {
                printf("ASCII %d: %d times\n", i, char_count[i]);
            }
        }
    }
}
```

This Day 4 content builds upon your Day 3 knowledge of arrays and loops, adding file I/O, number systems, and character handling - essential skills for more advanced C programming!