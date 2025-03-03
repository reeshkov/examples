// gcc -Wall -Wpointer-arith -Wmissing-prototypes -Wstrict-prototypes -fno-strict-aliasing -fno-strict-overflow -fno-delete-null-pointer-checks -Wempty-body -g3 -o showdb2 showdb2.c -lrpm -lrpmio -lsqlite3 -lgcrypt -lbz2 -lz -llzma -llua -lm -lzstd -lpopt -laudit -ldl -lpthread -Wl,-rpath -Wl,/usr/local/lib
// find /usr/share/applications -type f -name '*.desktop' -exec ./showdb2 {} \;

#include <errno.h>

#include <rpm/rpmlib.h>
#include <rpm/rpmmacro.h>
#include <rpm/rpmts.h>
#include <rpm/rpmlog.h>
#include <rpm/rpmdb.h>
#include <rpm/rpmsq.h>

int main(int argc, char ** argv)
{
    rpmSetVerbosity(RPMLOG_INFO);
    if (argc != 2 || (!argv[1])) return 2;
    int ec = 0;
    rpmts ts = rpmtsCreate();
    char * const fn =  argv[1];

    rpmPushMacro(NULL, "_dbpath", NULL, "/var/lib/rpm", RMIL_CMDLINE);
    rpmdbMatchIterator mi = rpmtsInitIterator(ts, RPMDBI_INSTFILENAMES, fn, 0);

    if (mi == NULL)
        mi = rpmtsInitIterator(ts, RPMDBI_PROVIDENAME, fn, 0);
    if (mi == NULL) {
        struct stat sb;
        if (lstat(fn, &sb) != 0)
            rpmlog(RPMLOG_ERR, ("file %s: %s\n"), fn, strerror(errno));
        else
            rpmlog(RPMLOG_NOTICE, ("file %s is not owned by any package\n"), fn);
    } else {
        Header h;
        while ((h = rpmdbNextIterator(mi)) != NULL) {
            rpmsqPoll();
            const char *errstr;
            char *str = headerFormat(h, "%{nvra}\n", &errstr);
            if ( str != NULL ) {
                rpmlog(RPMLOG_NOTICE, "%s from %s",fn, str);
                free(str);
            } else {
                rpmlog(RPMLOG_ERR, ("incorrect format: %s\n"), errstr);
            }
        }
    }
    rpmlog(RPMLOG_DEBUG, "stop\n");
    return ec;
}

