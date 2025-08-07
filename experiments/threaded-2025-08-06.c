/*
Experiment: Cross-platform watchdog wrapper with workload timeout

General description:
This program demonstrates how to wrap any C workload in a supervisory
control unit that enforces a hard execution-time limit. The real work
runs in a separate thread, while main() waits for it to finish or kills
it when the timeout expires.

Detailed description:
- The wrapper is portable to Windows and POSIX systems through two
  code paths guarded by _WIN32.
- main() spawns a worker thread that executes workload_main().
- main() blocks with a platform-specific timed wait:
    Windows  WaitForSingleObject
    Linux    pthread_timedjoin_np
    Fallback busy-wait loop with pthread_tryjoin_np
- If the worker finishes before TIMEOUT_MS, its exit status is copied
  to g_result and returned to the OS.
- If the timeout elapses, the worker thread is forcibly terminated
  (TerminateThread on Windows, pthread_cancel on POSIX), an error is
  reported on stderr, and main() exits with status 1.
- workload_main() here is a simple CPU-bound test function: a recursive
  Fibonacci calculator that prints fib(40). Replace it with any
  application logic to obtain the same watchdog behavior.
*/

#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#else
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#ifndef TIMEOUT_MS
#define TIMEOUT_MS 5000 /* milliseconds */
#endif

int workload_main(void);              /* user function */
static volatile int g_result = 1;     /* shared exit status */

#if defined(_WIN32)
static DWORD WINAPI runner(LPVOID p)
{
    (void)p;
    g_result = workload_main();
    return 0;
}
#else
static void *runner(void *p)
{
    (void)p;
    g_result = workload_main();
    return NULL;
}
#endif

int main(void)
{
#if defined(_WIN32)
    HANDLE th = CreateThread(NULL, 0, runner, NULL, 0, NULL);
    if (!th) { fprintf(stderr, "CreateThread failed\n"); return 1; }

    DWORD w = WaitForSingleObject(th, TIMEOUT_MS);
    if (w == WAIT_TIMEOUT) {
        TerminateThread(th, 1);
        CloseHandle(th);
        fprintf(stderr, "timeout after %u ms\n", (unsigned)TIMEOUT_MS);
        return 1;
    }
    CloseHandle(th);
#else
    pthread_t th;
    if (pthread_create(&th, NULL, runner, NULL)) { perror("pthread_create"); return 1; }

#if defined(__linux__)
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec  += TIMEOUT_MS / 1000;
    ts.tv_nsec += (TIMEOUT_MS % 1000) * 1000000L;
    if (ts.tv_nsec >= 1000000000L) { ts.tv_sec++; ts.tv_nsec -= 1000000000L; }

    int rc = pthread_timedjoin_np(th, NULL, &ts);
    if (rc == ETIMEDOUT) {
        pthread_cancel(th);
        pthread_join(th, NULL);
        fprintf(stderr, "timeout after %d ms\n", TIMEOUT_MS);
        return 1;
    } else if (rc) { errno = rc; perror("pthread_timedjoin_np"); return 1; }
#else   /* generic POSIX fallback */
    struct timespec sl = { 0, 10000000L }; /* 10 ms */
    long remaining = TIMEOUT_MS;
    while (remaining > 0) {
        if (pthread_tryjoin_np(th, NULL) == 0) break;
        nanosleep(&sl, NULL);
        remaining -= 10;
    }
    if (remaining <= 0) {
        pthread_cancel(th);
        pthread_join(th, NULL);
        fprintf(stderr, "timeout reached\n");
        return 1;
    }
#endif
#endif
    return g_result;
}

/* stub; replace with real work */
static int fib(int n)
{
    return n < 2 ? n : fib(n - 1) + fib(n - 2);
}

int workload_main(void)
{
    int n = 45;
    int r = fib(n);
    printf("fib(%d) = %d\n", n, r);
    return 0; /* success */
}


