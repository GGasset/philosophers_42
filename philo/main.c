/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:05:28 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/26 11:58:16 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_meeting	meeting;
	int			err;

	meeting = invite_philosophers(argc, argv, &err);
	if (err)
	{
		printf("Usage: "
			"number_of_philosophers time_to_die time_to_eat time_to_sleep"
			" [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	greet_philosophers(&meeting, &err);
	if (err)
	{
		printf("pthread err\n");
		return (disband_meeting(&meeting, 1));
	}
	observe_philosophers(&meeting);
	disband_meeting(&meeting, 1);
	return (0);
}
