NAME	=	miniRT

LIB	= libft.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -rf

FILES	=	main  log_error miniRT_data

PARSER_FILES = parse_scene validation_scene parse_helpers parse_ambient_light

SRC_DIR		= src

PARSER_DIR	= parser

OBJ_DIR	=	build

SRC	=	$(addsuffix .c, $(FILES))

PARSER_SRC	=	$(addprefix $(PARSER_DIR)/, $(addsuffix .c, $(PARSER_FILES)))

SRCS	= $(addprefix $(SRC_DIR)/, $(SRC))

PARSER_SRCS	=	$(addprefix $(SRC_DIR)/, $(PARSER_SRC))

OBJS	=	$(addsuffix .o, $(FILES))

PARSER_OBJS	=	$(addsuffix .o, $(PARSER_FILES))

ALL_OBJS = $(OBJS) $(addprefix $(PARSER_DIR)/, $(PARSER_OBJS))

%.o : %.c
		$(CC) -c $(CFLAGS) $< -o $@


all:	$(NAME)

$(addprefix $(OBJ_DIR)/, $(OBJS)): $(SRCS)
		@mkdir -p $(OBJ_DIR)
		$(CC) -c $(CFLAGS) $(SRCS)
		mv $(OBJS) $(OBJ_DIR)/

$(addprefix $(OBJ_DIR)/$(PARSER_DIR)/, $(PARSER_OBJS)): $(PARSER_SRCS)
		@mkdir -p $(OBJ_DIR)/$(PARSER_DIR)
		$(CC) -c $(CFLAGS) $(PARSER_SRCS)
		mv $(PARSER_OBJS) $(OBJ_DIR)/$(PARSER_DIR)/

$(LIB):
	cd libft && $(MAKE) all

$(NAME):	$(addprefix $(OBJ_DIR)/, $(ALL_OBJS)) $(LIB)
		$(CC) $(addprefix $(OBJ_DIR)/, $(ALL_OBJS))  -I include $(LIB) -lreadline -o $(NAME)

run:
	valgrind --suppressions=suppressions.supp --leak-check=full --show-leak-kinds=all --child-silent-after-fork=yes ./minishell

clean:
	$(RM) $(addprefix $(OBJ_DIR)/, $(ALL_OBJS)) $(OBJ_DIR)
	cd libft && $(MAKE) clean

fclean:	clean
	$(RM) $(NAME)
	cd libft && $(MAKE) fclean

re:	fclean all

.PHONY: all	clean fclean re
