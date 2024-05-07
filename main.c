#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "pila.h"

#define DIM 40

int cargaDataUsuario (Pila *p);
void muestraPila (Pila p);
void dividirPila(Pila p, Pila *min, Pila *max);
int buscaMenor (Pila *p);
int cuentaDatos (Pila p, int valor);
int sumaDatos (Pila p, int valor);
int cargaArreglo (int a[], int v, int dim, Pila p);
void muestraArreglo (int a[], int v);

int main()
{
    Pila temperaturas;
    Pila minimos;
    Pila maximos;
    inicpila(&temperaturas);
    inicpila(&minimos);
    inicpila(&maximos);

    cargaDataUsuario(&temperaturas);
    printf("\n Las temperaturas son: \n");
    muestraPila(temperaturas);

    dividirPila(temperaturas, &minimos, &maximos);
    printf("\n Las temperaturas minimas son: \n");
    muestraPila(minimos);
    printf("\n Las temperaturas maximas son: \n");
    muestraPila(maximos);

    printf("\n");

    int menor = 0;
    menor = buscaMenor(&temperaturas);
    printf("\n La menor temperatura es: %d \n", menor);

    int cantidad = cuentaDatos(temperaturas, 15);
    printf(" \n La cantidad de temperaturas mayores a 15 son: %d \n", cantidad);

    int total = sumaDatos(temperaturas, 15);
    printf("\n La suma de los valores mayores a 15 son: %d \n", total);

    int arregloTemp [DIM];
    int vArregloTemp = 0;

    printf("\n El arreglo es: \n");
    vArregloTemp = cargaArreglo(arregloTemp, vArregloTemp, DIM, temperaturas);
    muestraArreglo(arregloTemp, vArregloTemp);



    return 0;
}
//1. Hacer una función para cargar una pila de temperaturas con intervención del usuario validando que estén dentro
//del rango de valores elegido por el usuario. Las temperaturas deben ser de tipo entero y estar en el rango de -10 a 40.
int cargaDataUsuario (Pila *p)
{
    int data = 0;
    char opcion = 0;

    while ( opcion != 27 ){
        printf("Ingrese el valor de temperatura: \n");
        scanf("%d", &data);
        if(data < 41 && data > -11){
            apilar(p, data);
        }else {
            printf("La temperatura no esta dentro del rango!\n");
        }
        printf("Quiere cargar mas datos? Presione cualquier tecla, sino ESC para salir");
        opcion = getch();
        system("cls");
    }
    return data;
}
//2. Hacer una función que muestre la pila de las temperaturas (sin utilizar la función mostrar() de la librería de pilas)
//Se deberán mostrar 15 temperaturas por línea.
void muestraPila (Pila p)
{
    Pila aux;
    inicpila(&aux);
    int i = 0;

    while (!pilavacia(&p)){
        if(i % 15 == 0){
            printf("\n");
        }
        i++;
        printf(" %d |", tope(&p));
        apilar(&aux, desapilar(&p));
    }
}
//3. Hacer una función que copie a una pila menores las temperaturas <= 0 y a una pila mayores el resto de las temperaturas.
// No se deben perder los datos de la pila original.
void dividirPila(Pila p, Pila *min, Pila *max)
{
    int aux = 0;
    while(!pilavacia(&p)){
        aux = desapilar(&p);
        if (aux <= 0){
            apilar(min, aux);
        }else {
            apilar(max, aux);
        }
    }
}
//4. Hacer una función que encuentre la temperatura mínima en la pila y la retorne
//(la temperatura mínima debe quitarse de la pila).
int buscaMenor (Pila *p)
{
    Pila aux;
    inicpila(&aux);
    int menor = desapilar(p);

    while(!pilavacia(p)){
        if (menor < tope(p)){
            apilar(&aux, desapilar(p));
        }else{
            apilar(&aux, menor);
            menor = desapilar(p);
        }
    }

    while(!pilavacia(&aux)){
        apilar(p, desapilar(&aux));
    }
    return menor;
}
//5. Hacer una función que cuente las temperaturas de una pila, mayores a un valor dado y lo retorne.
//(el valor se recibe por parámetro).
int cuentaDatos (Pila p, int valor)
{
    int cantidad = 0;
    Pila aux;
    inicpila(&aux);

    while(!pilavacia(&p)){
        if (tope(&p) > valor){
            apilar(&aux, desapilar(&p));
            cantidad++;
            }
        apilar(&aux, desapilar(&p));
    }

    return cantidad;
}
//6.Hacer una función que sume las temperaturas de una pila, mayores a un valor dado y lo retorne. (el valor se recibe por parámetro).
int sumaDatos (Pila p, int valor)
{
    int total = 0;
    Pila aux;
    inicpila(&aux);

    while (!pilavacia(&p)){
        if (tope(&p) > valor){
            total = total + tope(&p);
            apilar(&aux, desapilar(&p));
        }else {
            apilar(&aux, desapilar(&p));
        }
    }

    return total;
}
//7. Hacer una función que cargue un arreglo de temperaturas ordenado de menor a mayor a partir de la pila de temperaturas.
int  cargaArreglo (int a[], int v, int dim, Pila p)
{
    while(!pilavacia(&p) && v < dim){
        a[v] = buscaMenor(&p);
        v++;
    }
    return v;
}
//8.Hacer una función que muestre un arreglo de temperaturas pero solo 20 por línea.
void muestraArreglo (int a[], int v)
{
    for(int i = 0; i < v; i++){
            if (i % 20 == 0){
                printf(" \n ");
            }
        printf(" %d |", a[i]);
    }
}

