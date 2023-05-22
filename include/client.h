/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:56:02 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 03:02:18 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include "libft.h"

# define CYAN "\x1B[36m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"

# define ESTR_INVALID_ARGS "Usage: ./client <srv_pid> <message>"
# define ESTR_INVALID_PID "Error: Invalid server PID entered"
# define ESTR_EMPTY_STR "Error: Message is empty"
# define ESTR_KILL_P1 "Error: Unable to send signal to the server. Possible"
# define ESTR_KILL_P2 " reasons could be invalid PID or lack of permissions"
# define ESTR_KILL ESTR_KILL_P1 ESTR_KILL_P2
# define ESTR_SIGACTION "Error: Unable to set signal handler"
# define ESTR_PONG_TIMEOUT "Error: Pong not received from the server"
# define ESTR_NO_ACK "Error: no acknowledgment for the message received"

# define STR_SUCCESS_P1 "I successfully sent the message with a size of %s%d%s"
# define STR_SUCCESS_P2 " to the server %s%d%s\n"
# define STR_SUCCESS STR_SUCCESS_P1 STR_SUCCESS_P2

# define BITS_PER_BYTE 8
# define RETRY_COUNT 3
# define USLEEP_SHORT 50
# define USLEEP_MEDIUM 500
# define USLEEP_LONG 2000

typedef enum e_error_code
{
	ECODE_INVALID_ARGS = 1,
	ECODE_INVALID_PID,
	ECODE_EMPTY_STR,
	ECODE_KILL,
	ECODE_SIGACTION,
	ECODE_PONG_TIMEOUT,
	ECODE_NO_ACK
}	t_error_code;

typedef struct s_client
{
	const char	*message;
	pid_t		server_pid;
	uint32_t	message_size;
	bool		is_pong_successful;
	bool		is_message_acknowledge;
}	t_client;

extern t_client	g_client;

/* client_utils.c */
void	handle_error(t_error_code error_code);
void	send_data(uint32_t data, uint32_t size);
void	send_message(const char *message);

#endif /* CLIENT_H */
