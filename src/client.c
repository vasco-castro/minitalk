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

static void	send_char(char c)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c >> bit & 1)
			kill(g_message.pid, SIGUSR2);
		else
			kill(g_message.pid, SIGUSR1);
		bit++;
		usleep(100);
	}
}

static void	send_message(void)
{
	int	i;

	i = 0;
	while (i <= g_message.size)
	{
		send_char(g_message.msg[i]);
		i++;
	}
}

// TODO: Validate pid exists
// TODO: Handle server not responding
// TODO: Handle signals from server (acknowledgements)
int	main(int argc, char const *argv[])
{
	if (!handle_args(argc, argv))
		return (EXIT_FAILURE);
	send_message();
	ft_printf("Message sent successfully.\n");
	return (EXIT_SUCCESS);
}
