/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:52:48 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 03:02:27 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "client.h"
#include "ft_printf.h"

t_client	g_client;

static void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_client.is_pong_successful = true;
	if (signum == SIGUSR2)
		g_client.is_message_acknowledge = true;
}

static void	set_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction (SIGUSR2, &sa, NULL) == -1)
		handle_error(ECODE_SIGACTION);
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		handle_error(ECODE_INVALID_ARGS);
	g_client.server_pid = ft_atoi(argv[1]);
	if (g_client.server_pid <= 0)
		handle_error(ECODE_INVALID_PID);
	g_client.message_size = ft_strlen(argv[2]);
	if (!g_client.message_size)
		handle_error(ECODE_EMPTY_STR);
	set_sigaction();
	g_client.message = argv[2];
	g_client.is_pong_successful = false;
	g_client.is_message_acknowledge = false;
	send_data(g_client.message_size, sizeof(uint32_t));
	usleep(USLEEP_SHORT);
	send_message(g_client.message);
	usleep(USLEEP_MEDIUM);
	if (!g_client.is_message_acknowledge)
		handle_error(ECODE_NO_ACK);
	else
		ft_printf(STR_SUCCESS, CYAN, g_client.message_size, RESET, GREEN,
			g_client.server_pid, RESET);
	return (EXIT_SUCCESS);
}
