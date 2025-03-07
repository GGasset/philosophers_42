/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   policies.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:43:41 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/27 15:40:21 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_err(int r_value, t_philo *philo)
{
	if (r_value != 0)
	{
		*philo->err = 1;
		philo->stop = 1;
	}
}

static int	grab_fork(t_philo *philo, int right_fork)
{
	pthread_mutex_t	*fork;

	if (philo->stop)
		return (0);
	if (right_fork)
		fork = philo->right_fork;
	else
		fork = philo->left_fork;
	if (!fork)
	{
		check_err(usleep(philo->args.die_t * 1000), philo);
		philo->stop = 1;
		*philo->err = 1;
		return (0);
	}
	check_err(pthread_mutex_lock(fork), philo);
	if (philo->stop)
		return (1);
	printf("%u %u has taken a fork\n",
		(unsigned int)get_elapsed_ms(philo->born_time),
		(unsigned int)philo->inmate_i + 1);
	return (1);
}

static void	eat(t_philo *philo)
{
	size_t	i;
	int		grabbed[2];

	if (philo->stop)
		return ;
	i = philo->inmate_i;
	grabbed[0] = grab_fork(philo, i % 2);
	grabbed[1] = grab_fork(philo, !(i % 2));
	check_err(pthread_mutex_lock(philo->eat_protection), philo);
	if (philo->stop)
	{
		stop_unlock(philo, grabbed);
		check_err(pthread_mutex_unlock(philo->eat_protection), philo);
		return ;
	}
	check_err(gettimeofday(&philo->last_ate_time, NULL), philo);
	printf("%u %u is eating\n", (unsigned int)get_elapsed_ms(philo->born_time),
		(unsigned int)philo->inmate_i + 1);
	check_err(pthread_mutex_unlock(philo->eat_protection), philo);
	check_err(usleep(philo->args.eat_t * 1000), philo);
	philo->n_servings++;
	check_err(pthread_mutex_unlock(philo->left_fork), philo);
	check_err(pthread_mutex_unlock(philo->right_fork), philo);
}

static void	sleepy_t(t_philo *philo)
{
	if (philo->stop)
		return ;
	printf("%u %u is sleeping\n",
		(unsigned int)get_elapsed_ms(philo->born_time),
		(unsigned int)philo->inmate_i + 1);
	check_err(usleep(philo->args.sleep_t * 1000), philo);
}

void	*philosopher_policy(void *raw_philo)
{
	size_t	i;
	t_philo	*philo;

	philo = (t_philo *)raw_philo;
	i = philo->inmate_i;
	check_err(gettimeofday(&philo->born_time, NULL), philo);
	check_err(gettimeofday(&philo->last_ate_time, NULL), philo);
	check_err(usleep((i % 2) * 2000), philo);
	while (!philo->stop)
	{
		eat(philo);
		sleepy_t(philo);
		if (philo->stop)
			break ;
		printf("%u %u is thinking\n",
			(unsigned int)get_elapsed_ms(philo->born_time),
			(unsigned int)philo->inmate_i + 1);
		check_err(usleep((i % 2) * 2000), philo);
		i++;
	}
	return (NULL);
}
