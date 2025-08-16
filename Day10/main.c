#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Function prototypes
int sum_digit(int val);
int ndigit_count(int val);
int is_armstrong(int num);
void find_armstrong_numbers(int start, int end);
void demonstrate_ctype_functions(void);
void demonstrate_ternary_operator(void);
void demonstrate_character_conversion(void);
void demonstrate_digit_algorithms(void);
void clear_input_buffer(void);
int safe_getchar(void);
void print_separator(const char* title);

// Utility functions for digit operations
int get_nth_digit(int number, int position);
int reverse_number(int num);
int is_palindrome(int num);

int main() {
    int choice;
    
    printf("=== C Programming Day 10 - Interactive Demo ===\n\n");
    
    do {
        printf("\nSelect a demonstration:\n");
        printf("1. Character Testing Functions (ctype.h)\n");
        printf("2. Character Conversion Functions\n");
        printf("3. Ternary Operator Examples\n");
        printf("4. Digit Processing Algorithms\n");
        printf("5. Armstrong Numbers\n");
        printf("6. Interactive Character Analysis\n");
        printf("7. Number Properties Calculator\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch(choice) {
            case 1:
                demonstrate_ctype_functions();
                break;
            case 2:
                demonstrate_character_conversion();
                break;
            case 3:
                demonstrate_ternary_operator();
                break;
            case 4:
                demonstrate_digit_algorithms();
                break;
            case 5:
                find_armstrong_numbers(1, 100000);
                break;
            case 6:
                {
                    print_separator("Interactive Character Analysis");
                    printf("Enter a character: ");
                    int ch = safe_getchar();
                    if (ch != -1) {
                        printf("\nAnalysis of character '%c' (ASCII: %d):\n", ch, ch);
                        printf("islower: %s\n", islower(ch) ? "YES" : "NO");
                        printf("isupper: %s\n", isupper(ch) ? "YES" : "NO");
                        printf("isdigit: %s\n", isdigit(ch) ? "YES" : "NO");
                        printf("isalpha: %s\n", isalpha(ch) ? "YES" : "NO");
                        printf("isalnum: %s\n", isalnum(ch) ? "YES" : "NO");
                        printf("isxdigit: %s\n", isxdigit(ch) ? "YES" : "NO");
                        printf("ispunct: %s\n", ispunct(ch) ? "YES" : "NO");
                        printf("isspace: %s\n", isspace(ch) ? "YES" : "NO");
                        printf("isprint: %s\n", isprint(ch) ? "YES" : "NO");
                        printf("iscntrl: %s\n", iscntrl(ch) ? "YES" : "NO");
                        printf("toupper: '%c'\n", toupper(ch));
                        printf("tolower: '%c'\n", tolower(ch));
                    }
                }
                break;
            case 7:
                {
                    print_separator("Number Properties Calculator");
                    int num;
                    printf("Enter a number: ");
                    scanf("%d", &num);
                    
                    printf("\nProperties of %d:\n", num);
                    printf("Digit sum: %d\n", sum_digit(abs(num)));
                    printf("Number of digits: %d\n", ndigit_count(abs(num)));
                    printf("Is Armstrong: %s\n", is_armstrong(abs(num)) ? "YES" : "NO");
                    printf("Is Palindrome: %s\n", is_palindrome(abs(num)) ? "YES" : "NO");
                    printf("Reversed: %d\n", reverse_number(abs(num)));
                    
                    // Extract individual digits
                    int temp = abs(num);
                    int digits = ndigit_count(temp);
                    printf("Individual digits: ");
                    for (int i = digits - 1; i >= 0; i--) {
                        printf("%d ", get_nth_digit(temp, i));
                    }
                    printf("\n");
                }
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}

// Utility function to print separator
void print_separator(const char* title) {
    printf("\n");
    for (int i = 0; i < 50; i++) printf("=");
    printf("\n%s\n", title);
    for (int i = 0; i < 50; i++) printf("=");
    printf("\n");
}

// Clear input buffer
void clear_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        // Clear the buffer
    }
}

// Safe character input
int safe_getchar(void) {
    int ch = getchar();
    if (ch == EOF) {
        printf("Error: Could not read input!\n");
        return -1;
    }
    return ch;
}

// Calculate sum of digits
int sum_digit(int val) {
    int sum = 0;
    while (val != 0) {
        sum += val % 10;
        val /= 10;
    }
    return sum;
}

// Count number of digits
int ndigit_count(int val) {
    int digit_count = 0;
    
    if (val == 0) {
        return 1;
    }
    
    if (val < 0) {
        val = -val;
    }
    
    while (val) {
        ++digit_count;
        val /= 10;
    }
    
    return digit_count;
}

// Get nth digit from right (0-indexed)
int get_nth_digit(int number, int position) {
    return (number / (int)pow(10, position)) % 10;
}

// Reverse a number
int reverse_number(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

// Check if number is palindrome
int is_palindrome(int num) {
    return num == reverse_number(num);
}

// Check if number is Armstrong number
int is_armstrong(int num) {
    int original = num;
    int digit_count = ndigit_count(num);
    int sum = 0;
    
    while (num > 0) {
        int digit = num % 10;
        sum += (int)pow(digit, digit_count);
        num /= 10;
    }
    
    return sum == original;
}

// Find Armstrong numbers in range
void find_armstrong_numbers(int start, int end) {
    print_separator("Armstrong Numbers");
    printf("Armstrong numbers between %d and %d:\n", start, end);
    
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (is_armstrong(i)) {
            printf("%d ", i);
            count++;
            if (count % 10 == 0) printf("\n"); // New line every 10 numbers
        }
    }
    
    if (count % 10 != 0) printf("\n");
    printf("Total found: %d\n", count);
}

// Demonstrate character testing functions
void demonstrate_ctype_functions(void) {
    print_separator("Character Testing Functions Demo");
    
    printf("Testing various characters:\n\n");
    
    char test_chars[] = {'a', 'Z', '5', '@', ' ', '\t', '\n', 'F'};
    int num_chars = sizeof(test_chars) / sizeof(test_chars[0]);
    
    printf("Char | Lower | Upper | Digit | Alpha | Alnum | Punct | Space | Print\n");
    printf("-----|-------|-------|-------|-------|-------|-------|-------|------\n");
    
    for (int i = 0; i < num_chars; i++) {
        char c = test_chars[i];
        char display_char = (c == '\n') ? 'N' : (c == '\t') ? 'T' : c;
        
        printf("  %c  |   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |   %d\n",
               display_char,
               islower(c) ? 1 : 0,
               isupper(c) ? 1 : 0,
               isdigit(c) ? 1 : 0,
               isalpha(c) ? 1 : 0,
               isalnum(c) ? 1 : 0,
               ispunct(c) ? 1 : 0,
               isspace(c) ? 1 : 0,
               isprint(c) ? 1 : 0);
    }
    
    printf("\nAll punctuation characters in ASCII:\n");
    for (int i = 0; i <= 127; i++) {
        if (ispunct(i)) {
            printf("%c", i);
        }
    }
    printf("\n");
    
    printf("\nAll hexadecimal digits:\n");
    for (int i = 0; i <= 127; i++) {
        if (isxdigit(i)) {
            printf("%c", i);
        }
    }
    printf("\n");
}

// Demonstrate character conversion
void demonstrate_character_conversion(void) {
    print_separator("Character Conversion Demo");
    
    printf("Case conversion examples:\n");
    
    char test_string[] = "Hello World! 123";
    printf("Original: %s\n", test_string);
    
    printf("To upper: ");
    for (int i = 0; test_string[i]; i++) {
        printf("%c", toupper(test_string[i]));
    }
    printf("\n");
    
    printf("To lower: ");
    for (int i = 0; test_string[i]; i++) {
        printf("%c", tolower(test_string[i]));
    }
    printf("\n");
    
    // Case-insensitive comparison demo
    printf("\nCase-insensitive comparison:\n");
    char c1 = 'A', c2 = 'a';
    printf("'%c' and '%c' are %s (case-insensitive)\n", 
           c1, c2, 
           (toupper(c1) == toupper(c2)) ? "SAME" : "DIFFERENT");
    
    // Manual implementation demo
    printf("\nManual case conversion (ASCII arithmetic):\n");
    char upper_char = 'M';
    char lower_equivalent = (upper_char >= 'A' && upper_char <= 'Z') ? 
                           upper_char - 'A' + 'a' : upper_char;
    printf("'%c' manually converted to lowercase: '%c'\n", upper_char, lower_equivalent);
}

// Demonstrate ternary operator
void demonstrate_ternary_operator(void) {
    print_separator("Ternary Operator Demo");
    
    // Basic examples
    int a = 15, b = 23;
    printf("Basic maximum finding:\n");
    printf("a = %d, b = %d\n", a, b);
    printf("Maximum using ternary: %d\n", a > b ? a : b);
    printf("Minimum using ternary: %d\n", a < b ? a : b);
    
    // Absolute value
    int x = -42;
    printf("\nAbsolute value:\n");
    printf("x = %d\n", x);
    printf("Absolute value: %d\n", x >= 0 ? x : -x);
    
    // Sign determination
    printf("Sign: %s\n", x > 0 ? "POSITIVE" : (x < 0 ? "NEGATIVE" : "ZERO"));
    
    // Grade assignment
    int score = 87;
    printf("\nGrade assignment:\n");
    printf("Score: %d\n", score);
    char grade = score >= 90 ? 'A' :
                 score >= 80 ? 'B' :
                 score >= 70 ? 'C' :
                 score >= 60 ? 'D' : 'F';
    printf("Grade: %c\n", grade);
    
    // String selection
    printf("\nString selection:\n");
    int temperature = 25;
    printf("Temperature: %dC\n", temperature);
    printf("Weather: %s\n", temperature > 30 ? "Hot" : 
                           temperature > 20 ? "Warm" : 
                           temperature > 10 ? "Cool" : "Cold");
    
    // Array index safety
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int index = 7;
    printf("\nSafe array access:\n");
    printf("Array size: %d, Requested index: %d\n", size, index);
    int safe_index = (index >= 0 && index < size) ? index : 0;
    printf("Safe index used: %d, Value: %d\n", safe_index, arr[safe_index]);
}

// Demonstrate digit algorithms
void demonstrate_digit_algorithms(void) {
    print_separator("Digit Processing Algorithms Demo");
    
    int test_numbers[] = {4235, 987678, 0, 123, 9876543};
    int num_count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    printf("Number | Digit Sum | Digit Count | Reversed | Palindrome?\n");
    printf("-------|-----------|-------------|----------|------------\n");
    
    for (int i = 0; i < num_count; i++) {
        int num = test_numbers[i];
        printf("%7d|%10d|%12d|%9d|%11s\n",
               num,
               sum_digit(num),
               ndigit_count(num),
               reverse_number(num),
               is_palindrome(num) ? "YES" : "NO");
    }
    
    // Digit extraction demo
    printf("\nDigit extraction for 56789:\n");
    int demo_num = 56789;
    int digits = ndigit_count(demo_num);
    
    for (int i = digits - 1; i >= 0; i--) {
        printf("Position %d (from right): %d\n", i, get_nth_digit(demo_num, i));
    }
    
    // Alternative extraction method
    printf("\nAlternative extraction (left to right):\n");
    int temp = demo_num;
    printf("Original: %d\n", temp);
    while (temp > 0) {
        int digit = temp % 10;
        printf("Last digit: %d, Remaining: %d\n", digit, temp / 10);
        temp /= 10;
    }
}
