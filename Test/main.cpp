#include "../Lib/reccore.h"

int test() {
  return 1;
}

//enum labels { kLoop };
reccore::LabelType kLoop = 0;

int main() {
  
  {
    void asm_test();
    //asm_test();
  }
    
//  auto& a = reccore::intel::ModRM::array;

  int* memarr = (int*)malloc(256*4);
  int* memarr2 = (int*)malloc(256*4);

  int test_num=0x11223300;
  reccore::CodeBlock* block;
  reccore::Emitter e;
  block = e.CreateBlock(0x2000);
  e.set_block(block);
  
  float fp_1 = 0.5f;
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
/*
    //FPU Testing
    ia32.EMMS();
    ia32.FINIT();
    ia32.FLD(EA("[disp32]",(int32_t)&fp_1),FP32);
    ia32.FCOS();
  */

/*
AVX testing*/
    ia32.HADDPD(XMM1,XMM2);
    ia32.VHADDPD(XMM1,XMM2,EA(XMM3));
    ia32.VHADDPD(YMM1,YMM2,EA(YMM3));
    ia32.VADDSUBPD(XMM1,XMM2,EA(XMM3));



/*loop test*/
    ia32.PUSH(ESI);
    ia32.PUSH(EDI);


    
#ifdef _WIN64
    //ia32.LEA(RDI,memarr);
    ia32.MOV(RDI,(uint64_t)memarr);
    ia32.MOV(RSI,(uint64_t)0);
    ia32.MOV(RAX,0x11223344);
    ia32.Label(kLoop);
    ia32.MOV(("[RDI+RSI*4]"),RAX);
    ia32.INC(RSI);
    ia32.CMP(ESI,256);
    ia32.JNE(kLoop);
    ia32.ResolveJumps();
    ia32.MOV(RSI,&memarr[1]);
#endif

    /*ia32.LEA(EDI,memarr);
    ia32.MOV(ESI,(uint32_t)0);
    ia32.MOV(EAX,0x11223344);
    ia32.Label(kLoop);
    //ia32.MOV(("[EDI+ESI*4]"),EAX);
    ia32.INC(ESI);
    ia32.CMP(ESI,256);
    ia32.JNE(kLoop);
    ia32.ResolveJumps();

    ia32.LEA(EDI,memarr2);
    ia32.MOV(EAX,0x55667788);
    ia32.MOV(ECX,0x100);
    ia32.Label(kLoop);
    ia32.MOV(("[EDI+ECX*4+disp8]",-4),EAX);
    ia32.LOOP(kLoop);
    ia32.ResolveJumps();*/

    ia32.POP(EDI);
    ia32.POP(ESI);


    //ia32.MOV(ECX,1234);    
    //ia32.ADD(ECX,0x1);
    //ia32.CMP(ECX,0x20000000);
    //ia32.Jcc(JNE,int8_t(off1-(2+block->cursor)));
    //ia32.ADD(EA(ModRM::kEBX),0x45);
    //ia32.CALL(&test);
    ia32.RET();

    
  }
  
  
  e.ExecuteBlock(block);
  e.DestroyBlock(block);

  free(memarr2);
  free(memarr);

  return 0;
}

