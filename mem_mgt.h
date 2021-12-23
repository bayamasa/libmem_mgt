#ifndef MEM_MGT_H
# define MEM_MGT_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

/* 管理数の上限 */
# define MAX_NUM 30

/* メモリ管理構造体 */
typedef struct s_mem_mgt
{
	void			*ptr;
	size_t			size;
	const char		*file;
	unsigned int	line;
	const char		*func;
}	t_mem_mgt;

/* 関数のプロトタイプ宣言 */
void	mem_mgt_init(void);
void	*mem_mgt_malloc(size_t size, const char *file, unsigned int line, const char *func);
void	mem_mgt_free(void *ptr);
void	mem_mgt_finish_check(int n);
void	mem_mgt_check(const char *file, unsigned int line, const char *func);
void	mem_mgt_free_all();

#endif
