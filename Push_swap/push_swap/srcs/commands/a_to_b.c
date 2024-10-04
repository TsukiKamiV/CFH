# include "../../includes/push_swap.h"

void	set_cheapest(t_stack *stack)
{
	long	nbr;
	t_stack	*cheapest_node;
	
	if (!stack)
		return ;
	nbr = LONG_MAX;
	while (stack)
	{
		if (stack->cost < nbr)
		{
			nbr = stack->cost;
			cheapest_node = stack;
		}
		stack = stack->next;
	}
	cheapest_node->cheapest = true;
}

void	find_target_for_a(t_stack *stack_a, t_stack *stack_b)
{
	t_stack		*cur_b;
	t_stack		*target_node;
	long			best_pos;
	
	while (stack_a)
	{
		best_pos = LONG_MIN;
		cur_b = stack_b;
		while (cur_b)
		{
			if (cur_b->nbr < stack_a->nbr && cur_b->nbr > best_pos)
			{
				best_pos = cur_b->nbr;
				target_node = cur_b;
			}
			cur_b = cur_b->next;
		}
		if (best_pos == LONG_MIN)
			stack_a->target = find_biggest(stack_b);
		else
			stack_a->target = target_node;
	}
}

void	init_node_a(t_stack *stack_a, t_stack *stack_b)
{
	index_cmp(stack_a);
	index_cmp(stack_b);
	find_target_for_a(stack_a, stack_b);
	cost_count(stack_a, stack_b);
	set_cheapest(stack_a);
}

void	a_to_b(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*cheapest;
	
	cheapest = get_cheapest(*stack_a);
	if (cheapest->above_median && cheapest->target->above_median)
		rotate_both(stack_a, stack_b, cheapest);
	else if (!(cheapest->above_median) && !(cheapest->target->above_median))
		reverse_rotate_both(stack_a, stack_b, cheapest);
	push_util(stack_a, cheapest, 'a');
	push_util(stack_b, cheapest->target, 'b');
	pb(stack_a, stack_b);
}
