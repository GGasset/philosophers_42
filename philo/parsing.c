/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:06:20 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/26 12:08:11 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_args *args, int *err)
{
	int	tmp_err;
	int	tmp;

	*err = (!args || (argc != 5 && argc != 6));
	if (*err)
		return (*err);
	tmp = ft_atoi_s(argv[1], &tmp_err);
	*err = *err || tmp_err || tmp <= 0;
	args->n_philo = tmp;
	args->die_t = ft_atoi_s(argv[2], &tmp_err);
	*err = *err || tmp_err || args->die_t < 0;
	args->eat_t = ft_atoi_s(argv[3], &tmp_err);
	*err = *err || tmp_err || args->eat_t < 0;
	args->sleep_t = ft_atoi_s(argv[4], &tmp_err);
	*err = *err || tmp_err || args->sleep_t < 0;
	args->servings_to_satiate = -1;
	if (argc == 6)
	{
		tmp = ft_atoi_s(argv[5], &tmp_err);
		*err = *err || tmp_err || tmp < 0;
		args->servings_to_satiate = tmp;
	}
	return (*err);
}
