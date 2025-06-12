#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <utmp.h>
#include <unistd.h>
#include <string.h>

int opt_pretty = 0;

void print_current_time_format() {
    time_t current_time;
    char time_str[20];

    time(&current_time);
    struct tm *local_time = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", local_time);
    printf(" %s ", time_str);
}

void print_uptime_default_format(long uptime_seconds) {
    long days = uptime_seconds / (60 * 60 * 24);
    uptime_seconds %= (60 * 60 * 24);
    long hours = uptime_seconds / (60 * 60);
    uptime_seconds %= (60 * 60);
    long minutes = uptime_seconds / 60;

    printf(" up ");
    if (days > 0) {
        printf("%ld day%s, ", days, (days == 1) ? "" : "s");
    }
    printf("%ld:%02ld", hours, minutes);
}

void print_uptime_pretty_format(long uptime_seconds) {
    long weeks = uptime_seconds / (60 * 60 * 24 * 7);
    uptime_seconds %= (60 * 60 * 24 * 7);
    long days = uptime_seconds / (60 * 60 * 24);
    uptime_seconds %= (60 * 60 * 24);
    long hours = uptime_seconds / (60 * 60);
    uptime_seconds %= (60 * 60);
    long minutes = uptime_seconds / 60;
    
    char final_uptime_str[100] = "up";
    int first_unit_printed = 0;

    if (weeks > 0) {
        sprintf(final_uptime_str + strlen(final_uptime_str), " %ld week%s", weeks, (weeks == 1) ? "" : "s");
        first_unit_printed = 1;
    }
    if (days > 0) {
        if (first_unit_printed) {
            strcat(final_uptime_str, ",");
        }
        sprintf(final_uptime_str + strlen(final_uptime_str), " %ld day%s", days, (days == 1) ? "" : "s");
        first_unit_printed = 1;
    }
    if (hours > 0) {
        if (first_unit_printed) {
            strcat(final_uptime_str, ",");
        }
        sprintf(final_uptime_str + strlen(final_uptime_str), " %ld hour%s", hours, (hours == 1) ? "" : "s");
        first_unit_printed = 1;
    }
    if (minutes > 0) {
        if (first_unit_printed) {
            strcat(final_uptime_str, ",");
        }
        sprintf(final_uptime_str + strlen(final_uptime_str), " %ld minute%s", minutes, (minutes == 1) ? "" : "s");
        first_unit_printed = 1;
    }

    if (!first_unit_printed) {
        strcat(final_uptime_str, " 0 minutes");
    }

    printf("%s", final_uptime_str);
}


int count_users() {
    int user_count = 0;
    struct utmp *ut;

    setutent();
    while ((ut = getutent()) != NULL) {
        if (ut->ut_type == USER_PROCESS && ut->ut_name[0] != '\0' && ut->ut_host[0] != '\0') {
            user_count++;
        }
    }
    endutent();
    return user_count;
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "p")) != -1) {
        switch (opt) {
            case 'p':
                opt_pretty = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-p]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (optind < argc) {
        fprintf(stderr, "Usage: %s [-p]\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sysinfo info;

    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return EXIT_FAILURE;
    }

    if (!opt_pretty) {
        print_current_time_format();
        print_uptime_default_format(info.uptime);
        printf(",  %d user%s", count_users(), (count_users() == 1) ? "" : "s");
        printf(",  load average: %.2f, %.2f, %.2f",
               (double)info.loads[0] / (1 << SI_LOAD_SHIFT),
               (double)info.loads[1] / (1 << SI_LOAD_SHIFT),
               (double)info.loads[2] / (1 << SI_LOAD_SHIFT));
    } else {
        print_uptime_pretty_format(info.uptime);
    }

    printf("\n");

    return 0;
}