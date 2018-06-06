#include "ft_select.h"

//static void	return_selected(t_select *t);

void other_operation(int step, t_select *list)
{
	int i;

	i = 0;
	if (step == 2)
	{
		while (i < list->ac)
			if (list->selected[i])
				list->selected[i++] = 0;
			else
				list->selected[i++] = 1;
		return ;
	}
	while (i < list->ac)
		list->selected[i++] = step;
}

static void	oversight_key(t_select *list)
{
	int 	key_code;

	read(0, &key_code, 4);
	ft_putnbr_fd(key_code, 2);
	if (key_code == ESC)
		finish_off(ESC, NULL);
	else if (key_code == SPC)
		spc_operation(list);
	else if (key_code == UP)
		up_and_down('u', list);
	else if (key_code == DOWN)
		up_and_down('d', list);
	else if (key_code == RIGHT)
		left_and_right('r', list);
	else if (key_code == LEFT)
		left_and_right('l', list);
	else if (key_code == DEL || key_code == BKS)
		del_operation(list);
	else if (key_code == ENTER || key_code == FAR_ENTER)
		enter_operation(list);
	else if (key_code == '1' || key_code == '2' || key_code == '3')
		other_operation((key_code - 49), list);
}



void 		get_default_term(struct termios *term, struct termios *old_term)
{
	ft_strncpy((char *)old_term->c_cc, (const char *)term->c_cc, 20);
	old_term->c_cflag = term->c_cflag;
	old_term->c_ispeed = term->c_ispeed;
	old_term->c_lflag = term->c_lflag;
	old_term->c_oflag = term->c_oflag;
	old_term->c_ospeed = term->c_ospeed;
}

static void		set_termios(int fd, t_select *list)
{
	tcgetattr(fd, &(list->term));		// get default term
	get_default_term(&(list->term), &(list->old_term));
	list->term.c_cc[VMIN] = 1;		// Minimum number of characters for noncanonical read (MIN).
	list->term.c_cc[VTIME] = 0;		// Timeout in deciseconds for noncanonical read (TIME).
	list->term.c_cflag &= ~(CSIZE | PARENB);
	list->term.c_cflag |= CS8; /* отменить преобразование кода '\r' в '\n' на вводе              */
	list->term.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN); // for reaction terminal on our moves
	list->term.c_oflag &= ~ OPOST;
	tcsetattr(fd, TCSANOW, &(list->term)); // set new options
}

static void	initial(t_select *list, int ac)
{
	char 	*temp_term;
	int 	temp_len;

	if (!(temp_term = getenv("TERM")) || tgetent(NULL, temp_term) < 0)
		exit((int)write(2, "Error with getting env\n", 7) * 0);
	if ((list->fd = open(ttyname(0), O_RDWR | O_NDELAY)) < 0)
		exit((int)write(2, "Error with opening\n", 7) * 0);
	set_termios(list->fd, list);
	ft_setnum((void **)(&(list->selected)), ac, 0);
	ac = 0;
	while (list->names[ac])
		if ((temp_len = (int)ft_strlen(list->names[ac++])) > list->max_len)
			list->max_len = temp_len;
	ft_putstr_fd(VI, 0); // switch off cursor
}

int			main(int ac, char **av, char **env)
{
	t_select *list;

	if (!env || !*env || !isatty(0))
		exit((int)write(2, "Wrong shell for this program.\n", 30) * 0 + 1);
	if (ac-- < 2)
		exit ((int)write(2, "usage: ft_select [file ...]\n", 28) * 0 + 1);
	list = (t_select *)malloc(sizeof(t_select));
	*list = (t_select){++av, (int *)malloc(sizeof(ac)), 0, ac, ac, 0, -1, {0, 0, 0, 0, {0}, 0, 0}, {0, 0, 0, 0, {0}, 0, 0}};
	initial(list, ac);
	goto_xy(0, 0);
	while (ac)
	{
		setsigs(list);
		print_items(list);
		oversight_key(list); // make it int
		if (!list->remained)
			finish_off(0, list);
	}
}