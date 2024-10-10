/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:44:55 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 19:28:02 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_stack
{
	int					nbr;
	int					index;
	int					push_cost;
	bool				above_median;
	bool				cheapest;
	struct s_stack		*target_node;
	struct s_stack		*next;
	struct s_stack		*prev;
}	t_stack;

int			error_syntax(char *str);
int			error_duplicate(t_stack *a, int n);
void		free_stack(t_stack **stack);
void		free_errors(t_stack **a);
void		ft_free_tab(char **tab);

void		init_stack_a(t_stack **a, int argc, char **argv);
char		**split(char *s, char c);

void		init_nodes_a(t_stack *a, t_stack *b);
void		init_nodes_b(t_stack *a, t_stack *b);

void		current_index(t_stack *stack);
void		set_cheapest(t_stack *stack);
t_stack		*get_cheapest(t_stack *stack);
void		prep_for_push(t_stack **s, t_stack *n, char c);

int			stack_len(t_stack *len);
t_stack		*find_last(t_stack *stack);
bool		stack_sorted(t_stack *stack);
t_stack		*find_min(t_stack *stack);
t_stack		*find_max(t_stack *stack);

void		sa(t_stack **a, bool print);
void		sb(t_stack **b, bool print);
void		ss(t_stack **a, t_stack **b, bool print);
void		ra(t_stack **a, bool print);
void		rb(t_stack **b, bool print);
void		rr(t_stack **a, t_stack **b, bool print);
void		rra(t_stack **a, bool print);
void		rrb(t_stack **b, bool print);
void		rrr(t_stack **a, t_stack **b, bool print);
void		pa(t_stack **a, t_stack **b, bool print);
void		pb(t_stack **b, t_stack **a, bool print);

void		sort_three(t_stack **a);
void		sort_stacks(t_stack **a, t_stack **b);

#endif
