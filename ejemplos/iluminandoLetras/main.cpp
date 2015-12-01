//Código para la  #hackminiblip 

#include "mbed.h"
#include "neopixel.h"

// Matrix led output pin
#define DATA_PIN P0_9

#define ANALOG_POTENTIOMETER P0_22
AnalogIn   ain(ANALOG_POTENTIOMETER);

void wait_potenciometro(int tiempo){
        // Rainbow delay
        float pot = ain.read();
        wait_ms(tiempo*pot);
}

void fill_pixel(neopixel::Pixel buffer[25], int x, int y, int red, int green, int blue){
    
    if(x<0) x=0;
    if(x>4) x=4;
    if(y<0) y=0;
    if(y>4) y=4;
       

    int posicion=x+y*5;
    buffer[posicion].red=red;
    buffer[posicion].green=green;
    buffer[posicion].blue=blue;
    
}

void void_matrix(neopixel::Pixel aux[25], int tam=25){
    
    for(int i=0;i<tam;i++){
        aux[i].red=0;
        aux[i].green=0;
        aux[i].blue=0;
    }
}

/* Genera la codificación de caracteres para imprimirlos en una matriz 5x5 (dibujado).         
Uso: 
    neopixel::Pixel letra[25];
    generaLetra(letra, 'a', 30, 0 , 0 );            
    array.update(letra, 25);
*/
void generaLetra(neopixel::Pixel vector[], char letra, int red, int green, int blue){

    /*
    * Cada letra tiene 5 valores en hexadecimal que representan en binario cada fila de la matrix 5x5 (aunque sobren 3 bits)
    */
    unsigned char espacio[5]={0x0, 0x0, 0x0, 0x0, 0x0};
    unsigned char a[5]={0x88, 0x88, 0xF8, 0x88, 0x70};
    unsigned char b[5]={0xF0, 0x88, 0xF0, 0x88, 0xF0};      
    unsigned char c[5]={0x78, 0x80, 0x80, 0x80, 0x78};   
    unsigned char d[5]={0xF0, 0x88, 0x88, 0x88, 0xF0};
    unsigned char e[5]={0xF8, 0x80, 0xF8, 0x80, 0xF8};
    unsigned char f[5]={0x80, 0x80, 0xE0, 0x80, 0xF8};    
    unsigned char g[5]={0x78, 0x88, 0xB8, 0x80, 0x78};
    unsigned char h[5]={0x88, 0x88, 0xF8, 0x88, 0x88};
    unsigned char i[5]={0x70, 0x20, 0x20, 0x20, 0x70};
    unsigned char j[5]={0x70, 0x88, 0x8,  0x8,  0x38};
    unsigned char k[5]={0x88, 0x88, 0xF0, 0xA0, 0x90}; 
    unsigned char l[5]={0xF8, 0x80, 0x80, 0x80, 0x80};
    unsigned char m[5]={0x88, 0x88, 0xA8, 0xD8, 0x88};
    unsigned char n[5]={0x98, 0xA8, 0xA8, 0xA8, 0xC8};
    unsigned char o[5]={0x70, 0x88, 0x88, 0x88, 0x70};
    unsigned char p[5]={0x80, 0x80, 0xF0, 0x88, 0xF0};
    unsigned char q[5]={0x78, 0x90, 0x90, 0x90, 0x60};
    unsigned char r[5]={0x88, 0x90, 0xF0, 0x88, 0xF0};    
    unsigned char s[5]={0xF0, 0x8,  0x70, 0x80, 0x78};
    unsigned char t[5]={0x20, 0x20, 0x20, 0x20, 0xF8};
    unsigned char u[5]={0x70,0x88,0x88,0x88,0x88};
    unsigned char v[5]={0x20,0x50,0x50,0x88,0x88};
    unsigned char w[5]={0x88,0xD8,0xA8,0x88,0x88};
    unsigned char x[5]={0x88,0x50,0x20,0x50,0x88};
    unsigned char y[5]={0x20,0x20,0x70,0x88,0x88};
    unsigned char z[5]={0xF8,0x80,0x70,0x8,0xF8};
    //"l" de literal
    unsigned char l0[5]={0x70, 0xC8, 0xA8, 0x98, 0x70};
    unsigned char l1[5]={0x70, 0x20, 0x20, 0x60, 0x20};    
    unsigned char l2[5]={0xF8, 0x80, 0x70, 0x8,  0xF0};    
    unsigned char l3[5]={0xF0, 0x8,  0x30, 0x8,  0xF0};
    unsigned char l4[5]={0x8,  0x8,  0x78, 0x88, 0x88};
    unsigned char l5[5]={0xF0, 0x8,  0xF0, 0x80, 0xF8};
    unsigned char l6[5]={0x70, 0x88, 0xF0, 0x80, 0x78};
    unsigned char l7[5]={0x10, 0x10, 0x10, 0x8,  0xF8};
    unsigned char l8[5]={0x70, 0x88, 0x70, 0x88, 0x70};
    unsigned char l9[5]={0x30, 0x8,  0x78, 0x88, 0x70}; 
                                        
    //Montamos un vector de punteros a los vectores de letras.
    unsigned char *vectorLetras  []={a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};
    //Hacemos lo mismo para los números.
    unsigned char *vectorNumeros []={l0, l1, l2, l3, l4, l5, l6, l7, l8, l9};
                              
    //Creamos un puntero para moverlo por los vectores.
    unsigned char *puntero;
     
    //Según el caracter que nos entre por la función haremos que el puntero apunte a un lugar o a otro.     
    if (letra==' ') //Se trata de un espacio         
        puntero=espacio;
    else if (letra>='0' && letra<='9') //El 0 es el 48 y el 57 el 9 en ASCII        
        puntero=vectorNumeros[(letra-'0')];    
    else             
        //a= al valor 97
        puntero=vectorLetras[(letra-'a')];
            
            //Vamos a recorrer todo el vector de bytes
            for(int i=0; i<5; i++){
                
                unsigned char elemento = puntero[i];
                //Creamos una máscara que será un bit a uno seguido de todo ceros.
                unsigned int mask=0x80;
                //Nos movemos por 5 bits de los 8 (los otros tres son 0 y no necesitamos evaluarlos, no contienen información relevante)
                for(int x=0; x<5; x++){
                    //Aplicamos la operacion and logica (solo cuando 1&1=1) haciendo que se rellene ese led en el vector con el color pasado.
                    if (elemento & mask)
                        fill_pixel(vector, x,i, red, green, blue);                                                                
                    //Desplazamos 1 bit de la máscara para que evalue "and" en la siguiente posición.
                    mask >>=1;
                }                
            }          
}    

void iluminaTexto(char cadena[], neopixel::PixelArray array){
      
       //Creamos un vector de pixeles.
       neopixel::Pixel letra[25];
        //Inicializamos el vector a 0
        void_matrix(letra);
        for(int i=0; i<strlen(cadena); i++){
            //Generamos la letra en el vector letra        
            generaLetra(letra, cadena[i], 30, 0 , 0 );
            //Iluminamos la matriz
            array.update(letra, 25);
            //Usamos la función wait_potenciometro a la que le pasamos un valor por defecto.
            wait_potenciometro(1000); 
            //Reseteamos la ltra (es un vector, seteando todos los valore a 0)
            void_matrix(letra);
            //Iluminamos la matriz a 0 (no la iluminamos = "la apagamos")
            array.update(letra, 25);
            //Hacemos un wait condicional del valor del potenciometro otra vez.                                  
            wait_potenciometro(300);   
        }
        wait_potenciometro(600);
        
        
}    

int main()
{
    // Create a temporary DigitalIn so we can configure the pull-down resistor.
    DigitalIn(DATA_PIN, PullDown);

    // The pixel array control class.
    //Se está creando un objeto de tipo PixelArray y se está nombrando como array a la que se le está pasando DATA_PIN
    neopixel::PixelArray array(DATA_PIN); 
    
    //Usamos un vector de char para introducir el texto.
    char todo[] = "abcdefghijakmlopqrstuvwxyz0123456789";
    char texto[]= "hacking miniblip";

    while (1) {        
        //Llamada en bucle a la función.
        iluminaTexto(texto, array);
    }
}
