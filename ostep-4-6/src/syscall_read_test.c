#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    struct timeval start, end;
    int nloops = 1000000;

    int fd = open("/dev/null", O_RDONLY);

    for (int t = 0; t < 5; t++) {

        gettimeofday(&start, NULL);

        for (int i = 0; i < nloops; i++) {
            read(fd, NULL, 0);
        }

        gettimeofday(&end, NULL);

        long diff = (end.tv_sec - start.tv_sec) * 1000000
                  + (end.tv_usec - start.tv_usec);

        printf("Trial %d (read): %.6f us\n",
               t + 1,
               (double)diff / nloops);
    }

    close(fd);
    return 0;
}