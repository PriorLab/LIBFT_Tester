#ifndef TESTER_H
# define TESTER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <setjmp.h>
# include <limits.h>

# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define CYAN    "\033[0;36m"
# define MAGENTA "\033[0;35m"
# define BOLD    "\033[1m"
# define RESET   "\033[0m"

extern int                   g_pass;
extern int                   g_fail;
extern int                   g_crash;
extern jmp_buf               g_jump;
extern volatile sig_atomic_t g_segfault;

void  setup_signals(void);
void  print_header(const char *name);
void  print_result(const char *desc, int passed);
void  print_summary(void);

/*
** CHECK: evaluates a boolean condition.
** If the function causes a segfault, the signal handler calls longjmp
** and the result is [CRASH] — tests continue regardless.
*/
# define CHECK(desc, cond) do {                          \
    g_segfault = 0;                                     \
    if (setjmp(g_jump) == 0) {                          \
        int _r = (int)(cond);                           \
        if (g_segfault) print_result(desc, -1);         \
        else            print_result(desc, _r);         \
    } else              print_result(desc, -1);         \
} while (0)

/*
** CHECK_STR: compares two strings with strcmp.
** Handles the case where one or both are NULL.
*/
# define CHECK_STR(desc, got, exp) do {                 \
    g_segfault = 0;                                     \
    if (setjmp(g_jump) == 0) {                          \
        char *_g = (got);                               \
        if (g_segfault)                                 \
            print_result(desc, -1);                     \
        else if (_g == NULL && (exp) == NULL)           \
            print_result(desc, 1);                      \
        else if (_g == NULL || (exp) == NULL)           \
            print_result(desc, 0);                      \
        else                                            \
            print_result(desc, strcmp(_g, exp) == 0);  \
    } else print_result(desc, -1);                      \
} while (0)

#endif
