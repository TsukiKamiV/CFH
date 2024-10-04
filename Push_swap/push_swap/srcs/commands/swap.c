#include "../../includes/push_swap.h"

void	sa(t_stack **stack_a)
{
	int	temp;
	
	if (!stack_a || !(*stack_a) || !(*stack_a)->next)
		return ;
	temp = (*stack_a)->nbr;
	(*stack_a)->nbr = (*stack_a)->next->nbr;
	(*stack_a)->next->nbr = temp;
	ft_printf("sa\n");
}

void	sb(t_stack **stack_b)
{
	int	temp;
	
	if (!stack_b || !(*stack_b) || !(*stack_b)->next)
		return ;
	temp = (*stack_b)->nbr;
	(*stack_b)->nbr = (*stack_b)->next->nbr;
	(*stack_b)->next->nbr = temp;
	ft_printf("sb\n");
}

void	ss(t_stack **stack_a, t_stack **stack_b)
{
	sa(stack_a);
	sb(stack_b);
	ft_printf("ss\n");
}
