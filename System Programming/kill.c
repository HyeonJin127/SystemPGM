#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

int signal_name_to_num(const char *sig_name) {
    if (strcmp(sig_name, "TERM") == 0 || strcmp(sig_name, "SIGTERM") == 0) {
        return SIGTERM;
    }
    if (strcmp(sig_name, "KILL") == 0 || strcmp(sig_name, "SIGKILL") == 0) {
        return SIGKILL;
    }

    char *endptr;
    long sig_num = strtol(sig_name, &endptr, 10);
    if (*endptr == '\0' && sig_num > 0 && sig_num <= 31) {
        return (int)sig_num;
    }

    return -1;
}

int main(int argc, char *argv[]) {
    int signal_to_send = SIGTERM;
    pid_t pid = 0;
    int opt;

    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
            case 's':
                signal_to_send = signal_name_to_num(optarg);
                if (signal_to_send == -1) {
                    fprintf(stderr, "%s: unknown signal: %s\n", argv[0], optarg);
                    return EXIT_FAILURE;
                }
                break;
            default:
                fprintf(stderr, "Usage: %s [-s SIGNAL] <PID>\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (optind + 1 != argc) {
        if (argc == 3 && argv[1][0] == '-') {
            char *sig_str = argv[1] + 1;
            signal_to_send = signal_name_to_num(sig_str);
            if (signal_to_send == -1) {
                 fprintf(stderr, "%s: unknown signal: %s\n", argv[0], sig_str);
                 return EXIT_FAILURE;
            }
            char *endptr_pid;
            long pid_val = strtol(argv[2], &endptr_pid, 10);
            if (*endptr_pid != '\0' || pid_val <= 0) {
                fprintf(stderr, "%s: invalid PID: %s\n", argv[0], argv[2]);
                return EXIT_FAILURE;
            }
            pid = (pid_t)pid_val;

        } else {
            fprintf(stderr, "Usage: %s [-s SIGNAL] <PID>\n", argv[0]);
            fprintf(stderr, "   or: %s -SIGNAL <PID>\n", argv[0]);
            return EXIT_FAILURE;
        }
    } else if (optind == argc -1) {
        char *endptr_pid;
        long pid_val = strtol(argv[optind], &endptr_pid, 10);
        if (*endptr_pid != '\0' || pid_val <= 0) {
            fprintf(stderr, "%s: invalid PID: %s\n", argv[0], argv[optind]);
            return EXIT_FAILURE;
        }
        pid = (pid_t)pid_val;
    }

    if (kill(pid, signal_to_send) == -1) {
        switch (errno) {
            case ESRCH:
                fprintf(stderr, "%s: kill %d: no such process\n", argv[0], (int)pid);
                break;
            case EPERM:
                fprintf(stderr, "%s: kill %d: operation not permitted\n", argv[0], (int)pid);
                break;
            default:
                perror(argv[0]);
                break;
        }
        return EXIT_FAILURE;
    }

    return 0;
}