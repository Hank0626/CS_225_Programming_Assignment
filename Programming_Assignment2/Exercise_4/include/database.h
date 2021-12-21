#ifndef DATABASE_H
#define DATABASE_H

#include "dataType.h"
#include <vector>
#include <assert.h>
#include "information.h"

using namespace std;

template<class T> class Block;
template<class T> class Relation;
class Database;
class information;
template<class T> class Neighbor;
class Graph;

enum RELATION {
    RELATION_PERSON,
    RELATION_MEDICALSTATUS,
    RELATION_REGISTRATION,
    RELATION_TREATMENT,
    RELATION_DISTANCE
};

template<class T> class Block {
    friend class Relation<T>;
    friend class Neighbor<T>;
    public:
        Block(){
            this->array.clear();
            this->overflowBuffer.clear();
        }
        T& operator[](int index) {
            return ((index < this->LENGTH) ?  this->overflowBuffer[index] : this->array[index - this->LENGTH]);
        }
        Block<T>* getNextBlock() {
            return this->ptNextBlock;
        }
        Block<T>* getPrevBlock() {
            return this->ptPrevBlock;
        }
        void setNextBlock(Block<T>* block) {
            this->ptNextBlock = block;
        }
        void setPrevBlock(Block<T>* block) {
            this->ptPrevBlock = block;
        }
        bool append(information* record,RELATION type);
        bool _append(T DATA);

        int BLOCK_ID[4] = {0,0,0,0};
        void combine(void);
        
    private:
        static const int LENGTH = 8;
        vector<T> array;
        vector<T> overflowBuffer;
        Block<T>* ptPrevBlock ;
        Block<T>* ptNextBlock ;
};

template<class T> class Relation {
    friend class Neighbor<T>;
    public:
        Relation() {
            Block<T>* dummy = new Block<T>;
            this->_dummy = dummy;
            this->_dummy->ptPrevBlock = this->_dummy;
            this->_dummy->ptNextBlock = this->_dummy;
            this->_length = 0;
        };
        Block<T>& operator[](int index) {
            assert(index < this->_length);
            Block<T>* block = this->_dummy->getNextBlock();
            for (int i=0;i<index;i++)
                block = block->getNextBlock();
            return block;
        }
        int getLength() {
            return this->_length;
        }
        void print(void);
        bool insert(T record,RELATION type,int key);
        bool remove(information* record,RELATION type);
        Block<T>* retrieve(int key,RELATION type);

        bool merge(int blockID_1, int blockID_2,RELATION type);
        void sort(RELATION type);
        bool split(int blockID, int splitPosition,RELATION type);
        void swap(Block<T>* A, Block<T>* B); 
    private:
        int _length;
        Block<T>* _dummy;
};


//this class is used for input data and divide them into different classes.
class information  {
    public:
        Person P;
        Treatment T;
        MedicalStatus M;
        Registration R;
        void setRecordID(int recordID) {
            this->_recordID = recordID;
            this->P.setRecordID(recordID);
            this->M.setRecordID(recordID);
            this->T.setRecordID(recordID);
            this->R.setRecordID(recordID);
            return;
        }
        int getRecordID() {
            return this->_recordID;
        }
    private:
        int _recordID;
};

class Database {
    public:
        Relation<Person>        person;                     //search by age_group
        Relation<MedicalStatus> medicalStatus;              //search by medicalStatus: 0: no risk; 1: low risk; 2: medium risk; 3: high risk;
        Relation<Registration>  registration;               //search by registation date
        Relation<Treatment>     treatment;                  //search by treatment: 0: typeA; 1: typeB; 2: typeC
        int _insert(information* DATA){
            int result = 1;
            result &= this->person.insert(DATA->P,RELATION_PERSON,DATA->P.age_group);
            result &= this->treatment.insert(DATA->T,RELATION_TREATMENT,DATA->T.day);
            result &= this->registration.insert(DATA->R,RELATION_TREATMENT,DATA->R.regist_date);
            result &= this->medicalStatus.insert(DATA->M,RELATION_MEDICALSTATUS,DATA->M.risk_status);
            return result;
}  
        int _remove(information* DATA){
            int result = 1;
            result &= this->person.remove(DATA,RELATION_PERSON);
            result &= this->treatment.remove(DATA,RELATION_TREATMENT);
            result &= this->registration.remove(DATA,RELATION_TREATMENT);
            result &= this->medicalStatus.remove(DATA,RELATION_MEDICALSTATUS);
            return result;
        }
};

class Graph{
    public:
        Graph(){
            this->numbers = 0;
            this->edges.clear();
            this->vertices.clear();
        }
        int numbers; 
        int distance;
        vector<int> vertices;
        vector<int> edges;
        void print(void){
                cout << this->vertices[0] << " has "<< this->numbers << " neighbors" << " in distance " << this->distance << endl;
                for(int i = 1; i <= this->numbers; i++){
                    cout << this->vertices[i] << " ";
                    cout << "their distance is " << this->edges[i-1] << endl;
            }
        }

};

template<class T> class Neighbor {
    public:
        Neighbor(){
            this->find_map = new Graph;
        }
        int threshold;
        Graph* find_map;
        int distance(Person A, Person B);
        Graph* neighbors(int num, Person A,Relation<Person> distan);
        
};


#endif