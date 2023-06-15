/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:50:04 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/15 17:36:19 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_bonus.h"

void	handle_error(t_error_code error_code)
{
	if (error_code == ECODE_INVALID_ARGS)
		ft_putendl_fd(ESTR_INVALID_ARGS, STDERR_FILENO);
	else if (error_code == ECODE_INVALID_PID)
		ft_putendl_fd(ESTR_INVALID_PID, STDERR_FILENO);
	else if (error_code == ECODE_EMPTY_STR)
		ft_putendl_fd(ESTR_EMPTY_STR, STDERR_FILENO);
	else if (error_code == ECODE_KILL)
		ft_putendl_fd(ESTR_KILL_P1 ESTR_KILL_P2, STDERR_FILENO);
	else if (error_code == ECODE_SIGACTION)
		ft_putendl_fd(ESTR_SIGACTION, STDERR_FILENO);
	else if (error_code == ECODE_PONG_TIMEOUT)
		ft_putendl_fd(ESTR_PONG_TIMEOUT, STDERR_FILENO);
	else if (error_code == ECODE_NO_ACK)
		ft_putendl_fd(ESTR_NO_ACK, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

static void	send_bit(uint32_t bit_val)
{
	int	signal_to_send;
	int	retries;

	retries = 0;
	signal_to_send = SIGUSR2;
	if (bit_val)
		signal_to_send = SIGUSR1;
	while (retries < RETRY_COUNT)
	{
		if (kill(g_client.server_pid, signal_to_send) == 0)
			return ;
		retries++;
	}
	handle_error(ECODE_KILL);
}

void	send_data(uint32_t data, uint32_t size)
{
	uint32_t	i;

	i = size * BITS_PER_BYTE;
	while (i)
	{
		g_client.is_pong_successful = false;
		send_bit(data & (1U << (i - 1)));
		usleep(USLEEP_LONG);
		if (!g_client.is_pong_successful)
			handle_error(ECODE_PONG_TIMEOUT);
		i--;
	}
}

void	send_message(const char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		send_data(message[i], sizeof(char));
		i++;
	}
}
