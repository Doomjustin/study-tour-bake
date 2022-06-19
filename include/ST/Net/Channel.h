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


  // ssize_t send();

  // ssize_t receive();

  // void on_received();

private:
};

} // namespace ST

#endif // STUDY_TOUR_NET_CHANNEL_H