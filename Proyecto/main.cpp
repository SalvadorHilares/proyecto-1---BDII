#include "ExtendibleHash.h"
// Plantilla de un Menú de Opciones

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// ExtendibleHash
ExtendibleHashFile<int> extendible("Soccer_Football_Clubs_Ranking.csv");

// Prototipos de las funciones
void menuPrincipal();
void SequentialFile();
void ExtendibleHashing();

// Funciones del submenú Operaciones básicas
void sumar();
void restar();
void multiplicar();
void dividir();

// Funciones del submenú Operaciones variadas
void Search();
void RangeSearch();
void Insertion();
void Delete();

int main()
{

    menuPrincipal();
    return 0;
}

void menuPrincipal()
{
    int opcion;
    bool repetir = true;

    do
    {
        system("cls");

        cout << "\n\n\t\t\tElija la tecnica de organizacion de archivos" << endl;
        cout << "\t\t\t--------------" << endl;
        cout << "\n\t1. Sequential File" << endl;
        cout << "\t2. Extendible Hashing" << endl;
        cout << "\t0. SALIR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            SequentialFile();
            break;

        case 2:
            ExtendibleHashing();
            break;

        case 0:
            repetir = false;
            break;
        }
    } while (repetir);
}

// Definiciones de las funciones

void SequentialFile()
{
    int opcion;
    bool repetir = true;

    do
    {
        system("cls");

        cout << "\n\n\t\t\tMENU OPERACIONES BASICAS" << endl;
        cout << "\t\t\t------------------------" << endl;
        cout << "\n\t1. Sumar" << endl;
        cout << "\t2. Restar" << endl;
        cout << "\t3. Multiplicar" << endl;
        cout << "\t4. Dividir" << endl;
        cout << "\t0. REGRESAR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            sumar();
            break;

        case 2:
            restar();
            break;

        case 3:
            multiplicar();
            break;

        case 4:
            dividir();
            break;

        case 0:
            repetir = false;
            break;
        }
    } while (repetir);
}

void ExtendibleHashing()
{
    int opcion;
    bool repetir = true;

    do
    {
        system("cls");

        cout << "\n\n\t\t\tElija la operacion que quiere realizar" << endl;
        cout << "\t\t\t-------------------------" << endl;
        cout << "\n\t1. Search" << endl;
        cout << "\t2. Range Search" << endl;
        cout << "\t3. Insertion " << endl;
        cout << "\t4. Delete" << endl;
        cout << "\t0. REGRESAR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Search();
            break;

        case 2:
            RangeSearch();
            break;

        case 3:
            Insertion();
            break;

        case 4:
            Delete();
            break;

        case 0:
            repetir = false;
            break;
        }
    } while (repetir);
}

void sumar()
{
    system("cls");
    
    int numero1, numero2;
    float resultado;

	cout << "\n\tSUMA DE DOS NUMEROS";
    cout << "\n\t===================\n";

    cout << "\n\tIngrese primer numero: ";
    cin >> numero1;

    cout << "\tIngrese segundo numero: ";
    cin >> numero2;

    cout << "\t---------------------------" << endl;
    resultado = numero1 + numero2;
    cout << "\tResultado: " << resultado << endl;

    system("pause>nul");
}

void restar()
{
    system("cls");
    
    int numero1, numero2;
    float resultado;

    cout << "\n\tRESTA DE DOS NUMEROS";
    cout << "\n\t====================\n";

    cout << "\n\tIngrese primer numero: ";
    cin >> numero1;

    cout << "\tIngrese segundo numero: ";
    cin >> numero2;

    cout << "\t---------------------------" << endl;
    resultado = numero1 - numero2;
    cout << "\tResultado: " << resultado << endl;

    system("pause>nul");
}

void multiplicar()
{
    system("cls");
    
    int numero1, numero2;
    float resultado;

    cout << "\n\tPRODUCTO DE DOS NUMEROS";
    cout << "\n\t=======================\n";

    cout << "\n\tIngrese primer numero: ";
    cin >> numero1;

    cout << "\tIngrese segundo numero: ";
    cin >> numero2;

    cout << "\t---------------------------" << endl;
    resultado = numero1 * numero2;
    cout << "\tResultado: " << resultado << endl;

    system("pause>nul");
}

void dividir()
{
    system("cls");
    
    int numero1, numero2;
    float resultado;

    cout << "\n\tCOCIENTE DE DOS NUMEROS";
    cout << "\n\t========================\n";

    cout << "\n\tIngrese primer numero: ";
    cin >> numero1;

    cout << "\tIngrese segundo numero: ";
    cin >> numero2;

    cout << "\t---------------------------" << endl;

    if (numero2 == 0)
    {
        cout << "\tResultado: No se puede dividir por cero." << endl;
    }
    else
    {
        resultado = numero1 / (numero2 * 1.0);
        cout << "\tResultado: " << resultado << endl;
    }

    system("pause>nul");
}

void Search()
{
    system("cls");

    cout << "\n\tBusca un registro por su key";
    cout << "\n\t======================\n";

    int key;
    cout << "\tIngrese el ranking del equipo que quiere buscar: ";
    cin >> key; // 1, 2, 3, 5, 6, 7
    system("cls");
    extendible.search(key);
    system("pause>nul");
}

void RangeSearch()
{
    system("cls");

    int begin_key;
    int end_key;

    cout << "\n\tBusqueda de un rango de archivos";
    cout << "\n\t==============================\n";

    cout << "\tIngrese el ranking inicial que desea buscar: ";
    cin >> begin_key;

    cout << "\tIngrese el ranking final que desea buscar: ";
    cin >> end_key;

    extendible.rangeSearch(begin_key,end_key);

    system("pause>nul");
}

void Insertion()
{
    system("cls");
    int ranking;
    string club_name;
    string country;
    double point_score;
    double one_year_change;
    double previous_point_score;
    char symbol_change;
    Record nuevo;

    cout << "\n\tInserte de un registro";
    cout << "\n\t======================\n";

    cout << "\tIngrese el ranking: ";
    cin >> ranking;
    nuevo.ranking=ranking;
    cout << "\tIngrese el nombre del club: ";
    cin >> club_name;
    nuevo.club_name=club_name;
    cout << "\tIngrese el pais de origen: ";
    cin >> country;
    nuevo.country=country;
    cout << "\tIngrese el puntaje: ";
    cin >> point_score;
    nuevo.point_score=point_score;
    cout << "\tIngrese el cambio de anio: ";
    cin >> one_year_change;
    nuevo.one_year_change=one_year_change;
    cout << "\tIngrese los puntos anteriores: ";
    cin >> previous_point_score;
    nuevo.previous_point_score=previous_point_score;
    cout << "\tIngrese el simbolo: ";
    cin >> symbol_change;
    nuevo.symbol_change=symbol_change;
    extendible.add(nuevo);

    system("pause>nul");
}

void Delete()
{
    system("cls");
    int key;
    cout << "\n\tEliminacion de un registro";
    cout << "\n\t===========================\n";

    cout << "\n\tIngrese el ranking del equipo que quiere eliminar: ";
    cin >> key;
    extendible.remove(key);

    system("pause>nul");
}