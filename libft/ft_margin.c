/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_margin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 12:20:12 by ariabyi           #+#    #+#             */
/*   Updated: 2018/01/21 12:23:06 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_margin(char *pen, char *apple)
{
	char		*applepen;
	char		*temp_applepen;

	applepen = NULL;
	temp_applepen = ft_multjoin(3, applepen, pen, apple);
	applepen = ft_strdup(temp_applepen);
	ft_strdel(&temp_applepen);
	ft_strdel(&pen);
	return (applepen);
}
