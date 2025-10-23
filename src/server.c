/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoares- <vsoares-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:40:33 by vsoares-          #+#    #+#             */
/*   Updated: 2025/10/23 22:31:58 by vsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	handle_signal(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("Received SIGUSR1 signal.\n");
	}
	else if (sig == SIGUSR2)
	{
		ft_printf("Received SIGUSR2 signal.\n");
	}
}

int main(int argc, char const *argv[])
{
	struct sigaction sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_signal;
	sigaction(SIGUSR1, &sa, NULL);
	// sigaction(SIGUSR2, &sa, NULL);
	(void)argc;
	(void)argv;
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		ft_printf("Waiting for messages...\n");
		sleep(5);
	}
	return (0);
}
