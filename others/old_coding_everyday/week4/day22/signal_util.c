#include <signal.h>

#include "util.h"

#ifndef HAVE_SIGIGNORE
__BEGIN_DECLS
int sigignore(int sig) {
    struct sigaction sa = { .sa_handler = SIG_IGN, .sa_flags = 0 };

    if (sigemptyset(&sa.sa_mask) == -1 || sigaction(sig, &sa, 0) == -1) {
        return -1;
    }
    return 0;
}
__END_DECLS
#endif
