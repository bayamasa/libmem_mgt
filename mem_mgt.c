#include "mem_mgt.h"

/* メモリ情報を格納する構造体の配列 */
t_mem_mgt	g_mem_mgt;

/* メモリ確保とそのメモリの情報を記録する関数 */
void	*mem_mgt_malloc(size_t size, const char *file, unsigned int line,
		const char *func)
{
	t_mem_info	*new;
	t_mem_info	*current;
	t_mem_info	*prev;

	if (g_mem_mgt.use_cnt + 1 > MAX_NUM)
	{
		printf("The maximum number of controls has been exceeded.\n");
		mem_mgt_free_all();
		exit(1);
	}
	if (g_mem_mgt.use_byte + size > MAX_SIZE)
	{
		printf("The maximum size that can be allocated by malloc has been exceeded.\n");
		mem_mgt_free_all();
		exit(1);
	}
	new = (t_mem_info *)malloc(sizeof(t_mem_info));
	if (new == NULL)
		return (NULL);
	new->ptr = malloc(size);
	if (new->ptr == NULL)
	{
		free(new);
		return (NULL);
	}
	g_mem_mgt.use_byte += size;
	g_mem_mgt.use_cnt++;
	new->mem_mgt_ptr = (void *)new;
	new->size = size;
	new->file = file;
	new->line = line;
	new->func = func;
	new->next = NULL;
	if (g_mem_mgt.head == NULL)
	{
		g_mem_mgt.head = new;
		return (new->ptr);
	}
	current = g_mem_mgt.head;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new;
	current = new;
	return (new->ptr);
}

/* メモリの解放とそのアドレスのメモリ情報を記録から削除する関数 */
void	mem_mgt_free(void *ptr)
{
	t_mem_info	*prev;
	t_mem_info	*current;

	if (g_mem_mgt.head == NULL)
	{
		free(ptr);
		return ;
	}
	current = g_mem_mgt.head;
	if (current->ptr == ptr)
	{
		g_mem_mgt.head = current->next;
		g_mem_mgt.use_byte -= current->size;
		g_mem_mgt.use_cnt--;
		free(current->mem_mgt_ptr);
		free(ptr);
		return ;
	}
	while (current != NULL)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			g_mem_mgt.use_byte -= current->size;
			g_mem_mgt.use_cnt--;
			current->ptr = NULL;
			current->size = 0;
			current->file = NULL;
			current->line = 0;
			current->func = NULL;
			free(current->mem_mgt_ptr);
			current->mem_mgt_ptr = NULL;
			break ;
		}
		prev = current;
		current = current->next;
	}
	free(ptr);
}

/* 未解放メモリの情報を表示し、全て解放し、プログラムを終了する関数 */
void	mem_mgt_finish_check(int n)
{
	t_mem_info	*current;

	if (g_mem_mgt.use_cnt == 0)
		exit(0);
	printf("\x1b[31m--------Detect memory leaks!!!!--------\x1b[39m\n");
	printf(" number     : %zu\n", g_mem_mgt.use_cnt);
	printf(" total size : %zubyte\n", g_mem_mgt.use_byte);
	printf("\x1b[31m---------------------------------------\x1b[39m\n");
	current = g_mem_mgt.head;
	while (current != NULL)
	{
		printf(" address : %p\n", current->ptr);
		printf(" size    : %zubyte\n", current->size);
		printf(" place   : %s:func %s:line %u\n", current->file, \
				current->func, current->line);
		printf("\x1b[31m---------------------------------------\x1b[39m\n");
		current = current->next;
	}
	mem_mgt_free_all();
	exit(n);
}

/* 未解放メモリの情報を表示する関数 */
void	mem_mgt_check(const char *file, unsigned int line, const char *func)
{
	t_mem_info	*current;

	printf("\x1b[33m--------------leeks check--------------\x1b[39m\n");
	printf(" check place : %s:func %s:line %u\n", file, func, line);
	printf(" number      : %zu\n", g_mem_mgt.use_cnt);
	printf(" total size  : %zubyte\n", g_mem_mgt.use_byte);
	printf("\x1b[33m---------------------------------------\x1b[39m\n");
	current = g_mem_mgt.head;
	while (current != NULL)
	{
		printf(" address : %p\n", current->ptr);
		printf(" size    : %zubyte\n", current->size);
		printf(" place   : %s:func %s:line %u\n", current->file, \
				current->func, current->line);
		printf("\x1b[33m---------------------------------------\x1b[39m\n");
		current = current->next;
	}
}

/* 未解放メモリを解放する関数 */
void	mem_mgt_free_all()
{
	t_mem_info	*current;

	current = g_mem_mgt.head;
	while (current != NULL)
	{
		if (current->ptr != NULL)
			mem_mgt_free(current->ptr);
		current = current->next;
	}
}
