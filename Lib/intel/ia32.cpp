/*****************************************************************************************************************
* Copyright (c) 2012 Khalid Ali Al-Kooheji                                                                       *
*                                                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and              *
* associated documentation files (the "Software"), to deal in the Software without restriction, including        *
* without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
* copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the       *
* following conditions:                                                                                          *
*                                                                                                                *
* The above copyright notice and this permission notice shall be included in all copies or substantial           *
* portions of the Software.                                                                                      *
*                                                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT          *
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.          *
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, * DAMAGES OR OTHER LIABILITY,      *
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE            *
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                                         *
*****************************************************************************************************************/
#include "../reccore.h"

#define BIT3_INTO_BIT0(x) ((x&0x8)>>3)

namespace reccore {
namespace intel {

inline uint8_t _ModRM(uint8_t mod,uint8_t reg,uint8_t rm)  {
	return (((mod&0x3)<<6)|((reg&0x7)<<3)|((rm&0x7)));
}

inline uint8_t _SIB(uint8_t scale,uint8_t index,uint8_t base)  {
	return (((scale&0x3)<<6)|((index&0x7)<<3)|((base&0x7)));
}

inline void emitREX(Emitter* e, EA mem) {
 if (mem.mod != 3) {
    if (mem.rm == 4) {
      e->emit8(PREFIX::REX(1,mem.reg>>3,mem.index>>3,mem.base>>3));
    } else {
      e->emit8(PREFIX::REX(1,mem.reg>>3,0,mem.rm>>3));
    }
  } else {
    e->emit8(PREFIX::REX(1,mem.reg>>3,0,mem.rm>>3)); //same as above i know
  }
}

inline void emitModRMSIB(Emitter* e, EA mem) {


	e->emit8(_ModRM(mem.mod,mem.reg,mem.rm));
  if (mem.rm == 4) {
    e->emit8(_SIB(mem.scale,mem.index,mem.base));
  }
  if (mem.mod == 0 && ((mem.rm == 5) || (mem.rm == 4 && mem.base == EBP)))
    e->emit32(mem.displacement);
  else if (mem.mod == 1)
    e->emit8(mem.displacement&0xFF);
  else if (mem.mod == 2)
    e->emit32(mem.displacement);
  
}


void IA32::AAA()
{
	e->emit8(0x37);
}

void IA32::AAD()
{
	e->emit8(0xD5);
	e->emit8(0x0A);
}

void IA32::AAM()
{
	e->emit8(0xD4);
	e->emit8(0x0A);
}

void IA32::AAS()
{
	e->emit8(0x3F);
}

void IA32::ADD(Reg8 dest, uint8_t imm) {
  if (dest == AL) {
    e->emit8(0x05);
    e->emit32(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,0,dest));
    e->emit32(imm);
  }
}

void IA32::ADD(Reg16 dest, uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  if (dest == AX) {
    e->emit8(0x05);
    e->emit16(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,0,dest));
    e->emit16(imm);
  }
}

void IA32::ADD(Reg32 dest, uint32_t imm) {
  if (dest == EAX) {
    e->emit8(0x05);
    e->emit32(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,0,dest));
    e->emit32(imm);
  }
}

void IA32::ADD(Reg64 dest, uint32_t imm) {
  e->emit8(PREFIX::REX(1,dest>>3,0,0));
  if (dest == EAX) {
    e->emit8(0x05);
    e->emit32(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,0,dest));
    e->emit32(imm);
  }
}

void IA32::ADD(EA rm, uint8_t imm) {
  e->emit8(0x80);
  emitModRMSIB(e,rm);
  e->emit8(imm);
}

void IA32::ADD(EA rm, uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  e->emit8(0x81);
  emitModRMSIB(e,rm);
  e->emit16(imm);
}

void IA32::ADD(EA rm, uint32_t imm) {
  e->emit8(0x81);
  emitModRMSIB(e,rm);
  e->emit32(imm);
}

void IA32::ADD(EA rm, Reg8 reg) {
  rm.reg = reg;
  e->emit8(0x00);
  emitModRMSIB(e,rm);
}

void IA32::ADD(EA rm, Reg16 reg) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  rm.reg = reg;
  e->emit8(0x01);
  emitModRMSIB(e,rm);
}

void IA32::ADD(EA rm, Reg32 reg) {
  rm.reg = reg;
  e->emit8(0x01);
  emitModRMSIB(e,rm);
}

void IA32::ADD(EA rm, Reg64 reg) {
  e->emit8(PREFIX::REX(1,reg>>3,0,0));
  rm.reg = reg;
  e->emit8(0x01);
  emitModRMSIB(e,rm);
}

void IA32::ADD(Reg8 reg, EA rm) {
  rm.reg = reg;
  e->emit8(0x02);
  emitModRMSIB(e,rm);
}

void IA32::ADD(Reg16 reg, EA rm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  rm.reg = reg;
  e->emit8(0x03);
  emitModRMSIB(e,rm);
}

void IA32::ADD(Reg32 reg, EA rm) {
  rm.reg = reg;
  e->emit8(0x03);
  emitModRMSIB(e,rm);
}

void IA32::ADD(Reg64 reg, EA rm) {
  e->emit8(PREFIX::REX(1,reg>>3,0,0));
  rm.reg = reg;
  e->emit8(0x03);
  emitModRMSIB(e,rm);
}

void IA32::ADDPD(Reg_xmm a, EA b) {
  e->emit8(0x66);
  e->emit8(0x05);
  e->emit8(0x58);
  b.reg = a;
  emitModRMSIB(e,b);
}

void IA32::VADDPD(Reg_xmm a, Reg_xmm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,0,1));
  e->emit8(0x58);
  emitModRMSIB(e,c);
}

void IA32::VADDPD(Reg_ymm a, Reg_ymm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,1,1));
  e->emit8(0x58);
  emitModRMSIB(e,c);
}


void IA32::ADDPS(Reg_xmm a, EA b) {
  e->emit8(0x05);
  e->emit8(0x58);
  b.reg = a;
  emitModRMSIB(e,b);
}

void IA32::VADDPS(Reg_xmm a, Reg_xmm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,0,0));
  e->emit8(0x58);
  emitModRMSIB(e,c);
}

void IA32::VADDPS(Reg_ymm a, Reg_ymm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,1,0));
  e->emit8(0x58);
  emitModRMSIB(e,c);
}

void IA32::CALL(uint16_t rel16) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  e->emit8(0xE8);
  e->emit16(rel16);
}

void IA32::CALL(uint32_t rel32) {
  
  e->emit8(0xE8);
  e->emit32(rel32);
}

void IA32::CALL(void* ptr) {

  auto rel32 = intptr_t(ptr) - (intptr_t(e->block()->address)+e->block()->cursor+5);
  CALL(uint32_t(rel32));
  /*MOV(EAX,uint32_t(ptr));
  e->emit8(0xFF);
  e->emit8(ModRM(3,2,EAX));*/
}


void IA32::CMP(Reg32 reg, uint32_t imm32) {
  if (reg == EAX) {
    e->emit8(0x3D);
    e->emit32(imm32);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(0x3,7,reg));
    e->emit32(imm32);
  }
}

void IA32::INC(Reg32 reg) {
  //e->emit8(
  //emitREX(e);
  e->emit8(0xFF);
  e->emit8(_ModRM(3,0,reg));
}

void IA32::Jcc(JumpCode cc, int8_t rel8) {
  e->emit8(0x70|cc);
  e->emit8(rel8);
}

void IA32::Jcc(JumpCode cc, int16_t rel16) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  e->emit8(0x0F);
  e->emit8(0x80|cc);
  e->emit16(rel16);
}

void IA32::Jcc(JumpCode cc, int32_t rel32) {
  e->emit8(0x0F);
  e->emit8(0x80|cc);
  e->emit32(rel32);
}

void IA32::JMP(int8_t rel8) {
  e->emit8(0xEB);
  e->emit8(rel8);
}

void IA32::JMP(int16_t rel16) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  e->emit8(0xE9);
  e->emit16(rel16);
}

void IA32::JMP(int32_t rel32) {
  e->emit8(0xE9);
  e->emit32(rel32);
}

void IA32::LEA(Reg16 r16, EA mem) {
  mem.reg = r16;
  e->emit8(0x8D);
  emitModRMSIB(e,mem);
}

void IA32::LEA(Reg32 r32, EA mem) {
  mem.reg = r32;
  e->emit8(0x8D);
  emitModRMSIB(e,mem);
}

void IA32::LEA(Reg64 r64, EA mem) {
  mem.reg = r64;  
  emitREX(e,mem);
  e->emit8(0x8D);
  emitModRMSIB(e,mem);
}

void IA32::LEA(Reg32 r32, void* ptr) {
  LEA(r32,EA("[disp32]",int32_t(ptr)));
}

void IA32::MOV(EA m8, Reg8 src) {
	e->emit8(0x88);
  m8.reg = src;
  emitModRMSIB(e,m8);
}

void IA32::MOV(EA m16, Reg16 src) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
	e->emit8(0x89);
  m16.reg = src;
  emitModRMSIB(e,m16);
}

void IA32::MOV(EA m32, Reg32 src) {
	e->emit8(0x89);
  m32.reg = src;
  emitModRMSIB(e,m32);
}

void IA32::MOV(EA m64, Reg64 src) {
  m64.reg = src;
  emitREX(e,m64);
	e->emit8(0x89);
  emitModRMSIB(e,m64);
}

void IA32::MOV(Reg8 dest, EA m8) {
	e->emit8(0x8A);
  m8.reg = dest;
  emitModRMSIB(e,m8);
}

void IA32::MOV(Reg16 dest, EA m16) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
	e->emit8(0x8B);
  m16.reg = dest;
  emitModRMSIB(e,m16);
}

void IA32::MOV(Reg32 dest, EA m32) {
	e->emit8(0x8B);
  m32.reg = dest;
  emitModRMSIB(e,m32);
}


void IA32::MOV(Reg8 dest, Reg8 src) {
	e->emit8(0x8A);
	e->emit8(_ModRM(0x3,dest,src));
}

void IA32::MOV(Reg16 dest, Reg16 src) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
	e->emit8(0x8B);
	e->emit8(_ModRM(0x3,dest,src));
}

void IA32::MOV(Reg32 dest, Reg32 src) {
	e->emit8(0x8B);
	e->emit8(_ModRM(0x3,dest,src));
}

void IA32::MOV(Reg8 dest, uint8_t imm) {
	e->emit8(0xB8|(dest&0x7));
	e->emit8(imm);
}

void IA32::MOV(Reg16 dest, uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
	e->emit8(0xB8|(dest&0x7));
	e->emit16(imm);
}

void IA32::MOV(Reg32 dest, uint32_t imm) {
	e->emit8(0xB8|(dest&0x7));
	e->emit32(imm);
}

/*void IA32::MOV(Reg64 dest, uint64_t imm) {
  e->emit8(PREFIX::REX(1,0,0,BIT3_INTO_BIT0(dest)));
	e->emit8(0xB8+(dest&0x7));
	e->emit64(imm);
}*/

void IA32::MOV(void* dest, Reg32 src) {
	//e->emit8(0x89);
	//e->emit8(ModRM(0x0,src,0x5));
  //e->emit32(uint32_t(dest));
  MOV(EA("[disp32]",int32_t(dest)),src);
}

void IA32::MOV(Reg32 dest, void* src) {
  MOV(dest,EA("[disp32]",int32_t(src)));
}

/*void IA32::MOV(Reg64 dest, Reg64 src) {
  e->emit8(PREFIX::REX(1,BIT3_INTO_BIT0(dest),0,BIT3_INTO_BIT0(src)));
	e->emit8(0x8B);
	e->emit8(ModRM(0x3,dest,src));
}*/

void IA32::NOP() {
  e->emit8(0x90);
}

void IA32::POP(Reg32 reg) {
  e->emit8(0x58|(reg&0x7));
}

void IA32::PUSH(EA mem) {
  e->emit8(0xFF);
  mem.reg = 6;
  emitModRMSIB(e,mem);
}

void IA32::PUSH(Reg32 reg) {
	e->emit8(0x50+reg);
}

void IA32::PUSH(uint8_t imm) {
  e->emit8(0x6A);
  e->emit8(imm);
}

void IA32::PUSH(uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  e->emit8(0x68);
  e->emit16(imm);
}
  
void IA32::PUSH(uint32_t imm) {
  e->emit8(0x68);
  e->emit32(imm);
}

void IA32::RET(bool farreturn) {
  if (!farreturn) {
    e->emit8(0xC3);
  } else {
    e->emit8(0xCB);
  }
}

}
}