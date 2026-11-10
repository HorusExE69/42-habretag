/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:47:06 by esaillan          #+#    #+#             */
/*   Updated: 2026/11/10 16:40:57 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*init_stack_b(int capacity)
{
	t_stack	*b;

	b = malloc(sizeof(t_stack));
	if (!b)
		return (NULL);
	b->stack = malloc(sizeof(int) * capacity);
	if (!b->stack)
	{
		free(b);
		return (NULL);
	}
	b->size = 0;
	return (b);
}

static t_result	*init_result(int size)
{
    t_result	*res;
    int		capacity;

    res = malloc(sizeof(t_result));
    if (!res)
        return (NULL);
    capacity = size * size + 2 * size;
    res->ope = calloc((size_t)capacity, sizeof(t_operators));
    if (!res->ope)
    {
        free(res);
        return (NULL);
    }
    res->nb = 0;
    return (res);
}

static t_result	*parse_and_sort(t_stack *a)
{
	t_stack		*b;
	t_result	*res;
	int			i;
	int			j;
	
	b = init_stack_b(a->size);
	if (!b)
		return (NULL);
	res = init_result(a->size);
	if (!res)
	{
		free(b->stack);
		free(b);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (a->size > 1)
	{
		i = 0;
		while (i < a->size - 1)
		{
			if (a->stack[0] > a->stack[1])
			{
				ft_sa(a);
				res->ope[j++] = SA;
			}
			ft_ra(a);
			res->ope[j++] = RA;
			i++;
		}
		ft_pb(a, b);
		res->ope[j++] = PB;
	}
	while (b->size > 0)
	{
		ft_pa(a, b);
		res->ope[j++] = PA;
		ft_ra(a);
		res->ope[j++] = RA;
	}
	res->nb = j;
	free(b->stack);
	free(b);
	return (res);
}

static int	is_sorted(t_stack *a)
{
	int	i;

	i = 0;
	while (i < a->size - 1)
	{
		if (a->stack[i] > a->stack[i + 1])
			return (0);
		i++;
	}
	return (1);
}

t_result	*simple_algo(t_stack *a)
{
	if (!a || !a->stack)
		return (NULL);
	if (is_sorted(a))
		return (NULL);
	return (parse_and_sort(a));
}