#include "utils/tester.h"
#include "libft.h"

/* Part 1 */
void test_isalpha(void);   void test_isdigit(void);   void test_isalnum(void);
void test_isascii(void);   void test_isprint(void);   void test_toupper(void);
void test_tolower(void);   void test_strlen(void);    void test_memset(void);
void test_bzero(void);     void test_memcpy(void);    void test_memmove(void);
void test_strlcpy(void);   void test_strlcat(void);   void test_strchr(void);
void test_strrchr(void);   void test_strncmp(void);   void test_memchr(void);
void test_memcmp(void);    void test_strnstr(void);   void test_atoi(void);
void test_calloc(void);    void test_strdup(void);

/* Part 2 */
void test_substr(void);    void test_strjoin(void);   void test_strtrim(void);
void test_split(void);     void test_itoa(void);      void test_strmapi(void);
void test_striteri(void);  void test_putchar_fd(void);void test_putstr_fd(void);
void test_putendl_fd(void);void test_putnbr_fd(void);

/* Part 3 */
#ifndef NO_PART3
void test_lstnew(void);    void test_lstadd_front(void); void test_lstsize(void);
void test_lstlast(void);   void test_lstadd_back(void);  void test_lstdelone(void);
void test_lstclear(void);  void test_lstiter(void);       void test_lstmap(void);
#endif

/* Extra edge cases */
void test_memset_extra(void);  void test_memcpy_extra(void);
void test_memmove_extra(void); void test_strlen_extra(void);
void test_strlcpy_extra(void); void test_strlcat_extra(void);
void test_strchr_extra(void);  void test_strrchr_extra(void);
void test_strncmp_extra(void); void test_atoi_extra(void);
void test_itoa_extra(void);    void test_substr_extra(void);
void test_strtrim_extra(void); void test_split_extra(void);
void test_strjoin_extra(void); void test_putnbr_extra(void);
void test_strmapi_extra(void); void test_striteri_extra(void);
void test_memchr_extra(void);  void test_memcmp_extra(void);
void test_strnstr_extra(void); void test_calloc_extra(void);
void test_strdup_extra(void);  void test_putchar_extra(void);
void test_combined(void);      void test_isX_exhaustive(void);
void test_atoi_borders(void);  void test_final_batch(void);
void test_reach_1000(void);

/* Allocation size checks + null protection */
void test_alloc_sizes(void);
void test_null_protection(void);

int main(void)
{
	setup_signals();
	printf(BOLD MAGENTA
		"\n╔══════════════════════════════════════╗\n"
		"║         LIBFT MEGA TESTER           ║\n"
		"╚══════════════════════════════════════╝\n" RESET);

	printf(BOLD YELLOW "\n── PART 1: Libc functions ──\n" RESET);
	test_isalpha(); test_isdigit(); test_isalnum(); test_isascii();
	test_isprint(); test_toupper(); test_tolower(); test_strlen();
	test_memset();  test_bzero();   test_memcpy();  test_memmove();
	test_strlcpy(); test_strlcat(); test_strchr();  test_strrchr();
	test_strncmp(); test_memchr();  test_memcmp();  test_strnstr();
	test_atoi();    test_calloc();  test_strdup();

	printf(BOLD YELLOW "\n── PART 2: Additional functions ──\n" RESET);
	test_substr();    test_strjoin();    test_strtrim();   test_split();
	test_itoa();      test_strmapi();    test_striteri();  test_putchar_fd();
	test_putstr_fd(); test_putendl_fd(); test_putnbr_fd();

#ifndef NO_PART3
	printf(BOLD YELLOW "\n── PART 3: Linked list ──\n" RESET);
	test_lstnew();    test_lstadd_front(); test_lstsize();
	test_lstlast();   test_lstadd_back();  test_lstdelone();
	test_lstclear();  test_lstiter();      test_lstmap();
#else
	printf(BOLD YELLOW "\n── PART 3: not implemented (skipped) ──\n" RESET);
#endif

	printf(BOLD YELLOW "\n── EXTRA: Deep edge cases ──\n" RESET);
	test_memset_extra();  test_memcpy_extra();  test_memmove_extra();
	test_strlen_extra();  test_strlcpy_extra(); test_strlcat_extra();
	test_strchr_extra();  test_strrchr_extra(); test_strncmp_extra();
	test_atoi_extra();    test_itoa_extra();    test_substr_extra();
	test_strtrim_extra(); test_split_extra();   test_strjoin_extra();
	test_putnbr_extra();  test_strmapi_extra(); test_striteri_extra();
	test_memchr_extra();  test_memcmp_extra();  test_strnstr_extra();
	test_calloc_extra();  test_strdup_extra();  test_putchar_extra();
	test_combined();      test_isX_exhaustive();test_atoi_borders();
	test_final_batch();   test_reach_1000();

	printf(BOLD YELLOW "\n── ALLOCATION SIZES & NULL PROTECTION ──\n" RESET);
	test_alloc_sizes();
	test_null_protection();

	print_summary();
	return (g_fail > 0 ? 1 : 0);
}
