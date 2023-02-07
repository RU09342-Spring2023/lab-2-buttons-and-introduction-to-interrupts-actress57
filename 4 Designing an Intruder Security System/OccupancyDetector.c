#include <msp430.h>

void gpioInit();

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    gpioInit();                 // Initialize all GPIO Pins for the project


    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    #define i()                 //counter variable



    while(1)
    {

        if (!(P4IN & BIT1))            // If S1 (P4.1) is pressed
        {
            int i = 0                   // initalizes counter to 0

            do
            {                           //do the warning state until 10 seconds pass or button is let go
                P6OUT &= ~BIT6;         //turn off green LED
                P1OUT ^= BIT0;          //toggle red LED

                __delay_cycles(200000);

                i = i + 1;              //Add to counter after every cylce

                if ((P4IN & BIT1))      //If the button is let go before 10 seconds go to Armed
                   {
                       i = 0;
                       break;
                   }

            }while (i < 20);

            do                          // do while/ after its been in warning for 10 seconds
            {
                P1OUT |= BIT0;          //solid red LED

                    if (!(P4IN & BIT1))  //if the button is pressed reset while loop but i cant figure out how yet
                    {
                        i = 0;
                        return;
                    }



            }while (i == 20);



        }


        else
        {
            P1OUT &= ~BIT0;
            P6OUT ^= BIT6;          // Toggle P6.6
            __delay_cycles(3000000);             // Delay for 100000*(1/MCLK)=0.1s
        }

    }




        // BIT3 00001000
        // P2IN 11100000
        //  &   00000000
    /*  if (!(P2IN & BIT3))            // If S2 (P2.3) is pressed (if the button is not not being pressed)
            P6OUT ^= BIT6;          // Toggle P6.6

        if (!(P4IN & BIT1))            // If S1 (P4.1) is pressed
            P1OUT ^= BIT0;          // Toggle P1.0

        __delay_cycles(100000);             // Delay for 100000*(1/MCLK)=0.1s */


    return 0;
}


void gpioInit()
{
   // Setting Directions of Pins

       P1DIR |= BIT0;              // Configure P1.0 to an Output
       P6DIR |= BIT6;              // Configure P6.6 to an Output
       P2DIR &= ~BIT3;             // Configure P2.3 to an Input
       P4DIR &= ~BIT1;             // Configure P4.1 to an Input



   // Configuring Pullup Resistors per MSP430FR2355 Family User Guide
   /*
    *   PXDIR | PXREN | PXOUT | I/O Configuration
    *     0       0       X     Input
    *     0       1       0     Input with Pull Down Resistor
    *     0       1       1     Input With Pull Up Resistor
    *     1       X       X     Output
    */

       P2REN |= BIT3;               // Enable Resistor on P2.3
       P2OUT |= BIT3;               // Configure Resistor on P2.3 to be Pullup

       P4REN |= BIT1;               // Enable Resistor on P4.1
       P4OUT |= BIT1;               // Configure Resistor on P4.1 to be Pullup

}
