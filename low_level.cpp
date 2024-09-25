#include <iostream>
#include <sys/mman.h>
#include <cstring>
#include <unistd.h>

void inline_arm_assembly() {
    unsigned long result;
    asm volatile (
        "mov x0, #42\n"
        "mov %0, x0\n"
        : "=r" (result)
    );
    std::cout << "ARM inline assembly result: " << result << std::endl;
}

void memory_mapping_example() {
    long page_size = sysconf(_SC_PAGESIZE);
    std::cout << "Page size: " << page_size << " bytes" << std::endl;

    void* mapped_memory = mmap(nullptr, page_size, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANON, -1, 0);

    if (mapped_memory == MAP_FAILED) {
        std::cerr << "Memory mapping failed!" << std::endl;
        return;
    }

    memset(mapped_memory, 0, page_size);
    std::cout << "Memory successfully mapped and initialized to 0." << std::endl;

    if (munmap(mapped_memory, page_size) != 0) {
        std::cerr << "Failed to unmap memory!" << std::endl;
    } else {
        std::cout << "Memory successfully unmapped." << std::endl;
    }
}

int main() {
    inline_arm_assembly();

    memory_mapping_example();

    return 0;
}

