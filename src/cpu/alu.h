#ifndef CPU_ALU_H_
#define CPU_ALU_H_

#define READ_BIT(value, n) ((value >> n) & 0x1)

#include "define/type.h"
#include "mem/mem.h"
#include <cstdint>

namespace cpu {

using mem::MemRead;
using mem::MemWrite;

class ALU {
 private:
  struct {
    uint16_t pc_reg;
    uint8_t sp_reg;
    uint8_t a_reg;
    uint8_t x_reg;
    uint8_t y_reg;
    uint8_t p_reg;
  } regfile;
 public:
  void reset() {
    regfile.pc_reg = 0;
    regfile.sp_reg = 0;
    regfile.a_reg = 0;
    regfile.x_reg = 0;
    regfile.y_reg = 0;
    regfile.p_reg = 0;
  }
  ALU() {
    reset();
  }
  void ClearC();
  void ClearZ();
  void ClearI();
  void ClearD();
  void ClearB();
  void ClearV();
  void ClearN();
  void SetC();
  void SetZ();
  void SetI();
  void SetD();
  void SetB();
  void SetV();
  void SetN();
  uint8_t ReadC();
  uint8_t ReadZ();
  uint8_t ReadI();
  uint8_t ReadD();
  uint8_t ReadB();
  uint8_t ReadV();
  uint8_t ReadN();
  void UpdateNZ(IN uint8_t value);
  void Inx();
  void Iny();
  void Dex();
  void Dey();
  void Tax();
  void Tay();
  void Tsx();
  void Txa();
  void Txs();
  void Tya();
  void Pha();
  void Php();
  void Pla();
  void Plp();
  void Adder(IN OUT uint8_t &opnd1, IN uint8_t opnd2,
      IN uint8_t cin, OUT uint8_t &cout);
  void Adc(IN MemData opnd);
  void Sbc(IN MemData opnd);
  void And(IN MemData opnd);
  void Eor(IN MemData opnd);
  void Ora(IN MemData opnd);
  void CmpFactory(IN uint8_t opnd1, IN MemData opnd2);
  void Cmp(IN MemData opnd);
  void Cpx(IN MemData opnd);
  void Cpy(IN MemData opnd);
  void LdFactory(IN OUT uint8_t &opnd1, IN MemData opnd2);
  void Lda(IN MemData opnd);
  void Ldx(IN MemData opnd);
  void Ldy(IN MemData opnd);
};

}; // namespace cpu

#endif // CPU_ALU_H_
