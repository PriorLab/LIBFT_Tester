#include "tester.h"

int                   g_pass    = 0;
int                   g_fail    = 0;
int                   g_crash   = 0;
jmp_buf               g_jump;
volatile sig_atomic_t g_segfault = 0;

static void sig_handler(int sig)
{
    (void)sig;
    g_segfault = 1;
    siglongjmp(g_jump, 1);
}

static void arm_signals(void)
{
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESETHAND;
    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGBUS,  &sa, NULL);
}

void  setup_signals(void) { arm_signals(); }

void  print_header(const char *name)
{
    printf("\n" BOLD CYAN
        "══════════════════════════════════════\n"
        "  Testing: ft_%s\n"
        "══════════════════════════════════════"
        RESET "\n", name);
}

void  print_result(const char *desc, int passed)
{
    arm_signals();
    if (passed == -1)
    {
        printf("  " RED "[CRASH]" RESET " %s\n", desc);
        g_crash++;
        g_fail++;
    }
    else if (passed)
    {
        printf("  " GREEN "[OK]   " RESET " %s\n", desc);
        g_pass++;
    }
    else
    {
        printf("  " RED "[KO]   " RESET " %s\n", desc);
        g_fail++;
    }
}

void  print_summary(void)
{
    printf("\n" BOLD
        "══════════════════════════════════════\n"
        "  SUMMARY\n"
        "══════════════════════════════════════\n" RESET);
    printf("  Total :  %d\n", g_pass + g_fail);
    printf("  " GREEN "Passed:  %d" RESET "\n", g_pass);
    if (g_fail > 0)
        printf("  " RED "Failed:  %d  (crashes: %d)" RESET "\n", g_fail, g_crash);
    else
        printf("  Failed:  0\n");
    if (g_fail == 0)
        printf("\n" BOLD GREEN "  ✓ All tests passed!" RESET "\n\n");
    else
        printf("\n" BOLD RED   "  ✗ Some tests failed." RESET "\n\n");
}
