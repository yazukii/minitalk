/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:00:05 by yidouiss          #+#    #+#             */
/*   Updated: 2023/01/30 15:15:55 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>

void	send_char(char c, int pid)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int i;

	if (argc != 3)
		ft_putstr("Usage: ./client [server PID] [message]");
	i = 0;
	while (argv[2][i])
	{
		send_char(argv[2][i], ft_atoi(argv[1]));
		i++;
	}
	send_char('\0', ft_atoi(argv[1]));
	return (0);
}
