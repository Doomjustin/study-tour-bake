#include <cstdlib>

#include <fmt/core.h>

#include "ST/Net/Socket.h"


int main(int argc, char* argv[])
{
  if (argc != 2) {
    fmt::print("usage: daytime-tcp-client <IP address>\n");
    return EXIT_FAILURE;
  }

  ST::Net::Socket socket{ ST::Net::Family::IPv4, ST::Net::Type::TCP };

  socket.connect(argv[1], 13);

  char receive_line[ST::MAX_LINE + 1];
  auto n = socket.read(receive_line, ST::MAX_LINE);

  while (n > 0) {
    receive_line[n] = 0;
    fmt::print("{}\n", receive_line);
    n = socket.read(receive_line, ST::MAX_LINE);
  }

  return EXIT_SUCCESS;
}