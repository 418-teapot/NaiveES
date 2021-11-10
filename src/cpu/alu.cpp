#include "cpu/alu.h"

namespace cpu {

void ALU::ClearC() {
  regfile.p_reg &= 0xFE;
}

void ALU::ClearZ() {
  regfile.p_reg &= 0xFD;
}

void ALU::ClearI() {
  regfile.p_reg &= 0xFB;
}

void ALU::ClearD() {
  regfile.p_reg &= 0xF7;
}

void ALU::ClearB() {
  regfile.p_reg &= 0xEF;
}

void ALU::ClearV() {
  regfile.p_reg &= 0xBF;
}

void ALU::ClearN() {
  regfile.p_reg &= 0x7F;
}

void ALU::SetC() {
  regfile.p_reg |= 0x01;
}

void ALU::SetZ() {
  regfile.p_reg |= 0x02;
}

void ALU::SetI() {
  regfile.p_reg |= 0x04;
}

void ALU::SetD() {
  regfile.p_reg |= 0x08;
}

void ALU::SetB() {
  regfile.p_reg |= 0x10;
}

void ALU::SetV() {
  regfile.p_reg |= 0x40;
}

void ALU::SetN() {
  regfile.p_reg |= 0x80;
}

uint8_t ALU::ReadC() {
  return READ_BIT(regfile.p_reg, 0);
}

uint8_t ALU::ReadZ() {
  return READ_BIT(regfile.p_reg, 1);
}

uint8_t ALU::ReadI() {
  return READ_BIT(regfile.p_reg, 2);
}

uint8_t ALU::ReadD() {
  return READ_BIT(regfile.p_reg, 3);
}

uint8_t ALU::ReadB() {
  return READ_BIT(regfile.p_reg, 4);
}

uint8_t ALU::ReadV() {
  return READ_BIT(regfile.p_reg, 6);
}

uint8_t ALU::ReadN() {
  return READ_BIT(regfile.p_reg, 7);
}

void ALU::UpdateNZ(IN uint8_t value) {
  if (!value) SetZ();
  else ClearZ();
  if (value & 0x80) SetN();
  else ClearN();
}

void ALU::Inx() {
  regfile.x_reg++;
  UpdateNZ(regfile.x_reg);
}

void ALU::Iny() {
  regfile.y_reg++;
  UpdateNZ(regfile.y_reg);
}

void ALU::Dex() {
  regfile.x_reg--;
  UpdateNZ(regfile.x_reg);
}

void ALU::Dey() {
  regfile.y_reg--;
  UpdateNZ(regfile.y_reg);
}

void ALU::Tax() {
  regfile.x_reg = regfile.a_reg;
  UpdateNZ(regfile.x_reg);
}

void ALU::Tay() {
  regfile.y_reg = regfile.a_reg;
  UpdateNZ(regfile.y_reg);
}

void ALU::Txa() {
  regfile.a_reg = regfile.x_reg;
  UpdateNZ(regfile.a_reg);
}

void ALU::Tya() {
  regfile.a_reg = regfile.y_reg;
  UpdateNZ(regfile.a_reg);
}

void ALU::Tsx() {
  regfile.x_reg = regfile.sp_reg;
  UpdateNZ(regfile.x_reg);
}

void ALU::Txs() {
  regfile.sp_reg = regfile.x_reg;
}

void ALU::Pha() {
  MemWrite(regfile.sp_reg--, regfile.a_reg);
}

void ALU::Php() {
  MemWrite(regfile.sp_reg--, regfile.p_reg);
}

void ALU::Pla() {
  MemRead(++regfile.sp_reg, regfile.a_reg);
}

void ALU::Plp() {
  MemRead(++regfile.sp_reg, regfile.p_reg);
}

void ALU::Adder(IN OUT uint8_t &opnd1, IN uint8_t opnd2,
    IN uint8_t cin, OUT uint8_t &cout) {
  uint16_t sum = opnd1 + opnd2 + cin;
  cout = READ_BIT(sum, 8);
  opnd1 = sum & 0xFF;
}

void ALU::Adc(IN MemData opnd) {
  regfile.pc_reg += (uint8_t)opnd.byte + 1;
  uint8_t cout = 0;
  Adder(regfile.a_reg, opnd.data, ReadC(), cout);
  if (cout) SetC();
  else ClearC();
  UpdateNZ(regfile.a_reg);
}

void ALU::Sbc(IN MemData opnd) {
  regfile.pc_reg += (uint8_t)opnd.byte + 1;
  uint8_t cout = 0;
  Adder(regfile.a_reg, -opnd.data, -ReadC(), cout);
  if (cout) SetC();
  else ClearC();
  UpdateNZ(regfile.a_reg);
}

void ALU::And(IN MemData opnd) {
  regfile.pc_reg += (uint8_t)opnd.byte + 1;
  regfile.a_reg &= opnd.data;
  UpdateNZ(regfile.a_reg);
}

void ALU::Eor(IN MemData opnd) {
  regfile.pc_reg += (uint8_t)opnd.byte + 1;
  regfile.a_reg ^= opnd.data;
  UpdateNZ(regfile.a_reg);
}

void ALU::Ora(IN MemData opnd) {
  regfile.pc_reg += (uint8_t)opnd.byte + 1;
  regfile.a_reg |= opnd.data;
  UpdateNZ(regfile.a_reg);
}

void ALU::CmpFactory(IN uint8_t opnd1, IN MemData opnd2) {
  regfile.pc_reg += (uint8_t)opnd2.byte + 1;
  uint8_t cout = 0;
  uint8_t tmp = opnd1;
  Adder(tmp, -opnd2.data, 0, cout);
  if (cout) SetC();
  else ClearC();
  UpdateNZ(tmp);
}

void ALU::Cmp(IN MemData opnd) {
  CmpFactory(regfile.a_reg, opnd);
}

void ALU::Cpx(IN MemData opnd) {
  CmpFactory(regfile.x_reg, opnd);
}

void ALU::Cpy(IN MemData opnd) {
  CmpFactory(regfile.y_reg, opnd);
}

void ALU::LdFactory(IN OUT uint8_t &opnd1, IN MemData opnd2) {
  regfile.pc_reg += (uint8_t)opnd2.byte + 1;
  opnd1 = opnd2.data;
  UpdateNZ(regfile.a_reg);
}

void ALU::Lda(IN MemData opnd) {
  LdFactory(regfile.a_reg, opnd);
}

void ALU::Ldx(IN MemData opnd) {
  LdFactory(regfile.x_reg, opnd);
}

void ALU::Ldy(IN MemData opnd) {
  LdFactory(regfile.y_reg, opnd);
}

} // namespace cpu
