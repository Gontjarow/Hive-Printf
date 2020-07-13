/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:57:36 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/28 23:30:24 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <math.h>

# define PAD_DEFAULT	0b00
# define PAD_ZERO		0b10
# define PAD_RIGHT		0b1

# define SPECIFIER_H	1
# define SPECIFIER_HH	2
# define SPECIFIER_L	3
# define SPECIFIER_LL	4

# define FLAG_JUSTIFY_LEFT	0b1
# define FLAG_FORCE_SIGN	0b10
# define FLAG_HIDE_SIGN		0b100
# define FLAG_PREFIX		0b1000
# define FLAG_PAD_ZERO		0b10000

typedef struct	s_data
{
	va_list	ap;
	int		bit;
	int		width;
	int		precision;
	int		specifier;
	char	padder;
	char	type;
	size_t	written;
}				t_data;

int				ft_printf(const char *format, ...);
char			parse_format(const char *format, t_data *flag);

int				output_str(char *arg, t_data *flag);
int				output_int(long long arg, t_data *flag);
int				output_uint(unsigned long long arg, t_data *flag);
int				output_pointer(void *arg, t_data *flag);
int				output_double(long double arg, t_data *flag);

void			putstr_case(const char *str, int mode);
int				width_padder(int length, t_data *flag, long long arg);
int				zero_padder(int length, t_data *flag, long long arg);
void			ft_putnstr(char *str, int bytes);


char			*strany(const char *string, char *specifiers);
char			*strany_skip(const char *string, char *specifiers);
char			*strchr_skip(const char *string, char specifier);
char			*utoa(unsigned long long num);
char			*ft_ftoa(long double value, unsigned char precision);

typedef union	u_double
{
	double d;
	unsigned long ul;
}				t_double;

typedef union	u_float
{
	float f;
	unsigned int u;
}				t_float;

int			float_to_binary(float f);
int			double_to_binary(double d);

#endif
