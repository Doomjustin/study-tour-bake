#include <time.h>
#include <string.h>
#include <stdio.h>

#include <cstdlib>

#include <fmt/core.h>

#include "ST/Net/Socket.h"


int main(int argc, char* argv[])
{
  ST::Net::Socket socket{};

  socket.bind(13);
  socket.listen();

  time_t ticks;
  char buffer[ST::MAX_LINE];
  while (true) {
    auto conneting_socket = socket.accept();

    ticks = time(nullptr);
    snprintf(buffer, ST::MAX_LINE, "%.24s\r\n", ctime(&ticks));
    conneting_socket.write(buffer, ST::MAX_LINE);
  }

  return EXIT_SUCCESS;
}