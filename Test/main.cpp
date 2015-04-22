#include "../Lib/reccore.h"

int test(int a,int b) {
  return a+b;
}

//enum labels { kLoop };
reccore::LabelType kLoop = 0;

template<typename T1, typename T2>
auto sum(T1 & t1, T2 & t2) -> decltype(t1 + t2){
return t1 + t2;
}

int main() {


  
  {
    void asm_test();
    void aes_test();
    //aes_test();
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

   // ia32.ENTER(200,10);

    //ia32.MOV(EAX,EA("[EBP+disp8]",8));    
    //ia32.ADD(EAX,EA("[EBP+disp8]",12));
    

/*
    //FPU Testing
    ia32.EMMS();
    ia32.FINIT();
    ia32.FLD(EA("[disp32]",(int32_t)&fp_1),FP32);
    ia32.FCOS();
  */
  ia32.PCLMULQDQ(XMM1,XMM2,81);
  ia32.VPCLMULQDQ(XMM1,XMM2,EA("[EAX]"),81);
/*
AVX testing/SSE*/
  //ia32.VFMADD132PD(XMM1,XMM2,XMM3);
    //ia32.EXTRACTPS(EAX,XMM1,12);
    //ia32.VEXTRACTPS(EAX,XMM1,12);
  //ia32.VMOVAPD(XMM1,EA(XMM2));
 // ia32.VMOVAPD(EA("[EAX]"),XMM3);

   /* ia32.HADDPD(XMM1,XMM2);
    ia32.VHADDPD(XMM1,XMM2,EA(XMM3));
    ia32.VHADDPD(YMM1,YMM2,EA(YMM3));
    ia32.VADDSUBPD(XMM1,XMM2,EA(XMM3));
    ia32.LDDQU(XMM1,EA("[EAX]"));
    ia32.VLDDQU(XMM1,EA("[EAX]"));
    ia32.VLDDQU(YMM1,EA("[EAX]"));*/



/*loop test*/
    
    //ia32.PUSHAD();


    
#ifdef _WIN64
    //ia32.LEA(RDI,memarr);
    ia32.MOV(EA("[RAX+R9]"),RAX);
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
/*
    ia32.LEA(EDI,memarr);
    ia32.MOV(ESI,(uint32_t)0);
    ia32.MOV(EAX,0x11223344);
    ia32.Label(kLoop);
    ia32.MOV(EA("[EDI+ESI*4]"),EAX);
    ia32.INC(ESI);
    ia32.CMP(ESI,256);
    ia32.JNE(kLoop);
    ia32.ResolveJumps();

    ia32.LEA(EDI,memarr2);
    ia32.MOV(EAX,0x55667788);
    ia32.MOV(ECX,0x100);
    ia32.Label(kLoop);
    ia32.MOV(EA("[EDI+ECX*4+disp8]",-4),EAX);
    ia32.LOOP(kLoop);
    ia32.ResolveJumps();*/

    //ia32.POPAD();
  

    //ia32.MOV(ECX,1234);    
    //ia32.ADD(ECX,0x1);
    //ia32.CMP(ECX,0x20000000);
    //ia32.Jcc(JNE,int8_t(off1-(2+block->cursor)));
    //ia32.ADD(EA(ModRM::kEBX),0x45);
    //ia32.CALL(&test);
    //ia32.LEAVE();
    ia32.RET();
  }

  //int r = (*block)(200,480);
	auto func	= static_cast<int (*)(int a,int b)>(block->address);
	int result = func(200,480);
  
  //e.ExecuteBlock(block);
  e.DestroyBlock(block);

  free(memarr2);
  free(memarr);

  return 0;
}

