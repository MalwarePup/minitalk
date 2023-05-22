/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:53:36 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 03:03:58 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "server.h"

t_server	g_server;

static void	sigint_handler(int signum)
{
	(void)signum;
	ft_printf(STR_SIGINT, RED, RESET);
	free(g_server.message);
	exit(EXIT_SUCCESS);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	g_server.client_pid = info->si_pid;
	if (!g_server.is_malloc_complete)
		handle_message_size(signum);
	else
		handle_message(signum);
}

static void	set_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		handle_error(ECODE_SIGACTION);
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		handle_error(ECODE_SIGACTION);
}

int	main(void)
{
	set_sigaction();
	ft_printf(CLEAR_TERM STR_PID, GREEN, getpid(), RESET);
	while (1)
		process();
}
