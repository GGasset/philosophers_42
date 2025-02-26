/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:21:30 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/26 13:18:55 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_args
{
	ssize_t	n_philo;
	ssize_t	die_t;
	ssize_t	eat_t;
	ssize_t	sleep_t;
	ssize_t	servings_to_satiate;
}		t_args;

typedef struct s_philo
{
	int				stop;
	int				dead;
	struct timeval	born_time;
	struct timeval	last_ate_time;
	size_t			n_servings;
	size_t			inmate_i;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*eat_protection;
	int				*err;
	t_args			args;
}		t_philo;

typedef struct s_meeting
{
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_t		*realities;
	t_args			args;
	size_t			philo_count;
	pthread_mutex_t	*eat_protection;
	int				err;
}		t_meeting;

int			main(int argc, char *argv[]);

void		*philosopher_policy(void *raw_philo);
void		stop_unlock(t_philo *philo, int grabbed[2]);
void		check_err(int r_value, t_philo *philo);

void		observe_philosophers(t_meeting *meeting);
void		check_death(t_meeting *meeting, size_t i, int *stop);
void		greet_philosophers(t_meeting *planning, int *err);

t_meeting	invite_philosophers(int argc, char **argv, int *err);
int			disband_meeting(t_meeting *meeting, int destroy_mutex);
void		philo_init(t_philo *philo, t_args args, t_meeting *meeting);
int			parse_args(int argc, char **argv, t_args *args, int *err);

size_t		get_elapsed_ms(struct timeval start);
void		ft_bzero(void *mem, size_t size);
int			ft_atoi_s(const char *nptr, int *err);

#endif