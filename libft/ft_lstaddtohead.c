/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamila <mcamila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 15:11:32 by mcamila           #+#    #+#             */
/*   Updated: 2019/09/21 15:22:12 by mcamila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstaddtohead(t_list *head, t_list *new)
{
	if (!head || !new)
		return (NULL);
	head->next = new;
	new->next = NULL;
    return (new);
}