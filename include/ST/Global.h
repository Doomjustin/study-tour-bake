#ifndef STUDY_TOUR_GLOBAL_H
#define STUDY_TOUR_GLOBAL_H

#include <string>
#include <cstddef>
#include <cstdint>


namespace ST {

constexpr static int MAX_BUFFER = 4096;

constexpr static int MAX_LINE = 4096;

} // namespace ST


// 网络相关
namespace ST::Net {

enum class Family {
  IPv4,
  IPv6
};

enum class Type {
  TCP,
  UDP
};

enum class Protocol {
  Undefined
};

int to_int(Family family);

int to_int(Type type);

int to_int(Protocol protocol);

std::string to_string(Family family);

std::string to_string(Type type);

std::string to_string(Protocol protocol);

} // namespace ST::Net

#endif // STUDY_TOUR_GLOBAL_H