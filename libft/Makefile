# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 11:09:58 by rodrodri          #+#    #+#              #
#    Updated: 2021/12/03 18:21:31 by rodrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

FLAGS	=	-Wall -Werror -Wextra

FUNS	=	ft_memset	\
			ft_bzero	\
			ft_memcpy	\
			ft_memccpy	\
			ft_memmove	\
			ft_memchr	\
			ft_memcmp	\
			ft_strlen	\
			ft_strdup	\
			ft_strcpy	\
			ft_strncpy	\
			ft_strcat	\
			ft_strncat	\
			ft_strlcat	\
			ft_strchr	\
			ft_strrchr	\
			ft_strstr	\
			ft_strnstr	\
			ft_strcmp	\
			ft_strncmp	\
			ft_atoi		\
			ft_isalpha	\
			ft_isdigit	\
			ft_isalnum	\
			ft_isascii	\
			ft_isprint	\
			ft_toupper	\
			ft_tolower	\
\
			ft_memalloc	\
			ft_memdel	\
			ft_strnew	\
			ft_strdel	\
			ft_strclr	\
			ft_striter	\
			ft_striteri	\
			ft_strmap	\
			ft_strmapi	\
			ft_strequ	\
			ft_strnequ	\
			ft_strsub	\
			ft_strjoin	\
			ft_strtrim	\
			ft_strsplit	\
			ft_itoa		\
			ft_putchar	\
			ft_putstr	\
			ft_putendl	\
			ft_putnbr	\
			ft_putchar_fd	\
			ft_putstr_fd	\
			ft_putendl_fd	\
			ft_putnbr_fd	\
\
			ft_lstnew		\
			ft_lstdelone	\
			ft_lstdel		\
			ft_lstadd		\
			ft_lstiter		\
			ft_lstmap		\
\
			ft_isspace		\
			ft_strrev		\
			ft_lstappend	\
			ft_lstdelnode	\
			ft_lstdelcont	\
			ft_lstcount		\
			ft_lstprepend	\
			ft_clst_add		\
			ft_clst_cnt		\
			ft_clst_iter	\
			ft_clst_del


SRCS	=	$(FUNS:=.c)

OBJS	=	$(SRCS:.c=.o)

HDRS	=	./includes

CC		=	clang

.PHONY:	all clean fclean re

all:	$(NAME)

$(NAME):	$(SRCS) $(HDRS)
	@$(CC) $(FLAGS) $(SRCS) -I $(HDRS) -c
	@ar rcs $(NAME) $(OBJS)

clean:
	@/bin/rm -f $(OBJS)

fclean:	clean
	@/bin/rm -f $(NAME)

re:	fclean all
