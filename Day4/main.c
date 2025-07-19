#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <math.h>


// Function Declarations
void show_ascii(void);
void demonstrate_number_systems(int number);
void float_comparison(void);
void character_representations(void);
void integer_suffixes(void);
void integer_overflow(void);
void save_array_to_file(int arr[], int size, const char* filename);
void analyze_character_types(const char* text);
void escape_sequences(void);
void scientific_notation(void);
void analyze_text_file(const char* filename);


// Main function
int main(void) {
    printf("=== Day 4: C Programming Practice ===\n\n");
    
    // Show ASCII table
    printf("=== ASCII Table ===\n");
    show_ascii();
    printf("ASCII table saved to ascii.txt\n\n");

    // Demonstrate number system
    printf("=== Number Systems ===\n");
    demonstrate_number_systems(167);
    printf("\n");

    // Float comparison 
    printf("=== Float Comparison ===\n");
    float_comparison();
    printf("\n");

    // Character representations demo
    printf("=== Character Representations ===\n");
    character_representations();
    printf("\n");

    // Integer suffixes demo
    printf("=== Integer Suffixes ===\n");
    integer_suffixes();
    printf("\n");

    // Integer overflow
    printf("=== Integer Overflow ===\n");
    integer_overflow();
    printf("\n");

    // Save array to file
    printf("=== Save Array to File ===\n");
    int arr[] = {66, 42, 73, 84, 695, 1000, 1234, 5678, 91011, 121314};
    save_array_to_file(arr, sizeof(arr) / sizeof(arr[0]), "array_stats.txt");
    printf("\n");

    // Analyze character types
    printf("=== Analyze Character Types ===\n");
    const char* text = "Hello, World! 12345 :at @ #$%^&*()_+ \n";
    analyze_character_types(text);
    printf("\n");

    // Escape sequences demo
    printf("=== Escape Sequences ===\n");
    escape_sequences();
    printf("\n");

    // Scientific notation demo
    printf("=== Scientific Notation ===\n");
    scientific_notation();
    printf("\n");

    // Analyze text file
    printf("=== Analyze Text File ===\n");
    analyze_text_file("ascii.txt");
    printf("\n");

    return 0;
}


void show_ascii(void) {

    FILE* file = fopen("ascii.txt", "w");
    if (!file)
    {
        fprintf(stderr,"File cannot created!\n");
        return;
    }

    for (int i = 0; i < 128; i++){
        if (iscntrl(i)) {
            fprintf(file, "%-3d  %2X   Control Character\n", i, i); // Control characters are not printable visually not displayed like "\n", "\t", etc.
        }
        else
        {
            fprintf(file, "%-3d  %2X   '%c'\n", i, i, (char)i); // Print ASCII value, hex value, and character
        }
    }
    
    fclose(file);
}

void demonstrate_number_systems(int number) {

    printf("Decimal: %d\n", number);
    printf("Octal: %o\n", number);
    printf("hex lowercase: %x\n", number);
    printf("hex lowercase: %X\n", number);
    
}

void float_comparison(void) {

    float a = 5.6;

    if (a == 5.6) printf("a is equal to 5.6\n");
    else printf("a is not equal to 5.6\n"); // 5.6 is a double literal, so it may not match float exactly due to precision issues

    if (a == 5.6f) printf("a is equal to 5.6f\n"); // avoid type promotion
    else printf("a is not equal to 5.6f\n");

}

void character_representations(void) {

    char a1 = 'A'; // Direct character representation
    char a2 = 65; // Decimal representation
    char a3 = '\x41'; // Hexadecimal representation
    char a4 = '\101'; // Octal representation
    printf("Character representations:\n");
    if (a1 == a2 && a1 == a3 && a1 == a4) {
        printf("All representations are equal: '%c' (%d, %x, %o)\n", a1, a1, a1, a1);
    } else {
        printf("Representations are not equal!\n");
    }
    printf("\n");
    
    printf("\x42URS\x41\n");           // Prints: BURSA
    printf("\102\101\102\101\012");    // Prints: BABA (with newline)

}

void integer_suffixes(void) {

    // Unsigned integers
    642u; // Unsigned int
    642U; // Unsigned int
    0x12u; // Unsigned int (hexadecimal)
    0x12U; // Unsigned int (hexadecimal)

    // Long suffixes
    45L; // Long
    45l; // Long
    0x12L; // Long (hexadecimal)
    0x12l; // Long (hexadecimal)

    // Long long suffixes
    12345678901LL; // Long long
    12345678901ll; // Long long

    // Unsigned long long suffixes
    56ull; // Unsigned long long
    56ULL; // Unsigned long long
    0x12ull; // Unsigned long long (hexadecimal)
    0x12ULL; // Unsigned long long (hexadecimal)
    12345678901234567890ULL; // Unsigned long long literal
    55llu; // Unsigned long long literal with llu suffix
    55LLU; // Unsigned long long literal with LLU suffix

    // special cases
    0; // Zero literal
    0u; // Unsigned zero
    0L; // Long zero
    0x0; // Hexadecimal zero
    0x0u; // Unsigned hexadecimal zero
    0x0L; // Long hexadecimal zero

    // Print examples
    printf("Unsigned int: %u\n", 642u);
    printf("Long: %ld\n", 45L);
    printf("Long long: %lld\n", 12345678901LL);
    printf("Unsigned long long: %llu\n", 12345678901234567890ULL);
    printf("Hexadecimal unsigned long long: %llu\n", 0x12ULL);
    printf("Hexadecimal unsigned long long with llu suffix: %llu\n", 0x12llu);  
    
}

void integer_overflow(void) {

    // teorical signed max 01111111 11111111 11111111 11111111
    // teorical signed min 10000000 00000000 00000000 00000000
    // and after overflow it will wrap around to negative value

    int x = 2147483647; // Maximum value for a signed int
    int y = x + 1; // This will cause overflow
    printf("Original int: %d\n", x);
    printf("After overflow: %d\n", y); // Undefined behavior, may wrap around to negative value

    // teorical unsigned max 11111111 11111111 11111111 11111111
    // teorical unsigned min 00000000 00000000 00000000 00000000
    // and after overflow it will wrap around to 0

    unsigned int ux = 4294967295u; // Maximum value for an unsigned int
    unsigned int uy = ux + 1; // This will wrap around to 0
    printf("Original unsigned int: %u\n", ux);
    printf("After overflow: %u\n", uy); // Wraps around to 0
}

void save_array_to_file(int arr[], int size, const char* filename) {

    FILE* file = fopen(filename, "w");
    if (!file) {    
        fprintf(stderr, "Error opening file %s for writing\n", filename);
        return;
    }

    fprintf(file, "Array size: %d\n", size);
    fprintf(file, "Array elements:\n");
    fprintf(file, "%-5s %-10s\n", "Index", "Value"); // Header for better readability

    for (int i = 0; i < size; i++) {
        fprintf(file, "%-5d %-10d\n", i, arr[i]); // Print index and value 
    }

    int min = arr[0], max = arr[0], sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
        sum += arr[i];
    }

    double average = (size > 0) ? (double)sum / size : 0.0;
    fprintf(file, "Min: %d\n", min);
    fprintf(file, "Max: %d\n", max);
    fprintf(file, "Sum: %d\n", sum);
    fprintf(file, "Average: %.2f\n", average);
    
    fclose(file);
    printf("Array saved to %s\n", filename);
}

void analyze_character_types(const char* text) {

    int digit_count = 0, letter_count = 0, space_count = 0, punctuation_count = 0, other_count = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if(isdigit(c)) digit_count++;
        else if(isalpha(c)) letter_count++;
        else if(isspace(c)) space_count++;
        else if(ispunct(c)) punctuation_count++;
        else other_count++;
    }

    printf("Letter count:      %d\n", letter_count);
    printf("Digit count:       %d\n", digit_count);
    printf("Whitespace count:  %d\n", space_count);
    printf("Punctuation count: %d\n", punctuation_count);
    printf("Other characters:  %d\n", other_count);
}

void escape_sequences(void) {
    printf("Escape Sequences:\n");
    printf("Newline: \\n\n");
    printf("Tab: \\t\n");
    printf("Backslash: \\\n");
    printf("Single Quote: \'\n");
    printf("Double Quote: \"\n");
    printf("Carriage Return: \\r\n");
    printf("Form Feed: \\f\n");
    printf("Alert (Bell): \\a\n");
    printf("Backspace: \\b\n");

    // Example usage
    printf("Hello,\nWorld!\n"); // Newline
    printf("Column1\tColumn2\n"); // Tab
}

void scientific_notation(void) {
    printf("Scientific Notation:\n");

    printf("2.8e8: %e\n", 2.8e8);
    printf("3.6E7: %e\n", 3.6E7);
    printf("4123e-5: %e\n", 4123e-5);

    printf("2.8e8: %f\n", 2.8e8);
    printf("3.6E7: %F\n", 3.6E7);
    printf("4123e-5: %f\n", 4123e-5);

}

void analyze_text_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    
    int char_count[256] = {0};  // 256 ASCII characters 
    // Initialize character count array to zero
    int c;
    
    while ((c = fgetc(file)) != EOF) { // Read each character from the file
        char_count[c]++;
    }
    
    fclose(file);
    
    // Print statistics
    printf("Character frequency analysis:\n");
    for (int i = 0; i < 256; i++) {
        if (char_count[i] > 0) {
            if (isprint(i)) {
                printf("'%c': %d times\n", i, char_count[i]);
            } else {
                printf("ASCII %d: %d times\n", i, char_count[i]);
            }
        }
    }
}

/*
=== Day 4: C Programming Practice ===

=== ASCII Table ===
ASCII table saved to ascii.txt

=== Number Systems ===
Decimal: 167
Octal: 247
hex lowercase: a7
hex lowercase: A7

=== Float Comparison ===
a is not equal to 5.6
a is equal to 5.6f

=== Character Representations ===
Character representations:
All representations are equal: 'A' (65, 41, 101)

BURSA
BABA

=== Integer Suffixes ===
Unsigned int: 642
Long: 45
Long long: 12345678901
Unsigned long long: 12345678901234567890
Hexadecimal unsigned long long: 18
Hexadecimal unsigned long long with llu suffix: 18

=== Integer Overflow ===
Original int: 2147483647
After overflow: -2147483648
Original unsigned int: 4294967295
After overflow: 0

=== Save Array to File ===
Array saved to array_stats.txt

=== Analyze Character Types ===
Letter count:      12
Digit count:       5
Whitespace count:  7
Punctuation count: 14
Other characters:  0

=== Escape Sequences ===
Escape Sequences:
Newline: \n
Tab: \t
Backslash: \
Single Quote: '
Double Quote: "
Carriage Return: \r
Form Feed: \f
Alert (Bell): \a
Backspace: \b
Hello,
World!
Column1 Column2

=== Scientific Notation ===
Scientific Notation:
2.8e8: 2.800000e+008
3.6E7: 3.600000e+007
4123e-5: 4.123000e-002
2.8e8: 280000000.000000
3.6E7:
4123e-5: 0.041230

=== Analyze Text File ===
Character frequency analysis:
ASCII 10: 128 times
' ': 800 times
'!': 1 times
'"': 1 times
'#': 1 times
'$': 1 times
'%': 1 times
'&': 1 times
''': 191 times
'(': 1 times
')': 1 times
'*': 1 times
'+': 1 times
',': 1 times
'-': 1 times
'.': 1 times
'/': 1 times
'0': 32 times
'1': 86 times
'2': 56 times
'3': 48 times
'4': 48 times
'5': 48 times
'6': 48 times
'7': 48 times
'8': 31 times
'9': 31 times
':': 1 times
';': 1 times
'<': 1 times
'=': 1 times
'>': 1 times
'?': 1 times
'@': 1 times
'A': 9 times
'B': 9 times
'C': 75 times
'D': 9 times
'E': 9 times
'F': 9 times
'G': 1 times
'H': 1 times
'I': 1 times
'J': 1 times
'K': 1 times
'L': 1 times
'M': 1 times
'N': 1 times
'O': 1 times
'P': 1 times
'Q': 1 times
'R': 1 times
'S': 1 times
'T': 1 times
'U': 1 times
'V': 1 times
'W': 1 times
'X': 1 times
'Y': 1 times
'Z': 1 times
'[': 1 times
'\': 1 times
']': 1 times
'^': 1 times
'_': 1 times
'`': 1 times
'a': 67 times
'b': 1 times
'c': 34 times
'd': 1 times
'e': 34 times
'f': 1 times
'g': 1 times
'h': 34 times
'i': 1 times
'j': 1 times
'k': 1 times
'l': 34 times
'm': 1 times
'n': 34 times
'o': 67 times
'p': 1 times
'q': 1 times
'r': 100 times
's': 1 times
't': 67 times
'u': 1 times
'v': 1 times
'w': 1 times
'x': 1 times
'y': 1 times
'z': 1 times
'{': 1 times
'|': 1 times
'}': 1 times
'~': 1 times
*/