/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoares- <vsoares-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:40:33 by vsoares-          #+#    #+#             */
/*   Updated: 2025/11/06 18:54:01 by vsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_message	g_message;

void	print_message(void)
{
	ft_printf("%s", g_message.msg);
	kill(g_message.pid, SIGUSR2);
	free(g_message.msg);
	g_message.size = 0;
	g_message.pid = 0;
}

void	parse_size(int sig)
{
	static int	bit = 0;

	if (sig == SIGUSR2)
		g_message.size += (1 << bit);
	bit++;
	kill(g_message.pid, SIGUSR1);
}

void	parse_char(int sig)
{
	static int	bit = 0;
	static int	i = 0;

	if (sig == SIGUSR2)
		g_message.msg[i] += (1 << bit);
	bit++;
	if (bit == CHAR_BIT)
	{
		i++;
		bit = 0;
	}
	if (i == g_message.size)
	{
		i = 0;
		print_message();
	}
	else
		kill(g_message.pid, SIGUSR1);
}

void	handle_sigaction(int sig, siginfo_t *info, void *context)
{
	static int	bit = 0;

	if (bit == 0)
		g_message.pid = info->si_pid;
	if (bit < 32)
		parse_size(sig);
	if (bit == 32)
	{
		g_message.msg = ft_calloc(g_message.size + 1, sizeof(char));
		if (!g_message.msg)
		{
			ft_fprintf(2, "Error with allocation!\n");
			exit(EXIT_FAILURE);
		}
	}
	if (bit >= 32)
		parse_char(sig);
	bit++;
	if (bit > 32 && g_message.size == 0)
		bit = 0;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigaction;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (42)
		pause();
	return (EXIT_SUCCESS);
}
