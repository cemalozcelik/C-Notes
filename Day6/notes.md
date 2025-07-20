# C Programming Day 6 Notes

## Buffer Management and Operator Precedence

## 1. Buffer Clearing

### Problem: Why Do We Need Buffer Clearing?

```c
void clear_buffer()
{
    int c;
    c = getchar();
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
```

**Situation:** When you use scanf and user enters invalid input like "12 asd":
- scanf only reads "12" and assigns it to variable x
- " asd\n" remains in the input buffer
- Next scanf tries to read this remaining data and doesn't wait for new input

**Solution:** clear_buffer() function clears all characters in buffer until '\n' (newline) character.

### How It Works:
1. `getchar()` reads one character from buffer
2. While loop reads and discards all characters until newline ('\n') or end of file (EOF)
3. After buffer is cleared, next scanf works properly

### Alternative Buffer Clearing Method:
```c
// Method 2: Using scanf to consume remaining characters
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

## 2. Increment and Decrement Operators

### Pre-increment vs Post-increment

```c
int a = 12, b = 6;
printf("%d\n", a++);  // Print a's value first (12), then increment
printf("%d\n", a);    // Incremented value (13)
printf("%d\n", ++b);  // Increment first, then print (7)
```

**Difference:**
- `a++` (post-increment): Use value first, then increment
- `++b` (pre-increment): Increment first, then use value

### Side Effects
- **++x**: Produces incremented value of x, side effect is incrementing x
- **x++**: Produces current value of x, side effect is incrementing x

## 3. Operator Precedence Table

Order of operator evaluation in C:

| Precedence | Operators | Associativity |
|------------|-----------|---------------|
| 1 | `() [] . ->` | Left→Right |
| 2 | `+ - ! ~ & * sizeof (type cast) ++ --` | Right→Left |
| 3 | `* / %` | Left→Right |
| 4 | `+ -` | Left→Right |
| 5 | `<< >>` | Left→Right |
| 6 | `< <= > >=` | Left→Right |
| 7 | `== !=` | Left→Right |
| 8 | `&` | Left→Right |
| 9 | `^` | Left→Right |
| 10 | `|` | Left→Right |
| 11 | `&&` | Left→Right |
| 12 | `||` | Left→Right |
| 13 | `? :` | Right→Left |
| 14 | `= += -= *= /= %= >>= <<= &= ^= |=` | Right→Left |
| 15 | `,` | Left→Right |

### Memory Trick for Precedence:
**PEMDAS-like rule**: Parentheses → Unary → Multiplicative → Additive → Shift → Relational → Equality → Bitwise → Logical → Ternary → Assignment → Comma

## 4. Practical Examples

### Example 1: Complex Expression
```c
x1++ * y1 - 10 / 5 < z1 % 5;
```

**Parenthesized form:**
```c
(((x1++) * y1) - (10 / 5)) < (z1 % 5);
```

**Step by step:**
1. `x1++` → produces value 10, makes x1 = 11
2. `10 * y1` → 10 * 10 = 100
3. `10 / 5` → 2
4. `z1 % 5` → 10 % 5 = 0
5. `100 - 2` → 98
6. `98 < 0` → 0 (false)

### Example 2: Right-to-Left Evaluation
```c
!~x1++;
```

**Parenthesized form:**
```c
!(~(x1++));
```

Operators at precedence level 2 are evaluated right-to-left.

### Example 3: Comparison Operators
```c
printf("Value: %d\n", 1 == 2 != 3);  // ((1 == 2) != 3) = (0 != 3) = 1
printf("Value: %d\n", 1 != 2 == 3);  // ((1 != 2) == 3) = (1 == 3) = 0
```

Comparison operators in C:
- Return **1** if true
- Return **0** if false

## 5. Notes

### Modulo Operator (%)
- Use `%` operator for **integer types**
- Use `fmod()` function for **double/float types**
- If right operand is 0, results in **undefined behavior**

### lvalue Expressions
- Operands of `++` and `--` operators must be lvalue
- lvalue: Expressions that have memory location and can be modified
- Example: `5++` is invalid, `x++` is valid
