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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //Configure UART0
    //Specify baud rate = 115200
    //8 data bits, 1 stop bit, no parity bit
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    //Configure UART1
    //Specify baud rate = 115200
    //8 data bits, 1 stop bit, no parity bit
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
                         (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX7_8, UART_FIFO_RX4_8);

    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX1_8, UART_FIFO_RX4_8);

    //Enable UART interrupt
    IntEnable(INT_UART1);

    UARTEnable(UART1_BASE);

    UARTCharPut(UART1_BASE, 0X42);
    UARTCharPut(UART1_BASE, 0X57);
    UARTCharPut(UART1_BASE, 0X02);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X01);
    UARTCharPut(UART1_BASE, 0X02);

    UARTCharPut(UART1_BASE, 0X42);
    UARTCharPut(UART1_BASE, 0X57);
    UARTCharPut(UART1_BASE, 0X02);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X04);
    UARTCharPut(UART1_BASE, 0X06);

    UARTCharPut(UART1_BASE, 0X42);
    UARTCharPut(UART1_BASE, 0X57);
    UARTCharPut(UART1_BASE, 0X02);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X00);
    UARTCharPut(UART1_BASE, 0X14);

    UARTCharPut(UART1_BASE, 0X42);
      UARTCharPut(UART1_BASE, 0X57);
      UARTCharPut(UART1_BASE, 0X02);
      UARTCharPut(UART1_BASE, 0X00);
      UARTCharPut(UART1_BASE, 0X00);
      UARTCharPut(UART1_BASE, 0X00);
      UARTCharPut(UART1_BASE, 0X00);
      UARTCharPut(UART1_BASE, 0X02);

    //Enable UART
    UARTEnable(UART0_BASE);
    UARTIntEnable(UART0_BASE, UART_INT_RX);

    UARTIntEnable(UART1_BASE, UART_INT_RX);

    while(1);

	//return 0;
}

void UARTIntHandler(void)
{
    UARTIntClear(UART1_BASE, UART_INT_RX);

    int i = 0;
    //int character = 0;

    while(UARTCharsAvail(UART1_BASE) || i < 10)
    {
        //character = 0x30 + UARTCharGet(UART1_BASE);
        UARTCharPut(UART0_BASE, UARTCharGet(UART1_BASE));
        i++;
    }

    //IntDisable(INT_UART1);
}
