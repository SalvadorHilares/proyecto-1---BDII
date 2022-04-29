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
    //DESBORDE DEL BUCKET
    long next_bucket;
    //PROFUNDIDAD
    long depth;

    Bucket(){
        next_bucket = -1;
        depth = 2;
    }
    bool isFull(){
        return (records.size() == MAX_B);
    }
	bool isEmpty(){
        return records.size() == 0;
    }
	int insert(Record key){
        if (isFull()) return -1;
	    for(int i = 0; i < records.size(); i++)
		    if (records.at(i).ranking == key.ranking)
			    return 0;
	    records.push_back(key);
	    return 1;
    }
	bool search(int ranking){
        for(int i = 0; i < records.size(); i++)
		    if (records.at(i).ranking == ranking)
			    return true;
	    return false;
    }
	void copy(vector <Record> temp){
        for(int i = 0; i < records.size(); i++)
            temp.push_back(records.at(i));
        records.clear();
    }
	void del(int key){
        for(int i = 0; i < records.size(); i++)
		    if (records.at(i).ranking == key)
			    records.erase(records.begin() + i);
	    throw("This key is not found");
    }
};


template<typename T>
class ExtendibleHashFile{
    private:
        string filename;
        hash<T> str_hash;
        vector <Bucket> buckets;
    public:
        ExtendibleHashFile(string _filename){
            this->filename = "hash.dat";
            //transformarlo al formato visto en clase sin guardarlo en memoria secundaria, solo para interactuar usando la RAM
            ifstream file(_filename, ios::in);
            string linea = "";
            string delimitador = ",";
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
                record.point_score = stod(campos[3]);
                record.one_year_change = stod(campos[4]);
                record.previous_point_score = stod(campos[5]);
                record.symbol_change = linea[0];

                write_record(record);
            }
            file.close();
        }
        vector<Record> search(T key); // Buscar un bucket en especifico y retornar los elementos
        vector<Record> rangeSearch(T begin_key, T end_key); // Busqueda por rango
        void add(Record record); // Añadir un elemento al registro
        void remove(T key); //Remover un elemento del archivo
        ~ExtendibleHashFile(){}
};

template<typename T>
vector<Record> ExtendibleHashFile<T>::search(T key){
    // 1. Encontrar el codigo binario usando el key
    size_t hashcode = str_hash(key);
    bitset<D_global> bin (hashcode);
    // 2. Encontrar su posición física en el archivo de datos
    ifstream file(this->filename, ios::binary | ios::in);
    if(file.is_open()){
        file.seekg(bin* sizeof(Bucket));
        Bucket bucket;
        file.read((char*)&bucket, sizeof(Bucket));
        if(bucket.size == 0) throw("No se encontro el bucket");
        file.close();
        return bucket.records;
    }else cerr<<"No se pudo abrir el archivo";
}

template<typename T>
vector<Record> ExtendibleHashFile<T>::rangeSearch(T begin_key, T end_key){
    size_t begin_hashcode = str_hash(begin_key);
    size_t end_hashcode = str_hash(end_key);
    throw("Falta implementar");
}

template<typename T>
void ExtendibleHashFile<T>::add(Record record){
    size_t hashcode = str_hash(record);
    bitset<D_global> bin(hashcode);
    ifstream inputFile(this->filename, ios::binary | ios::in);
    ofstream outputFile(this->filename, ios::trunc | ios::binary | ios::out);
    throw("Falta implementar");
}

template<typename T>
void ExtendibleHashFile<T>::remove(T key){
    size_t hashcode = str_hash(key);
    throw("Falta implementar");
}