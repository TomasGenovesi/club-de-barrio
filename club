#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Socio {
    int idSocio;            // 1, 2, 3, ... sin huecos
    char nombre[50];
    int categoria;          // 1 Infantil, 2 Activo, 3 Vitalicio
    float cuotaMensual;
    bool activo;            // false = dado de baja
};

struct Pago {
    int idSocio;
    char mes[8];            // "MM-AAAA"
    float monto;
};

void crearArchivoSiNoExiste(const char* nombreArchivo);
void mostrarMenu();

int main() {
    // Si los archivos no existen los creo vacios: "ab" crea y no borra nada.
    crearArchivoSiNoExiste("socios.dat");
    crearArchivoSiNoExiste("pagos.dat");

    cout.setf(ios::fixed);                    // los montos siempre con 2 decimales
    cout.precision(2);
    cout.setf(ios::left, ios::adjustfield);   // las columnas de los listados alineadas a la izquierda

    int opcion = -1;

    while (opcion != 0 && cin) {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(10000, '\n');              // saco el Enter, asi los getline de abajo no leen una linea vacia

        switch (opcion) {
            case 1: cout << "Todavia no implementado" << endl; break;
            case 2: cout << "Todavia no implementado" << endl; break;
            case 3: cout << "Todavia no implementado" << endl; break;
            case 4: cout << "Todavia no implementado" << endl; break;
            case 5: cout << "Todavia no implementado" << endl; break;
            case 6: cout << "Todavia no implementado" << endl; break;
            case 0: cout << "Hasta luego" << endl; break;
            default: cout << "Opcion invalida" << endl;
        }
    }

    return 0;
}

void crearArchivoSiNoExiste(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "ab");

    if (archivo != NULL) fclose(archivo);
}

void mostrarMenu() {
    cout << "\n=== Club Social y Deportivo Villa Albert ===" << endl;
    cout << "1) Alta de socio" << endl;
    cout << "2) Modificar socio" << endl;
    cout << "3) Baja de socio" << endl;
    cout << "4) Listado del padron" << endl;
    cout << "5) Registrar pago" << endl;
    cout << "6) Reporte de cobranza" << endl;
    cout << "0) Salir" << endl;
    cout << "Opcion: ";
}
