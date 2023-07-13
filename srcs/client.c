/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:17:22 by jhogonca          #+#    #+#             */
/*   Updated: 2023/07/13 17:23:15 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *str);
void	ft_putnbr(unsigned int pid);

static int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *str++ - '0';
	return (result);
}

static void	send_msg(int spid, char *msg)
{
	unsigned char	c;
	int				bits;

	while (*msg)
	{
		c = *msg;
		bits = 8;
		while (--bits >= 0)
		{
			if (c & (1 << bits))
				kill(spid, SIGUSR1);
			else
				kill(spid, SIGUSR2);
			usleep(50);
		}
		msg++;
	}
}

static void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		write(1, "\033[32mMessage received by server\033[0m\n", 37);
}

int	main(int ac, char **av)
{
	struct sigaction	st_signal;

	if (ac != 3)
		exit(write(1, "\033[31mInvalid input\033[0m\n", 24));
	ac = -1;
	while (av[1][++ac])
		if (!(av[1][ac] >= '0' && av[1][ac] <= '9'))
			exit(write(1, "\033[31mInvalid Server PID\033[0m\n", 28));
	ft_putstr("\033[0;35mCLIENT PID: \033[0m");
	ft_putstr("\033[45m");
	ft_putnbr(getpid());
	ft_putstr("\033[0m\n");
	st_signal.sa_handler = &sig_handler;
	st_signal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &st_signal, NULL) == -1)
		write(1, "Failed to change SIGUSR1's behavior", 35);
	if (sigaction(SIGUSR2, &st_signal, NULL) == -1)
		write(1, "Failed to change SIGUSR2's behavior", 35);
	send_msg(ft_atoi(av[1]), av[2]);
	if (av[2][0] != '\0')
		send_msg(ft_atoi(av[1]), "\n");
	return (0);
}
