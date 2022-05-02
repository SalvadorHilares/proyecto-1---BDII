#include "SequentialFile.h"

void menuPrincipal();

void Sequential_File();
void sequential_add_(SequentialFile<record,const char* > sequential);
void sequential_remove_(SequentialFile<record,const char* > sequential);
void sequential_search_per_range_(SequentialFile<record,const char* > sequential);
void sequential_add_table_(SequentialFile<record,const char* > sequential);

void ExtendibleHashing();
void Search();
void RangeSearch();
void Insertion();
void Delete();

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
        cout << "\t0. SALIR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Sequential_File();
            break;
        case 0:
            repetir = false;
            break;
        }
    } while (repetir);
}

void sequential_search_(SequentialFile<record,const char* > &sequential)
{
    system("cls");

    cout << "\n\tBusca un registro por su key";
    cout << "\n\t======================\n";

    char* key;
    cout << "\tIngrese el key quiere buscar: ";
    cin >> key; 
    
    system("cls");

    auto rec=sequential.search_record(key);
    rec[0].showData();

    system("pause>nul");
}

void Sequential_File()
{
    int opcion;
    bool repetir = true;
    auto seqfile = SequentialFile<record,const char*>("../datafile.dat","../auxfile.dat");

    do
    {
        system("cls");

        cout << "\n\n\t\t\tElija la operacion que quiere realizar" << endl;
        cout << "\t\t\t------------------------" << endl;
        cout << "\n\t1. Add" << endl;
        cout << "\t2. Search" << endl;
        cout << "\t3. Search per range" << endl;
        cout << "\t4. Delete" << endl;
        cout << "\t5. Add Table" << endl;
        cout << "\t0. REGRESAR" << endl;

        cout << "\n\tIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
          case 1:
              sequential_add_(seqfile);
              break;

          case 2:
              sequential_search_(seqfile);
              break;

          case 3:
              sequential_search_per_range_(seqfile);
              break;

          case 4:
              sequential_remove_(seqfile);
              break;  
          
          case 5:
              sequential_add_table_(seqfile);
              break;

          case 0:
              repetir = false;
              break;

        }
    } while (repetir);
}

void sequential_search_per_range_(SequentialFile<record,const char* > sequential)
{
    system("cls");

    int begin_key;
    int end_key;

    cout << "\n\tBusqueda de un rango de archivos";
    cout << "\n\t==============================\n";

    cout << "\tIngrese el key inicial que desea buscar: ";
    cin >> begin_key;

    cout << "\tIngrese el key final que desea buscar: ";
    cin >> end_key;

    vector<record>rec;  
    for (int i =0; i+begin_key<=end_key;++i){
        cout<<"------record "<< begin_key <<"------"<<endl;
        string tmp = std::to_string(i+begin_key);
        char const *aux = tmp.c_str();
        rec=sequential.search_record(aux);
        rec[0].showData();
    }

    system("pause>nul");
}

void sequential_add_(SequentialFile<record,const char* > sequential )
{
    system("cls");
    
    string ranking;
    string club_name;
    string country;
    string point_score;
    string one_year_change;
    string previous_point_score;
    string symbol_change;

    record row;
    row = record();

    cout << "\n\tInserte de un registro";
    cout << "\n\t======================\n";

    cout << "\tIngrese el ranking: ";
    cin >> ranking;
    row.set_ranking(ranking);

    cout << "\tIngrese el nombre del club: ";
    cin >> club_name;
    row.set_club_name(club_name);

    cout << "\tIngrese el pais de origen: ";
    cin >> country; 
    row.set_country(country);

    cout << "\tIngrese el puntaje: ";
    cin >> point_score;
    row.set_point_score(point_score);
    
    cout << "\tIngrese el cambio de anio: ";
    cin >> one_year_change;
    row.set_one_year_change(one_year_change);
    
    cout << "\tIngrese los puntos anteriores: ";
    cin >> previous_point_score;
    row.set_previous_point_score(previous_point_score);
    
    cout << "\tIngrese el simbolo: ";
    cin >> symbol_change;
    row.set_symbol_change(symbol_change);

    sequential.add_record(row);

    system("pause>nul");
}

void sequential_remove_(SequentialFile<record,const char* > sequential)
{
    system("cls");
    string key;
    cout << "\n\tEliminacion de un registro";
    cout << "\n\t===========================\n";

    cout << "\n\tIngrese el key que quiere eliminar: ";
    cin >> key;
    char const *aux = key.c_str();
    sequential.remove_record(aux);

    system("pause>nul");
}

void sequential_add_table_(SequentialFile<record,const char* > sequential){
    cout << "\n\tIngrese el nombre de dataset: ";
    string filename;
    cin>>filename;

    ifstream data(filename);
    string line;
    vector<vector<string>> parsedCsv;
    while(getline(data,line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> parsedRow;
        while(getline(lineStream,cell,','))
        {
            parsedRow.push_back(cell);
        }

        parsedCsv.push_back(parsedRow);
    }
}

void ExtendibleHashing(){return;}
/*void ExtendibleHashing()
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
}*/