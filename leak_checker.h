/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_checker.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:21:02 by tkirihar          #+#    #+#             */
/*   Updated: 2021/12/23 04:02:39 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAK_CHECKER_H
# define LEAK_CHECKER_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

/* 管理数の上限 */
# define MAX_NUM 30

/* メモリ管理構造体 */
typedef struct s_mem
{
	void			*ptr;
	size_t			size;
	const char		*file;
	unsigned int	line;
	const char		*func;
}	t_mem;

/* 関数のプロトタイプ宣言 */
void	leak_checker_init(void);
void	*leak_checker_malloc(size_t size, const char *file, unsigned int line, const char *func);
void	leak_checker_free(void *ptr);
void	leak_checker_finish_check(int n);
void	leak_checker_check(const char *file, unsigned int line, const char *func);
void	free_all();

#endif
