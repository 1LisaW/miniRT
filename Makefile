NAME        = miniRT
LIB         = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
TESTING_FLAGS = -g
RM          = rm -rf
FILES       = main log_error miniRT_data

PARSER_FILES =	parse_scene validation_scene parse_helpers validate_helpers \
                get_rgb get_coords shape parse_shape\
                parse_ambient_light parse_camera parse_light parse_sphere parse_plane parse_cylinder \
                log_parsed_data
IMG_FILES = 	create_win win_events img_data translation_events
VEC_OPS_FILES =	basic_vector_ops get_vec_length normalize_vector copy_vector scale_vector \
				cross_product inverse_matrix
SDF_FILES =		sd_selector
RAY_TRACE_FILES = trace_ray matrix intersection color \
				precompute_data cylinder_intersection normal

SRC_DIR     	= src
PARSER_DIR  	= parser
IMG_DIR			= image
VEC_OPS_DIR 	= vector_ops
SDF_DIR			= sd_functions
RAY_TRACE_DIR	= ray_tracing
MINILIBX_DIR	= minilibx-linux
LINKED_OBJS 	= obj

SRC         	= $(addsuffix .c, $(FILES))
PARSER_SRC  	= $(addprefix $(PARSER_DIR)/, $(addsuffix .c, $(PARSER_FILES)))
IMG_SRC			= $(addprefix $(IMG_DIR)/, $(addsuffix .c, $(IMG_FILES)))
VEC_OPS_SRC		= $(addprefix $(VEC_OPS_DIR)/, $(addsuffix .c, $(VEC_OPS_FILES)))
SDF_SRC			= $(addprefix $(SDF_DIR)/, $(addsuffix .c, $(SDF_FILES)))
RAY_TRACE_SRC	= $(addprefix $(RAY_TRACE_DIR)/, $(addsuffix .c, $(RAY_TRACE_FILES)))

SRCS        	= $(addprefix $(SRC_DIR)/, $(SRC))
PARSER_SRCS 	= $(addprefix $(SRC_DIR)/, $(PARSER_SRC))
IMG_SRCS		= $(addprefix $(SRC_DIR)/, $(IMG_SRC))
VEC_OPS_SRCS	= $(addprefix $(SRC_DIR)/, $(VEC_OPS_SRC))
SDF_SRCS		= $(addprefix $(SRC_DIR)/, $(SDF_SRC))
RAY_TRACE_SRCS	= $(addprefix $(RAY_TRACE_DIR)/, $(RAY_TRACE_SRC))

OBJS        	= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(FILES)))
PARSER_OBJS 	= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(PARSER_FILES)))
IMG_OBJS		= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(IMG_FILES)))
VEC_OPS_OBJS	= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(VEC_OPS_FILES)))
SDF_OBJS 		= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(SDF_FILES)))
RAY_TRACE_OBJS 	= $(addprefix $(LINKED_OBJS)/, $(addsuffix .o, $(RAY_TRACE_FILES)))

ALL_OBJS    = $(OBJS) $(PARSER_OBJS) $(IMG_OBJS) $(VEC_OPS_OBJS) $(SDF_OBJS) $(RAY_TRACE_OBJS)

# COLORS
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

%.o : %.c
	@echo $(CYAN) "Compiling $@...🛠️" $(EOC)
	@mkdir -p $(LINKED_OBJS)
	@$(CC) -c $(CFLAGS)  -I/usr/include -Imlx_linux -O3 $< -o $@

all: submodule $(NAME)
	@echo $(GREEN) "OK COMPILED" $(EOC)

testing: CFLAGS = $(TESTING_FLAGS)

testing: submodule $(NAME)
	@echo $(RED) "WARNING: COMPILED WITHOUT MANDATORY FLAGS" $(EOC)

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

$(LINKED_OBJS)/%.o: $(SRC_DIR)/$(VEC_OPS_DIR)/%.c
	@mkdir -p $(LINKED_OBJS)
	@$(CC) -c $(CFLAGS) $< -o $@

$(LINKED_OBJS)/%.o: $(SRC_DIR)/$(SDF_DIR)/%.c
	@mkdir -p $(LINKED_OBJS)
	@$(CC) -c $(CFLAGS) $< -o $@

$(LINKED_OBJS)/%.o: $(SRC_DIR)/$(RAY_TRACE_DIR)/%.c
	@mkdir -p $(LINKED_OBJS)
	@$(CC) -c $(CFLAGS) $< -o $@

$(LIB):
	@cd libft -s && $(MAKE) all

$(NAME): $(ALL_OBJS) $(LIB)
	@$(CC) $(ALL_OBJS) -I include $(LIB)  -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

run:
	@valgrind --suppressions=suppressions.supp --leak-check=full --show-leak-kinds=all --child-silent-after-fork=yes ./miniRT

clean:
	@$(RM) $(LINKED_OBJS)
	@$(MAKE) clean -C $(MINILIBX_DIR) -s
	@$(MAKE) clean -C libft -s
	@echo $(RED) "Cleaned..." $(EOC)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C libft -s
	@echo $(PURPLE) "Full Cleaned...🧹" $(EOC)

re: fclean all
	@git submodule update --remote -q

.PHONY: all clean fclean re submodule testing

