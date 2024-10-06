#include "../../includes/push_swap.h"

void	sort_stacks(t_stack **stack_a, t_stack **stack_b)
{
	int	len_a;
	
	len_a = lst_length(*stack_a);
	if (len_a-- > 3 && !is_sorted(*stack_a))
		pb(stack_b, stack_a, false);
	if (len_a-- > 3 && !is_sorted(*stack_a))
		pb(stack_b, stack_a, false);
	while (len_a-- > 3 && !is_sorted(*stack_a))
	{
		init_node_a(*stack_a, *stack_b);
		a_to_b(stack_a, stack_b);
	}
	sort_three(stack_a);
	while (*stack_b)
	{
		init_node_b(*stack_a, *stack_b);
		b_to_a(stack_a, stack_b);
	}
	index_cmp(*stack_a);
	min_on_top(stack_a);
}

void	sort_three(t_stack **a)
{
	t_stack	*biggest;
	
	biggest = find_biggest(*a);
	//ft_printf("the biggest number is: %d\n", biggest->nbr);
	if (biggest == *a)
		ra(a, false);
	else if ((*a)->next == biggest)
		rra(a, false);
	if ((*a)->nbr > (*a)->next->nbr)
		sa(a, false);
}

void	min_on_top(t_stack **stack_a)
{
	while ((*stack_a)->nbr != find_smallest(*stack_a)->nbr)
	{
		if (find_smallest(*stack_a)->above_median)
			ra(stack_a, false);
		else
			rra(stack_a, false);
	}
}
