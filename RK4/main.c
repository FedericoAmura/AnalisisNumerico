#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PASODEFAULT 0.1
#define VOLTAJE 100
#define RESISTENCIA 10
#define INDUCTOR 1
#define VINICIALF 0
#define VINICIALG 0
#define INICIOINTERVALO 0
#define FININTERVALO 3
#define MAXIMOITERACIONES 500

double f(double t, double x, double y){
    return (-20*x+10*y+VOLTAJE);
}

double g(double t, double x, double y){
    return (10*x-20*y);
}

int main()
{
    //declaro la variable a ingresar paso
    double paso = PASODEFAULT;
    //declaro el inicio y fin del intervalo
    double iIntervalo = INICIOINTERVALO;
    double fIntervalo = FININTERVALO;
    //declaro las variables para usar en las cuentas
    double m1,m2,m3,m4,k1,k2,k3,k4;
    double xn = VINICIALF;
    double yn = VINICIALG;
    //declaro el iterador para poder atajar cualquier loop infinito del programa
    double iterador = 0;
    //declaro un caracter, utilizado para poder pausar el programa al final
    char salir;
    //declaro y creo un archivo para sacar todos los valores y graficarlos luego
    FILE* output = fopen("./output.csv","w");

    //pido el valor del volumen a calcular
    printf("Ingrese el paso para realizar las iteraciones (por defecto es 0.1) El paso debe dividir el intervalo en un numero de partes entero: ");
    //leo el valor del volumen ingresado
    scanf("%lf",&paso);

    //imprimo el encabezado del archivo, con el paso y los limites del intervalo
    fprintf(output,"El paso es %f\n",paso);
    fprintf(output,"Inicio intervalo: %f, Fin intervalo: %f\n",iIntervalo,fIntervalo);
    fprintf(output,"m1,k1,m2,k2,m3,k3,m4,k4,");
    fprintf(output,"X(t),Y(t)\n");
    //imprimo los valores iniciales
    fprintf(output,"0,0,0,0,0,0,0,0,");
    fprintf(output,"%f,%f\n",xn,yn);
    //ejecuto RK4
    do{
        //calculo coeficientes para la iteracion
        m1 = f(iIntervalo+iterador*paso,xn,yn);
        k1 = g(iIntervalo+iterador*paso,xn,yn);

        m2 = f(iIntervalo+iterador*paso+0.5*paso,xn+0.5*paso*m1,yn+0.5*paso*k1);
        k2 = g(iIntervalo+iterador*paso+0.5*paso,xn+0.5*paso*m1,yn+0.5*paso*k1);

        m3 = f(iIntervalo+iterador*paso+0.5*paso,xn+0.5*paso*m2,yn+0.5*paso*k2);
        k3 = g(iIntervalo+iterador*paso+0.5*paso,xn+0.5*paso*m2,yn+0.5*paso*k2);

        m4 = f(iIntervalo+iterador*paso+paso,xn+paso*m3,yn+paso*k3);
        k4 = g(iIntervalo+iterador*paso+paso,xn+paso*m3,yn+paso*k3);

        //calculo proximo valor de la iteracion
        xn = xn+paso*(m1+2*m2+2*m3+m4)/6;
        yn = yn+paso*(k1+2*k2+2*k3+k4)/6;

        //imprimo valores de la iteracion en el archivo de salida
        fprintf(output,"%f,%f,%f,%f,%f,%f,%f,%f,",m1,k1,m2,k2,m3,k3,m4,k4);
        fprintf(output,"%f,%f\n",xn,yn);

        //verifico no estar en un loop pasado del limite y avanzo un paso
        if (iterador>MAXIMOITERACIONES) exit(EXIT_FAILURE);
        iterador = iterador + 1;
    }while(iIntervalo+iterador*paso<fIntervalo);

    //imprimo valores finales
    printf("Los valores calculados al final del intervalo son:\n");
    printf("X(t) = %f\n",xn);
    printf("Y(t) = %f\n",yn);
    printf("Calculados con un paso de: %f\n",paso);
    //pido una tecla para salir del programa
    getch();
    fclose(output);
    return 0;
}
