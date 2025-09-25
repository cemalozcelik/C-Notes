#include <stdio.h>
#include <stdlib.h>

//predefined macros test
void test_macros() {
    printf("File: %s\n", __FILE__);
    printf("Line: %d\n", __LINE__);
    printf("Date: %s\n", __DATE__);
    printf("Time: %s\n", __TIME__);
    printf("Function: %s\n", __func__);
    
    #ifdef __STDC__
        printf("Standard C compiler\n");
    #endif
}

//basic switch example
void switch_basic() {
    int x = 2;
    
    switch(x) {
        case 1:
            printf("one\n");
            break;
        case 2:
            printf("two\n");
            break;
        case 3:
            printf("three\n");
            break;
        default:
            printf("other\n");
    }
}

//fallthrough example - day of year calculation
void fallthrough_example() {
    int day = 15;
    int month = 9;
    int year = 2025;
    
    int sum = day;
    
    switch(month - 1) {
        case 11: sum += 30; //fallthrough
        case 10: sum += 31; //fallthrough  
        case 9:  sum += 30; //fallthrough
        case 8:  sum += 31; //fallthrough
        case 7:  sum += 31; //fallthrough
        case 6:  sum += 30; //fallthrough
        case 5:  sum += 31; //fallthrough
        case 4:  sum += 30; //fallthrough
        case 3:  sum += 31; //fallthrough
        case 2:  sum += 28; //fallthrough - no leap year calc for now
        case 1:  sum += 31;
    }
    
    printf("Day of year: %d\n", sum);
}

//character switch example
void char_switch_test() {
    char c = 'A';
    
    switch(c) {
        case 'A':
        case 'a':
            printf("Letter A\n");
            break;
        case 'B':  
        case 'b':
            printf("Letter B\n");
            break;
        default:
            printf("Other letter\n");
    }
}

//goto example - breaking out of nested loops
void goto_nested_loops() {
    int i, j, k;
    
    //nested loops - exit with goto
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            for(k = 0; k < 3; k++) {
                printf("i=%d, j=%d, k=%d\n", i, j, k);
                
                if(i == 1 && j == 1 && k == 1) {
                    goto exit_loops;
                }
            }
        }
    }
    
    exit_loops:
        printf("Exited from all nested loops\n");
}

//error handling pattern with goto
void error_handling_pattern() {
    int *ptr1 = NULL;
    int *ptr2 = NULL;
    FILE *file = NULL;
    
    ptr1 = malloc(sizeof(int) * 10);
    if(!ptr1) {
        printf("ptr1 allocation failed\n");
        goto cleanup;
    }
    
    ptr2 = malloc(sizeof(int) * 20);  
    if(!ptr2) {
        printf("ptr2 allocation failed\n");
        goto cleanup;
    }
    
    file = fopen("test.txt", "w");
    if(!file) {
        printf("file open failed\n");
        goto cleanup;
    }
    
    //normal operations here
    fprintf(file, "Hello World\n");
    printf("All operations completed successfully\n");
    
    cleanup:
        if(file) {
            fclose(file);
            printf("file closed\n");
        }
        if(ptr2) {
            free(ptr2);
            printf("ptr2 freed\n");
        }
        if(ptr1) {
            free(ptr1);
            printf("ptr1 freed\n");
        }
}

//switch variable declaration test
void switch_variable_test() {
    int a = 1;
    
    switch(a) {
        int x; //valid - before any case
        case 1: 
            x = 10;
            printf("x = %d\n", x);
            break;
        case 2:
            x = 20;
            printf("x = %d\n", x);
            break;
    }
}

//invalid switch examples - commented out for reference
/*
void invalid_switch_examples() {
    int x = 5;
    int n = 3;
    
    switch(n) {
        case x:        //ERROR - x is not constant
        case "Hello":  //ERROR - string literal not allowed
        case 2.5:      //ERROR - float not allowed
    }
}
*/

//symbolic constants for remote control
#define OFF 0
#define ON 1  
#define STANDBY 2
#define HOLD 3

void remote_control_demo() {
    int state = ON;
    
    switch(state) {
        case OFF:
            printf("Device OFF\n");
            break;
        case ON:
            printf("Device ON\n");
            break;
        case STANDBY:
            printf("Device STANDBY\n");
            break;
        case HOLD:
            printf("Device HOLD\n");
            break;
        default:
            printf("Unknown state\n");
    }
}

//days in month calculation
void days_in_month_calc() {
    int month = 2;
    int days;
    
    switch(month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days = 31;
            break;
        case 4: case 6: case 9: case 11:
            days = 30;
            break;
        case 2:
            days = 28; //no leap year check
            break;
        default:
            printf("Invalid month\n");
            return;
    }
    
    printf("Month %d has %d days\n", month, days);
}

//dynamic memory allocation example
void dynamic_memory_demo() {
    int n = 5;
    int *arr = NULL;
    
    printf("Allocating memory for %d integers...\n", n);
    
    arr = malloc(n * sizeof(int));
    if(!arr) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    //fill array with values
    for(int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    printf("Memory allocation successful\n");
    
    //cleanup
    free(arr);
    arr = NULL;
    printf("Memory freed\n");
}

int main() {
    printf("=== C Programming Day 15 - Examples ===\n\n");
    
    printf("1. Predefined macros:\n");
    test_macros();
    
    printf("\n2. Basic switch:\n");
    switch_basic();
    
    printf("\n3. Fallthrough example (day of year):\n");
    fallthrough_example();
    
    printf("\n4. Character switch:\n");
    char_switch_test();
    
    printf("\n5. Goto - breaking nested loops:\n");
    goto_nested_loops();
    
    printf("\n6. Error handling with goto:\n");
    error_handling_pattern();
    
    printf("\n7. Switch variable declaration:\n");
    switch_variable_test();
    
    printf("\n8. Remote control demo (symbolic constants):\n");
    remote_control_demo();
    
    printf("\n9. Days in month calculation:\n");
    days_in_month_calc();
    
    printf("\n10. Dynamic memory allocation demo:\n");
    dynamic_memory_demo();
    
    return 0;
}

//notes:
//- case labels must be unique
//- no break = fallthrough behavior
//- goto labels have function scope
//- predefined macros cannot be undefined
//- switch only works with integer expressions
//- case values must be constants