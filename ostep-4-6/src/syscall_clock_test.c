// syscall_clock_test.c
// 목적:
// clock_gettime()을 사용하여 getpid() 시스템 콜 비용 측정
// gettimeofday()와 비교하기 위함.

#define _GNU_SOURCE
#include <time.h>     // clock_gettime()
#include <unistd.h>
#include <stdio.h>

// 두 timespec 구조체의 차이를 나노초(ns) 단위로 계산
static long long ns_diff(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1000000000LL
         + (b.tv_nsec - a.tv_nsec);
}

int main() {

    struct timespec start, end;
    int nloops = 1000000;

    for (int t = 0; t < 5; t++) {

        // CLOCK_MONOTONIC:
        // 시스템 시간 변경 영향을 받지 않는 안정적인 타이머
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < nloops; i++) {
            getpid();
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        long long diff = ns_diff(start, end);

        // 나노초 → 마이크로초 변환 후 평균 계산
        printf("Trial %d (clock_gettime): %.6f us\n",
               t + 1,
               (double)diff / 1000.0 / nloops);
    }

    return 0;
}