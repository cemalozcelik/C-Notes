#include<stdio.h>
#include<math.h>    

// function declerations
void clear_buffer();
void buffered_input();
void increment_demonstration();
void precedence_demonstration();
void unary_operator_demonstration();


int main() {

    // buffered_input(); 

    // increment_demonstration(); 

    // precedence_demonstration(); 

    unary_operator_demonstration();
}

// Function to clear the input buffer
// This function reads characters from the input until it encounters a newline or EOF
// for the second scanf the input should be cleared because it get the buffered input
// This is useful to avoid issues with leftover input when reading new data
void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to demonstrate buffered input
void buffered_input()
{
    int x , y;
    char response;

    printf("Enter first number: (123abc) ");
    scanf("%d", &x);

    printf("Read character before clearing buffer:" ); 
    response = getchar(); // Read the next character, which may be leftover from previous input
    printf("The ASCII value of the character is: %d ('%c')", response, response);

    printf("\nNow Clear the buffer...\n");
    clear_buffer(); // if we do not clear the buffered input, the next scanf will not work properly
    printf("Enter second number: ");
    scanf("%d", &y);

    printf("Result - number 1: %d, number 2: %d\n", x, y);
    
    clear_buffer(); // This ensures that any leftover input is cleared before the next input operation
}


// Function to demonstrate incrementing a variable
void increment_demonstration() {
    
    int a = 10, b = 10;
    printf("Initial values: a = %d, b = %d\n", a, b);

    // post-increment
    printf("Post-increment: a++ = %d, b = %d\n", a++, b);
    printf("After post-increment: a = %d, b = %d\n", a, b);

    // pre-increment
    printf("Pre-increment: ++b = %d, a = %d\n", ++b, a);
    printf("After pre-increment: a = %d, b = %d\n", a, b);

    int x = 5;
    int y = 5;
    printf("Initial values: x = %d, y = %d\n", x, y);

    int result = x++ + ++y; // x is post-incremented, y is pre-incremented
    printf("Result of x++ + ++y: %d (x = %d, y = %d)\n", result, x, y);
    
    int result1 = x++ * 2;
    int result2 = ++y * 2;
    printf("Result of x++ * 2: %d (x = %d)\n", result1, x);
    printf("Result of ++y * 2: %d (y = %d)\n", result2, y);
    
}

void precedence_demonstration() {
    
    int a = 10, b = 5, c = 7, d = 3;
    printf("Initial values: a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);

    // Demonstrating operator precedence
    int result1 = a + b * c - d; // Multiplication has higher precedence
    printf("Result of a + b * c - d: %d\n", result1);
    
    int result2 = (a + b) * (c - d); // Parentheses change precedence
    printf("Result of (a + b) * (c - d): %d\n", result2); 

    int result3 = a + (b * c) - d; // Parentheses around multiplication
    printf("Result of a + (b * c) - d: %d\n", result3);
    
    int result4 = a + b * (c - d); // Parentheses around subtraction
    printf("Result of a + b * (c - d): %d\n", result4);

    // < > + - * / % operators
    int result5 = a > b + c - d; // Comparison operators return 1 (true) or 0 (false) 
    // Here, it checks if a is greater than the result of b + c - d
    printf("Result of a > b + c - d: %d\n", result5);

    int tricky = a + b > c;
    printf("Result of a + b > c: %d (a + b = %d, c = %d)\n", tricky, a + b, c);
    
    // modulus operator
    int result6 = a % b; // Modulus operator
    printf("Result of %d %% %d: %d\n", a, b, result6);

    // double fmodulus operator
    double da = 10.5, db = 3.2;
    double result7 = fmod(da, db); // Floating-point modulus
    printf("Result of fmod(%.2f, %.2f): %.2f\n", da, db, result7);

}

// Function to demonstrate unary operators
void unary_operator_demonstration() {
    int x = 5;
    printf("Initial value of x: %d\n", x);

    // Unary plus
    int unary_plus = +x;
    printf("Unary plus: +x = %d\n", unary_plus);

    // Unary minus
    int unary_minus = -x;
    printf("Unary minus: -x = %d\n", unary_minus);

    // Logical NOT
    int logical_not = !x; // Logical NOT operator
    printf("Logical NOT: !x = %d\n", logical_not);

    // Bitwise NOT
    int bitwise_not = ~x; // Bitwise NOT operator // Binary: 00000000 00000000 00000000 00000101
    printf("Bitwise NOT: ~x = %d\n", bitwise_not); // Binary: 11111111 11111111 11111111 11111010 (two's complement representation)
    printf("x in binary hex: %08X\n", x); // Display in hexadecimal format
    printf("Bitwise NOT in binary: %08X\n", bitwise_not); // Display in hexadecimal format

}

