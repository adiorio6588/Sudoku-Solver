/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiorio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 15:02:51 by zli               #+#    #+#             */
/*   Updated: 2018/07/03 21:25:46 by adiorio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sudoku.h"

void	fill_board(char *argv[], char **board, int r, int c)
{
	int		i;
	int		i_c;

	i = 1;
	while (i < r + 1)
	{
		i_c = 0;
		while (i_c < c)
		{
			if (argv[i][i_c] != '.')
				board[i - 1][i_c] = argv[i][i_c];
			else
				board[i - 1][i_c] = ' ';
			i_c++;
		}
		i++;
	}
}

char	**create_board(char *argv[], int r, int c)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc(r * sizeof(char *));
	while (i < r)
	{
		arr[i] = (char *)malloc(c * sizeof(char));
		i++;
	}
	fill_board(argv, arr, r, c);
	return (arr);
}

void	print_board(char **board, int row, int col)
{
	int r;
	int c;

	r = 0;
	while (r < row)
	{
		c = 0;
		while (c < col)
		{
			write(1, &board[r][c], 1);
			if (c != col - 1)
				write(1, " ", 1);
			c++;
		}
		write(1, "\n", 1);
		r++;
	}
}

int		solve_sudoku(char **board)
{
	int row;
	int col;
	int num;

	if (!find_unassigned_location(board, &row, &col, 9))
		return (1);
	num = 1;
	while (num <= 9)
	{
		if (is_ok(board, row, col, (num + '0')))
		{
			board[row][col] = (num + '0');
			if (solve_sudoku(board) == 1)
				return (1);
			board[row][col] = ' ';
		}
		num++;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	char	**board;
	int		i;

	if (argc != 10)
		write(1, "Error\n", 6);
	else
	{
		board = create_board(argv, 9, 9);
		if (solve_sudoku(board) == 1)
		{
			print_board(board, 9, 9);
			i = 0;
			while (i < 9)
			{
				free(board[i]);
				i++;
			}
			free(board);
		}
		else
			write(1, "Error\n", 6);
	}
	return (0);
}
