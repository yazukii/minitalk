/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:00:02 by yidouiss          #+#    #+#             */
/*   Updated: 2023/01/30 15:14:45 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <signal.h>

typedef struct s_data
{
	int		pid;
	char	c;
	int		i;
}				t_data;

t_data	data;

void	handler(int sig)
{
	(void)sig;
	if (data.i == 8)
	{
		ft_putchar(data.c);
		data.c = 0;
		data.i = 0;
	}
	else
	{
		data.c = data.c << 1;
		if (sig == SIGUSR1)
			data.c = data.c | 1;
		data.i++;
	}
	kill(data.pid, SIGUSR2);
}

int	main(void)
{
	int	pid;
	struct sigaction sa;

	pid = getpid();
	ft_putstr("Server PID: ");
	ft_putnbr_fd(pid, 1);
	ft_putchar('\n');
	sa.sa_handler = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}