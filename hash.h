#include <fstream>
#include <iostream>
#include <list>
#include <map>
#define MAX_B 3
using namespace std;

struct Record {
  char nombre[30];
  char carrera[20];
  int ciclo;

  void setData() {
    cout << "Alumno:";
    cin >> nombre;
    cout << "Carrera: ";
    cin >> carrera;
    cout << "Ciclo: ";
    cin >> ciclo;
  }

  void showData() {
    cout << "\nNombre: " << nombre;
    cout << "\nCarrera: " << carrera;
    cout << "\nCiclo : " << ciclo;
  }
};

struct Bucket{
    Record records[MAX_B];
    int size;
    long next_bucket;

    void showData(){
        cout<<"["<<endl;
        for(int i=0; i<size ; i++)
            records[i].showData();
        cout<<"]"<<endl;
    }

    Bucket(){
        size = 0;
        next_bucket = -1;
    }
};

class StaticHashFile {
private:
  string fileName;
  //definir una cantidad maxima de paginas primarias
  int N;
  hash<string> str_hash;
    
public:
  StaticHashFile(string _fileName, int _N) {
    this->fileName = _fileName;    
    this->N = _N;
  }

  ~StaticHashFile() {  }

 void write_record(Record record){
       //1- usando una funcion hashing ubicar la pagina de datos
      size_t hashcode = str_hash(record.nombre);
      int primary_page = hashcode % this->N; // página
      
      //2- leer la pagina de datos, 
      ifstream file(this->fileName, ios::in | ios::binary);
      ofstream file2(this->fileName, ios::out | ios::app | ios::binary);
      if(file.is_open() && file2.is_open()){
        file.seekg(primary_page* sizeof(Bucket));
        Bucket bucket;
        file.read((char*)&bucket, sizeof(Bucket));
        
        //3- verificar si size < MAX_B,si es asi, se inserta en esa pagina y se regresa al archivo
        if(bucket.size < MAX_B){
            bucket.records[bucket.size++] = record;
            file.seekg(primary_page* sizeof(Bucket));
            file2.write((char*)&bucket, sizeof(Bucket));
        }
        //4- caso contrario, crear nuevo bucket, insertar ahi, mantener el enlace
        else{
            Bucket newBucket;
            newBucket.records[newBucket.size++] = record;
            bucket.next_bucket = (long)&newBucket;
            file.seekg(primary_page* sizeof(Bucket));
            file2.write((char*)&bucket, sizeof(Bucket));
        }
      file.close();
      file2.close();
      }else cerr<<"El archivo no se pudo abrir.\n";
      
  }


  Record search(string nombre){
      //1- usando una funcion hashing ubicar la pagina de datos
      size_t hashcode = str_hash(nombre);
      int primary_page = hashcode % this->N;
      //2- leer la pagina de datos, ubicar el registro que coincida con el nombre
      fstream file(this->fileName, ios::in | ios::binary);
      file.seekg(primary_page* sizeof(Bucket));
      Bucket bucket;
      file.read((char*)&bucket, sizeof(Bucket));
      Record record;
      bool existe = false;
      for(int i=0; i<bucket.size; i++)
        if(bucket.records[i].nombre == nombre){
            record = bucket.records[i];
            existe = true;
        }
      //3- si no se encuentra el registor en esa pagina, ir a la pagina enlazada
      if(existe == false){
          int lazed_page = bucket.next_bucket;
          file.seekg(lazed_page* sizeof(Bucket));
          Bucket bucket_o;
          file.read((char*)&bucket_o, sizeof(Bucket));
          for(int i=0; i<bucket_o.size; i++){
            if(bucket_o.records[i].nombre == nombre){
                record = bucket_o.records[i];
                existe = true;
            }
          }
        if(!existe){ 
            cerr<<"No se encontro el archivo";
        }
      }
      file.close();
      return record;
  }

  void scanAll(){
      //1- abrir el archivo de datos y mostrar todo
      ifstream file(this->fileName, ios::in | ios::binary);
      while(file.peek() != EOF) {
          Bucket bucket;
          file.read((char*)&bucket, sizeof(Bucket));
          bucket.showData();
      } 
      file.close();
  }
};