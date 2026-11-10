/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_p_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:29:29 by esaillan          #+#    #+#             */
/*   Updated: 2026/11/10 15:22:57 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_op_code	ft_pa(t_stack *a, t_stack *b)
{
	int	changed;

	if (b->size == 0)
		return (ERROR);
	changed = ft_popfront(b);
	ft_pushfront(a, changed);
	return (GOOD);
}

t_op_code	ft_pb(t_stack *a, t_stack *b)
{
	int	changed;

	if (a->size == 0)
		return (ERROR);
	changed = ft_popfront(a);
	ft_pushfront(b, changed);
	return (GOOD);
}
