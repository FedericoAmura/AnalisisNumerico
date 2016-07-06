#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define MARGEN 0.25
#define ERRORACEPTABLE 0.001
#define MAXIMOITERACIONES 1000

double farea(double radio, double volumen){
    return (2*PI*pow(radio+MARGEN,2)+2*volumen/radio+MARGEN*volumen/(PI*pow(radio,2)));
}

double derivada(double radio, double volumen){
    return (4*PI*(radio+MARGEN)-2*volumen/pow(radio,2)-2*MARGEN*volumen/(PI*pow(radio,3)));
}

double segunda(double radio, double volumen){
    return (4*PI+4*volumen/pow(radio,3)+6*MARGEN*volumen/(PI*pow(radio,4)));
}

int main()
{
    //declaro la variable a ingresar volumen
    double volumen;
    //declaro las variables para usar en las cuentas
    double area, error, radioactual, radioanterior, alturaactual, a, b;
    double errormaximo = ERRORACEPTABLE;
    //declaro el iterador para poder atajar cualquier loop infinito del programa
    int iterador;
    //declaro un caracter, utilizado para poder pausar el programa al final
    char salir;

    //pido el valor del volumen a calcular
    printf("Ingrese el volumen del cilindro, por defecto es 1000cm3: ");
    //leo el valor del volumen ingresado
    scanf("%lf",&volumen);
    //verifico que no sea un volumen negativo, en cuyo caso utilizo el volumen default
    if (volumen<=0){
        printf("\nVolumen invalido, se utilizara el valor default de 1000cm3\n");
        volumen = 1000;
    }
    printf("El volumen es: %f, se calculara ahora el radio adecuado para que el cilindro tenga la menor area posible\n\n",volumen);

    //consigo un valor de raiz, dado que el volumen es variable
    //para esto, hago biseccion entre los valores enteros que cambia el signo de la derivada
    a = 0;
    b = 1;
    iterador = 0;
    while(derivada(a,volumen)*derivada(b,volumen)>0){
        iterador++;
        a++;
        b++;
        if (iterador>MAXIMOITERACIONES) exit(EXIT_FAILURE);
    }
    radioactual = (a+b)/2;

    printf("Tomo como valor inicial o semilla: %f\n\n",radioactual);

    //aplico newton-raphson
    iterador = 0;
    do{
        iterador++;
        printf("Iteracion: %d\n",iterador);
        radioanterior = radioactual;
        radioactual = radioactual - derivada(radioactual,volumen)/segunda(radioactual,volumen);
        printf("radio actual: %f\n",radioactual);
        printf("radio anterior: %f\n",radioanterior);
        error = fabs(radioactual-radioanterior);
        printf("el error actual es: %f\n\n",error);
        if (iterador>MAXIMOITERACIONES) exit(EXIT_FAILURE);
    }while(errormaximo<error);

    //imprimo resultados
    printf("Se realizaron %d iteraciones hasta tener un error aceptable\n\n", iterador);
    alturaactual = volumen/(PI*pow(radioactual,2));
    printf("Se calculo que el radio del cilindro que minimiza el area es: %fcm\n", radioactual);
    printf("Con una altura de: %fcm\n\n", alturaactual);
    printf("El cilindro se construiria con dos planchas circulares de %fcm de radio para las tapas, mas una cuadrada de %fcm por %fcm para la pared para que tenga un area minima para el volumen dado\n", radioactual, (2*PI*radioactual)+0.25, alturaactual);
    printf("Lo que nos da un area minima total de material a usar de: %fcm2\n", 2*PI*pow(radioactual,2)+((2*PI*radioactual)+0.25)*alturaactual);

    //pido una tecla para salir del programa
    getch();
    return 0;
}
