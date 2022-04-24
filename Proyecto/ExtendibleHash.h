#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#define MAX_B 5
#define D_global 8
using namespace std;

template<typename T>
struct Record{
    T primary_key;
};

template<typename T>
struct Bucket{
    //ELEMENTOS DEL BUCKET
    vector<Record<T>> records;
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
};


template<typename T, typename J>
class ExtendibleHashFile{
    private:
        string filename;
        hash<T> str_hash;
    public:
        ExtendibleHashFile(string _filename){
            this->filename = filename;
        }
        vector<Record<J>> search(T key); // Buscar un bucket en especifico y retornar los elementos
        vector<Record<J>> rangeSearch(T begin_key, T end_key); // Busqueda por rango
        void add(Record<J> record); // Añadir un elemento al registro
        void remove(T key); //Remover un elemento del archivo
        ~ExtendibleHashFile(){}
};

template<typename T, typename J>
vector<Record<J>> ExtendibleHashFile<T,J>::search(T key){
    // 1. Encontrar el codigo binario usando el key
    size_t hashcode = str_hash(key);
    bitset<D_global> bin (hashcode);
    // 2. Encontrar su posición física en el archivo de datos
    ifstream file(this->filename, ios::binary | ios::in);
    if(file.is_open()){
        file.seekg(bin* sizeof(Bucket<J>));
        Bucket<J> bucket;
        file.read((char*)&bucket, sizeof(Bucket<J>));
        if(bucket.size == 0) throw("No se encontro el bucket");
        file.close();
        return bucket.records;
    }else cerr<<"No se pudo abrir el archivo";
}

template<typename T, typename J>
vector<Record<J>> ExtendibleHashFile<T,J>::rangeSearch(T begin_key, T end_key){
    size_t begin_hashcode = str_hash(begin_key);
    size_t end_hashcode = str_hash(end_key);
    throw("Falta implementar");
}

template<typename T, typename J>
void ExtendibleHashFile<T,J>::add(Record<J> record){
    size_t hashcode = str_hash(record);
    bitset<D_global> bin(hashcode);
    ifstream inputFile(this->filename, ios::binary | ios::in);
    ofstream outputFile(this->filename, ios::trunc | ios::binary | ios::out);
    throw("Falta implementar");
}

template<typename T, typename J>
void ExtendibleHashFile<T,J>::remove(T key){
    size_t hashcode = str_hash(key);
    throw("Falta implementar");
}