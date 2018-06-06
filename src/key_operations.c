#include "ft_select.h"

void    up_and_down(int code, t_select *list)
{
	int 	temp;
	int 	step;

	if (code == 'u')
	{
		step = -1;
		temp = -1;
	} else
	{
		temp = list->ac;
		step = 1;
	}
	list->cursor += step;
	while (list->selected[list->cursor] == -1 || list->cursor == temp)
	{
		if (list->selected[list->cursor] == -1)
			list->cursor += step;
		if (list->cursor == temp)
			list->cursor = (code == 'u') ? list->ac - 1 : 0;
	}
}

void    left_and_right(int code, t_select *list)
{
	int		step;

	if (code == 'l')
		step = 1;
	else
		step = -1;
	list->cursor += ((ROWS - 1) * -1 * step);
	if ((list->cursor < 0 && code == 'l') ||
			(list->cursor > list->remained - 1 && code == 'r'))
		list->cursor = code == 'r' ? list->ac - 1 : 0;
	if (list->cursor > list->remained - 1)
		list->cursor = list->ac - 1;
	while (list->selected[list->cursor] == -1)
		list->cursor += step;
}

void    del_operation(t_select *list)
{
	list->selected[list->cursor++] = -1;
	if (list->cursor == list->ac)
		list->cursor = 0;
	list->remained--;
	ft_putchar_fd(list->remained + 48, 2);
}

void    spc_operation(t_select *list)
{
	if (list->selected[list->cursor])
		list->selected[list->cursor] = 0;
	else
		list->selected[list->cursor] = 1;
	list->cursor++;
	while (list->selected[list->cursor] == -1 || list->cursor == list->ac)
	{
		if (list->selected[list->cursor] == -1)
			list->cursor++;
		if (list->cursor == list->ac)
			list->cursor = 0;
	}
}

void    enter_operation(t_select *list)
{
	int i;

	i = -1;
	clr_screen();
	while (list->names[++i])
		if (list->selected[i] == 1)
			ft_pmult_fd(1, 2, list->names[i], " ");
	finish_off(-1, NULL);
}