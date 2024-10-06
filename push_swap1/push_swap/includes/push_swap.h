#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_stack
{
	int	nbr;
	int	index;
	int	cost;
	int	above_median;
	bool	cheapest;
	struct s_stack	*target;
	struct s_stack	*next;
	struct s_stack	*previous;
}		t_stack;

//process argument
char	**split_arg(char *arg, char set);
long	ft_atol(char *s);
//process_stack
t_stack		*find_last_node(t_stack *stack);
void	append_list(t_stack **stack, int nb);
void		init_stack_a(t_stack **stack_a, char *argv[]);
void		ft_print_list(t_stack *lst);
//check_stack_utils
bool		is_sorted(t_stack *stack);
int		lst_length(t_stack *stack);
//sorting_utils
t_stack	*find_biggest(t_stack *lst);
t_stack	*find_smallest(t_stack *lst);
void	index_cmp(t_stack *stack);
void	cost_count(t_stack *stack_a, t_stack *stack_b);
t_stack	*get_cheapest(t_stack *stack);
//a_to_b
void	find_target_for_a(t_stack *stack_a, t_stack *stack_b);
void	init_node_a(t_stack *stack_a, t_stack *stack_b);
void	set_cheapest(t_stack *stack);
void	a_to_b(t_stack **stack_a, t_stack **stack_b);
//b_to_a
void	find_target_for_b(t_stack *stack_a, t_stack *stack_b);
void	init_node_b(t_stack *stack_a, t_stack *stack_b);
void	b_to_a(t_stack **stack_a, t_stack **stack_b);
//sort_stacks
void	sort_stacks(t_stack **a, t_stack **b);
void	sort_three(t_stack **a);
void	min_on_top(t_stack **stack_a);
//operations
//swap
static void	swap(t_stack **head);
void	sa(t_stack **stack_a, bool print);
void	sb(t_stack **stack_b, bool print);
void	ss(t_stack **stack_a, t_stack **stack_b, bool print);
//push
static void	push(t_stack **dst, t_stack **src);
void	pa(t_stack **stack_a, t_stack **stack_b, bool print);
void	pb(t_stack **stack_a, t_stack **stack_b, bool print);
void	push_util(t_stack **stack, t_stack *first, char name);
//rotate
static void	rotate(t_stack **stack);
void	ra(t_stack **stack_a, bool print);
void	rb(t_stack **stack_b, bool print);
void	rr(t_stack **stack_a, t_stack **stack_b, bool print);
void	rotate_both(t_stack **stack_a, t_stack **stack_b, t_stack *cheapest);
//reverse_rotate
static void	reverse_rotate(t_stack **stack);
void	rra(t_stack **stack_a, bool print);
void	rrb(t_stack **stack_b, bool print);
void	rrr(t_stack **stack_a, t_stack **stack_b, bool print);
void	reverse_rotate_both(t_stack **stack_a, t_stack **stack_b, t_stack *cheapest);
//handle errors
int	error_syntax(char *str);
int	error_duplicate(t_stack *stack_a, int n);
void	free_stack(t_stack **stack);
void	free_errors(t_stack **stack_a);
#endif /* push_swap_h */
