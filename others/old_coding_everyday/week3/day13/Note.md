```c
R_Zero = 0.0;
R_PosInf = 1.0/R_Zero;
R_NegInf = -1.0/R_Zero;
R_Nan = R_Zero/R_Zero;

signal(SIGHUP, SIG_IGN);
signal(SIGPIPE, SIG_IGN);

static void setupSigSegvAction(void) {
    struct sigaction act;

    sigemptyset (&act.sa_mask);
    /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction
     * is used. Otherwise, sa_handler is used */
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
    act.sa_sigaction = segvHandler;
    sigaction (SIGSEGV, &act, NULL);
    sigaction (SIGBUS, &act, NULL);
    sigaction (SIGFPE, &act, NULL);
    sigaction (SIGILL, &act, NULL);
    sigaction (SIGBUS, &act, NULL);
    return;
}
```
