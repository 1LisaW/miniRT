NAME	=	../libft.a

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

AR	=	ar -rcs

RM	=	rm -rf

FILES	=	ft_strlen ft_isspace ft_reallocate ft_strcmp ft_atof ft_issign ft_isdigit \
			ft_atoi ft_substr ft_split ft_abs_f

SRC	=	$(addsuffix .c, $(FILES))

OBJ	=	$(addsuffix .o, $(FILES))

all:	$(NAME)

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@${AR} $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all	clean fclean re
