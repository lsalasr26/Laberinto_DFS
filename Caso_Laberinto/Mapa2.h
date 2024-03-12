#ifndef __TAREA2__
#define __TAREA2__

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



// VECTOR DE PARES PARA REPRESENTAR LAS CUATRO DIRECCIONES POSIBLES DE MOVIMIENTO
vector<pair<int, int>> direcciones = { {0,1}, {0,-1}, {-1,0}, {1,0} };


// VECTORES PARA ALMACENAR LAS POSICIONES 
vector<pair<int, int>> posicionesParaTesoro;
vector<pair<int, int>> posicionesSonTesoro;
vector<pair<int, int>> posicionesNoTesoro;
vector<pair<int, int>> posicionesObstaculo;



//SE CREA UN ENUM PARA PODER DEVOLVER MAS ESCENARIOS Y NO LIMITARSE AL BOOLEANO
enum class ResultadoDFS {
    FueraDeRango,
    EnObstaculo,
    SinCamino,
    EnTesoro,
    CaminoHaciaTesoro,
    YaVisitado
};


// FUNCION PARA VERIFICAR SI UNA POSICION ESTA DENTRO DE LOS LIMITES DEL MAPA
bool limitado(const vector<vector<char>>& T, int i, int j) {
    return i >= 0 && j >= 0 && i < T.size() && j < T[0].size();
}

// FUNCION DFS QUE BUSCA UN CAMINO HACIA EL TESORO EN EL MAPA
ResultadoDFS dfs(vector<vector<char>>& T, int i, int j) {
    if (!limitado(T, i, j)) return ResultadoDFS::FueraDeRango;
    if (T[i][j] == 'X') return ResultadoDFS::EnObstaculo;
    if (T[i][j] == 'v') return ResultadoDFS::YaVisitado;
    if (T[i][j] == 't') return ResultadoDFS::EnTesoro;

    T[i][j] = 'v';

    for (auto& d : direcciones) {
        int adj_i = i + d.first;
        int adj_j = j + d.second;
        auto resultado = dfs(T, adj_i, adj_j);
        if (resultado == ResultadoDFS::EnTesoro || resultado == ResultadoDFS::CaminoHaciaTesoro) {
            return ResultadoDFS::CaminoHaciaTesoro;
        }
    }
    return ResultadoDFS::SinCamino;
}


//FUNCION QUE EVALUA EN EL MAPA CADA POSICION Y LA GUARDA EN EL ARCHIVO
void evaluarMapa(const vector<vector<char>>& mapaOriginal) {
    vector<vector<char>> T = mapaOriginal; // Hacer una copia para mantener el original

    for (int i = 0; i < T.size(); ++i) {
        for (int j = 0; j < T[i].size(); ++j) {
            if (T[i][j] == 't') {
                posicionesSonTesoro.push_back({ i, j }); // La posición es un tesoro por sí misma
            }
            else if (T[i][j] == 'X') {
                posicionesObstaculo.push_back({ i, j }); // La posición es un obstáculo
            }
            else if (T[i][j] == '.') {
                vector<vector<char>> copiaMapa = T; // Copiar el mapa para cada punto
                if (dfs(copiaMapa, i, j) == ResultadoDFS::CaminoHaciaTesoro) {
                    posicionesParaTesoro.push_back({ i, j }); // La posición lleva a un tesoro
                }
                else {
                    posicionesNoTesoro.push_back({ i, j }); // La posición NO lleva a un tesoro
                }
            }
        }
    }

    // Guardar los resultados en un archivo
    ofstream archivo("resultados_tesoro.txt");
    if (archivo.is_open()) {
        archivo << "Posiciones que llevan a un tesoro:\n";
        for (const auto& pos : posicionesParaTesoro) {
            archivo << "(" << pos.first << ", " << pos.second << ")\n";
        }
        archivo << "\nPosiciones que no llevan a un tesoro:\n";
        for (const auto& pos : posicionesNoTesoro) {
            archivo << "(" << pos.first << ", " << pos.second << ")\n";
        }
        archivo << "\nPosiciones que son obstáculos:\n";
        for (const auto& pos : posicionesObstaculo) {
            archivo << "(" << pos.first << ", " << pos.second << ")\n";
        }
        archivo << "\nPosiciones que tesoros:\n";
        for (const auto& pos : posicionesSonTesoro) {
            archivo << "(" << pos.first << ", " << pos.second << ")\n";
        }
        archivo.close();
        cout << "\n\nLos resultados han sido guardados en resultados_tesoro.txt\n\n ";
        system("pause");
    }
    else {
        cout << "\n\nError al abrir el archivo para guardar los resultados.\n\n ";
        system("pause");
    }
}


void imprimirMapa(const vector<vector<char>>& T) {
    cout << "\n-----Mapa completo-----\n\n";
    cout << "  "; // Espacio para la esquina superior izquierda
    for (int j = 0; j < T[0].size(); j++) {
        cout << j << " "; // Números de columna
    }
    cout << "\n";

    for (int i = 0; i < T.size(); i++) {
        cout << i << " "; // Número de fila al inicio de cada fila
        for (int j = 0; j < T[i].size(); j++) {
            cout << T[i][j] << " ";
        }
        cout << endl;
    }
}

bool buscarEnLista(const vector<pair<int, int>>& lista, const pair<int, int>& punto) {
    return find(lista.begin(), lista.end(), punto) != lista.end();
}



void consultarPosicion(const pair<int, int>& punto) {
    if (buscarEnLista(posicionesSonTesoro, punto)) {
        cout << "\n\033[32mFelicidades, la posicion inicial es un TESORO.\n\033[0m";
    }
    else if (buscarEnLista(posicionesObstaculo, punto)) {
        cout << "\n\033[31mQue mal, La posicion inicial es un obstaculo.\n\033[0m";
    }
    else if (buscarEnLista(posicionesParaTesoro, punto)) {
        cout << "\n\033[32mFelicidades, existe un camino hacia el tesoro desde la posicion inicial.\n\033[0m";
    }
    else if (buscarEnLista(posicionesNoTesoro, punto)) {
        cout << "\n\033[31mLo lamentamos, no se puede llegar a un tesoro desde la posicion inicial.\n\033[0m";
    }
    else {
        cout << "\n\033[31mTen cuidado, la posicion inicial no es valida.\n\033[0m";
    }
}

void buscarTesoro() {
    int x, y;
    cout << "\n\nIngrese las coordenadas para consultar (x y): ";
    cin >> x >> y;
    consultarPosicion({ x, y });
}


void mapa() {
    int n, m; // Dimensiones del mapa
    cout << "Digite las dimensiones del mapa (n m): ";
    cin >> n >> m;

    vector<vector<char>> T(n, vector<char>(m)); // Crear el mapa
    cout << "\nIngrese el mapa:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool entradaValida = false;
            while (!entradaValida) {
                cout << "\nIngrese el valor para la posicion [" << i << "][" << j << "] (solo '.', 't', 'X' son validos): ";
                char valor;
                cin >> valor;
                if (valor == '.' || valor == 't' || valor == 'X') {
                    T[i][j] = valor;
                    entradaValida = true;
                }
                else {
                    cout << "\nEntrada invalida. Por favor, intente nuevamente.\n";
                }
            }
        }
    }

    evaluarMapa(T);

    char opcion;
    do {
        system("cls");
        imprimirMapa(T);
        buscarTesoro();
        cout << "\nDesea buscar otro tesoro en el mismo mapa? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');
}



#endif // !__TAREA2__
#pragma once
