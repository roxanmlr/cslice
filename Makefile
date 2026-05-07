NAME     = test_cslice
CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g -fsanitize=address,undefined

ROOT_SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard tests/*_test.c)
TEST_BINS = $(patsubst tests/%_test.c,bin/test_%,$(TEST_SRCS))

all: $(NAME)

$(NAME): $(ROOT_SRCS) cslice.h
	$(CC) $(CFLAGS) $(ROOT_SRCS) -o $@

# Build all individual test binaries
tests: $(TEST_BINS)

# Build one binary:          make bin/test_sl_new
bin/test_%: tests/%_test.c cslice.c cslice.h | bin
	$(CC) $(CFLAGS) cslice.c $< -o $@

bin:
	mkdir -p bin

# Build and run one test:    make test_sl_new
test_%: bin/test_%
	$<

# Build and run every test
run_tests: tests
	@for t in $(TEST_BINS); do echo "--- $$t ---"; $$t; done

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME) $(TEST_BINS)

re: fclean all

.PHONY: all tests run_tests clean fclean re
