#include "lib/include.h"

extern void Configurar_UART3(void)
{
    SYSCTL->RCGCUART  = (1<<3);   //Paso 1 (RCGCUART) pag.344 UART/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<2);     //Paso 2 (RCGCGPIO) pag.340 Enable clock port A
    //(GPIOAFSEL) pag.671 Enable alternate function
    GPIOC->AFSEL = (1<<6) | (1<<7);
    //GPIO Port Control (GPIOPCTL) PC6-> U3Rx PC7-> U3Tx pag.688
    GPIOC->PCTL = (GPIOC->PCTL&0x11FFFFFF) | 0x11000000;// (1<<0) | (1<<4);//0x00000011
    // GPIO Digital Enable (GPIODEN) pag.682
    GPIOC->DEN = (1<<6) | (1<<7);//PA1 PA0
    //UART0 UART Control (UARTCTL) pag.918 DISABLE!!
    UART3->CTL = (0<<9) | (0<<8) | (0<<0);

    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 80,000,000 / (16 * 19200) = 260.4166667
    UARTFBRD[DIVFRAC] = integer(0.4166667 * 64 + 0.5) = 27
    */
    UART3->IBRD = 260;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART3->FBRD = 27;
    //  UART Line Control (UARTLCRH) pag.916
    UART3->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART3->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART3->CTL = (1<<0) | (1<<8) | (1<<9);
}


extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART3->FR & (1<<4)) != 0 );
    v = UART3->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART3->FR & (1<<5)) != 0 );
    UART3->DR = c;
}
extern void printString(char* string)
{
    int i=0;
    while( string[i]>47) //Nota. Se inicia a partir de 48 se inicia los números en ASCII
    {
        printChar(string[i]);
        i++;
    }
}

extern int readString(char delimitador, char *string) //tamaño del palabra
{

   int i=0;
   char c = readChar();
   while(c != delimitador)
   {
       string[i] = c;
       i++;
       c = readChar();
   }

   return i;
}

extern void Invertir(char *Nombre, int tam) //invertir y números
{
int i = 1;
int a=1;
int b=0;
int flag = 0;
int Size;
Size=tam;
   
if (tam < 10) //se calcula el tamaño necesario paraa guardar el nombre con números
        tam = tam + (tam-1);// se delimita el espacio para nombres pequeños 
    else
    {
        tam = 18 + ((tam - 9)*3);// se delimita el espacio para nombres grandes
    }    
        char invert[tam];
    
while(i<tam) 
{
if (flag == 0 )//coloca las letras al reves 
{
	invert[b]=Nombre[Size-i];
	i=i+1;
	b=b+1;
    flag=1;

}
else//colocar numeros 
{
	flag=0;
	invert[b]=a+'0';
	a=a+1;
	b=b+1;
}

}
  for(int j=0; j<=(tam-1); j++) //se reasigna el valor del arreglo para llamarlo a la funcion
{
    Nombre[j]=invert[j];
} 
  for(int n=tam ;n <= 100;n++) //se rellenan las casillas vacias del arreglo inicial 
    Nombre[n] = 0;
  return;
} 
