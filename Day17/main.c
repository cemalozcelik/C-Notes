/*
 * C Programming Day 17 - Arrays Practice
 * Complete implementation of all array algorithms from notes
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 100

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

// Algorithm Functions
void print_unique_values(const int* a, int size) {
    int freq[1000] = {0};
    
    printf("Unique values: ");
    for (int i = 0; i < size; i++) {
        if (freq[a[i]] == 0) {
            printf("%d ", a[i]);
            freq[a[i]] = 1;
        }
    }
    printf("\n");
}

void reverse_copy(const int* source, int* dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[size - 1 - i];
    }
}

int main() {
    int a[SIZE];
    
    randomize();
    set_random_array(a, SIZE);
    
    printf("=== ORIGINAL ARRAY ===\n");
    print_array(a, SIZE);
    wait_for_enter();
    
    // ========================================
    // 1. AVERAGE (ARITHMETIC MEAN)
    // ========================================
    printf("\n=== 1. AVERAGE ===\n");
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += a[i];
    }
    printf("Average: %f\n", (double)sum / SIZE);
    wait_for_enter();
    
    // ========================================
    // 2. ODD NUMBERS AVERAGE
    // ========================================
    printf("\n=== 2. ODD NUMBERS AVERAGE ===\n");
    int odd_sum = 0;
    int odd_count = 0;
    
    for (int i = 0; i < SIZE; i++) {
        if (a[i] % 2) {
            odd_sum += a[i];
            odd_count++;
        }
    }
    
    if (odd_count)
        printf("Odd average: %f\n", (double)odd_sum / odd_count);
    else
        printf("No odd numbers in array\n");
    wait_for_enter();
    
    // ========================================
    // 3. MAX ELEMENT
    // ========================================
    printf("\n=== 3. MAX ELEMENT ===\n");
    int max = a[0];
    int max_id = 0;
    
    for (int i = 1; i < SIZE; i++) {
        if (a[i] > max) {
            max = a[i];
            max_id = i;
        }
    }
    
    printf("Max value: %d   Max index: %d\n", max, max_id);
    wait_for_enter();
    
    // ========================================
    // 4. MIN AND MAX TOGETHER
    // ========================================
    printf("\n=== 4. MIN AND MAX ===\n");
    max = a[0];
    int min = a[0];
    
    for (int i = 1; i < SIZE; i++) {
        if (a[i] > max)
            max = a[i];
        else if (a[i] < min)
            min = a[i];
    }
    
    printf("Max = %d     Min = %d\n", max, min);
    wait_for_enter();
    
    // ========================================
    // 5. RUNNER-UP (SECOND MAXIMUM)
    // ========================================
    printf("\n=== 5. RUNNER-UP ===\n");
    max = a[0];
    int runner_up = a[1];
    
    if (a[1] > a[0]) {
        max = a[1];
        runner_up = a[0];
    }
    
    for (int i = 2; i < SIZE; i++) {
        if (a[i] > max) {
            runner_up = max;
            max = a[i];
        }
        else if (a[i] != max && a[i] > runner_up)
            runner_up = a[i];
    }
    
    printf("Runner-up = %d      Max = %d\n", runner_up, max);
    wait_for_enter();
    
    // ========================================
    // 6. REVERSE (IN-PLACE)
    // ========================================
    printf("\n=== 6. REVERSE (IN-PLACE) ===\n");
    int temp;
    for (int i = 0; i < SIZE / 2; i++) {
        temp = a[i];
        a[i] = a[SIZE - 1 - i];
        a[SIZE - 1 - i] = temp;
    }
    print_array(a, SIZE);
    
    // Reverse back for next tests
    for (int i = 0; i < SIZE / 2; i++) {
        temp = a[i];
        a[i] = a[SIZE - 1 - i];
        a[SIZE - 1 - i] = temp;
    }
    
    // ========================================
    // 7. LINEAR SEARCH
    // ========================================
    printf("\n=== 7. LINEAR SEARCH ===\n");
    int sval;
    printf("Enter value to search: ");
    scanf("%d", &sval);
    
    int i;
    for (i = 0; i < SIZE && a[i] != sval; i++)
        ;
    
    if (i < SIZE)
        printf("Found at index %d\n", i);
    else
        printf("%d not found\n", sval);
    wait_for_enter();
    
    // ========================================
    // 8. UNIQUE VALUES (Homework 1)
    // ========================================
    printf("\n=== 8. UNIQUE VALUES (O(n)) ===\n");
    print_unique_values(a, SIZE);
    wait_for_enter();
    
    // ========================================
    // 9. REVERSE COPY (Homework 2)
    // ========================================
    printf("\n=== 9. REVERSE COPY ===\n");
    int b[SIZE];
    reverse_copy(a, b, SIZE);
    
    printf("Original array:\n");
    print_array(a, SIZE);
    
    printf("Reversed copy:\n");
    print_array(b, SIZE);
    wait_for_enter();
    
    // ========================================
    // 10. ARRAY INITIALIZATION EXAMPLES
    // ========================================
    printf("\n=== 10. INITIALIZATION EXAMPLES ===\n");
    
    int arr1[10] = {3, 7, 9, 2};  // Partial init
    printf("Partial init: ");
    for (int j = 0; j < 10; j++)
        printf("%d ", arr1[j]);
    printf("\n");
    
    int arr2[10] = {0};  // All zeros
    printf("All zeros: ");
    for (int j = 0; j < 10; j++)
        printf("%d ", arr2[j]);
    printf("\n");
    
    int arr3[] = {[5] = 17, [13] = 25};  // Designated
    printf("Designated init (size=%zu): ", sizeof(arr3)/sizeof(arr3[0]));
    for (int j = 0; j < 14; j++)
        printf("%d ", arr3[j]);
    printf("\n");
    wait_for_enter();
    
    return 0;
}