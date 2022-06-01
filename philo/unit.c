/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:37:40 by stapioca          #+#    #+#             */
/*   Updated: 2022/04/28 19:52:21 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_atoi(const char *str)
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

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
