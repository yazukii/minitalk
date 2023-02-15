/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yidouiss <yidouiss@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:00:02 by yidouiss          #+#    #+#             */
/*   Updated: 2023/02/08 21:11:18 by yidouiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <signal.h>

int	ft_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0 && power == 0)
		return (1);
	else
		return (nb * ft_power(nb, power - 1));
}

void	get_len(int *bit, char **str, int *received, int s)
{
	static int	len_val = 0;

	if (s == SIGUSR2)
		len_val += ft_power(2, *bit);
	if (*bit == 31)
	{
		*received = 1;
		*str = malloc(len_val + 1 * sizeof(char));
		*bit = 0;
		len_val = 0;
		return ;
	}
	(*bit)++;
}

void	restart(int *len, char **str, int *i)
{
	*len = 0;
	if (str)
	{
		ft_putstr(*str);
		free(*str);
		*str = 0;
	}
	*i = 0;
}

void	get_info(int signal)
{
	static int	char_value = 0;
	static int	bit = 0;
	static int	len = 0;
	static int	i = 0;
	static char	*final_str = 0;

	if (!len)
		get_len(&bit, &final_str, &len, signal);
	else
	{
		if (signal == SIGUSR2)
			char_value += ft_power(2, bit);
		if (bit == 7)
		{
			final_str[i++] = char_value;
			bit = 0;
			if (char_value == 0)
				return (restart(&len, &final_str, &i));
			char_value = 0;
			return ;
		}
		bit++;
	}
}
int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

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
	sa.sa_handler = &get_info;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		usleep(100);
	return (0);
}
