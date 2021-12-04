NAME	=	test_gnl

FLAGS	=	-Wall -Werror -Wextra

HDRS	=	../libft/includes

CC		=	clang

all: $(NAME)

$(NAME): libft.a get_next_line.o main.o
	$(CC) $(FLAGS) -g -I $(HDRS) -I ../ -o $(NAME) main.o get_next_line.o \
	-L ../libft/ -lft

libft.a:
	# @make -C ../libft/ fclean && make -C ../libft/
	@make -C ../libft/

get_next_line.o:	../get_next_line.c
	$(CC) $(FLAGS) -g -I $(HDRS) -I ../ ../get_next_line.c -o get_next_line.o -c

main.o:				main.c.test
	$(CC) $(FLAGS) -I $(HDRS) -I ../ -x c main.c.test -o main.o -c

debug: FLAGS += -g
debug: .FORCE
debug: $(NAME)

clean:
	@/bin/rm -f main.o get_next_line.o

fclean:	clean
	@/bin/rm -f $(NAME)

re:		fclean all

test:	.FORCE

.PHONY:	all clean fclean re .FORCE