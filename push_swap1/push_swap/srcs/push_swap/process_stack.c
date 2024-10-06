#include "../../includes/push_swap.h"

long	ft_atol(char *s)
{
	int	i;
	long	res;
	int	sign;
	
	i = 0;
	sign = 1;
	res = 0;
	while (s[i] && (s[i] == ' ' || (s[i] <= 13 && s[i] >= 9)))
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}

t_stack	*find_last_node(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

void	append_list(t_stack **stack, int nb)
{
	t_stack	*node_tmp;
	t_stack	*node_last;
	
	if (!stack)
		return ;
	node_tmp = malloc(sizeof(t_stack));
	if (!node_tmp)
		return ;
	node_tmp->next = NULL;
	node_tmp->nbr = nb;
	node_tmp->cheapest = 0;
	if (!(*stack))
	{
		*stack = node_tmp;
		node_tmp->previous = NULL;
	}
	else
	{
		node_last = find_last_node(*stack);
		node_last->next = node_tmp;
		node_tmp->previous = node_last;
	}
}

void	ft_print_list(t_stack *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		ft_printf("%d\n", lst->nbr);
		lst = lst->next;
	}
}

void	init_stack_a(t_stack **stack_a, char *argv[])
{
	int	i;
	long	nb;
	
	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			free_errors(stack_a);
		nb = ft_atol(argv[i]);
		if (nb > INT_MAX || nb < INT_MIN)
			free_errors(stack_a);
		if (error_duplicate(*stack_a, (int)nb))
			free_errors(stack_a);
		append_list(stack_a, (int)nb);
		i++;
	}
}
