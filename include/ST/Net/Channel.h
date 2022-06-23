#ifndef STUDY_TOUR_NET_CHANNEL_H
#define STUDY_TOUR_NET_CHANNEL_H

#include <memory>

#include "Socket.h"


namespace ST::Net {

/**
 * @brief 维持一个连接通道，可以发送和接受数据
 *
 */
class Channel {
public:
  Channel(std::shared_ptr<Socket> self, std::shared_ptr<Socket> other);

  Channel(const Channel& other) = delete;
  Channel& operator=(const Channel& other) = delete;

  Channel(Channel&& other) noexcept = default;
  Channel& operator=(Channel&& other) noexcept = default;

  ~Channel() = default;

  void receive_event();

  void send_event();

private:
  std::unique_ptr<Socket> self_;
  std::unique_ptr<Socket> other_;
};

} // namespace ST

#endif // STUDY_TOUR_NET_CHANNEL_H