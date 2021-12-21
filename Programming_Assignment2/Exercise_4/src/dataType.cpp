#include "dataType.h"
#include "database.h"
#include <vector>
using namespace std;

int Neighbor::distance(Person* A, Person* B){
    int dis = 0;
    dis = (A->address.first - B->address.first)*(A->address.first - B->address.first) + (A->address.second - B->address.second)*(A->address.second - B->address.second);
    return dis;
}

int Neighbor::neighbors(int num){
    int bound = num*this->threshold;
}