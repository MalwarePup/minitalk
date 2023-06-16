# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 11:38:04 by ladloff           #+#    #+#              #
#    Updated: 2023/06/16 12:33:25 by ladloff          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL			:=	/bin/sh

CLIENT_NAME		:=	client
SERVER_NAME		:=	server

SRC_DIR			:=	./src
BUILD_DIR		:=	./build
INCLUDE_DIR		:=	./include
LIBFT_DIR		:=	./lib/libft

SRC_CLIENT		:=	client/client.c \
					client/client_utils.c
SRC_SERVER		:=	server/server.c \
					server/server_utils.c

OBJ_CLIENT		:=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_CLIENT))
OBJ_SERVER		:=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_SERVER))

DEP_CLIENT		:=	$(OBJ_CLIENT:.o=.d)
DEP_SERVER		:=	$(OBJ_SERVER:.o=.d)

CFLAGS			:=	-Wall -Wextra -Werror -Wpedantic -MMD -MP
CPPFLAGS		:=	-I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include
LDFLAGS			:=	-L$(LIBFT_DIR)
LDLIBS			:=	-lft

.PHONY: all lib clean fclean re bonus rebonus cleanlib fcleanlib relib

ifeq ($(BONUS),1)
CLIENT_NAME		:=	client_bonus
SERVER_NAME		:=	server_bonus
SRC_CLIENT		:=	client/client_bonus.c \
					client/client_utils_bonus.c
SRC_SERVER		:=	server/server_bonus.c \
					server/server_utils_bonus.c
OBJ_CLIENT		:=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_CLIENT))
OBJ_SERVER		:=	$(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_SERVER))
DEP_CLIENT		:=	$(OBJ_CLIENT:.o=.d)
DEP_SERVER		:=	$(OBJ_SERVER:.o=.d)
endif

all: lib $(CLIENT_NAME) $(SERVER_NAME)

lib:
	$(MAKE) -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

-include $(DEP_CLIENT) $(DEP_SERVER)

$(CLIENT_NAME): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LDFLAGS) $(LDLIBS) -o $(CLIENT_NAME)

$(SERVER_NAME): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LDFLAGS) $(LDLIBS) -o $(SERVER_NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	$(RM) client client_bonus server server_bonus

re: fclean all

bonus:
	$(MAKE) BONUS=1 all

rebonus: fclean bonus

cleanlib:
	$(MAKE) clean -C $(LIBFT_DIR)

fcleanlib:
	$(MAKE) fclean -C $(LIBFT_DIR)

relib: fcleanlib lib
