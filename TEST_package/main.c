// TEST_package.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "main.h"
#include "task_sub.h"


//タスク系初期化
#define TASK_NUM 2
pthread_t task[TASK_NUM];
int task_result[TASK_NUM];


//メイン
int main() {

  Common global;
  pthread_mutex_init(&global.mutex, NULL);
  init(&global);

  /////////////////////////////////////
  // 	   TASK MAKE

  //sub1
  if ((task_result[0] = pthread_create(&task[0], NULL, &task_sub1, &global)) != 0)
  {
    fprintf(stderr, "pthread_create(): ret = %d\n", task_result[0]);
    exit(1);
  }
  //sub2
  if ((task_result[1] = pthread_create(&task[1], NULL, &task_sub2, &global)) != 0)
  {
    fprintf(stderr, "pthread_create(): ret = %d\n", task_result[1]);
    exit(1);
  }


  /////////////////////////////////////

  /////////////////////////////////////
  // 	   TASK FIN

  int i = 0;
  for (i = 0; i < TASK_NUM; i++)
  {
    if ((task_result[i] = pthread_join(task[i], NULL)) != 0)
    {
      fprintf(stderr, "pthread_join(): ret = %d\n", task_result[i]);
      exit(2);
    }
    printf("TASK JOIN : %d\n", i);
  }
  /////////////////////////////////////

  while (1)
  {
    if (global.fin >= 1)break;
    sleep(0.5);
  }

  printf("fin main\n");
  pthread_cancel(task[0]);
  pthread_cancel(task[1]);

  pthread_mutex_destroy(&global.mutex);

  return 0;
}




void init(Common* global)
{
  global->init = 0;
  global->count = 0;
  global->fin = 0;
}
