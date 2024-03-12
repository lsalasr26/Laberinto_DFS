/*Ejercicios de Grafos*/
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//#include "mapa.h"
#include "mapa2.h"
using namespace std;

int main() {
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
            return 0; 
        default:
            cout << "\nOpcion no valida. Por favor, intente nuevamente.\n\n";
            system("pause");
            break;
        }
        system("cls");
    }
}