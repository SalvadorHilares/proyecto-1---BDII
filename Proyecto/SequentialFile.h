#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include "Utils.h"

#define AddressType int32_t
#define INVALID 'x'
#define MAX_CAPACITY 5

using namespace std;

enum FileID {AUXFILE,DATAFILE};
template <class Record, class Key>
class SequentialFile{
private:
    string DATAFILE_DP;
    string AUXFILE_DP;
    struct RecordData{
        AddressType pos;
        char ref;
        Record record;
        RecordData(){
            pos = -1;
        }
        RecordData(AddressType pos_, char ref_, Record record_){
            pos = pos_;
            ref = ref_;
            record = record_;
        }
    };
    void write_record(AddressType pos, fstream& file, Record& record, FileID FileID);
    void first_write_record_data(fstream& file, AddressType pos, char ref);
    void insert_with_sequential_search(Record& record);
    void read_record(AddressType pos, fstream& file, Record& record, FileID FileID);
    void first_read_record_data(fstream& file, AddressType& pos, char& ref);
    int number_of_records(fstream& file, FileID FileID);
    int number_of_records(string filename, FileID FileID);
    static bool compare_records(Record& r1, Record& r2);
    bool is_empty(FileID FileID);
    bool is_full();
    bool is_removable();
    void read_status_for_deleted_record(fstream&file, bool& status);
    void write_status_for_deleted_record(fstream&file, bool status);
public:
    SequentialFile(string DATAFILE_DP_, string AUXFILE_DP_);
    void insert_all(vector<Record> &record);
    void add_record(Record record);
    pair<RecordData,RecordData> sequential_search(Key key);
    vector<Record> search_record(Key key);
    vector<Record> search_per_range(Key start, Key end);
    void remove_record(Key key);
    vector<Record> load();
};

#endif // SEQUENTIAL_H