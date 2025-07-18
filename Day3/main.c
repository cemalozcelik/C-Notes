#include <stdio.h>

// Function Definitions 

void print_banner();
void demonstrate_arrays();
void demonstrate_loops();
int find_max_in_array(int arr[], int size);
int find_min_in_array(int arr[], int size);
double calculate_average(int arr[], int size);
void print_array(int arr[], int size);
void reverse_array(int arr[], int size);
int linear_search(int arr[], int size, int target);
void bubble_sort(int arr[], int size);
int count_frequency(int arr[], int size, int target);


int main() {
    print_banner();
    
    // Demonstrate arrays
    printf("\n=== ARRAYS DEMONSTRATION ===\n");
    demonstrate_arrays();
    
    // Demonstrate different types of loops
    printf("\n=== LOOPS DEMONSTRATION ===\n");
    demonstrate_loops();
    
    // Working with user input array
    printf("\n=== INTERACTIVE ARRAY OPERATIONS ===\n");
    int size;
    printf("Enter the size of array (max 10): ");
    scanf("%d", &size);
    
    if (size > 10 || size <= 0) {
        printf("Invalid size! Using default size of 5.\n");
        size = 5;
    }
    
    int user_array[10];
    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &user_array[i]);
    }
    
    printf("\nYour array: ");
    print_array(user_array, size);
    
    printf("Maximum value: %d\n", find_max_in_array(user_array, size));
    printf("Minimum value: %d\n", find_min_in_array(user_array, size));
    printf("Average: %.2f\n", calculate_average(user_array, size));
    
    // Search demonstration
    int search_value;
    printf("\nEnter a value to search for: ");
    scanf("%d", &search_value);
    int position = linear_search(user_array, size, search_value);
    if (position != -1) {
        printf("Found %d at position %d\n", search_value, position);
        printf("Number of occurrences: %d\n", count_frequency(user_array, size, search_value));
    } else {
        printf("%d not found in the array\n", search_value);
    }
    
    // Reverse array
    printf("\nReversing the array...\n");
    reverse_array(user_array, size);
    printf("Reversed array: ");
    print_array(user_array, size);
    
    // Sort array
    printf("\nSorting the array...\n");
    bubble_sort(user_array, size);
    printf("Sorted array: ");
    print_array(user_array, size);
    
    return 0;
}

void print_banner() {
    printf("================================\n");
    printf("          DAY 3                 \n");
    printf("================================\n");
}

void demonstrate_arrays() {
    // Array initialization
    int numbers[5] = {10, 20,30, 60, 180};
    int grades[] = {85, 92, 78, 96, 88}; // Size inferred from initializers

    printf("Static array demonstration:\n");
    printf("Numbers array: ");
    print_array(numbers, 5);

    printf("Grades array: ");
    print_array(grades, 5);

    // Array manipulation
    printf("\nArray manipulation:\n");
    printf("Original grades: ");
    print_array(grades, 5);

    // Adding 5 to each grade
    for(int i = 0; i < 5; i++) {
        grades[i] += 5;
    }

    printf("After adding 5 each grade: ");
    print_array(grades, 5);
}

void demonstrate_loops() {
    printf("Loop demonstrations:\n");

    // for loop
    printf("\n1. Fpr loop (counting 1-5): ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // while loop
    printf("2. While loop (counting down from 5): ");
    int countdown = 5;
    while (countdown >= 1) {
        printf("%d ", countdown);
        countdown--;
    }
    printf("\n");

    // do-while loop
    printf("3. Do-while loop (counting up from 1 to 5): ");
    int even = 2;
    do {
        printf("%d ", even);
        even += 2;
    } while (even <= 10);       
    printf("\n");

    // Nested loops - multiplication table
    printf("\n4. Nested loops (multiplication table 1-3):\n");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("%d x %d = %d\n", i, j, i * j);
        }
    }
    printf("\n");
    
    // Break and continue statements
    printf("5. Break and continue demonstration:\n");
    for (int i = 1; i <= 10; i++) {
        if (i == 5) {
            printf("Breaking at %d\n", i);
            break; // Breaks the loop when i is 5
        }
        if (i % 2 == 0) {
            printf("%d is even, skipping\n", i);
            continue; // Skips the rest of the loop for even numbers
        }
        printf("%d is odd\n", i);
    }
    printf("\n");
    
}


// Function to find the maximum value in an array
// Returns the maximum value found in the array
int find_max_in_array(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}   


// Function to find the minimum value in an array
// Returns the minimum value found in the array
int find_min_in_array(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Function to calculate the average of an array
// Returns the average as a double
double calculate_average(int arr[], int size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += arr[i];
    }
    
    return (double)sum / size ; // Cast to double for accurate division
}

// Function to print an array
void print_array(int arr[], int size){
    if (size == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < size; i++){
        if (i == size-1){       
            printf("%d]\n", arr[i]);
        }
        else {
            printf("%d,", arr[i]);
        }
    }
}

// Function to reverse an array
void reverse_array(int arr[], int size){
    int temp; // for example 1 3 5 7
    for (int i = 0; i < size / 2; i++){
        temp = arr[i]; // take 1
        arr[i] = arr[size - 1 - i]; // initialize first index with last element 7
        arr[size - 1 - i] = temp; // last index initialized to temp
    }
}

// Function to perform linear search
// Returns the index of the target if found, otherwise returns -1
int linear_search(int arr[], int size, int target){
    for (int i = 0; i < size; i++){
            if (arr[i] == target){
                return i; // Return where is the target index
            }
        }
    return -1; // Return -1 if not found
}

// Function to perform bubble sort
// Sorts the array in ascending order
// Uses a simple bubble sort algorithm
void bubble_sort(int arr[], int size){
    int temp;
    for (int i = 0; i < size -1; i++){
        for (int j = 0; j < size -1; j++){
            if(arr[j] > arr[j+1]){
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to count frequency of a target in an array
// Returns the count of occurrences of the target in the array
int count_frequency(int arr[], int size, int target){
    int count = 0;
    for (int i = 0; i < size; i++){
            if (arr[i] == target){
                count++; // Increment count if target is found
            }
    }
    return count;
}


/*
================================
          DAY 3
================================

=== ARRAYS DEMONSTRATION ===
Static array demonstration:
Numbers array: [10,20,30,60,180]
Grades array: [85,92,78,96,88]

Array manipulation:
Original grades: [85,92,78,96,88]
After adding 5 each grade: [90,97,83,101,93]

=== LOOPS DEMONSTRATION ===
Loop demonstrations:

1. Fpr loop (counting 1-5): 1 2 3 4 5
2. While loop (counting down from 5): 5 4 3 2 1
3. Do-while loop (counting up from 1 to 5): 2 4 6 8 10

4. Nested loops (multiplication table 1-3):
1 x 1 = 1
1 x 2 = 2
1 x 3 = 3
2 x 1 = 2
2 x 2 = 4
2 x 3 = 6
3 x 1 = 3
3 x 2 = 6
3 x 3 = 9

5. Break and continue demonstration:
1 is odd
2 is even, skipping
3 is odd
4 is even, skipping
Breaking at 5


=== INTERACTIVE ARRAY OPERATIONS ===
Enter the size of array (max 10): 6
Enter 6 integers:
Element 1: 5
Element 2: 7
Element 3: 2
Element 4: 66
Element 5: 22
Element 6: 88

Your array: [5,7,2,66,22,88]
Maximum value: 88
Minimum value: 2
Average: 31.67

Enter a value to search for: 66
Found 66 at position 3
Number of occurrences: 1

Reversing the array...
Reversed array: [88,22,66,2,7,5]

Sorting the array...
Sorted array: [2,5,7,22,66,88]
*/