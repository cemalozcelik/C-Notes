# C Programming Day 20 - String Operations and Introduction to Pointers

## String Operations - Solutions

### 1. String Copy
```c
char source[SIZE];
char dest[SIZE];

printf("Enter text: ");
sgets(source);

int i;
for (i = 0; source[i] != '\0'; i++) {
    dest[i] = source[i];
}
dest[i] = '\0';

printf("[%s]\n", source);
printf("[%s]\n", dest);
```

**Alternative (compact form):**
```c
int i = 0;
while ((dest[i] = source[i]) != '\0')
    i++;

// Or even more compact:
while (dest[i++] = source[i++])
    ;
```

**How it works:** Assignment returns the assigned value, loop continues until `'\0'` (which is 0, false).

---

### 2. Remove Character (Using Second Array)
```c
char source[SIZE];
char dest[SIZE];

printf("Enter text: ");
sgets(source);

int c;
printf("Enter character to remove: ");
c = getchar();

int i, k;
for (i = 0, k = 0; source[i] != '\0'; i++) {
    if (source[i] != c) {
        dest[k++] = source[i];
    }
}
dest[k] = '\0';

printf("Original: [%s]\n", source);
printf("Result:   [%s]\n", dest);
```

**Logic:** Copy only characters that don't match the target character.

---

### 3. Remove Character (In-Place, No Second Array)
```c
char source[SIZE];

printf("Enter text: ");
sgets(source);

int c;
printf("Enter character to remove: ");
c = getchar();

int idx_read = 0;
int idx_write = 0;

while (source[idx_read] != '\0') {
    if (source[idx_read] != c) {
        source[idx_write++] = source[idx_read];
    }
    idx_read++;
}

source[idx_write] = '\0';
printf("Result: [%s]\n", source);
```

**Two-pointer technique:**
- `idx_read` - reads each character
- `idx_write` - writes only non-matching characters
- More space-efficient (O(1) extra space)

---

### 4. String Comparison
```c
char s1[SIZE];
char s2[SIZE];

printf("Enter two strings: ");
scanf("%s%s", s1, s2);

int i = 0;
int flag = 0;

while (s1[i] == s2[i]) {
    if (s1[i] == '\0') {
        flag = 1;
        break;
    }
    i++;
}

if (flag)
    printf("Strings are EQUAL\n");
else
    printf("Strings are DIFFERENT\n");
```

**Logic:**
1. Compare character by character
2. If both reach `'\0'` together → Equal
3. If mismatch found → Different

---

### 5. Word Count
```c
char str[SIZE];

printf("Enter text: ");
sgets(str);

int word_count = 0;
int flag = 0;
int i = 0;

while (str[i] != '\0') {
    if (isspace(str[i]))
        flag = 0;  // Outside word
    else if (flag == 0) {
        flag = 1;  // Entering new word
        word_count++;
    }
    i++;
}

printf("[%s]\n", str);
printf("Word count: %d\n", word_count);
```

**State machine approach:**
- `flag = 0` → OUTWORD (outside a word)
- `flag = 1` → INWORD (inside a word)
- Count increases when transitioning from OUTWORD to INWORD

**Macro version:**
```c
#define INWORD  1
#define OUTWORD 0
```

---

### 6. Palindrome Check (With Second Array)
```c
char str1[SIZE];
char str2[SIZE];

printf("Enter text: ");
sgets(str1);

// Copy only alphabetic characters
int len = 0;
for (int k = 0; str1[k] != '\0'; k++) {
    if (isalpha(str1[k]))
        str2[len++] = str1[k];
}
str2[len] = '\0';

// Check palindrome
int j;
for (j = 0; j < len / 2; j++) {
    if (str2[j] != str2[len - 1 - j])
        break;
}

if (j == len / 2)
    printf("Text is PALINDROME\n");
else
    printf("Text is NOT PALINDROME\n");
```

**Logic:**
1. Extract only letters (ignore spaces, punctuation)
2. Compare first half with reversed second half
3. If loop completes (`j == len/2`) → Palindrome

**Examples:**
- "at sahibi" → "atsahibi" → Not palindrome
- "hasta" → "hasta" → Palindrome
- "tiras neden sarit" → "tirasnedensarit" → Palindrome

---

## Compiler Warnings and Logic Checks

### 1. Unused Return Values
```c
int c = getchar();  // Warning if c not used

// Suppress warning by explicit cast to void
(void)getchar();  // Intentionally ignoring return value
```

### 2. CRT_SECURE_NO_WARNINGS
```c
#define _CRT_SECURE_NO_WARNINGS

// Suppresses Visual Studio warnings about scanf, strcpy, etc.
// VS suggests scanf_s, strcpy_s (safer versions)
```

### 3. Code Has No Effect
```c
5;          // Valid syntax, but does nothing
a;          // Valid, no effect
a + 5;      // Valid, result discarded
a == 10;    // Warning: Code has no effect
```

**These are legal but meaningless statements.**

### 4. Unreachable Code
```c
int foo(int a) {
    if (a == 1)
        return 10;
    else
        return 100;
    
    return 1000;  // Warning: Unreachable code
}
```

Compilers can detect code that will never execute.

### 5. Infinite Loops
```c
while (1) {
    // Infinite loop
}
```

Some compilers warn about infinite loops, but not required to do so.

### 6. Stack Overflow
**Occurs in recursive functions without proper base case:**

```c
int factorial(int n) {
    return n * factorial(n - 1);  // No base case!
}
// Stack overflow - infinite recursion
```

**Proper recursion:**
```c
int factorial(int n) {
    if (n <= 1)
        return 1;  // Base case
    return n * factorial(n - 1);
}
```

**What happens:**
- Each function call uses stack memory
- Automatic variables allocated on stack
- Infinite recursion exhausts stack space
- Stack overflow error

---

## Code Quality Principles

### Avoid Code Repetition
**Code duplication is a disaster.**

**Bad:**
```c
printf("Enter name: ");
scanf("%s", name);
printf("Enter surname: ");
scanf("%s", surname);
printf("Enter age: ");
scanf("%d", &age);
```

**Better:**
```c
char* prompts[] = {"name", "surname", "age"};
// Use loop or function
```

**Principle:** DRY (Don't Repeat Yourself)

---

## Introduction to Pointers

### What Are Pointers?

**Pointer = Address**

Addresses store the **runtime location** of objects in memory.

### Two Types of Pointers
1. **Object pointers** - Point to variables/objects
2. **Function pointers** - Point to functions

---

### Pointer Types

**Every type has a corresponding pointer type:**

```c
int x;       // x is type int
int *ptr;    // ptr is type "pointer to int" (int*)

double y;
double *dptr;  // pointer to double (double*)

char c;
char *cptr;    // pointer to char (char*)
```

**Pointer type = Type of what it points to + `*`**

---

### Pointer Declaration Syntax

All three forms are equivalent:

```c
int *ptr;      // Most common
int* ptr;      // Emphasizes type
int * ptr;     // Space on both sides
```

**Type of `ptr`:** `int*` (pointer to int)

**Terminology:**
- `int*` → "pointer to int"
- `double*` → "pointer to double"
- `char*` → "pointer to char"

---

### Pointer Size

**All pointer types have the same size!**

```c
sizeof(int*)     // 4 bytes (32-bit) or 8 bytes (64-bit)
sizeof(double*)  // Same
sizeof(char*)    // Same
sizeof(short*)   // Same
```

**Why?** Pointers store memory addresses, which are the same size regardless of what they point to.

**On 32-bit systems:** Pointers = 4 bytes
**On 64-bit systems:** Pointers = 8 bytes

---

### Pointer Storage Duration

Pointers can have different storage durations:

```c
// Global (static storage)
int *global_ptr;

void func() {
    // Automatic storage (local)
    int *local_ptr;
    
    // Static storage (local but persistent)
    static int *static_ptr;
}
```

---

### Address-of Operator (&)

```c
int x = 10;
&x  // Address of x, type is int*
```

**The `&` operator:**
- Returns the address of a variable
- Type of `&x` is `int*` when x is `int`

---

### Basic Pointer Usage (Preview)

```c
int x = 10;
int *ptr;

ptr = &x;  // ptr now holds address of x

// ptr stores where x is located in memory
```

**More details in upcoming lessons!**

---

## Key Takeaways

### String Operations
1. **String copy** - Character-by-character or compact loop
2. **Remove character** - Two approaches: second array or in-place
3. **String comparison** - Compare until mismatch or both reach `'\0'`
4. **Word count** - State machine: INWORD/OUTWORD
5. **Palindrome** - Extract letters, compare with reverse
6. **Two-pointer technique** - Efficient for in-place modifications

### Compiler Warnings
1. **Unused return values** - Cast to `(void)` if intentional
2. **Code has no effect** - Valid but meaningless statements
3. **Unreachable code** - Code that never executes
4. **Stack overflow** - From infinite recursion

### Pointers - Introduction
1. **Pointer = address** of object in memory
2. **Every type has pointer type** (int → int*, double → double*)
3. **All pointers same size** (4 or 8 bytes)
4. **Address-of operator (`&`)** - Gets address of variable
5. **Pointer declaration** - `type *name`
6. **Storage duration** - Can be global, local, or static

---

## Important Notes

### gets() Function
```c
gets(str);  // Deprecated in C99, removed from C11
```

**Why removed:** No bounds checking → buffer overflow vulnerability

**Use instead:**
- `fgets(str, SIZE, stdin)`
- `sgets(str)` (custom implementation)
- `gets_s(str, SIZE)` (C11 optional, not widely supported)

### Visual Studio Security Warnings
Visual Studio suggests `_s` versions (secure versions) of functions:
- `scanf_s` instead of `scanf`
- `strcpy_s` instead of `strcpy`

Use `#define _CRT_SECURE_NO_WARNINGS` to suppress if needed.

---

## Common Patterns

### String Copy Loop
```c
int i = 0;
while ((dest[i] = source[i]) != '\0')
    i++;
```

### Two-Pointer In-Place Modification
```c
int read = 0, write = 0;
while (source[read] != '\0') {
    if (condition)
        source[write++] = source[read];
    read++;
}
source[write] = '\0';
```

### Palindrome Check Pattern
```c
for (j = 0; j < len / 2; j++) {
    if (str[j] != str[len - 1 - j])
        break;
}
if (j == len / 2)
    // Is palindrome
```