#include <xmmintrin.h>
#include <immintrin.h>

int* memarr;

void test_func1() {

}
int test_num=0x11223300;
void asm_test() {
  
  /*long long x = 0x1234123412341234;
  ++x;

  long long y = x;*/
  //auto m = _mm256_set_ps(4.0, 3.0, 2.0, 1.0,8,7,6,5);
memarr = (int*)malloc(256*4);
for (int i=0;i<256;++i)
memarr[i] = 0x11223344;

#ifndef _WIN64
  _asm {
    /*lea edi,memarr
    mov esi,2
    mov eax,0x11223344
    mov [EDI+ESI*2],eax
*/
    vaddps xmm1, xmm2 , xmm3

    //cmp ecx,0x20000000
    //mov ebx , [test_num]
    //add [ebx],0x45
   // mov ebx,[EBP+ESI*8+0xF8]
    //push [eax]
    //call test_func1
  }
#endif
free(memarr);
}