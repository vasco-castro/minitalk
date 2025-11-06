/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoares- <vsoares-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:41:39 by vsoares-          #+#    #+#             */
/*   Updated: 2025/11/06 18:54:29 by vsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_message	g_message;

static void	handle_args(int argc, char const *argv[])
{
	if (argc != 3)
	{
		if (argc < 3)
			write(2, "Error: Not enough arguments.\n", 29);
		else
			write(2, "Error: Too many arguments.\n", 27);
		write(2, "Usage: ./client <PID> <message>\n", 32);
		exit(EXIT_FAILURE);
	}
	g_message.pid = ft_atoi(argv[1]);
	if (g_message.pid <= 0 || kill(g_message.pid, 0))
	{
		write(2, "Error: Invalid PID.\n", 21);
		exit(EXIT_FAILURE);
	}
	if (!argv[2] || argv[2][0] == '\0')
	{
		write(2, "Error: Message cannot be empty.\n", 33);
		exit(EXIT_FAILURE);
	}
	g_message.msg = (char *)argv[2];
	g_message.size = ft_strlen(argv[2]);
}

static void	send_size(void)
{
	static int	bit = 0;

	if (g_message.size >> bit & 1)
		kill(g_message.pid, SIGUSR2);
	else
		kill(g_message.pid, SIGUSR1);
	bit++;
}

static void	send_char(void)
{
	static int	i = 0;
	static int	bit = 0;

	if (bit == CHAR_BIT)
	{
		bit = 0;
		i++;
	}
	if (g_message.msg[i] >> bit & 1)
		kill(g_message.pid, SIGUSR2);
	else
		kill(g_message.pid, SIGUSR1);
	bit++;
}

void	handle_sigaction(int sig, siginfo_t *info, void *context)
{
	static int	size = 0;

	(void)info;
	(void)context;
	if (sig == SIGUSR2)
	{
		write(1, "Message sent successfully.\n", 27);
		exit(EXIT_SUCCESS);
	}
	if (size < 32)
	{
		send_size();
		size++;
	}
	else
		send_char();
}

int	main(int argc, char const *argv[])
{
	struct sigaction	sa;

	handle_args(argc, argv);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigaction;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	handle_sigaction(SIGUSR1, NULL, NULL);
	while (42)
		pause();
	return (EXIT_SUCCESS);
}
