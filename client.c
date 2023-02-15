/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:00:05 by yidouiss          #+#    #+#             */
/*   Updated: 2023/02/15 17:48:29 by yidouiss         ###   ########.fr       */
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
		usleep(100);
		bit++;
	}
}

void	send_len(int len, int pid)
{
	int	i;

	i = -1;
	ft_putnbr_fd(len, 1);
	while (++i < 32)
	{
		if (len & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		len = len >> 1;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr("Usage: ./client [server PID] [message]");
		return (1);
	}
	send_len(ft_strlen(argv[2]), ft_atoi(argv[1]));
	while (argv[2][i])
	{
		send_char(argv[2][i], ft_atoi(argv[1]));
		i++;
	}
	send_char('\0', ft_atoi(argv[1]));
	return (0);
}
