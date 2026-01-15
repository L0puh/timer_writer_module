#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "/var/tmp/test_module/"

int main(int argc, char *argv[])
{
    char command[512];
    char full_path[256];

    if (argc != 4) {
        fprintf(stderr,
            "usage: %s <module.ko> <filename> <seconds>\n",
            argv[0]);
        return 1;
    }

    const char *module = argv[1];
    const char *filename = argv[2];
    const char *seconds = argv[3];

    if (atoi(seconds) < 1) {
        fprintf(stderr, "error: seconds must be >= 1\n");
        return 1;
    }

    snprintf(full_path, sizeof(full_path),
             PATH "%s", filename);

    snprintf(command, sizeof(command),
             "sudo insmod %s filename=%s seconds=%s",
             module, full_path, seconds);

    printf("loading module with parameters:\n");
    printf("  file:   %s\n", full_path);
    printf("  period: %s sec\n", seconds);

    if (system(command) != 0) {
        fprintf(stderr, "failed to load module\n");
        return 1;
    }

    printf("module loaded successfully\n");
    return 0;
}

