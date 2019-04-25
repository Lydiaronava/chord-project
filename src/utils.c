#include <stdlib.h>
#include <time.h>

#include <mpi.h>

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

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Helper function for computing the Chord IDs of the peers
void init_chord_ids(int ids[NB_PEERS])
{
    for (int i = 0; i < NB_PEERS; i++) {
        ids[i] = f(i);
    }

    qsort(ids, NB_PEERS, sizeof(int), cmpfunc);
}

void simulator(void)
{
    int chord_ids[NB_PEERS];
    init_chord_ids(chord_ids);

    for (int i = 1; i <= NB_PEERS; i++) {
        // Send the process Chord ID
        MPI_Send(&chord_ids[i - 1], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD);
        // Send the Chord ID of the successor
        MPI_Send(&chord_ids[i % NB_PEERS], 1, MPI_INT, i, TAGINIT, MPI_COMM_WORLD);
    }
}
