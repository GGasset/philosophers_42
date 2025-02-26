/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:16:43 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/26 12:00:35 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	disband_meeting(t_meeting *meeting, int destroy_mutex)
{
	size_t	i;

	i = 0;
	while (i < meeting->philo_count && destroy_mutex)
	{
		pthread_mutex_destroy(meeting->eat_protection + i);
		pthread_mutex_destroy(meeting->forks + i);
		i++;
	}
	if (!meeting)
		return (0);
	if (meeting->forks)
		free(meeting->forks);
	if (meeting->philosophers)
		free(meeting->philosophers);
	if (meeting->realities)
		free(meeting->realities);
	if (meeting->eat_protection)
		free(meeting->eat_protection);
	meeting->eat_protection = 0;
	meeting->realities = 0;
	meeting->philosophers = 0;
	meeting->forks = 0;
	meeting->philo_count = 0;
	return (0);
}
