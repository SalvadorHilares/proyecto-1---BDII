#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
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
    
    void showData(){
        cout<<"Ranking: "<<ranking<<endl;
        cout<<"Club name: "<<club_name<<endl;
        cout<<"Country: "<<country<<endl;
        cout<<"Point score: "<<point_score<<endl;
        cout<<"One year change: "<<one_year_change<<endl;
        cout<<"Previous point score: "<<previous_point_score<<endl;
        cout<<"Symbol change: "<<symbol_change<<endl;
        cout<<"------------------------------------------------"<<endl;
    }
};

struct Bucket{
    //ELEMENTOS DEL BUCKET
    vector<Record> records{MAX_B};
    //PROFUNDIDAD
    long depth;
    //numero de records
    int size;

    Bucket(){
        size = 0;
        depth = 2;
    }
    bool isFull(){
        return (records.size() == size);
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
		    if (records.at(i).ranking == key){
			    records.erase(records.begin() + i);
                return;
            }
	    throw("This key is not found");
    }
};

// Search!! RangeSearch Add Remove
template<typename T>
class ExtendibleHashFile{
    private:
        string filename;
        vector <Bucket> buckets;
        int depthoverf;
    public:
        ExtendibleHashFile(string _filename){
            this->filename = filename;
            depthoverf=8;
            for(int i = 0; i <  (1 << depthoverf); i++)
			    buckets.push_back(Bucket());
            //transformarlo al formato visto en clase sin guardarlo en memoria secundaria, solo para interactuar usando la RAM
            ifstream file(_filename, ios::in);
            string linea = "";
            string delimitador = ",";
            getline(file,linea);
            while(getline(file,linea)){
                Record record = Record();
                vector<string> campos;
                int pos = 0;
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

        private:
            void split(int bucket_num);
            void reinsert(int bucket_num);
            void Doubledirectory();
            int hash (int n){
	            return n&( (1 << depthoverf) - 1);
            }
};

template<typename T>
void ExtendibleHashFile<T>::search(T key){
    int hashcode = hash(key);
    bool encontrado = buckets[hashcode].search(key);
	if (!encontrado)
		cerr<<"No se encontro el dato en el archivo"<<endl;
}


template<typename T>
void ExtendibleHashFile<T>::rangeSearch(T begin_key, T end_key){
    for(int i=begin_key;i<=end_key;i++){
        int hash_code = hash(i);
        bool encontrado = buckets[hash_code].search(i);
        if (!encontrado){
            cerr<<"No se encontro el dato en el archivo"<<endl;
            break;
        }
    }
}

template<typename T>
void ExtendibleHashFile<T>::remove(T key){
    int hashcode = hash(key);
	buckets[hashcode].remove(key);
}


template<typename T>
void ExtendibleHashFile<T> :: Doubledirectory(){
	for(int i = 0; i < (1 << depthoverf); i++)
		buckets.push_back(buckets.at(i));
    depthoverf++;
}

template<typename T>
void ExtendibleHashFile<T> :: reinsert(int bucket_num){
	vector <Record> temp;
	buckets[bucket_num].copy(temp);
	for(int i = 0; i < temp.size(); i++){
		Record key = temp.at(i);
		int bucket_num  = hash(key.ranking);
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
	if (depthoverf == localdepth)
		Doubledirectory();
	int mirrorindex = bucket_num ^ (1 << localdepth);
	buckets[bucket_num].depth++;
	localdepth++;
	buckets[mirrorindex] = Bucket();
    buckets[mirrorindex].depth = localdepth;
    buckets[mirrorindex].size = MAX_B;
    int num = 1 << localdepth;
	for(int i = mirrorindex + num; i < (1 << depthoverf); i += num)
		buckets[i] = buckets[mirrorindex];
	for(int i = mirrorindex - num; i >=0 ; i -= num)
		buckets[i] = buckets[mirrorindex];
	reinsert(bucket_num);
}

template<typename T>
void ExtendibleHashFile<T>::add(Record record){
    int hashcode = hash(record.ranking);
    int temp = buckets[hashcode].insert(record);
    if (temp == -1){
        split(hashcode);
		add(record);
	}
}