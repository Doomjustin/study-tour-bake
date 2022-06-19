#include <cstdlib>
#include <vector>

#include "ST/Net/Socket.h"
#include "ST/Exercise.h"
#include "ST/Process.h"


void str_echo(int socket_fd);
static constexpr const char* ServerAddress = "test-server";


int main()
{
  ST::Net::Socket server_socket{};
  server_socket.bind(ServerAddress, ServerPort);
  server_socket.listen();
  // std::vector<ST::Process> processes{};

  int child_pid;

  ST::Process::auto_remove();
  while (true) {
    // 结束时自动close相应的fd，所以不需要像书中一样处理
    auto connect_socket = server_socket.accept();
    ST::Process child_process { str_echo, connect_socket.fd() };
  }

  return EXIT_SUCCESS;
}

// 和书中例子相同
void str_echo(int socket_fd)
{
  ssize_t n;
  char buffer[ST::MAX_LINE];

again:
  while ((n = read(socket_fd, buffer, ST::MAX_LINE)) > 0)
    writen(socket_fd, buffer, n);

  if (n < 0 && errno == EINTR)
    goto again;
  else if (n < 0)
    err_sys("str_echo: read error");
}
