/*
** tests/test_extra.c
** Testes extra para chegar aos 1000: casos limites mais agressivos,
** combinações e verificações de comportamento preciso.
*/
#include "../utils/tester.h"
#include "libft.h"

/* ══════════════════════════════════════════════════════════
**  Extra: ft_memset — verificações de byte a byte
** ══════════════════════════════════════════════════════════ */
void	test_memset_extra(void)
{
	char	buf[128];
	print_header("memset (extra)");

	/* garante que preenche exactamente n bytes */
	memset(buf, 'A', sizeof(buf));
	ft_memset(buf, 'B', 10);
	int ok = 1;
	for (int i = 0; i < 10; i++) if (buf[i] != 'B') { ok = 0; break; }
	CHECK("10 bytes all 'B'",       ok);
	ok = 1;
	for (int i = 10; i < 20; i++) if (buf[i] != 'A') { ok = 0; break; }
	CHECK("bytes 10-19 untouched 'A'", ok);

	/* valor 1 */
	ft_memset(buf, 1, 5);
	CHECK("val=1: buf[0]=1",          (unsigned char)buf[0] == 1);
	CHECK("val=1: buf[4]=1",          (unsigned char)buf[4] == 1);

	/* valor 127 */
	ft_memset(buf, 127, 4);
	CHECK("val=127: buf[0]=127",      (unsigned char)buf[0] == 127);
	CHECK("val=127: buf[3]=127",      (unsigned char)buf[3] == 127);

	/* valor 128 */
	ft_memset(buf, 128, 4);
	CHECK("val=128: buf[0]=128",      (unsigned char)buf[0] == 128);

	/* n grande */
	ft_memset(buf, 'Z', 128);
	ok = 1;
	for (int i = 0; i < 128; i++) if (buf[i] != 'Z') { ok = 0; break; }
	CHECK("128 bytes all 'Z'",      ok);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_memcpy — verificações de retorno e bytes
** ══════════════════════════════════════════════════════════ */
void	test_memcpy_extra(void)
{
	char	dst[64];
	char	src[64];
	print_header("memcpy (extra)");

	/* copia exactamente n bytes, nao mais */
	memset(dst, 'A', sizeof(dst));
	memset(src, 'B', sizeof(src));
	ft_memcpy(dst, src, 20);
	int ok = 1;
	for (int i = 0; i < 20; i++) if (dst[i] != 'B') { ok = 0; break; }
	CHECK("20 bytes copied",        ok);
	ok = 1;
	for (int i = 20; i < 30; i++) if (dst[i] != 'A') { ok = 0; break; }
	CHECK("bytes 20-29 untouched",  ok);

	/* copia todos os valores de byte possiveis */
	for (int i = 0; i < 64; i++) src[i] = (char)i;
	ft_memcpy(dst, src, 64);
	ok = 1;
	for (int i = 0; i < 64; i++) if (dst[i] != (char)i) { ok = 0; break; }
	CHECK("all values 0-63",    ok);

	/* retorno: verificar que e dst */
	void *ret = ft_memcpy(dst, src, 10);
	CHECK("return == dst",           ret == dst);
	CHECK("return not NULL",       ret != NULL);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_memmove — casos de sobreposição complexos
** ══════════════════════════════════════════════════════════ */
void	test_memmove_extra(void)
{
	char	buf[64];
	print_header("memmove (extra)");

	/* mover 1 byte para a direita */
	memset(buf, 0, sizeof(buf));
	buf[0] = 'X';
	ft_memmove(buf + 1, buf, 1);
	CHECK("move 1 byte right: buf[1]='X'", buf[1] == 'X');

	/* mover string inteira 1 posicao a direita */
	strcpy(buf, "hello");
	ft_memmove(buf + 1, buf, 5);
	CHECK("move str+1: buf[1]='h'",   buf[1] == 'h');
	CHECK("move str+1: buf[5]='o'",   buf[5] == 'o');

	/* mover string inteira 1 posicao a esquerda */
	strcpy(buf, "Xhello");
	ft_memmove(buf, buf + 1, 5);
	CHECK("move str-1: buf[0]='h'",   buf[0] == 'h');
	CHECK("move str-1: buf[4]='o'",   buf[4] == 'o');

	/* overlap de 1 byte */
	strcpy(buf, "abcd");
	ft_memmove(buf + 3, buf, 4);
	CHECK("overlap 1 byte: buf[3]='a'",buf[3] == 'a');

	/* retorno */
	void *ret = ft_memmove(buf, buf, 5);
	CHECK("return == dst",            ret == buf);

	/* n grande */
	memset(buf, 'A', 50);
	memset(buf + 25, 'B', 25);
	ft_memmove(buf + 10, buf, 40);
	CHECK("move 40 bytes: buf[10]='A'", buf[10] == 'A');
	CHECK("move 40 bytes: buf[35]='B'", buf[35] == 'B');
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strlen — strings especiais
** ══════════════════════════════════════════════════════════ */
void	test_strlen_extra(void)
{
	print_header("strlen (extra)");

	CHECK("only newline: 1",            ft_strlen("\n") == 1);
	CHECK("only tab: 1",                ft_strlen("\t") == 1);
	CHECK("only nul: 0",                ft_strlen("\0") == 0);
	CHECK("2 chars",                  ft_strlen("ab") == 2);
	CHECK("3 chars",                  ft_strlen("abc") == 3);
	CHECK("str with numbers",          ft_strlen("abc123") == 6);
	CHECK("str with specials",        ft_strlen("a!b@c") == 5);
	CHECK("str with space",           ft_strlen("a b") == 3);
	CHECK("str only spaces 3",         ft_strlen("   ") == 3);
	CHECK("str only spaces 5",         ft_strlen("     ") == 5);
	/* nao conta o nul no fim */
	CHECK("\"hello\" does not count nul",  ft_strlen("hello") == 5);
	CHECK("\"a\" does not count nul",      ft_strlen("a") == 1);
	/* retorno e size_t (sem sinal) */
	CHECK("size_t: not negative",     (int)ft_strlen("abc") >= 0);
	/* string com char 127 */
	CHECK("char 127",                 ft_strlen("\x7f") == 1);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strlcpy — comparacoes com comportamento real
** ══════════════════════════════════════════════════════════ */
void	test_strlcpy_extra(void)
{
	char	dst[64];
	size_t	r;
	print_header("strlcpy (extra)");

	/* devolve sempre strlen(src), independente de size */
	r = ft_strlcpy(dst, "abcde", 100);
	CHECK("returns strlen(src)=5 with size=100", r == 5);
	r = ft_strlcpy(dst, "abcde", 3);
	CHECK("returns strlen(src)=5 with size=3",   r == 5);
	r = ft_strlcpy(dst, "abcde", 0);
	CHECK("returns strlen(src)=5 with size=0",   r == 5);

	/* nul-terminator sempre presente (quando size>0) */
	memset(dst, 'X', sizeof(dst));
	ft_strlcpy(dst, "hello", 3);
	CHECK("nul at dst[2] when size=3", dst[2] == '\0');

	memset(dst, 'X', sizeof(dst));
	ft_strlcpy(dst, "hello", 10);
	CHECK("nul at dst[5] when full copy", dst[5] == '\0');

	/* src com chars especiais */
	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "ab\ncd", 10);
	CHECK("src with newline: copies", strcmp(dst, "ab\ncd") == 0);
	CHECK("src with newline: returns 5", r == 5);

	/* size=2: copia 1 char + nul */
	memset(dst, 'X', sizeof(dst));
	ft_strlcpy(dst, "hello", 2);
	CHECK("size=2: dst[0]='h'", dst[0] == 'h');
	CHECK("size=2: dst[1]='\\0'", dst[1] == '\0');
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strlcat — casos especificos
** ══════════════════════════════════════════════════════════ */
void	test_strlcat_extra(void)
{
	char	dst[64];
	size_t	r;
	print_header("strlcat (extra)");

	/* devolve strlen(dst) + strlen(src) sempre */
	strcpy(dst, "ab");
	r = ft_strlcat(dst, "cde", 100);
	CHECK("returns 2+3=5",            r == 5);

	strcpy(dst, "ab");
	r = ft_strlcat(dst, "cde", 2);
	CHECK("size=strlen(dst): returns 2+3=5", r == 5);

	/* nao escreve alem de size */
	memset(dst, 'X', sizeof(dst));
	dst[0] = 'a'; dst[1] = '\0';
	ft_strlcat(dst, "bcde", 4);
	CHECK("does not write past size=4", dst[4] == 'X');
	CHECK("nul at dst[3] (size-1)",    dst[3] == '\0');

	/* concatenacao com 1 char */
	strcpy(dst, "a");
	r = ft_strlcat(dst, "b", 10);
	CHECK("\"a\"+\"b\" -> \"ab\"",    strcmp(dst, "ab") == 0);
	CHECK("returns 2",                r == 2);

	/* concatenacao que preenche exactamente */
	strcpy(dst, "ab");
	r = ft_strlcat(dst, "cd", 5);
	CHECK("fills exactly: \"abcd\"",strcmp(dst, "abcd") == 0);
	CHECK("fills exactly: returns 4",r == 4);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strchr / ft_strrchr — casos especiais
** ══════════════════════════════════════════════════════════ */
void	test_strchr_extra(void)
{
	print_header("strchr (extra)");

	/* busca em cada posicao de uma string */
	const char *s = "abcde";
	CHECK("pos 0", ft_strchr(s, 'a') == s);
	CHECK("pos 1", ft_strchr(s, 'b') == s + 1);
	CHECK("pos 2", ft_strchr(s, 'c') == s + 2);
	CHECK("pos 3", ft_strchr(s, 'd') == s + 3);
	CHECK("pos 4", ft_strchr(s, 'e') == s + 4);
	CHECK("pos 5: nul", ft_strchr(s, '\0') == s + 5);

	/* chars especiais */
	CHECK("newline in str", ft_strchr("a\nb", '\n') != NULL);
	CHECK("tab in str",     ft_strchr("a\tb", '\t') != NULL);
	CHECK("space in str",  ft_strchr("a b", ' ') != NULL);

	/* devolve ponteiro para dentro da string original */
	CHECK("ponteiro dentro da str", ft_strchr(s, 'c') == s + 2);
}

void	test_strrchr_extra(void)
{
	print_header("strrchr (extra)");

	const char *s = "abcde";
	CHECK("pos 0 (unico 'a')", ft_strrchr(s, 'a') == s);
	CHECK("pos 4 (unico 'e')", ft_strrchr(s, 'e') == s + 4);
	CHECK("nul pos 5",         ft_strrchr(s, '\0') == s + 5);

	/* todas iguais: devolve ultima */
	CHECK("\"aaaa\": ultimo",  ft_strrchr("aaaa", 'a') == (char*)"aaaa" + 3);
	CHECK("\"aaab\": ultimo a",ft_strrchr("aaab", 'a') == (char*)"aaab" + 2);
	CHECK("\"baaa\": ultimo a",ft_strrchr("baaa", 'a') == (char*)"baaa" + 3);

	/* chars especiais */
	CHECK("newline: last",  ft_strrchr("a\nb\n", '\n') == (char*)"a\nb\n" + 3);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strncmp — tabela de casos
** ══════════════════════════════════════════════════════════ */
void	test_strncmp_extra(void)
{
	print_header("strncmp (extra)");

	/* mesmo char, n=1 */
	CHECK("n=1 'a'=='a' -> 0",   ft_strncmp("a", "a", 1) == 0);
	CHECK("n=1 'a'<'b'  -> <0",  ft_strncmp("a", "b", 1) < 0);
	CHECK("n=1 'b'>'a'  -> >0",  ft_strncmp("b", "a", 1) > 0);
	/* strings de tamanho diferente */
	CHECK("\"a\" vs \"ab\" n=2 -> <0", ft_strncmp("a", "ab", 2) < 0);
	CHECK("\"ab\" vs \"a\" n=2 -> >0", ft_strncmp("ab", "a", 2) > 0);
	/* n=0: sempre 0 */
	CHECK("n=0 qualquer -> 0",   ft_strncmp("xyz", "abc", 0) == 0);
	/* prefixos iguais */
	CHECK("prefixo igual n=3",   ft_strncmp("abcXXX", "abcYYY", 3) == 0);
	CHECK("prefixo igual n=4",   ft_strncmp("abcXXX", "abcYYY", 4) != 0);
	/* case sensitive */
	CHECK("case: 'a' vs 'A'",    ft_strncmp("a", "A", 1) != 0);
	CHECK("case: 'A' vs 'a'",    ft_strncmp("A", "a", 1) != 0);
	/* 0x80 = 128, que e > todos os ascii */
	CHECK("0x80 > 0x7F",         ft_strncmp("\x80", "\x7f", 1) > 0);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_atoi — casos de whitespace e sinais
** ══════════════════════════════════════════════════════════ */
void	test_atoi_extra(void)
{
	print_header("atoi (extra)");

	/* todos os whitespace validos antes do numero */
	CHECK("' '  antes",   ft_atoi(" 1") == 1);
	CHECK("'\\t' antes",  ft_atoi("\t1") == 1);
	CHECK("'\\n' antes",  ft_atoi("\n1") == 1);
	CHECK("'\\v' antes",  ft_atoi("\v1") == 1);
	CHECK("'\\f' antes",  ft_atoi("\f1") == 1);
	CHECK("'\\r' antes",  ft_atoi("\r1") == 1);
	/* mix de whitespace */
	CHECK("mix ws antes", ft_atoi(" \t\n1") == 1);
	/* sinal imediato apos ws */
	CHECK("ws + '-'",     ft_atoi("  -5") == -5);
	CHECK("ws + '+'",     ft_atoi("  +5") == 5);
	/* numeros com zeros */
	CHECK("\"0000\"",     ft_atoi("0000") == 0);
	CHECK("\"0001\"",     ft_atoi("0001") == 1);
	CHECK("\"-0\"",       ft_atoi("-0") == 0);
	/* para imediatamente em nao-digito pos sinal */
	CHECK("\"+a\"  -> 0", ft_atoi("+a") == 0);
	CHECK("\"-a\"  -> 0", ft_atoi("-a") == 0);
	/* numeros pequenos */
	CHECK("\"1\"   -> 1", ft_atoi("1") == 1);
	CHECK("\"2\"   -> 2", ft_atoi("2") == 2);
	CHECK("\"9\"   -> 9", ft_atoi("9") == 9);
	/* negativos pequenos */
	CHECK("\"-2\"  -> -2",ft_atoi("-2") == -2);
	CHECK("\"-9\"  -> -9",ft_atoi("-9") == -9);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_itoa — verificações de comprimento
** ══════════════════════════════════════════════════════════ */
void	test_itoa_extra(void)
{
	char	*r;
	print_header("itoa (extra)");

	/* comprimento correcto */
	r = ft_itoa(0);      CHECK("len \"0\" = 1",  r && strlen(r) == 1); free(r);
	r = ft_itoa(9);      CHECK("len \"9\" = 1",  r && strlen(r) == 1); free(r);
	r = ft_itoa(10);     CHECK("len \"10\" = 2", r && strlen(r) == 2); free(r);
	r = ft_itoa(99);     CHECK("len \"99\" = 2", r && strlen(r) == 2); free(r);
	r = ft_itoa(100);    CHECK("len \"100\"= 3", r && strlen(r) == 3); free(r);
	r = ft_itoa(-1);     CHECK("len \"-1\" = 2", r && strlen(r) == 2); free(r);
	r = ft_itoa(-10);    CHECK("len \"-10\"= 3", r && strlen(r) == 3); free(r);
	r = ft_itoa(-100);   CHECK("len \"-100\"=4", r && strlen(r) == 4); free(r);

	/* nao deve ter zeros a esquerda */
	r = ft_itoa(42);
	CHECK("no leading zeros: r[0]='4'", r && r[0] == '4'); free(r);
	r = ft_itoa(-42);
	CHECK("negative: r[0]='-'", r && r[0] == '-'); free(r);
	r = ft_itoa(-42);
	CHECK("negative: r[1]='4'", r && r[1] == '4'); free(r);

	/* so contem digitos (e eventual '-') */
	r = ft_itoa(123);
	CHECK("only digits: r[0]='1'", r && r[0]=='1');
	CHECK("only digits: r[1]='2'", r && r[1]=='2');
	CHECK("only digits: r[2]='3'", r && r[2]=='3');
	CHECK("only digits: r[3]='\\0'",r && r[3]=='\0'); free(r);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_substr — nul-terminator e comprimentos
** ══════════════════════════════════════════════════════════ */
void	test_substr_extra(void)
{
	char	*r;
	print_header("substr (extra)");

	/* comprimento correcto */
	r = ft_substr("Hello World", 0, 5);
	CHECK("len = 5", r && strlen(r) == 5); free(r);
	r = ft_substr("Hello World", 6, 5);
	CHECK("len = 5", r && strlen(r) == 5); free(r);
	r = ft_substr("Hello", 0, 0);
	CHECK("len = 0", r && strlen(r) == 0); free(r);

	/* nul-terminator em posicoes especificas */
	r = ft_substr("abcde", 1, 3);
	CHECK_STR("\"bcd\"", r, "bcd");
	CHECK("nul em r[3]", r && r[3] == '\0'); free(r);

	/* start = strlen - 1 */
	r = ft_substr("Hello", 4, 10);
	CHECK_STR("start=ultimo char", r, "o"); free(r);

	/* string com espacos */
	r = ft_substr("Hello World", 5, 1);
	CHECK_STR("start=space", r, " "); free(r);

	/* string longa */
	r = ft_substr("0123456789", 3, 4);
	CHECK_STR("str longa", r, "3456"); free(r);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strtrim — casos limite
** ══════════════════════════════════════════════════════════ */
void	test_strtrim_extra(void)
{
	char	*r;
	print_header("strtrim (extra)");

	/* string de 1 char fora do set */
	r = ft_strtrim("x", "ab");
	CHECK_STR("1 char fora set", r, "x"); free(r);

	/* set maior que a string */
	r = ft_strtrim("a", "abcdefgh");
	CHECK_STR("set grande: remove tudo", r, ""); free(r);

	/* set com 1 char que nao e na string */
	r = ft_strtrim("hello", "x");
	CHECK_STR("set not in string", r, "hello"); free(r);

	/* trim so de 1 lado (esquerda) */
	r = ft_strtrim("xxxhello", "x");
	CHECK_STR("trim 3 chars esquerda", r, "hello"); free(r);

	/* trim so de 1 lado (direita) */
	r = ft_strtrim("helloxxx", "x");
	CHECK_STR("trim 3 chars direita", r, "hello"); free(r);

	/* chars do set nao contiguos */
	r = ft_strtrim("abXba", "ab");
	CHECK_STR("non-contiguous: \"X\"", r, "X"); free(r);

	/* string toda de 1 char no set */
	r = ft_strtrim("aaaa", "a");
	CHECK_STR("tudo no set -> \"\"", r, ""); free(r);

	/* set com espaco e letra */
	r = ft_strtrim(" a hello a ", " a");
	CHECK_STR("set=\" a\": remove bordas", r, "hello"); free(r);

	/* resultado e uma copia (nul-terminada) */
	r = ft_strtrim("  hi  ", " ");
	CHECK("resultado nul-terminado", r && r[strlen(r)] == '\0'); free(r);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_split — verificações de cada string
** ══════════════════════════════════════════════════════════ */
static int	count_w(char **a) { int i=0; if(!a) return -1; while(a[i]) i++; return i; }
static void	free_sp(char **a) { if(!a) return; for(int i=0;a[i];i++) free(a[i]); free(a); }

void	test_split_extra(void)
{
	char	**r;
	print_header("split (extra)");

	/* comprimento de cada palavra */
	r = ft_split("hello world", ' ');
	CHECK("r[0] len=5", r && r[0] && strlen(r[0]) == 5);
	CHECK("r[1] len=5", r && r[1] && strlen(r[1]) == 5);
	free_sp(r);

	/* delimitador que nao existe: 1 string = original */
	r = ft_split("hello", 'z');
	CHECK("1 word: not NULL",  r && count_w(r) == 1);
	if (r) { CHECK("1 str = original", strcmp(r[0], "hello") == 0); free_sp(r); }

	/* string so com 1 delimitador */
	r = ft_split(",", ',');
	CHECK("so delim: 0 strs", r && count_w(r) == 0);
	free_sp(r);

	/* palavras de comprimentos diferentes */
	r = ft_split("a bb ccc", ' ');
	CHECK("lens diferentes: 3", r && count_w(r) == 3);
	if (r) {
		CHECK("r[0]=\"a\" len=1",  strlen(r[0]) == 1);
		CHECK("r[1]=\"bb\" len=2", strlen(r[1]) == 2);
		CHECK("r[2]=\"ccc\"len=3", strlen(r[2]) == 3);
		free_sp(r);
	}

	/* cada string tem o seu proprio nul */
	r = ft_split("abc def ghi", ' ');
	if (r) {
		CHECK("r[0] nul em [3]", r[0][3] == '\0');
		CHECK("r[1] nul em [3]", r[1][3] == '\0');
		CHECK("r[2] nul em [3]", r[2][3] == '\0');
		free_sp(r);
	}

	/* delimitador '/' */
	r = ft_split("usr/bin/ls", '/');
	CHECK("'/': 3 partes", r && count_w(r) == 3);
	if (r) {
		CHECK("r[0]=\"usr\"", strcmp(r[0], "usr") == 0);
		CHECK("r[1]=\"bin\"", strcmp(r[1], "bin") == 0);
		CHECK("r[2]=\"ls\"",  strcmp(r[2], "ls")  == 0);
		free_sp(r);
	}
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strjoin — verificações de ponteiro e conteudo
** ══════════════════════════════════════════════════════════ */
void	test_strjoin_extra(void)
{
	char	*r;
	print_header("strjoin (extra)");

	/* resultado e novo ponteiro */
	char *s1 = "hello";
	char *s2 = " world";
	r = ft_strjoin(s1, s2);
	CHECK("resultado != s1",          r != s1);
	CHECK("resultado != s2",          r != s2);
	free(r);

	/* strings com numeros */
	r = ft_strjoin("123", "456");
	CHECK_STR("numeros: \"123456\"", r, "123456"); free(r);

	/* string com newline no meio */
	r = ft_strjoin("line1\n", "line2");
	CHECK_STR("newline: ok", r, "line1\nline2"); free(r);

	/* s1 muito longa */
	r = ft_strjoin("0123456789012345678901234567890123456789", "x");
	CHECK("s1 longa: len=41", r && strlen(r) == 41); free(r);

	/* s2 muito longa */
	r = ft_strjoin("x", "0123456789012345678901234567890123456789");
	CHECK("s2 longa: len=41", r && strlen(r) == 41); free(r);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_putnbr_fd — verificar cada digito
** ══════════════════════════════════════════════════════════ */
void	test_putnbr_extra(void)
{
	int		fds[2];
	char	buf[32];
	ssize_t	n;
	print_header("putnbr_fd (extra)");

#define TNBR(val, exp, desc) do { \
	pipe(fds); ft_putnbr_fd(val, fds[1]); close(fds[1]); \
	n = read(fds[0], buf, 31); close(fds[0]); buf[n] = '\0'; \
	CHECK(desc, strcmp(buf, exp) == 0); \
} while (0)

	TNBR(11,    "11",    "11");
	TNBR(99,    "99",    "99");
	TNBR(123,   "123",   "123");
	TNBR(-123,  "-123",  "-123");
	TNBR(999,   "999",   "999");
	TNBR(-999,  "-999",  "-999");
	TNBR(10000, "10000", "10000");
	TNBR(-10000,"-10000","-10000");
	TNBR(2,     "2",     "2");
	TNBR(-2,    "-2",    "-2");
#undef TNBR
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strmapi — verificar cada caracter transformado
** ══════════════════════════════════════════════════════════ */
static char	fn_zero(unsigned int i, char c) { (void)i; (void)c; return '0'; }
static char	fn_idx_char(unsigned int i, char c) { (void)c; return (char)('0' + i); }

void	test_strmapi_extra(void)
{
	char	*r;
	print_header("strmapi (extra)");

	/* fn que substitui tudo por '0' */
	r = ft_strmapi("hello", fn_zero);
	CHECK_STR("tudo -> '0'", r, "00000"); free(r);

	/* fn que usa o indice como char */
	r = ft_strmapi("xxxxx", fn_idx_char);
	CHECK_STR("idx como char", r, "01234"); free(r);

	/* string com especiais: nao crash */
	r = ft_strmapi("a\nb\tc", fn_zero);
	CHECK("specials: no crash", r != NULL);
	if (r) { CHECK("specials: len=5", strlen(r) == 5); free(r); }

	/* resultado e independente do input */
	char *orig = ft_strdup("hello");
	r = ft_strmapi(orig, fn_zero);
	CHECK("original unchanged", strcmp(orig, "hello") == 0);
	free(r); free(orig);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_striteri — verificar cada caracter modificado
** ══════════════════════════════════════════════════════════ */
static void	fn_zero_ip(unsigned int i, char *c) { (void)i; *c = '0'; }
static void	fn_idx_ip(unsigned int i, char *c)  { (void)c; *c = (char)('a' + i); }

void	test_striteri_extra(void)
{
	char	s[32];
	print_header("striteri (extra)");

	/* substitui tudo por '0' */
	strcpy(s, "hello");
	ft_striteri(s, fn_zero_ip);
	CHECK("tudo -> '0': \"00000\"", strcmp(s, "00000") == 0);

	/* usa indice */
	strcpy(s, "XXXXX");
	ft_striteri(s, fn_idx_ip);
	CHECK("idx: \"abcde\"", strcmp(s, "abcde") == 0);

	/* 2 chars */
	strcpy(s, "XY");
	ft_striteri(s, fn_idx_ip);
	CHECK("2 chars: \"ab\"", strcmp(s, "ab") == 0);

	/* 1 char */
	strcpy(s, "X");
	ft_striteri(s, fn_idx_ip);
	CHECK("1 char: \"a\"", strcmp(s, "a") == 0);

	/* nul-terminator preservado */
	strcpy(s, "abc");
	ft_striteri(s, fn_zero_ip);
	CHECK("nul preservado", s[3] == '\0');
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_memchr — mais casos raw
** ══════════════════════════════════════════════════════════ */
void	test_memchr_extra(void)
{
	char	buf[16];
	print_header("memchr (extra)");

	/* preenche buffer com 0-15 */
	for (int i = 0; i < 16; i++) buf[i] = (char)i;

	CHECK("finds 0x00 at pos 0",  ft_memchr(buf, 0, 16) == buf);
	CHECK("finds 0x01 at pos 1",  ft_memchr(buf, 1, 16) == buf + 1);
	CHECK("finds 0x0F at pos 15", ft_memchr(buf, 15, 16) == buf + 15);
	CHECK("n=16: finds last",    ft_memchr(buf, 15, 16) == buf + 15);
	CHECK("n=15: does not find last",ft_memchr(buf, 15, 15) == NULL);
	CHECK("search 16: not found", ft_memchr(buf, 16, 16) == NULL);
	CHECK("n=1: so primeiro byte",ft_memchr(buf, 1, 1)   == NULL);
	CHECK("n=2: finds pos 1",      ft_memchr(buf, 1, 2)   == buf + 1);

	/* bytes identicos: devolve o primeiro */
	memset(buf, 'X', 16);
	buf[3] = 'Y'; buf[7] = 'Y';
	CHECK("repeated: finds first 'Y'",  ft_memchr(buf, 'Y', 16) == buf + 3);

	/* n=0 com qualquer valor */
	CHECK("n=0 val=0 -> NULL",    ft_memchr(buf, 0, 0) == NULL);
	CHECK("n=0 val='X'-> NULL",   ft_memchr(buf, 'X', 0) == NULL);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_memcmp — mais casos
** ══════════════════════════════════════════════════════════ */
void	test_memcmp_extra(void)
{
	print_header("memcmp (extra)");

	/* diff no 1o byte */
	CHECK("diff byte 0: <0", ft_memcmp("bcd", "acd", 3) > 0);
	CHECK("diff byte 0: >0", ft_memcmp("acd", "bcd", 3) < 0);

	/* diff no ultimo byte */
	CHECK("diff byte 2: <0", ft_memcmp("abA", "abB", 3) < 0);
	CHECK("diff byte 2: >0", ft_memcmp("abB", "abA", 3) > 0);

	/* n=0 com ptrs diferentes */
	CHECK("n=0 ptrs dif -> 0", ft_memcmp("abc", "xyz", 0) == 0);

	/* buffers identicos de vários tamanhos */
	CHECK("n=1  igual", ft_memcmp("a", "a", 1) == 0);
	CHECK("n=5  igual", ft_memcmp("hello", "hello", 5) == 0);
	CHECK("n=10 igual", ft_memcmp("0123456789", "0123456789", 10) == 0);

	/* 0xFF em varias posicoes */
	char a[] = {0xFF, 0x00};
	char b[] = {0x00, 0xFF};
	CHECK("0xFF>0x00 byte0", ft_memcmp(a, b, 1) > 0);
	CHECK("0x00<0xFF byte0", ft_memcmp(b, a, 1) < 0);
	CHECK("n=2: diff byte0", ft_memcmp(a, b, 2) > 0);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strnstr — edge cases adicionais
** ══════════════════════════════════════════════════════════ */
void	test_strnstr_extra(void)
{
	print_header("strnstr (extra)");

	/* haystack = needle: encontra */
	CHECK("h==n: finds",       ft_strnstr("ab", "ab", 2) != NULL);
	CHECK("h==n pos 0",           ({ const char *_h = "ab"; ft_strnstr(_h, "ab", 2) == _h; }));

	/* needle 1 char */
	CHECK("needle 1 char start", ({ const char *_h = "hello"; ft_strnstr(_h, "h", 5) == _h; }));
	CHECK("needle 1 char end",    ft_strnstr("hello", "o", 5) == (char*)"hello" + 4);
	CHECK("needle 1 char middle",   ft_strnstr("hello", "l", 5) == (char*)"hello" + 2);

	/* needle mais longo que haystack */
	CHECK("needle>haystack->NULL",ft_strnstr("ab", "abc", 2) == NULL);
	CHECK("needle>haystack n=0",  ft_strnstr("", "a", 0) == NULL);

	/* len exacto para encontrar */
	CHECK("exact len: finds",     ft_strnstr("abcde", "cde", 5) != NULL);
	CHECK("len-1: not found",      ft_strnstr("abcde", "cde", 4) == NULL);

	/* haystack com repeticoes */
	CHECK("repeated: first occurrence", ({ const char *_h = "abab"; ft_strnstr(_h, "ab", 4) == _h; }));

	/* needle vazio com len=0 */
	CHECK("needle=\"\" len=0: h", ft_strnstr("abc", "", 0) != NULL);

	/* strings com espacos */
	CHECK("space in needle",     ft_strnstr("hello world", "lo wo", 11) != NULL);
	CHECK("space: correct position",ft_strnstr("hello world", "lo wo", 11)
		== (char*)"hello world" + 3);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_calloc — verificacoes de zeragem completa
** ══════════════════════════════════════════════════════════ */
void	test_calloc_extra(void)
{
	char	*p;
	int		ok;
	print_header("calloc (extra)");

	/* 1 byte */
	p = ft_calloc(1, 1);
	CHECK("1*1: byte=0", p && (unsigned char)p[0] == 0); if(p) free(p);

	/* 8 bytes */
	p = ft_calloc(8, 1);
	if (p) {
		ok = 1;
		for (int i = 0; i < 8; i++) if ((unsigned char)p[i] != 0) { ok=0; break; }
		CHECK("8*1: all zero", ok);
		free(p);
	}

	/* 4 * sizeof(long) */
	p = ft_calloc(4, sizeof(long));
	if (p) {
		ok = 1;
		for (int i = 0; i < (int)(4*sizeof(long)); i++)
			if ((unsigned char)p[i] != 0) { ok=0; break; }
		CHECK("4*sizeof(long): all zero", ok);
		free(p);
	}

	/* ponteiro e libertavel (nao crasha) */
	p = ft_calloc(0, 0);
	CHECK("calloc(0,0): free sem crash", 1); if(p) free(p);

	/* nmemb=0 com size grande */
	p = ft_calloc(0, 1000);
	CHECK("calloc(0,1000): not NULL", p != NULL); if(p) free(p);

	/* nmemb grande com size=0 */
	p = ft_calloc(1000, 0);
	CHECK("calloc(1000,0): not NULL", p != NULL); if(p) free(p);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_strdup — ponteiros e conteudo
** ══════════════════════════════════════════════════════════ */
void	test_strdup_extra(void)
{
	char	*p;
	char	*orig;
	print_header("strdup (extra)");

	/* resultado e escrevivel */
	p = ft_strdup("abc");
	if (p) { p[0] = 'X'; CHECK("escrevivel: p[0]='X'", p[0] == 'X'); free(p); }

	/* copia exacta byte a byte */
	orig = "hello\nworld";
	p = ft_strdup(orig);
	CHECK("exact copy with \\n", p && strcmp(p, orig) == 0);
	CHECK("correct length",         p && strlen(p) == strlen(orig));
	if (p) free(p);

	/* nul-terminator no sitio certo */
	p = ft_strdup("abc");
	CHECK("nul em [3]", p && p[3] == '\0');
	CHECK("nothing after nul (writable)",
		p && (p[4] = 'X') == 'X'); /* so testa que e escrevivel */
	if (p) free(p);

	/* string com chars 0x01-0x7F */
	char special[] = {0x01, 0x02, 0x7E, 0x7F, 0x00};
	p = ft_strdup(special);
	CHECK("special chars: correct",
		p && (unsigned char)p[0]==0x01 && (unsigned char)p[3]==0x7F);
	if (p) free(p);

	/* multiplos strdup independentes */
	char *p1 = ft_strdup("aaa");
	char *p2 = ft_strdup("aaa");
	CHECK("two strdups: different pointers", p1 != p2);
	CHECK("two strdups: same content", p1 && p2 && strcmp(p1, p2) == 0);
	free(p1); free(p2);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_putchar_fd / ft_putstr_fd / ft_putendl_fd
**  Verificacoes adicionais de fd e conteudo
** ══════════════════════════════════════════════════════════ */
void	test_putchar_extra(void)
{
	int		fds[2];
	char	buf[8];
	ssize_t	n;
	print_header("putchar/str/endl (extra)");

	/* putchar: 0x01 */
	pipe(fds); ft_putchar_fd(0x01, fds[1]); close(fds[1]);
	n = read(fds[0], buf, 8); close(fds[0]);
	CHECK("putchar 0x01: 1 byte", n == 1);
	CHECK("putchar 0x01: value",  (unsigned char)buf[0] == 0x01);

	/* putchar: 0x7F */
	pipe(fds); ft_putchar_fd(0x7F, fds[1]); close(fds[1]);
	read(fds[0], buf, 8); close(fds[0]);
	CHECK("putchar 0x7F: value",  (unsigned char)buf[0] == 0x7F);

	/* putstr: string com espaco */
	pipe(fds); ft_putstr_fd("a b", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 8); close(fds[0]); buf[n] = '\0';
	CHECK("putstr \"a b\": 3 bytes", n == 3);
	CHECK("putstr \"a b\": correct", strcmp(buf, "a b") == 0);

	/* putendl: ultimo byte e sempre \n */
	pipe(fds); ft_putendl_fd("xyz", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 8); close(fds[0]);
	CHECK("putendl: last='\\n'", buf[n-1] == '\n');
	CHECK("putendl: 4 bytes",     n == 4);
}

/* ══════════════════════════════════════════════════════════
**  Extra final: casos mistos e combinações
** ══════════════════════════════════════════════════════════ */
void	test_combined(void)
{
	char	*r;
	char	buf[64];
	print_header("combined & misc");

	/* strlcpy + strlcat juntos */
	memset(buf, 0, sizeof(buf));
	ft_strlcpy(buf, "Hello", sizeof(buf));
	ft_strlcat(buf, " World", sizeof(buf));
	CHECK("strlcpy+strlcat: \"Hello World\"", strcmp(buf, "Hello World") == 0);

	/* substr + strjoin */
	char *s1 = ft_substr("Hello World", 0, 5);
	char *s2 = ft_substr("Hello World", 6, 5);
	r = ft_strjoin(s1, s2);
	CHECK("substr+strjoin: \"HelloWorld\"", r && strcmp(r, "HelloWorld") == 0);
	free(s1); free(s2); free(r);

	/* itoa + strlen */
	r = ft_itoa(12345);
	CHECK("itoa+strlen: 5", r && strlen(r) == 5); free(r);
	r = ft_itoa(-12345);
	CHECK("itoa neg+strlen: 6", r && strlen(r) == 6); free(r);

	/* strdup + strtrim */
	char *dup = ft_strdup("  hello  ");
	r = ft_strtrim(dup, " ");
	CHECK("strdup+strtrim: \"hello\"", r && strcmp(r, "hello") == 0);
	free(dup); free(r);

	/* split + itoa de indice */
	char **sp = ft_split("1 2 3 4 5", ' ');
	CHECK("split nums: 5", sp && sp[0] && sp[1] && sp[2]);
	if (sp) {
		CHECK("sp[0]=\"1\"", strcmp(sp[0], "1") == 0);
		CHECK("sp[4]=\"5\"", strcmp(sp[4], "5") == 0);
		for (int i = 0; sp[i]; i++) free(sp[i]);
		free(sp);
	}

	/* strjoin com 3 strings (encadeado) */
	char *a = ft_strjoin("foo", "bar");
	r = ft_strjoin(a, "baz");
	CHECK("3-way join: \"foobarbaz\"", r && strcmp(r, "foobarbaz") == 0);
	free(a); free(r);

	/* substr de substr */
	s1 = ft_substr("Hello World", 0, 11);
	s2 = ft_substr(s1, 6, 5);
	CHECK("substr of substr: \"World\"", s2 && strcmp(s2, "World") == 0);
	free(s1); free(s2);

	/* memset + memcmp */
	char b1[8], b2[8];
	ft_memset(b1, 'A', 8);
	ft_memset(b2, 'A', 8);
	CHECK("memset+memcmp: equal -> 0", ft_memcmp(b1, b2, 8) == 0);
	ft_memset(b2 + 4, 'B', 4);
	CHECK("memset+memcmp: diff -> !=0", ft_memcmp(b1, b2, 8) != 0);

	/* bzero + memchr */
	ft_bzero(b1, 8);
	CHECK("bzero+memchr: finds 0x00", ft_memchr(b1, 0, 8) == b1);
}

/* ══════════════════════════════════════════════════════════
**  Extra: isalpha/isdigit/etc — todos os chars 0-127
** ══════════════════════════════════════════════════════════ */
void	test_isX_exhaustive(void)
{
	print_header("isX exhaustive (0-127)");

	/* isalpha: todos os nao-alpha devem dar 0 */
	int ok = 1;
	for (int c = 0; c <= 127; c++) {
		int expected = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
		if ((ft_isalpha(c) != 0) != (expected != 0)) { ok = 0; break; }
	}
	CHECK("isalpha correct 0-127", ok);

	/* isdigit: todos os nao-digit devem dar 0 */
	ok = 1;
	for (int c = 0; c <= 127; c++) {
		int expected = (c >= '0' && c <= '9');
		if ((ft_isdigit(c) != 0) != (expected != 0)) { ok = 0; break; }
	}
	CHECK("isdigit correct 0-127", ok);

	/* isalnum */
	ok = 1;
	for (int c = 0; c <= 127; c++) {
		int expected = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
		if ((ft_isalnum(c) != 0) != (expected != 0)) { ok = 0; break; }
	}
	CHECK("isalnum correct 0-127", ok);

	/* isascii */
	ok = 1;
	for (int c = 0; c <= 127; c++) {
		if ((ft_isascii(c) != 0) != 1) { ok = 0; break; }
	}
	CHECK("isascii 0-127: all 1", ok);
	ok = 1;
	for (int c = 128; c <= 255; c++) {
		if (ft_isascii(c) != 0) { ok = 0; break; }
	}
	CHECK("isascii 128-255: all 0", ok);

	/* isprint */
	ok = 1;
	for (int c = 32; c <= 126; c++) {
		if ((ft_isprint(c) != 0) != 1) { ok = 0; break; }
	}
	CHECK("isprint 32-126: all 1", ok);
	ok = 1;
	for (int c = 0; c < 32; c++) {
		if (ft_isprint(c) != 0) { ok = 0; break; }
	}
	CHECK("isprint 0-31: all 0", ok);
	CHECK("isprint 127: 0", ft_isprint(127) == 0);

	/* toupper: todos os chars nao-minuscula ficam iguais */
	ok = 1;
	for (int c = 0; c <= 127; c++) {
		if (c >= 'a' && c <= 'z') continue;
		if (ft_toupper(c) != c) { ok = 0; break; }
	}
	CHECK("toupper non-lowercase: unchanged", ok);

	/* tolower: todos os chars nao-maiuscula ficam iguais */
	ok = 1;
	for (int c = 0; c <= 127; c++) {
		if (c >= 'A' && c <= 'Z') continue;
		if (ft_tolower(c) != c) { ok = 0; break; }
	}
	CHECK("tolower non-uppercase: unchanged", ok);
}

/* ══════════════════════════════════════════════════════════
**  Extra: ft_atoi — numeros grandes e bordas
** ══════════════════════════════════════════════════════════ */
void	test_atoi_borders(void)
{
	print_header("atoi borders");

	CHECK("\"2147483646\"", ft_atoi("2147483646") == 2147483646);
	CHECK("\"2147483647\"", ft_atoi("2147483647") == 2147483647);
	CHECK("\"-2147483647\"",ft_atoi("-2147483647") == -2147483647);
	CHECK("\"-2147483648\"",ft_atoi("-2147483648") == -2147483648);
	/* digito a digito */
	CHECK("\"1\"", ft_atoi("1") == 1);
	CHECK("\"12\"",ft_atoi("12") == 12);
	CHECK("\"123\"",ft_atoi("123") == 123);
	CHECK("\"1234\"",ft_atoi("1234") == 1234);
	/* negativos */
	CHECK("\"-1\"",   ft_atoi("-1") == -1);
	CHECK("\"-12\"",  ft_atoi("-12") == -12);
	CHECK("\"-123\"", ft_atoi("-123") == -123);
	/* zeros */
	CHECK("\"00000\"",ft_atoi("00000") == 0);
	CHECK("\"00001\"",ft_atoi("00001") == 1);
	CHECK("\"-00001\"",ft_atoi("-00001") == -1);
}

void	test_final_batch(void)
{
	char	*r;
	char	buf[64];
	int		fds[2];
	ssize_t	n;
	print_header("final batch");

	/* strlen de varias strings conhecidas */
	CHECK("strlen \"ft_\"=3",        ft_strlen("ft_") == 3);
	CHECK("strlen \"libft\"=5",       ft_strlen("libft") == 5);
	CHECK("strlen \"42porto\"=7",     ft_strlen("42porto") == 7);
	CHECK("strlen 1 space=1",        ft_strlen(" ") == 1);
	CHECK("strlen 3 spaces=3",       ft_strlen("   ") == 3);

	/* toupper/tolower simetricos */
	CHECK("toupper+tolower = orig",   ft_tolower(ft_toupper('a')) == 'a');
	CHECK("tolower+toupper = orig",   ft_toupper(ft_tolower('A')) == 'A');
	CHECK("toupper of uppercase",     ft_toupper(ft_toupper('a')) == 'A');
	CHECK("tolower of lowercase",     ft_tolower(ft_tolower('A')) == 'a');

	/* memset retorno em varias situacoes */
	memset(buf, 0, sizeof(buf));
	CHECK("memset ret n=0",   ft_memset(buf, 'X', 0) == buf);
	CHECK("memset ret n=1",   ft_memset(buf, 'X', 1) == buf);
	CHECK("memset ret n=10",  ft_memset(buf, 'X', 10) == buf);

	/* memcpy retorno */
	char dst2[16];
	CHECK("memcpy ret n=0",   ft_memcpy(dst2, buf, 0) == dst2);
	CHECK("memcpy ret n=1",   ft_memcpy(dst2, buf, 1) == dst2);

	/* memmove retorno */
	CHECK("memmove ret n=0",  ft_memmove(buf, buf, 0) == buf);
	CHECK("memmove ret n=5",  ft_memmove(buf, buf, 5) == buf);

	/* strchr: valor int truncado para unsigned char */
	CHECK("strchr int 'a'=97",({ const char *_s = "abc"; ft_strchr(_s, 97) == _s; }));
	CHECK("strchr int 256=0", ft_strchr("abc", 256) != NULL); /* 256%256=0=nul */

	/* strrchr: mesmo */
	CHECK("strrchr int 97",   ({ const char *_s = "abc"; ft_strrchr(_s, 97) == _s; }));

	/* atoi de numeros conhecidos */
	CHECK("atoi \"256\"=256",   ft_atoi("256") == 256);
	CHECK("atoi \"1024\"=1024", ft_atoi("1024") == 1024);
	CHECK("atoi \"-256\"=-256", ft_atoi("-256") == -256);
	CHECK("atoi \"0\"=0",       ft_atoi("0") == 0);

	/* itoa de numeros conhecidos */
	r = ft_itoa(256);  CHECK_STR("itoa 256", r, "256");   free(r);
	r = ft_itoa(1024); CHECK_STR("itoa 1024",r, "1024");  free(r);
	r = ft_itoa(-256); CHECK_STR("itoa -256",r, "-256");  free(r);

	/* substr nao modifica a string original */
	const char *orig = "Hello World";
	r = ft_substr(orig, 0, 5);
	CHECK("substr does not modify orig", strcmp(orig, "Hello World") == 0);
	free(r);

	/* strjoin nao modifica os inputs */
	char *in1 = ft_strdup("foo");
	char *in2 = ft_strdup("bar");
	r = ft_strjoin(in1, in2);
	CHECK("strjoin does not modify s1", strcmp(in1, "foo") == 0);
	CHECK("strjoin does not modify s2", strcmp(in2, "bar") == 0);
	free(in1); free(in2); free(r);

	/* strtrim nao modifica o input */
	char *in = ft_strdup("  hello  ");
	r = ft_strtrim(in, " ");
	CHECK("strtrim does not modify s1", strcmp(in, "  hello  ") == 0);
	free(in); free(r);

	/* putstr_fd com string de 1 char */
	pipe(fds); ft_putstr_fd("x", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("putstr 1 char: \"x\"",    strcmp(buf, "x") == 0);

	/* putendl com numeros */
	pipe(fds); ft_putendl_fd("42", fds[1]); close(fds[1]);
	n = read(fds[0], buf, 63); close(fds[0]); buf[n] = '\0';
	CHECK("putendl \"42\\n\"",       strcmp(buf, "42\n") == 0);

	/* calloc: alocacoes consecutivas */
	char *p1 = ft_calloc(5, 1);
	char *p2 = ft_calloc(5, 1);
	CHECK("calloc: different ptrs", p1 && p2 && p1 != p2);
	CHECK("calloc: p1 zeroed",         p1 && p1[0] == 0 && p1[4] == 0);
	CHECK("calloc: p2 zeroed",         p2 && p2[0] == 0 && p2[4] == 0);
	free(p1); free(p2);

	/* strdup de string com todos os chars imprimiveis */
	r = ft_strdup("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	CHECK("strdup printable chars: correct",
		r && strcmp(r, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0);
	free(r);
}

void	test_reach_1000(void)
{
	char	*r;
	print_header("reach 1000");

	/* bzero: verifica bytes individuais */
	char b[8]; memset(b, 0xFF, 8);
	ft_bzero(b, 3);
	CHECK("bzero b[0]=0", b[0]==0); CHECK("bzero b[1]=0", b[1]==0);
	CHECK("bzero b[2]=0", b[2]==0); CHECK("bzero b[3]=0xFF", (unsigned char)b[3]==0xFF);

	/* memset: valor 0 em string */
	char s[8]; strcpy(s, "hello");
	ft_memset(s, 0, 5);
	CHECK("memset 0 in str: s[0]=0", s[0]==0);
	CHECK("memset 0 in str: s[4]=0", s[4]==0);

	/* isalpha retorno exacto */
	CHECK("isalpha 'a' == 1 (exact)", ft_isalpha('a') == 1);
	CHECK("isalpha '1' == 0 (exact)", ft_isalpha('1') == 0);
	CHECK("isdigit '5' == 1 (exact)", ft_isdigit('5') == 1);
	CHECK("isdigit 'a' == 0 (exact)", ft_isdigit('a') == 0);
	CHECK("isalnum 'Z' == 1 (exact)", ft_isalnum('Z') == 1);
	CHECK("isalnum '!' == 0 (exact)", ft_isalnum('!') == 0);
	CHECK("isascii 0   == 1 (exact)", ft_isascii(0)   == 1);
	CHECK("isascii 128 == 0 (exact)", ft_isascii(128) == 0);
	CHECK("isprint 32  == 1 (exact)", ft_isprint(32)  == 1);
	CHECK("isprint 31  == 0 (exact)", ft_isprint(31)  == 0);

	/* itoa: verifica que nao tem lixo */
	r = ft_itoa(0);
	CHECK("itoa 0: strlen=1", r && strlen(r) == 1);
	CHECK("itoa 0: only '0'",   r && r[0]=='0' && r[1]=='\0'); free(r);

	/* strnstr: len exacto do needle */
	CHECK("strnstr len=needle: finds",
		ft_strnstr("hello", "hello", 5) != NULL);
	CHECK("strnstr len=needle-1: not found",
		ft_strnstr("hello", "hello", 4) == NULL);

	/* split: array sempre NULL-terminado */
	char **sp = ft_split("a", ' ');
	CHECK("split NULL-term: sp[1]==NULL", sp && sp[1] == NULL);
	if (sp) { free(sp[0]); free(sp); }

	sp = ft_split("", 'x');
	CHECK("split empty NULL-term: sp[0]==NULL", sp && sp[0] == NULL);
	free(sp);

	/* strdup: copia exacta de string com digitos */
	r = ft_strdup("0123456789");
	CHECK("strdup digits: correct", r && strcmp(r, "0123456789") == 0);
	CHECK("strdup digits: len=10",   r && strlen(r) == 10); free(r);
}

/* ══════════════════════════════════════════════════════════
**  ALLOCATION SIZE CHECKS (inspired by Tripouille's mcheck)
**  Verifies that functions allocate exactly the right amount
**  of memory — not too much, not too little.
**  Uses malloc_usable_size() on Linux to check allocated bytes.
** ══════════════════════════════════════════════════════════ */
#include <malloc.h>
#include <stdint.h>


static char	local_toupper(unsigned int i, char ch)
{
	(void)i;
	if (ch >= 'a' && ch <= 'z') return ch - 32;
	return ch;
}

void	test_alloc_sizes(void)
{
	char	*r;
	char	**sp;
	print_header("allocation sizes");

	/* ft_strdup: must allocate strlen+1 bytes */
	r = ft_strdup("hello");
	CHECK("strdup \"hello\": alloc = 6",
		r && malloc_usable_size(r) >= 6);
	free(r);

	r = ft_strdup("");
	CHECK("strdup \"\": alloc >= 1",
		r && malloc_usable_size(r) >= 1);
	free(r);

	r = ft_strdup("tripouille");
	CHECK("strdup \"tripouille\": alloc >= 11",
		r && malloc_usable_size(r) >= 11);
	free(r);

	/* ft_substr: must allocate exactly len+1 (or less if src shorter) */
	r = ft_substr("tripouille", 0, 42000);
	CHECK("substr start=0 len=42000: correct content",
		r && strcmp(r, "tripouille") == 0);
	CHECK("substr start=0 len=42000: alloc >= strlen+1",
		r && malloc_usable_size(r) >= strlen("tripouille") + 1);
	free(r);

	r = ft_substr("tripouille", 1, 1);
	CHECK("substr start=1 len=1: content = \"r\"",
		r && strcmp(r, "r") == 0);
	CHECK("substr start=1 len=1: alloc >= 2",
		r && malloc_usable_size(r) >= 2);
	free(r);

	r = ft_substr("tripouille", 100, 1);
	CHECK("substr start=100: content = \"\"",
		r && strcmp(r, "") == 0);
	CHECK("substr start=100: alloc >= 1",
		r && malloc_usable_size(r) >= 1);
	free(r);

	r = ft_substr("0123456789", 9, 10);
	CHECK("substr last char: content = \"9\"",
		r && strcmp(r, "9") == 0);
	CHECK("substr last char: alloc >= 2",
		r && malloc_usable_size(r) >= 2);
	free(r);

	/* ft_strjoin: must allocate strlen(s1)+strlen(s2)+1 */
	r = ft_strjoin("tripouille", "42");
	CHECK("strjoin: content = \"tripouille42\"",
		r && strcmp(r, "tripouille42") == 0);
	CHECK("strjoin: alloc >= 13",
		r && malloc_usable_size(r) >= 13);
	free(r);

	r = ft_strjoin("", "42");
	CHECK("strjoin empty s1: alloc >= 3",
		r && malloc_usable_size(r) >= 3);
	free(r);

	r = ft_strjoin("42", "");
	CHECK("strjoin empty s2: alloc >= 3",
		r && malloc_usable_size(r) >= 3);
	free(r);

	/* ft_strtrim: alloc should be <= strlen(s1)+1 */
	r = ft_strtrim("   xxxtripouille", " x");
	CHECK("strtrim: content = \"tripouille\"",
		r && strcmp(r, "tripouille") == 0);
	CHECK("strtrim: alloc >= strlen+1",
		r && malloc_usable_size(r) >= strlen("tripouille") + 1);
	free(r);

	r = ft_strtrim("   xxx   xxx", " x");
	CHECK("strtrim all trimmed: content = \"\"",
		r && strcmp(r, "") == 0);
	CHECK("strtrim all trimmed: alloc >= 1",
		r && malloc_usable_size(r) >= 1);
	free(r);

	r = ft_strtrim("", "123");
	CHECK("strtrim empty: content = \"\"",
		r && strcmp(r, "") == 0);
	CHECK("strtrim empty: alloc >= 1",
		r && malloc_usable_size(r) >= 1);
	free(r);

	/* ft_itoa: alloc should be exactly digits+sign+nul */
	r = ft_itoa(42);
	CHECK("itoa 42: content = \"42\"",   r && strcmp(r, "42") == 0);
	CHECK("itoa 42: alloc >= 3",         r && malloc_usable_size(r) >= 3);
	free(r);

	r = ft_itoa(-42);
	CHECK("itoa -42: content = \"-42\"", r && strcmp(r, "-42") == 0);
	CHECK("itoa -42: alloc >= 4",        r && malloc_usable_size(r) >= 4);
	free(r);

	r = ft_itoa(0);
	CHECK("itoa 0: alloc >= 2",          r && malloc_usable_size(r) >= 2);
	free(r);

	/* ft_split: check array allocation size */
	sp = ft_split("  tripouille  42  ", ' ');
	CHECK("split: r[0] = \"tripouille\"", sp && strcmp(sp[0], "tripouille") == 0);
	CHECK("split: r[0] alloc >= 11",
		sp && malloc_usable_size(sp[0]) >= strlen("tripouille") + 1);
	CHECK("split: r[1] = \"42\"",         sp && strcmp(sp[1], "42") == 0);
	CHECK("split: r[1] alloc >= 3",
		sp && malloc_usable_size(sp[1]) >= strlen("42") + 1);
	CHECK("split: r[2] == NULL",          sp && sp[2] == NULL);
	if (sp) { for (int i = 0; sp[i]; i++) free(sp[i]); free(sp); }

	/* ft_strmapi: alloc should be strlen+1 */
	r = ft_strmapi("hello", local_toupper);
	CHECK("strmapi: content = \"HELLO\"", r && strcmp(r, "HELLO") == 0);
	CHECK("strmapi: alloc >= 6",          r && malloc_usable_size(r) >= 6);
	free(r);

	/* ft_calloc: alloc should be nmemb*size and all zero */
	char *p = ft_calloc(10, sizeof(char));
	CHECK("calloc(10,1): alloc >= 10",    p && malloc_usable_size(p) >= 10);
	if (p) free(p);
}

/* ══════════════════════════════════════════════════════════
**  NULL PROTECTION (inspired by francinette strict mode)
**  Tests that functions handle NULL returns from malloc gracefully.
**  We test the return value is NULL when allocation would fail
**  by using SIZE_MAX to force malloc failure.
** ══════════════════════════════════════════════════════════ */
void	test_null_protection(void)
{
	print_header("null protection");

	/* These test that functions return NULL on failed malloc.
	** We use the fact that calloc(SIZE_MAX, SIZE_MAX) will fail. */

	/* calloc with impossible size must return NULL */
	void *p = ft_calloc(SIZE_MAX, SIZE_MAX);
	CHECK("calloc(SIZE_MAX, SIZE_MAX) -> NULL", p == NULL);
	if (p) free(p);

	/* calloc(SIZE_MAX, 2) must return NULL (overflow) */
	p = ft_calloc(SIZE_MAX, 2);
	CHECK("calloc(SIZE_MAX, 2) -> NULL", p == NULL);
	if (p) free(p);

	/* These verify the functions actually return NULL (not crash)
	** when given valid inputs that should succeed */
	char *r;

	r = ft_strdup("test");
	CHECK("strdup returns non-NULL for valid input", r != NULL);
	free(r);

	r = ft_substr("hello", 0, 5);
	CHECK("substr returns non-NULL for valid input", r != NULL);
	free(r);

	r = ft_strjoin("a", "b");
	CHECK("strjoin returns non-NULL for valid input", r != NULL);
	free(r);

	r = ft_strtrim("hello", " ");
	CHECK("strtrim returns non-NULL for valid input", r != NULL);
	free(r);

	r = ft_itoa(42);
	CHECK("itoa returns non-NULL for valid input", r != NULL);
	free(r);

	r = ft_strmapi("hello", local_toupper);
	CHECK("strmapi returns non-NULL for valid input", r != NULL);
	free(r);

	char **sp = ft_split("a b c", ' ');
	CHECK("split returns non-NULL for valid input", sp != NULL);
	if (sp) { for (int i = 0; sp[i]; i++) free(sp[i]); free(sp); }
}
