#include"main.h"
#include"task_sub1.h"



//サブタスク1
void* task_sub1(void* global)
{
	Common* g_task = (Common*)global;

	while (1)
	{
		g_task->count += 1;
		printf("1:%d\n", g_task->count);
		if (g_task->fin >= 1)break;
		sleep(1);
	}
	printf("finish 1\n");
	pthread_exit((void*)0);
}
