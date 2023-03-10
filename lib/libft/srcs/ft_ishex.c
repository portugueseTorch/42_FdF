/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda_cruz <gda_cruz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:00:33 by gda_cruz          #+#    #+#             */
/*   Updated: 2023/02/04 13:01:19 by gda_cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ishex(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) \
		&& !(str[i] >= 'a' && str[i] <= 'f') \
		&& !(str[i] >= 'A' && str[i] <= 'F'))
			return (0);
		i++;
	}
	return (1);
}
