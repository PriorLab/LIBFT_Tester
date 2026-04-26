#include "../utils/tester.h"
#include "libft.h"

void	test_substr(void)
{
	char	*r;
	print_header("substr");

	r = ft_substr("Hello World", 6, 5);
	CHECK_STR("start=6 len=5 -> \"World\"",   r, "World"); free(r);
	r = ft_substr("Hello", 0, 5);
	CHECK_STR("start=0 len=5 -> full copy",   r, "Hello"); free(r);
	r = ft_substr("Hello", 0, 100);
	CHECK_STR("len>strlen -> full copy",       r, "Hello"); free(r);
	r = ft_substr("Hello", 2, 2);
	CHECK_STR("start=2 len=2 -> \"ll\"",       r, "ll"); free(r);
	r = ft_substr("Hello", 4, 1);
	CHECK_STR("start=4 len=1 -> \"o\"",        r, "o"); free(r);
	r = ft_substr("Hello", 0, 1);
	CHECK_STR("start=0 len=1 -> \"H\"",        r, "H"); free(r);
	r = ft_substr("Hello", 5, 5);
	CHECK_STR("start==strlen -> \"\"",          r, ""); free(r);
	r = ft_substr("Hello", 10, 5);
	CHECK_STR("start>strlen -> \"\"",           r, ""); free(r);
	r = ft_substr("Hello", 0, 0);
	CHECK_STR("len=0 -> \"\"",                  r, ""); free(r);
	r = ft_substr("", 0, 5);
	CHECK_STR("empty string -> \"\"",           r, ""); free(r);
	r = ft_substr("", 0, 0);
	CHECK_STR("empty len=0 -> \"\"",            r, ""); free(r);
	r = ft_substr("Hello", 3, 100);
	CHECK_STR("start=3 len=100 -> \"lo\"",      r, "lo"); free(r);
	r = ft_substr("Hello", 1, 3);
	CHECK_STR("start=1 len=3 -> \"ell\"",       r, "ell"); free(r);
	r = ft_substr("Hello", 0, 3);
	CHECK("nul at r[3]",                        r && r[3] == '\0'); free(r);
	r = ft_substr("Hello World", 6, 5);
	CHECK("correct length = 5",                 r && strlen(r) == 5); free(r);
	r = ft_substr("abcde", 0, 5);
	CHECK_STR("exact length copy",              r, "abcde"); free(r);
	r = ft_substr("x", 0, 1);
	CHECK_STR("1-char string",                  r, "x"); free(r);
	r = ft_substr("x", 0, 0);
	CHECK_STR("1-char len=0",                   r, ""); free(r);
	r = ft_substr("x", 1, 1);
	CHECK_STR("start=1 on 1-char str",          r, ""); free(r);
}

void	test_strjoin(void)
{
	char	*r;
	print_header("strjoin");

	r = ft_strjoin("Hello", " World");
	CHECK_STR("basic join",                     r, "Hello World"); free(r);
	r = ft_strjoin("", "World");
	CHECK_STR("empty s1 -> s2",                 r, "World"); free(r);
	r = ft_strjoin("Hello", "");
	CHECK_STR("empty s2 -> s1",                 r, "Hello"); free(r);
	r = ft_strjoin("", "");
	CHECK_STR("both empty -> \"\"",             r, ""); free(r);
	r = ft_strjoin("a", "b");
	CHECK_STR("single chars -> \"ab\"",         r, "ab"); free(r);
	r = ft_strjoin("42", " is the answer");
	CHECK_STR("numbers + text",                 r, "42 is the answer"); free(r);
	r = ft_strjoin("Hello\n", "World");
	CHECK_STR("with newline",                   r, "Hello\nWorld"); free(r);
	r = ft_strjoin("abc", "def");
	CHECK("length = 6",                         r && strlen(r) == 6);
	CHECK("nul at r[6]",                        r && r[6] == '\0'); free(r);
	r = ft_strjoin("foo ", "bar");
	CHECK_STR("space in s1",                    r, "foo bar"); free(r);
	r = ft_strjoin("foo", " bar");
	CHECK_STR("space in s2",                    r, "foo bar"); free(r);
	r = ft_strjoin("0123456789", "abcdefghij");
	CHECK("long join: len=20",                  r && strlen(r) == 20); free(r);
	r = ft_strjoin("x", "y");
	CHECK_STR("x+y -> \"xy\"",                  r, "xy"); free(r);
}

void	test_strtrim(void)
{
	char	*r;
	print_header("strtrim");

	r = ft_strtrim("  hello  ", " ");
	CHECK_STR("trim spaces",                    r, "hello"); free(r);
	r = ft_strtrim("xxhelloxx", "x");
	CHECK_STR("trim 'x'",                       r, "hello"); free(r);
	r = ft_strtrim("hello", " ");
	CHECK_STR("nothing to trim",                r, "hello"); free(r);
	r = ft_strtrim("", " ");
	CHECK_STR("empty string -> \"\"",           r, ""); free(r);
	r = ft_strtrim("   ", " ");
	CHECK_STR("only spaces -> \"\"",            r, ""); free(r);
	r = ft_strtrim("hello", "");
	CHECK_STR("empty set -> unchanged",         r, "hello"); free(r);
	/* set chars are individual, not a substring */
	r = ft_strtrim("abcba", "ab");
	CHECK_STR("set=\"ab\": trims a and b -> \"c\"", r, "c"); free(r);
	r = ft_strtrim("abacaba", "ab");
	CHECK_STR("set=\"ab\": trims until c -> \"c\"",  r, "c"); free(r);
	r = ft_strtrim("\t hello \t", " \t");
	CHECK_STR("set=\" \\t\"",                   r, "hello"); free(r);
	r = ft_strtrim("   hello", " ");
	CHECK_STR("trim left only",                 r, "hello"); free(r);
	r = ft_strtrim("hello   ", " ");
	CHECK_STR("trim right only",                r, "hello"); free(r);
	r = ft_strtrim("x hello x", "x");
	CHECK_STR("middle untouched",               r, " hello "); free(r);
	r = ft_strtrim("a", "a");
	CHECK_STR("1 char in set -> \"\"",          r, ""); free(r);
	r = ft_strtrim("a", "b");
	CHECK_STR("1 char not in set -> \"a\"",     r, "a"); free(r);
	r = ft_strtrim("  hi  ", " ");
	CHECK("nul at r[2]",                        r && r[2] == '\0'); free(r);
	r = ft_strtrim("abcXYZcba", "abc");
	CHECK_STR("multi-char set -> \"XYZ\"",      r, "XYZ"); free(r);
}

static int	count_words(char **a)
{
	int	i = 0;
	if (!a) return -1;
	while (a[i]) i++;
	return i;
}

static void	free_split(char **a)
{
	int	i = 0;
	if (!a) return;
	while (a[i]) free(a[i++]);
	free(a);
}

void	test_split(void)
{
	char	**r;
	print_header("split");

	r = ft_split("hello world foo", ' ');
	CHECK("3 words: count=3",                   r && count_words(r) == 3);
	if (r) {
		CHECK("r[0]=\"hello\"",                 strcmp(r[0], "hello") == 0);
		CHECK("r[1]=\"world\"",                 strcmp(r[1], "world") == 0);
		CHECK("r[2]=\"foo\"",                   strcmp(r[2], "foo") == 0);
		CHECK("r[3]==NULL",                     r[3] == NULL);
		free_split(r);
	}
	r = ft_split("  hello  world  ", ' ');
	CHECK("consecutive delimiters: 2 words",    r && count_words(r) == 2);
	if (r) { CHECK("r[0]=\"hello\"", strcmp(r[0],"hello")==0); free_split(r); }
	r = ft_split("", ' ');
	CHECK("empty string: 0 words",              r && count_words(r) == 0);
	CHECK("empty string: r[0]==NULL",           r && r[0] == NULL);
	free_split(r);
	r = ft_split("hello", 'x');
	CHECK("no delimiter: 1 word",               r && count_words(r) == 1);
	if (r) { CHECK("r[0]=\"hello\"", strcmp(r[0],"hello")==0); free_split(r); }
	r = ft_split("xxxxx", 'x');
	CHECK("only delimiters: 0 words",           r && count_words(r) == 0);
	free_split(r);
	r = ft_split(",hello,world", ',');
	CHECK("delimiter at start: 2 words",        r && count_words(r) == 2);
	if (r) { CHECK("r[0]=\"hello\"", strcmp(r[0],"hello")==0); free_split(r); }
	r = ft_split("hello,world,", ',');
	CHECK("delimiter at end: 2 words",          r && count_words(r) == 2);
	if (r) { CHECK("r[1]=\"world\"", strcmp(r[1],"world")==0); free_split(r); }
	r = ft_split("word", ' ');
	CHECK("single word: count=1",               r && count_words(r) == 1);
	free_split(r);
	r = ft_split("a b c", ' ');
	CHECK("a b c: 3 words",                     r && count_words(r) == 3);
	if (r) {
		CHECK("r[0]=\"a\"",                     strcmp(r[0],"a")==0);
		CHECK("r[1]=\"b\"",                     strcmp(r[1],"b")==0);
		CHECK("r[2]=\"c\"",                     strcmp(r[2],"c")==0);
		free_split(r);
	}
	r = ft_split("a:b:c:d", ':');
	CHECK("colon delimiter: 4 words",           r && count_words(r) == 4);
	free_split(r);
	r = ft_split("abc def", ' ');
	CHECK("r[0] nul-terminated",                r && r[0] && r[0][3] == '\0');
	CHECK("r[1] nul-terminated",                r && r[1] && r[1][3] == '\0');
	free_split(r);
	r = ft_split("a,b", ',');
	CHECK("a,b: 2 words",                       r && count_words(r) == 2);
	if (r) {
		CHECK("r[0]=\"a\"",                     strcmp(r[0],"a")==0);
		CHECK("r[1]=\"b\"",                     strcmp(r[1],"b")==0);
		free_split(r);
	}
	r = ft_split("   a   b   ", ' ');
	CHECK("many consecutive delimiters: 2",     r && count_words(r) == 2);
	free_split(r);
	r = ft_split("line1\nline2\nline3", '\n');
	CHECK("newline delimiter: 3 words",         r && count_words(r) == 3);
	if (r) { CHECK("r[0]=\"line1\"", strcmp(r[0],"line1")==0); free_split(r); }
}

void	test_itoa(void)
{
	char	*r;
	print_header("itoa");

	r = ft_itoa(0);    CHECK_STR("0",         r, "0");         free(r);
	r = ft_itoa(1);    CHECK_STR("1",         r, "1");         free(r);
	r = ft_itoa(-1);   CHECK_STR("-1",        r, "-1");        free(r);
	r = ft_itoa(9);    CHECK_STR("9",         r, "9");         free(r);
	r = ft_itoa(-9);   CHECK_STR("-9",        r, "-9");        free(r);
	r = ft_itoa(10);   CHECK_STR("10",        r, "10");        free(r);
	r = ft_itoa(-10);  CHECK_STR("-10",       r, "-10");       free(r);
	r = ft_itoa(42);   CHECK_STR("42",        r, "42");        free(r);
	r = ft_itoa(-42);  CHECK_STR("-42",       r, "-42");       free(r);
	r = ft_itoa(100);  CHECK_STR("100",       r, "100");       free(r);
	r = ft_itoa(999);  CHECK_STR("999",       r, "999");       free(r);
	r = ft_itoa(1000); CHECK_STR("1000",      r, "1000");      free(r);
	r = ft_itoa(-1000);CHECK_STR("-1000",     r, "-1000");     free(r);
	r = ft_itoa(2147483647);
	CHECK_STR("INT_MAX=2147483647",            r, "2147483647"); free(r);
	/* INT_MIN is the trickiest case — breaks naive -n implementations */
	r = ft_itoa(-2147483648);
	CHECK_STR("INT_MIN=-2147483648",           r, "-2147483648"); free(r);
	r = ft_itoa(-2147483647);
	CHECK_STR("-2147483647",                   r, "-2147483647"); free(r);
	r = ft_itoa(1000000);  CHECK_STR("1000000",  r, "1000000");  free(r);
	r = ft_itoa(-1000000); CHECK_STR("-1000000", r, "-1000000"); free(r);
	r = ft_itoa(123);
	CHECK("nul at r[3]",                       r && r[3] == '\0'); free(r);
	r = ft_itoa(-12);
	CHECK("nul at r[3]",                       r && r[3] == '\0'); free(r);
}

static char	fn_toupper_i(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z') return c - 32;
	return c;
}
static char	fn_addidx(unsigned int i, char c) { return (char)(c + (int)i); }
static char	fn_identity(unsigned int i, char c) { (void)i; return c; }
static char	fn_rot13(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z') return (char)('a' + (c - 'a' + 13) % 26);
	if (c >= 'A' && c <= 'Z') return (char)('A' + (c - 'A' + 13) % 26);
	return c;
}
static unsigned int	g_last_idx = 9999;
static char	fn_check_idx(unsigned int i, char c) { g_last_idx = i; return c; }

void	test_strmapi(void)
{
	char	*r;
	char	*orig;
	print_header("strmapi");

	r = ft_strmapi("hello", fn_toupper_i);
	CHECK_STR("toupper -> \"HELLO\"",          r, "HELLO"); free(r);
	r = ft_strmapi("WORLD", fn_identity);
	CHECK_STR("identity -> \"WORLD\"",          r, "WORLD"); free(r);
	r = ft_strmapi("", fn_toupper_i);
	CHECK_STR("empty -> \"\"",                  r, ""); free(r);
	/* a+0=a, b+1=c, c+2=e */
	r = ft_strmapi("abc", fn_addidx);
	CHECK_STR("add index: \"ace\"",             r, "ace"); free(r);
	r = ft_strmapi("Hello World", fn_rot13);
	CHECK_STR("rot13",                          r, "Uryyb Jbeyq"); free(r);
	/* index must be correct */
	r = ft_strmapi("abcde", fn_check_idx);
	CHECK("last index passed = 4",              g_last_idx == 4); free(r);
	r = ft_strmapi("a", fn_check_idx);
	CHECK("1 char: index = 0",                  g_last_idx == 0); free(r);
	/* original string must not be modified */
	orig = ft_strdup("hello");
	r = ft_strmapi(orig, fn_toupper_i);
	CHECK("original string unchanged",          strcmp(orig, "hello") == 0);
	free(r); free(orig);
	/* result must be a new allocation */
	orig = "hello";
	r = ft_strmapi(orig, fn_identity);
	CHECK("new string allocated",               r != orig); free(r);
	r = ft_strmapi("abc", fn_toupper_i);
	CHECK("nul at r[3]",                        r && r[3] == '\0'); free(r);
	r = ft_strmapi("a", fn_toupper_i);
	CHECK_STR("1 char -> \"A\"",                r, "A"); free(r);
	r = ft_strmapi("Hello World", fn_toupper_i);
	CHECK_STR("with space",                     r, "HELLO WORLD"); free(r);
}

static void	fn_upper_ip(unsigned int i, char *c)
{ (void)i; if (*c >= 'a' && *c <= 'z') *c -= 32; }
static void	fn_addidx_ip(unsigned int i, char *c) { *c = (char)(*c + (int)i); }
static void	fn_noop(unsigned int i, char *c) { (void)i; (void)c; }
static unsigned int	g_iter_idx = 9999;
static void	fn_check_idx_ip(unsigned int i, char *c) { (void)c; g_iter_idx = i; }

void	test_striteri(void)
{
	char	s[32];
	print_header("striteri");

	strcpy(s, "hello");
	ft_striteri(s, fn_upper_ip);
	CHECK("modifies in-place -> \"HELLO\"",     strcmp(s, "HELLO") == 0);

	strcpy(s, "WORLD");
	ft_striteri(s, fn_noop);
	CHECK("noop: no change",                    strcmp(s, "WORLD") == 0);

	strcpy(s, "");
	ft_striteri(s, fn_upper_ip);
	CHECK("empty: no crash",                    strcmp(s, "") == 0);

	/* a+0=a, b+1=c, c+2=e */
	strcpy(s, "abc");
	ft_striteri(s, fn_addidx_ip);
	CHECK("add index: \"ace\"",                 strcmp(s, "ace") == 0);

	strcpy(s, "hello");
	ft_striteri(s, fn_check_idx_ip);
	CHECK("last index = 4",                     g_iter_idx == 4);

	strcpy(s, "a");
	ft_striteri(s, fn_check_idx_ip);
	CHECK("1 char: index = 0",                  g_iter_idx == 0);

	strcpy(s, "xyz");
	ft_striteri(s, fn_upper_ip);
	CHECK("\"xyz\" -> \"XYZ\"",                 strcmp(s, "XYZ") == 0);

	strcpy(s, "a");
	ft_striteri(s, fn_upper_ip);
	CHECK("\"a\" -> \"A\"",                     s[0] == 'A' && s[1] == '\0');
}

void	test_putchar_fd(void)
{
	int		fds[2];
	char	buf[8];
	print_header("putchar_fd");

#define TCHAR(c, desc) do { \
	pipe(fds); ft_putchar_fd(c, fds[1]); close(fds[1]); \
	read(fds[0], buf, 1); close(fds[0]); \
	CHECK(desc, buf[0] == (char)(c)); \
} while (0)

	TCHAR('A',  "writes 'A'");
	TCHAR('z',  "writes 'z'");
	TCHAR('0',  "writes '0'");
	TCHAR('9',  "writes '9'");
	TCHAR('\n', "writes newline");
	TCHAR('\t', "writes tab");
	TCHAR('!',  "writes '!'");
	TCHAR(' ',  "writes space");
	TCHAR(0,    "writes NUL byte");
	TCHAR(127,  "writes DEL");
#undef TCHAR
	pipe(fds); ft_putchar_fd('X', fds[1]); close(fds[1]);
	ssize_t n = read(fds[0], buf, 8); close(fds[0]);
	CHECK("writes exactly 1 byte",              n == 1);
}

void	test_putstr_fd(void)
{
	int		fds[2];
	char	buf[64];
	ssize_t	n;
	print_header("putstr_fd");

	pipe(fds); ft_putstr_fd("Hello", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("\"Hello\": correct",                 strcmp(buf, "Hello") == 0);
	CHECK("\"Hello\": 5 bytes",                 n == 5);

	pipe(fds); ft_putstr_fd("", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]);
	CHECK("empty: 0 bytes",                     n == 0);

	pipe(fds); ft_putstr_fd("42", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("\"42\": correct",                    strcmp(buf, "42") == 0);
	CHECK("\"42\": 2 bytes",                    n == 2);

	pipe(fds); ft_putstr_fd("hi", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]);
	CHECK("does not write nul: 2 bytes",        n == 2);

	pipe(fds); ft_putstr_fd("Hello World", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("\"Hello World\": correct",           strcmp(buf, "Hello World") == 0);

	pipe(fds); ft_putstr_fd("a", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("1 char: correct",                    strcmp(buf, "a") == 0);
	CHECK("1 char: 1 byte",                     n == 1);
}

void	test_putendl_fd(void)
{
	int		fds[2];
	char	buf[64];
	ssize_t	n;
	print_header("putendl_fd");

	pipe(fds); ft_putendl_fd("Hello", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("\"Hello\\n\": correct",              strcmp(buf, "Hello\n") == 0);
	CHECK("\"Hello\\n\": 6 bytes",              n == 6);

	pipe(fds); ft_putendl_fd("", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("empty: only newline",                strcmp(buf, "\n") == 0);
	CHECK("empty: 1 byte",                      n == 1);

	pipe(fds); ft_putendl_fd("42", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("\"42\\n\": correct",                 strcmp(buf, "42\n") == 0);
	CHECK("\"42\\n\": 3 bytes",                 n == 3);

	pipe(fds); ft_putendl_fd("a", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("\"a\\n\": correct",                  strcmp(buf, "a\n") == 0);

	pipe(fds); ft_putendl_fd("Hi", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]);
	CHECK("last byte is '\\n'",                 buf[n-1] == '\n');
}

void	test_putnbr_fd(void)
{
	int		fds[2];
	char	buf[64];
	ssize_t	n;
	print_header("putnbr_fd");

#define TNBR(val, exp) do { \
	pipe(fds); ft_putnbr_fd(val, fds[1]); close(fds[1]); \
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0'; \
	CHECK(#val " -> \"" exp "\"", strcmp(buf, exp) == 0); \
} while (0)

	TNBR(0,           "0");
	TNBR(1,           "1");
	TNBR(-1,          "-1");
	TNBR(9,           "9");
	TNBR(-9,          "-9");
	TNBR(10,          "10");
	TNBR(-10,         "-10");
	TNBR(42,          "42");
	TNBR(-42,         "-42");
	TNBR(100,         "100");
	TNBR(-100,        "-100");
	TNBR(999,         "999");
	TNBR(1000,        "1000");
	TNBR(-1000,       "-1000");
	TNBR(2147483647,  "2147483647");
	TNBR(-2147483648, "-2147483648");
	TNBR(1000000,     "1000000");
	TNBR(-1000000,    "-1000000");
#undef TNBR
}
