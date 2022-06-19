#ifndef STUDY_TOUR_NET_SOCKET_H
#define STUDY_TOUR_NET_SOCKET_H

#include <cstdint>
#include <cstddef>
#include <memory>
#include <string>

#include "Address.h"


namespace ST::Net {

constexpr static int DEFAULT_BACK_LOG = 5;

/**
 * @brief 提供所有和socket相关的操作，不应该由用户调用
 *
 */
class Socket {
public:
  // 打开socket连接
  Socket(Family family = Family::IPv4,
         Type type = Type::TCP,
         Protocol protocol = Protocol::Undefined);

  Socket(const Socket& other) = delete;
  Socket& operator=(const Socket& other) = delete;

  Socket(Socket&& other) noexcept = default;
  Socket& operator=(Socket&& other) noexcept = default;

  // 自动销毁
  ~Socket();

  int fd() const noexcept { return fd_; }

  bool is_connected() const noexcept { return connect_address_ != nullptr; }
  void connect(const std::string& address, in_port_t port);

  bool is_binded() const noexcept { return self_address_ != nullptr; }
  void bind(const std::string& address, in_port_t port);
  void bind(in_port_t port);

  void listen(int bakclog = DEFAULT_BACK_LOG);
  Socket accept();

  ssize_t read(void* buffer, size_t size);

  ssize_t write(const void* buffer, size_t size);

  // void send(const void* buffer, size_t size);

  // void receive(void* buffer, size_t size);

  std::weak_ptr<Address> connect_address() const noexcept { return connect_address_; }
  std::weak_ptr<Address> self_address() const noexcept { return self_address_; }

  Family family() const noexcept { return family_; }
  Type type() const noexcept { return type_; }
  Protocol protocol() const noexcept { return protocol_; }

private:
  int fd_;
  Family family_;
  Type type_;
  Protocol protocol_;
  std::shared_ptr<Address> connect_address_;
  std::shared_ptr<Address> self_address_;

  void bind(std::shared_ptr<Address> address);
  void connect(std::shared_ptr<Address> address);

  void set_fd(int fd) { fd_ = fd; }
};

} // namespace ST::Net

#endif // STUDY_TOUR_NET_SOCKET_H