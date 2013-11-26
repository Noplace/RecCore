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
#pragma once

namespace reccore {
namespace intel {



class IA32 : public InstructionSet {
 public:
  inline int8_t offset8(SIZE_T bytes) {
    return int8_t(bytes-(2+e->block()->cursor));
  }

	IA32(Emitter* pEmitter) : InstructionSet(pEmitter) {

  }
  virtual ~IA32() {

  }

  

  void AAA();
  void AAD();
  void AAM();
  void AAS();

  void ADD(Reg8 dest, uint8_t imm);
  void ADD(Reg16 dest, uint16_t imm);
  void ADD(Reg32 dest, uint32_t imm);
  void ADD(Reg64 dest, uint32_t imm);
  void ADD(EA rm, uint8_t imm);
  void ADD(EA rm, uint16_t imm);
  void ADD(EA rm, uint32_t imm);
  void ADD(EA rm, Reg8 reg);
  void ADD(EA rm, Reg16 reg);
  void ADD(EA rm, Reg32 reg);
  void ADD(EA rm, Reg64 reg);
  void ADD(Reg8 reg, EA rm);
  void ADD(Reg16 reg, EA rm);
  void ADD(Reg32 reg, EA rm);
  void ADD(Reg64 reg, EA rm);

  void ADDPD(Reg_xmm a, EA b);
  void VADDPD(Reg_xmm a, Reg_xmm b, EA c);
  void VADDPD(Reg_ymm a, Reg_ymm b, EA c);

  void ADDPS(Reg_xmm a, EA b);
  void VADDPS(Reg_xmm a, Reg_xmm b, EA c);
  void VADDPS(Reg_ymm a, Reg_ymm b, EA c);


  void CALL(uint16_t rel16);
  void CALL(uint32_t rel32);
  void CALL(void* ptr);

  void CMP(Reg32 reg, uint32_t imm32);
  

  void INC(Reg32 reg);

  void Jcc(JumpCode cc, int8_t rel8);
  void Jcc(JumpCode cc, int16_t rel16);
  void Jcc(JumpCode cc, int32_t rel32);

  void JNE(const int label) {
    Jcc(kJNE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }

  void JMP(int8_t rel8);
  void JMP(int16_t rel16);
  void JMP(int32_t rel32);

  void LEA(Reg16 r16, EA mem);
  void LEA(Reg32 r32, EA mem);
  void LEA(Reg64 r64, EA mem);
  void LEA(Reg32 r32, void* ptr);

  void MOV(EA m8, Reg8 src);
  void MOV(EA m16, Reg16 src);
  void MOV(EA m32, Reg32 src);
  void MOV(EA m64, Reg64 src);
  void MOV(Reg8 dest, EA m8);
  void MOV(Reg16 dest, EA m16);
  void MOV(Reg32 dest, EA m32);
  void MOV(Reg8 dest, Reg8 src);
  void MOV(Reg16 dest, Reg16 src);
  void MOV(Reg32 dest, Reg32 src);
  void MOV(Reg8 dest, uint8_t imm);
  void MOV(Reg16 dest, uint16_t imm);
  void MOV(Reg32 dest, uint32_t imm);
  //void MOV(Reg64 dest, uint64_t imm);
  void MOV(void* dest, Reg32 src);
  void MOV(Reg32 dest, void* src);
  //void MOV(Reg64 dest, Reg64 src);

  void NOP();

  void POP(Reg32 reg);

  void PUSH(EA mem); 
  void PUSH(Reg32 reg);
  void PUSH(uint8_t imm);
  void PUSH(uint16_t imm);
  void PUSH(uint32_t imm);

  void RET(bool farreturn=false);

  //call if using labels, should only be called once before ExecuteBlock
  void ResolveJumps() {
    for each (auto jump in jumps) {
      auto item = jump.second;
      switch (item.size) {
        case 0 : e->block()->ptr8bit[item.cursor] = offset8(labels[item.label]); break;
        //case 1 : e->block()->ptr8bit[item.cursor] = offset16(labels[item.label]); break;
        //case 2 : e->block()->ptr8bit[item.cursor] = offset32(labels[item.label]); break;
        
      }
    }
    jumps.clear();
    labels.clear();
    jump_counter = 0;
    
  }
 private:

  /*__inline uint8_t WriteBitAt(uint8_t bit,uint8_t index)  {
	  bit&=0x1;
	  return (bit<<index);
  }

  __inline uint8_t WriteBitsAt(uint8_t bits,uint8_t count,uint8_t index)  {
	  bits&=((1<<count)-1);
	  return (bits<<index);
  }

  __inline uint8_t ModRM(uint8_t mod,uint8_t reg,uint8_t rm)  {
	  return (((mod&0x3)<<6)|((reg&0x7)<<3)|((rm&0x7)));
  }

  __inline uint8_t SIB(uint8_t scale,uint8_t index,uint8_t base)  {
	  return (((scale&0x3)<<6)|((index&0x7)<<3)|((base&0x7)));
  }*/
};

}
}