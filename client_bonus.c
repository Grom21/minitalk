/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:29:26 by etisha            #+#    #+#             */
/*   Updated: 2021/12/27 18:29:36 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_stoper = 0;

static int	ft_atoi(const char *str)
{
	int				i;
	long long int	result;

	i = 0;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 2147483647)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (0);
	return (result);
}

static void	ft_confirm(int signal)
{
	if (signal == SIGUSR1)
		write (1, "Have signal\n", 12);
	g_stoper = 1;
}

static void	ft_send_signal(int pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		usleep(600);
		if (c & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c = c >> 1;
		while (g_stoper != 1)
		{
		}
		g_stoper = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		write (1, "Error! Enter \"PID\" \"You message\"\n", 33);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write (1, "Error! Wrong PID!\n", 18);
		return (0);
	}
	signal(SIGUSR1, ft_confirm);
	i = -1;
	while (argv[2][++i])
		ft_send_signal(pid, argv[2][i]);
	ft_send_signal(pid, argv[2][i]);
	return (0);
}
