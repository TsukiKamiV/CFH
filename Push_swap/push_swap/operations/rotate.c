#include "../includes/push_swap.h"

void	ra(t_stack **stack_a)
{
	t_stack	*first;
	t_stack	*last;
	
	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	first = *stack_a;
	*stack_a = (*stack_a)->next;
	first->next = NULL;
	last = *stack_a;
	while (last->next)
		last = last->next;
	last->next = first;
	ft_printf("ra\n");
}

void	rb(t_stack **stack_b)
{
	t_stack	*first;
	t_stack	*last;
	
	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	first = *stack_b;
	*stack_b = (*stack_b)->next;
	first->next = NULL;
	last = *stack_b;
	while (last->next)
		last = last->next;
	last->next = first;
	ft_printf("rb\n");
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	ra(stack_a);
	rb(stack_b);
	ft_printf("rr\n");
}
