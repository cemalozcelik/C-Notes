#include <stdio.h>

// Static variable to hold the counter value
static int count = 0;

// Static helper functions
static void inc() {
    count++;
}

static void dec() {
    count--;
}

// Public functions
void increment() {
    inc();
}

void decrement() {
    dec();
}

int get_counter() {
    return count;
}

void reset_counter() {
    count = 0;
}