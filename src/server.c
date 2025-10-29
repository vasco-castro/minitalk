/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoares- <vsoares-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:40:33 by vsoares-          #+#    #+#             */
/*   Updated: 2025/10/24 16:03:25 by vsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

// t_message	g_message;

void	handle_sigaction(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = 0;

	if (sig == SIGUSR2)
		c += (1 << bit);
	bit++;
	if (bit >= CHAR_BIT)
	{
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
			write(1, &c, 1);
		c = 0;
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

void	handle_signal(int sig)
{
	static char	c = 0;
	static int	bit = 0;

	if (sig == SIGUSR2)
		c += (1 << bit);
	bit++;
	if (bit >= CHAR_BIT)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigaction;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (42)
		pause();
	return (EXIT_SUCCESS);
}
