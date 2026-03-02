#include <stdio.h>
#include <stdlib.h>

#define PHYS_MEM_SIZE 65536  // 64KB 정도의 물리 메모리를 가정

// 실제 RAM이라고 생각하고 만든 배열
unsigned char physical_memory[PHYS_MEM_SIZE];

// Base & Bounds 정보 저장용 구조체
// base  : 이 프로그램이 시작하는 물리 메모리 위치
// bounds: 이 프로그램이 사용할 수 있는 최대 크기
typedef struct {
    unsigned int base;
    unsigned int bounds;
} BaseBounds;


// 가상 주소를 물리 주소로 바꾸는 함수
unsigned int translate(BaseBounds config, unsigned int v_addr) {

    // 가상 주소가 허용 범위를 넘으면 접근 차단
    // 실제 OS에서는 segmentation fault 같은 예외가 발생한다고 보면 됨
    if (v_addr >= config.bounds) {
        printf("Memory Fault! Address %u is out of bounds.\n", v_addr);
        exit(1);
    }

    // 허용된 범위라면 base를 더해서 실제 물리 주소 계산
    unsigned int p_addr = config.base + v_addr;

    printf("VA %u -> PA %u\n", v_addr, p_addr);
    return p_addr;
}

int main() {

    // 32KB 지점부터 시작해서 16KB만 사용 가능하다고 가정
    // 즉, 이 프로그램은 32768 ~ 49151 범위만 접근 가능
    BaseBounds secure_partition = {32768, 16384};

    printf("=== Base & Bounds Simulation ===\n");

    // 정상 접근 (bounds 안에 있mda)
    unsigned int pa1 = translate(secure_partition, 100);
    physical_memory[pa1] = 42;

    // 이것도 정상 접근
    unsigned int pa2 = translate(secure_partition, 5000);
    physical_memory[pa2] = 99;

    // bounds를 넘는 접근 → 여기서 프로그램 종료됨
    translate(secure_partition, 20000);

    return 0;
}