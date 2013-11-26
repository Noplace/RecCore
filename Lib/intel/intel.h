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

enum OMode{_64Bit=0,_32Bit=1,_16Bit=1,_8Bit=0};
enum IAMode{Compat_Leg_Mode,x64_Mode,_FP,_SSE,_MMX,_VMX};

enum Granularity{PackedBytes=0,PackedWords=1,PackedDoublewords=2,Quadword=3};


enum Reg8{AL,CL,DL,BL,AH,CH,DH,BH,R8L,R9L,R10L,R11L,R12L,R13L,R14L,R15L};
enum Reg16{AX,CX,DX,BX,SP,BP1,SI,DI,R8W,R9W,R10W,R11W,R12W,R13W,R14W,R15W};
enum Reg32{EAX,ECX,EDX,EBX,ESP,EBP,ESI,EDI,R8D,R9D,R10D,R11D,R12D,R13D,R14D,R15D,SIBDisp=5};
enum Reg64{RAX,RCX,RDX,RBX,RSP,RBP,RSI,RDI,R8,R9,R10,R11,R12,R13,R14,R15};
enum Reg_mm{MM0,MM1,MM2,MM3,MM4,MM5,MM6,MM7};
enum Reg_xmm{XMM0,XMM1,XMM2,XMM3,XMM4,XMM5,XMM6,XMM7,XMM8,XMM9,XMM10,XMM11,XMM12,XMM13,XMM14,XMM15};
enum Reg_ymm{YMM0,YMM1,YMM2,YMM3,YMM4,YMM5,YMM6,YMM7,YMM8,YMM9,YMM10,YMM11,YMM12,YMM13,YMM14,YMM15};
enum Reg_eee{CR0=0,CR2=2,CR3=3,CR4=4,DR0=0,DR1=1,DR2=2,DR3=3,DR6=6,DR7=7};
enum Reg_sreg{ES,CS,SS,DS,FS,GS};

enum JumpCode {
kJA = 0x7,
kJAE = 0x3,
kJB = 0x2,
kJBE = 0x6,
kJC = 0x2,
kJCXZ = 0x0,
kJECXZ = 0x0,
kJRCXZ = 0x0,
kJE = 0x4,
kJG = 0xF,
kJGE = 0xD,
kJL = 0xC,
kJLE = 0xE,
kJNA = 0x6,
kJNAE = 0x2,
kJNB = 0x3,
kJNBE = 0x7,
kJNC = 0x3,
kJNE = 0x5,
kJNG = 0xE,
kJNGE = 0xC,
kJNL = 0xD,
kJNLE = 0xF,
kJNO = 0x1,
kJNP = 0xB,
kJNS = 0x9,
kJNZ = 0x5,
kJO = 0x0,
kJP = 0xA,
kJPE = 0xA,
kJPO = 0xB,
kJS = 0x8,
kJZ = 0x4,

};

struct Jump	{
	enum ConditionCode {A,AE,B,BE,C,E,Z,G,GE,L,LE,NA,NAE,NB,NBE,NC,NE,NG,NGE,NL,NLE,NO,NP,NS,NZ,O,P,PE,PO,S};
	static const uint32_t UnknownAddress = 0xfefefefe;
	static const uint8_t NOT = 1;
	enum ttt{Overflow=0,Below=1,NotAbove_Or_Equal=1,Equal=2,Zero=2,Below_Or_Equal=3,NotAbove=3,Sign=4,Parity=5,Parity_Even=5,LessThan=6,NotGreaterThan_Or_EqualTo=6,LessThan_Or_EqualTo=7,NotGreaterThan=7};
};


namespace PREFIX {
namespace Group1 {
	const uint8_t LOCK = 0xF0;
	const uint8_t REPNE=0xF2;
	const uint8_t REPNZ=REPNE;
	const uint8_t REP=0xF3;
	const uint8_t REPE=REP;
	const uint8_t REPZ=REP;
}
namespace Group2 {
	const uint8_t CS_OVERRIDE=0x2E;
	const uint8_t SS_OVERRIDE=0x36;
	const uint8_t DS_OVERRIDE=0x3E;
	const uint8_t ES_OVERRIDE=0x26;
	const uint8_t FS_OVERRIDE=0x64;
	const uint8_t GS_OVERRIDE=0x65;
	const uint8_t BRANCH_NOT_TAKEN=0x2E;
	const uint8_t BRANCH_TAKEN=0x3E;
}
namespace Group3 {
	const uint8_t OPERAND_SIZE_OVERRIDE=0x66;
}
namespace Group4 {
	const uint8_t ADDRESS_SIZE_OVERRIDE=0x67;
}

__inline uint8_t REX(uint8_t W,uint8_t R,uint8_t X,uint8_t B) {
	return 0x40|((W&0x1)<<3)|((R&0x1)<<2)|((X&0x1)<<1)|((B&0x1));
}

__inline uint8_t VEX3_0() {
  return 0xC4;
}

__inline uint8_t VEX3_1(uint8_t R,uint8_t X,uint8_t B,uint8_t mmmmm) {
  R = ~R;
  X = ~X;
  B = ~B;
  return ((R&0x1)<<7)|((X&0x1)<<6)|((B&0x1)<<5)|((mmmmm&0x1F));
}

__inline uint8_t VEX3_2(uint8_t W,uint8_t vvvv,uint8_t L,uint8_t pp) {
  vvvv = ~vvvv;
  return ((W&0x1)<<7)|((vvvv&0xF)<<3)|((L&0x1)<<2)|((pp&0x3));
}

__inline uint8_t VEX2_0() {
  return 0xC5;
}

__inline uint8_t VEX2_1(uint8_t R,uint8_t vvvv,uint8_t L,uint8_t pp) {
  R = ~R;
  vvvv = ~vvvv;
  return ((R&0x1)<<7)|((vvvv&0xF)<<3)|((L&0x1)<<2)|((pp&0x3));
}

}


}
}
#include "addressing.h"
#include "ia32.h"