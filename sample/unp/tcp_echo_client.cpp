#include <string.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

#include "ST/Exercise.h"
#include "ST/Net/Socket.h"


void str_cli(FILE* fp, int socket_fd);

int main(int argc, char* argv[])
{
  if (argc != 2)
    err_quit("usage: tcp-echo-client <IP address>");

  ST::Net::Socket client_socket {};
  client_socket.connect(argv[1], ServerPort);

  std::cout << "echo client:" << std::endl;
  str_cli(stdin, client_socket.fd());

  return EXIT_SUCCESS;
}

void str_cli(FILE* fp, int socket_fd)
{
  char receive_line[ST::MAX_LINE];
  char send_line[ST::MAX_LINE];
  while (fgets(send_line, ST::MAX_LINE, fp) != nullptr) {
    writen(socket_fd, send_line, strlen(send_line));

    if (read_line(socket_fd, receive_line, ST::MAX_LINE) == 0)
      err_quit("str_cli: server terminated prematurely");

    fputs(receive_line, stdout);
  }
}