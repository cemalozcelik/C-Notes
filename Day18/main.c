/*
 * C Programming Day 18 - Advanced Arrays Practice
 * Bubble sort, sizeof, merge, unique random generator
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 100
#define URAND_MAX 10

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

// Unique random number generator
int urand(void) {
    static int a[URAND_MAX] = {0};  // Track which numbers generated
    static int count = 0;            // How many generated so far
    int val;
    
    if (count == URAND_MAX)
        return -1;  // All numbers exhausted
    
    // Find ungenerated number
    for (;;) {
        val = rand() % URAND_MAX;
        if (a[val] == 0)
            break;
    }
    
    a[val] = 1;  // Mark as generated
    count++;
    return val;
}

// Macro for array size
#define asize(a) (sizeof(a) / sizeof((a)[0]))

// Maximum Subarray - Brute Force O(n²)
void max_subarray_bruteforce(int *a, int size) {
    int max_sum = a[0];
    int start = 0, end = 0;
    
    for (int i = 0; i < size; i++) {
        int current_sum = 0;
        for (int j = i; j < size; j++) {
            current_sum += a[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
                start = i;
                end = j;
            }
        }
    }
    
    printf("Max sum: %d\n", max_sum);
    printf("Subarray indices: [%d, %d]\n", start, end);
    printf("Elements: ");
    for (int i = start; i <= end; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// Maximum Subarray - Kadane's Algorithm O(n)
void max_subarray_kadane(int *a, int size) {
    int max_sum = a[0];
    int current_sum = a[0];
    int start = 0, end = 0, temp_start = 0;
    
    for (int i = 1; i < size; i++) {
        // Either extend current subarray or start new one
        if (a[i] > current_sum + a[i]) {
            current_sum = a[i];
            temp_start = i;
        } else {
            current_sum = current_sum + a[i];
        }
        
        // Update maximum if needed
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
    }
    
    printf("Max sum: %d\n", max_sum);
    printf("Subarray indices: [%d, %d]\n", start, end);
    printf("Elements: ");
    for (int i = start; i <= end; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[SIZE];
    
    randomize();
    
    // ========================================
    // 1. BASIC BUBBLE SORT
    // ========================================
    printf("=== 1. BASIC BUBBLE SORT ===\n");
    set_random_array(a, SIZE);
    
    printf("Before sorting:\n");
    print_array(a, SIZE);
    
    // Bubble sort - ascending order
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    
    printf("After bubble sort (ascending):\n");
    print_array(a, SIZE);
    wait_for_enter();
    
    // ========================================
    // 2. CUSTOM BUBBLE SORT - ODDS THEN EVENS
    // ========================================
    printf("\n=== 2. CUSTOM SORT - ODDS FIRST, THEN EVENS ===\n");
    set_random_array(a, SIZE);
    
    printf("Before sorting:\n");
    print_array(a, SIZE);
    
    // Sort: odds first (sorted), then evens (sorted)
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1 - i; j++) {
            // Swap if: current odd AND next even
            //       OR: same parity AND current > next
            if ((a[j] % 2 != 0 && a[j + 1] % 2 == 0) || 
                ((a[j] % 2 == a[j + 1] % 2) && (a[j] > a[j + 1]))) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    
    printf("After custom sort (odds then evens):\n");
    print_array(a, SIZE);
    wait_for_enter();
    
    // ========================================
    // 3. BUBBLE SORT VS QUICK SORT PERFORMANCE
    // ========================================
    printf("\n=== 3. PERFORMANCE COMPARISON ===\n");
    
#undef SIZE
#define SIZE 10000
    
    int* p = (int*)malloc(SIZE * sizeof(int));
    if (!p) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    
    set_random_array(p, SIZE);
    
    // Bubble Sort timing
    clock_t start = clock();
    
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1 - i; j++) {
            if (p[j] > p[j + 1]) {
                int temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    clock_t end = clock();
    printf("Bubble sort (%d elements): %.4f seconds\n", 
           SIZE, (double)(end - start) / CLOCKS_PER_SEC);
    
    // Reset array for qsort
    set_random_array(p, SIZE);
    
    // Quick Sort timing
    start = clock();
    qsort(p, SIZE, sizeof(*p), icmp);
    end = clock();
    
    printf("Quick sort  (%d elements): %.4f seconds\n", 
           SIZE, (double)(end - start) / CLOCKS_PER_SEC);
    
    printf("\nNote: At 100,000 elements, difference becomes hours vs seconds!\n");
    
    free(p);
    wait_for_enter();
    
    // ========================================
    // 4. UNIQUE RANDOM NUMBER GENERATOR
    // ========================================
    printf("\n=== 4. UNIQUE RANDOM NUMBER GENERATOR ===\n");
    
    printf("Generating %d unique random numbers (0-%d):\n", URAND_MAX, URAND_MAX - 1);
    for (int i = 0; i < URAND_MAX; i++) {
        printf("%d ", urand());
    }
    printf("\n");
    
    printf("Trying to generate one more (should return -1): %d\n", urand());
    wait_for_enter();
    
    // ========================================
    // 5. sizeof OPERATOR DEMONSTRATIONS
    // ========================================
    printf("\n=== 5. sizeof OPERATOR ===\n");
    
    // Basic types
    printf("sizeof(char)   = %zu\n", sizeof(char));
    printf("sizeof(int)    = %zu\n", sizeof(int));
    printf("sizeof(long)   = %zu\n", sizeof(long));
    printf("sizeof(double) = %zu\n", sizeof(double));
    printf("\n");
    
    // Expressions
    int x = 10;
    printf("int x = 10;\n");
    printf("sizeof x       = %zu\n", sizeof x);
    printf("sizeof(x)      = %zu\n", sizeof(x));
    printf("sizeof(x + 5)  = %zu\n", sizeof(x + 5));
    printf("\n");
    
    // Character constants
    printf("sizeof 'A'     = %zu (char promoted to int)\n", sizeof 'A');
    printf("sizeof('A'+5)  = %zu\n", sizeof('A' + 5));
    printf("\n");
    
    // Unevaluated context
    printf("=== Unevaluated Context Demo ===\n");
    x = 5;
    printf("x = %d\n", x);
    printf("sizeof(x++)    = %zu\n", sizeof(x++));
    printf("x after sizeof = %d (x++ was NOT executed!)\n", x);
    printf("\n");
    wait_for_enter();
    
    // ========================================
    // 6. sizeof WITH ARRAYS
    // ========================================
    printf("\n=== 6. sizeof WITH ARRAYS ===\n");
    
    int arr[10] = {0};
    printf("int arr[10];\n");
    printf("sizeof arr              = %zu (total bytes)\n", sizeof arr);
    printf("sizeof arr[0]           = %zu (one element)\n", sizeof arr[0]);
    printf("sizeof arr / sizeof arr[0] = %zu (element count)\n", 
           sizeof arr / sizeof arr[0]);
    printf("\n");
    
    // Using asize macro
    int nums[] = {4, 5, 67, 8, 76, 5, 4, 3, 2, 6};
    printf("int nums[] = {4, 5, 67, 8, 76, 5, 4, 3, 2, 6};\n");
    printf("asize(nums) = %zu\n", asize(nums));
    printf("Array contents: ");
    for (int i = 0; i < asize(nums); i++)
        printf("%d ", nums[i]);
    printf("\n\n");
    
    // Declare array based on another's size
    int doubled[asize(nums) * 2] = {0};
    printf("int doubled[asize(nums) * 2]; // size = %zu\n", asize(doubled));
    wait_for_enter();
    
    // ========================================
    // 7. MERGE ALGORITHM
    // ========================================
    printf("\n=== 7. MERGE SORTED ARRAYS ===\n");
    
#undef SIZE
#define SIZE 10
    
    int a1[SIZE], b1[SIZE];
    int merged[2 * SIZE];
    
    // Generate and sort two arrays
    set_random_array(a1, SIZE);
    set_random_array(b1, SIZE);
    qsort(a1, SIZE, sizeof(int), icmp);
    qsort(b1, SIZE, sizeof(int), icmp);
    
    printf("Array A (sorted):\n");
    print_array(a1, SIZE);
    
    printf("Array B (sorted):\n");
    print_array(b1, SIZE);
    
    // Merge algorithm - O(n)
    int idx_a = 0;
    int idx_b = 0;
    
    for (int i = 0; i < 2 * SIZE; i++) {
        if (idx_a == SIZE)
            merged[i] = b1[idx_b++];
        else if (idx_b == SIZE)
            merged[i] = a1[idx_a++];
        else if (a1[idx_a] < b1[idx_b])
            merged[i] = a1[idx_a++];
        else
            merged[i] = b1[idx_b++];
    }
    
    printf("Merged array (still sorted):\n");
    print_array(merged, 2 * SIZE);
    wait_for_enter();
    
    // ========================================
    // 8. ARRAY INDEXING QUIRK
    // ========================================
    printf("\n=== 8. ARRAY INDEXING QUIRK ===\n");
    
    int quirky[10] = {5, 3, 2, 5, 6, 7, 1, 9, 7, 8};
    
    printf("Normal indexing a[i]:\n");
    for (int i = 0; i < 10; i++)
        printf("%d ", quirky[i]);
    printf("\n\n");
    
    printf("Reverse indexing i[a] (also legal!):\n");
    for (int i = 0; i < 10; i++)
        printf("%d ", i[quirky]);  // Legal C syntax!
    printf("\n");
    
    printf("\nBoth produce the same result!\n");
    printf("(Explained by pointer arithmetic - covered later)\n");
    wait_for_enter();
    
    // ========================================
    // 9. SIZEOF PITFALL - SIGNED/UNSIGNED
    // ========================================
    printf("\n=== 9. sizeof PITFALL WARNING ===\n");
    
    int test[] = {4, 6, 2, 6, 1, 5, 9, 7, 8};
    printf("int test[] = {4, 6, 2, 6, 1, 5, 9, 7, 8};\n");
    printf("asize(test) = %zu\n\n", asize(test));
    
    printf("DANGER: for(int i = -2; i < asize(test) - 2; i++)\n");
    printf("This loop will NOT execute!\n");
    printf("Why? asize returns size_t (unsigned)\n");
    printf("-2 converts to unsigned: 4,294,967,294\n");
    printf("Always be careful with signed/unsigned comparisons!\n");
    
    return 0;
}