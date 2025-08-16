#include <stdio.h>

#define PI 3.14159
#define SQUARE(x) ((x) * (x))

int main() {
    // Identifiers & Naming Rules
    int total = 10;
    float _score = 95.5;
    char name1 = 'A';

    int sum = 1, Sum = 2, SUM = 3;
    printf("sum = %d, Sum = %d, SUM = %d\n", sum, Sum, SUM);

    // Operators
    int x = 5;
    int y = 10;
    int result = x + y;
    printf("x + y = %d\n", result);

    x += 2;
    printf("x += 2 -> x = %d\n", x);

    printf("sizeof(int) = %lu bytes\n", sizeof(int));

    // Tokens example
    sum += 4;

    // Expressions
    int z = x + 5;
    int *ptr = &x;
    printf("z = %d, *ptr = %d\n", z, *ptr);

    // Constant expression
    int constant = 10 + 20 - 5;

    // Object and Type
    int object = 42;
    printf("object = %d\n", object);

    char letter = 'C';
    float number = 3.14;

    // Statements
    x++;
    y = x + 1;

    {
        int a = 1;
        int b = 2;
        printf("a + b = %d\n", a + b);
    }

    // Control Statements
    if (x > 5)
        printf("x is greater than 5\n");
    else
        printf("x is 5 or less\n");

    for (int i = 0; i < 3; i++)
        printf("for loop: i = %d\n", i);

    // Escape characters
    char newline = '\n';
    char tab = '\t';
    char quote = '\"';
    printf("Escape test:%cTab%cQuote%c\n", newline, tab, quote);

    // ASCII
    char ch = 'A';
    printf("Character: %c, ASCII: %d\n", ch, ch);

    // Type casting
    int a = 5, b = 2;
    float fresult = (float)a / b;
    printf("Result of a / b = %.2f\n", fresult);

    // sizeof
    printf("sizeof(char) = %lu\n", sizeof(char));
    printf("sizeof(short) = %lu\n", sizeof(short));
    printf("sizeof(int) = %lu\n", sizeof(int));
    printf("sizeof(long) = %lu\n", sizeof(long));
    printf("sizeof(float) = %lu\n", sizeof(float));
    printf("sizeof(double) = %lu\n", sizeof(double));

    // Const
    const int maxAge = 100;

    // Macros
    printf("PI = %f\n", PI);
    printf("SQUARE(5) = %d\n", SQUARE(5));

    return 0;
}
