#include <stdio.h>

// Function declaration
int get_mid(a,b,c); // implicit int declaration
void logic_demonstration();
void short_circuit_demonstration();
void demorgan_law_demonstration(int a, int b);
void comparison_demonstration(int a, int b);
void bitwise_operations();
void normalize_time(int *day, int *hour, int *min, int *sec);

// Main function
int main() {
    int x = 5, y = 10, z = 7;
    int mid = get_mid(x, y, z);
    printf("The middle value among %d, %d, and %d is: %d\n", x, y, z, mid);

    logic_demonstration();

    short_circuit_demonstration();

    int p = 0, q = 0;
    printf("Demonstrating De Morgan's laws with p = %d and q = %d:\n", p, q);
    demorgan_law_demonstration(p, q);

    p = 1, q = 0;
    printf("Demonstrating De Morgan's laws with p = %d and q = %d:\n", p, q);
    demorgan_law_demonstration(p, q);

    p = 0, q = 1;
    printf("Demonstrating De Morgan's laws with p = %d and q = %d:\n", p, q);
    demorgan_law_demonstration(p, q);

    p = 1, q = 1;
    printf("Demonstrating De Morgan's laws with p = %d and q = %d:\n", p, q);
    demorgan_law_demonstration(p, q);

    // usage

    int age = 20;
    int salary = 5000;
    if( age < 18 || salary < 3000) {
        printf("You are not eligible for the loan.\n");
    } else {
        printf("You are eligible for the loan.\n");
    }

    // Demorgan's laws in practice
    if (!(age >= 18 && salary >= 3000)) {
        printf("You are not eligible for the loan (using De Morgan's law).\n");
    } else {
        printf("You are eligible for the loan (using De Morgan's law).\n");
    }

    // Comparison demonstration
    int a = 10, b = -20;
    printf("Comparing %d and %d:\n", a, b);
    comparison_demonstration(a, b);

    // find max with just less than operator
    x = 5, y = 10, z = 7;

    int max_xy = !(x < y) ? x : y;
    int max_xyz = !(max_xy < z) ? max_xy : z;
    printf("The maximum value among %d, %d, and %d is: %d\n", x, y, z, max_xyz);

    // assignment operators
    int x1 = 10;
    printf("x1 = %d\n", x1);
    printf("(x1 = 5) returns: %d\n", x1 = 5);
    printf("x1 after assignment: %d\n", x1);

    // multiple assignment
    int a1, b1, c1, d1, e1;
    a1 = b1 = c1 = d1 = e1 = 42;
    printf("a1 = b1 = c1 = d1 = e1 = 42 →\n");
    printf("a1=%d, b1=%d, c1=%d, d1=%d, e1=%d\n", a1, b1, c1, d1, e1);

    // multiple assignment with expressions
    int f1, g1, h1;
    f1 = (g1 = 5) + (h1 = 10);
    printf("f1 = (g1 = 5) + (h1 = 10) →\n");
    printf("f1=%d, g1=%d, h1=%d\n", f1, g1, h1);

    // assignment with arithmetic operations
    int i = 10;
    i += 5; // equivalent to i = i + 5
    printf("i after += 5: %d\n", i);
    i -= 3; // equivalent to i = i - 3
    printf("i after -= 3: %d\n", i);
    i *= 2; // equivalent to i = i * 2
    printf("i after *= 2: %d\n", i);
    i /= 4; // equivalent to i = i / 4
    printf("i after /= 4: %d\n", i);

    // type conversion with assignment
    double j = 3.14;
    int z1 = j; // implicit conversion from double to int
    printf("j = 3.14, z1 = j \n");
    printf("z1 = %d\n", z1);

    bitwise_operations();
    
    printf("Demonstrating time normalization:\n");
    printf("Enter time in days, hours, minutes, and seconds:\n");
    int day, hour, min, sec;
    scanf("%d %d %d %d", &day, &hour, &min, &sec);
    normalize_time(&day, &hour, &min, &sec);
    

    return 0;
}

// there is reverse logic
int get_mid(x,y,z) {
    if (!(x > y && x > z || x<y && x<z)) // x is not the largest and not the smallest
        return x; // x is the middle value
    else if (!(y > x && y > z || y < x && y < z)) // y is not the largest and not the smallest
        return y; // y is the middle value
    else // z is the only remaining option
        return z; // z is the middle value
}

// Function to demonstrate logical operations
void logic_demonstration() 
{
    printf("NOT operation on 1: %d\n", !1); // Logical NOT
    printf("NOT operation on 0: %d\n", !0); // Logical NOT

    int test_vals[] = {0,1,-1,50,100,-60};
    for(int i=0; i<6; i++) {
        printf("!(%d) = %d, !!(%d) = %d\n", 
               test_vals[i], !test_vals[i], 
               test_vals[i], !!test_vals[i]);
    }

    // && operator
    int a = 5, b = 10, c = 15;
    // initial values
    printf("Initial values: a = %d, b = %d, c = %d\n", a, b, c);
    // a && b a &&c  c && b
    printf("a && b: %d\n", a && b);
    printf("a && c: %d\n", a && c);
    printf("c && b: %d\n", c && b);

    // || operator
    printf("a || b: %d\n", a || b);
    printf("a || c: %d\n", a || c);
    printf("c || c: %d\n", c || c);

    // && and || together
    printf("a && b || c: %d\n", a && b || c);
    printf("a || b && c: %d\n", a || b && c);
    printf("a && b || c && a: %d\n", a && b || c && a);

    
    // decrement and increment operators with logical operator
    int p = 5;
    if (p && (p++)) {
        printf("p is changed in &&: %d\n", p);
    }

    printf("p after if: %d\n", p);

    if (p || ++p) // second operand is evaluated only if the first is false
    {
        // p is incremented only if the first operand is false
        // since p is not zero, it will not increment !!!!important
        printf("p is not changed in ||: %d\n", p);
    }
    printf("p after if with ++: %d\n", p);
}

void short_circuit_demonstration() 
{
    
    // short-circuit evaluation with logical AND (&&)
    int x = 0, y = 10;
    printf("Initial values: x = %d, y = %d\n", x, y);
    int result1 = x && ++y; // y is evaluated only if x is true (non-zero)
    printf("Result of x && ++y: %d (y = %d)\n", result1, y); // y is not incremented because x is false

    // short-circuit evaluation with logical OR (||)
    int result2 = x || ++y; // y is evaluated only if x is false
    printf("Result of x || ++y: %d (y = %d)\n", result2, y); // y is incremented because x is false
    printf("Final value of y: %d\n", y); // y is now incremented to 11

    // pratically, short-circuit evaluation can be used to avoid unnecessary computations
    int *ptr = NULL;
    int value = 42; // otostopun galaxi rehberi

    // wrong way SEGMENTATION FAULT
    // if (*ptr > 0 && ptr != NULL)  we should check if ptr is NULL before dereferencing it 
    // {
    //     *ptr = value; // This will cause a segmentation fault if ptr is NULL
    // } else {
    //     printf("Pointer is NULL, skipping assignment.\n");
    // }

    if (ptr != NULL && *ptr > 0) {
        *ptr = value; // or ptr = &value; // This will not cause a segmentation faults
    } else {
        printf("Pointer is NULL, skipping assignment.\n");
    }

}

#include <stdio.h>

void demorgan_law_demonstration(int p, int q)
{
    // De Morgan's Laws Demonstration
    printf("De Morgan's laws demonstration for p = %d, q = %d:\n", p, q);

    // First De Morgan Law: !(A && B) == !A || !B
    int result1 = !(p && q);
    int result2 = (!p || !q);
    printf("  !(p && q) = %d,   (!p || !q) = %d\n", result1, result2);

    // Second De Morgan Law: !(A || B) == !A && !B
    result1 = !(p || q);
    result2 = (!p && !q);
    printf("  !(p || q) = %d,   (!p && !q) = %d\n", result1, result2);

    printf("\n");
}

void comparison_demonstration(int a, int b) {

    // Standard comparison operators
    printf("  a == b: %d\n", a == b); // Equal to
    printf("  a != b: %d\n", a != b); // Not equal to
    printf("  a < b: %d\n", a < b);   // Less than
    printf("  a > b: %d\n", a > b);   // Greater   
    printf("  a <= b: %d\n", a <= b); // Less than or equal to
    printf("  a >= b: %d\n", a >= b); // Greater than

    printf("a == b = !(a < b) && !(b < a) = %d\n", !(a < b) && !(b < a));

    printf("a != b = (a < b) || (b < a) = %d\n", (a < b) || (b < a));

}

void bitwise_operations() {
    // Bitwise operations demonstration
    int x1 = 12, x2 = 5;
    
    // Bitwise AND
    printf("Bitwise AND: %d & %d = %d\n", x1, x2, x1 & x2);
    
    // Bitwise OR
    printf("Bitwise OR: %d | %d = %d\n", x1, x2, x1 | x2);
    
    // Bitwise XOR
    printf("Bitwise XOR: %d ^ %d = %d\n", x1, x2, x1 ^ x2);
    
    // Bitwise NOT
    printf("Bitwise NOT: ~%d = %d\n", x1, ~x1);
    
    // Left shift
    printf("Left shift: %d << 1 = %d\n", x1, x1 << 1);
    
    // Right shift
    printf("Right shift: %d >> 1 = %d\n", x1, x1 >> 1);
}

void normalize_time(int *day, int *hour, int *min, int *sec) {
    // Normalize time values
    if (*sec >= 60) {
        *min += *sec / 60;
        *sec %= 60;
    }
    if (*min >= 60) {
        *hour += *min / 60;
        *min %= 60;
    }
    if (*hour >= 24) {
        *day += *hour / 24;
        *hour %= 24;
    }
    
    printf("Normalized time: %d days %d hours %d minutes %d seconds\n", 
           *day, *hour, *min, *sec);
}