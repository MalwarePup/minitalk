/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:56:35 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/24 11:26:20 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include "ft_printf.h"

# define RED "\x1B[31m"
# define CYAN "\x1B[36m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"

# define CLEAR_TERM "\e[1;1H\e[2J"

# define ESTR_KILL "Error: Unable to send signal to the server (pong)"
# define ESTR_MALLOC "Error: Memory allocation failure"
# define ESTR_SIGACTION "Error: Unable to set signal handler"

# define STR_LINE "----------------------------------------------------------\n"
# define STR_PID "Welcome to Minitalk!\n This is my PID: %s%d%s\n" STR_LINE
# define STR_SIGINT "\n\nI handle the %sSIGINT%s signal, see you later\n"
# define STR_CLIENT "I got a signal from the client with following PID %s%d%s"
# define STR_SIZE "\nI handle message size of %s%d%s and the message is:"
# define STR_PRINT "\n\n%s\n"
# define STR_SUCCESS STR_CLIENT STR_SIZE STR_PRINT STR_LINE

# define BITS_PER_BYTE 8
# define BYTE_SIZE 7
# define MAX_OFFSET 31
# define USLEEP 200

typedef enum e_error_code
{
	ECODE_KILL = 1,
	ECODE_MALLOC,
	ECODE_SIGACTION
}	t_error_code;

typedef struct s_server
{
	uint32_t	offset;
	char		*message;
	pid_t		client_pid;
	uint32_t	current_bit;
	uint32_t	message_size;
	uint32_t	received_index;
	bool		is_malloc_complete;
	bool		is_message_received;
}	t_server;

extern t_server	g_server;

/* server_utils.c */
void	handle_message_size(int signum);
void	handle_message(int signum);
void	handle_error(t_error_code error_code);
void	process(void);

#endif /*  SERVER_BONUS_H */
