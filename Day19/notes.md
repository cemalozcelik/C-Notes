# C Programming Day 19 - Strings and Character Arrays

## Binary Search Algorithm

### Concept
Search in **sorted arrays** by repeatedly dividing search space in half.

**Time Complexity:** O(log n) - much faster than linear search O(n)

### Implementation
```c
int binary_search(int *a, int size, int sval) {
    int idx_first = 0;
    int idx_last = size - 1;
    int idx_mid;
    
    while (idx_first <= idx_last) {
        idx_mid = (idx_first + idx_last) / 2;
        
        if (a[idx_mid] == sval)
            return idx_mid;  // Found!
        
        if (a[idx_mid] > sval)
            idx_last = idx_mid - 1;   // Search left half
        else
            idx_first = idx_mid + 1;  // Search right half
    }
    
    return -1;  // Not found
}
```

### How It Works
1. Find middle element
2. If target equals middle → Found!
3. If target < middle → Search left half
4. If target > middle → Search right half
5. Repeat until found or exhausted

**Key:** Array must be sorted first!

**Example:** Finding 42 in sorted array
```
[10, 20, 30, 40, 50, 60, 70, 80, 90]
Step 1: mid=50, 42<50 → search left
[10, 20, 30, 40]
Step 2: mid=20, 42>20 → search right
[30, 40]
Step 3: mid=30, 42>30 → search right
[40]
Step 4: Found at index 3
```

---

## Strings and Character Arrays

### Fundamental Concepts

#### Character Codes (ASCII)
```c
char c = 65;        // 'A'
printf("%c", c);    // Prints: A

char d = 'A';       // Same as 65
char e = '0';       // Character '0' = 48 (NOT zero!)
char f = '\0';      // Null character = 0
```

**Important distinctions:**
- `'A'` = 65 (character A)
- `'0'` = 48 (character zero)
- `'\0'` = 0 (null character)
- `0` = 0 (integer zero)

#### Null-Terminated Strings

**C strings are null-terminated byte streams.**

```c
char str[] = "HELLO";
// Memory: ['H']['E']['L']['L']['O']['\0']
//          0    1    2    3    4    5
```

**CRITICAL:** Every string **must** end with `'\0'` (null character).
- Without `'\0'`, functions don't know where string ends → **UB**

### String Declaration and Initialization

#### Valid Declarations
```c
// String literal initialization
char s1[100] = "Ali ata bak";      // Adds '\0' automatically

// Character array with explicit size
char s2[] = "CEMAL";                // Size = 6 (includes '\0')

// Character by character (with null)
char s3[] = {'A', 'L', 'I', '\0'}; // Explicit null terminator

// Partial initialization
char s4[10] = "Hi";                // Remaining = 0 (null chars)

// Static/global (auto-initialized to 0)
static char s5[100];               // All zeros = empty string
```

#### Invalid or Dangerous
```c
// No null terminator - UB when used!
char s1[] = {'A', 'L', 'I'};       // Size=3, no '\0'

// Too small for string + '\0'
char s2[3] = "ABC";                // No room for '\0' (C allows, C++ error)

// Automatic storage, uninitialized
void func() {
    char s3[100];                  // Garbage values
    s3[0] = 'A';
    s3[1] = 'B';
    // s3[2] is garbage, no '\0' → UB when used
}

// Cannot assign strings after declaration
char s4[100];
s4 = "hello";                      // Syntax error! Arrays aren't lvalues
```

### C vs C++ Difference
```c
char s[5] = "EMRAH";  // 5 chars + '\0' = 6 total
```
- **C:** Compiles (but UB if used as string - no null terminator)
- **C++:** Syntax error (won't fit)

---

## String Output

### puts Function
```c
char str[] = "Hello World";
puts(str);  // Prints string + newline automatically
```
- Adds `\n` at end
- Takes address of string

### printf with %s
```c
char name[] = "Cemal";
char surname[] = "Ozcelik";
int year = 1998;

printf("%s %s %d yilinda dogdu\n", name, surname, year);
// Output: Cemal Özçelik 1998 yilinda dogdu
```

**%s format specifier:** Expects address of char array (string)

---

## String Input

### Character-by-Character Input
```c
char str[SIZE];
int c;
int idx = 0;

printf("Bir yazi girin: ");
while ((c = getchar()) != '\n') {
    str[idx++] = c;
}
str[idx] = '\0';  // CRITICAL: Add null terminator!

printf("Girilen: (%s)\n", str);
```

### scanf with %s
```c
char str[100];
scanf("%s", str);  // Stops at whitespace (space, tab, newline)
```

**Limitations:**
- Stops at first whitespace
- No bounds checking → **Buffer overflow risk!**

**Example:**
```c
scanf("%s", str);  // Input: "Ali Veli"
printf("(%s)", str);  // Output: "Ali" only
```

### Multiple Words with scanf
```c
char name[SIZE];
char surname[SIZE];
int age;

scanf("%s%s%d", name, surname, &age);  // "Cemal Ozcelik 28"
printf("%d yasindaki %s %s", age, name, surname);
```

### Custom Input Function - sgets
```c
// Custom implementation (from nutility)
void sgets(char *str) {
    int c;
    int idx = 0;
    
    while ((c = getchar()) != '\n')
        str[idx++] = c;
    
    str[idx] = '\0';
}

// Usage
char str[100];
sgets(str);  // Reads entire line including spaces
```

---

## Common String Operations

### 1. String Length
```c
char str[SIZE];
sgets(str);

int len = 0;
for (int i = 0; str[i] != '\0'; i++)
    len++;

printf("Length: %d\n", len);
```

**Alternative loop conditions:**
```c
for (i = 0; str[i] != '\0'; i++)  // Explicit comparison
for (i = 0; str[i] != 0; i++)     // Same (0 = '\0')
for (i = 0; str[i]; i++)          // Implicit (non-zero = true)
```

### 2. Append Character
```c
char str[100];
scanf("%s", str);

// Find end
int i;
for (i = 0; str[i] != '\0'; i++)
    ;

// Append 'x'
str[i] = 'x';
str[i + 1] = '\0';  // Don't forget null terminator!

printf("(%s)", str);
```

### 3. Count Specific Character
```c
char str[SIZE];
int ch;
int count = 0;

printf("Bir yazi girin: ");
sgets(str);

printf("Sayilacak karakter: ");
ch = getchar();

for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == ch)
        count++;
}

printf("%d adet %c\n", count, ch);
```

**Case-insensitive version:**
```c
if (toupper(str[i]) == toupper(ch))  // Ignore case
    count++;
```

### 4. Character Frequency (Histogram)
```c
#include <ctype.h>

char str[SIZE];
int counts[26] = {0};  // A-Z frequency

printf("Bir yazi girin: ");
sgets(str);

// Count each letter
for (int i = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
        counts[toupper(str[i]) - 'A']++;
    }
}

// Print frequencies
for (int i = 0; i < 26; i++) {
    if (counts[i])
        printf("%d adet %c\n", counts[i], 'A' + i);
}
```

**How it works:**
- `toupper(str[i])` → Convert to uppercase
- `- 'A'` → 'A'=0, 'B'=1, ..., 'Z'=25
- `counts[index]++` → Increment frequency

### 5. String Reverse (In-Place)
```c
char str[SIZE];

printf("Bir yazi girin: ");
sgets(str);

// Find length
int len = 0;
for (int i = 0; str[i] != '\0'; i++)
    len++;

// Reverse
for (int i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
}

printf("Tersi: (%s)\n", str);
```

### 6. String Concatenation
```c
char s1[SIZE];
char s2[SIZE];

printf("Iki kelime giriniz: ");
scanf("%s%s", s1, s2);

// Find end of s1
int i;
for (i = 0; s1[i] != '\0'; i++)
    ;

// Append s2 to s1
int k;
for (k = 0; s2[k] != '\0'; k++) {
    s1[i + k] = s2[k];
}

s1[i + k] = '\0';  // Add null terminator

printf("%s\n", s1);
```

---

## Important Character Testing Functions (ctype.h)

```c
#include <ctype.h>

isalpha(c)   // Is alphabetic? (A-Z, a-z)
isdigit(c)   // Is digit? (0-9)
isalnum(c)   // Is alphanumeric?
isspace(c)   // Is whitespace? (space, tab, newline)
isupper(c)   // Is uppercase?
islower(c)   // Is lowercase?

toupper(c)   // Convert to uppercase
tolower(c)   // Convert to lowercase
```

---

## Key Takeaways

1. **Strings are char arrays ending with `'\0'`**
2. **No `'\0'` = not a valid string** → UB when used
3. **String literals automatically add `'\0'`**
4. **Array size must include space for `'\0'`**
5. **`'0'` ≠ `'\0'` ≠ `0`** (different values!)
6. **scanf %s stops at whitespace**
7. **Always add `'\0'` when building strings manually**
8. **Static/global arrays auto-initialize to 0**
9. **Local automatic arrays have garbage values**
10. **Strings cannot be assigned** (`s = "text"` is invalid after declaration)

---

## Common Pitfalls

### Missing Null Terminator
```c
char s[3] = {'A', 'B', 'C'};  // No '\0'!
puts(s);  // UB - keeps reading past array
```

### Buffer Overflow with scanf
```c
char name[5];
scanf("%s", name);  // User enters "Alexander"
// Buffer overflow! Writes past array bounds
```

### Forgetting to Add '\0'
```c
char str[100];
int idx = 0;
while ((c = getchar()) != '\n')
    str[idx++] = c;
// Missing: str[idx] = '\0';
```

### Confusing Character Values
```c
if (c == 0)    // Checks if null character
if (c == '0')  // Checks if character '0' (48)
```

---

## Common Patterns to Memorize

### String Length
```c
int len = 0;
while (str[len] != '\0')
    len++;
```

### String Traversal
```c
for (int i = 0; str[i] != '\0'; i++)
    // Process str[i]
```

### Find End of String
```c
int i;
for (i = 0; str[i] != '\0'; i++)
    ;
// i now points to '\0' position
```

### String Copy Pattern
```c
int i;
for (i = 0; src[i] != '\0'; i++)
    dest[i] = src[i];
dest[i] = '\0';
```