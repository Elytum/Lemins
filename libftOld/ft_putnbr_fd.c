/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 18:34:09 by smarie-c          #+#    #+#             */
/*   Updated: 2013/11/21 18:53:15 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	rev;

	rev = 0;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	while (n > 0)
	{
		rev = rev * 10;
		rev = rev + (n % 10);
		n = n / 10;
	}
	while (rev > 0)
	{
		n = rev % 10;
		ft_putchar_fd(n + 48, fd);
		rev = rev / 10;
	}
}
