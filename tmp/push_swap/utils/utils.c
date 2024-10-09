#include "../includes/push_swap.h"

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(1);
}

void	ft_free(char **str)
{
	int	i;
	
	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

int	is_sorted(t_list **stack)
{
	t_list	*head;
	
	head = *stack;
	while (head && head->next)
	{
		if (head->value > head->next->value)
			return (0);
		head = head->next;
	}
	return (1);
}

int	get_distance(t_list **stack, int index)
{
	t_list	*head;
	int		distance;
	
	distance = 0;
	head = *stack;
	while (head)
	{
		if (head->index == index)
			break ;
		distance++;
		head = head->next;
	}
	return (distance);
}

void	free_stack(t_list **stack)
{
	t_list	*head;
	t_list	*tmp;
	
	head = *stack;
	while (head)
	{
		tmp = head;
		head = head->next;
		free (tmp);
	}
	free (stack);
}
