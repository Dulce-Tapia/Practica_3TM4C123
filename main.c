#include "lib/include.h"

int main(void)
{ 
    int valor;
    char c='5';
    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART3();
    Configurar_GPIO();
    
    char string= readString('&'); //solo lee comillas no la letra 
    //printString(string);
      

    /*while (1)
    {
        c = readChar();

         switch(c)
         {
             case 'r':
                 //GPIODATA port F 662
                 printChar('a');
                 GPIOF->DATA = (1<<1);
                 break;
             case 'b':
                 //GPIODATA port F 662
                 printChar('b');
                 GPIOF->DATA = (1<<2);
                 break;
             case 'g':
                 //GPIODATA port F 662
                 printChar('c');
                 GPIOF->DATA = (1<<3);
                 break;
             case 'y':
                 //GPIODATA port F 662
                 printChar('d');
                 GPIOF->DATA = (1<<3) | (1<<2);
                 break;
             default:
                 printChar((char)valor);
                 GPIOF->DATA = (0<<1) | (0<<2) | (0<<3);
                 break;
         }
    }*/
    
}

