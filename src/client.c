/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoares- <vsoares-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:41:39 by vsoares-          #+#    #+#             */
/*   Updated: 2025/10/24 16:02:07 by vsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

t_message	g_message;

static bool	handle_args(int argc, char const *argv[])
{
	if (argc != 3)
	{
		if (argc < 3)
			write(1, "Error: Not enough arguments.\n", 29);
		else
			write(1, "Error: Too many arguments.\n", 27);
		write(1, "Usage: ./client <PID> <message>\n", 32);
		return (false);
	}
	g_message.pid = ft_atoi(argv[1]);
	if (g_message.pid <= 0)
	{
		write(1, "Error: Invalid PID.\n", 21);
		return (false);
	}
	if (!argv[2] || argv[2][0] == '\0')
	{
		write(1, "Error: Message cannot be empty.\n", 33);
		return (false);
	}
	g_message.msg = (char *)argv[2];
	g_message.size = ft_strlen(argv[2]);
	return (true);
}

static void	send_bit()
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

static void	finish()
{
	write(1, "Message sent successfully.\n", 27);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	if (!handle_args(argc, argv))
		return (EXIT_FAILURE);
	signal(SIGUSR1, send_bit);
	signal(SIGUSR2, finish);
	send_bit();
	while (42)
		pause();
	return (EXIT_SUCCESS);
}
