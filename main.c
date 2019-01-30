

/**
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void Timer0IntHandler();

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    int i = SysCtlClockGet();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); //Enable Timer0 as peripheral

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)); //Wait for Timer0 module to be ready

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    TimerClockSourceSet(TIMER0_BASE, SysCtlClockGet()); //Set Timer0 clock source to precision internal oscillator
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); //Configure Timer0-TimerA to be a periodic timer

    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //Timer0-TimerA timeout interrupt

    TimerLoadSet(TIMER0_BASE, TIMER_A, 25000000); //Set period for TimerA

    IntEnable(INT_TIMER0A); //Enable Timer0-TimerA enable
    IntPrioritySet(INT_TIMER0A, 18); //Set Timer0-TimerA priority level

    TimerEnable(TIMER0_BASE, TIMER_A); //Enable Timer0-TimerA

    IntMasterEnable();

    while(1);

	return 0;
}

void Timer0IntHandler()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //clear Timer0-TimerA timeout interrupt

    UARTCharPut(UART0_BASE, 'A');
}
