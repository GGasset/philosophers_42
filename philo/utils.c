/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:35:50 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/26 13:23:07 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_unlock(t_philo *philo, int grabbed[2])
{
	size_t	i;

	i = philo->inmate_i;
	if (grabbed[(i % 2)])
		check_err(pthread_mutex_unlock(philo->left_fork), philo);
	if (grabbed[!(i % 2)])
		check_err(pthread_mutex_unlock(philo->right_fork), philo);
}

void	check_death(t_meeting *meeting, size_t i, int *stop)
{
	size_t	elapsed_ms;

	if (0 != pthread_mutex_lock(meeting->eat_protection + i))
		meeting->err = 1;
	elapsed_ms = get_elapsed_ms(meeting->philosophers[i].last_ate_time);
	meeting->philosophers[i].dead
		= elapsed_ms > (size_t)meeting->args.die_t;
	if (meeting->philosophers[i].dead)
		*stop = 2;
	if (pthread_mutex_unlock(meeting->eat_protection + i) != 0)
		meeting->err = 1;
}

void	ft_bzero(void *mem, size_t size)
{
	size_t	i;

	if (!mem)
		return ;
	i = 0;
	while (i < size)
	{
		((char *)mem)[i] = 0;
		i++;
	}
}

size_t	get_elapsed_ms(struct timeval start)
{
	size_t			out;
	struct timeval	now;

	gettimeofday(&now, NULL);
	out = (now.tv_sec - start.tv_sec) * 1000;
	out += (now.tv_usec - start.tv_usec) / 1000;
	return (out);
}
