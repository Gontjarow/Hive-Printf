/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 07:48:21 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 17:50:59 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init(size_t *len, int *prefix, int *w, t_data *flag)
{
	if (flag->precision == -1)
	{
		flag->p = *len;
	}
	else
	{
		flag->p = flag->precision;
	}
	if (flag->p > *len)
	{
		flag->p = *len;
	}
	if ((size_t)flag->width - *prefix > flag->p)
	{
		*w = (size_t)flag->width - *prefix - flag->p;
		if (*len > flag->p)
		{
			*w -= (*len - flag->p);
		}
	}
	else
	{
		*w = 0;
	}
}

static void	init_zeros(size_t *len, int *z, int *w, t_data *flag)
{
	if (flag->precision > (int)(*len))
	{
		*z = flag->precision - *len;
	}
	else
	{
		*z = 0;
	}
	if (*z > 0)
	{
		*w -= *z;
	}
}

static void	justify_left(const char *str, t_data *flag)
{
	int		w;
	int		z;
	size_t	len;
	int		prefix;

	prefix = 2;
	len = ft_strlen(str);
	init(&len, &prefix, &w, flag);
	init_zeros(&len, &z, &w, flag);
	flag->written += ft_putstrn("0x", prefix);
	width_padder(z, '0', flag);
	flag->written += putstr_case(str, -1);
	width_padder(w, ' ', flag);
}

static void	justify_right(const char *str, t_data *flag)
{
	int		w;
	int		z;
	size_t	len;
	int		prefix;

	prefix = 2;
	len = ft_strlen(str);
	init(&len, &prefix, &w, flag);
	init_zeros(&len, &z, &w, flag);
	width_padder(w, ' ', flag);
	flag->written += ft_putstrn("0x", prefix);
	width_padder(z, '0', flag);
	flag->written += putstr_case(str, -1);
}

/*
** Undefined flags: #, 0, ' ', +
** Applicable flags: -
** Precision: Minimum amount of digits.
** Leading zeroes (after prefix) if necessary.
*/

void	output_pointer(void *arg, t_data *flag)
{
	char	*str;

	if (arg)
		str = ft_itoa_base((long long)arg, 16);
	else
		str = ft_strdup("0");
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(str, flag);
	else
		justify_right(str, flag);
	free(str);
}
