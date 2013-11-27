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

  void ADC(Reg8 dest, uint8_t imm);
  void ADC(Reg16 dest, uint16_t imm);
  void ADC(Reg32 dest, uint32_t imm);
  void ADC(Reg64 dest, uint32_t imm);
  void ADC(EA rm, uint8_t imm);
  void ADC(EA rm, uint16_t imm);
  void ADC(EA rm, uint32_t imm);
  void ADC(EA rm, Reg8 reg);
  void ADC(EA rm, Reg16 reg);
  void ADC(EA rm, Reg32 reg);
  void ADC(EA rm, Reg64 reg);
  void ADC(Reg8 reg, EA rm);
  void ADC(Reg16 reg, EA rm);
  void ADC(Reg32 reg, EA rm);
  void ADC(Reg64 reg, EA rm);

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

  void ADDSD(Reg_xmm a, EA b);
  void VADDSD(Reg_xmm a, Reg_xmm b, EA c);

  void ADDSS(Reg_xmm a, EA b);
  void VADDSS(Reg_xmm a, Reg_xmm b, EA c);

  void ADDSUBPD(Reg_xmm a, EA b);
  void VADDSUBPD(Reg_xmm a, Reg_xmm b, EA c);
  void VADDSUBPD(Reg_ymm a, Reg_ymm b, EA c);

  void AND(Reg8 dest, uint8_t imm);
  void AND(Reg16 dest, uint16_t imm);
  void AND(Reg32 dest, uint32_t imm);
  void AND(Reg64 dest, uint32_t imm);
  void AND(EA rm, uint8_t imm);
  void AND(EA rm, uint16_t imm);
  void AND(EA rm, uint32_t imm);
  void AND(EA rm, Reg8 reg);
  void AND(EA rm, Reg16 reg);
  void AND(EA rm, Reg32 reg);
  void AND(EA rm, Reg64 reg);
  void AND(Reg8 reg, EA rm);
  void AND(Reg16 reg, EA rm);
  void AND(Reg32 reg, EA rm);
  void AND(Reg64 reg, EA rm);

  void CALL(uint16_t rel16);
  void CALL(uint32_t rel32);
  void CALL(void* ptr);

  void CMP(Reg32 reg, uint32_t imm32);

  void EMMS();

  void F2XM1();
  void FABS();
  void FADD(EA mfp, FPSize size);
  void FADD(Reg_sti dest, Reg_sti src);
  void FADDP(Reg_sti dest, Reg_sti src);
  void FIADD(EA mint, IntSize size);
  void FBLD(EA m80dec);
  void FBSTP(EA m80bcd);
  void FCHS();
  void FCLEX();
  void FNCLEX();
  void FCOMI(Reg_sti STi);
  void FCOMIP(Reg_sti STi);
  void FUCOMI(Reg_sti STi);
  void FUCOMIP(Reg_sti STi);
  void FCOS();
  void FDIV(EA mfp, FPSize size);
  void FDIV(Reg_sti dest, Reg_sti src);
  void FDIVP(Reg_sti dest, Reg_sti src);
  void FIDIV(EA mint, IntSize size);
  void FDIVR(EA mfp, FPSize size);
  void FDIVR(Reg_sti dest, Reg_sti src);
  void FDIVPR(Reg_sti dest, Reg_sti src);
  void FIDIVR(EA mint, IntSize size);
  void FINIT();
  void FNINIT();
  void FLD(EA mfp, FPSize size);  
  void FLD(Reg_sti STi);
  void FLD1();
  void FLDL2T();
  void FLDL2E();
  void FLDPI();
  void FLDLG2();
  void FLDLN2();
  void FLDZ();
  void FLDCW(EA m2byte);
  void FLDENV(EA mem);
  void FSIN();
  void FSINCOS();
  void FSQRT();
  void FST(EA mfp, FPSize size);
  void FST(Reg_sti STi);
  void FSTP(EA mfp, FPSize size);
  void FSTP(Reg_sti STi);
  void FXAM();
  void FXCH(Reg_sti STi);
  void FXRSTOR(EA m512byte);
  void FXSAVE(EA m512byte);
  void FXTRACT();
  void FYL2X();
  void FYL2XP1();

  void GETSEC();

  void HADDPD(Reg_xmm a, EA b);
  void VHADDPD(Reg_xmm a, Reg_xmm b, EA c);
  void VHADDPD(Reg_ymm a, Reg_ymm b, EA c);


  void HADDPS(Reg_xmm a, EA b);
  void VHADDPS(Reg_xmm a, Reg_xmm b, EA c);
  void VHADDPS(Reg_ymm a, Reg_ymm b, EA c);

  void INC(Reg32 reg);
  void INC(Reg64 reg);

  void Jcc(JumpCode cc, int8_t rel8);
  void Jcc(JumpCode cc, int16_t rel16);
  void Jcc(JumpCode cc, int32_t rel32);

  void JA(LabelType label) {
    Jcc(kJA,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JAE(LabelType label) {
    Jcc(kJAE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JB(LabelType label) {
    Jcc(kJB,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JBE(LabelType label) {
    Jcc(kJBE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JC(LabelType label) {
    Jcc(kJC,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JE(LabelType label) {
    Jcc(kJE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JG(LabelType label) {
    Jcc(kJG,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JGE(LabelType label) {
    Jcc(kJGE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JL(LabelType label) {
    Jcc(kJL,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JLE(LabelType label) {
    Jcc(kJLE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNA(LabelType label) {
    Jcc(kJNA,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNAE(LabelType label) {
    Jcc(kJNAE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNB(LabelType label) {
    Jcc(kJNB,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNBE(LabelType label) {
    Jcc(kJNBE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNC(LabelType label) {
    Jcc(kJNC,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNE(LabelType label) {
    Jcc(kJNE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNG(LabelType label) {
    Jcc(kJNG,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNGE(LabelType label) {
    Jcc(kJNGE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNL(LabelType label) {
    Jcc(kJNL,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNLE(LabelType label) {
    Jcc(kJNLE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNO(LabelType label) {
    Jcc(kJNO,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNP(LabelType label) {
    Jcc(kJNP,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNS(LabelType label) {
    Jcc(kJNS,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JNZ(LabelType label) {
    Jcc(kJNZ,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JO(LabelType label) {
    Jcc(kJO,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JP(LabelType label) {
    Jcc(kJP,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JPE(LabelType label) {
    Jcc(kJPE,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JPO(LabelType label) {
    Jcc(kJPO,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JS(LabelType label) {
    Jcc(kJS,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void JZ(LabelType label) {
    Jcc(kJZ,int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }

  void JMP(int8_t rel8);
  void JMP(int16_t rel16);
  void JMP(int32_t rel32);

  void JMP(LabelType label) {
    JMP(int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }

  

  void LEA(Reg16 r16, EA mem);
  void LEA(Reg32 r32, EA mem);
  void LEA(Reg64 r64, EA mem);
  void LEA(Reg32 r32, void* ptr);

  void LOOP(int8_t rel8);
  void LOOPE(int8_t rel8);
  void LOOPNE(int8_t rel8);
  void LOOP(LabelType label){
    LOOP(int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void LOOPE(LabelType label){
    LOOPE(int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }
  void LOOPNE(LabelType label) {
    LOOPNE(int8_t(0xFF));
    jumps[jump_counter++] = {0,label,e->GetCursor()-1};
  }


  void MOV(EA m8, Reg8 src);
  void MOV(EA m16, Reg16 src);
  void MOV(EA m32, Reg32 src);
  void MOV(EA m64, Reg64 src);
  void MOV(Reg8 dest, EA m8);
  void MOV(Reg16 dest, EA m16);
  void MOV(Reg32 dest, EA m32);
  void MOV(Reg64 dest, EA m64);
  void MOV(Reg8 dest, Reg8 src);
  void MOV(Reg16 dest, Reg16 src);
  void MOV(Reg32 dest, Reg32 src);
  void MOV(Reg8 dest, uint8_t imm);
  void MOV(Reg16 dest, uint16_t imm);
  void MOV(Reg32 dest, uint32_t imm);
  void MOV(Reg64 dest, uint64_t imm);
  void MOV(void* dest, Reg32 src);
  void MOV(Reg32 dest, void* src);
  void MOV(Reg64 dest, void* src);
  void MOV(Reg64 dest, Reg64 src);

  void NOP();

  void POP(Reg32 reg);

  void PUSH(EA mem); 
  void PUSH(Reg16 reg);
  void PUSH(Reg32 reg);
  void PUSH(Reg64 reg);
  void PUSH(uint8_t imm);
  void PUSH(uint16_t imm);
  void PUSH(uint32_t imm);

  void RET(bool farreturn=false);

  //call if using labels, preferebly only call once after finishing writing to the  block
  //todo , 16bit and 32bit offsets
  void ResolveJumps() {
    for each (auto jump in jumps) {
      auto item = jump.second;
      switch (item.size) {
        case 0 :  {
            uint8_t offset = int8_t(labels[item.label]-(1+item.cursor));
            e->block()->ptr8bit[item.cursor] = offset; 
           break;
        }
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