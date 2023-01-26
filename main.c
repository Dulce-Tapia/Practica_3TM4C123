#include "lib/include.h"
// pines tx - pc6
//       rx - pc7
int main(void)
{ 
    //int valor;
    char c='5';
    int tam=100; //arreglo tamaño
    char Nombre[tam]; //guardar nombre
    Configurar_PLL(_80MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART3();
    Configurar_GPIO();
    
    //char string= readString('&'); //solo lee comillas no la letra 
    //printString(string);
      

    while (1)
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
             case 'x': 
                 GPIOF->DATA = (1<<2) | (1<<3); //indicador 
                 tam=readString('.',&Nombre[0]);
                 Invertir(&Nombre[0],tam);
                 printString(&Nombre[0]);
                break; 
         }
    }
    
}

