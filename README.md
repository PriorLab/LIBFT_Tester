# libft Mega Tester

> ⚠️ **DISCLAIMER** ⚠️
>
> **This tester was generated with the help of AI and is provided only as a guide.**
> Errors and false positives may occur. Always verify results manually and cross-check
> with other testers — they may be more complete or more accurate.
> **Do not rely solely on this tester to validate a libft submission as new updates and furthers tests can be made.**
>
> Other recommended testers:
> - [francinette](https://github.com/xicodomingues/francinette)
> - [libftTester](https://github.com/Tripouille/libftTester)

---
Give it a like if it helped you.
A functional tester for the **libft** project at 42 (subject v19.2).
Includes **1036 functional tests** + **automated structure, norm, and code quality checks**.

**Requirements:** `cc`, `bash`, `awk`, `gcc` (all standard on any 42 machine).
No Python, no extra dependencies.

---

## Expected structure

```
42/
├── Libft/              ← student repository
│   ├── Makefile
│   ├── libft.h
│   ├── ft_*.c          ← Part 1 + Part 2
│   └── ft_lst*.c       ← Part 3 (mandatory)
│
└── libft_tester_v2/    ← this tester
    ├── Makefile
    ├── check_manual.sh
    ├── README.md
    ├── main.c
    ├── utils/
    │   ├── tester.h
    │   └── tester.c
    └── tests/
        ├── test_part1.c
        ├── test_part2.c
        ├── test_part3.c
        └── test_extra.c
```

---

## Installation

```bash
# 1. Go to the folder containing the student's Libft
cd ~/42

# 2. Extract the tester (it becomes a sibling of Libft)
tar -xzf libft_tester_v2.tar.gz

# 3. Confirm the structure
ls
# should show: Libft/  libft_tester_v2/

# 4. Enter the tester
cd libft_tester_v2
```

If your Libft has a different name or location:
```bash
make LIBFT_DIR=/absolute/path/to/libft
```

---

## Commands

| Command | Description |
|---|---|
| `make` | Compiles libft + runs **1036 functional tests** |
| `make leaks` | Same as `make` but with **valgrind** (detects memory leaks) |
| `make check` | **13 automated checks** — structure, static helpers, forbidden functions, README |
| `make clean` | Removes the tester binary |
| `make re` | Full clean rebuild |

---

## `make` — 1036 functional tests

Tests are split into 5 sections that run sequentially.
A `[CRASH]` (segfault) is caught and the remaining tests continue regardless.

### Part 1 — Libc functions (23 functions)

| Function | Notable edge cases tested |
|---|---|
| `ft_isalpha/digit/alnum/ascii/print` | Return **exactly 1 or 0** (not just `!= 0`), all chars 0–127 swept |
| `ft_toupper / ft_tolower` | Boundaries `@`, `[`, `` ` ``, `{` must remain unchanged |
| `ft_strlen` | Stops at `'\0'`, does not count it, returns `size_t` |
| `ft_memset` | Negative value truncated to `unsigned char`, `n=0` changes nothing, returns `dst` |
| `ft_bzero` | Correct byte count, `n=0` and `n=1` boundaries |
| `ft_memcpy` | Raw bytes `0xFF`, `0x00`, `n=0`, returns `dst`, does not read past `n` |
| `ft_memmove` | Overlap `dst > src`, `dst < src`, `dst == src` all correct |
| `ft_strlcpy` | Always returns `strlen(src)` even with `size=0`, nul-terminator guaranteed |
| `ft_strlcat` | Behaviour when `size <= strlen(dst)`, always returns `strlen(dst)+strlen(src)` |
| `ft_strchr / ft_strrchr` | Finds `'\0'`, `int 256 == unsigned char 0` |
| `ft_strncmp / ft_memcmp` | **Unsigned** byte comparison (`0xFF > 0x01`), does not stop at `'\0'` |
| `ft_memchr` | Does not stop at `'\0'`, `n` limits search, search `-1 == 0xFF` |
| `ft_strnstr` | Empty needle returns `haystack`, `len=0` with non-empty needle returns `NULL` |
| `ft_atoi` | All 6 whitespace chars (`\t\n\r\f\v`), double signs, overflow matches libc |
| `ft_calloc` | `calloc(0, x)` and `calloc(x, 0)` return a unique freeable pointer |
| `ft_strdup` | Exact byte copy, memory is writable, correct length |

### Part 2 — Additional functions (11 functions)

| Function | Notable edge cases tested |
|---|---|
| `ft_substr` | `start >= strlen` returns `""`, `len > available` copies to end, `start=100` allocates `>= 1` byte |
| `ft_strjoin` | Correct nul-terminator, correct allocation size |
| `ft_strtrim` | Set is **individual chars**, not a substring — `"ab"` removes `a` and `b` separately |
| `ft_split` | NULL-terminator on array AND each string, consecutive delimiters, delimiter at start/end |
| `ft_itoa` | `INT_MIN = -2147483648` (breaks naive `-n` implementations) |
| `ft_strmapi` | Correct index passed, original string unmodified, new allocation returned |
| `ft_striteri` | In-place modification, correct index, empty string no crash |
| `ft_putchar/str/endl/nbr_fd` | Tested via pipe, exact byte count verified, INT_MIN handled |

### Part 3 — Linked list (9 functions)

| Function | Notable edge cases tested |
|---|---|
| `ft_lstnew` | `content NULL`, `next` always `NULL` on creation |
| `ft_lstadd_front` | Head updated, correct chain after multiple adds |
| `ft_lstsize` | `NULL` list returns 0, list not modified |
| `ft_lstlast` | `NULL` list returns `NULL`, `last->next == NULL` |
| `ft_lstadd_back` | Head unchanged, tail updated correctly |
| `ft_lstdelone` | Does **not** touch `next` node, `del` called on `content` |
| `ft_lstclear` | `*lst = NULL` at end, double clear without crash, 50-node list |
| `ft_lstiter` | Correct order, list unchanged, `NULL` does not call `f` |
| `ft_lstmap` | New list independent from original, original intact after mapping |

### Extra — Deep edge cases

Additional tests inspired by **Tripouille's libftTester** and **francinette**:

- **Allocation size checks** using `malloc_usable_size()` — verifies that functions allocate
  exactly the right number of bytes (e.g. `substr("tripouille", 100, 1)` must allocate `>= 1`
  byte for the nul, not 0; `strjoin` must allocate `strlen(s1)+strlen(s2)+1`)
- **NULL protection** — `calloc(SIZE_MAX, SIZE_MAX)` must return `NULL`
- **Exhaustive char sweep** — `isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint`,
  `toupper`, `tolower` verified for every value 0–127
- **Combined function tests** — `strlcpy` + `strlcat` chained, `substr` + `strjoin`, etc.
- **Boundary arithmetic** — `INT_MAX`, `INT_MIN`, `SIZE_MAX` across all relevant functions

---

## `make leaks` — Memory leak detection

Runs the same 1036 tests under **valgrind**:
```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
```
Any unreleased memory causes the command to exit with an error code.

---

## `make check` — 13 automated checks

No Python required. Uses only `bash`, `awk`, `gcc`, and `grep`.

| # | Check | What it detects |
|---|---|---|
| 1 | **Mandatory files** | All 43 `.c` files present (Part 1 + 2 + 3) |
| 2 | **Makefile rules** | `all`, `clean`, `fclean`, `re`, `bonus`, `NAME` present |
| 3 | **ar vs libtool** | `libtool` is forbidden — must use `ar` |
| 4 | **Relinking** | Second `make` must not recompile anything |
| 5 | **Active test code** | `printf`, `scanf`, `main()` outside comments (uses `gcc -E`) |
| 6 | **Global variables** | Declarations at global scope — forbidden by subject |
| 7 | **Files at root** | No `.c` files in subdirectories |
| 8 | **t_list in header** | Struct with `content` and `next` declared in `libft.h` |
| 9 | **Files in Makefile** | Every `.c` file referenced in the Makefile |
| 10 | **Static helpers** | Helper functions (non-`ft_*`) must be `static` |
| 11 | **Forbidden functions** | Each function only uses what the subject allows |
| 12 | **README.md** | All required sections from subject v19.2 |
| 13 | **Norminette** | 0 errors — one norm error = 0 on the entire project |

### Check 10 — Static helpers in detail

Finds function definitions inside `ft_*.c` files that are not the main `ft_*` function
of that file and are not declared `static`. Uses `awk` to track brace depth and
only flags definitions at global scope (depth 0).

### Check 11 — Forbidden functions in detail

Verifies each function only uses what the subject explicitly permits:

| Functions | Allowed |
|---|---|
| `isalpha`, `isdigit`, ..., `atoi`, `striteri` | Nothing |
| `calloc`, `strdup`, `substr`, `strjoin`, `strtrim`, `split`, `itoa`, `strmapi` | `malloc` only |
| `putchar_fd`, `putstr_fd`, `putendl_fd`, `putnbr_fd` | `write` only |
| `lstnew`, `lstmap`, `lstclear`, `lstdelone` | `malloc` + `free` |

> Note: indirect calls via function pointers cannot be detected automatically.

### Check 12 — README.md in detail

Verifies all sections required by subject v19.2:
- First line italicised, mentioning the 42 curriculum and a login
- `Description` section
- `Instructions` section (compilation, installation, execution)
- `Resources` section (documentation, references)
- Mention of AI usage (or explicit statement that it was not used)
- Detailed description of the library functions

---

## Requirements

| Tool | Required for | Notes |
|---|---|---|
| `cc` | `make`, `make leaks` | Always available on 42 machines |
| `gcc` | `make check` | Used to strip comments; falls back to `sed` if unavailable |
| `bash` + `awk` | `make check` | Always available |
| `valgrind` | `make leaks` | Linux only |
| `norminette` | `make check` | Optional — warns if not installed |

---

