include colors.mk
include config.mk
include targets.mk

NAME = minitalk

all: $(NAME)

$(NAME): client server

server: $(LIBFT) $(OBJ_SERVER)
	@printf "$(GREEN)Building $(NAME) server.$(RESET)\n"
	@$(BANNER)
	@$(COMPILE) $(OBJ_SERVER) $(LIBFT) $(LIBFT_FLAGS) -o server

client: $(LIBFT) $(OBJ_CLIENT)
	@printf "$(GREEN)Building $(NAME) client.$(RESET)\n"
	@$(BANNER)
	@$(COMPILE) $(OBJ_CLIENT) $(LIBFT) $(LIBFT_FLAGS) -o client

clean:
	@printf "$(YELLOW)Cleaning objects.$(RESET)\n"
	@$(REMOVE) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	@printf "$(YELLOW)Cleaning binaries.$(RESET)\n"
	@$(REMOVE) server client
	@make fclean -s -C $(LIBFT_DIR)

re: fclean all
