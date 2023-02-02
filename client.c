/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:00:05 by yidouiss          #+#    #+#             */
/*   Updated: 2023/02/02 13:10:35 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

void	send_char(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(600);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int i;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client [server PID] [message]");
		return (1);
	}
	i = 0;
	while (argv[2][i])
	{
		send_char(argv[2][i], ft_atoi(argv[1]));
		i++;
	}
	send_char('\0', ft_atoi(argv[1]));
	return (0);
}
