# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 11:38:04 by ladloff           #+#    #+#              #
#    Updated: 2023/06/12 16:00:43 by ladloff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME		:=	client
B_CLIENT_NAME	:=	client_bonus
SERVER_NAME		:=	server
B_SERVER_NAME	:=	server_bonus

SRC_PATH		:=	./src
BUILD_PATH		:=	./build
INCLUDE_PATH	:=	./include
LIBFT_PATH		:=	./lib/libft

SRC_CLIENT		:=	client/client.c client/client_utils.c
B_SRC_CLIENT	:=	client/client_bonus.c client/client_utils_bonus.c
SRC_SERVER		:=	server/server.c server/server_utils.c
B_SRC_SERVER	:=	server/server_bonus.c server/server_utils_bonus.c

OBJ_CLIENT		:=	$(patsubst %.c,$(BUILD_PATH)/%.o,$(SRC_CLIENT))
B_OBJ_CLIENT	:=	$(patsubst %.c,$(BUILD_PATH)/%.o,$(B_SRC_CLIENT))
OBJ_SERVER		:=	$(patsubst %.c,$(BUILD_PATH)/%.o,$(SRC_SERVER))
B_OBJ_SERVER	:=	$(patsubst %.c,$(BUILD_PATH)/%.o,$(B_SRC_SERVER))


INCLUDE_FLAGS	:=	-I$(INCLUDE_PATH) -I$(LIBFT_PATH)/include
CFLAGS			:=	-Wall -Wextra -Werror $(INCLUDE_FLAGS)
LDFLAGS			:=	-L$(LIBFT_PATH)
LDLIBS			:=	-lft

.PHONY: all libft clean fclean re bonus rebonus clean_libft fclean_libft

all: libft $(CLIENT_NAME) $(SERVER_NAME)

libft:
	$(MAKE) -C $(LIBFT_PATH)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_NAME): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LDFLAGS) $(LDLIBS) -o $(CLIENT_NAME)

$(SERVER_NAME): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LDFLAGS) $(LDLIBS) -o $(SERVER_NAME)

clean:
	rm -f $(BUILD_PATH)/*.o

fclean: clean
	rm -rf $(BUILD_PATH)
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(B_CLIENT_NAME) $(B_SERVER_NAME)

re: fclean all

bonus: libft $(B_CLIENT_NAME) $(B_SERVER_NAME)

$(B_CLIENT_NAME): $(B_OBJ_CLIENT)
	$(CC) $(CFLAGS) $(B_OBJ_CLIENT) $(LDFLAGS) $(LDLIBS) -o $(B_CLIENT_NAME)

$(B_SERVER_NAME): $(B_OBJ_SERVER)
	$(CC) $(CFLAGS) $(B_OBJ_SERVER) $(LDFLAGS) $(LDLIBS) -o $(B_SERVER_NAME)

rebonus: fclean bonus

cleanlibft:
	$(MAKE) clean -C $(LIBFT_PATH)

fcleanlibft:
	$(MAKE) fclean -C $(LIBFT_PATH)

relibft: fcleanlibft libft
