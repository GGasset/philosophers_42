/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:06:56 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/27 15:30:24 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	get_index(size_t current, ssize_t change, size_t arr_len)
{
	ssize_t	out;

	out = (ssize_t)current;
	out += change;
	if (out < 0)
	{
		out = out % (ssize_t)arr_len;
		out *= -1;
		out = arr_len - out;
	}
	else if ((size_t)out >= arr_len)
	{
		out = out % arr_len;
	}
	return (out);
}

t_meeting	invite_philosophers(int argc, char **argv, int *err)
{
	t_args		args;
	t_meeting	out;
	size_t		i;

	ft_bzero(&out, sizeof(t_meeting));
	if (parse_args(argc, argv, &args, err))
		return (out);
	out.args = args;
	out.philo_count = args.n_philo;
	out.philosophers = malloc(sizeof(t_philo) * args.n_philo);
	out.forks = malloc(sizeof(pthread_mutex_t) * args.n_philo);
	out.eat_protection = malloc(sizeof(pthread_mutex_t) * args.n_philo);
	if (!out.philosophers || !out.forks || !out.eat_protection || *err)
		disband_meeting(&out, 0);
	i = 0;
	while (i < out.philo_count && !*err && out.philosophers)
	{
		ft_bzero(out.philosophers + i, sizeof(t_philo));
		out.philosophers[i].inmate_i = i;
		philo_init(out.philosophers + i, args, &out);
		pthread_mutex_init(out.forks + i, NULL);
		pthread_mutex_init(out.eat_protection + i, NULL);
		i++;
	}
	return (out);
}

void	philo_init(t_philo *philo, t_args args, t_meeting *meeting)
{
	size_t	i;

	philo->err = &meeting->err;
	philo->args = args;
	i = philo->inmate_i;
	philo->eat_protection = meeting->eat_protection + i;
	if (meeting->philo_count <= 1)
	{
		philo->left_fork = meeting->forks;
		return ;
	}
	philo->left_fork = meeting->forks + get_index(i, -1, args.n_philo);
	philo->right_fork = meeting->forks + i;
}
