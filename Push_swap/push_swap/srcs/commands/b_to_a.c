# include "../../includes/push_swap.h"

void	find_target_for_b(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*cur_a;
	t_stack	*target_node;
	long	target_index;
	
	while (stack_b)
	{
		target_index = LONG_MAX;
		cur_a = stack_a;
		while (cur_a)
		{
			if (cur_a->nbr > stack_b->nbr && cur_a->nbr < target_index)
			{
				target_index = cur_a->nbr;
				target_node = cur_a;
			}
			cur_a = cur_a->next;
		}
		if (target_index == LONG_MAX)
			stack_b->target = find_smallest(stack_a);
		else
			stack_b->target = target_node;
		stack_b = stack_b->next;
	}
}

void	init_node_b(t_stack *stack_a, t_stack *stack_b)
{
	index_cmp(stack_a);
	index_cmp(stack_b);
	find_target_for_b(stack_a, stack_b);
}

void	b_to_a(t_stack **stack_a, t_stack **stack_b)
{
	push_util(stack_a, (*stack_b)->target, 'a');
	pa(stack_a, stack_b);
}
