# include "../../includes/push_swap.h"

void	pb(t_stack **stack_a, t_stack **stack_b)
{
	int	temp;
	t_stack	*stack_tmp;
	
	if (!stack_a || !(*stack_a))
		return ;
	//printf("the first nb of stack a: %d\n", (*stack_a)->nbr);
	temp = (*stack_a)->nbr;
	stack_tmp = (*stack_a);
	(*stack_a) = (*stack_a)->next;
	free (stack_tmp);
	stack_tmp = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_tmp)
		return ;
	stack_tmp->nbr = temp;
	stack_tmp->next = *stack_b;
	*stack_b = stack_tmp;
	ft_printf("pa\n");
}

void	pa(t_stack **stack_a, t_stack **stack_b)
{
	int	temp;
	t_stack	*stack_tmp;
	
	if (!stack_b || !(*stack_b))
		return ;
	//printf("the first nb of stack a: %d\n", (*stack_a)->nbr);
	temp = (*stack_b)->nbr;
	stack_tmp = (*stack_b);
	(*stack_b) = (*stack_b)->next;
	free (stack_tmp);
	stack_tmp = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_tmp)
		return ;
	stack_tmp->nbr = temp;
	stack_tmp->next = *stack_a;
	*stack_a = stack_tmp;
	ft_printf("pb\n");
}

void	push_util(t_stack **stack, t_stack *first, char name)
{
	while (*stack != first)
	{
		if (name == 'a')
		{
			if (first->above_median)
				ra(stack);
			else
				rra(stack);
		}
		else if (name == 'b')
		{
			if (first->above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}
