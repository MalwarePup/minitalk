# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 11:38:04 by ladloff           #+#    #+#              #
#    Updated: 2023/05/22 03:15:33 by ladloff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_EXEC		?=	client
B_CLIENT_EXEC	?=	client_bonus
SERVER_EXEC		?=	server
B_SERVER_EXEC	?=	server_bonus

SRC_DIR			?=	./src
OBJ_DIR			?=	./obj
INC_DIR			?=	./include
LIB_DIR			?=	./libft

SRC_CLIENT		?=	client/client.c client/client_utils.c
B_SRC_CLIENT	?=	client/client_bonus.c client/client_utils_bonus.c
SRC_SERVER		?=	server/server.c server/server_utils.c
B_SRC_SERVER	?=	server/server_bonus.c server/server_utils_bonus.c

OBJ_CLIENT		:=	$(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)
B_OBJ_CLIENT	:=	$(B_SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER		:=	$(SRC_SERVER:%.c=$(OBJ_DIR)/%.o)
B_OBJ_SERVER	:=	$(B_SRC_SERVER:%.c=$(OBJ_DIR)/%.o)
LIB_INC			:=	$(addprefix -I, $(LIB_DIR)/include)
INC				:=	$(addprefix -I, $(INC_DIR))

CFLAGS			:=	-Wall -Wextra -Werror $(INC) $(LIB_INC)
LDFLAGS			:=	-L$(LIB_DIR) -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(CLIENT_EXEC) $(SERVER_EXEC)

$(CLIENT_EXEC): $(OBJ_CLIENT)
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LDFLAGS) -o $(CLIENT_EXEC)

$(SERVER_EXEC): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LDFLAGS) -o $(SERVER_EXEC)

clean:
	@$(MAKE) clean -C libft
	@rm -f $(OBJ_DIR)/*.o

fclean: clean
	@$(MAKE) fclean -C libft
	@rm -rf $(OBJ_DIR)
	@rm -f $(CLIENT_EXEC) $(SERVER_EXEC) $(B_CLIENT_EXEC) $(B_SERVER_EXEC)

re: fclean all

bonus: $(B_CLIENT_EXEC) $(B_SERVER_EXEC)

$(B_CLIENT_EXEC): $(B_OBJ_CLIENT)
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(B_OBJ_CLIENT) $(LDFLAGS) -o $(B_CLIENT_EXEC)

$(B_SERVER_EXEC): $(B_OBJ_SERVER)
	$(CC) $(CFLAGS) $(B_OBJ_SERVER) $(LDFLAGS) -o $(B_SERVER_EXEC)

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
