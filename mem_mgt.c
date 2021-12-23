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
void	*mem_mgt_malloc(size_t size, const char *file, unsigned int line, const char *func)
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
			g_mem_mgt.mem_info[i].ptr = ptr;
			g_mem_mgt.mem_info[i].size = size;
			g_mem_mgt.mem_info[i].file = file;
			g_mem_mgt.mem_info[i].line = line;
			g_mem_mgt.mem_info[i].func = func;
			break ;
		}
		i++;
	}
	return (ptr);
}

/* メモリの確保とそのアドレスのメモリ情報を記録から削除する関数 */
void	mem_mgt_free(void *ptr)
{
	size_t	i;

	i = 0;
	while (i < MAX_NUM)
	{
		if (g_mem_mgt.mem_info[i].ptr == ptr)
		{
			g_mem_mgt.mem_info[i].ptr = NULL;
			g_mem_mgt.mem_info[i].size = 0;
			g_mem_mgt.mem_info[i].file = NULL;
			g_mem_mgt.mem_info[i].line = 0;
			g_mem_mgt.mem_info[i].func = NULL;
			break ;
		}
		i++;
	}
	free(ptr);
}

/* 解放が行われていないメモリの情報を表示し、プログラムを終了する関数 */
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
			printf(" 場所     : %s:%u行目:%s関数\n", g_mem_mgt.mem_info[i].file, g_mem_mgt.mem_info[i].line, g_mem_mgt.mem_info[i].func);
			printf("\x1b[31m--------------------------------------\x1b[39m\n");
			first_flag = false;
		}
		i++;
	}
	mem_mgt_free_all();
	exit(n);
}

/* 開放が行われていないメモリの情報を表示する関数 */
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
				printf("\x1b[33m--%s:%u行目:%s関数のヒープ領域--\x1b[39m\n", file, line, func);
			printf(" アドレス : %p\n", g_mem_mgt.mem_info[i].ptr);
			printf(" サイズ   : %zuバイト\n", g_mem_mgt.mem_info[i].size);
			printf(" 場所     : %s:%u行目:%s関数\n", g_mem_mgt.mem_info[i].file, g_mem_mgt.mem_info[i].line, g_mem_mgt.mem_info[i].func);
			printf("\x1b[33m--------------------------------------\x1b[39m\n");
			first_flag = false;
		}
		i++;
	}
}

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
