#include"main.h"
#include"task_con.h"

//TCP con task
void* task_con(void* global)
{
  Common* g_task = (Common*)global;
  int sock = -1, i = 0;
  while (1)
  {
    i++;
    // connction check
    if (sock == -1)
    {
      sock = establishConnection();
      printf("Failed to establish connection.\n");
      continue;
    }
    // Send a message to the server
    char message[MAX_SIZE];
    sprintf(message, "%d\n", i);
    int messageSize = strlen(message);
    if (send(sock, message, messageSize, 0) != messageSize)
    {
      sock = -1;
      printf("Failed to send the message.\n");
      close(sock);
      continue;
    }

    // Receive a response from the server
    char buffer[MAX_SIZE];
    int bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead < 0)
    {
      printf("Failed to receive data.\n");
      close(sock);
      continue;
    }
    buffer[bytesRead] = '\0';
    printf("Received response from server: %s",buffer);

    // Fin  
    if (g_task->fin >= 1)
    {
      close(sock);
      break;
    }
    sleep(0.1);
  }
  pthread_exit((void*)0);
}


int establishConnection() {

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    printf("Failed to create socket.\n");
    return -1;
  }

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(SERVER_PORT);

  if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0)
  {
    printf("Invalid address or address not supported.\n");
    return -1;
  }


  struct timeval timeout;
  timeout.tv_sec = TIMEOUT_SECONDS;
  timeout.tv_usec = 0;

  if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&timeout), sizeof(timeout)) < 0)
  {
    printf("Failed to set receive timeout.\n");
  }
  if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)(&timeout), sizeof(timeout)) < 0)
  {
    printf("Failed to set send timeout.\n");
  }

  int connectResult = connect(sock, (struct sockaddr*)(&serverAddress), sizeof(serverAddress));
  if (connectResult < 0)
  {
    printf("Failed to connect to the server.\n");
    close(sock);
    return -1;
  }
  else
  {
    printf("Success.\n");
  }
  return sock;

}

