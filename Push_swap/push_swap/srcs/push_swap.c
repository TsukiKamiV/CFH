#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_stack	*a;
	t_stack	*b;
	
	a = NULL;
	b = NULL;/*
	if (argc == 1 || (argc == 2 && argv[1][0] == '\0'))
		return (1);
	else if (argc == 2)
		argv = ft_split(argv[1], ' ');*/
	if (argc < 2)
		return (1);
	//ft_printf("%s\n", argv[1]);
	init_stack_a(&a, argv + 1);
	ft_printf("stack a:\n");
	ft_print_list(a);
	/*
	if (is_sorted(a) == 0)
		ft_printf("List already sorted\n");
	else if (is_sorted(a) == 1)
		ft_printf("List not sorted\n");*/
	if (is_sorted(a) != 0)
	{
		//ft_printf("the list has %d elements.\n", lst_length(a));
		if (lst_length(a) == 2)
			sa(a);
		else if (lst_length(a) == 3)
			sort_three(&a);
		printf("\n");
		ft_print_list(a);
	}
	
	return 0;
}
