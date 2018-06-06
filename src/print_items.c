#include "ft_select.h"

void		print_items(t_select *list)
{
	int counter;
	int y;
	int x;

	clr_screen();
	if ((COLUMNS / (list->max_len + 1) * (ROWS - 2) <= list->remained))
		return ((void)write(2, "Bad size\n", 9));
	x = 0;
	y = 0;
	counter = 0;
	while (list->names[counter])
	{
		if (list->selected[counter] == -1 && ++counter)
			continue ;
		goto_xy(x, y);
		if (list->selected[counter])
			ft_putstr_fd(SO, 0);
		if (counter == list->cursor)
			ft_putstr_fd(US, 0);
		ft_pmult_fd(0, 2, list->names[counter], "\n");
		normal_mode(list);
		if (list->selected[counter++])
			ft_putstr_fd(SE, 0);
		if (y == ROWS - 2)
			(x += list->max_len + 1);
		y = (y == ROWS - 2) ? 0 : (y + 1);

	}
}

void		clr_screen(void)
{
	int i;
	int rows;

	i = 0;
	rows = ROWS;
	while (i < rows)
	{
		write(2, tgoto(tgetstr("cm", NULL), 0, i), ft_strlen(tgoto(tgetstr("cm", NULL), 0, i)));
		write(2, tgetstr("ce", NULL), ft_strlen(tgetstr("ce", NULL)));
		i++;
	}

	write(2, tgoto(tgetstr("cm", NULL), 0, 0), ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
//	ft_putstr_fd(CL, 0);
}