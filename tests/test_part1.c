#include "../utils/tester.h"
#include "libft.h"

void	test_isalpha(void)
{
	print_header("isalpha");
	CHECK("'a' lowercase           -> 1", ft_isalpha('a') == 1);
	CHECK("'z' lowercase           -> 1", ft_isalpha('z') == 1);
	CHECK("'A' uppercase           -> 1", ft_isalpha('A') == 1);
	CHECK("'Z' uppercase           -> 1", ft_isalpha('Z') == 1);
	CHECK("'m' middle              -> 1", ft_isalpha('m') == 1);
	CHECK("'M' middle              -> 1", ft_isalpha('M') == 1);
	CHECK("'@'=64 before A         -> 0", ft_isalpha('@') == 0);
	CHECK("'['=91 after Z          -> 0", ft_isalpha('[') == 0);
	CHECK("'\\'=92                 -> 0", ft_isalpha('\\') == 0);
	CHECK("']'=93                  -> 0", ft_isalpha(']') == 0);
	CHECK("'^'=94                  -> 0", ft_isalpha('^') == 0);
	CHECK("'_'=95                  -> 0", ft_isalpha('_') == 0);
	CHECK("'`'=96 before a         -> 0", ft_isalpha('`') == 0);
	CHECK("'{'=123 after z         -> 0", ft_isalpha('{') == 0);
	CHECK("'0' digit               -> 0", ft_isalpha('0') == 0);
	CHECK("'9' digit               -> 0", ft_isalpha('9') == 0);
	CHECK("'5' digit               -> 0", ft_isalpha('5') == 0);
	CHECK("' ' space               -> 0", ft_isalpha(' ') == 0);
	CHECK("'\\n'                   -> 0", ft_isalpha('\n') == 0);
	CHECK("'\\t'                   -> 0", ft_isalpha('\t') == 0);
	CHECK("'\\0' null              -> 0", ft_isalpha('\0') == 0);
	CHECK("'!' punct               -> 0", ft_isalpha('!') == 0);
	CHECK("'~'                     -> 0", ft_isalpha('~') == 0);
	CHECK("-1 negative             -> 0", ft_isalpha(-1) == 0);
	CHECK("127 DEL                 -> 0", ft_isalpha(127) == 0);
	CHECK("128 extended            -> 0", ft_isalpha(128) == 0);
	CHECK("200                     -> 0", ft_isalpha(200) == 0);
	CHECK("255                     -> 0", ft_isalpha(255) == 0);
	CHECK("returns exactly 1",           ft_isalpha('a') == 1);
	CHECK("returns exactly 0",           ft_isalpha('1') == 0);
}

void	test_isdigit(void)
{
	print_header("isdigit");
	CHECK("'0'",                         ft_isdigit('0') == 1);
	CHECK("'9'",                         ft_isdigit('9') == 1);
	CHECK("'5'",                         ft_isdigit('5') == 1);
	CHECK("'1'",                         ft_isdigit('1') == 1);
	CHECK("'8'",                         ft_isdigit('8') == 1);
	CHECK("'/'=47 before '0'     -> 0",  ft_isdigit('/') == 0);
	CHECK("':'=58 after '9'      -> 0",  ft_isdigit(':') == 0);
	CHECK("'a' letter            -> 0",  ft_isdigit('a') == 0);
	CHECK("'Z' letter            -> 0",  ft_isdigit('Z') == 0);
	CHECK("' ' space             -> 0",  ft_isdigit(' ') == 0);
	CHECK("'\\0' null            -> 0",  ft_isdigit('\0') == 0);
	CHECK("'\\n'                 -> 0",  ft_isdigit('\n') == 0);
	CHECK("'!'                   -> 0",  ft_isdigit('!') == 0);
	CHECK("-1 negative           -> 0",  ft_isdigit(-1) == 0);
	CHECK("255                   -> 0",  ft_isdigit(255) == 0);
	CHECK("returns exactly 1",           ft_isdigit('0') == 1);
	CHECK("returns exactly 0",           ft_isdigit('a') == 0);
}

void	test_isalnum(void)
{
	print_header("isalnum");
	CHECK("'a'",                         ft_isalnum('a') == 1);
	CHECK("'Z'",                         ft_isalnum('Z') == 1);
	CHECK("'0'",                         ft_isalnum('0') == 1);
	CHECK("'9'",                         ft_isalnum('9') == 1);
	CHECK("'z'",                         ft_isalnum('z') == 1);
	CHECK("'A'",                         ft_isalnum('A') == 1);
	CHECK("'/'=47                -> 0",  ft_isalnum('/') == 0);
	CHECK("':'=58                -> 0",  ft_isalnum(':') == 0);
	CHECK("'@'=64                -> 0",  ft_isalnum('@') == 0);
	CHECK("'['=91                -> 0",  ft_isalnum('[') == 0);
	CHECK("'`'=96                -> 0",  ft_isalnum('`') == 0);
	CHECK("'{'=123               -> 0",  ft_isalnum('{') == 0);
	CHECK("' ' space             -> 0",  ft_isalnum(' ') == 0);
	CHECK("'!'                   -> 0",  ft_isalnum('!') == 0);
	CHECK("'\\0'                 -> 0",  ft_isalnum('\0') == 0);
	CHECK("'_'                   -> 0",  ft_isalnum('_') == 0);
	CHECK("-1                    -> 0",  ft_isalnum(-1) == 0);
	CHECK("255                   -> 0",  ft_isalnum(255) == 0);
	CHECK("returns exactly 1",           ft_isalnum('a') == 1);
	CHECK("returns exactly 0",           ft_isalnum('!') == 0);
}

void	test_isascii(void)
{
	print_header("isascii");
	CHECK("0   NUL lower bound    -> 1", ft_isascii(0)   == 1);
	CHECK("1                      -> 1", ft_isascii(1)   == 1);
	CHECK("32  space              -> 1", ft_isascii(32)  == 1);
	CHECK("65  'A'                -> 1", ft_isascii(65)  == 1);
	CHECK("126                    -> 1", ft_isascii(126) == 1);
	CHECK("127 DEL upper bound    -> 1", ft_isascii(127) == 1);
	CHECK("128 out of range       -> 0", ft_isascii(128) == 0);
	CHECK("129                    -> 0", ft_isascii(129) == 0);
	CHECK("200                    -> 0", ft_isascii(200) == 0);
	CHECK("255                    -> 0", ft_isascii(255) == 0);
	CHECK("-1 negative            -> 0", ft_isascii(-1)  == 0);
	CHECK("256                    -> 0", ft_isascii(256) == 0);
	CHECK("returns exactly 1",          ft_isascii(65)  == 1);
	CHECK("returns exactly 0",          ft_isascii(200) == 0);
}

void	test_isprint(void)
{
	print_header("isprint");
	CHECK("32  space lower bound  -> 1", ft_isprint(32)  == 1);
	CHECK("33  '!'                -> 1", ft_isprint(33)  == 1);
	CHECK("48  '0'                -> 1", ft_isprint(48)  == 1);
	CHECK("65  'A'                -> 1", ft_isprint(65)  == 1);
	CHECK("97  'a'                -> 1", ft_isprint(97)  == 1);
	CHECK("125 '}'                -> 1", ft_isprint(125) == 1);
	CHECK("126 '~' upper bound    -> 1", ft_isprint(126) == 1);
	CHECK("0   NUL                -> 0", ft_isprint(0)   == 0);
	CHECK("8   BS                 -> 0", ft_isprint(8)   == 0);
	CHECK("9   TAB                -> 0", ft_isprint(9)   == 0);
	CHECK("10  LF                 -> 0", ft_isprint(10)  == 0);
	CHECK("13  CR                 -> 0", ft_isprint(13)  == 0);
	CHECK("27  ESC                -> 0", ft_isprint(27)  == 0);
	CHECK("31                     -> 0", ft_isprint(31)  == 0);
	CHECK("127 DEL                -> 0", ft_isprint(127) == 0);
	CHECK("128                    -> 0", ft_isprint(128) == 0);
	CHECK("-1                     -> 0", ft_isprint(-1)  == 0);
	CHECK("returns exactly 1",          ft_isprint(65)  == 1);
	CHECK("returns exactly 0",          ft_isprint(9)   == 0);
}

void	test_toupper(void)
{
	print_header("toupper");
	CHECK("'a' -> 'A'",                  ft_toupper('a') == 'A');
	CHECK("'b' -> 'B'",                  ft_toupper('b') == 'B');
	CHECK("'m' -> 'M'",                  ft_toupper('m') == 'M');
	CHECK("'y' -> 'Y'",                  ft_toupper('y') == 'Y');
	CHECK("'z' -> 'Z'",                  ft_toupper('z') == 'Z');
	CHECK("'A' already upper",           ft_toupper('A') == 'A');
	CHECK("'Z' already upper",           ft_toupper('Z') == 'Z');
	CHECK("'M' already upper",           ft_toupper('M') == 'M');
	CHECK("'`'=96 unchanged",            ft_toupper('`') == '`');
	CHECK("'{'=123 unchanged",           ft_toupper('{') == '{');
	CHECK("'@'=64 unchanged",            ft_toupper('@') == '@');
	CHECK("'['=91 unchanged",            ft_toupper('[') == '[');
	CHECK("'0' digit unchanged",         ft_toupper('0') == '0');
	CHECK("'9' digit unchanged",         ft_toupper('9') == '9');
	CHECK("' ' space unchanged",         ft_toupper(' ') == ' ');
	CHECK("'!' unchanged",               ft_toupper('!') == '!');
	CHECK("'~' unchanged",               ft_toupper('~') == '~');
	CHECK("0 NUL unchanged",             ft_toupper(0) == 0);
	CHECK("'\\n' unchanged",             ft_toupper('\n') == '\n');
}

void	test_tolower(void)
{
	print_header("tolower");
	CHECK("'A' -> 'a'",                  ft_tolower('A') == 'a');
	CHECK("'B' -> 'b'",                  ft_tolower('B') == 'b');
	CHECK("'M' -> 'm'",                  ft_tolower('M') == 'm');
	CHECK("'Y' -> 'y'",                  ft_tolower('Y') == 'y');
	CHECK("'Z' -> 'z'",                  ft_tolower('Z') == 'z');
	CHECK("'a' already lower",           ft_tolower('a') == 'a');
	CHECK("'z' already lower",           ft_tolower('z') == 'z');
	CHECK("'@'=64 unchanged",            ft_tolower('@') == '@');
	CHECK("'['=91 unchanged",            ft_tolower('[') == '[');
	CHECK("'`'=96 unchanged",            ft_tolower('`') == '`');
	CHECK("'{'=123 unchanged",           ft_tolower('{') == '{');
	CHECK("'0' digit unchanged",         ft_tolower('0') == '0');
	CHECK("'!' unchanged",               ft_tolower('!') == '!');
	CHECK("' ' space unchanged",         ft_tolower(' ') == ' ');
	CHECK("0 NUL unchanged",             ft_tolower(0) == 0);
}

void	test_strlen(void)
{
	print_header("strlen");
	CHECK("\"\" empty string       -> 0", ft_strlen("") == 0);
	CHECK("\"a\" one char          -> 1", ft_strlen("a") == 1);
	CHECK("\"\\0\"                 -> 0", ft_strlen("\0") == 0);
	CHECK("\"hello\"               -> 5", ft_strlen("hello") == 5);
	CHECK("\"hello world\"         ->11", ft_strlen("hello world") == 11);
	CHECK("\"\\n\" newline         -> 1", ft_strlen("\n") == 1);
	CHECK("\"\\t\" tab             -> 1", ft_strlen("\t") == 1);
	CHECK("\"\\r\"                 -> 1", ft_strlen("\r") == 1);
	CHECK("\"a\\0b\" stops at nul  -> 1", ft_strlen("a\0b") == 1);
	CHECK("10 chars",                    ft_strlen("0123456789") == 10);
	CHECK("20 chars",                    ft_strlen("01234567890123456789") == 20);
	CHECK("string with spaces     -> 5", ft_strlen("a b c") == 5);
	CHECK("nul not counted",             ft_strlen("hello") == 5);
	CHECK("returns size_t",              ft_strlen("abc") == (size_t)3);
}

void	test_memset(void)
{
	char	buf[64];
	print_header("memset");

	memset(buf, 0, sizeof(buf));
	ft_memset(buf, 'A', 5);
	CHECK("fills 5 bytes with 'A'",      buf[0]=='A' && buf[4]=='A');
	CHECK("byte 5 untouched",            buf[5] == 0);
	CHECK("byte 6 untouched",            buf[6] == 0);

	memset(buf, 'X', sizeof(buf));
	ft_memset(buf, 0, 5);
	CHECK("fills 5 bytes with 0",        buf[0]==0 && buf[4]==0);
	CHECK("byte 5 still 'X'",            buf[5] == 'X');

	memset(buf, 'X', sizeof(buf));
	ft_memset(buf, 'Z', 0);
	CHECK("n=0: nothing changes",        buf[0] == 'X');

	ft_memset(buf, 255, 4);
	CHECK("value 255: buf[0]=0xFF",      (unsigned char)buf[0] == 255);
	CHECK("value 255: buf[3]=0xFF",      (unsigned char)buf[3] == 255);

	ft_memset(buf, -1, 3);
	CHECK("-1 truncated to 0xFF",        (unsigned char)buf[0] == 0xFF);

	memset(buf, 0, sizeof(buf));
	ft_memset(buf, 'B', 1);
	CHECK("n=1: buf[0]='B'",             buf[0] == 'B');
	CHECK("n=1: buf[1] untouched",       buf[1] == 0);

	ft_memset(buf, 'C', sizeof(buf));
	CHECK("fills full buffer: buf[0]",   buf[0] == 'C');
	CHECK("fills full buffer: buf[63]",  buf[63] == 'C');

	CHECK("returns dst",                 ft_memset(buf, 0, 4) == buf);

	ft_memset(buf, 0, 10);
	CHECK("value 0: buf[0]==0",          buf[0] == 0);
	CHECK("value 0: buf[9]==0",          buf[9] == 0);
}

void	test_bzero(void)
{
	char	buf[32];
	print_header("bzero");

	memset(buf, 'X', sizeof(buf));
	ft_bzero(buf, 8);
	CHECK("zeros 8 bytes",               buf[0]==0 && buf[7]==0);
	CHECK("byte 8 untouched",            buf[8] == 'X');
	CHECK("byte 9 untouched",            buf[9] == 'X');

	memset(buf, 'X', sizeof(buf));
	ft_bzero(buf, 0);
	CHECK("n=0: buf[0] still 'X'",       buf[0] == 'X');
	CHECK("n=0: buf[1] still 'X'",       buf[1] == 'X');

	memset(buf, 'X', sizeof(buf));
	ft_bzero(buf, 1);
	CHECK("n=1: buf[0]=0",               buf[0] == 0);
	CHECK("n=1: buf[1] still 'X'",       buf[1] == 'X');

	memset(buf, 0xFF, sizeof(buf));
	ft_bzero(buf, sizeof(buf));
	CHECK("full buffer: buf[0]=0",       buf[0] == 0);
	CHECK("full buffer: buf[31]=0",      buf[31] == 0);

	memset(buf, 'Y', sizeof(buf));
	ft_bzero(buf, 2);
	CHECK("n=2: buf[0]=0",               buf[0] == 0);
	CHECK("n=2: buf[1]=0",               buf[1] == 0);
	CHECK("n=2: buf[2]='Y'",             buf[2] == 'Y');
}

void	test_memcpy(void)
{
	char	dst[64];
	char	src[] = "Hello, World!";
	char	raw[] = {0x00, 0x01, 0xFF, 0x7F, 0x80};
	print_header("memcpy");

	memset(dst, 0, sizeof(dst));
	ft_memcpy(dst, src, 5);
	CHECK("copies 5 bytes",              strncmp(dst, "Hello", 5) == 0);
	CHECK("byte 5 untouched",            dst[5] == 0);

	memset(dst, 0, sizeof(dst));
	ft_memcpy(dst, src, 0);
	CHECK("n=0: nothing copied",         dst[0] == 0);

	memset(dst, 'X', sizeof(dst));
	ft_memcpy(dst, src, strlen(src) + 1);
	CHECK("copies including nul",        strcmp(dst, src) == 0);

	memset(dst, 'X', sizeof(dst));
	ft_memcpy(dst, raw, 5);
	CHECK("raw byte 0x00",               (unsigned char)dst[0] == 0x00);
	CHECK("raw byte 0x01",               (unsigned char)dst[1] == 0x01);
	CHECK("raw byte 0xFF",               (unsigned char)dst[2] == 0xFF);
	CHECK("raw byte 0x7F",               (unsigned char)dst[3] == 0x7F);
	CHECK("raw byte 0x80",               (unsigned char)dst[4] == 0x80);
	CHECK("byte 5 untouched after raw",  dst[5] == 'X');

	memset(dst, 0, sizeof(dst));
	ft_memcpy(dst, "Z", 1);
	CHECK("n=1: copies 1 byte",          dst[0] == 'Z');

	CHECK("returns dst",                 ft_memcpy(dst, src, 3) == dst);

	memset(dst, 0, sizeof(dst));
	ft_memcpy(dst, "\xff\xfe\xfd", 3);
	CHECK("0xFF copied",                 (unsigned char)dst[0] == 0xFF);
	CHECK("0xFE copied",                 (unsigned char)dst[1] == 0xFE);
	CHECK("0xFD copied",                 (unsigned char)dst[2] == 0xFD);
}

void	test_memmove(void)
{
	char	buf[64];
	print_header("memmove");

	strcpy(buf, "Hello");
	ft_memmove(buf + 10, buf, 6);
	CHECK("no overlap: copy ok",         strcmp(buf + 10, "Hello") == 0);
	CHECK("no overlap: src intact",      strcmp(buf, "Hello") == 0);

	strcpy(buf, "abcdefgh");
	ft_memmove(buf + 2, buf, 6);
	CHECK("overlap dst>src: correct",    strncmp(buf + 2, "abcdef", 6) == 0);

	strcpy(buf, "abcdefgh");
	ft_memmove(buf, buf + 2, 6);
	CHECK("overlap dst<src: correct",    strncmp(buf, "cdefgh", 6) == 0);

	strcpy(buf, "unchanged");
	ft_memmove(buf, buf, 9);
	CHECK("src==dst: no change",         strcmp(buf, "unchanged") == 0);

	strcpy(buf, "test");
	ft_memmove(buf + 1, buf, 0);
	CHECK("n=0: nothing changes",        strcmp(buf, "test") == 0);

	strcpy(buf, "abc");
	ft_memmove(buf + 3, buf, 1);
	CHECK("n=1 no overlap: buf[3]='a'",  buf[3] == 'a');

	strcpy(buf, "abc");
	ft_memmove(buf + 1, buf, 1);
	CHECK("n=1 overlap: buf[1]='a'",     buf[1] == 'a');

	CHECK("returns dst",                 ft_memmove(buf, buf, 1) == buf);

	char raw[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	ft_memmove(raw + 1, raw, 4);
	CHECK("raw overlap: raw[1]=1",       raw[1] == 1);
	CHECK("raw overlap: raw[2]=2",       raw[2] == 2);
	CHECK("raw overlap: raw[4]=4",       raw[4] == 4);
}

void	test_strlcpy(void)
{
	char	dst[32];
	size_t	r;
	print_header("strlcpy");

	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "Hello", 20);
	CHECK("copies \"Hello\"",            strcmp(dst, "Hello") == 0);
	CHECK("returns 5 (strlen src)",      r == 5);
	CHECK("nul at dst[5]",               dst[5] == '\0');
	CHECK("dst[6] untouched",            dst[6] == 'X');

	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "Hello", 3);
	CHECK("truncate: dst[0]='H'",        dst[0] == 'H');
	CHECK("truncate: dst[1]='e'",        dst[1] == 'e');
	CHECK("truncate: dst[2]='\\0'",      dst[2] == '\0');
	CHECK("truncate: dst[3] untouched",  dst[3] == 'X');
	CHECK("truncate: returns 5",         r == 5);

	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "Hello", 1);
	CHECK("size=1: only nul",            dst[0] == '\0');
	CHECK("size=1: dst[1] untouched",    dst[1] == 'X');
	CHECK("size=1: returns 5",           r == 5);

	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "Hello", 0);
	CHECK("size=0: dst untouched",       dst[0] == 'X');
	CHECK("size=0: returns 5",           r == 5);

	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "", 10);
	CHECK("empty src: dst[0]='\\0'",     dst[0] == '\0');
	CHECK("empty src: returns 0",        r == 0);
	CHECK("empty src: dst[1] untouched", dst[1] == 'X');

	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "abcde", 6);
	CHECK("size=strlen+1: full copy",    strcmp(dst, "abcde") == 0);
	CHECK("size=strlen+1: returns 5",    r == 5);

	memset(dst, 'X', sizeof(dst));
	r = ft_strlcpy(dst, "abcde", 5);
	CHECK("size=strlen: 4 chars+nul",
		strncmp(dst, "abcd", 4) == 0 && dst[4] == '\0');
	CHECK("size=strlen: returns 5",      r == 5);
}

void	test_strlcat(void)
{
	char	dst[64];
	size_t	r;
	print_header("strlcat");

	strcpy(dst, "Hello");
	r = ft_strlcat(dst, " World", 30);
	CHECK("basic concat",                strcmp(dst, "Hello World") == 0);
	CHECK("returns 11",                  r == 11);

	strcpy(dst, "Hello");
	r = ft_strlcat(dst, " World", 8);
	CHECK("truncate: \"Hello W\"",       strcmp(dst, "Hello W") == 0);
	CHECK("truncate: returns 11",        r == 11);

	strcpy(dst, "Hello");
	r = ft_strlcat(dst, " World", 3);
	CHECK("size<len: dst unchanged",     strcmp(dst, "Hello") == 0);
	CHECK("size<len: returns size+strlen(src)", r == 3 + strlen(" World"));

	strcpy(dst, "Hello");
	r = ft_strlcat(dst, " World", 5);
	CHECK("size==len: dst unchanged",    strcmp(dst, "Hello") == 0);
	CHECK("size==len: returns 5+6=11",   r == 11);

	dst[0] = '\0';
	r = ft_strlcat(dst, "World", 10);
	CHECK("empty dst: concat ok",        strcmp(dst, "World") == 0);
	CHECK("empty dst: returns 5",        r == 5);

	strcpy(dst, "Hello");
	r = ft_strlcat(dst, "", 20);
	CHECK("empty src: dst unchanged",    strcmp(dst, "Hello") == 0);
	CHECK("empty src: returns 5",        r == 5);

	dst[0] = '\0';
	r = ft_strlcat(dst, "", 10);
	CHECK("both empty: returns 0",       r == 0);
	CHECK("both empty: dst=\"\"",        dst[0] == '\0');

	dst[0] = '\0';
	r = ft_strlcat(dst, "World", 1);
	CHECK("size=1 empty dst: unchanged", dst[0] == '\0');

	strcpy(dst, "ab");
	r = ft_strlcat(dst, "c", 10);
	CHECK("src 1 char: dst=\"abc\"",     strcmp(dst, "abc") == 0);
	CHECK("src 1 char: returns 3",       r == 3);

	strcpy(dst, "Hello");
	ft_strlcat(dst, " World", 8);
	CHECK("nul always guaranteed",       dst[7] == '\0');
}

void	test_strchr(void)
{
	const char *s = "hello world";
	print_header("strchr");

	CHECK("finds 'h' at start",          ft_strchr(s, 'h') == s);
	CHECK("finds 'e' at pos 1",          ft_strchr(s, 'e') == s + 1);
	CHECK("finds 'o' at pos 4",          ft_strchr(s, 'o') == s + 4);
	CHECK("finds ' ' at pos 5",          ft_strchr(s, ' ') == s + 5);
	CHECK("finds 'w' at pos 6",          ft_strchr(s, 'w') == s + 6);
	CHECK("finds 'd' at end pos 10",     ft_strchr(s, 'd') == s + 10);
	CHECK("finds FIRST 'l' at pos 2",    ft_strchr(s, 'l') == s + 2);
	CHECK("finds '\\0' after last char", ft_strchr(s, '\0') == s + 11);
	CHECK("'z' not found -> NULL",       ft_strchr(s, 'z') == NULL);
	CHECK("'A' not found -> NULL",       ft_strchr(s, 'A') == NULL);
	CHECK("'9' not found -> NULL",       ft_strchr(s, '9') == NULL);
	CHECK("empty str: '\\0' -> ptr",     ft_strchr("", '\0') != NULL);
	CHECK("empty str: 'a' -> NULL",      ft_strchr("", 'a') == NULL);
	/* int 256 % 256 == 0 == '\0' */
	CHECK("int 256 = nul: found",        ft_strchr("abc", 256) != NULL);
	CHECK("int 257 = 0x01: found",       ft_strchr("\x01" "bc", 257) != NULL);
	CHECK("1-char str: found",           ft_strchr("a", 'a') != NULL);
	CHECK("1-char str: not found",       ft_strchr("a", 'b') == NULL);
}

void	test_strrchr(void)
{
	const char *s = "hello world";
	print_header("strrchr");

	CHECK("last 'l' at pos 9",           ft_strrchr(s, 'l') == s + 9);
	CHECK("last 'o' at pos 7",           ft_strrchr(s, 'o') == s + 7);
	CHECK("'h' only once at pos 0",      ft_strrchr(s, 'h') == s);
	CHECK("'d' at end pos 10",           ft_strrchr(s, 'd') == s + 10);
	CHECK("finds '\\0' at pos 11",       ft_strrchr(s, '\0') == s + 11);
	CHECK("'z' -> NULL",                 ft_strrchr(s, 'z') == NULL);
	CHECK("'A' -> NULL",                 ft_strrchr(s, 'A') == NULL);
	CHECK("empty str: '\\0' -> ptr",     ft_strrchr("", '\0') != NULL);
	CHECK("empty str: 'a' -> NULL",      ft_strrchr("", 'a') == NULL);
	CHECK("int 256 = nul: found",        ft_strrchr("abc", 256) != NULL);
	CHECK("1-char str: found",           ft_strrchr("a", 'a') != NULL);
	CHECK("1-char str: not found",       ft_strrchr("a", 'b') == NULL);
	{ const char *_h = "aaa"; CHECK("\"aaa\": returns last 'a'", ft_strrchr(_h, 'a') == _h + 2); }
}

void	test_strncmp(void)
{
	print_header("strncmp");
	CHECK("equal n=3             -> 0",  ft_strncmp("abc", "abc", 3) == 0);
	CHECK("equal up to n         -> 0",  ft_strncmp("abcX", "abcY", 3) == 0);
	CHECK("n=0                   -> 0",  ft_strncmp("abc", "xyz", 0) == 0);
	CHECK("n=0 both empty        -> 0",  ft_strncmp("", "", 0) == 0);
	CHECK("s1 < s2               -> <0", ft_strncmp("abc", "abd", 3) < 0);
	CHECK("s1 > s2               -> >0", ft_strncmp("abd", "abc", 3) > 0);
	CHECK("both empty            -> 0",  ft_strncmp("", "", 5) == 0);
	CHECK("s1 empty              -> <0", ft_strncmp("", "a", 1) < 0);
	CHECK("s2 empty              -> >0", ft_strncmp("a", "", 1) > 0);
	CHECK("unsigned 0xC8>0x64    -> >0", ft_strncmp("\xc8", "\x64", 1) > 0);
	CHECK("unsigned 0x80>0x01    -> >0", ft_strncmp("\x80", "\x01", 1) > 0);
	CHECK("unsigned 0x01<0x80    -> <0", ft_strncmp("\x01", "\x80", 1) < 0);
	CHECK("unsigned 0xFF>0x00    -> >0", ft_strncmp("\xff", "\x00", 1) > 0);
	CHECK("diff after nul        -> 0",  ft_strncmp("abc\0X", "abc\0Y", 5) == 0);
	CHECK("n>len: equal          -> 0",  ft_strncmp("abc", "abc", 100) == 0);
	CHECK("n>len: s1 shorter     -> <0", ft_strncmp("ab", "abc", 100) < 0);
	CHECK("n>len: s2 shorter     -> >0", ft_strncmp("abc", "ab", 100) > 0);
	CHECK("n=1 equal             -> 0",  ft_strncmp("abc", "aXX", 1) == 0);
	CHECK("n=1 different         -> !=0",ft_strncmp("abc", "bXX", 1) != 0);
	CHECK("long equal strings    -> 0",  ft_strncmp("abcdefghij", "abcdefghij", 10) == 0);
}

void	test_memchr(void)
{
	char	raw[] = {0x00, 0x01, 0x7F, 0x80, 0xFF, 0x42, 0x00};
	const char *s = "Hello World";
	print_header("memchr");

	CHECK("'W' at pos 6",                ft_memchr(s, 'W', 11) == s + 6);
	CHECK("'H' at pos 0",                ft_memchr(s, 'H', 11) == s);
	CHECK("'d' at pos 10",               ft_memchr(s, 'd', 11) == s + 10);
	CHECK("n=0 -> NULL",                 ft_memchr(s, 'H', 0) == NULL);
	CHECK("not found -> NULL",           ft_memchr(s, 'z', 11) == NULL);
	CHECK("raw: 0x00 at pos 0",          ft_memchr(raw, 0x00, 7) == raw);
	CHECK("raw: 0x01 at pos 1",          ft_memchr(raw, 0x01, 7) == raw + 1);
	CHECK("raw: 0x7F at pos 2",          ft_memchr(raw, 0x7F, 7) == raw + 2);
	CHECK("raw: 0x80 at pos 3",          ft_memchr(raw, 0x80, 7) == raw + 3);
	CHECK("raw: 0xFF at pos 4",          ft_memchr(raw, 0xFF, 7) == raw + 4);
	CHECK("raw: 0x42 at pos 5",          ft_memchr(raw, 0x42, 7) == raw + 5);
	CHECK("does not stop at nul",        ft_memchr(raw, 0x42, 7) == raw + 5);
	CHECK("n limits search",             ft_memchr(raw, 0xFF, 4) == NULL);
	CHECK("finds at exactly n-1",        ft_memchr(raw, 0xFF, 5) == raw + 4);
	CHECK("search -1 == 0xFF",           ft_memchr(raw, -1, 7) == raw + 4);
	CHECK("second 0x00 at pos 6",        ft_memchr(raw + 1, 0x00, 6) == raw + 6);
}

void	test_memcmp(void)
{
	char	a[] = {0x00, 0xFF, 0x01, 0x80};
	char	b[] = {0x00, 0x01, 0xFF, 0x7F};
	print_header("memcmp");

	CHECK("equal n=3             -> 0",  ft_memcmp("abc", "abc", 3) == 0);
	CHECK("n=0                   -> 0",  ft_memcmp("abc", "xyz", 0) == 0);
	CHECK("s1 < s2               -> <0", ft_memcmp("abc", "abd", 3) < 0);
	CHECK("s1 > s2               -> >0", ft_memcmp("abd", "abc", 3) > 0);
	CHECK("unsigned 0xFF>0x01    -> >0", ft_memcmp(a + 1, b + 1, 1) > 0);
	CHECK("unsigned 0x01<0xFF    -> <0", ft_memcmp(b + 1, a + 1, 1) < 0);
	CHECK("unsigned 0x80>0x7F    -> >0", ft_memcmp(a + 3, b + 3, 1) > 0);
	CHECK("compares past nul",           ft_memcmp("ab\0cd", "ab\0ef", 5) < 0);
	CHECK("n=1 same byte         -> 0",  ft_memcmp("abc", "aXX", 1) == 0);
	CHECK("n=1 diff bytes        -> !=0",ft_memcmp("abc", "bXX", 1) != 0);
	CHECK("long equal            -> 0",  ft_memcmp("0123456789", "0123456789", 10) == 0);
	CHECK("diff in last byte",           ft_memcmp("abcX", "abcY", 4) != 0);
	CHECK("n=4 equal             -> 0",  ft_memcmp("abc\0", "abc\0", 4) == 0);
}

void	test_strnstr(void)
{
	const char	*h = "lorem ipsum dolor sit amet";
	print_header("strnstr");

	CHECK("finds \"ipsum\"",             ft_strnstr(h, "ipsum", 26) == h + 6);
	CHECK("finds at start",              ft_strnstr(h, "lorem", 26) == h);
	CHECK("finds \"amet\"",              ft_strnstr(h, "amet", 26) != NULL);
	CHECK("finds at end",                ft_strnstr("abcdef", "ef", 6) == (char*)"abcdef" + 4);
	CHECK("empty needle -> haystack",    ft_strnstr(h, "", 26) == h);
	CHECK("empty needle n=0 -> h",       ft_strnstr("abc", "", 0) != NULL);
	CHECK("needle outside len -> NULL",  ft_strnstr(h, "ipsum", 5) == NULL);
	CHECK("not found -> NULL",           ft_strnstr(h, "xyz", 26) == NULL);
	CHECK("needle longer -> NULL",       ft_strnstr("ab", "abc", 2) == NULL);
	{ const char *_h = "abc"; CHECK("needle==haystack", ft_strnstr(_h, "abc", 3) != NULL); }
	CHECK("len=0 non-empty needle->NULL",ft_strnstr("abc", "a", 0) == NULL);
	CHECK("finds exactly at limit",      ft_strnstr("abcde", "de", 5) != NULL);
	CHECK("past limit -> NULL",          ft_strnstr("abcde", "de", 4) == NULL);
	CHECK("needle 1 char: found",        ft_strnstr("hello", "h", 5) != NULL);
	CHECK("needle 1 char: not found",    ft_strnstr("hello", "z", 5) == NULL);
	CHECK("both empty: returns ptr",     ft_strnstr("", "", 0) != NULL);
	{ const char *_h = "ababab"; CHECK("returns first occurrence", ft_strnstr(_h, "ab", 6) == _h); }
	CHECK("len=1: finds 1 char",         ft_strnstr("abc", "a", 1) != NULL);
	CHECK("len=1: 2-char needle -> NULL",ft_strnstr("abc", "ab", 1) == NULL);
}

void	test_atoi(void)
{
	print_header("atoi");
	CHECK("\"0\"                   -> 0",    ft_atoi("0") == 0);
	CHECK("\"1\"                   -> 1",    ft_atoi("1") == 1);
	CHECK("\"-1\"                  -> -1",   ft_atoi("-1") == -1);
	CHECK("\"42\"                  -> 42",   ft_atoi("42") == 42);
	CHECK("\"-42\"                 -> -42",  ft_atoi("-42") == -42);
	CHECK("\"+42\"                 -> 42",   ft_atoi("+42") == 42);
	CHECK("\" 42\" space",                   ft_atoi(" 42") == 42);
	CHECK("\"  42\" 2 spaces",               ft_atoi("  42") == 42);
	CHECK("\"\\t42\" tab",                   ft_atoi("\t42") == 42);
	CHECK("\"\\n42\" LF",                    ft_atoi("\n42") == 42);
	CHECK("\"\\r42\" CR",                    ft_atoi("\r42") == 42);
	CHECK("\"\\f42\" FF",                    ft_atoi("\f42") == 42);
	CHECK("\"\\v42\" VT",                    ft_atoi("\v42") == 42);
	CHECK("\"\\t\\n 42\" mixed ws",          ft_atoi("\t\n 42") == 42);
	CHECK("\" -42\" space+neg",              ft_atoi(" -42") == -42);
	CHECK("\" +42\" space+pos",              ft_atoi(" +42") == 42);
	CHECK("\"42abc\" stops at letter -> 42", ft_atoi("42abc") == 42);
	CHECK("\"42 43\"              -> 42",    ft_atoi("42 43") == 42);
	CHECK("\"12.34\"              -> 12",    ft_atoi("12.34") == 12);
	CHECK("\"abc\"               -> 0",      ft_atoi("abc") == 0);
	CHECK("\"\"                  -> 0",      ft_atoi("") == 0);
	CHECK("\"-\"                 -> 0",      ft_atoi("-") == 0);
	CHECK("\"+\"                 -> 0",      ft_atoi("+") == 0);
	CHECK("\"--42\"              -> 0",      ft_atoi("--42") == 0);
	CHECK("\"+-42\"              -> 0",      ft_atoi("+-42") == 0);
	CHECK("\"-+42\"              -> 0",      ft_atoi("-+42") == 0);
	CHECK("INT_MAX  2147483647",             ft_atoi("2147483647") == 2147483647);
	CHECK("INT_MIN -2147483648",             ft_atoi("-2147483648") == -2147483648);
	CHECK("\"0042\"              -> 42",     ft_atoi("0042") == 42);
	CHECK("\"007\"               -> 7",      ft_atoi("007") == 7);
	CHECK("\"   -0\"             -> 0",      ft_atoi("   -0") == 0);
	CHECK("overflow+ matches libc",          ft_atoi("9999999999") == atoi("9999999999"));
	CHECK("overflow- matches libc",          ft_atoi("-9999999999") == atoi("-9999999999"));
}

void	test_calloc(void)
{
	char	*p;
	int		i;
	print_header("calloc");

	p = ft_calloc(10, 1);
	CHECK("10*1: not NULL",              p != NULL);
	if (p) {
		i = 0; while (i < 10 && p[i] == 0) i++;
		CHECK("10 bytes all zero",       i == 10);
		free(p);
	}
	p = ft_calloc(1, 10);
	CHECK("1*10: not NULL",              p != NULL);
	if (p) {
		i = 0; while (i < 10 && p[i] == 0) i++;
		CHECK("1*10: 10 bytes zero",     i == 10);
		free(p);
	}
	p = ft_calloc(4, sizeof(int));
	CHECK("4 ints: not NULL",            p != NULL);
	if (p) {
		i = 0; while (i < (int)(4 * sizeof(int)) && p[i] == 0) i++;
		CHECK("4 ints: all zero",        i == (int)(4 * sizeof(int)));
		free(p);
	}
	p = ft_calloc(0, 1);
	CHECK("calloc(0,1) != NULL",         p != NULL);
	if (p) free(p);
	p = ft_calloc(1, 0);
	CHECK("calloc(1,0) != NULL",         p != NULL);
	if (p) free(p);
	p = ft_calloc(0, 0);
	CHECK("calloc(0,0) != NULL",         p != NULL);
	if (p) free(p);
	p = ft_calloc(1, 1);
	CHECK("calloc(1,1): byte=0",         p && p[0] == 0);
	if (p) free(p);
	p = ft_calloc(100, 1);
	CHECK("100 bytes: not NULL",         p != NULL);
	if (p) {
		i = 0; while (i < 100 && p[i] == 0) i++;
		CHECK("100 bytes: all zero",     i == 100);
		free(p);
	}
}

void	test_strdup(void)
{
	char	*p;
	print_header("strdup");

	p = ft_strdup("hello");
	CHECK("duplicates \"hello\"",        p && strcmp(p, "hello") == 0);
	CHECK("nul at p[5]",                 p && p[5] == '\0');
	CHECK("correct length",              p && strlen(p) == 5);
	if (p) { p[0] = 'H'; CHECK("memory is writable", p[0] == 'H'); }
	free(p);

	p = ft_strdup("");
	CHECK("empty: not NULL",             p != NULL);
	CHECK("empty: p[0]='\\0'",           p && p[0] == '\0');
	CHECK("empty: strlen=0",             p && strlen(p) == 0);
	free(p);

	p = ft_strdup("a");
	CHECK("1 char: correct",             p && strcmp(p, "a") == 0);
	CHECK("1 char: nul at p[1]",         p && p[1] == '\0');
	free(p);

	p = ft_strdup("Hello, World! 42");
	CHECK("long string",                 p && strcmp(p, "Hello, World! 42") == 0);
	free(p);

	p = ft_strdup("abc\ndef");
	CHECK("with newline",                p && strcmp(p, "abc\ndef") == 0);
	free(p);

	p = ft_strdup("abc\tdef");
	CHECK("with tab",                    p && strcmp(p, "abc\tdef") == 0);
	free(p);

	p = ft_strdup("   ");
	CHECK("only spaces: len=3",          p && strlen(p) == 3);
	free(p);

	p = ft_strdup("123456789");
	CHECK("numeric string",              p && strcmp(p, "123456789") == 0);
	free(p);
}
