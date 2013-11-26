#include "../Lib/reccore.h"

int test() {
  return 1;
}

enum labels { kLoop };

int main() {
  
  {
    void asm_test();
    //asm_test();
  }
    
//  auto& a = reccore::intel::ModRM::array;

  int* memarr = (int*)malloc(256*4);

  int test_num=0x11223300;
  reccore::CodeBlock* block;
  reccore::Emitter e;
  block = e.CreateBlock(0x2000);
  e.set_block(block);
  {
    using namespace reccore::intel;
    IA32 ia32(&e);
    //ia32.MOV(&test_num,EBX);
    //ia32.MOV(EBX,EA(ModRM::kSIB_p_disp32,SIB::kEAX_m_4,EBP,0x11223344));
    //ia32.PUSH(EA(ModRM::kEAX));
    //ia32.MOV(EAX,0x11223344);
    //ia32.PUSH(EAX);
    //ia32.PUSH(uint8_t(0x11));
    //ia32.JMP(uint8_t(6));
    ia32.VADDPD(YMM1,YMM2,EA(YMM3));
    ia32.PUSH(ESI);
    ia32.PUSH(EDI);

    ia32.LEA(EDI,memarr);
    ia32.MOV(ESI,(uint32_t)0);
    ia32.MOV(EAX,0x11223344);
    ia32.Label(kLoop);
    ia32.MOV(EA("[EDI+ESI*4]"),EAX);
    ia32.INC(ESI);
    ia32.CMP(ESI,256);
    ia32.JNE(kLoop);
    ia32.POP(EDI);
    ia32.POP(ESI);
    //ia32.MOV(ECX,1234);    
    //ia32.ADD(ECX,0x1);
    //ia32.CMP(ECX,0x20000000);
    //ia32.Jcc(JNE,int8_t(off1-(2+block->cursor)));
    //ia32.ADD(EA(ModRM::kEBX),0x45);
    //ia32.CALL(&test);
    ia32.RET();

    ia32.ResolveJumps();
  }
  
  
  e.ExecuteBlock(block);
  e.DestroyBlock(block);

free(memarr);

  return 0;
}

