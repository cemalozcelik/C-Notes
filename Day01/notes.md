# Day 1 – C Language Basics

## Core Concepts

### Identifiers & Naming Rules
- Cannot use keywords as names (e.g., `int`, `return`)
- Names must begin with a letter or underscore `_`, not a digit
- Maximum 63 characters
- C is case-sensitive: `sum`, `Sum`, and `SUM` are different

### Identifier Categories
- Variables, Functions, Constants
- Tags (labels for `goto`)
- Types (e.g., `typedef`, `struct`)

### Operators
- C has 45 built-in operators
- `sizeof` is both a keyword and an operator

### Tokens in C
C source code is made of tokens:
- Keywords (`int`, `if`, `return`)
- Identifiers (`x`, `total`)
- Constants (`10`, `'A'`)
- Operators (`+`, `-`, `*`)
- String literals (`"text"`)
- Delimiters (`;`, `{}`, `()`)

Example:
```c
sum += 4; // 4 tokens: sum, +=, 4, ;
```

### Code Layout
Whitespace and indentation are ignored by the compiler but matter for readability.

### Expression vs Statement
- **Expression:** Produces a value (`x + 5`, `10`)
- **Statement:** Performs an action (`x++;`, `return 0;`)

### Value Categories
- **lvalue:** Has a memory address (`x`, `x[4]`)
- **rvalue:** Temporary value, no address (`5`, `x + 5`)

### Constant Expressions
- Compile-time evaluable: `10 + 80 - 40`
- Not constant: `x + y`

### Object & Type
Object = memory-holding entity (e.g., `int x = 10;`)

Type defines:
- How many bytes to allocate
- How to interpret 0s and 1s
- Which operations are allowed

### Static vs Dynamic Types
- Static type languages: C, C++, Java
- Dynamic type languages: Python, JS, etc.

### Data Types
- Basic types: `int`, `char`, `float`, `double`
- User-defined types: `struct`, `enum`, `typedef`

### Declaration vs Statement
- **Declaration:** Tells compiler what a name means (`int x;`)
- **Statement:** Tells compiler to perform an action (`x++;`)

### Statement Types
- Expression Statement: `x++;`
- Null Statement: `;`
- Compound Statement: `{ x++; y++; }`
- Control Statements: `if`, `while`, `for`, `switch`, `goto`, `break`, `continue`, `return`

### Character Classes
- Invalid in identifiers: `@`, `$`, `` ` ``
- Printable characters: visible symbols
- Alphabetic: A-Z, a-z
- Numeric: 0–9
- Punctuation: `;`, `{`, `+`, etc.

### Scope (Namespace)
- Local scope: inside blocks/functions
- Global scope: top-level declarations only (no executable code)

Example:
```c
int x = 10;  // OK
// x++;     // Not allowed globally
```

### Undefined Behavior
Unpredictable result due to compiler optimizations or logic errors

Example: using uninitialized variables or modifying the same variable multiple times in one expression