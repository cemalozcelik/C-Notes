# C Programming Day 15 - Notes

## Predefined Symbolic Constants

These macros are automatically defined (no `#define` needed) and **cannot** be removed with `#undef`:

- `__LINE__` - current line number
- `__FILE__` - current filename  
- `__DATE__` - compilation date
- `__TIME__` - compilation time
- `__func__` - function name (added in C99)
- `__STDC__` - defined if compiler extensions are disabled (standard C)
- `__cplusplus` - defined for C++ compilers

```c
printf("File: %s, Line: %d\n", __FILE__, __LINE__);
```

**Note**: These are useful for debugging and can't be undefined.

---

## Switch Statement

Better alternative to if-else chains. Compiler can optimize better in some cases.

### Basic syntax:
```c
switch(x) {  // x must be integer expression (no floats!)
    case 1:
        statements;
        break;
    case 2:
        statements; 
        break;
    default:
        statements;
        break;
}
```

### Important rules:
- Case labels must be **unique** (syntax error otherwise)
- Case values must be **integer constants** (no variables!)
- Cases don't need to be in order
- Character constants are OK: `case 'a':`

### Fall-through behavior:
If no `break`, execution continues to next case!

```c
switch(x) {
    case 1:
        printf("One ");  // if x=1, prints "One Two Three"
    case 2:  
        printf("Two ");  // if x=2, prints "Two Three"
    case 3:
        printf("Three");
        break;
}
```

### Valid/Invalid examples:
```c
// VALID
case 1:
case 'a':
case 10/2-1:  // evaluates to 4
case CONSTANT:  // if CONSTANT is #defined

// INVALID  
int x = 5;
case x:        // ERROR: not constant
case "hello":  // ERROR: string literal
case 2.5:      // ERROR: float
```

### Variable declarations in switch:
```c
// VALID: before any case
switch(x) {
    int var;  // OK here
    case 1: var = 10; break;
    case 2: var = 20; break;
}

// INVALID in C: declaration inside case
switch(x) {
    case 1:
        int var;  // ERROR in C (OK in C++)
        break;
}

// VALID: use null statement
switch(x) {
    case 1:;       // null statement
        int var = 10;  // now OK
        break;
}
```

### Performance tip:
Sequential case values → compiler creates **jump table** → O(1) access time!

---

## Goto Statement

Creates **labels** with function scope.

```c
label_name:
    statement;
```

### Usage:
```c
goto error;  // jumps to error label

error:
    printf("Error occurred\n");
```

### Scope rules:
- Labels have **function scope** (can be used anywhere in function)
- Don't conflict with variable names
- Forward and backward jumps allowed (but backward jumps rarely used)

### Good use cases:

**1. Breaking out of nested loops:**
```c
while(1) {
    while(1) {
        while(1) {
            if(condition)
                goto result;  // breaks all loops
        }
    }
}

result:
    printf("Done\n");
```

**2. Error handling:**
```c
ptr1 = malloc(size1);
if(!ptr1) goto cleanup;

ptr2 = malloc(size2); 
if(!ptr2) goto cleanup;

// normal processing...
return SUCCESS;

cleanup:
    free(ptr1);
    free(ptr2);
    return ERROR;
```

**3. Switch statement limitations:**
```c
while(1) {
    switch(cmd) {
        case EXIT:
            goto exit_program;  // can't break from while with just break
        case CONTINUE:
            break;  // only breaks from switch
    }
}

exit_program:
    printf("Exiting...\n");
```

---

## Preprocessor Directives

### #line directive
Changes `__LINE__` macro value (used by code generators):
```c
#line 1000           // __LINE__ becomes 1000
#line 1000 "test.c"  // changes both __LINE__ and __FILE__
```

### #error directive  
Stops compilation with error message:
```c
#ifndef __cplusplus
#error This file must be compiled with C++ compiler!
#endif
```

### #pragma directive
Compiler-specific commands:
```c
#pragma once                    // include guard
#pragma pack(1)                // struct alignment  
#pragma warning(disable: 4706) // disable warning
```

### Multiple inclusion guard
Prevents header from being included multiple times:
```c
#ifndef HEADER_H
#define HEADER_H

// header content here

#endif
```

**Alternative**: `#pragma once` (compiler-specific but widely supported)

---

## Common Patterns

### State machine with switch:
```c
#define OFF     0
#define ON      1  
#define STANDBY 2
#define HOLD    3

switch(get_remote_state()) {
    case OFF:     handle_off(); break;
    case ON:      handle_on(); break; 
    case STANDBY: handle_standby(); break;
    case HOLD:    handle_hold(); break;
    default:      handle_error(); break;
}
```

### Fall-through for grouped cases:
```c
switch(month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        days = 31; 
        break;
    case 4: case 6: case 9: case 11:
        days = 30;
        break;
    case 2:
        days = 28 + is_leap_year(year);
        break;
}
```

### Day of year calculation (clever fall-through):
```c
int sum = day;
switch(month - 1) {
    case 11: sum += 30; // fallthrough - December
    case 10: sum += 31; // fallthrough - November  
    case 9:  sum += 30; // fallthrough - October
    case 8:  sum += 31; // fallthrough - September
    case 7:  sum += 31; // fallthrough - August
    case 6:  sum += 30; // fallthrough - July
    case 5:  sum += 31; // fallthrough - June
    case 4:  sum += 30; // fallthrough - May
    case 3:  sum += 31; // fallthrough - April
    case 2:  sum += 28 + is_leap_year(year); // fallthrough - March
    case 1:  sum += 31; // January
}
```

---

## Key Takeaways

1. **Switch is faster than if-else chains** when cases are sequential
2. **Always consider fall-through** - use `break` unless intentional
3. **Goto isn't always evil** - useful for error handling and breaking nested loops
4. **Predefined macros are great for debugging**
5. **Use symbolic constants** instead of magic numbers in switch cases

## Tools mentioned:
- **Compiler Explorer**: https://godbolt.org/ (see assembly output)
- **Static analysis tools** for code quality