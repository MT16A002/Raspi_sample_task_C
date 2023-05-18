#define TASK_CON
#ifdef TASK_CON

void* task_con(void* global);
int establishConnection();

const char* SERVER_IP = "192.168.2.10";
const int SERVER_PORT = 6341;
const int TIMEOUT_SECONDS = 5;
const int MAX_SIZE = 8192;

#endif