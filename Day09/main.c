#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>  // For _getch() and _getche() (Windows only)
#include <Windows.h> // For Sleep() function
#include <time.h>   // For time() function

// ================================
// UTILITY FUNCTIONS
// ================================

/**
 * Clears the input buffer by consuming all characters until newline or EOF
 * Use this after scanf to prevent buffer-related issues
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        ; // Empty loop body - just consuming characters
    }
}

/**
 * Checks if a year is a leap year
 * Rules: Divisible by 4, but not by 100, unless also divisible by 400
 * @param y: Year to check
 * @return: 1 if leap year, 0 if not
 */
int isleap(int y) {
    return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
}

/**
 * Checks if a number is even
 * @param x: Number to check
 * @return: 1 if even, 0 if odd
 */
int iseven(int x) {
    return x % 2 == 0;
}

/**
 * Returns absolute value of a number (demonstrates redundant else)
 * @param x: Input number
 * @return: Absolute value of x
 */
int getabs(int x) {
    if (x >= 0)
        return x;
    return -x;  // No else needed - this only runs if x < 0
}

// ================================
// DEMONSTRATION FUNCTIONS
// ================================

/**
 * Demonstrates basic getchar() usage
 * Shows line-buffered input with echo
 */
void demo_getchar() {
    printf("\n=== GETCHAR DEMO ===\n");
    printf("Type some characters and press Enter: ");
    
    int c1 = getchar();
    int c2 = getchar();
    int c3 = getchar();
    
    printf("First char: %c (ASCII: %d)\n", c1, c1);
    printf("Second char: %c (ASCII: %d)\n", c2, c2);
    printf("Third char: %c (ASCII: %d)\n", c3, c3);
    
    clear_input_buffer(); // Clean remaining characters
}

/**
 * Demonstrates _getch() usage (Windows only)
 * Shows immediate input without echo
 */
void demo_getch() {
    printf("\n=== _GETCH DEMO ===\n");
    printf("Press any key (no echo, immediate response): ");
    
    int c = _getch();
    printf("\nYou pressed: %c (ASCII: %d)\n", c, c);
}

/**
 * Demonstrates _getche() usage (Windows only)
 * Shows immediate input with echo
 */
void demo_getche() {
    printf("\n=== _GETCHE DEMO ===\n");
    printf("Press any key (with echo, immediate response): ");
    
    int c = _getche();
    printf("\nYou pressed: %c (ASCII: %d)\n", c, c);
}

/**
 * Demonstrates the buffer sharing problem between scanf and getchar
 */
void demo_buffer_problem() {
    printf("\n=== BUFFER PROBLEM DEMO ===\n");
    
    int x, y;
    
    printf("Enter first number (try: 123abc): ");
    scanf("%d", &x);
    printf("Read: %d\n", x);
    
    printf("Enter second number: ");
    // Without clear_input_buffer(), this will try to read "abc"
    clear_input_buffer(); // Comment this line to see the problem
    scanf("%d", &y);
    printf("Read: %d\n", y);
}

/**
 * Manual integer reading using getchar
 * Demonstrates character-to-digit conversion
 */
int read_number_manually() {
    printf("\n=== MANUAL NUMBER READING ===\n");
    printf("Enter a number: ");
    
    int result = 0;
    int c;
    
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
            printf("Current result: %d\n", result);
        } else {
            printf("Ignoring non-digit: %c\n", c);
        }
    }
    
    return result;
}

/**
 * Checks if a large number is divisible by 3
 * Uses digit sum property: A number is divisible by 3 if sum of digits is divisible by 3
 */
void check_divisible_by_3() {
    printf("\n=== LARGE NUMBER DIVISIBILITY BY 3 ===\n");
    printf("Enter a very large number: ");
    
    int c;
    int sum = 0;
    
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            int digit = c - '0';
            sum += digit;
            printf("Digit: %d, Running sum: %d\n", digit, sum);
        }
    }
    
    if (sum % 3 == 0) {
        printf("The number IS divisible by 3!\n");
    } else {
        printf("The number is NOT divisible by 3.\n");
    }
    printf("Sum of digits: %d\n", sum);
}

/**
 * Demonstrates character test functions from ctype.h
 */
void demo_character_tests() {
    printf("\n=== CHARACTER TEST FUNCTIONS ===\n");
    printf("Enter a character: ");
    
    int ch = getchar();
    clear_input_buffer();
    
    printf("\nCharacter '%c' (ASCII %d) analysis:\n", ch, ch);
    
    if (isupper(ch)) printf("✓ Uppercase letter\n");
    if (islower(ch)) printf("✓ Lowercase letter\n");
    if (isalpha(ch)) printf("✓ Alphabetic character\n");
    if (isdigit(ch)) printf("✓ Digit\n");
    if (isalnum(ch)) printf("✓ Alphanumeric\n");
    if (isxdigit(ch)) printf("✓ Hexadecimal digit\n");
    if (ispunct(ch)) printf("✓ Punctuation\n");
    if (isspace(ch)) printf("✓ Whitespace\n");
    if (isblank(ch)) printf("✓ Blank (space/tab)\n");
    if (isprint(ch)) printf("✓ Printable\n");
    if (isgraph(ch)) printf("✓ Graphic (printable, not space)\n");
    if (iscntrl(ch)) printf("✓ Control character\n");
}

/**
 * Demonstrates else-if ladder vs multiple ifs
 */
void demo_grade_calculator() {
    printf("\n=== GRADE CALCULATOR (ELSE-IF DEMO) ===\n");
    
    int score;
    printf("Enter your score (0-100): ");
    scanf("%d", &score);
    clear_input_buffer();
    
    // Using else-if ladder (efficient)
    if (score >= 90) {
        printf("Grade: A (Excellent!)\n");
    } else if (score >= 80) {
        printf("Grade: B (Good!)\n");
    } else if (score >= 70) {
        printf("Grade: C (Average)\n");
    } else if (score >= 60) {
        printf("Grade: D (Below Average)\n");
    } else {
        printf("Grade: F (Fail)\n");
    }
}

/**
 * Demonstrates common if-else mistakes and corrections
 */
void demo_common_mistakes() {
    printf("\n=== COMMON IF-ELSE MISTAKES DEMO ===\n");
    
    int x = 5;
    
    printf("x = %d\n", x);
    
    // Mistake 1: Assignment vs Comparison
    printf("\n1. Assignment vs Comparison:\n");
    if (x == 5) {  // Correct: comparison
        printf("x equals 5 (correct comparison)\n");
    }
    
    // Mistake 2: Range checking
    printf("\n2. Range checking:\n");
    if (x > 3 && x < 10) {  // Correct: logical AND
        printf("x is between 3 and 10 (correct)\n");
    }
    
    // Mistake 3: Yoda condition (defensive programming)
    printf("\n3. Yoda condition:\n");
    if (5 == x) {  // Preferred: prevents accidental assignment
        printf("Using Yoda condition (5 == x)\n");
    }
    
    // Mistake 4: Always true condition
    printf("\n4. Logic error example:\n");
    // Wrong: if (x != 5 || x != 3) - always true!
    // Correct:
    if (x != 5 && x != 3) {
        printf("x is neither 5 nor 3\n");
    } else {
        printf("x is either 5 or 3\n");
    }
}

/**
 * Displays ASCII table for printable characters
 */
void display_ascii_table() {
    printf("\n=== ASCII TABLE (Printable Characters) ===\n");
    printf("Dec | Hex | Char\n");
    printf("----+-----+-----\n");
    
    for (int i = 33; i < 127; i++) {
        printf("%3d | %2X  |  %c\n", i, i, i);
        
        if ((i - 32) % 20 == 0) {
            printf("Press any key to continue...\n");
            _getch();
        }
    }
}

/**
 * Random character animation (just for fun!)
 */
void random_character_animation() {
    printf("\n=== RANDOM CHARACTER ANIMATION ===\n");
    printf("Press any key to stop...\n");
    
    while (!_kbhit()) {  // While no key is pressed
        // Clear screen (Windows specific)
        system("cls");
        
        // Generate random characters
        for (int i = 0; i < 50; i++) {
            putchar(rand() % 26 + 'A');  // Random uppercase letter
        }
        printf("\n");
        
        for (int i = 0; i < 50; i++) {
            putchar(rand() % 10 + '0');  // Random digit
        }
        printf("\n");
        
        Sleep(100);  // Wait 100ms
    }
    _getch();  // Consume the key press
}

/**
 * Leap year tester
 */
void test_leap_year() {
    printf("\n=== LEAP YEAR TESTER ===\n");
    
    int year;
    printf("Enter a year: ");
    scanf("%d", &year);
    clear_input_buffer();
    
    if (isleap(year)) {
        printf("%d is a leap year!\n", year);
        printf("February has 29 days.\n");
    } else {
        printf("%d is not a leap year.\n", year);
        printf("February has 28 days.\n");
    }
    
    // Test some well-known years
    printf("\nSome examples:\n");
    int test_years[] = {1900, 2000, 2004, 2023, 2024};
    int num_tests = sizeof(test_years) / sizeof(test_years[0]);
    
    for (int i = 0; i < num_tests; i++) {
        printf("%d: %s\n", test_years[i], 
               isleap(test_years[i]) ? "Leap year" : "Not leap year");
    }
}

/**
 * Interactive menu system
 */
void show_menu() {
    int choice;
    
    do {
        printf("\n");
        printf("1. getchar() Demo\n");
        printf("2. _getch() Demo\n");
        printf("3. _getche() Demo\n");
        printf("4. Buffer Problem Demo\n");
        printf("5. Manual Number Reading\n");
        printf("6. Large Number Divisibility\n");
        printf("7. Character Test Functions\n");
        printf("8. Grade Calculator\n");
        printf("9. Common Mistakes Demo\n");
        printf("10. ASCII Table\n");
        printf("11. Random Animation\n");
        printf("12. Leap Year Tester\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                demo_getchar();
                break;
            case 2:
                demo_getch();
                break;
            case 3:
                demo_getche();
                break;
            case 4:
                demo_buffer_problem();
                break;
            case 5: {
                int num = read_number_manually();
                printf("Final result: %d\n", num);
                break;
            }
            case 6:
                check_divisible_by_3();
                break;
            case 7:
                demo_character_tests();
                break;
            case 8:
                demo_grade_calculator();
                break;
            case 9:
                demo_common_mistakes();
                break;
            case 10:
                display_ascii_table();
                break;
            case 11:
                random_character_animation();
                break;
            case 12:
                test_leap_year();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        
        if (choice != 0) {
            printf("Press any key to continue...");
            _getch();
        }
        
    } while (choice != 0);
}

// ================================
// MAIN FUNCTION
// ================================

int main() {
    srand((unsigned int)time(NULL));
    
    show_menu();
    
    return 0;
}