/*Ejercicios de Grafos*/
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//#include "mapa.h"
#include "mapa2.h"
using namespace std;






void mostrarMenu() {
    char opcion;

    while (true) {
        cout << "\t---------MENU PRINCIPAL---------\n";
        cout << "\n1. Ejecutar mapa\n";
        cout << "\n2. Salir\n";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case '1':
            system("cls");
            mapa();
            cout << "\n";
            break;
        case '2':
            cout << "\nSaliendo del programa...\n";
            exit(0); // Cambi� 'return 0;' por 'exit(0);' para asegurar que se termine el programa completamente
        default:
            cout << "\nOpcion no valida. Por favor, intente nuevamente.\n\n";
            system("pause");
            break;
        }
        system("cls");
    }
}



int main() {

    cout << "\n---------CASO 2---------\n";
    cout << "\nGrupo:\n\n";
    cout << "\tBrayan Carranza Corrales\n";
    cout << "\tLuis Salas Rivera\n";
    cout << "\n\nConclusiones:\n";
    cout << "\n1- Dado que el programa ya analiza toda la matriz del laberinto para guardar la informaci�n en el documento, no es necesario analizar nuevamente la coordenada que proporciona el usuario para consultar. Esto sugiere que se puede optimizar el rendimiento del programa evitando realizar un an�lisis adicional sobre la coordenada ingresada por el usuario, ya que esta informaci�n ya est� disponible en las estructuras de datos guardadas previamente.\n";
    cout << "\n2- El algoritmo DFS implementado es eficiente para encontrar caminos hacia los tesoros en el laberinto. Esto se puede inferir debido a que el programa realiza la b�squeda en tiempo razonable incluso para laberintos de tama�o considerable. Es importante resaltar la elecci�n acertada del algoritmo, ya que permite explorar el laberinto de manera exhaustiva y encontrar caminos hacia los tesoros de manera efectiva. \n";
    cout << "\n3-El programa organiza de manera clara y estructurada la informaci�n sobre las posiciones del laberinto, distinguiendo entre posiciones que llevan a un tesoro, posiciones que no llevan a un tesoro, posiciones que son obst�culos y posiciones que son tesoros en s� mismas. Esta organizaci�n facilita la comprensi�n del estado del laberinto y proporciona una base s�lida para la toma de decisiones durante la b�squeda de tesoros. \n";
    cout << "\n\n\n";
    system("pause");
    system("cls");
    mostrarMenu();
    return 0;
}