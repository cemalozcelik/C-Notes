/*
 * C Programming Day 19 - Strings and Character Arrays Practice
 * Binary search, string operations, character manipulation
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 1000

// Utility Functions
void wait_for_enter(void) {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
    getchar();
}

void randomize(void) {
    srand((unsigned)time(0));
}

void print_array(const int* p, int size) {
    for (int i = 0; i < size; i++) {
        if (i && i % 20 == 0)
            printf("\n");
        printf("%3d ", p[i]);
    }
    printf("\n------------------------------------------------------------\n");
}

void set_random_array(int* p, int size) {
    for (int i = 0; i < size; i++) {
        p[i] = rand() % 1000;
    }
}

// Comparison function for qsort
static int icmp(const void* vp1, const void* vp2) {
    return *(const int*)vp1 - *(const int*)vp2;
}

// Custom string input function
void sgets(char* str) {
    int c;
    int idx = 0;
    
    while ((c = getchar()) != '\n' && idx < SIZE - 1)
        str[idx++] = c;
    
    str[idx] = '\0';
}

// Binary search function
int binary_search(int* a, int size, int sval) {
    int idx_first = 0;
    int idx_last = size - 1;
    int idx_mid;
    int cnt = 0;
    
    while (idx_first <= idx_last) {
        cnt++;
        idx_mid = (idx_first + idx_last) / 2;
        
        if (a[idx_mid] == sval) {
            printf("Found after %d comparisons\n", cnt);
            return idx_mid;
        }
        
        if (a[idx_mid] > sval)
            idx_last = idx_mid - 1;
        else
            idx_first = idx_mid + 1;
    }
    
    printf("Not found after %d comparisons\n", cnt);
    return -1;
}

int main() {
    
    // ========================================
    // 1. BINARY SEARCH
    // ========================================
    printf("=== 1. BINARY SEARCH ===\n");
    
    int a[100];
    randomize();
    set_random_array(a, 100);
    qsort(a, 100, sizeof(int), icmp);
    
    printf("Sorted array:\n");
    print_array(a, 100);
    
    int sval;
    printf("Enter value to search: ");
    scanf("%d", &sval);
    getchar(); // Consume newline
    
    int result = binary_search(a, 100, sval);
    
    if (result != -1)
        printf("Value %d found at index %d\n", sval, result);
    else
        printf("Value %d not found\n", sval);
    
    wait_for_enter();
    
    // ========================================
    // 2. CHARACTER CODES DEMONSTRATION
    // ========================================
    printf("\n=== 2. CHARACTER CODES ===\n");
    
    char c1 = 65;
    char c2 = 'A';
    char c3 = '0';
    char c4 = '\0';
    
    printf("char c1 = 65      -> '%c' (code: %d)\n", c1, c1);
    printf("char c2 = 'A'     -> '%c' (code: %d)\n", c2, c2);
    printf("char c3 = '0'     -> '%c' (code: %d)\n", c3, c3);
    printf("char c4 = '\\0'    -> (null terminator, code: %d)\n", c4);
    
    printf("\nImportant distinctions:\n");
    printf("'A' = %d (character A)\n", 'A');
    printf("'0' = %d (character zero)\n", '0');
    printf("'\\0' = %d (null terminator)\n", '\0');
    printf("0 = %d (integer zero)\n", 0);
    
    wait_for_enter();
    
    // ========================================
    // 3. STRING LENGTH
    // ========================================
    printf("\n=== 3. STRING LENGTH ===\n");
    
    char str1[SIZE];
    printf("Enter a string: ");
    sgets(str1);
    
    int len = 0;
    for (int i = 0; str1[i] != '\0'; i++)
        len++;
    
    printf("String: (%s)\n", str1);
    printf("Length: %d\n", len);
    
    wait_for_enter();
    
    // ========================================
    // 4. APPEND CHARACTER
    // ========================================
    printf("\n=== 4. APPEND CHARACTER ===\n");
    
    char str2[100];
    printf("Enter a word: ");
    scanf("%s", str2);
    getchar();
    
    printf("Original: (%s)\n", str2);
    
    // Find end
    int i;
    for (i = 0; str2[i] != '\0'; i++)
        ;
    
    // Append 'x'
    str2[i] = 'x';
    str2[i + 1] = '\0';
    
    printf("After appending 'x': (%s)\n", str2);
    
    wait_for_enter();
    
    // ========================================
    // 5. COUNT SPECIFIC CHARACTER
    // ========================================
    printf("\n=== 5. COUNT SPECIFIC CHARACTER ===\n");
    
    char str3[SIZE];
    int ch;
    int count = 0;
    
    printf("Enter a string: ");
    sgets(str3);
    
    printf("Enter character to count: ");
    ch = getchar();
    getchar(); // Consume newline
    
    for (int i = 0; str3[i] != '\0'; i++) {
        if (str3[i] == ch)
            count++;
    }
    
    printf("String: (%s)\n", str3);
    printf("Character '%c' appears %d times\n", ch, count);
    
    // Case-insensitive count
    count = 0;
    for (int i = 0; str3[i] != '\0'; i++) {
        if (toupper(str3[i]) == toupper(ch))
            count++;
    }
    printf("Case-insensitive count: %d times\n", count);
    
    wait_for_enter();
    
    // ========================================
    // 6. CHARACTER FREQUENCY (HISTOGRAM)
    // ========================================
    printf("\n=== 6. CHARACTER FREQUENCY ===\n");
    
    char str4[SIZE];
    int counts[26] = {0};
    
    printf("Enter a string: ");
    sgets(str4);
    
    // Count each letter
    for (int i = 0; str4[i] != '\0'; i++) {
        if (isalpha(str4[i])) {
            counts[toupper(str4[i]) - 'A']++;
        }
    }
    
    printf("\nCharacter frequency:\n");
    for (int i = 0; i < 26; i++) {
        if (counts[i])
            printf("%c: %d times\n", 'A' + i, counts[i]);
    }
    
    wait_for_enter();
    
    // ========================================
    // 7. STRING REVERSE
    // ========================================
    printf("\n=== 7. STRING REVERSE ===\n");
    
    char str5[SIZE];
    printf("Enter a string: ");
    sgets(str5);
    
    printf("Original: (%s)\n", str5);
    
    // Find length
    len = 0;
    for (int i = 0; str5[i] != '\0'; i++)
        len++;
    
    // Reverse
    for (int i = 0; i < len / 2; i++) {
        char temp = str5[i];
        str5[i] = str5[len - i - 1];
        str5[len - i - 1] = temp;
    }
    
    printf("Reversed: (%s)\n", str5);
    
    wait_for_enter();
    
    // ========================================
    // 8. STRING CONCATENATION
    // ========================================
    printf("\n=== 8. STRING CONCATENATION ===\n");
    
    char s1[SIZE];
    char s2[SIZE];
    
    printf("Enter first word: ");
    scanf("%s", s1);
    printf("Enter second word: ");
    scanf("%s", s2);
    getchar();
    
    printf("First: (%s)\n", s1);
    printf("Second: (%s)\n", s2);
    
    // Find end of s1
    int j;
    for (j = 0; s1[j] != '\0'; j++)
        ;
    
    // Append s2 to s1
    int k;
    for (k = 0; s2[k] != '\0'; k++) {
        s1[j + k] = s2[k];
    }
    s1[j + k] = '\0';
    
    printf("Concatenated: (%s)\n", s1);
    
    wait_for_enter();
    
    // ========================================
    // 9. NULL TERMINATOR DEMONSTRATION
    // ========================================
    printf("\n=== 9. NULL TERMINATOR IMPORTANCE ===\n");
    
    // With null terminator
    char good[10] = {'H', 'E', 'L', 'L', 'O', '\0'};
    printf("With null terminator: (%s)\n", good);
    
    // Demonstrating manual string building
    char manual[10];
    manual[0] = 'T';
    manual[1] = 'E';
    manual[2] = 'S';
    manual[3] = 'T';
    manual[4] = '\0';  // Critical!
    printf("Manually built string: (%s)\n", manual);
    
    printf("\nNote: Without '\\0', printing would be undefined behavior!\n");
    
    wait_for_enter();
    
    // ========================================
    // 10. STRING COMPARISON
    // ========================================
    printf("\n=== 10. STRING COMPARISON ===\n");
    
    char str_a[SIZE];
    char str_b[SIZE];
    
    printf("Enter first string: ");
    sgets(str_a);
    printf("Enter second string: ");
    sgets(str_b);
    
    // Compare strings
    int idx = 0;
    while (str_a[idx] != '\0' && str_b[idx] != '\0') {
        if (str_a[idx] != str_b[idx])
            break;
        idx++;
    }
    
    if (str_a[idx] == '\0' && str_b[idx] == '\0')
        printf("Strings are EQUAL\n");
    else
        printf("Strings are DIFFERENT\n");
    
    return 0;
}