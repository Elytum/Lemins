/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarie-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/30 17:01:11 by smarie-c          #+#    #+#             */
/*   Updated: 2013/12/01 23:05:58 by smarie-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_fibonacci(int n)
{
	int	i;
	int first;
	int second;
	int	ret;

	i = 0;
	first = 1;
	second = 1;
	while (i < n)
	{
		if (i == 1 || i == 0)
			n = 1;
		else
		{
			ret = first + second;
			first = second;
			second = ret;
			i++;
		}
	}
	return (ret);
}
