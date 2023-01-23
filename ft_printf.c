/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaltaza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:33:23 by abaltaza          #+#    #+#             */
/*   Updated: 2023/01/23 18:39:22 by abaltaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

int	ft_printf(const char *format, ...) {
       va_list args;
	int	i;
 	int	ret;

	va_start(args, format);

	i = 0;
	ret = 0;
	while (format && format[i]) {
		if(	
