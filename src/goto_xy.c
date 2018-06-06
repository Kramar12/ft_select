#include "ft_select.h"

void	goto_xy(int x, int y)
{
	if (x < 0 || y < 0 || x > COLUMNS - 1 || y > ROWS - 1)
		finish_off((int)write(0, "Off-screen point\n", 17), NULL); // there has to be message "off-screen point"
	ft_putstr_fd(tgoto(CM, x, y), 0);
}

void	normal_mode(t_select *list)
{
	if (NORM)
		ft_putstr_fd(NORM, 0);
	else
	{
		if (SE)
			ft_putstr_fd(SE, 0);
		else
			normal_mode(list);
	}
}

t_select	*old_settings(int code, t_select **t)
{
	static t_select *tmp;

	if (!code)
		return (tmp);
	tmp = *t;
	return (*t);
}
