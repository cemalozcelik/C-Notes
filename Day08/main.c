#include <stdio.h>

int main() {
    printf("=== Day 8 - C Programming Practice ===\n\n");

    // 1. Comma operator returns the rightmost value
    int result = (6, 7);
    printf("1. Comma Operator:\n");
    printf("   Result of (6, 7): %d\n\n", result);

    // 2. Understanding how x+++y is parsed
    int x = 10, y = 5;
    int z = x+++y;  // Interpreted as (x++) + y
    printf("2. Maximum Munch Rule:\n");
    printf("   x = 10, y = 5, x+++y results in z = %d, x becomes %d\n\n", z, x);

    // 3. Sequence point: logical OR ensures left side completes
    x = 5;
    int safe_result = x++ || (x > 10);
    printf("3. Sequence Points:\n");
    printf("   After x++ || (x > 10): x = %d, result = %d\n\n", x, safe_result);

    // 4. Comma operator also introduces a sequence point
    x = 5;
    int comma_result = (x++, x * 2);
    printf("4. Comma Operator with Expression:\n");
    printf("   x incremented to %d, final result = %d\n\n", x, comma_result);

    // 5. Chained assignments
    int a, b, c;
    a = b = c = 42;
    printf("5. Chained Assignments:\n");
    printf("   a = %d, b = %d, c = %d\n", a, b, c);

    int p = 1, q = 1, r = 1;
    p += q += r;
    printf("   After p += q += r: p = %d, q = %d, r = %d\n\n", p, q, r);

    // 6. Comma in if condition
    double val = 3.4;
    printf("6. Comma in Condition:\n");
    if (val > 2, 0) {
        printf("   This won’t print\n");
    } else {
        printf("   The condition evaluates to 0, so this prints\n\n");
    }

    // 7. Short-circuit AND (&&)
    x = 0; y = 10;
    if (x++ && y++) {
        printf("7. Short-Circuit AND:\n   Both true\n");
    } else {
        printf("7. Short-Circuit AND:\n   One or both are false\n");
    }
    printf("   After: x = %d, y = %d\n\n", x, y);

    // 8. Short-circuit OR (||)
    x = 1; y = 10;
    if (x++ || y++) {
        printf("8. Short-Circuit OR:\n   One condition is true\n");
    }
    printf("   After: x = %d, y = %d\n\n", x, y);

    // 9. Operator precedence in arithmetic
    int calc = -3 + 4 * 5 - 6;
    printf("9. Arithmetic Precedence:\n");
    printf("   -3 + 4 * 5 - 6 = %d\n", calc);
    calc = 3 + 4 % 5 - 6;
    printf("   3 + 4 %% 5 - 6 = %d\n\n", calc);

    // 10. Boolean logic with comparisons
    x = 0; y = 1;
    int bool_result = !!x == !!y > x + 1;
    printf("10. Boolean Expression:\n");
    printf("   !!x = %d, !!y = %d, result = %d\n\n", !!x, !!y, bool_result);

    // 11. Floating point precision
    double d = 0.0;
    d = d + 0.1 + 0.1 + 0.1 + 0.1;
    printf("11. Floating Point Precision:\n");
    printf("   Sum = %.17f\n", d);
    if (d == 0.4)
        printf("   Equal to 0.4\n\n");
    else {
        printf("   Not exactly 0.4 due to precision loss\n\n");
    }

    // 12. Assignment returns a value
    printf("12. Assignment Returns Value:\n");
    printf("   Result of (x = 100): %d\n", x = 100);
    printf("   x is now: %d\n\n", x);

    // 13. Logic mistake: using OR instead of AND
    x = 10;
    printf("13. Common Logic Mistake:\n");
    if (x != 5 || x != 13) {
        printf("   This is always true!\n");
    }
    if (x != 5 && x != 13) {
        printf("   This checks if x is neither 5 nor 13\n\n");
    }

    // 14. Multi-step comma operator
    int step1, step2, step3;
    int final = (step1 = 5, step2 = step1 * 2, step3 = step2 + 1);
    printf("14. Comma Operator in Sequence:\n");
    printf("   step1 = %d, step2 = %d, step3 = %d, final = %d\n", step1, step2, step3, final);

    return 0;
}
