#include "ft_select.h"

void 		get_default_term(struct termios *term, struct termios *old_term);

void	finish_off(int s, t_select *list_old)
{
	t_select *list;

	list = NULL;
	list = old_settings(0, &list);
	normal_mode(list);
	(void)list_old;
	get_default_term(&list->old_term, &list->term);
	list->term.c_lflag |= (ICANON | ECHO);
	list->term.c_oflag |= OPOST;
	tcsetattr(list->fd, TCSANOW, &list->term);
	if (s != -1)
		clr_screen();
	ft_putstr_fd(VE, 0);
	if ((list && list->remained) && s != ESC) // added  "&& s != ESC" 06/06/14:12
		write(0, "\n", 1);
	ft_putstr_fd(ME, 0);	// added 06/06/14:12
	close(list->fd);
	free(list->selected);
	free(list);
	exit(s);
}
