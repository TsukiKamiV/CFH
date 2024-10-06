#include "../../includes/push_swap.h"

int	main(int argc, char *argv[])
{
	t_stack	*a;
	t_stack	*b;
	
	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
	{
		ft_printf("Error\n");
		return (1);
	}
	else if (argc == 2)
		argv = split_arg(argv[1], ' ');
	init_stack_a(&a, argv + 1);
	//ft_printf("stack a:\n");
	//ft_print_list(a);
	if (!is_sorted(a))
	{
		if (lst_length(a) == 2)
			sa(&a, false);
		else if (lst_length(a) == 3)
			sort_three(&a);
		else if (lst_length(a) > 3)
			sort_stacks(&a, &b);
		ft_print_list(a);
	}
	return 0;
}

