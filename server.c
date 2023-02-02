/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:00:02 by yidouiss          #+#    #+#             */
/*   Updated: 2023/02/02 12:37:42 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <signal.h>

void	handler(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_putchar(i);
		bit = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	struct sigaction sa;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr("Usage: ./server");
		return (0);
	}
	pid = getpid();
	ft_putstr("Server PID: ");
	ft_putnbr_fd(pid, 1);
	ft_putchar('\n');
	sa.sa_handler = &handler;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}