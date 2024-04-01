NAME        = miniRT
LIB         = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
RM          = rm -rf
FILES       = main log_error miniRT_data

PARSER_FILES = parse_scene validation_scene parse_helpers validate_helpers \
                get_rgb get_coords shape parse_shape\
                parse_ambient_light parse_camera parse_light parse_sphere parse_plane parse_cylinder \
                log_parsed_data
IMG_FILES = create_win win_events init_img_data get_start_img
VEC_OPS_FILES = basic_vector_ops get_vec_lenght normalize_vector
SRC_DIR     = src
PARSER_DIR  = parser
IMG_DIR = image
VEC_OPS_DIR = vector_ops
MINILIBX_DIR = minilibx-linux
LINKED_OBJS = obj

SRC         = $(addsuffix .c, $(FILES))
PARSER_SRC  = $(addprefix $(PARSER_DIR)/, $(addsuffix .c, $(PARSER_FILES)))
IMG_SRC	=	$(addprefix $(IMG_DIR)/, $(addsuffix .c, $(IMG_FILES)))
VEC_OPS_SRC	=	$(addprefix $(VEC_OPS_DIR)/, $(addsuffix .c, $(VEC_OPS_FILES)))
SRCS        = $(addprefix $(SRC_DIR)/, $(SRC))
PARSER_SRCS = $(addprefix $(SRC_DIR)/, $(PARSER_SRC))
IMG_SRCS	=	$(addprefix $(SRC_DIR)/, $(IMG_SRC))

OBJS        = $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(FILES)))
PARSER_OBJS = $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(PARSER_FILES)))
IMG_OBJS	= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(IMG_FILES)))
VEC_OPS_OBJS	= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(VEC_OPS_FILES)))
ALL_OBJS    = $(OBJS) $(PARSER_OBJS) $(IMG_OBJS)

%.o : %.c
	@mkdir -p $(LINKED_OBJS)
	@$(CC) -c $(CFLAGS)  -I/usr/include -Imlx_linux -O3 $< -o $@

all: submodule $(NAME)

submodule:
	@git submodule update --init
	@cd $(MINILIBX_DIR) && ./configure
	@$(MAKE) -C $(MINILIBX_DIR) -s

$(LINKED_OBJS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(LINKED_OBJS)
	@$(CC) -c $(CFLAGS) $< -o $@

$(LINKED_OBJS)/%.o: $(SRC_DIR)/$(PARSER_DIR)/%.c
	@mkdir -p $(LINKED_OBJS)
	@$(CC) -c $(CFLAGS) $< -o $@


$(LINKED_OBJS)/%.o: $(SRC_DIR)/$(IMG_DIR)/%.c
		@mkdir -p $(LINKED_OBJS)
		@$(CC) -c $(CFLAGS) $< -o $@

$(LIB):
	@cd libft && $(MAKE) all

$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(ALL_OBJS) -I include $(LIB)  -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

run:
	@valgrind --suppressions=suppressions.supp --leak-check=full --show-leak-kinds=all --child-silent-after-fork=yes ./miniRT

clean:
	@$(RM) $(LINKED_OBJS)
	@$(MAKE) clean -C $(MINILIBX_DIR) -s
	@cd libft && $(MAKE) clean

fclean: clean
	@$(RM) $(NAME)
	@cd libft && $(MAKE) fclean

re: fclean all
	@git submodule update --remote -q

.PHONY: all clean fclean re submodule

