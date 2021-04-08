/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:54:29 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/08 08:46:10 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	send_int(t_data *flag)
{
	if (flag->specifier == 0)
		output_int(va_arg(flag->ap, int), flag);
	else if (flag->specifier == SPECIFIER_L)
		output_int(va_arg(flag->ap, long int), flag);
	else if (flag->specifier == SPECIFIER_LL)
		output_int(va_arg(flag->ap, long long int), flag);
	else if (flag->specifier == SPECIFIER_H)
		output_int((signed short)va_arg(flag->ap, int), flag);
	else if (flag->specifier == SPECIFIER_HH)
		output_int((signed char)va_arg(flag->ap, int), flag);
}

static void	send_uint(t_data *flag)
{
	if (flag->specifier == 0)
		output_uint(va_arg(flag->ap, unsigned int), flag);
	else if (flag->specifier == SPECIFIER_L)
		output_uint(va_arg(flag->ap, unsigned long int), flag);
	else if (flag->specifier == SPECIFIER_LL)
		output_uint(va_arg(flag->ap, unsigned long long int), flag);
	else if (flag->specifier == SPECIFIER_H)
		output_uint((unsigned short)va_arg(flag->ap, unsigned int), flag);
	else if (flag->specifier == SPECIFIER_HH)
		output_uint((unsigned char)va_arg(flag->ap, unsigned int), flag);
}

static void	send_floating(t_data *flag)
{
	if (flag->specifier == 0)
		output_double(va_arg(flag->ap, double), flag);
	else if (flag->specifier == SPECIFIER_L)
		output_double(va_arg(flag->ap, long double), flag);
}

static char	try_parsing(const char *format, t_data *flag)
{
	char	parsed;

	parsed = parse_format(++format, flag);
	if (parsed == 0)
		return (0);
	if (flag->type == 's')
		output_str(va_arg(flag->ap, char *), flag);
	else if (flag->type == '%')
		flag->written += write(1, "%", 1);
	else if (flag->type == 'c')
		output_char((unsigned char)va_arg(flag->ap, int), flag);
	else if (ft_strchr("di", flag->type))
		send_int(flag);
	else if (ft_strchr("Xxuo", flag->type))
		send_uint(flag);
	else if (flag->type == 'p')
		output_pointer(va_arg(flag->ap, void *), flag);
	else if (flag->type == 'f')
		send_floating(flag);
	return (parsed);
}

int	ft_printf(const char *format, ...)
{
	t_data	flag;

	flag = (t_data){{{0}}, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	va_start(flag.ap, format);
	while (*format)
	{
		if (format[0] == '%')
		{
			flag.bit = 0;
			flag.width = 0;
			flag.precision = -1;
			flag.specifier = 0;
			flag.type = 0;
			flag.p = 0;
			format += 1 + try_parsing(format, &flag);
			continue ;
		}
		write(1, format, 1);
		++flag.written, *format && ++format;
	}
	va_end(flag.ap);
	return (flag.written);
}
