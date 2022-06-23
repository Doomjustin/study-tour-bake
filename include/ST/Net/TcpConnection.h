#ifndef STUDY_TOUR_NET_TCP_CONNECTION_H
#define STUDY_TOUR_NET_TCP_CONNECTION_H

#include <unistd.h>

#include <optional>

#include "Socket.h"


namespace ST::Net {

class TcpConnection {
public:

  TcpConnection(const TcpConnection& other);
  TcpConnection& operator=(const TcpConnection& other);

  TcpConnection(TcpConnection&& other) noexcept;
  TcpConnection& operator=(TcpConnection&& other) noexcept;

  ~TcpConnection() { close(connected_fd_); }

  void shutdown();

  std::optional<ssize_t> send();

  std::optional<ssize_t> receive();

private:
  int connected_fd_;

  explicit TcpConnection(int connected_fd);
};

} // namespace ST::Net

#endif // STUDY_TOUR_NET_NECTION_H