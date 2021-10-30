#ifndef MEM_RAM_H_
#define MEM_RAM_H_

#include "define/width.h"
#include "define/type.h"
#include <cstdint>

namespace mem {

class Mem {
 private:
  uint8_t ram[RAM_SIZE];
 public:
  void Mem();
  void reset();
  void read(uint16_t ram_addr, uint8_t OUT &ram_data);
  void write(uint16_t ram_addr, uint8_t IN &ram_data);
};

} // namespace mem

#endif // MEM_RAM_H_