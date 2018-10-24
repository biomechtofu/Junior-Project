/**
 * Andrew Kwok
 * Junior Project Testing
 * Oregon Institute of Technology
 *
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc./tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //Configure UART
    //Specify baud rate = 115200
    //8 data bits, 1 stop bit, no parity bit
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTFIFODisable(UART0_BASE);
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX7_8, UART_FIFO_RX1_8);

    //Enable UART interrupt
    IntEnable(INT_UART0);

    //Enable UART
    UARTEnable(UART0_BASE);
    UARTIntEnable(UART0_BASE, UART_INT_RX);

    while(1);

	//return 0;
}

void UARTIntHandler(void)
{
    UARTIntClear(UART0_BASE, UART_INT_RX);

    while(UARTCharsAvail(UART0_BASE))
    {
        UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE));
    }
}
