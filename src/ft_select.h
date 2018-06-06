#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "../libft/libft.h"
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <time.h>
# include <curses.h>
# include "errno.h"


# define ESC 0x1B
# define SPC 0x20
# define FAR_ENTER	0x7F0A
# define ENTER	0xA
# define DEL 0x7E335B1B
# define BKS 0x7F
# define UP 0x415B1B
# define DOWN 0x425B1B
# define RIGHT 0x435B1B
# define LEFT 0x445B1B

# define COLUMNS (tgetnum("co"))
# define ROWS (tgetnum("li"))

# define CD (tgetstr("cd", NULL)) /* Clear screen 											*/
# define CE (tgetstr("ce", NULL)) /* Clear screen 											*/
# define CL (tgetstr("cl", NULL)) /* Clear screen 											*/
# define CH (tgetstr("ch", NULL)) /* курсор на начало 											*/
# define CV (tgetstr("cv", NULL)) /* курсор на начало 											*/
# define CM (tgetstr("cm", NULL)) /* Cursor motion											*/
# define ME (tgetstr("me", NULL)) /* end of all modes										*/
# define SE (tgetstr("se", NULL)) /* end of standard output mode			*/
# define SO (tgetstr("so", NULL)) /* pointer p moves to										*/
# define TE (tgetstr("te", NULL)) /* the end of the program which use move of the cursor	*/
# define TI (tgetstr("ti", NULL)) /* the start of the program which use move of the cursor	*/
# define US (tgetstr("us", NULL)) /* the start of underline									*/
# define UE (tgetstr("ue", NULL)) /* the end of underline									*/
# define VE (tgetstr("ve", NULL)) /* normal view of cursor									*/
# define VI (tgetstr("vi", NULL)) /* make invisible cursor									*/
# define DM (tgetstr("dm", NULL)) /* make invisible cursor									*/
# define ED (tgetstr("ed", NULL)) /* make invisible cursor									*/

# define NORM (tgetstr("me", NULL))


# define MSG1 (ft_putstr_fd("Error occured\n", 2))
# define MSG2 (ft_putstr_fd("Not enough room.\n", 2))
//# define ERROR_EXIT do{MSG1;finish(0);}while(0)

typedef struct		s_select
{
	char			**names;
	int				*selected;
	int				cursor;
	int				ac;
	int				remained;
	int				max_len;
	int				fd;
	struct termios	term;
	struct termios	old_term;
}					t_select;


void    up_and_down(int code, t_select *list);
void    left_and_right(int code, t_select *list);
void    del_operation(t_select *list);
void    spc_operation(t_select *list);
void    enter_operation(t_select *list);
//void		set_termios(int fd, struct termios *term);
//

void		clr_screen(void);
void				goto_xy(int x, int y);
void				normal_mode(t_select *t);
void				stand_end(t_select *t);
void				finish_off(int s, t_select *t);
void				setsigs(t_select *t);
void				print_items(t_select *t);

t_select			*old_settings(int code, t_select **t);

#endif
