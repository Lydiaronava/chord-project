#include <stdlib.h>
#include <time.h>

#include "utils.h"

int f(int n)
{
    static int init = 0;
    static int hashes_table[M] = {-1};

    // Initialize the RNG seed only once
    if (!init) {
        srand(time(NULL));
        init = 1;
    }

    // If this value hasn't been asked yet, compute it.
    if (hashes_table[n] == -1) {
        int collision = 0;

        do {
            hashes_table[n] = rand() % M;

            for (int i = 0; i < M; i++) {
                if (i != n && hashes_table[i] == hashes_table[n]) {
                    collision = 1;
                }
            }
        } while (collision); // Each hash must be unique
    }

    return hashes_table[n];
}
