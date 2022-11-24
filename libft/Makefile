NAME		= libft.a
CFLAGS		= -Wall -Werror -Wextra -I.
CC			= cc
MAIN		= 	ft_isalnum.c 		\
				ft_isalpha.c 		\
				ft_isascii.c 		\
				ft_isdigit.c 		\
				ft_isprint.c 		\
				ft_tolower.c 		\
				ft_toupper.c 		\
				ft_strchr.c	 		\
				ft_strrchr.c 		\
				ft_strlen.c  		\
				ft_strncmp.c 		\
				ft_strcmp.c 		\
				ft_memset.c  		\
				ft_memchr.c  		\
				ft_memcpy.c  		\
				ft_bzero.c   		\
				ft_memcmp.c  		\
				ft_memmove.c 		\
				ft_strnstr.c 		\
				ft_strlcpy.c 		\
				ft_strlcat.c 		\
				ft_atoi.c	 		\
				ft_calloc.c	 		\
				ft_strdup.c 		\
				ft_substr.c 		\
				ft_strjoin.c		\
				ft_strtrim.c 		\
				ft_split.c			\
				ft_itoa.c	 		\
				ft_strmapi.c 		\
				ft_striteri.c		\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putnbr_fd.c		\
				ft_putendl_fd.c		\

BONUS		=	ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c

MAINOBJ		=	$(MAIN:.c=.o)
BONUSOBJ	=	$(BONUS:.c=.o)

$(NAME) : $(MAINOBJ) $(BONUSOBJ)
	ar -rcs $(NAME) $^

bonus	: $(BONUSOBJ)
	ar -rcs $(NAME) $^

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f $(MAINOBJ) $(BONUSOBJ)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

all:	$(NAME) bonus

.PHONY: bonus clean fclean re all
