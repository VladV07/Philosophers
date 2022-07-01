/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:14:58 by stapioca          #+#    #+#             */
/*   Updated: 2022/07/01 22:01:14 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_get(const char *str)
{
	long int	nb;
	int			sign;

	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + *str - '0';
		str++;
		if (nb > 2147483647 && *str != '\0' && sign == 1)
			return (-1);
		if (nb > 2147483648 && *str != '\0' && sign == -1)
			return (0);
	}
	if (sign == -1)
		nb = ~nb + 1;
	return (nb);
}

long long	get_time(void)
{
	struct timeval	t;
	long long		now;

	gettimeofday (&t, NULL);
	now = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (now);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

int	err_print(int code)
{
	if (code == 1)
		printf("wrong number of arguments.\n");
	else if (code == 2)
		printf("arguments are not correct.\n");
	else if (code == 3)
		printf("malloc allocation error.\n");
	else if (code == 4)
		printf("semafor creation error.\n");
	else if (code == 5)
		printf("fork error.\n");
	else if (code == 6)
		printf("failed to create the thread.\n");
	else if (code == 7)
		printf("failed to join the thread.\n");
	return (1);
}

void	ft_free(t_philo *dt)
{
	sem_unlink("print");
	sem_unlink("fork");
	sem_close(dt->sem_print);
	sem_close(dt->sem_fork);
	free(dt->pid);
	free(dt);
}
