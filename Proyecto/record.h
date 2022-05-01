
#include "Utils.h"

struct record{
    char ranking [10]{' '};
    char club_name [50]{' '};
    char country [30]{' '};
    char point_score [10]{' '};
    char one_year_change [10]{' '};
    char previous_point_score [10]{' '};
    char symbol_change [1]{' '};

    int nextDel;
    char ref;

    record() = default;
    record( 
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

    bool operator < (record& other){
        return strcmp(this->ranking, other.ranking) < 0;
    }

    bool operator == (record& other){
        return strcmp(this->ranking, other.ranking) == 0;
    }

    void set_ranking(string ranking_){
        strcpy(ranking, ranking_.c_str());
    }

    void set_club_name(string club_name_){
        strcpy(ranking, club_name_.c_str());
    }

    void set_country(string country_){
        strcpy(ranking, country_.c_str());
    }

    void set_point_score(string point_score_){
        strcpy(ranking, point_score_.c_str());
    }

    void set_one_year_change(string one_year_change_){
        strcpy(ranking, one_year_change_.c_str());
    }

    void set_previous_point_score(string previous_point_score_){
        strcpy(ranking, previous_point_score_.c_str());
    }

    void set_symbol_change(string symbol_change_){
        strcpy(ranking, symbol_change_.c_str());
    }
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