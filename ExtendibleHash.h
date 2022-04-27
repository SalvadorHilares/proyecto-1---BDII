#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#define MAX_B 5
#define D_global 8
using namespace std;

struct Record{
    int ranking;
    string club_name;
    string country;
    double point_score;
    double one_year_change;
    double previous_point_score;
    char symbol_change;

    void showData(){
        cout<<"RANKING: "<<ranking<<endl;
        cout<<"CLUB_NAME: "<<club_name<<endl;
        cout<<"COUNTRY: "<<country<<endl;
        cout<<"POINT_SCORE: "<<point_score<<endl;
        cout<<"ONE YEAR CHANGE: "<<one_year_change<<endl;
        cout<<"PREVIOUS POINT SCORE: "<<previous_point_score<<endl;
        cout<<"SYMBOL CHANGE: "<<symbol_change<<endl;
    }
};

struct Bucket{
    //ELEMENTOS DEL BUCKET
    vector<Record> records;
    //CANTIDAD DE ELEMENTOS DEL BUCKET
    int size;
    //DESBORDE DEL BUCKET
    long next_bucket;
    //PROFUNDIDAD
    long depth;

    Bucket(){
        size = 0;
        next_bucket = -1;
        depth = 1;
    }

    void showData(){
        cout<<"["<<endl;
        for(int i=0; i<size ; i++)
            records[i].showData();
        cout<<"]"<<endl;
    }
};


template<typename T>
class ExtendibleHashFile{
    private:
        string filename;
        hash<T> str_hash;
    public:
        ExtendibleHashFile(string _filename){
            this->filename = "hash.dat";
            //transformarlo al formato visto en clase sin guardarlo en memoria secundaria, solo para interactuar usando la RAM
            ifstream file(_filename, ios::binary | ios::in);
            string linea = "";
            char delimitador = ',';
            getline(file,linea);
            while(getline(file,linea)){
                Record record = Record();
                vector<string> campos;
                size_t pos = 0;
                while (((pos = linea.find(delimitador)) != string::npos)) {
                    campos.push_back(linea.substr(0, pos));
                    linea.erase(0, pos + 1);
                }
                record.ranking = stoi(campos[0]);
                record.club_name = campos[1];
                record.country = campos[2];
                record.point_score = stod(campos[3].substr(0,pos));
                record.one_year_change = stod(campos[4].substr(0,pos));
                record.previous_point_score = stod(campos[5].substr(0,pos));
                record.symbol_change = campos[6][0];

                write_record(record);
            }
            file.close();
        }
        Record search(T key); // Buscar un bucket en especifico y retornar los elementos
        vector<Record> rangeSearch(T begin_key, T end_key); // Busqueda por rango
        void add(Record record); // Añadir un elemento al archivo
        void remove(T key); //Remover un elemento del archivo
        void scanAll(); //Imprimir todo el archivo
        ~ExtendibleHashFile(){}

    private:
        void write_record(Record record){
            size_t hashcode = str_hash(record.ranking);
            bitset<D_global> bin(hashcode);
            //2- leer la pagina de datos, 
            ifstream file(this->filename, ios::in | ios::binary);
            ofstream file2(this->filename, ios::out | ios::app | ios::binary);
            if(file.is_open() && file2.is_open()){
                file.seekg((int)(bin.to_ullong())* sizeof(Bucket));
                Bucket bucket;
                file.read((char*)&bucket, sizeof(Bucket));
        
                //3- verificar si size < MAX_B,si es asi, se inserta en esa pagina y se regresa al archivo
                if(bucket.size < MAX_B){
                    bucket.records[bucket.size++] = record;
                    file.seekg((int)(bin.to_ullong())* sizeof(Bucket));
                    file2.write((char*)&bucket, sizeof(Bucket));
                }
                //4- caso contrario, crear nuevo bucket, insertar ahi, mantener el enlace
                else{
                    Bucket newBucket;
                    newBucket.records[newBucket.size++] = record;
                    bucket.next_bucket = (long)&newBucket;
                    file.seekg((int)(bin.to_ullong())* sizeof(Bucket));
                    file2.write((char*)&bucket, sizeof(Bucket));
                }
            file.close();
            file2.close();
            }else cerr<<"El archivo no se pudo abrir.\n";
        }
};

template<typename T>
Record ExtendibleHashFile<T>::search(T key){
    // 1. Encontrar el codigo binario usando el key
    size_t hashcode = str_hash(key);
    bitset<D_global> bin (hashcode);
    // 2. Encontrar su posición física en el archivo de datos
    ifstream file(this->filename, ios::binary | ios::in);
    if(file.is_open()){
        file.seekg((int)(bin.to_ullong())* sizeof(Bucket));
        Bucket bucket;
        file.read((char*)&bucket, sizeof(Bucket));
        if(bucket.size == 0) throw("No se encontro el bucket");
        for(int i=0; i<bucket.size; i++)
            if(bucket.records[i].ranking == key)
                return bucket.records[i];
        file.close();
    }else cerr<<"No se pudo abrir el archivo";
    throw("Error al ejecutar la funcion");
}

template<typename T>
vector<Record> ExtendibleHashFile<T>::rangeSearch(T begin_key, T end_key){
    size_t begin_hashcode = str_hash(begin_key);
    size_t end_hashcode = str_hash(end_key);
    throw("Falta implementar");
}

template<typename T>
void ExtendibleHashFile<T>::add(Record record){
    throw("Falta implementar");
}

template<typename T>
void ExtendibleHashFile<T>::scanAll(){
    //1- abrir el archivo de datos y mostrar todo
    ifstream file(this->filename, ios::in | ios::binary);
    while(file.peek() != EOF) {
        Bucket bucket;
        file.read((char*)&bucket, sizeof(Bucket));
        bucket.showData();
    } 
    file.close();
}

template<typename T>
void ExtendibleHashFile<T>::remove(T key){
    size_t hashcode = str_hash(key);
    throw("Falta implementar");
}