#include"main.h"
#include"task_sub2.h"



//サブタスク2
void* task_sub2(void* global)
{
	Common* g_task = (Common*)global;

	while (1)
	{
		g_task->count += 1000;
		printf("2:%d\n", g_task->count);
		if (g_task->fin >= 1)break;
		sleep(1);
	}
	printf("finish 2\n");
	pthread_exit((void*)0);
}
