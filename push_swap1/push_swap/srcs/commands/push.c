# include "../../includes/push_swap.h"

static void	push(t_stack **dst, t_stack **src)
{
	t_stack	*push_node;
	
	if (!*src)
		return ;
	push_node = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->previous = NULL;
	push_node->previous = NULL;
	if (!*dst)
	{
		*dst = push_node;
		push_node->next = NULL;
	}
	else
	{
		push_node->next = *dst;
		push_node->next->previous = push_node;
		*dst = push_node;
	}
}

void	pa(t_stack **stack_a, t_stack **stack_b, bool print)
{
	push(stack_a, stack_b);
	if (!print)
		ft_printf("pa\n");
}

void	pb(t_stack **stack_b, t_stack **stack_a, bool print)
{
	push(stack_b, stack_a);
	if (!print)
		ft_printf("pb\n");
}

void	push_util(t_stack **stack, t_stack *first, char name)
{
	while (*stack != first)
	{
		if (name == 'a')
		{
			if (first->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (name == 'b')
		{
			if (first->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}
	}
}
