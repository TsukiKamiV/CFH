#include "../../includes/push_swap.h"

void	rra(t_stack **stack_a)
{
	t_stack	*last;
	t_stack	*second_last;
	
	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	last = *stack_a;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	if (second_last)
	{
		second_last->next = NULL;
		last->next = *stack_a;
		*stack_a = last;
	}
	ft_printf("rra\n");
}

void	rrb(t_stack **stack_b)
{
	t_stack	*last;
	t_stack	*second_last;
	
	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	last = *stack_b;
	second_last = NULL;
	while (last->next)
	{
		second_last = last;
		last = last->next;
	}
	if (second_last)
	{
		second_last->next = NULL;
		last->next = *stack_b;
		*stack_b = last;
	}
	ft_printf("rrb\n");
}

void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	if (!stack_a || !(*stack_a) || !stack_b || !(*stack_b))
		return ;
	rra(stack_a);
	rrb(stack_b);
	ft_printf("rrr\n");
}

void	reverse_rotate_both(t_stack **stack_a, t_stack **stack_b, t_stack *cheapest)
{
	while (*stack_b != cheapest->target && *stack_a != cheapest)
		rrr(stack_a, stack_b);
	index_cmp(*stack_a);
	index_cmp(*stack_b);
}
