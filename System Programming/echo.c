#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int opt_no_newline = 0;
int opt_enable_escapes = 0;

void process_escapes_and_print(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\') {
            switch (str[++i]) {
                case 'n':putchar('\n'); break;
                case 't':putchar('\t'); break;
                case 'b':putchar('\b'); break;
                case 'r':putchar('\r'); break;
                case 'f':putchar('\f'); break;
                case 'v':putchar('\v'); break;
                case '\\':putchar('\\'); break;
                case '0': {
                    int octal_val = 0;
                    int j = 0;
                    while (j < 3 && str[i+1+j] >= '0' && str[i+1+j] <= '7') {
                        octal_val = octal_val * 8 + (str[i+1+j] - '0');
                        j++;
                    }
                    if (j > 0) {
                        putchar(octal_val);
                        i += j;
                    } else {
                        putchar('\\');
                        putchar('0');
                    }
                    break;
                }

                default:
                    putchar('\\');
                    putchar(str[i]);
                    break;
            }
        } else {
            putchar(str[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "ne")) != -1) {
        switch (opt) {
            case 'n':
                opt_no_newline = 1;
                break;
            case 'e':
                opt_enable_escapes = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-ne] [string...]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    for (int i = optind; i < argc; i++) {
        if (opt_enable_escapes) {
            process_escapes_and_print(argv[i]);
        } else {
            printf("%s", argv[i]);        
        }

        if (i < argc - 1) {
            printf(" ");
        }
    }

    if (!opt_no_newline) {
        printf("\n");
    }

    return 0;
}