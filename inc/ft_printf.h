/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 03:57:59 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:14:52 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_putchar(int fd, char c, int *ret);
void	ft_putstr(int fd, char *str, int *ret);
void	ft_putnbr(int fd, int n, int *ret);
void	ft_put_u_nbr(int fd, unsigned int n, int *ret);
void	ft_putnbr_base(int fd, unsigned int n, char c, int *ret);
void	ft_putadress(int fd, void *p, int *ret);
int		printf_fd(int fd, const char *str, ...);

#endif