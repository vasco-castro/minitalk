# Directories
SRCS_DIR = ./src
LIB_DIR = ./lib

# Source files, using addprefix and addsuffix
SRC_CLIENT = $(addprefix $(SRCS_DIR)/, \
	$(addsuffix .c, client) \
)
SRC_SERVER = $(addprefix $(SRCS_DIR)/, \
	$(addsuffix .c, server) \
)

# Object files convertion
OBJ_SERVER = $(SRC_SERVER:%.c=%.o)
OBJ_CLIENT = $(SRC_CLIENT:%.c=%.o)

# LIBFT linking and compilation flags
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR)/include


$(LIBFT):
	@printf "$(GREEN)Building LIBFT.$(RESET)\n"
	@make -s -C $(LIBFT_DIR)
