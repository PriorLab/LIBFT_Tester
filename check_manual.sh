#!/bin/bash
# =============================================================
#  LIBFT - Manual Checks  (bash only, no python required)
#  Usage: bash check_manual.sh /path/to/Libft
#         or: make check
# =============================================================

LIBFT="$1"
if [ -z "$LIBFT" ]; then
    LIBFT="$(dirname $(pwd))/Libft"
fi

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

pass=0
fail=0
warn_count=0

ok()   { echo -e "  ${GREEN}[OK]${RESET}   $1"; pass=$((pass + 1)); }
ko()   { echo -e "  ${RED}[KO]${RESET}   $1"; fail=$((fail + 1)); }
warn() { echo -e "  ${YELLOW}[!!]${RESET}   $1"; warn_count=$((warn_count + 1)); }
hdr()  { echo -e "\n${BOLD}${CYAN}══════════════════════════════════════${RESET}";
         echo -e "${BOLD}${CYAN}  $1${RESET}";
         echo -e "${BOLD}${CYAN}══════════════════════════════════════${RESET}"; }

# Strip C comments from a file using gcc preprocessor (available everywhere cc is)
# Falls back to a simpler sed approach if gcc fails
strip_comments() {
    local file="$1"
    # Use gcc to strip comments — works on any system with cc
    gcc -fpreprocessed -dD -E "$file" 2>/dev/null | grep -v "^#" || \
    # Fallback: crude sed (won't handle multiline /* */ perfectly but catches most cases)
    sed 's|//.*||g; s|/\*[^*]*\*\+\([^/*][^*]*\*\+\)*/||g' "$file"
}

echo -e "${BOLD}Libft path: $LIBFT${RESET}"

# ── 1. Mandatory files ────────────────────────────────────────
hdr "1. Mandatory files (Part 1 + 2 + 3)"

if test -f "$LIBFT/libft.h"; then ok "libft.h exists"; else ko "libft.h missing"; fi
if test -f "$LIBFT/Makefile"; then ok "Makefile exists"; else ko "Makefile missing"; fi

ALL_FUNCTIONS="ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
               ft_toupper ft_tolower ft_strlen ft_memset ft_bzero ft_memcpy \
               ft_memmove ft_strlcpy ft_strlcat ft_strchr ft_strrchr ft_strncmp \
               ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strdup \
               ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi \
               ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
               ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
               ft_lstdelone ft_lstclear ft_lstiter ft_lstmap"

all_present=1
for fn in $ALL_FUNCTIONS; do
    if ! test -f "$LIBFT/${fn}.c"; then
        ko "${fn}.c is MISSING"
        all_present=0
    fi
done
[ $all_present -eq 1 ] && ok "all 43 mandatory files present"

# ── 2. Makefile rules ─────────────────────────────────────────
hdr "2. Makefile — mandatory rules"

for rule in all clean fclean re bonus; do
    grep -qE "^$rule\s*:" "$LIBFT/Makefile" \
        && ok "rule '$rule' exists" \
        || ko "rule '$rule' is MISSING"
done
grep -qE "^\\\$\(NAME\)\s*:|^NAME\s*:=" "$LIBFT/Makefile" \
    && ok "NAME variable/rule exists" \
    || ko "NAME missing from Makefile"

# ── 3. ar vs libtool ─────────────────────────────────────────
hdr "3. ar vs libtool"

grep -q "libtool" "$LIBFT/Makefile" \
    && ko "uses libtool — FORBIDDEN by the subject" \
    || ok "does not use libtool"
grep -qE "\bar\b" "$LIBFT/Makefile" \
    && ok "uses 'ar' to build the library" \
    || ko "'ar' not found in Makefile"

# ── 4. Unnecessary relinking ──────────────────────────────────
hdr "4. Unnecessary relinking"

make -C "$LIBFT" > /dev/null 2>&1
OUTPUT=$(make -C "$LIBFT" 2>&1)
if echo "$OUTPUT" | grep -qiE "Nothing to be done|is up to date"; then
    ok "no unnecessary relinking"
else
    ko "unnecessary relinking (second 'make' recompiled something)"
    echo "$OUTPUT" | head -5 | sed 's/^/    /'
fi

# ── 5. Active test code ───────────────────────────────────────
hdr "5. Active test code (printf/scanf/main outside comments)"

TEST_FOUND=0
for f in "$LIBFT"/ft_*.c; do
    # Use gcc to strip comments, then search for test code
    cleaned=$(strip_comments "$f")
    if echo "$cleaned" | grep -qE "\bprintf\b|\bscanf\b|\bputs\b"; then
        ko "$(basename $f): active printf/scanf/puts found"
        TEST_FOUND=1
    fi
    if echo "$cleaned" | grep -qE "^\s*int\s+main\s*\("; then
        ko "$(basename $f): active main() found"
        TEST_FOUND=1
    fi
done
[ $TEST_FOUND -eq 0 ] && ok "no active test code found"

# ── 6. Global variables ───────────────────────────────────────
hdr "6. Global variables (FORBIDDEN)"

# Strategy: look for lines that start at column 0 with a C type,
# end with ';', have no '(' or ')', and are NOT static/extern/typedef/#
# We use awk to track brace depth and only flag depth==0 declarations
GLOBAL_FOUND=0
for f in "$LIBFT"/ft_*.c; do
    cleaned=$(strip_comments "$f")
    result=$(echo "$cleaned" | awk '
        BEGIN { depth = 0 }
        {
            # Count braces
            for (i = 1; i <= length($0); i++) {
                c = substr($0, i, 1)
                if (c == "{") depth++
                else if (c == "}") depth--
            }
            # At global scope (depth==0), look for variable declarations
            if (depth == 0) {
                line = $0
                # Skip empty, preprocessor, static, extern, typedef
                if (line ~ /^[[:space:]]*$/) next
                if (line ~ /^[[:space:]]*#/) next
                if (line ~ /static/) next
                if (line ~ /extern/) next
                if (line ~ /typedef/) next
                # Must end with ; and have no () (to exclude function decls)
                if (line ~ /;$/ && line !~ /\(/ && line !~ /\)/) {
                    # Must start with a C type keyword
                    if (line ~ /^[[:space:]]*(int|char|long|float|double|size_t|unsigned|void\*)/) {
                        print NR ": " line
                    }
                }
            }
        }
    ')
    if [ -n "$result" ]; then
        ko "global variable in $(basename $f):"
        echo "$result" | sed 's/^/    /'
        GLOBAL_FOUND=1
    fi
done
[ $GLOBAL_FOUND -eq 0 ] && ok "no global variables found"

# ── 7. Files at root ─────────────────────────────────────────
hdr "7. Files at repository root"

SUBDIR=$(find "$LIBFT" -name "ft_*.c" -mindepth 2 2>/dev/null)
if [ -n "$SUBDIR" ]; then
    ko "ft_*.c files in subdirectories (must be at root):"
    echo "$SUBDIR" | sed 's/^/    /'
else
    ok "all ft_*.c files are at root"
fi

# ── 8. t_list in header ───────────────────────────────────────
hdr "8. libft.h — t_list struct (mandatory)"

if grep -q "t_list" "$LIBFT/libft.h" 2>/dev/null; then
    ok "t_list declared in libft.h"
    grep -q "content" "$LIBFT/libft.h" && ok "'content' member present" || ko "'content' member missing"
    grep -q "next"    "$LIBFT/libft.h" && ok "'next' member present"    || ko "'next' member missing"
else
    ko "t_list missing from libft.h — MANDATORY"
fi

# ── 9. Unreferenced files ─────────────────────────────────────
hdr "9. Files not referenced in Makefile"

UNUSED=0
for f in "$LIBFT"/ft_*.c; do
    base=$(basename "$f")
    grep -q "$base" "$LIBFT/Makefile" || { ko "$base is not in the Makefile"; UNUSED=1; }
done
[ $UNUSED -eq 0 ] && ok "all .c files are referenced in Makefile"

# ── 10. Helper functions are static ──────────────────────────
hdr "10. Helper functions must be static"

# For each ft_*.c file, look for function definitions that:
# - start at column 0 (not indented)
# - are NOT the ft_* function the file is named after
# - are NOT declared as static
# We use a simple awk: find lines matching "type name(" at depth 0
STATIC_ISSUES=0
for f in "$LIBFT"/ft_*.c; do
    ft_name=$(basename "$f" .c)   # e.g. ft_split
    cleaned=$(strip_comments "$f")
    result=$(echo "$cleaned" | awk -v ftname="$ft_name" '
        BEGIN { depth = 0 }
        {
            for (i = 1; i <= length($0); i++) {
                c = substr($0, i, 1)
                if (c == "{") depth++
                else if (c == "}") depth--
            }
            # Function definition: at depth 0 (before the opening brace of the func),
            # starts with a type, not static, not the main ft_ function
            if (depth == 0) {
                line = $0
                # Skip preprocessor, empty, static, extern
                if (line ~ /^[[:space:]]*#/) next
                if (line ~ /^[[:space:]]*$/) next
                if (line ~ /static/) next
                if (line ~ /extern/) next
                if (line ~ /typedef/) next
                # Look for: return_type funcname( pattern at start of line
                if (match(line, /^[a-zA-Z_][a-zA-Z0-9_ \t\*]+[[:space:]]([a-zA-Z_][a-zA-Z0-9_]*)[[:space:]]*\(/, arr)) {
                    fname = arr[1]
                    # Skip the main ft_ function and control flow keywords
                    if (fname == ftname) next
                    if (fname ~ /^(if|while|for|return|sizeof|else)$/) next
                    # Skip if line ends with ; (declaration, not definition)
                    if (line ~ /;[[:space:]]*$/) next
                    print NR ": " line " — not static"
                }
            }
        }
    ')
    if [ -n "$result" ]; then
        ko "non-static helper in $(basename $f):"
        echo "$result" | sed 's/^/    /'
        STATIC_ISSUES=1
    fi
done
[ $STATIC_ISSUES -eq 0 ] && ok "all helper functions appear to be static"

# ── 11. Forbidden external functions ─────────────────────────
hdr "11. Forbidden external functions"

FORBIDDEN_FOUND=0

# Functions that must use NO external functions
NO_EXT="ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
        ft_toupper ft_tolower ft_strlen ft_memset ft_bzero \
        ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_strchr \
        ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi \
        ft_striteri"

for fn in $NO_EXT; do
    f="$LIBFT/${fn}.c"
    [ -f "$f" ] || continue
    cleaned=$(strip_comments "$f")
    # Look for calls to clearly forbidden functions
    for forbidden in malloc free calloc realloc printf fprintf write read exit; do
        if echo "$cleaned" | grep -qE "\b${forbidden}\s*\("; then
            ko "${fn}.c uses forbidden: ${forbidden}()"
            FORBIDDEN_FOUND=1
        fi
    done
done

# write-only functions (putchar_fd, putstr_fd, putendl_fd, putnbr_fd)
WRITE_ONLY="ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd"
for fn in $WRITE_ONLY; do
    f="$LIBFT/${fn}.c"
    [ -f "$f" ] || continue
    cleaned=$(strip_comments "$f")
    for forbidden in malloc free calloc printf scanf; do
        if echo "$cleaned" | grep -qE "\b${forbidden}\s*\("; then
            ko "${fn}.c uses forbidden: ${forbidden}()"
            FORBIDDEN_FOUND=1
        fi
    done
done

# malloc-only functions — check they don't use write/printf
MALLOC_ONLY="ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi"
for fn in $MALLOC_ONLY; do
    f="$LIBFT/${fn}.c"
    [ -f "$f" ] || continue
    cleaned=$(strip_comments "$f")
    for forbidden in printf fprintf scanf write; do
        if echo "$cleaned" | grep -qE "\b${forbidden}\s*\("; then
            ko "${fn}.c uses forbidden: ${forbidden}()"
            FORBIDDEN_FOUND=1
        fi
    done
done

[ $FORBIDDEN_FOUND -eq 0 ] && ok "no obvious forbidden external functions found"
warn "Note: indirect calls (via function pointers) cannot be detected automatically"

# ── 12. README.md ────────────────────────────────────────────
hdr "12. README.md (required by subject v19.2)"

README=""
for name in README.md readme.md README README.txt; do
    [ -f "$LIBFT/$name" ] && README="$LIBFT/$name" && break
done

if [ -z "$README" ]; then
    ko "README.md not found — MANDATORY"
else
    ok "README.md found: $(basename $README)"

    FIRST=$(head -1 "$README")
    # First line must be italicized and mention "42 curriculum" and a login
    if echo "$FIRST" | grep -qiE "created.*42|42.*curriculum|42.*project|42.*by"; then
        ok "first line references the 42 curriculum"
    else
        ko "first line must read: '*This project has been created as part of the 42 curriculum by <login>*'"
        echo "    Got: $FIRST" | cut -c1-100
    fi

    CONTENT=$(cat "$README")

    echo "$CONTENT" | grep -qiE "##?\s*Description|Description" \
        && ok "has 'Description' section" \
        || ko "missing 'Description' section"

    echo "$CONTENT" | grep -qiE "##?\s*(Instructions|Usage|Compilation|Installation|How to)" \
        && ok "has 'Instructions'/'Usage' section" \
        || ko "missing 'Instructions' section"

    echo "$CONTENT" | grep -qiE "##?\s*(Resources|References|Links|Sources)" \
        && ok "has 'Resources' section" \
        || ko "missing 'Resources' section"

    echo "$CONTENT" | grep -qiE "\bAI\b|artificial intelligence|ChatGPT|Claude|GPT|Copilot|LLM" \
        && ok "README mentions AI usage (required)" \
        || ko "README must describe how AI was used (or that it was not used)"

    echo "$CONTENT" | grep -qiE "libft|library|ft_|functions" \
        && ok "README describes the library" \
        || ko "README must include a detailed description of the library"

    LINE_COUNT=$(wc -l < "$README")
    if [ "$LINE_COUNT" -gt 20 ]; then
        ok "README length looks good ($LINE_COUNT lines)"
    else
        warn "README seems short ($LINE_COUNT lines) — subject requires detailed content"
    fi
fi

# ── 13. Norminette ───────────────────────────────────────────
hdr "13. Norminette"

if command -v norminette > /dev/null 2>&1; then
    NORM_OUT=$(norminette "$LIBFT"/ft_*.c "$LIBFT"/libft.h 2>&1)
    NORM_ERR=$(echo "$NORM_OUT" | grep -c "Error" || true)
    NORM_ERR=$(echo "$NORM_ERR" | tr -d '[:space:]')
    if [ "$NORM_ERR" = "0" ]; then
        ok "norminette: 0 errors"
    else
        ko "norminette: $NORM_ERR error(s)"
        echo "$NORM_OUT" | grep "Error" | head -20 | sed 's/^/    /'
    fi
else
    warn "norminette not installed — run manually: norminette *.c *.h"
fi

# ── Summary ───────────────────────────────────────────────────
echo -e "\n${BOLD}══════════════════════════════════════${RESET}"
echo -e "${BOLD}  SUMMARY${RESET}"
echo -e "${BOLD}══════════════════════════════════════${RESET}"
echo -e "  Total:   $((pass + fail))"
echo -e "  ${GREEN}Passed:  $pass${RESET}"
[ "$fail" -gt 0 ]       && echo -e "  ${RED}Failed:  $fail${RESET}"
[ "$warn_count" -gt 0 ] && echo -e "  ${YELLOW}Warnings:$warn_count${RESET}"

if [ "$fail" -gt 0 ]; then
    echo -e "\n${BOLD}${RED}  x Issues found — see above${RESET}\n"
else
    echo -e "\n${BOLD}${GREEN}  v All checks passed${RESET}\n"
fi
echo -e "${YELLOW}  REMINDER: norminette is the most critical check!${RESET}"
echo -e "${YELLOW}  One norm error = 0 on the entire project.\n${RESET}"
