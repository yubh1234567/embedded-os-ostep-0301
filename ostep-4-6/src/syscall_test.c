// syscall_test.c
// 목적:
// gettimeofday()를 사용하여 getpid() 시스템 콜의 평균 비용을 측정한다.
// 1,000,000회 반복 후 평균값(us)을 계산한다.

// 숙제, 백준 열심히 하세요 유병현씨

#include <sys/time.h>  // gettimeofday()
#include <unistd.h>    // getpid()
#include <stdio.h>     // printf()

int main() {

    struct timeval start, end;  // 시작/종료 시간 저장 구조체
    int nloops = 1000000;       // 시스템 콜 반복 횟수

    // 5회 반복 측정 (측정 안정성 확보 목적)
    for (int t = 0; t < 5; t++) {

        // 측정 시작 시간 기록
        gettimeofday(&start, NULL);

        // getpid()를 1,000,000회 호출
        // getpid는 매우 가벼운 시스템 콜 (프로세스 ID 반환)
        for (int i = 0; i < nloops; i++) {
            getpid();
        }

        // 측정 종료 시간 기록
        gettimeofday(&end, NULL);

        // 전체 경과 시간 계산 (마이크로초 단위)
        long diff = (end.tv_sec - start.tv_sec) * 1000000
                  + (end.tv_usec - start.tv_usec);

        // 평균 시스템 콜 비용 계산
        printf("Trial %d (getpid): %.6f us\n",
               t + 1,
               (double)diff / nloops);
    }

    return 0;
}