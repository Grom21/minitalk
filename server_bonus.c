/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:29:45 by etisha            #+#    #+#             */
/*   Updated: 2021/12/27 18:29:48 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		c = n + '0';
		write (fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

static char	ft_print_char(char c)
{
	if (c == '\0')
		write (1, "\n", 1);
	else
		write (1, &c, 1);
	c = 0;
	return (c);
}

static void	ft_signal(int sigusr, siginfo_t *inf, void *text)
{
	static int	x;
	static char	c;
	static int	pid;

	(void)text;
	if (pid != inf->si_pid)
	{
		x = 0;
		c = 0;
	}
	if (sigusr == SIGUSR1)
	{
		c ^= 1 << x;
		x++;
	}
	else
		x++;
	if (x == 8)
	{
		c = ft_print_char(c);
		x = 0;
	}
	pid = inf->si_pid;
	kill(inf->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sigredirect;
	sigset_t			m_sign;

	ft_putnbr_fd(getpid(), 1);
	write (1, "\n", 1);
	sigredirect.sa_sigaction = ft_signal;
	sigemptyset(&m_sign);
	sigaddset(&m_sign, SIGINT);
	sigaddset(&m_sign, SIGUSR1);
	sigaddset(&m_sign, SIGUSR2);
	sigredirect.sa_mask = m_sign;
	while (1)
	{
		sigaction(SIGUSR1, &sigredirect, 0);
		sigaction(SIGUSR2, &sigredirect, 0);
		pause();
	}
	return (0);
}
