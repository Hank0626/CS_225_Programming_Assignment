#include "information.cpp"
#include "helper.cpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "database.cpp"

using namespace std;

int main(){
    Database origin;
    int a = 0;
    int b = 9;
    information* lpy;
    srand(time(NULL));
    for(int i = 0; i < 100 ; i++){
        information* john = new information;
        john->setRecordID(int(rand()));
        john->P.age_group= int((rand()*2)%9);
        john->P.address.first = int(rand()*3%80);
        john->P.address.second = int(rand()*2%60);
        john->P.profession = rand()*6%8;
        john->M.risk_status = rand()%3;
        origin.person.insert(john->P,RELATION_PERSON,john->P.age_group);
    }
    lpy->setRecordID(int(rand()));
    lpy->P.age_group= int((rand()*2)%9);
    lpy->P.address.first = int(rand()*3%80);
    lpy->P.address.second = int(rand()*2%60);
    lpy->P.profession = rand()*6%8;
    lpy->M.risk_status = rand()%3;
    Neighbor<Person> see;
    see.threshold = 4;
    see.neighbors(6,lpy->P,origin.person);
    see.find_map->print();
    return 1;
}