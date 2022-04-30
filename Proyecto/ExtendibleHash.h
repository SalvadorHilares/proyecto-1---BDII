#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#define MAX_B 5
using namespace std;

struct Record{
    int ranking;
    string club_name;
    string country;
    double point_score;
    double one_year_change;
    double previous_point_score;
    char symbol_change;
    /*
    void showData(){
        cout<<"RANKING: "<<ranking<<endl;
        cout<<"CLUB_NAME: "<<club_name<<endl;
        cout<<"COUNTRY: "<<country<<endl;
        cout<<"POINT_SCORE: "<<point_score<<endl;
        cout<<"ONE YEAR CHANGE: "<<one_year_change<<endl;
        cout<<"PREVIOUS POINT SCORE: "<<previous_point_score<<endl;
        cout<<"SYMBOL CHANGE: "<<symbol_change<<endl;
    }*/
    void showData(){
    cout<<ranking;
    cout<<club_name;
    cout<<country;
    cout<<point_score;
    cout<<one_year_change;
    cout<<previous_point_score;
    cout<<symbol_change<<endl;
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
        for(int i = 0; i < records.size(); i++){
		    if (records.at(i).ranking == ranking){
			    records.at(i).showData();
                return true;
            }
        }
	    return false;
    }
	void copy(vector <Record> temp){
        for(int i = 0; i < records.size(); i++)
            temp.push_back(records.at(i));
        records.clear();
    }
	void remove(int key){
        for(int i = 0; i < records.size(); i++)
		    if (records.at(i).ranking == key)
			    records.erase(records.begin() + i);
	    throw("This key is not found");
    }
};

// Search!! RangeSearch Add Remove
template<typename T>
class ExtendibleHashFile{
    private:
        string filename;
        hash<T> str_hash;
        vector <Bucket> buckets;
        int depthoverf;
    public:
        ExtendibleHashFile(string _filename){
            this->filename = filename;
            depthoverf=8;
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

                add(record);
            }
            file.close();
        }
        void search(T key);     //---
        void rangeSearch(T begin_key, T end_key); //---
        void add(Record record); 
        void remove(T key); //---
        ~ExtendibleHashFile(){}


        //
        	void split(int bucket_num);
            void reinsert(int bucket_num);
            void Doubledirectory();
        //
};

template<typename T>
void ExtendibleHashFile<T>::search(T key){
    size_t hashcode = str_hash(key);
    bool encontrado = buckets[hashcode].search(key);
	if (!encontrado)
		cout << key << "El registro no existe" << endl;
}
	



template<typename T>
void ExtendibleHashFile<T>::rangeSearch(T begin_key, T end_key){
    T key_aux=begin_key;
    size_t begin_hashcode = str_hash(begin_key);
    size_t end_hashcode = str_hash(end_key);
    for(size_t i=begin_hashcode;i<end_hashcode;i++){
        bool encontrado = buckets[i].search(key_aux);
        if (!encontrado)
        cout << key_aux << "El registro no existe" << endl;
        key_aux++;
    }

}

template<typename T>
void ExtendibleHashFile<T>::remove(T key){
    size_t hashcode = str_hash(key);
	buckets[hashcode].remove(key);
}



template<typename T>
void ExtendibleHashFile<T> :: Doubledirectory(){
	for(int i = 0; i < (1 << depthoverf); i++)
		buckets.push_back(buckets.at(i));
    depthoverf++;
	//cout << "line 94 " << this->globaldepth << endl;;
}

template<typename T>
void ExtendibleHashFile<T> :: reinsert(int bucket_num){
	vector <Record> temp;
	buckets[bucket_num].copy(temp);
	for(int i = 0; i < temp.size(); i++){
		Record key = temp.at(i);
		size_t bucket_num  = str_hash(key.ranking);
		//cout << "new bucket_num" << bucket_num << endl;
		int banderita = buckets[bucket_num].insert(key);
		if (banderita == -1){
			split(bucket_num);
			buckets[bucket_num].insert(key);
		}
	}
}

template<typename T>
void ExtendibleHashFile<T> :: split(int bucket_num){
	int localdepth = buckets[bucket_num].depth;
	//cout << globaldepth << " " << localdepth << endl;
	if (depthoverf == localdepth)
		Doubledirectory();
	int mirrorindex = bucket_num ^ (1 << localdepth);
	buckets[bucket_num].depth++;
	localdepth++;
	//cout << buckets[bucket_num]->getdepth() << endl;
	buckets[mirrorindex] = Bucket();
    buckets[mirrorindex].depth=localdepth;
    int num = 1 << localdepth;
	for(int i = mirrorindex + num; i < (1 << depthoverf); i += num)
		buckets[i] = buckets[mirrorindex];
	for(int i = mirrorindex - num; i >=0 ; i -= num)
		buckets[i] = buckets[mirrorindex];
	reinsert(bucket_num);
}









template<typename T>
void ExtendibleHashFile<T>::add(Record record){
    size_t hashcode = str_hash(record.ranking);
    int temp = buckets[hashcode].insert(record);
    if (temp == -1){
        cout << "splitting bucketnum " << hashcode << endl;
        split(hashcode);
		add(record);
	}
	else if (temp == 0){
		cout << "La llave ya existe" << endl;
	}
	else{
		cout <<"El registro con llave: "<< record.ranking << " ya fue insertado "<<endl;
	}
}























/*
template<typename T>
void ExtendibleHashFile<T>::add(Record record){
    size_t hashcode = str_hash(record);
    bitset<D_global> bin(hashcode);
    ifstream inputFile(this->filename, ios::binary | ios::in);
    ofstream outputFile(this->filename, ios::trunc | ios::binary | ios::out);
    throw("Falta implementar");
}
*/




/*
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
*/