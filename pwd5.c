#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 4096

// User-defined getcwd function
char* my_getcwd(char *buffer, size_t size) {
    const char* self_cmd = "/proc/self/cwd";

    ssize_t len = readlink(self_cmd, buffer, size - 1);

    if (len != -1) {
        buffer[len] = '\0';
        return buffer;
    } else {
        return NULL;
    }
}

int main(int argc, char *argv[]) {
    // Check for command-line arguments
    if (argc != 2 || strcmp(argv[1], "pwd") != 0) {
        printf("Usage: %s pwd\n", argv[0]);
        return 1;
    }

    char buffer[MAX_LEN];

    if (my_getcwd(buffer, sizeof(buffer)) != NULL) {
        printf("%s\n", buffer);
    } else {
        perror("my_getcwd error");
        return 1;
    }

    return 0;
}

