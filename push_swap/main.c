/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:17:20 by habretag          #+#    #+#             */
/*   Updated: 2026/11/10 16:38:06 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "ft_printf.h"

t_stack	*check_no_flags(int argc, char **argv)
{
    int		i;
    t_stack	*res;

    i = 0;
    res = malloc(sizeof(t_stack));
    if (!res)
        return (NULL);
    res->size = argc;
    res->stack = malloc(sizeof(int) * argc);
    if (!res->stack)
    {
        free(res);
        return (NULL);
    }
    while (i < argc)
    {
        if (!ft_isnumber(argv[i]))
        {
            free(res->stack);
            free(res);
            return (NULL);
        }
        res->stack[i] = ft_atoi(argv[i]);
        i++;
    }
    return (res);
}

t_stack	*check_flags(int argc, char **argv, int *flag)
{
	if (ft_strcmp(argv[1], "--simple") == 0)
		*flag = 0;
	else if (ft_strcmp(argv[1], "--medium") == 0)
		*flag = 1;
	else if (ft_strcmp(argv[1], "--complex") == 0)
		*flag = 2;
	else if (ft_strcmp(argv[1], "--adaptative") == 0)
		*flag = 3;
	return (check_no_flags(argc - 2, argv + 2));
}

int	main(int argc, char **argv)
{
    int		flag;
    t_stack	*a;
    t_result	*res;

    flag = -1;
    if (argc < 2)
        return (1);
    if (argv[1][0] == '-' && argv[1][1] == '-')
        a = check_flags(argc, argv, &flag);
    else
        a = check_no_flags(argc - 1, argv + 1);
    if (!a)
        return (1);
    if (flag == 3)
    {
        res = compute_algo(a);
        if (res)
            print_t_stack(res);
    }
    else if (flag == 0)
    {
        res = simple_algo(a);
        if (res)
            print_t_stack(res);
    }
    for (int i = 0; i < a->size; i++)
        ft_printf("%d ", a->stack[i]);
    return (0);
}
