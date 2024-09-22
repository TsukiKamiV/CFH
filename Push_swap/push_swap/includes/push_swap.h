#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "../lib/libft/libft.h"

typedef struct s_stack
{
	int	nbr;
	int	index;
	int	cost;
	struct s_stack	*target;
	struct s_stack	*next;
	struct s_stack	*previous;
}		t_stack;

//process_stack
long	ft_atol(char *s);
t_stack		*find_last_node(t_stack *stack);
void	append_list(t_stack **stack, int nb);
void		init_stack_a(t_stack **stack_a, char *argv[]);
void		ft_print_list(t_stack *lst);

//check_stack_utils
int	is_sorted(t_stack *stack);
int	lst_length(t_stack *stack);

//sorting_utils
void	sort_three(t_stack **a);
t_stack	*find_biggest(t_stack *lst);

//operations
//swap
void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **stack_a, t_stack **stack_b);

//rotate
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);

//reverse_rotate
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
#endif /* push_swap_h */
