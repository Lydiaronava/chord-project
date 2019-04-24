#include <stdlib.h>
#include <time.h>

#include "utils.h"

int f(int n)
{
    static int init = 0;
    static int hashes_table[(1 << M)] = {0};

    // Initialize only once
    if (!init) {
        // Empty entries are represented with -1
        for (int i = 0; i < (1 << M); i++) {
            hashes_table[i] = -1;
        }

        srand(time(NULL)); // Set the RNG seed
        init = 1;
    }

    // If this value hasn't been asked yet, compute it.
    if (hashes_table[n] == -1) {
        int collision = 0;

        do {
            hashes_table[n] = rand() % (1 << M);

            for (int i = 0; i < (1 << M); i++) {
                if (i != n && hashes_table[i] == hashes_table[n]) {
                    collision = 1;
                }
            }
        } while (collision); // Each hash must be unique
    }

    return hashes_table[n];
}
