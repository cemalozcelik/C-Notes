# C Programming Day 5 Notes

## Number Systems & Basic Printf

Started with showing same number in different formats:
```c
int ival = 255;
printf("decimal: %d, octal: %o, hexadecimal: %x\n", ival, ival, ival);
// Output: decimal: 255, octal: 377, hexadecimal: ff
```

Basic stuff but good to remember:
- %d = decimal (normal numbers)
- %o = octal (base 8, uses 0-7)
- %x = hexadecimal (base 16, uses 0-9 and a-f)

## Width and Alignment

This is actually pretty useful for making things look neat:

```c
printf("%8d test\n", i);    // Right aligned, 8 chars wide
printf("%-8d test\n", i);   // Left aligned, 8 chars wide  
printf("%05d\n", i);        // Zero padded
```

The output shows the difference clearly:
```
Right-aligned:
       0 test
       1 test
       
Left-aligned:
0        test
1        test

Zero-padded:
00001
00002
```

Works with strings too:
```c
printf("'%10s'", name);    // Right: '       Ali'
printf("'%-10s'", name);   // Left:  'Ali       '
```

## Formatted Tables

Made a nice looking table using width formatting:
```c
printf("%-6s %-15s %-6s %-6s %-10s\n", "Index", "Name", "Age", "Score", "Status");
printf("--------------------------------------------------------\n");
```

Key things:
- Use consistent widths for columns
- Left align text with -
- Add separator lines for clarity

## Printf Return Values

TIL printf returns how many characters it printed:
```c
int count = printf("Hello World");  // count = 11
int count2 = printf("%d", 12345);   // count2 = 5
```

Could be useful for... formatting? Not sure when I'd use this but good to know.

## Nested Printf

```c
int x = 548;
printf("%d\n", printf("%d", printf("%d", x)));
// Output: 54831
```

Printf returns how many characters it printed. So:
1. `printf("%d", 548)` → prints "548", returns 3
2. `printf("%d", 3)` → prints "3", returns 1  
3. `printf("%d\n", 1)` → prints "1"

Result: 548 + 3 + 1 = "54831"

## Scanf with Different Number Systems

```c
scanf("%d", &num);  // Reads as decimal
scanf("%o", &num);  // Reads as octal  
scanf("%x", &num);  // Reads as hexadecimal
```

If you input "FF" with %x, it reads as 255.
If you input "77" with %o, it reads as 63 (7*8 + 7).

The return value of scanf is important - tells you how many values it successfully read.

Buffer problems: if you input "123ABC" to %d, it reads 123 and leaves "ABC" in the buffer. Next scanf will try to read "ABC" and probably fail.

## Float vs Double Precision

This is where things get weird with floating point numbers.

Float vs Double for 1/3:
```
Float (1/3):  0.3333333433
Double (1/3): 0.3333333333
```

Some numbers can be represented exactly in binary:
- 0.75 = 1/2 + 1/4 exact
- 0.25 = 1/4 exact  
- 0.125 = 1/8 exact

But others can't:
- 0.1 = 0.10000000000000001  not exact
- 0.2 = 0.20000000000000001  not exact

This causes the classic problem:
```c
double sum = 0.1 + 0.2;  // 0.30000000000000004
if (sum == 0.3) // FALSE!
```

Solution: use tolerance when comparing floats:
```c
double epsilon = 1e-9;
if (fabs(sum - 0.3) < epsilon) // TRUE
```

## Percent Character

To print % you need %%:
```c
printf("KDV: %.2f%%\n", 18.0);  // Output: KDV: 18.00%
```
