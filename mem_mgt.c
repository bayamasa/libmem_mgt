#include "mem_mgt.h"

/* メモリ情報を格納する構造体の配列 */
t_mem_mgt	g_mem_mgt;

/* メモリ管理配列を初期化する関数 */
void	mem_mgt_init(void)
{
	size_t	i;

	g_mem_mgt.use_byte = 0;
	g_mem_mgt.use_mem_info = 0;
	i = 0;
	while (i < MAX_NUM)
	{
		g_mem_mgt.mem_info[i].ptr = NULL;
		g_mem_mgt.mem_info[i].size = 0;
		g_mem_mgt.mem_info[i].file = NULL;
		g_mem_mgt.mem_info[i].line = 0;
		g_mem_mgt.mem_info[i].func = NULL;
		i++;
	}
}

/* メモリ確保とそのメモリの情報を記録する関数 */
void	*mem_mgt_malloc(size_t size, const char *file, unsigned int line,
		const char *func)
{
	size_t	i;
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < MAX_NUM)
	{
		if (g_mem_mgt.mem_info[i].ptr == NULL)
		{
			g_mem_mgt.use_byte += size;
			g_mem_mgt.mem_info[i].ptr = ptr;
			g_mem_mgt.mem_info[i].size = size;
			g_mem_mgt.mem_info[i].file = file;
			g_mem_mgt.mem_info[i].line = line;
			g_mem_mgt.mem_info[i].func = func;
			g_mem_mgt.use_mem_info++;
			break ;
		}
		i++;
	}
	return (ptr);
}

/* メモリの解放とそのアドレスのメモリ情報を記録から削除する関数 */
void	mem_mgt_free(void *ptr)
{
	size_t	i;

	i = 0;
	while (i < MAX_NUM)
	{
		if (g_mem_mgt.mem_info[i].ptr == ptr)
		{
			g_mem_mgt.use_byte -= g_mem_mgt.mem_info[i].size;
			g_mem_mgt.mem_info[i].ptr = NULL;
			g_mem_mgt.mem_info[i].size = 0;
			g_mem_mgt.mem_info[i].file = NULL;
			g_mem_mgt.mem_info[i].line = 0;
			g_mem_mgt.mem_info[i].func = NULL;
			g_mem_mgt.use_mem_info--;
			break ;
		}
		i++;
	}
	free(ptr);
}

/* 未解放メモリの情報を表示し、全て解放し、プログラムを終了する関数 */
void	mem_mgt_finish_check(int n)
{
	size_t	i;
	bool	first_flag;

	first_flag = true;
	i = 0;
	while (i < MAX_NUM)
	{
		if (g_mem_mgt.mem_info[i].ptr != NULL)
		{
			if (first_flag)
				printf("\x1b[31m--------メモリリークを検出!!!!--------\x1b[39m\n");
			printf(" アドレス : %p\n", g_mem_mgt.mem_info[i].ptr);
			printf(" サイズ   : %zuバイト\n", g_mem_mgt.mem_info[i].size);
			printf(" 場所     : %s:%s関数:%u行目\n", g_mem_mgt.mem_info[i].file, \
			g_mem_mgt.mem_info[i].func, g_mem_mgt.mem_info[i].line);
			printf("\x1b[31m--------------------------------------\x1b[39m\n");
			first_flag = false;
		}
		i++;
	}
	mem_mgt_free_all();
	exit(n);
}

/* 未解放メモリの情報を表示する関数 */
void	mem_mgt_check(const char *file, unsigned int line, const char *func)
{
	size_t	i;
	bool	first_flag;

	first_flag = true;
	i = 0;
	while (i < MAX_NUM)
	{
		if (g_mem_mgt.mem_info[i].ptr != NULL)
		{
			if (first_flag)
				printf("\x1b[33m--%s:%s関数:%u行目のヒープ領域--\x1b[39m\n", \
				file, func, line);
			printf(" アドレス : %p\n", g_mem_mgt.mem_info[i].ptr);
			printf(" サイズ   : %zuバイト\n", g_mem_mgt.mem_info[i].size);
			printf(" 場所     : %s:%s関数:%u行目\n", g_mem_mgt.mem_info[i].file, \
			g_mem_mgt.mem_info[i].func, g_mem_mgt.mem_info[i].line);
			printf("\x1b[33m--------------------------------------\x1b[39m\n");
			first_flag = false;
		}
		i++;
	}
}

/* 未解放メモリを解放する関数 */
void	mem_mgt_free_all()
{
	size_t	i;

	i = 0;
	while (i < MAX_NUM)
	{
		if (g_mem_mgt.mem_info[i].ptr != NULL)
			mem_mgt_free(g_mem_mgt.mem_info[i].ptr);
		i++;
	}
}
