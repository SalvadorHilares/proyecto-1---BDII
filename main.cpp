#include "ExtendibleHash.h"

int main(){
    ExtendibleHashFile<int>* file = new ExtendibleHashFile<int>("Soccer_Football_Clubs_Ranking.csv");
    file->scanAll();
    return 0;
}