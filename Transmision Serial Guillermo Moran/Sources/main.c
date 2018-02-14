/* ###################################################################
**     Filename    : main.c
**     Project     : Transmision Serial Guillermo Moran
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-01-18, 10:09, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "TI1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
#include "AS1.h"
#include "AD1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char estado;
unsigned int Enviados = 2;
unsigned int Med;
typedef union{
	unsigned char u8[2];
	unsigned int u16;
}AMPLITUD;

volatile AMPLITUD iADC;

unsigned char trama[15]={0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

byte CodError;



void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;){
	  
	  switch(estado){
	  
	  	  case ESPERAR:
	  		  break;
	  		  
	  	  case MEDIR:
	  		  
	  		CodError = AD1_Measure(TRUE); 
	  		
	  		//Medicion del Potenciometro
	  		
	  		CodError = AD1_GetValue16(&Med);	
	  				  
	  		Med = Med >> 4;
	     	iADC.u16 = (Med & 0x7F) + ((Med & 0xF80)<< 1) ; // mascara de 7 bits
	     	trama[2] = iADC.u8[1];
	     	trama[1] = iADC.u8[0];
	     	estado = ENVIAR;
	     	break;
	     	
	     	
	  	  case ENVIAR:
	  		  
	  		  
	  		  AS1_SendBlock(trama,4,&Enviados);
	  		  estado = ESPERAR;
	  		  break;
	  		  
	  	  default:
	  		  break;
	  		  
	  }
  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
