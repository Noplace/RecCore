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

void IA32::ADC(Reg8 dest, uint8_t imm) {
  if (dest == AL) {
    e->emit8(0x14);
    e->emit32(imm);
  } else {
    e->emit8(0x80);
    e->emit8(_ModRM(3,2,dest));
    e->emit32(imm);
  }
}

void IA32::ADC(Reg16 dest, uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  if (dest == AX) {
    e->emit8(0x15);
    e->emit16(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,2,dest));
    e->emit16(imm);
  }
}

void IA32::ADC(Reg32 dest, uint32_t imm) {
  if (dest == EAX) {
    e->emit8(0x15);
    e->emit32(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,2,dest));
    e->emit32(imm);
  }
}

void IA32::ADC(Reg64 dest, uint32_t imm) {
  e->emit8(PREFIX::REX(1,dest>>3,0,0));
  if (dest == RAX) {
    e->emit8(0x15);
    e->emit32(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,2,dest));
    e->emit32(imm);
  }
}

void IA32::ADC(EA rm, uint8_t imm) {
  e->emit8(0x80);
  rm.reg = 2;
  emitModRMSIB(e,rm);
  e->emit8(imm);
}

void IA32::ADC(EA rm, uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  e->emit8(0x81);
  rm.reg = 2;
  emitModRMSIB(e,rm);
  e->emit16(imm);
}

void IA32::ADC(EA rm, uint32_t imm) {
  e->emit8(0x81);
  rm.reg = 2;
  emitModRMSIB(e,rm);
  e->emit32(imm);
}

void IA32::ADC(EA rm, Reg8 reg) {
  rm.reg = reg;
  e->emit8(0x10);
  emitModRMSIB(e,rm);
}

void IA32::ADC(EA rm, Reg16 reg) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  rm.reg = reg;
  e->emit8(0x11);
  emitModRMSIB(e,rm);
}

void IA32::ADC(EA rm, Reg32 reg) {
  rm.reg = reg;
  e->emit8(0x11);
  emitModRMSIB(e,rm);
}

void IA32::ADC(EA rm, Reg64 reg) {
  e->emit8(PREFIX::REX(1,reg>>3,0,0));
  rm.reg = reg;
  e->emit8(0x11);
  emitModRMSIB(e,rm);
}

void IA32::ADC(Reg8 reg, EA rm) {
  rm.reg = reg;
  e->emit8(0x12);
  emitModRMSIB(e,rm);
}

void IA32::ADC(Reg16 reg, EA rm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  rm.reg = reg;
  e->emit8(0x03);
  emitModRMSIB(e,rm);
}

void IA32::ADC(Reg32 reg, EA rm) {
  rm.reg = reg;
  e->emit8(0x13);
  emitModRMSIB(e,rm);
}

void IA32::ADC(Reg64 reg, EA rm) {
  e->emit8(PREFIX::REX(1,reg>>3,0,0));
  rm.reg = reg;
  e->emit8(0x13);
  emitModRMSIB(e,rm);
}

void IA32::ADD(Reg8 dest, uint8_t imm) {
  if (dest == AL) {
    e->emit8(0x05);
    e->emit32(imm);
  } else {
    e->emit8(0x80);
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
  if (dest == RAX) {
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

void IA32::ADDSD(Reg_xmm a, EA b) {
  e->emit8(0xF2);
  e->emit8(0x05);
  e->emit8(0x58);
  b.reg = a;
  emitModRMSIB(e,b);
}

void IA32::VADDSD(Reg_xmm a, Reg_xmm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,0,2));
  e->emit8(0x58);
  emitModRMSIB(e,c);
}

void IA32::ADDSS(Reg_xmm a, EA b) {
  e->emit8(0xF3);
  e->emit8(0x05);
  e->emit8(0x58);
  b.reg = a;
  emitModRMSIB(e,b);
}

void IA32::VADDSS(Reg_xmm a, Reg_xmm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,0,1));
  e->emit8(0x58);
  emitModRMSIB(e,c);
}

void IA32::ADDSUBPD(Reg_xmm a, EA b) {
  e->emit8(0x66);
  e->emit8(0x0F);
  e->emit8(0xD0);
  b.reg = a;
  emitModRMSIB(e,b);
}

void IA32::VADDSUBPD(Reg_xmm a, Reg_xmm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,0,1));
  e->emit8(0xD0);
  emitModRMSIB(e,c);
}

void IA32::VADDSUBPD(Reg_ymm a, Reg_ymm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,1,1));
  e->emit8(0xD0);
  emitModRMSIB(e,c);
}


void IA32::AND(Reg8 dest, uint8_t imm) {
  if (dest == AL) {
    e->emit8(0x24);
    e->emit32(imm);
  } else {
    e->emit8(0x80);
    e->emit8(_ModRM(3,4,dest));
    e->emit32(imm);
  }
}

void IA32::AND(Reg16 dest, uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  if (dest == AX) {
    e->emit8(0x25);
    e->emit16(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,4,dest));
    e->emit16(imm);
  }
}

void IA32::AND(Reg32 dest, uint32_t imm) {
  if (dest == EAX) {
    e->emit8(0x25);
    e->emit32(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,4,dest));
    e->emit32(imm);
  }
}

void IA32::AND(Reg64 dest, uint32_t imm) {
  e->emit8(PREFIX::REX(1,dest>>3,0,0));
  if (dest == RAX) {
    e->emit8(0x25);
    e->emit32(imm);
  } else {
    e->emit8(0x81);
    e->emit8(_ModRM(3,4,dest));
    e->emit32(imm);
  }
}

void IA32::AND(EA rm, uint8_t imm) {
  e->emit8(0x80);
  rm.reg = 4;
  emitModRMSIB(e,rm);
  e->emit8(imm);
}

void IA32::AND(EA rm, uint16_t imm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  e->emit8(0x81);
  rm.reg = 4;
  emitModRMSIB(e,rm);
  e->emit16(imm);
}

void IA32::AND(EA rm, uint32_t imm) {
  e->emit8(0x81);
  rm.reg = 4;
  emitModRMSIB(e,rm);
  e->emit32(imm);
}

void IA32::AND(EA rm, Reg8 reg) {
  rm.reg = reg;
  e->emit8(0x20);
  emitModRMSIB(e,rm);
}

void IA32::AND(EA rm, Reg16 reg) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  rm.reg = reg;
  e->emit8(0x21);
  emitModRMSIB(e,rm);
}

void IA32::AND(EA rm, Reg32 reg) {
  rm.reg = reg;
  e->emit8(0x21);
  emitModRMSIB(e,rm);
}

void IA32::AND(EA rm, Reg64 reg) {
  e->emit8(PREFIX::REX(1,reg>>3,0,0));
  rm.reg = reg;
  e->emit8(0x21);
  emitModRMSIB(e,rm);
}

void IA32::AND(Reg8 reg, EA rm) {
  rm.reg = reg;
  e->emit8(0x22);
  emitModRMSIB(e,rm);
}

void IA32::AND(Reg16 reg, EA rm) {
  e->emit8(PREFIX::Group3::OPERAND_SIZE_OVERRIDE);
  rm.reg = reg;
  e->emit8(0x23);
  emitModRMSIB(e,rm);
}

void IA32::AND(Reg32 reg, EA rm) {
  rm.reg = reg;
  e->emit8(0x23);
  emitModRMSIB(e,rm);
}

void IA32::AND(Reg64 reg, EA rm) {
  e->emit8(PREFIX::REX(1,reg>>3,0,0));
  rm.reg = reg;
  e->emit8(0x23);
  emitModRMSIB(e,rm);
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

void IA32::EMMS() {
  e->emit8(0x0F);
  e->emit8(0x77);
}

void IA32::F2XM1() {
  e->emit8(0xD9);
  e->emit8(0xF0);
}

void IA32::FABS() {
  e->emit8(0xD9);
  e->emit8(0xE1);
}

void IA32::FADD(EA mfp, FPSize size) {
  switch (size) {
    case FP32:
      e->emit8(0xD8);
      mfp.reg = 0;
      emitModRMSIB(e,mfp);
      break;
    case FP64:
      e->emit8(0xDC);
      mfp.reg = 0;
      emitModRMSIB(e,mfp);
      break;
  }
}

void IA32::FADD(Reg_sti dest, Reg_sti src) {
  if (dest == ST0) {
    e->emit8(0xD8);
    e->emit8(0xC0+src);
  } else {
    e->emit8(0xDC);
    e->emit8(0xC0+dest);
  }
}

void IA32::FADDP(Reg_sti dest, Reg_sti src) {
  if (dest == ST1 && src == ST0) {
    e->emit8(0xDE);
    e->emit8(0xC1);
  } else if (src == ST0) {
    e->emit8(0xDC);
    e->emit8(0xC0+dest);
  }
}

void IA32::FIADD(EA mint, IntSize size) {
  switch (size) {
    case Int16:
      e->emit8(0xDE);
      mint.reg = 0;
      emitModRMSIB(e,mint);
      break;
    case Int32:
      e->emit8(0xDA);
      mint.reg = 0;
      emitModRMSIB(e,mint);
      break;
  }
}

void IA32::FBLD(EA m80dec) {
  e->emit8(0xDF);
  m80dec.reg = 4;
  emitModRMSIB(e,m80dec);
}

void IA32::FBSTP(EA m80bcd) {
  e->emit8(0xDF);
  m80bcd.reg = 6;
  emitModRMSIB(e,m80bcd);
}

void IA32::FCHS() {
  e->emit8(0xD9);
  e->emit8(0xE0);
}

void IA32::FCLEX() {
  e->emit8(0x9B);
  e->emit8(0xDB);
  e->emit8(0xE2);
}

void IA32::FNCLEX() {
  e->emit8(0xDB);
  e->emit8(0xE2);
}

void IA32::FCOMI(Reg_sti STi) {
  e->emit8(0xDB);
  e->emit8(0xF0+STi);
}

void IA32::FCOMIP(Reg_sti STi) {
  e->emit8(0xDF);
  e->emit8(0xF0+STi);
}

void IA32::FUCOMI(Reg_sti STi) {
  e->emit8(0xDB);
  e->emit8(0xE8+STi);
}

void IA32::FUCOMIP(Reg_sti STi) {
  e->emit8(0xDF);
  e->emit8(0xE8+STi);
}


void IA32::FCOS() {
  e->emit8(0xD9);
  e->emit8(0xFF);
}


void IA32::FDIV(EA mfp, FPSize size) {
  switch (size) {
    case FP32:
      e->emit8(0xD8);
      mfp.reg = 6;
      emitModRMSIB(e,mfp);
      break;
    case FP64:
      e->emit8(0xDC);
      mfp.reg = 6;
      emitModRMSIB(e,mfp);
      break;
  }
}

void IA32::FDIV(Reg_sti dest, Reg_sti src) {
  if (dest == ST0) {
    e->emit8(0xD8);
    e->emit8(0xF0+src);
  } else {
    e->emit8(0xDC);
    e->emit8(0xF8+dest);
  }
}

void IA32::FDIVP(Reg_sti dest, Reg_sti src) {
  if (dest == ST1 && src == ST0) {
    e->emit8(0xDE);
    e->emit8(0xF9);
  } else if (src == ST0) {
    e->emit8(0xDE);
    e->emit8(0xF8+dest);
  }
}

void IA32::FIDIV(EA mint, IntSize size) {
  switch (size) {
    case Int16:
      e->emit8(0xDE);
      mint.reg = 6;
      emitModRMSIB(e,mint);
      break;
    case Int32:
      e->emit8(0xDA);
      mint.reg = 6;
      emitModRMSIB(e,mint);
      break;
  }
}


void IA32::FDIVR(EA mfp, FPSize size) {
  switch (size) {
    case FP32:
      e->emit8(0xD8);
      mfp.reg = 7;
      emitModRMSIB(e,mfp);
      break;
    case FP64:
      e->emit8(0xDC);
      mfp.reg = 7;
      emitModRMSIB(e,mfp);
      break;
  }
}

void IA32::FDIVR(Reg_sti dest, Reg_sti src) {
  if (dest == ST0) {
    e->emit8(0xD8);
    e->emit8(0xF8+src);
  } else {
    e->emit8(0xDC);
    e->emit8(0xF0+dest);
  }
}

void IA32::FDIVPR(Reg_sti dest, Reg_sti src) {
  if (dest == ST1 && src == ST0) {
    e->emit8(0xDE);
    e->emit8(0xF1);
  } else if (src == ST0) {
    e->emit8(0xDE);
    e->emit8(0xF0+dest);
  }
}

void IA32::FIDIVR(EA mint, IntSize size) {
  switch (size) {
    case Int16:
      e->emit8(0xDE);
      mint.reg = 7;
      emitModRMSIB(e,mint);
      break;
    case Int32:
      e->emit8(0xDA);
      mint.reg = 7;
      emitModRMSIB(e,mint);
      break;
  }
}


void IA32::FINIT() {
  e->emit8(0x9B);
  e->emit8(0xDB);
  e->emit8(0xE3);
}

void IA32::FNINIT() {
  e->emit8(0xDB);
  e->emit8(0xE3);
}

void IA32::FLD(EA mfp, FPSize size) {
  switch (size) {
    case FP32:
      e->emit8(0xD9);
      mfp.reg = 0;
      emitModRMSIB(e,mfp);
      break;
    case FP64:
      e->emit8(0xDD);
      mfp.reg = 0;
      emitModRMSIB(e,mfp);
      break;
    case FP80:
      e->emit8(0xDB);
      mfp.reg = 5;
      emitModRMSIB(e,mfp);
      break;
  }

}

void IA32::FLD(Reg_sti STi) {
  e->emit8(0xD9);
  e->emit8(0xC0+(STi&0x7));
}

void IA32::FLD1() {
  e->emit8(0xD9);
  e->emit8(0xE8);
}

void IA32::FLDL2T() {
  e->emit8(0xD9);
  e->emit8(0xE9);
}

void IA32::FLDL2E() {
  e->emit8(0xD9);
  e->emit8(0xEA);
}

void IA32::FLDPI() {
  e->emit8(0xD9);
  e->emit8(0xEB);
}

void IA32::FLDLG2() {
  e->emit8(0xD9);
  e->emit8(0xEC);
}

void IA32::FLDLN2() {
  e->emit8(0xD9);
  e->emit8(0xED);
}

void IA32::FLDZ() {
  e->emit8(0xD9);
  e->emit8(0xEE);
}

void IA32::FLDCW(EA m2byte) {
  e->emit8(0xD9);
  m2byte.reg = 5;
  emitModRMSIB(e,m2byte);
}

void IA32::FLDENV(EA mem) {
  e->emit8(0xD9);
  mem.reg = 4;
  emitModRMSIB(e,mem);
}

void IA32::FSIN() {
  e->emit8(0xD9);
  e->emit8(0xFE);
}

void IA32::FSINCOS() {
  e->emit8(0xD9);
  e->emit8(0xFB);
}

void IA32::FSQRT() {
  e->emit8(0xD9);
  e->emit8(0xFA);
}

void IA32::FST(EA mfp, FPSize size) {
  switch (size) {
    case FP32:
      e->emit8(0xD9);
      mfp.reg = 2;
      emitModRMSIB(e,mfp);
      break;
    case FP64:
      e->emit8(0xDD);
      mfp.reg = 2;
      emitModRMSIB(e,mfp);
      break;
  }

}

void IA32::FST(Reg_sti STi) {
  e->emit8(0xDD);
  e->emit8(0xD0+STi);
}

void IA32::FSTP(EA mfp, FPSize size) {
  switch (size) {
    case FP32:
      e->emit8(0xD9);
      mfp.reg = 3;
      emitModRMSIB(e,mfp);
      break;
    case FP64:
      e->emit8(0xDD);
      mfp.reg = 3;
      emitModRMSIB(e,mfp);
      break;
    case FP80:
      e->emit8(0xDB);
      mfp.reg = 7;
      emitModRMSIB(e,mfp);
      break;
  }

}

void IA32::FSTP(Reg_sti STi) {
  e->emit8(0xDD);
  e->emit8(0xD8+STi);
}



void IA32::FXAM() {
  e->emit8(0xD9);
  e->emit8(0xE5);
}
void IA32::FXCH(Reg_sti STi) {
  e->emit8(0xD9);
  e->emit8(0xC8+STi);
}

void IA32::FXRSTOR(EA m512byte) {
  e->emit8(0x0F);
  e->emit8(0xAE);
  m512byte.reg = 1;
  emitModRMSIB(e,m512byte);
}

void IA32::FXSAVE(EA m512byte) {
  e->emit8(0x0F);
  e->emit8(0xAE);
  m512byte.reg = 0;
  emitModRMSIB(e,m512byte);
}

void IA32::FXTRACT() {
  e->emit8(0xD9);
  e->emit8(0xF4);
}

void IA32::FYL2X() {
  e->emit8(0xD9);
  e->emit8(0xF1);
}

void IA32::FYL2XP1() {
  e->emit8(0xD9);
  e->emit8(0xF9);
}

void IA32::GETSEC() {
  e->emit8(0x0F);
  e->emit8(0x37);
}

void IA32::HADDPD(Reg_xmm a, EA b) {
  e->emit8(0x66);
  e->emit8(0x0F);
  e->emit8(0x7C);
  b.reg = a;
  emitModRMSIB(e,b);
}

void IA32::VHADDPD(Reg_xmm a, Reg_xmm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,0,1));
  e->emit8(0x7C);
  emitModRMSIB(e,c);
}

void IA32::VHADDPD(Reg_ymm a, Reg_ymm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,1,1));
  e->emit8(0x7C);
  emitModRMSIB(e,c);
}


void IA32::HADDPS(Reg_xmm a, EA b) {
  e->emit8(0xF2);
  e->emit8(0x0F);
  e->emit8(0x7C);
  b.reg = a;
  emitModRMSIB(e,b);
}

void IA32::VHADDPS(Reg_xmm a, Reg_xmm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,0,2));
  e->emit8(0x7C);
  emitModRMSIB(e,c);
}

void IA32::VHADDPS(Reg_ymm a, Reg_ymm b, EA c) {
  c.reg = a;
  e->emit8(PREFIX::VEX2_0());
  e->emit8(PREFIX::VEX2_1(a>>3,b,1,2));
  e->emit8(0x7C);
  emitModRMSIB(e,c);
}

void IA32::INC(Reg32 reg) {
  //e->emit8(
  //emitREX(e);
  e->emit8(0xFF);
  e->emit8(_ModRM(3,0,reg));
}

void IA32::INC(Reg64 reg) {
  e->emit8(PREFIX::REX(1,0,0,reg>>3));
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

void IA32::LOOP(int8_t rel8) {
  e->emit8(0xE2);
  e->emit8(rel8);
}

void IA32::LOOPE(int8_t rel8) {
  e->emit8(0xE1);
  e->emit8(rel8);
}

void IA32::LOOPNE(int8_t rel8) {
  e->emit8(0xE0);
  e->emit8(rel8);
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

void IA32::MOV(Reg64 dest, EA m64) {
  m64.reg = dest;	
  emitREX(e,m64);
  e->emit8(0x8B);
  emitModRMSIB(e,m64);
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

void IA32::MOV(Reg64 dest, uint64_t imm) {
  e->emit8(PREFIX::REX(1,0,0,dest>>3));
	e->emit8(0xB8+(dest&0x7));
	e->emit64(imm);
}

void IA32::MOV(void* dest, Reg32 src) {
  MOV(EA("[disp32]",int32_t(dest)),src);
}

void IA32::MOV(Reg32 dest, void* src) {
  MOV(dest,EA("[disp32]",int32_t(src)));
}

void IA32::MOV(Reg64 dest, void* src) {
  MOV(RSI,(uint64_t)src);
  MOV(dest,EA("[RSI]"));
}

void IA32::MOV(Reg64 dest, Reg64 src) {
  e->emit8(PREFIX::REX(1,dest>>3,0,src>>3));
	e->emit8(0x8B);
	e->emit8(_ModRM(0x3,dest,src));
}

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

void IA32::PUSH(Reg16 reg) {
	e->emit8(0x50+reg);
}

void IA32::PUSH(Reg32 reg) {
	e->emit8(0x50+reg);
}

void IA32::PUSH(Reg64 reg) {
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