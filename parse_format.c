/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:42:32 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/18 21:43:23 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// width, precision, signage, justification, fill
// https://www.cypress.com/file/54441/download

// char	argument_index(const char * format)
// {
// 	char	bytes;
// 	char	*c;

// 	bytes = 0;
// 	if (ft_isdigit(*format) && (c = ft_strchr(format, '$')))
// 	{
// 		bytes = c - format;
// 	}
// 	return (bytes + 1);
// }

char	parse_format(const char * format, t_flag *flag)
{
	int bytes;

	if (*format == '%')
	{
		write(1, format, 1);
		return (1);
	}
	bytes = 0;
	while (*(++format))
	{
		if (*format == '-')
		{
			flag->pad = PAD_RIGHT;
			++format;
		}
		while (*format == '0')
		{
			flag->pad |= PAD_ZERO;
			++format;
		}
		while (ft_isdigit(*format))
		{
			flag->width *= 10;
			flag->width += (*format - '0');
			++format;
		}
		if ((flag->type = *strcany("dinouxX", *format)))
		{
			++format;
			print_i(flag, format);
		}
		else if((flag->type = *strcany("sc", *format)))
		{
			++format;
			print_s(flag, format);
		}
		else
		{
			ft_putstr("{All we had to do was follow the damn flags, printf!}");
			return (0);
		}
	}
	return (bytes);
}
