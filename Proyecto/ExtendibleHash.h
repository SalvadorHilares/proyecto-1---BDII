#include <fstream>
#include <iostream>
#include <vector>
#define MAX_B 5
using namespace std;

struct Record{

};

struct Bucket{
    //ELEMENTOS DEL BUCKET
    Record records[MAX_B];
    //CANTIDAD DE ELEMENTOS DEL BUCKET
    int size;
    //NUMERO DE BITS
    long long D;
};


template<typename T>
class ExtendibleHashFile{
    private:
        string filename;
        hash<T> str_hash;
    public:
        ExtendibleHashFile(string _filename){
            this->filename = filename;
        }
        vector<Record> search(T key);
        vector<Record> rangeSearch(T begin_key, T end_key);
        void add(Record record);
        void remove(T key); //Remover un elemento del archivo
        long depth(Record record); //Profundidad de un registro
        ~ExtendibleHashFile(){}
};

template<typename T>
vector<Record> ExtendibleHashFile<T>::search(T key){
    size_t hashcode = str_hash(key);
    throw("Falta implementar");
}

template<typename T>
vector<Record> ExtendibleHashFile<T>::rangeSearch(T begin_key, T end_key){
    size_t begin_hashcode = str_hash(begin_key);
    size_t end_hashcode = str_hash(end_key);
    throw("Falta implementar");
}

template<typename T>
void ExtendibleHashFile<T>::remove(T key){
    size_t hashcode = str_hash(key);
    throw("Falta implementar");
}

template<typename T>
long ExtendibleHashFile<T>::depth(Record record){
    throw("Falta implementar");
}