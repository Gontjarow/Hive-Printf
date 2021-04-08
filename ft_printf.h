/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:57:36 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/08 08:35:13 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <math.h>

# define SPECIFIER_HH	1
# define SPECIFIER_H	2
# define SPECIFIER_L	3
# define SPECIFIER_LL	4

# define FLAG_JUSTIFY_LEFT	0b1
# define FLAG_FORCE_SIGN	0b10
# define FLAG_PAD_SIGN		0b100
# define FLAG_PREFIX		0b1000
# define FLAG_LEADING_ZERO	0b10000

/*
** Note: Haiku
**	I don't want these here,
**	but I have no options left.
**	Blame Norminette.
** Note: These are specifically related to the final output.
** p = output length or "total precision" without padding
** w = width padding
** z = zero padding
*/

typedef struct s_data
{
	va_list	ap;
	int		bit;
	int		width;
	int		precision;
	int		specifier;
	char	type;
	size_t	written;
	size_t	p;
	size_t	w;
	size_t	z;
}	t_data;

/*
** Main
*/

int		ft_printf(const char *format, ...);
char	parse_format(const char *format, t_data *flag);

/*
** Parser helpers
*/

char	*strany(const char *string, char *specifiers);
char	*strany_skip(const char *string, char *specifiers);
char	*strchr_skip(const char *string, char specifier);

/*
** Conversion: s
*/

void	output_str(char *arg, t_data *flag);

/*
** Conversion: di c
*/

void	output_int(long long arg, t_data *flag);
void	output_char(unsigned char arg, t_data *flag);

/*
** Conversion: Xx u o
*/

void	output_uint(unsigned long long arg, t_data *flag);
void	output_unsigned(unsigned long long arg, t_data *flag);
void	output_octal(unsigned long long arg, t_data *flag);

/*
** Conversion: p
*/

void	output_pointer(void *arg, t_data *flag);

/*
** Conversion: f
*/

void	output_double(long double arg, t_data *flag);

/*
** Output helpers
*/

size_t	putstr_case(const char *str, int mode);
size_t	putstrn_case(const char *str, size_t n, int mode);
void	width_padder(int w, const char c, t_data *flag);
char	*ft_utoa(unsigned long long number);
char	*ft_utoa_base(unsigned long long number, int base);

#endif
