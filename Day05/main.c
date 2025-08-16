#include <stdio.h>
#include <math.h>

int max3(int a, int b, int c);
void width_and_alignment(void);
void formated_output(void);
void nested_printf(void);
void printf_return_value_examples(void);
void scanf_different_number_systems(void);
void float_double_sensitivity(void);
void percent_character_printing(void);

int main(void){

    int ival = 255;
    printf("decimal: %d, octal: %o, hexadecimal: %x\n", ival, ival, ival); // foundation of number views
    printf("\n");
    
    width_and_alignment(); // width and alignment
    printf("\n");

    // formatted output 
    formated_output();
    printf("\n");


    // nested printf
    nested_printf();
    printf("\n");

    // printf return value examples
    printf_return_value_examples();
    printf("\n");

    // scanf with different number systems
    // scanf_different_number_systems();
    printf("\n");

    // float and double sensitivity
    float_double_sensitivity();
    printf("\n");

    // percent character printing
    percent_character_printing();
    printf("\n");
    return 0;
}

int max3(int a, int b, int c) {
    if (a >= b && a >= c) {
        return a;
    } else if (b >= a && b >= c) {
        return b;
    } else {
        return c;
    }
}

void width_and_alignment(void) {
    printf("Right-aligned numbers in 8-character width:\n");
    for (int i = 0; i < 5; i++) {
        printf("%8d test\n", i);
    }
    
    printf("\nLeft-aligned numbers in 8-character width:\n");
    for (int i = 0; i < 5; i++) {
        printf("%-8d test\n", i);
    }
    
    printf("\nZero-padded numbers:\n");
    for (int i = 1; i <= 5; i++) {
        printf("%05d\n", i);
    }
    
    printf("\nString width formatting:\n");
    char* names[] = {"Ali", "Mehmet", "A"};
    for (int i = 0; i < 3; i++) {
        printf("Right: '%10s' | Left: '%-10s'\n", names[i], names[i]);
    }
}

void formated_output(void) {
    printf("%-6s %-15s %-6s %-6s %-10s\n", "Index", "Name", "Age", "Score", "Status");
    printf("--------------------------------------------------------\n");
    char* names[5] = {"Ali", "Zeynep", "Cem", "Mehmet", "Can"};
    for (int i = 0; i < 5; i++) {
        int age = 20 + i;
        int score = 50 + i * 7;
        const char* status = (score >= 65) ? "Passed" : "Failed";
        printf("%-6d %-15s %-6d %-6d %-10s\n", i, names[i], age, score, status);
    }
}




void nested_printf(void) {
    int x = 548;
    printf("%d\n", printf("%d", printf("%d", x)));
    // The inner printf calls will print the value of x and return the number of characters printed. so 987 returns 3,
    // then the next printf will print 3 and return 1, and finally the outer printf will print 1 and return 1.
    // The output will be: 54831
}

void printf_return_value_examples(void) {
    printf("Printf returns the number of characters printed:\n");
    
    int chars_printed = printf("Hello World");
    printf(" <- This printed %d characters\n", chars_printed);
    
    chars_printed = printf("%d", 12345);
    printf(" <- This printed %d characters\n", chars_printed);
    
    chars_printed = printf("%.2f", 3.14159);
    printf(" <- This printed %d characters\n", chars_printed);
}

void scanf_different_number_systems(void) {
    int decimal, octal, hexadecimal;
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);
    printf("Enter an octal number (0-7 only): ");
    scanf("%o", &octal);
    printf("Enter a hexadecimal number: ");
    scanf("%x", &hexadecimal);
    
    printf("Decimal: %d, Octal: %o, Hexadecimal: %x\n", decimal, octal, hexadecimal);

    int retval = scanf("%d %o %x", &decimal, &octal, &hexadecimal);
    if (retval != 3) {
        printf("One or more inputs were invalid. Only %d value(s) were read.\n", retval);
    }
    else {
        printf("All inputs were read successfully.\n");
    }

    printf("Return value: %d\n", retval);
    // if do wrong input, scanf will return the number of successfully read values and buffer will not be cleared.
    // Enter a decimal number: 123 123 45a
    // Enter an octal number (0-7 only): Enter a hexadecimal number: Decimal: 123, Octal: 123, Hexadecimal: 45a
}

void float_double_sensitivity(void) {
    printf("=== Float vs Double Precision ===\n");
    float f = 1.0f / 3.0f;
    double d = 1.0 / 3.0;
    
    printf("Float (1/3):  %.10f\n", f);
    printf("Double (1/3): %.10lf\n", d);
    
    if (f == d) {
        printf("Float and Double are equal.\n");
    } else {
        printf("Float and Double are NOT equal.\n");
    }
    
    printf("\n=== Binary Representation Issues ===\n");
    printf("Numbers that can be represented exactly:\n");
    double exact1 = 0.75; // 1/2 + 1/4
    double exact2 = 0.25; // 1/4
    double exact3 = 0.125; // 1/8
    printf("0.75 = %.17f (exact)\n", exact1);
    printf("0.25 = %.17f (exact)\n", exact2);
    printf("0.125 = %.17f (exact)\n", exact3);
    
    printf("\nNumbers that CANNOT be represented exactly:\n");
    double inexact1 = 0.1;
    double inexact2 = 0.2;
    double inexact3 = 0.3;
    printf("0.1 = %.17f (not exact)\n", inexact1);
    printf("0.2 = %.17f (not exact)\n", inexact2);
    printf("0.3 = %.17f (not exact)\n", inexact3);
    
    printf("\n=== Floating Point Comparison Problem ===\n");
    double sum = 0.1 + 0.2;
    printf("0.1 + 0.2 = %.17f\n", sum);
    printf("0.3       = %.17f\n", 0.3);
    
    if (sum == 0.3) {
        printf("Equal (unexpected!)\n");
    } else {
        printf("NOT Equal (as expected)\n");
    }
    
    printf("\nCorrect way to compare floats:\n");
    double epsilon = 1e-9;
    if (fabs(sum - 0.3) < epsilon) {
        printf("Equal within tolerance (correct approach)\n");
    } else {
        printf("Not equal even with tolerance\n");
    }
}

void percent_character_printing(void) {
    double kdv = 18.0;
    printf("\nTo print percent character, use %%:\n");
    printf("KDV: %%.2f%%%%\n"); // Shows the format
    printf("KDV: %.2f%%\n", kdv); // Actual usage
    
    printf("\nMore examples:\n");
    printf("Discount: 25%%\n");
    printf("Success rate: %.1f%%\n", 87.590); // Prints 87.6
}

/*
decimal: 255, octal: 377, hexadecimal: ff

Right-aligned numbers in 8-character width:
       0 test
       1 test
       2 test
       3 test
       4 test

Left-aligned numbers in 8-character width:
0        test
1        test
2        test
3        test
4        test

Zero-padded numbers:
00001
00002
00003
00004
00005

String width formatting:
Right: '       Ali' | Left: 'Ali       '
Right: '    Mehmet' | Left: 'Mehmet    '
Right: '         A' | Left: 'A         '

Index  Name            Age    Score  Status
--------------------------------------------------------
0      Ali             20     50     Failed
1      Zeynep          21     57     Failed
2      Cem             22     64     Failed
3      Mehmet          23     71     Passed
4      Can             24     78     Passed

54831

Printf returns the number of characters printed:
Hello World <- This printed 11 characters
12345 <- This printed 5 characters
3.14 <- This printed 4 characters


=== Float vs Double Precision ===
Float (1/3):  0.3333333433
Double (1/3): 0.3333333333
Float and Double are NOT equal.

=== Binary Representation Issues ===
Numbers that can be represented exactly:
0.75 = 0.75000000000000000 (exact)
0.25 = 0.25000000000000000 (exact)
0.125 = 0.12500000000000000 (exact)

Numbers that CANNOT be represented exactly:
0.1 = 0.10000000000000001 (not exact)
0.2 = 0.20000000000000001 (not exact)
0.3 = 0.29999999999999999 (not exact)

=== Floating Point Comparison Problem ===
0.1 + 0.2 = 0.30000000000000004
0.3       = 0.29999999999999999
NOT Equal (as expected)

Correct way to compare floats:
Equal within tolerance (correct approach)


To print percent character, use %:
KDV: %.2f%%
KDV: 18.00%

More examples:
Discount: 25%
Success rate: 87.6%
*/