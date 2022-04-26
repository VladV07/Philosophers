/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stapioca <stapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:09:12 by stapioca          #+#    #+#             */
/*   Updated: 2022/04/26 21:29:50 by stapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct s_stract
{
	int	nb_of_ph;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_times_each_ph_must_eat;
	int	vilka_count;
	pthread_mutex_t	mutex;
	pthread_t		*pt;
}	t_philo;

int	ft_atoi(const char *str);

#endif