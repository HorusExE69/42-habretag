/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habretag <habretag@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:19:12 by habretag          #+#    #+#             */
/*   Updated: 2026/11/10 15:55:00 by habretag         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include "stack.h"
# include "operators.h"
# include "result.h"

// Main functions
t_result	*compute_algo(t_stack *a);
t_result	*simple_algo(t_stack *a);

// Test
void	print_t_stack(t_result *result);

// Utils functions
char		**ft_substr(char **s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t n);
int			ft_isnumber(char *str);
int			ft_atoi(const char *nptr);

// Operators utils
void		ft_swap(int *a, int *b);
int			ft_pop(t_stack *stack);
void		ft_push(t_stack *stack, int new);
int			ft_popfront(t_stack *stack);
void		ft_pushfront(t_stack *stack, int new);

// Operators
t_op_code	ft_operator(t_stack *a, t_stack *b, t_operators operator);
t_op_code	ft_sa(t_stack *a);
t_op_code	ft_sb(t_stack *b);
t_op_code	ft_ss(t_stack *a, t_stack *b);
t_op_code	ft_pa(t_stack *a, t_stack *b);
t_op_code	ft_pb(t_stack *a, t_stack *b);
t_op_code	ft_ra(t_stack *a);
t_op_code	ft_rb(t_stack *b);
t_op_code	ft_rr(t_stack *a, t_stack *b);
t_op_code	ft_rra(t_stack *a);
t_op_code	ft_rrb(t_stack *b);
t_op_code	ft_rrr(t_stack *a, t_stack *b);

#endif