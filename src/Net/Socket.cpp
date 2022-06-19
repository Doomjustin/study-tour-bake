#include "ST/Net/Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <spdlog/spdlog.h>

#include "ST/Net/IPv4Address.h"
#include "ST/Net/IPv6Address.h"
#include "ST/Exception.h"


namespace ST::Net {

Socket::Socket(Family family, Type type, Protocol protocol)
  : fd_{ -1 },
    family_{ family },
    type_{ type },
    protocol_{ protocol },
    connect_address_{ nullptr },
    self_address_{ nullptr }
{
  fd_ = ::socket(to_int(family), to_int(type), to_int(protocol));
  if (fd_ == -1) {
    SPDLOG_ERROR("can't open socket[family = {}, type = {}, protocol = {}]",
          to_string(family), to_string(type), to_string(protocol));
    throw std::system_error{ errno, std::generic_category(), "can't open socket" };
  }
  SPDLOG_INFO("created Socket[{}]", fd_);
}

Socket::~Socket()
{
  if (fd_ == -1) return;
  
  auto res = ::close(fd_);
  if (res == -1)
    SPDLOG_ERROR("can't close socket[fd = {}]", fd_);

  SPDLOG_INFO("Socket[{}] closed", fd_);
  fd_ = -1;
}


void Socket::connect(const std::string& address, in_port_t port)
{
  std::shared_ptr<Address> connect_address;
  switch (family_) {
  case Family::IPv4: default:
    connect_address = std::make_shared<IPv4Address>(address, port);
    break;
  case Family::IPv6:
    connect_address = std::make_shared<IPv6Address>(address, port);
    break;
  }

  connect(connect_address);
}

void Socket::connect(std::shared_ptr<Address> address)
{
  SPDLOG_INFO("connecting to address[{}]", address->to_string());

  auto res = ::connect(fd_, address->address(), address->length());
  if (res == -1) {
    SPDLOG_ERROR("connect to address[{}] error: {}", address->to_string(), strerror(errno));
    throw std::system_error{ errno, std::generic_category(),
          "can't connect" };
  }

  connect_address_ = address;

  SPDLOG_INFO("connected to address[{}]", address->to_string());
}

void Socket::bind(const std::string& address, in_port_t port)
{
  std::shared_ptr<Address> bind_address;
  switch (family_) {
  case Family::IPv4: default:
    bind_address = std::make_shared<IPv4Address>(address, port);
    break;
  case Family::IPv6:
    bind_address = std::make_shared<IPv6Address>(address, port);
    break;
  }

  bind(bind_address);
}

void Socket::bind(in_port_t port)
{
  std::shared_ptr<Address> bind_address;
  switch (family_) {
  case Family::IPv4: default:
    bind_address = std::make_shared<IPv4Address>(port);
    break;
  case Family::IPv6:
    bind_address = std::make_shared<IPv6Address>(port);
    break;
  }

  bind(bind_address);
}

void Socket::bind(std::shared_ptr<Address> address)
{
  SPDLOG_INFO("binding to address[{}]", address->to_string());

  auto res = ::bind(fd_, address->address(), address->length());
  if (res == -1) {
    SPDLOG_ERROR("bind to address[{}] error: {}", address->to_string(), strerror(errno));
    throw std::system_error{ errno, std::generic_category(),
          "can't bind" };
  }
  self_address_ = address;

  SPDLOG_INFO("binded to address[{}]", address->to_string());
}

void Socket::listen(int backlog)
{
  // static_assert(bind_address_ != nullptr, "you shouln't listen before bind");
  SPDLOG_INFO("listening on address[{}]", self_address_->to_string());

  auto res = ::listen(fd_, backlog);
  if (res == -1) {
    SPDLOG_ERROR("listen no address[{}] error: {}", self_address_->to_string(), strerror(errno));
    throw std::system_error{ errno, std::generic_category(),
          "can't listen" };
  }

  SPDLOG_INFO("listened on address[{}]", self_address_->to_string());
}

Socket Socket::accept()
{
  SPDLOG_INFO("accepting");

  auto connecting_fd = ::accept(fd_, nullptr, nullptr);
  if (connecting_fd == -1) {
    SPDLOG_ERROR("accept error: {}", strerror(errno));
    throw std::system_error{ errno, std::generic_category(),
          "can't accept" };
  }

  Socket connecting_socket { family_, type_, protocol_ };
  connecting_socket.set_fd(connecting_fd);

  SPDLOG_INFO("accepted");
  return connecting_socket;
}

ssize_t Socket::read(void* buffer, size_t size)
{
  SPDLOG_INFO("try to read {} bytes from fd: {}", size, fd_);

  auto read_bytes = ::read(fd_, buffer, size);
  if (read_bytes == -1) {
    SPDLOG_ERROR("read from [{}] error: {}", fd_, strerror(errno));
    throw std::system_error{ errno, std::generic_category(),
          "can't read" };
  }

  SPDLOG_INFO("readed {} bytes from fd: {}", read_bytes, fd_);
  return read_bytes;
}

ssize_t Socket::write(const void* buffer, size_t size)
{
  SPDLOG_INFO("try to write {} bytes to fd: {}", size, fd_);

  auto write_bytes = ::write(fd_, buffer, size);
  if (write_bytes == -1) {
    SPDLOG_ERROR("write to [{}] error: {}", fd_, strerror(errno));
    throw std::system_error{ errno, std::generic_category(),
          "can't read" };
  }

  SPDLOG_INFO("write {} bytes to fd: {}", write_bytes, fd_);
  return write_bytes;
}


} // namespace ST::Net