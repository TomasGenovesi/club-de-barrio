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
const char* nombreCategoria(int categoria);
void altaSocio();
void listarPadron();

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
            case 1: altaSocio(); break;
            case 2: cout << "Todavia no implementado" << endl; break;
            case 3: cout << "Todavia no implementado" << endl; break;
            case 4: listarPadron(); break;
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

const char* nombreCategoria(int categoria) {
    if (categoria == 1) return "Infantil";
    if (categoria == 2) return "Activo";
    if (categoria == 3) return "Vitalicio";
    return "?";
}

void altaSocio() {
    FILE* archivo = fopen("socios.dat", "rb");

    if (archivo == NULL) {
        cout << "No se pudo abrir socios.dat" << endl;
        return;
    }

    // El numero nuevo es el que sigue al ultimo. Como nunca se borra nadie,
    // alcanza con contar los registros del archivo y sumar 1.
    fseek(archivo, 0, SEEK_END);
    long cantidad = ftell(archivo) / sizeof(Socio);
    fclose(archivo);

    Socio socio;
    memset(&socio, 0, sizeof(Socio));         // dejo todo en cero para no grabar basura
    socio.idSocio = cantidad + 1;

    cout << "Nombre: ";
    cin.getline(socio.nombre, 50);
    cout << "Categoria (1 Infantil, 2 Activo, 3 Vitalicio): ";
    cin >> socio.categoria;
    cout << "Cuota mensual: ";
    cin >> socio.cuotaMensual;
    socio.activo = true;

    archivo = fopen("socios.dat", "ab");      // el alta va siempre al final

    if (archivo == NULL) {
        cout << "No se pudo abrir socios.dat" << endl;
        return;
    }

    int escribio = fwrite(&socio, sizeof(Socio), 1, archivo);
    fclose(archivo);

    if (escribio != 1) {
        cout << "No se pudo grabar el socio" << endl;
        return;
    }

    cout << "Socio dado de alta con el numero " << socio.idSocio << endl;
}

void listarPadron() {
    FILE* archivo = fopen("socios.dat", "rb");

    if (archivo == NULL) {
        cout << "No se pudo abrir socios.dat" << endl;
        return;
    }

    Socio socio;
    int activos = 0;

    cout << "\n";
    cout.width(8);  cout << "Socio";
    cout.width(22); cout << "Nombre";
    cout.width(12); cout << "Categoria";
    cout << "Cuota" << endl;

    while (fread(&socio, sizeof(Socio), 1, archivo) == 1) {
        if (socio.activo) {
            cout.width(8);  cout << socio.idSocio;
            cout.width(22); cout << socio.nombre;
            cout.width(12); cout << nombreCategoria(socio.categoria);
            cout << "$" << socio.cuotaMensual << endl;
            activos++;
        }
    }

    fclose(archivo);

    if (activos == 0) cout << "No hay socios activos" << endl;
    else cout << "Total de socios activos: " << activos << endl;
}
