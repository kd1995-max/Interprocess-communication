#include "/home/krishanudev/rahulSir/files/headers/headers.h"

/*
*   Function description
*   This function is responsible to run the client
*   will monitor the change.txt then sends to Application A i.e server
*/
void A(){
  char *serMsg;
  read_the_changes(&serMsg);
  char *ip = "127.0.0.1";
  int port = 5566;

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;

  int n;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("sending new status\n");
  
  
  send(sock, serMsg, strlen(serMsg), 0);


  close(sock);
}
