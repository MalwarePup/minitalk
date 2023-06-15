/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:47:54 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/15 21:04:10 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"
#include "libft.h"

void	handle_message_size(int signum)
{
	if (signum == SIGUSR1)
		g_server.message_size |= (1U << g_server.offset);
	if (!g_server.offset)
	{
		g_server.offset = BYTE_SIZE;
		g_server.is_malloc_complete = true;
	}
	else
		g_server.offset--;
}

void	handle_message(int signum)
{
	if (signum == SIGUSR1)
		g_server.current_bit |= (1U << g_server.offset);
	if (!g_server.offset)
	{
		g_server.message[g_server.received_index++] = g_server.current_bit;
		g_server.current_bit = 0;
		g_server.offset = BYTE_SIZE;
		if (g_server.received_index == g_server.message_size)
		{
			g_server.message[g_server.received_index] = '\0';
			g_server.is_message_received = true;
		}
	}
	else
		g_server.offset--;
}

void	handle_error(t_error_code error_code)
{
	if (error_code == ECODE_KILL)
		ft_putendl_fd(ESTR_KILL, STDERR_FILENO);
	else if (error_code == ECODE_MALLOC)
		ft_putendl_fd(ESTR_MALLOC, STDERR_FILENO);
	else if (error_code == ECODE_SIGACTION)
		ft_putendl_fd(ESTR_SIGACTION, STDERR_FILENO);
	free(g_server.message);
	exit(EXIT_FAILURE);
}

static void	pong_when_operation_complete(bool *is_operation_complete)
{
	while (!*is_operation_complete)
	{
		usleep(USLEEP);
		if (kill(g_server.client_pid, SIGUSR1) == -1)
			handle_error(ECODE_KILL);
	}
}

void	process(void)
{
	ft_memset(&g_server, 0, sizeof(t_server));
	g_server.offset = MAX_OFFSET;
	pause();
	pong_when_operation_complete(&g_server.is_malloc_complete);
	g_server.message = malloc((g_server.message_size + 1) * sizeof(char));
	if (!g_server.message)
		handle_error(ECODE_MALLOC);
	pong_when_operation_complete(&g_server.is_message_received);
	if (kill(g_server.client_pid, SIGUSR2) == -1)
		handle_error(ECODE_KILL);
	ft_printf(STR_CLIENT STR_SIZE STR_PRINT STR_LINE, GREEN,
		g_server.client_pid, RESET, CYAN, g_server.message_size, RESET,
		g_server.message);
	free(g_server.message);
}
