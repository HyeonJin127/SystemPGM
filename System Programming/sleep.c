#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number_of_seconds>\n", argv[0]);
        fprintf(stderr, "Pause for <number_of_seconds> seconds.\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    long seconds_to_sleep;

    seconds_to_sleep = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || (seconds_to_sleep == 0 && errno != 0) || seconds_to_sleep < 0) {
        if (seconds_to_sleep < 0) {
            fprintf(stderr, "%s: invalid time interval '%s': A non-negative number is required.\n", argv[0], argv[1]);
        } else {
            fprintf(stderr, "%s: invalid time interval '%s'\n", argv[0], argv[1]);
        }
        return EXIT_FAILURE;
    }

    unsigned int remaining_sleep_time = sleep((unsigned int)seconds_to_sleep);

    return EXIT_SUCCESS;
}