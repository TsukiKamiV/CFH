#include "../../includes/push_swap.h"

void	sort_stacks(t_stack **stack_a, t_stack **stack_b)
{
	//1. push 2 numbers from stack a to stack b without checking anything
	//sort the two numbers in stack b in descending order???
	//2. from now on every node in stack a needs a target-node in stack b
	//a "target node" is the "closest smaller" number to the stack a node
	//if the current node in stack a can't find a node smaller than itself, then its "target node" is the biggest node in stack b
	//count the "cost" for pushing every node in stack a to stack b, find the "cheapest" node to be pushed in stack a
	int	len_a;
	
	len_a = lst_length(*stack_a);
	if (len_a-- > 3 && is_sorted(*stack_a) == 1)
		pb(stack_a, stack_b);
	if (len_a-- > 3 && is_sorted(*stack_a) == 1)
		pb(stack_a, stack_b);
	while (len_a-- > 3 && is_sorted(*stack_a) == 1)
	{
		init_node_a(*stack_a, *stack_b);
		b_to_a(stack_a, stack_b);
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
		ra(a);
	else if ((*a)->next == biggest)
		rra(a);
	if ((*a)->nbr > (*a)->next->nbr)
		sa(a);
}

void	min_on_top(t_stack **stack_a)
{
	while ((*stack_a)->nbr != find_smallest(*stack_a)->nbr)
	{
		if (find_smallest(*stack_a)->above_median)
			ra(stack_a);
		else
			rra(stack_a);
	}
}
