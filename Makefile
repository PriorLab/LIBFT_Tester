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
	@printf "\033[1;36m[*] A compilar a libft (all + bonus)...\033[0m\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory re
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory bonus
	@ar rcs $(LIBFT_DIR)/libft.a $(LIBFT_DIR)/*.o
	@printf "\033[1;32m[ok] libft compilada\033[0m\n"
	@printf "\033[1;34m[*] A compilar o tester...\033[0m\n"
	@if $(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iutils \
		$(SRCS_BASE) $(SRCS_P3) -L$(LIBFT_DIR) -lft -o $(BIN) 2>/dev/null; then \
		printf "\033[1;32m[ok] Part 1 + 2 + 3\033[0m\n" && echo "" && ./$(BIN); \
	elif $(CC) $(CFLAGS) -I$(LIBFT_DIR) -Iutils \
		$(SRCS_BASE) -DNO_PART3 -L$(LIBFT_DIR) -lft -o $(BIN_NOP3) 2>/dev/null; then \
		printf "\033[1;33m[!] Part 3 em falta — so Part 1 e 2\033[0m\n" && echo "" && ./$(BIN_NOP3); \
	else \
		printf "\033[1;31m[ERRO] Nao compilou\033[0m\n" && exit 1; \
	fi

leaks:
	@if [ -f $(BIN) ]; then \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --error-exitcode=1 -q ./$(BIN); \
	elif [ -f $(BIN_NOP3) ]; then \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --error-exitcode=1 -q ./$(BIN_NOP3); \
	else \
		echo "Corre 'make' primeiro"; exit 1; \
	fi

check:
	@bash check_manual.sh $(LIBFT_DIR)

clean:
	@rm -f $(BIN) $(BIN_NOP3)
	@printf "\033[1;33m[ok] limpo\033[0m\n"

re: clean all
