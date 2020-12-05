#include "ft_ls.h"

void				print_columns(t_node ***columns, size_t width)
{
	unsigned short	i;
	unsigned short	j;
	t_node			**curr_row;
	t_node			*curr_cell;

	i = 0;
	curr_row = columns[0];
	while (curr_row)
	{
		j = 0;
		curr_cell = curr_row[0];
		while (curr_cell)
		{
			ft_printf("%-*s ", width, curr_cell->name);
			curr_cell = curr_row[++j];
		}
		ft_printf("\n");
		curr_row = columns[++i];
	}
}

void 				fill_columns(t_node ***columns, t_node *curr,
					  unsigned short cols, unsigned rows)
{
	unsigned short	i;
	unsigned short	j;

	j = 0;
	while (j < cols)
	{
		i = 0;
		while (i < rows && curr)
		{
			columns[i++][j] = curr;
			curr = curr->next;
		}
		j++;
	}
}

t_node				***create_columns(unsigned short num_of_columns,
						   unsigned short num_of_rows)
{
	unsigned short	i;
	t_node			***columns;

	i = 0;
	MEM_CHECK((columns = (t_node ***)ft_memalloc(sizeof(t_node **) *
			(num_of_rows + 1))));
	while (i < num_of_rows)
		MEM_CHECK((columns[i++] = (t_node **)ft_memalloc(sizeof(t_node *) *
				(num_of_columns + 1))));
	return (columns);
}

void				print_by_column(t_node *parent)
{
	t_node			***columns;
	struct winsize	w;
	unsigned short	num_of_columns;
	unsigned short	num_of_rows;

	(void) parent;
	ioctl(0, TIOCGWINSZ, &w);
	num_of_columns = w.ws_col / (parent->format.name_len + 1);
	num_of_rows = parent->format.num_of_files / num_of_columns +
				  ((parent->format.num_of_files % num_of_columns == 0) ? 0 : 1);
	columns = create_columns(num_of_columns, num_of_rows);
	fill_columns(columns, parent->content, num_of_columns, num_of_rows);
	print_columns(columns, parent->format.name_len);
}

