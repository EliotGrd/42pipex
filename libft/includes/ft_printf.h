/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:33:30 by egiraud           #+#    #+#             */
/*   Updated: 2025/05/12 01:07:51 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		ft_putnbr(int nb);
int		ft_putunsigned_base(unsigned int nb, char *base);
int		ft_putchar_c(int n);
int		ft_putstr_c(char *str);
int		ft_putaddress(void *ptr);
/*int		ft_strlen(char *str);*/

#endif
