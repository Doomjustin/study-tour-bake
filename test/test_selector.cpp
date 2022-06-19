#include <cstdlib>

#include "ST/Net/Selector.h"


int main()
{
  ST::Net::Selector selector{};

  selector.add_read_set(1, 2, 3, 4, 1);
  selector.remove_read_set(2, 3, 5);

  selector.add_write_set(1, 2, 3, 4, 1);
  selector.remove_read_set(2, 3, 5);

  selector.add_exception_set(1, 2, 3, 4, 1);
  selector.remove_exception_set(2, 3, 5);

  return EXIT_SUCCESS;
}