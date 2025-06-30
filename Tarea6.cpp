#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iomanip>
using namespace std;

// Declaración de funciones
void calcularEstadisticas(const vector<float>&);
void prediccionSimple(const vector<float>&);
void segmentarDatos(const vector<string>&, const vector<float>&);
void visualizarDatos(const vector<float>&);
void ordenarDatos(vector<string>&, vector<float>&);
void buscarEstudiante(const vector<string>&, const vector<float>&);
void clasificarDesempeno(const vector<string>&, const vector<float>&);
void detectarMejoria(const vector<string>&, const vector<float>&);
void simularNotaFinal(const vector<string>&);
void limpiarPantalla();
void pausa();

int main() {
    int n;
    cout << "Ingrese el numero de estudiantes: ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Entrada invalida. Ingrese un numero positivo: ";
    }

    vector<string> nombres(n);
    vector<float> calificaciones(n);

    // Ingreso de datos
    for (int i = 0; i < n; ++i) {
        cout << "Nombre del estudiante " << i + 1 << ": ";
        cin >> ws;
        getline(cin, nombres[i]);

        cout << "Calificacion de " << nombres[i] << " (0 a 10): ";
        while (!(cin >> calificaciones[i]) || calificaciones[i] < 0 || calificaciones[i] > 10) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Ingrese calificacion entre 0 y 10: ";
        }
    }

    // Menú interactivo
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n--- MENU DE OPCIONES ---\n";
        cout << "1. Calcular estadisticas\n";
        cout << "2. Prediccion simple\n";
        cout << "3. Segmentar datos\n";
        cout << "4. Visualizar datos (histograma)\n";
        cout << "5. Ordenar datos\n";
        cout << "6. Buscar estudiante\n";
        cout << "7. Clasificacion por desempeño\n";
        cout << "8. Deteccion de mejoria\n";
        cout << "9. Simulacion de nota final\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: calcularEstadisticas(calificaciones); break;
            case 2: prediccionSimple(calificaciones); break;
            case 3: segmentarDatos(nombres, calificaciones); break;
            case 4: visualizarDatos(calificaciones); break;
            case 5: ordenarDatos(nombres, calificaciones); break;
            case 6: buscarEstudiante(nombres, calificaciones); break;
            case 7: clasificarDesempeno(nombres, calificaciones); break;
            case 8: detectarMejoria(nombres, calificaciones); break;
            case 9: simularNotaFinal(nombres); break;
            case 0: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida.\n"; pausa();
        }
    } while (opcion != 0);

    return 0;
}

// ------------------------ FUNCIONES ------------------------

void calcularEstadisticas(const vector<float>& notas) {
    float suma = 0;
    for (float nota : notas) suma += nota;
    float media = suma / notas.size();

    vector<float> ordenadas = notas;
    sort(ordenadas.begin(), ordenadas.end());
    float mediana = (ordenadas.size() % 2 == 0) ? 
                    (ordenadas[ordenadas.size()/2 - 1] + ordenadas[ordenadas.size()/2]) / 2 :
                    ordenadas[ordenadas.size()/2];

    map<float, int> frecuencia;
    for (float nota : notas) frecuencia[nota]++;
    int maxFreq = 0;
    float moda = notas[0];
    for (auto par : frecuencia) {
        if (par.second > maxFreq) {
            maxFreq = par.second;
            moda = par.first;
        }
    }

    float sumaCuadrados = 0;
    for (float nota : notas) sumaCuadrados += pow(nota - media, 2);
    float desviacion = sqrt(sumaCuadrados / notas.size());

    cout << fixed << setprecision(2);
    cout << "\nMedia: " << media;
    cout << "\nMediana: " << mediana;
    cout << "\nModa: " << moda;
    cout << "\nDesviacion estandar: " << desviacion << "\n";
    pausa();
}

void prediccionSimple(const vector<float>& notas) {
    if (notas.size() < 2) {
        cout << "No hay suficientes datos para predecir.\n";
        pausa();
        return;
    }
    float sumaDiferencias = 0;
    for (size_t i = 1; i < notas.size(); ++i)
        sumaDiferencias += notas[i] - notas[i - 1];

    float promedioDiferencia = sumaDiferencias / (notas.size() - 1);
    float prediccion = notas.back() + promedioDiferencia;

    cout << fixed << setprecision(2);
    cout << "Prediccion de la proxima nota: " << prediccion << "\n";
    pausa();
}

void segmentarDatos(const vector<string>& nombres, const vector<float>& notas) {
    float suma = 0;
    for (float nota : notas) suma += nota;
    float media = suma / notas.size();

    cout << "\n-- Estudiantes por encima de la media --\n";
    for (size_t i = 0; i < notas.size(); ++i)
        if (notas[i] > media) cout << nombres[i] << " - " << notas[i] << "\n";

    cout << "\n-- Estudiantes por debajo o igual a la media --\n";
    for (size_t i = 0; i < notas.size(); ++i)
        if (notas[i] <= media) cout << nombres[i] << " - " << notas[i] << "\n";

    pausa();
}

void visualizarDatos(const vector<float>& notas) {
    cout << "\nHistograma de calificaciones:\n";
    for (float nota : notas) {
        cout << fixed << setprecision(1) << nota << ": ";
        int barras = static_cast<int>(nota * 5);
        for (int i = 0; i < barras; ++i) cout << "#";
        cout << "\n";
    }
    pausa();
}

void ordenarDatos(vector<string>& nombres, vector<float>& notas) {
    for (size_t i = 0; i < notas.size(); ++i) {
        for (size_t j = i + 1; j < notas.size(); ++j) {
            if (notas[j] > notas[i]) {
                swap(notas[i], notas[j]);
                swap(nombres[i], nombres[j]);
            }
        }
    }
    cout << "\nDatos ordenados descendente:\n";
    for (size_t i = 0; i < notas.size(); ++i)
        cout << nombres[i] << ": " << notas[i] << "\n";
    pausa();
}

void buscarEstudiante(const vector<string>& nombres, const vector<float>& notas) {
    string buscado;
    cout << "Ingrese el nombre a buscar: ";
    cin >> ws;
    getline(cin, buscado);

    for (size_t i = 0; i < nombres.size(); ++i) {
        if (nombres[i] == buscado) {
            cout << "Estudiante encontrado: " << nombres[i] << " - Nota: " << notas[i] << "\n";
            pausa();
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
    pausa();
}

void clasificarDesempeno(const vector<string>& nombres, const vector<float>& notas) {
    cout << "\n-- Alto (>=8.5) --\n";
    for (size_t i = 0; i < notas.size(); ++i)
        if (notas[i] >= 8.5) cout << nombres[i] << " - " << notas[i] << "\n";

    cout << "\n-- Medio (6.0 a 8.49) --\n";
    for (size_t i = 0; i < notas.size(); ++i)
        if (notas[i] >= 6 && notas[i] < 8.5) cout << nombres[i] << " - " << notas[i] << "\n";

    cout << "\n-- Bajo (<6.0) --\n";
    for (size_t i = 0; i < notas.size(); ++i)
        if (notas[i] < 6) cout << nombres[i] << " - " << notas[i] << "\n";
    pausa();
}

void detectarMejoria(const vector<string>& nombres, const vector<float>& notas) {
    vector<float> nuevaNota(notas.size());
    for (size_t i = 0; i < nombres.size(); ++i) {
        cout << "Nueva calificacion de " << nombres[i] << ": ";
        while (!(cin >> nuevaNota[i]) || nuevaNota[i] < 0 || nuevaNota[i] > 10) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Ingrese calificacion entre 0 y 10: ";
        }
    }
    cout << "\n-- Comparacion de desempeño --\n";
    for (size_t i = 0; i < nombres.size(); ++i) {
        string resultado = (nuevaNota[i] > notas[i]) ? "Mejoró" :
                           (nuevaNota[i] < notas[i]) ? "Empeoró" : "Igual";
        cout << nombres[i] << ": " << notas[i] << " -> " << nuevaNota[i] << " (" << resultado << ")\n";
    }
    pausa();
}

void simularNotaFinal(const vector<string>& nombres) {
    float peso1, peso2;
    cout << "Ingrese porcentaje para tareas: ";
    cin >> peso1;
    cout << "Ingrese porcentaje para examen: ";
    cin >> peso2;

    if (peso1 + peso2 != 100) {
        cout << "Los porcentajes deben sumar 100.\n";
        pausa();
        return;
    }

    for (const string& nombre : nombres) {
        float tarea, examen;
        cout << "\nCalificacion de tareas de " << nombre << ": ";
        cin >> tarea;
        cout << "Calificacion de examen de " << nombre << ": ";
        cin >> examen;
        float final = (tarea * peso1 + examen * peso2) / 100.0;
        cout << "Nota final: " << final << " -> " << (final >= 6.0 ? "Aprobado" : "Reprobado") << "\n";
    }
    pausa();
}

void limpiarPantalla() {
    cout << "\033[2J\033[1;1H"; // Limpia la consola en la mayoría de terminales Unix
}

void pausa() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

