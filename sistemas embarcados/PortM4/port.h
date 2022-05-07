//#include "derivative.h" /* include peripheral declarations */

#define NVIC_SYSTICK_CTRL    ((volatile unsigned long *) 0xe000e010)
#define NVIC_SYSTICK_LOAD    ((volatile unsigned long *) 0xe000e014)
#define NVIC_INT_CTRL        ((volatile unsigned long *) 0xe000ed04) //Interrupt control and state register (ICSR)

#define NVIC_SYSTICK_CLK     0x00000004 //BIT4 -> Clock processador
#define NVIC_SYSTICK_INT     0x00000002 //BIT1 -> Hab. interrupção
#define NVIC_SYSTICK_ENABLE  0x00000001 //BIT0 -> Habilitar

#define NVIC_PENDSVSET       0x10000000 //BIT28 -> Habilita Interrupção por software
#define NVIC_PENDSVCLR       0x08000000 //BIT27 -> Limpa a flag de interrupção

/*
APSR       EPSR T:Thumb state bit        ESPR  			ISPR
0 0 0 0 0 | 0 0  1 | 0 0 0 0 |0 0 0 0| 0 0 0 0 0 0| 0 | 0 0 0 0 0 0 0 0 0
							   APSR
*/

#define INITIAL_XPSR 		0x01000000 //BIT24 : Thumb State bit  ESTA CORRETO ??

typedef unsigned long cpu_t;

extern cpu_t *stk_tmp;

void init_os_timer(void);

cpu_t *PrepareStack(void *task, cpu_t *stk, int stk_size);

#define dispatcher() __asm(									    	\
							"cpsie i               \n"				\
							"svc 0                 \n"				\
	     				  )

#define SAVE_CONTEXT() __asm( 							    		\
								"MRS   R0, PSP           \n"        \
								"SUBS  R0, R0, #0X20     \n"        \
								"STM   R0, {R4-R11}      \n"        \
							)

#define RESTORE_CONTEXT() __asm(									\
								"LDM    R0, {R4-R11}     \n"	    \
								"ADDS   R0, R0, #0x20    \n"        \
								"MSR    PSP, R0          \n"        \
								"LDR    LR, =0xFFFFFFFD  \n"        \
								"CPSIE  I                \n"        \
								"BX     LR               \n"        \
							    )

#define SAVE_SP() __asm( "LDR R1, =stk_tmp     \n"                 \
						 "STR R0, [R1]         \n"                 \
						)

#define RESTORE_SP() __asm( "LDR R1, =stk_tmp     \n"              \
		 	 	 	 	    "LDR R0, [R1]         \n"              \
						  )

#define Clear_PendSV() *(NVIC_INT_CTRL) = NVIC_PENDSVCLR

#define yield() *(NVIC_INT_CTRL) |=  NVIC_PENDSVSET // = ou |=  ??

