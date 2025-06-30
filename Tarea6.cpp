// Programa: Clasificacion de rendimiento academico
// Autor: Estudiante
// Descripcion: Este programa analiza las notas de estudiantes usando arreglos
// y permite hacer estadisticas, predicciones y clasificaciones simples

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iomanip>
using namespace std;

// FUNCIONES UTILIZADAS
double calcularMedia(vector<float> notas);
float calcularMediana(vector<float> notas);
float calcularModa(vector<float> notas);
double calcularDesviacionEstandar(vector<float> notas);
void prediccionSiguienteNota(vector<float> notas);
void clasificarNotas(vector<string> nombres, vector<float> notas);
void mostrarHistograma(vector<float> notas);
void ordenarNotas(vector<string>& nombres, vector<float>& notas);
void buscarEstudiante(vector<string> nombres, vector<float> notas);
void compararDosRondas(vector<string> nombres, vector<float> notas);
void simularNotaFinal(vector<string> nombres);
void pausa();

int main() {
    int cantidad;
    cout << "Ingrese el numero de estudiantes: ";
    cin >> cantidad;

    vector<string> nombres(cantidad);
    vector<float> notas(cantidad);

    // Ingreso de datos
    for (int i = 0; i < cantidad; i++) {
        cout << "Nombre del estudiante " << i + 1 << ": ";
        cin >> ws;
        getline(cin, nombres[i]);

        cout << "Nota del estudiante (0 a 10): ";
        cin >> notas[i];
    }

    int opcion;
    do {
        cout << "\n\nMENU PRINCIPAL" << endl;
        cout << "1. Calcular estadisticas" << endl;
        cout << "2. Predecir siguiente nota" << endl;
        cout << "3. Clasificar notas (alto, medio, bajo)" << endl;
        cout << "4. Mostrar histograma" << endl;
        cout << "5. Ordenar notas" << endl;
        cout << "6. Buscar estudiante por nombre" << endl;
        cout << "7. Comparar segunda ronda de notas" << endl;
        cout << "8. Simular promedio final" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << fixed << setprecision(2);
                cout << "Media: " << calcularMedia(notas) << endl;
                cout << "Mediana: " << calcularMediana(notas) << endl;
                cout << "Moda: " << calcularModa(notas) << endl;
                cout << "Desviacion estandar: " << calcularDesviacionEstandar(notas) << endl;
                pausa();
                break;
            case 2:
                prediccionSiguienteNota(notas);
                break;
            case 3:
                clasificarNotas(nombres, notas);
                break;
            case 4:
                mostrarHistograma(notas);
                break;
            case 5:
                ordenarNotas(nombres, notas);
                break;
            case 6:
                buscarEstudiante(nombres, notas);
                break;
            case 7:
                compararDosRondas(nombres, notas);
                break;
            case 8:
                simularNotaFinal(nombres);
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}

// FUNCIONES AUXILIARES

double calcularMedia(vector<float> notas) {
    double suma = 0;
    for (int i = 0; i < notas.size(); i++) {
        suma += notas[i];
    }
    return suma / notas.size();
}

float calcularMediana(vector<float> notas) {
    sort(notas.begin(), notas.end());
    int n = notas.size();
    if (n % 2 == 0) {
        return (notas[n/2 - 1] + notas[n/2]) / 2;
    } else {
        return notas[n/2];
    }
}

float calcularModa(vector<float> notas) {
    map<float, int> frecuencia;
    for (int i = 0; i < notas.size(); i++) {
        frecuencia[notas[i]]++;
    }
    int max = 0;
    float moda = notas[0];
    map<float, int>::iterator it;
    for (it = frecuencia.begin(); it != frecuencia.end(); ++it) {
        if (it->second > max) {
            max = it->second;
            moda = it->first;
        }
    }
    return moda;
}

double calcularDesviacionEstandar(vector<float> notas) {
    double media = calcularMedia(notas);
    double suma = 0;
    for (int i = 0; i < notas.size(); i++) {
        suma += pow(notas[i] - media, 2);
    }
    return sqrt(suma / notas.size());
}

void prediccionSiguienteNota(vector<float> notas) {
    if (notas.size() < 2) {
        cout << "No hay suficientes datos para predecir." << endl;
        return;
    }
    float sumaDif = 0;
    for (int i = 1; i < notas.size(); i++) {
        sumaDif += notas[i] - notas[i-1];
    }
    float promedioDif = sumaDif / (notas.size() - 1);
    float siguiente = notas[notas.size()-1] + promedioDif;
    cout << "Siguiente nota estimada: " << siguiente << endl;
    pausa();
}

void clasificarNotas(vector<string> nombres, vector<float> notas) {
    cout << "\nAlto (>=8.5):" << endl;
    for (int i = 0; i < notas.size(); i++) {
        if (notas[i] >= 8.5) {
            cout << nombres[i] << " - " << notas[i] << endl;
        }
    }
    cout << "\nMedio (6 a 8.4):" << endl;
    for (int i = 0; i < notas.size(); i++) {
        if (notas[i] >= 6 && notas[i] < 8.5) {
            cout << nombres[i] << " - " << notas[i] << endl;
        }
    }
    cout << "\nBajo (<6):" << endl;
    for (int i = 0; i < notas.size(); i++) {
        if (notas[i] < 6) {
            cout << nombres[i] << " - " << notas[i] << endl;
        }
    }
    pausa();
}

void mostrarHistograma(vector<float> notas) {
    cout << "\nHistograma de notas:\n";
    for (int i = 0; i < notas.size(); i++) {
        cout << fixed << setprecision(1) << notas[i] << ": ";
        int cantidad = int(notas[i] * 2);
        for (int j = 0; j < cantidad; j++) cout << "*";
        cout << endl;
    }
    pausa();
}

void ordenarNotas(vector<string>& nombres, vector<float>& notas) {
    for (int i = 0; i < notas.size(); i++) {
        for (int j = i+1; j < notas.size(); j++) {
            if (notas[j] > notas[i]) {
                swap(notas[i], notas[j]);
                swap(nombres[i], nombres[j]);
            }
        }
    }
    cout << "\nNotas ordenadas (descendente):" << endl;
    for (int i = 0; i < notas.size(); i++) {
        cout << nombres[i] << ": " << notas[i] << endl;
    }
    pausa();
}

void buscarEstudiante(vector<string> nombres, vector<float> notas) {
    string buscado;
    cout << "Ingrese el nombre del estudiante a buscar: ";
    cin >> ws;
    getline(cin, buscado);
    bool encontrado = false;
    for (int i = 0; i < nombres.size(); i++) {
        if (nombres[i] == buscado) {
            cout << "Nota de " << nombres[i] << ": " << notas[i] << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "Estudiante no encontrado." << endl;
    }
    pausa();
}

void compararDosRondas(vector<string> nombres, vector<float> notas) {
    vector<float> nuevasNotas(notas.size());
    cout << "Ingrese la segunda ronda de notas:" << endl;
    for (int i = 0; i < notas.size(); i++) {
        cout << nombres[i] << ": ";
        cin >> nuevasNotas[i];
    }
    for (int i = 0; i < notas.size(); i++) {
        string estado;
        if (nuevasNotas[i] > notas[i]) estado = "Mejoro";
        else if (nuevasNotas[i] < notas[i]) estado = "Empeoro";
        else estado = "Igual";
        cout << nombres[i] << ": " << notas[i] << " -> " << nuevasNotas[i] << " (" << estado << ")\n";
    }
    pausa();
}

void simularNotaFinal(vector<string> nombres) {
    float pesoTareas, pesoExamen;
    cout << "Ingrese porcentaje de tareas: ";
    cin >> pesoTareas;
    cout << "Ingrese porcentaje de examen: ";
    cin >> pesoExamen;

    if (pesoTareas + pesoExamen != 100) {
        cout << "Los porcentajes deben sumar 100." << endl;
        pausa();
        return;
    }

    for (int i = 0; i < nombres.size(); i++) {
        float tarea, examen;
        cout << "\nNota de tareas de " << nombres[i] << ": ";
        cin >> tarea;
        cout << "Nota de examen de " << nombres[i] << ": ";
        cin >> examen;
        float promedio = (tarea * pesoTareas + examen * pesoExamen) / 100;
        cout << "Promedio final: " << promedio << " -> " << (promedio >= 6 ? "Aprobado" : "Reprobado") << endl;
    }
    pausa();
}

void pausa() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}
