# C Programming Day 8 Notes

## 1. Opening Example
```c
printf("%d\n", (6, 7));
```
**Result:** Prints `7`
**Why:** The comma operator evaluates both operands but returns the value of the right operand.

---

## 2. Sequence Points and Side Effects (ÇOK ÖNEMLİ - VERY IMPORTANT!)

### What is a Side Effect?
A side effect occurs when code changes the state of something in memory.

```c
int x = 10;
++x;  // This has a side effect - x's value changes
```

**Key Question:** When does x's value actually change?
**Answer:** After a sequence point (like the semicolon `;`)

### Critical Definition (TANIM):
> "Using an object that has undergone a side effect before the side effect is guaranteed to occur is called **undefined behavior**."

### Examples of Undefined Behavior:
```c
x++ * x        // UNDEFINED! x is modified and used in same expression
int y = x + ++x; // UNDEFINED! x modified and used without sequence point
x = x++;       // UNDEFINED! x modified twice without sequence point
y = x + (x = 10); // UNDEFINED! x modified and used simultaneously
```

### The 4 Operators That Create Sequence Points:
1. `&&` (logical AND)
2. `||` (logical OR) 
3. `? :` (ternary operator)
4. `,` (comma operator)

**Plus:** The semicolon `;` also creates a sequence point


### Safe Examples:
```c
x++ || func(x)  // OK - sequence point after x++
x++ && func(x)  // OK - sequence point after x++
x++ , func(x)   // OK - sequence point after x++
```

### Control Structures and Sequence Points:
```c
int x = 10;
if(x++ > 9)     // if creates sequence point
    a = x;      // a = 11 (side effect has occurred)

int n = 5;
while(n-- > 0)  // while creates sequence point
    func(n);    // n has been decremented

for(int i = 0; i++ < 10; )  // for has sequence points
```

---

## 3. Maximum Munch Rule

When tokenizing, the compiler takes the longest meaningful token possible.

### Example from Your Notes:
```c
int x = 10, y = 5;
int z = x+++y;  // What does this become?
```

**Tokenization Process:**
- `x` ✓ (identifier)
- `+` ✓ (meaningful)
- `++` ✓ (more meaningful - increment operator)
- `+++` ✗ (not meaningful)
- So take `++`, continue with remaining `+`
- `+` ✓ (addition operator)
- `y` ✓ (identifier)

**Result:** `x++ + y` = `10 + 5` = `15`, and x becomes 11

---

## 4. Comma Operator (Virgül Operatörü)

### When Comma is NOT an Operator:
```c
int x, y, z;           // Separator/delimiter
func(x, y);            // Separator in function call
int a[] = {1,2,3,4,5}; // Separator in array initialization
```

### When Comma IS an Operator:
- Has the **lowest precedence** of all operators
- Creates a **sequence point** after the left operand
- Expression value is the **right operand's value**

```c
exp1 , exp2    // Value is exp2
a = b , b = c  // First assign b to a, then assign c to b
5, 7           // Value is 7
```

### Examples:
```c
x++, y = x, z = x + y;  // OK - sequence points after each comma

// Useful in for loops:
for(i = 0; ; i++, k += i)  // Multiple operations

// In if statements:
if(x = func(), x > 0)  // Call func(), assign to x, then check x > 0
```

### Important Notes:
```c
func(12, 4)      // Comma is separator
func((12, 4))    // Comma is operator - passes 4 to function

int x[5] = {1,2,3,4,5};        // Normal initialization
int x[5] = {(1,2,3,4,5)};      // First element gets 5, rest are 0

(x,y) = 10;      // SYNTAX ERROR - (x,y) is not an lvalue
```

---

### Example 1: Comma in if Statement
```c
double dval = 3.4;
if (dval > 2, 0)  // Comma operator!
    printf("Evet dogru\n");
else
    printf("Dogru degil\n");  // This prints!
```
**Explanation:** 
- `dval > 2` evaluates to `1` (true)
- Comma operator discards left operand
- Expression value becomes `0` (right operand)
- `if(0)` is false, so else block executes

### Example 2: Chained Assignment
```c
int x = 1, y = 1, z = 1;
x += y += z;
// Equivalent to: x = x + (y = y + z)
// Step by step:
// 1. y = y + z = 1 + 1 = 2
// 2. x = x + 2 = 1 + 2 = 3
// Result: x=3, y=2, z=1
```

### Example 3: Expression Evaluation
```c
x = 2, y, z;  // x = 2, then comma operator with y, then z
              // Final value is z, but assignments aren't made to y,z

x *= 3 + 2;   // x = x * (3 + 2) = 2 * 5 = 10

x *= y = z = 4;  // z=4, y=4, then x = x * 4 = 10 * 4 = 40

x = y == z;   // y==z is 1 (true), so x = 1

x == (y = z); // This doesn't assign to x! Just compares x with (y=z)
```

### Example 4: Arithmetic with Precedence
```c
x = -3 + 4 * 5 - 6;    // = -3 + 20 - 6 = 11
x = 3 + 4 % 5 - 6;     // = 3 + 4 - 6 = 1  (4%5=4)
x = -3 * 4 % -6 / 5;   // = -12 % -6 / 5 = 0 / 5 = 0
x = (7 + 6) % 5 / 2;   // = 13 % 5 / 2 = 3 / 2 = 1
```

### Example 5: Sequence Point in if
```c
int a = 0;
if (-1 < a-- < 0)  // Complex expression!
    printf("if girdi %d\n", --a);
else
    printf("else girdi %d\n", a);  // This executes, a = -1
```
**Step by step:**
1. `a--` creates side effect (a will become -1)
2. But current value (0) is used in comparison
3. `-1 < 0 < 0` becomes `-1 < 0` (true) becomes `1 < 0` (false)
4. if condition is false, but due to sequence point, a is now -1

### Example 6: Comma in if with Short-Circuit
```c
x = 1;
if (++x > 2, 5)  // ++x makes x=2, 2>2 is false, but comma makes condition 5 (true)
    printf("%d\n", ++x);  // Prints 3 (x was 2, now 3)
```

### Example 7: Complex Boolean Logic
```c
x = 0; y = 1;
printf("%d\n", !!x == !!y > x + 1);
// !!x = 0, !!y = 1, x+1 = 1
// !!y > x+1 = 1 > 1 = 0
// !!x == 0 = 0 == 0 = 1
// Prints: 1
```

### Example 8: Floating Point Comparison Issue
```c
double d = 0.;
d = d + 0.1 + 0.1 + 0.1 + 0.1;  // d = 0.4 (approximately)
if (d == 0.4)  // This might fail due to floating point precision!
    printf("d, 1. degerinde\n");
else
    printf("d, 1. degerinde degil\n");  // This likely prints
```

### Example 9: Short-Circuit Evaluation
```c
int x, y = 1, z = 1, t = 1;
x = (++y > 1) || ((z++ > 1) && (++t > 1));
// Step by step:
// 1. ++y makes y=2, so (++y > 1) = (2 > 1) = true
// 2. Since || left side is true, right side is NOT evaluated
// 3. z++ and ++t are never executed
// 4. z and t remain 1
// Result: x=1, y=2, z=1, t=1
```

---