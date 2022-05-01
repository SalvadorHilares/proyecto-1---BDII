
#include "Utils.h"

struct Record{
    char ranking [10]{' '};
    char club_name [50]{' '};
    char country [30]{' '};
    char point_score [10]{' '};
    char one_year_change [10]{' '};
    char previous_point_score [10]{' '};
    char symbol_change [1]{' '};

    int nextDel;
    char ref;

    Record() = default;
    Record( 
            string  ranking_,
            string  club_name_,
            string  country_,
            string  point_score_,
            string  one_year_change_,
            string  previous_point_score_,
            string  symbol_change_
          )
          {
            strcpy(ranking, ranking_.c_str());              
            strcpy(club_name, club_name_.c_str());
            strcpy(country, country_.c_str());
            strcpy(point_score, point_score_.c_str());
            strcpy(one_year_change, one_year_change_.c_str());
            strcpy(previous_point_score, previous_point_score_.c_str());
            strcpy(symbol_change, symbol_change_.c_str());

            this->nextDel = 0;
            this->ref = 'd';

          }

    const char* get_key()const{
        return ranking;
    }

    bool equal_key(const char* key){
        return strcmp(this->ranking, key) == 0;
    }

    bool less_than_key(const char* key){
        return strcmp(this->ranking, key) < 0;
    }

    bool greater_than_key(const char* key){
        return strcmp(this->ranking, key) > 0;
    }

    bool less_or_equal(const char* key){
        return strcmp(this->ranking, key) <= 0;
    }

    bool greater_or_equal(const char* key){
        return strcmp(this->ranking, key) >= 0;
    }

    bool operator < (Record& other){
        return strcmp(this->ranking, other.ranking) < 0;
    }

    bool operator == (Record& other){
        return strcmp(this->ranking, other.ranking) == 0;
    }
    /*void showData(){
        cout<<"RANKING: "<<ranking<<endl;
        cout<<"CLUB_NAME: "<<club_name<<endl;
        cout<<"COUNTRY: "<<country<<endl;
        cout<<"POINT_SCORE: "<<point_score<<endl;
        cout<<"ONE YEAR CHANGE: "<<one_year_change<<endl;
        cout<<"PREVIOUS POINT SCORE: "<<previous_point_score<<endl;
        cout<<"SYMBOL CHANGE: "<<symbol_change<<endl;
    }*/
};