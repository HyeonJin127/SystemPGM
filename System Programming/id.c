#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void print_user_id_info(const char *username) {
    struct passwd *pw;
    uid_t uid, euid;
    gid_t gid, egid;
    int ngroups = 0;
    gid_t *groups = NULL;

    if (username == NULL) {
        uid = getuid();
        euid = geteuid();
        gid = getgid();
        egid = getegid();
        pw = getpwuid(uid);
    } else {
        pw = getpwnam(username);
        if (pw == NULL) {
            fprintf(stderr, "id: '%s': no such user\n", username);
            exit(EXIT_FAILURE);
        }
        uid = pw->pw_uid;
        euid = pw->pw_uid;
        gid = pw->pw_gid;
        egid = pw->pw_gid;
    }

    const char *uname = (pw != NULL) ? pw->pw_name : "unknown";

    struct group *gr = getgrgid(gid);
    const char *gname = (gr != NULL) ? gr->gr_name : "unknown";

    struct passwd *epw = getpwuid(euid);
    const char *euname = (epw != NULL) ? epw->pw_name : "unknown";

    struct group *egr = getgrgid(egid);
    const char *egname = (egr != NULL) ? egr->gr_name : "unknown";

    printf("uid=%d(%s) gid=%d(%s)", (int)uid, uname, (int)gid, gname);

    if (euid != uid) {
        printf(" euid=%d(%s)", (int)euid, euname);
    }
    if (egid != gid) {
        printf(" egid=%d(%s)", (int)egid, egname);
    }

    if (username == NULL) {
        ngroups = getgroups(0, NULL);
    } else {
        ngroups = 0;
    }

    if (ngroups > 0) {
        groups = (gid_t *)malloc(sizeof(gid_t) * ngroups);
        if (groups == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        if (getgroups(ngroups, groups) == -1) {
            perror("getgroups");
            free(groups);
            exit(EXIT_FAILURE);
        }

        printf(" groups=");
        for (int i = 0; i < ngroups; i++) {
            struct group *gr_supp = getgrgid(groups[i]);
            const char *gname_supp = (gr_supp != NULL) ? gr_supp->gr_name : "unknown";
            printf("%d(%s)%s", (int)groups[i], gname_supp, (i == ngroups - 1) ? "" : ",");
        }
        free(groups);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_user_id_info(NULL);
    } else if (argc == 2) {
        print_user_id_info(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s [USERNAME]\n", argv[0]);
        return EXIT_FAILURE;
    }

    return 0;
}