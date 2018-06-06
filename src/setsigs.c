#include "ft_select.h"

void 	pre_finish(int s)
{
	finish_off(s, NULL);
}
static void	suspend(int s)
{
	struct termios	t_attr;
	char			susp[2];

	(void)s;
	if (tcgetattr(0, &t_attr) == -1)
		finish_off((int)write(1, "Error with getting attr\n", 24), NULL);
	susp[0] = t_attr.c_cc[VSUSP];
	susp[1] = 0;
	t_attr.c_lflag |= ICANON;
	t_attr.c_lflag |= ECHO;
	t_attr.c_oflag |= OPOST;
	if (tcsetattr(0, TCSADRAIN, &t_attr) == -1)
		finish_off((int)write(1, "Error with setting attr\n", 24), NULL);
	ft_putstr_fd(VE, 2);
	ft_putstr_fd(TE, 2);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, susp);
}

static void	restart(int s)
{
	t_select	*t;
	char		buf[2];

	(void)s;
	t = NULL;
	t = old_settings(0, &t);
	tcgetattr(t->fd, &t->term);
	t->term.c_lflag &= ~(ICANON | ECHO);
	t->term.c_oflag &= ~(OPOST);
	t->term.c_cc[VMIN] = 1;
	t->term.c_cc[VTIME] = 0;
	tcsetattr(t->fd, TCSANOW, &t->term);
	if (tgetent(NULL, getenv("TERM")) <= 0)
		finish_off((int)write(1, "Error with setting attr\n", 24), NULL);
	setsigs(t);
	ft_putstr_fd(VI, 0);
	ft_putstr_fd(TI, 0);
	buf[0] = -62;
	buf[1] = 0;
	ioctl(0, TIOCSTI, buf);
}

static void	size_changed(int s)
{
	t_select *t;

	(void)s;
	t = NULL;
	t = old_settings(0, &t);
	if (tgetent(NULL, getenv("TERM")) <= 0)
		finish_off((int)write(1, "Error with getting env\n", 23), NULL);
	print_items(t);
}

void		setsigs(t_select *t)
{
	t = old_settings(1, &t);
	signal(SIGWINCH, size_changed);
	signal(SIGTSTP, suspend);
	signal(SIGCONT, restart);
	signal(SIGILL, pre_finish);
	signal(SIGPIPE, pre_finish);
	signal(SIGFPE, pre_finish);
	signal(SIGSYS, pre_finish);
	signal(SIGEMT, pre_finish);
	signal(SIGTRAP, pre_finish);
	signal(SIGHUP, pre_finish);
	signal(SIGINT, pre_finish);
	signal(SIGQUIT, pre_finish);
	signal(SIGABRT, pre_finish);
	signal(SIGKILL, pre_finish);
	signal(SIGBUS, pre_finish);
	signal(SIGSEGV, pre_finish);
	signal(SIGALRM, pre_finish);
	signal(SIGTERM, pre_finish);
	signal(SIGUSR1, pre_finish);
	signal(SIGUSR2, pre_finish);
}

