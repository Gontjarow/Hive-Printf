/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 07:48:21 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 21:47:15 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_zeros(size_t *len, t_data *flag)
{
	flag->z = 0;
	if (flag->precision > (int)(*len))
	{
		flag->z = flag->precision - *len;
		flag->w -= flag->z;
	}
}

static void	init(size_t *len, int *prefix, t_data *flag)
{
	flag->p = flag->precision;
	if (flag->precision == -1 || flag->p > *len)
	{
		flag->p = *len;
	}
	flag->w = 0;
	if ((size_t)flag->width - *prefix > flag->p)
	{
		flag->w = (size_t)flag->width - *prefix - flag->p;
		if (*len > flag->p)
		{
			flag->w -= (*len - flag->p);
		}
	}
	init_zeros(len, flag);
}

static void	justify_left(const char *str, t_data *flag)
{
	size_t	len;
	int		prefix;

	prefix = 2;
	len = ft_strlen(str);
	init(&len, &prefix, flag);
	flag->written += ft_putstrn("0x", prefix);
	width_padder(flag->z, '0', flag);
	flag->written += putstr_case(str, -1);
	width_padder(flag->w, ' ', flag);
}

static void	justify_right(const char *str, t_data *flag)
{
	size_t	len;
	int		prefix;

	prefix = 2;
	len = ft_strlen(str);
	init(&len, &prefix, flag);
	width_padder(flag->w, ' ', flag);
	flag->written += ft_putstrn("0x", prefix);
	width_padder(flag->z, '0', flag);
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
