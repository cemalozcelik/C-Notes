#ifndef CUTILITY_H
#define CUTILITY_H

// Macro definitions
#define isleap(y)    ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))

// Function declarations
int     ndigit(int val);
int     isprime(int val);
void    sleep_ms(int milliseconds);
void    putline(void);
void    clear_input_buffer(void);

#endif // CUTILITY_H