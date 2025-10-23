/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoares- <vsoares-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:41:39 by vsoares-          #+#    #+#             */
/*   Updated: 2025/10/23 22:18:08 by vsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		if (argc < 3)
		{
			write(1, "Error: Not enough arguments.\n", 29);
		}
		else
		{
			write(1, "Error: Too many arguments.\n", 27);
		}

		write(1, "Usage: ./client <PID> <message>\n", 32);
		return (1);
	}
	int pid = ft_atoi(argv[2]);
	if (pid <= 0)
	{
		write(1, "Error: Invalid PID.\n", 21);
		return (1);
	}
	if (!argv[2] || argv[2][0] == '\0')
	{
		write(1, "Error: Message cannot be empty.\n", 33);
		return (1);
	}

	ft_printf(GREEN "Message: %s\t to server with PID: %d\n" RESET, argv[1], pid);

	kill(pid, SIGUSR1);
	return (0);
}
