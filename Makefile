.DEFAULT_GOAL := all

CC     = cc
CFLAGS = -Wall -Wextra -Werror -g3
BIN      = tester_all
BIN_NOP3 = tester_nop3
SRCS_BASE = utils/tester.c tests/test_part1.c tests/test_part2.c \
            tests/test_extra.c main.c
SRCS_P3   = tests/test_part3.c
LIBFT_DIR = $(shell dirname $(shell pwd))/Libft

.PHONY: all leaks check clean re

all:
	@printf "\033[1;36m[*] Building libft...\033[0m\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory re
	@# Try 'bonus' if it exists — if not, 'all' already has everything
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory bonus 2>/dev/null || true
	@ar rcs $(LIBFT_DIR)/libft.a $(LIBFT_DIR)/*.o 2>/dev/null || true
	@test -f $(LIBFT_DIR)/libft.a || \
		(printf "\033[1;31m[ERROR] libft.a not found after make\033[0m\n" && exit 1)
	@printf "\033[1;32m[ok] libft built\033[0m\n"
	@printf "\033[1;34m[*] Compiling tester...\033[0m\n"
	@if $(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iutils \
		$(SRCS_BASE) $(SRCS_P3) -L$(LIBFT_DIR) -lft -o $(BIN) 2>/dev/null; then \
		printf "\033[1;32m[ok] Part 1 + 2 + 3\033[0m\n" && echo "" && ./$(BIN); \
	elif $(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iutils \
		$(SRCS_BASE) -DNO_PART3 -L$(LIBFT_DIR) -lft -o $(BIN_NOP3) 2>/dev/null; then \
		printf "\033[1;33m[!] Part 3 missing — running Part 1 + 2 only\033[0m\n" && echo "" && ./$(BIN_NOP3); \
	else \
		printf "\033[1;31m[ERROR] Compilation failed\033[0m\n" && exit 1; \
	fi

leaks:
	@if [ -f $(BIN) ]; then \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --error-exitcode=1 -q ./$(BIN); \
	elif [ -f $(BIN_NOP3) ]; then \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --error-exitcode=1 -q ./$(BIN_NOP3); \
	else \
		echo "Run 'make' first"; exit 1; \
	fi

check:
	@bash check_manual.sh $(LIBFT_DIR)

clean:
	@rm -f $(BIN) $(BIN_NOP3)
	@printf "\033[1;33m[ok] cleaned\033[0m\n"

re: clean all
