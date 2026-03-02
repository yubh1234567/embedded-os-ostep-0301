// syscall_read_test.c
// 목적:
// read(fd, NULL, 0) 시스템 콜의 평균 비용을 측정한다.
// getpid보다 더 무거운 시스템 콜과 비교하기 위함.

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>  // open()

int main() {

    struct timeval start, end;
    int nloops = 1000000;

    // /dev/null 파일을 열어 file descriptor 확보
    // 실제 디스크 I/O를 피하기 위해 사용
    int fd = open("/dev/null", O_RDONLY);

    for (int t = 0; t < 5; t++) {

        gettimeofday(&start, NULL);

        for (int i = 0; i < nloops; i++) {
            // 반환값은 사용하지 않음 (측정 목적)
            (void)read(fd, NULL, 0);
        }

        gettimeofday(&end, NULL);

        long diff = (end.tv_sec - start.tv_sec) * 1000000
                  + (end.tv_usec - start.tv_usec);

        printf("Trial %d (read): %.6f us\n",
               t + 1,
               (double)diff / nloops);
    }

    close(fd);  // 파일 디스크립터 정리

    return 0;
}