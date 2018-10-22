#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

void UARTIntHandler(void)
{
	uint32_t ui32Status;
	
	ui32Status = UART0_IM_R | UART_IM_RXIM | UART_IM_TXIM;
	
	if(ui32Status == UART_IM_RXIM)
	{
		UART0_IM_R &= ~UART_IM_RXIM;
	}
	else if(ui32Status == UART_IM_RXIM)
	{
		UART0_IM_R &= ~UART_IM_RXIM;
	}
}

int main(void)
{
		UART0_CTL_R = UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE;
		
		NVIC_EN0_R = UART0_CTL_R;
	
		while(1);
	
		return 1;
}