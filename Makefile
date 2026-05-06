NAME = test_cslice
SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJS = $(patsubst objs/%.o,%.c,$(SRCS))
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined

all: $(NAME)
$(NAME): $(OBJS) | $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

objs/%.o:%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $^ -o $@
clean:
	rm -rf objs
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re