#define _GNU_SOURCE
#include <time.h>
#include <unistd.h>
#include <stdio.h>

static long long ns_diff(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1000000000LL + (b.tv_nsec - a.tv_nsec);
}

int main() {
    struct timespec start, end;
    int nloops = 1000000;

    for (int t = 0; t < 5; t++) {

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < nloops; i++) {
            getpid();
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        long long diff = ns_diff(start, end);

        printf("Trial %d (clock): %.6f us\n",
               t + 1,
               (double)diff / 1000.0 / nloops);
    }

    return 0;
}