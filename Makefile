include colors.mk
include config.mk
include targets.mk

NAME = minitalk

all: $(NAME)

$(NAME): client server

server: $(OBJ_SERVER) $(LIBFT)
	@printf "$(GREEN)Building $(NAME) server.$(RESET)\n"
	@$(COMPILE) $(OBJ_SERVER) $(LIBFT) $(LIBFT_FLAGS) -o server

client: $(OBJ_CLIENT) $(LIBFT)
	@printf "$(GREEN)Building $(NAME) client.$(RESET)\n"
	@$(COMPILE) $(OBJ_CLIENT) $(LIBFT) $(LIBFT_FLAGS) -o client

clean:
	@printf "$(YELLOW)Cleaning objects.$(RESET)\n"
	@$(REMOVE) $(OBJ_SERVER) $(OBJ_CLIENT)
	@make clean -s -C $(LIBFT_DIR)

fclean: clean
	@printf "$(YELLOW)Cleaning binaries.$(RESET)\n"
	@$(REMOVE) server client
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all
