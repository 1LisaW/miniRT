NAME	=	miniRT

LIB	= libft.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -rf

FILES	=	main log_error miniRT_data

PARSER_FILES = parse_scene validation_scene parse_helpers validate_helpers \
				get_rgb get_coords shape parse_shape\
				parse_ambient_light parse_camera parse_light parse_sphere parse_plane parse_cylinder \
				log_parsed_data
SRC_DIR		= src

PARSER_DIR	= parser

OBJ_DIR	=	build

MINILIBX_DIR = minilibx-linux

SRC	=	$(addsuffix .c, $(FILES))

PARSER_SRC	=	$(addprefix $(PARSER_DIR)/, $(addsuffix .c, $(PARSER_FILES)))

SRCS	= $(addprefix $(SRC_DIR)/, $(SRC))

PARSER_SRCS	=	$(addprefix $(SRC_DIR)/, $(PARSER_SRC))

OBJS	=	$(addsuffix .o, $(FILES))

PARSER_OBJS	=	$(addsuffix .o, $(PARSER_FILES))

ALL_OBJS = $(OBJS) $(addprefix $(PARSER_DIR)/, $(PARSER_OBJS))

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@


all: submodule $(NAME)

submodule:
	@git submodule update --init
	@cd $(MINILIBX_DIR) && ./configure
	@$(MAKE) -C $(MINILIBX_DIR) -s


$(addprefix $(OBJ_DIR)/, $(OBJS)): $(SRCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(SRCS)
	@mv $(OBJS) $(OBJ_DIR)/

$(addprefix $(OBJ_DIR)/$(PARSER_DIR)/, $(PARSER_OBJS)): $(PARSER_SRCS)
	@mkdir -p $(OBJ_DIR)/$(PARSER_DIR)
	@$(CC) -c $(CFLAGS) $(PARSER_SRCS)
	@mv $(PARSER_OBJS) $(OBJ_DIR)/$(PARSER_DIR)/

$(LIB):
	@cd libft && $(MAKE) all

$(NAME):	$(addprefix $(OBJ_DIR)/, $(ALL_OBJS)) $(LIB)
	@$(CC) $(addprefix $(OBJ_DIR)/, $(ALL_OBJS))  -I include $(LIB) -lreadline -o $(NAME)

run:
	@valgrind --suppressions=suppressions.supp --leak-check=full --show-leak-kinds=all --child-silent-after-fork=yes ./minishell

clean:
	@$(RM) $(addprefix $(OBJ_DIR)/, $(ALL_OBJS)) $(OBJ_DIR)
	@$(MAKE) clean -C $(MINILIBX_DIR) -s
	@cd libft && $(MAKE) clean

fclean:	clean
	@$(RM) $(NAME)
	@cd libft && $(MAKE) fclean

re:	fclean all
	@git submodule update --remote -q

.PHONY: all	clean fclean re
