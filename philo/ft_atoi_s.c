/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggasset- <ggasset-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:58:56 by ggasset-          #+#    #+#             */
/*   Updated: 2025/02/04 17:37:52 by ggasset-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static char	is_blank(char c)
{
	char	output;

	output = c == ' ';
	output = c == '\t' || output;
	output = c == '\n' || output;
	output = c == '\v' || output;
	output = c == '\f' || output;
	output = c == '\r' || output;
	return (output);
}

static void	skip_blanks(int *i, const char *nptr)
{
	*i = 0;
	while (is_blank(nptr[*i]) && nptr[*i])
		++*i;
}

static void	check_sign(const char *nptr, int *i, int *sign, int *err)
{
	*sign = 1 - 2 * (nptr[*i] == '-');
	*i += nptr[*i] == '-' || nptr[*i] == '+';
	*err = !ft_isdigit(nptr[*i]);
}

int	ft_atoi_s(const char *nptr, int *err)
{
	int	sign;
	int	output;
	int	prev;
	int	i;

	if (!err)
		return (0);
	prev = 0;
	output = 0;
	skip_blanks(&i, nptr);
	check_sign(nptr, &i, &sign, err);
	while (ft_isdigit(nptr[i]) && !*err)
	{
		output *= 10;
		output += (nptr[i] - '0') * sign;
		if (prev > output && sign == 1)
			*err = 1;
		else if (prev < output && sign == -1)
			*err = 1;
		prev = output;
		i++;
	}
	return (output);
}
