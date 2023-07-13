/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:57:02 by jhogonca          #+#    #+#             */
/*   Updated: 2023/07/12 15:34:13 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void	ft_putstr(char *str);
void	ft_putnbr(unsigned int pid);

static void	handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static int				bit_index = -1;
	static unsigned char	c;

	(void)context;
	if (bit_index < 0)
		bit_index = 7;
	if (signum == SIGUSR1)
		c |= (1 << bit_index);
	if (--bit_index < 0)
	{
		write(1, &c, 1);
		c = 0;
		if (kill(info->si_pid, SIGUSR1) == -1)
			ft_putstr("Server failed send confirmation to client");
	}
}

static void	config_signals(void)
{
	struct sigaction	sa_signal;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = block_mask;
	sa_signal.sa_sigaction = &handle_sigusr;
	if (sigaction(SIGUSR1, &sa_signal, NULL) == -1)
		ft_putstr("Failed to change SIGUSR1's behavior");
	if (sigaction(SIGUSR2, &sa_signal, NULL) == -1)
		ft_putstr("Failed to change SIGUSR2's behavior");
}

int	main(void)
{
	ft_putstr("\033[34mSERVER PID: \033[0m");	
	ft_putstr("\033[44m");
	ft_putnbr(getpid());
	ft_putstr("\033[0m");
	write(1, "\n", 1);
	while (true)
		config_signals();
	return (0);
}
