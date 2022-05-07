#include "os.h"
#include "stdint.h"

cpu_t *stk_tmp;

cpu_t *PrepareStack(void *task, cpu_t *stk, int stk_size){

  stk = (cpu_t*)((int)stk + stk_size);


  *stk-- = (cpu_t)INITIAL_XPSR;            // xPSR

  *stk-- = (cpu_t)task;					   // PC

  *stk-- = 0;							   // LR
  *stk-- = (cpu_t)0x12121212u; 			   // R12
  *stk-- = (cpu_t)0x03030303u; 			   // R3
  *stk-- = (cpu_t)0x02020202u; 			   // R2
  *stk-- = (cpu_t)0x01010101u;             // R1
  *stk-- = (cpu_t)0; 		        	   // R0

  /*
#if FPU_ENABLE == 1
  *stk-- = (cpu_t)0xFFFFFFFDu; 		       // LR
#endif
*/
  *stk-- = (cpu_t)0x11111111u; 		       // R11
  *stk-- = (cpu_t)0x10101010u; 		       // R10
  *stk-- = (cpu_t)0x09090909u; 		       // R9
  *stk-- = (cpu_t)0x08080808u; 		       // R8
  *stk-- = (cpu_t)0x07070707u; 		       // R7
  *stk-- = (cpu_t)0x06060606u; 		       // R6
  *stk-- = (cpu_t)0x05050505u; 		       // R5
  *stk-- = (cpu_t)0x04040404u; 		       // R4
  *stk-- = (cpu_t)0x03030303u; 		       // R3

   return stk;
}

//SWITCH CONTEXT
__attribute__ ((naked)) void PendSV_Handler(void){ //Naked -> interrupção não salva registradores na pilha

  SAVE_CONTEXT();
  SAVE_SP();

  Clear_PendSV();

  current_task->stk=stk_tmp;
  stk_tmp = scheduler();

  RESTORE_SP();
  RESTORE_CONTEXT();
}

__attribute__ ((naked)) void SVC_Handler(void){

	/* Faz com que pendsv e systick tenham menor prioridade
	*(NVIC_SYSPRI3) |= NVIC_PENDSV_PRI;
	*(NVIC_SYSPRI3) |= NVIC_SYSTICK_PRI;*/

	RESTORE_SP();
	SAVE_SP();

}

//Timer interno ao processador
void init_os_timer(void){

  uint32_t cpu_clock_hz = 120000000;                  		 //Clock do sistema = 120MHz
  uint32_t valor_comparador = cpu_clock_hz / 1000;  		 //tempo para interrupção = 1ms

  *(NVIC_SYSTICK_CTRL) = 0;                         		//Desabilita para configurar o ST-Timer
  *(NVIC_SYSTICK_LOAD) = valor_comparador - 1u;     		//Módulo de contagem
  *(NVIC_SYSTICK_CTRL) = NVIC_SYSTICK_CLK | NVIC_SYSTICK_INT | NVIC_SYSTICK_ENABLE ; //Liga: Clock do proc, Interrupção e contagem
}

// Interrupção de timer
__attribute__ ((naked)) void SysTick_Handler(void){
  //TPM1SC_TOF = 0;

  if(os_inc_and_compare()){
    SAVE_CONTEXT();
    SAVE_SP();

    current_task->stk=stk_tmp;
    stk_tmp = scheduler();

    RESTORE_SP();
    RESTORE_CONTEXT();
  }

}
