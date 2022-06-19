#include <cstdlib>
#include <cstdio>

#include <fmt/core.h>

#include "ST/Cast.h"


int main()
{
  uint16_t host_data_16 = 0x1122;
  uint32_t host_data_32 = 0x11223344;
  uint64_t host_data_64 = 0x112233445566;

  auto net_data_16 = ST::byte_order_cast<ST::net, uint16_t>(host_data_16);
  auto net_data_32 = ST::byte_order_cast<ST::net>(host_data_32);
  auto net_data_64 = ST::byte_order_cast<ST::net>(host_data_64);


  printf("host_data_16 = 0x%x\n", host_data_16);
  printf("host_data_32 = 0x%x\n", host_data_32);
  printf("host_data_64 = 0x%lx\n", host_data_64);
  printf("net_data_16 = 0x%x\n", net_data_16);
  printf("net_data_32 = 0x%x\n", net_data_32);
  printf("net_data_64 = 0x%lx\n", net_data_64);

  return EXIT_SUCCESS;
}