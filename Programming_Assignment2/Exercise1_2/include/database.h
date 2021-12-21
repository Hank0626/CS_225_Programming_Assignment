#ifndef DATABASE_H
#define DATABASE_H

#include "dataType.h"
#include <vector>
#include <assert.h>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;

template<class T> class Block;
template<class T> class Relation;
class Database;

person<int>* fourToOne(Person pp, MedicalStatus pms, Registration preg, Treatment ptm);
void oneToFour(person<int> P, Person& pp, MedicalStatus& pms, Registration& preg, Treatment& ptm);


template<class T> class Block {
    friend class Relation<T>;
    public:
        Block() {
            this->array.clear();
            this->overflowBuffer.clear();
            // random init block id
            this->BLOCK_ID = rand();
        }
        static const int MAX_LENGTH = 8;
        unsigned int BLOCK_ID;
        std::vector<T> array;
        std::vector<T> overflowBuffer;
        bool full() {
            // if one of array and overflowBuffer is full, then this block is full
            return ((int)array.size() == MAX_LENGTH || (int)overflowBuffer.size() == MAX_LENGTH);
        }
        int size() {
            if ((int)array.size() != 0) return (int)array.size();
            else return (int)overflowBuffer.size();
        }
        void Sort();
};

template<class T> void Block<T>::Sort() {
    // sort the elements in block and put all elements from overflowBuffer to array
    std::sort(this->overflowBuffer.begin(), this->overflowBuffer.end());
    overflowBuffer.swap(array);
    overflowBuffer.clear();
}

template<class T> class Relation {
    public:
        T operator[](int key){
            return this->retrieve(key);
        };
        void print(string title);
        bool insert(T record);
        bool remove(int key);
        T retrieve(int key);
        bool merge(int blockID_1, int blockID_2);
        bool merge(typename list< Block<T> >::iterator iter_1, typename list< Block<T> >::iterator iter_2);
        typename list< Block<T> >::iterator split(int blockID, int splitPosition);
        typename list< Block<T> >::iterator split(typename list< Block<T> >::iterator iter, int splitPosition);
        bool search(int key);
        void getAllData(vector<T>& res);
    private:
        list< Block<T> > blocks;
};

template<class T> void Relation<T>::getAllData(vector<T>& res) {
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter) {
        vector<T>& A = (iter->full()) ? iter->array : iter->overflowBuffer;
        for (int i=0;i<(int)A.size();i++)
            res.push_back(A[i]);
    }
    return;
}

template<class T> void Relation<T>::print(string title) {
    // formatted output
    cout << "====================" << endl;
    cout << title << endl;
    cout << "====================" << endl;
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter) {
        vector<T>& A = (iter->full()) ? iter->array : iter->overflowBuffer;
        for (int i=0;i<(int)A.size();i++)
        A[i].print();
    }
    cout << "====================" << endl;
    cout << endl;
    return;
}


template<class T> bool Relation<T>::insert(T record) {
    bool all_full = true;
    // iterate through the list
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter)
    if (!iter->full()) { // if this block is not full, insert into it
        iter->overflowBuffer.push_back(record);
        // if after insertion the block is full, sort it.
        if (iter->full()) iter->Sort();
        all_full = false;
        return true;
    }

    // if new block is needed
    if (blocks.empty() || all_full) {
        Block<T> newBlock;
        newBlock.overflowBuffer.push_back(record);
        blocks.push_back(newBlock);
        return true;
    }

    // unreachable
    return false;
}

template<class T> bool Relation<T>::remove(int key) {
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter) {
        vector<T>& A = (iter->full()) ? iter->array : iter->overflowBuffer;
        for (int i=0;i<(int)A.size();i++)
        if (A[i].getRecordID() == key) {
            bool full = iter->full();
            // delete this element
            swap(A[i], A[(int)A.size()-1]);
            A.pop_back();
            if (full) { // if after deletion the block is not full, put all elements back into overflowBuffer
                iter->array.swap(iter->overflowBuffer);
                iter->array.clear();
            }
            if (iter->size() == 0)
                this->blocks.erase(iter);
            return true;
        }
    }
    return false;
}

template<class T> T Relation<T>::retrieve(int key) {
    // search through the link
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter) {
        vector<T>& A = (iter->full()) ? iter->array : iter->overflowBuffer;
        for (int i=0;i<(int)A.size();i++)
        if (A[i].getRecordID() == key)
        return A[i];
    }
    T x;
    x.setRecordID(-1);
    return x;
}

template<class T> bool Relation<T>::search(int key) {
    // if key not in the relation, return an instance with an ID of -1
    T x = this->retrieve(key);
    return (x.getRecordID() != -1);
}

template<class T> bool Relation<T>::merge(int blockID_1, int blockID_2) {
    // merge two block. They need not to be adjacent.
    // append the second block behind the first block.
    // if after merge, the block size is exceeded, merge fails and do nothing. return false.
    typename list< Block<T> >::iterator iter_1, iter_2, iter;
    for (iter = this->blocks.begin(); iter != this->blocks.end(); ++iter)
    if (iter->BLOCK_ID == blockID_1) iter_1 = iter;
    else if (iter->BLOCK_ID == blockID_2) iter_2 = iter;

    return this->merge(iter_1, iter_2);
}

template<class T> bool Relation<T>::merge(typename list< Block<T> >::iterator iter_1, typename list< Block<T> >::iterator iter_2) {
    if (iter_1->size() + iter_2->size() <= iter_1->MAX_LENGTH) {
        // append the second one to the first one
        iter_1->overflowBuffer.insert(iter_1->overflowBuffer.end(), iter_2->overflowBuffer.begin(), iter_2->overflowBuffer.end());
        if (iter_1->full()) 
            iter_1->Sort();
        this->blocks.erase(iter_2);
        return true;
    }
    // merge fail
    return false;
}

template<class T> typename list< Block<T> >::iterator Relation<T>::split(int blockID, int splitPosition) {
    // split like python.
    typename list< Block<T> >::iterator iter;
    for (iter = this->blocks.begin(); iter != this->blocks.end(); ++iter)
    if (iter->BLOCK_ID == blockID)
    return this->split(iter, splitPosition);
}

template<class T> typename list< Block<T> >::iterator Relation<T>::split(typename list< Block<T> >::iterator iter, int splitPosition) {
    Block<T> newBlock;
    if (splitPosition >= 0)
        newBlock.overflowBuffer.insert(newBlock.overflowBuffer.end(), iter.begin(), iter.begin()+splitPosition-1);
    else
        newBlock.overflowBuffer.insert(newBlock.overflowBuffer.end(), iter.begin(), iter.end()+splitPosition+1);
    this->blocks.insert(iter+1, newBlock);
    return iter+1;
}

class Database {
    public:
        bool search(person<int> per);           // true if in the database
        bool search(person<int>* per);
        bool search(int ID);
        void insert(person<int> per);
        void insert(person<int>* per);
        person<int> retrieve(int ID);
        bool remove(int ID);                    // false if not in the database 
        bool modify(int ID, person<int> per);   // false if not in the database 
        bool modify(int ID, person<int>* per);  // false if not in the database 
        void print();
        void getReportList(vector< person<int> >& reportList);
    private:
        Relation<Person>        personInfo;           
        Relation<MedicalStatus> medicalStatusInfo;       
        Relation<Registration>  registrationInfo;
        Relation<Treatment>     treatmentInfo;
};

void Database::getReportList(vector< person<int> >& reportList) {
    vector<Person> pps;
    vector<MedicalStatus> pmss;
    vector<Registration> pregs;
    vector<Treatment> ptms;
    this->personInfo.getAllData(pps);
    this->medicalStatusInfo.getAllData(pmss);
    this->registrationInfo.getAllData(pregs);
    this->treatmentInfo.getAllData(ptms);
    for (int i=0;i<(int)pps.size();i++)
    reportList.push_back(*fourToOne(pps[i], pmss[i], pregs[i], ptms[i]));
    return;
}

void Database::print() {
    personInfo.print("PERSON");
    medicalStatusInfo.print("MEDICALSTATUS");
    registrationInfo.print("REGISTRATION");
    treatmentInfo.print("TREATMENT");
    return;
}


bool Database::search(person<int> per) {
    int ID = per.identification;
    return personInfo.search(ID);
}

bool Database::search(person<int>* per) {
    return this->search(*per);
}

bool Database::search(int ID) {
    return personInfo.search(ID);
}

void Database::insert(person<int> per) {
    Person pp;
    MedicalStatus pms;
    Registration preg;
    Treatment ptm;
    oneToFour(per, pp, pms, preg, ptm);
    this->personInfo.insert(pp);
    this->medicalStatusInfo.insert(pms);
    this->registrationInfo.insert(preg);
    this->treatmentInfo.insert(ptm);
    return;
}

void Database::insert(person<int>* per) {
    this->insert(*per);
}

person<int> Database::retrieve(int ID) {
    return *fourToOne(personInfo.retrieve(ID), medicalStatusInfo.retrieve(ID), registrationInfo.retrieve(ID), treatmentInfo.retrieve(ID));
}

bool Database::remove(int ID) {
    bool result = this->personInfo.remove(ID);
    result &= this->medicalStatusInfo.remove(ID);
    result &= this->registrationInfo.remove(ID);
    result &= this->treatmentInfo.remove(ID);
    return result;
}

bool Database::modify(int ID, person<int> per) {
    bool result = this->personInfo.remove(ID);
    result &= this->medicalStatusInfo.remove(ID);
    result &= this->registrationInfo.remove(ID);
    result &= this->treatmentInfo.remove(ID);
    if (result) this->insert(per);
    return result;
}

bool Database::modify(int ID, person<int>* per) {
    return this->modify(ID, *per);
}

person<int>* fourToOne(Person pp, MedicalStatus pms, Registration preg, Treatment ptm) {
    person<int>* P          = new person<int>;
    P->name                 = pp.name;
    P->email                = pp.email;
    P->profession           = pp.profession;
    P->birthday             = pp.birthday;
    P->age_group            = pp.age_group;

    P->risk_status          = pms.risk_status;

    P->priority             = preg.priority;
    P->treatment_type       = preg.treatment_type;
    P->withdrawal           = preg.withdrawal;
    P->letter               = preg.letter;
    P->regist               = preg.regist;
    P->treated              = preg.treated;
    P->wait                 = preg.wait;
    P->deadline             = preg.deadline;
    P->withdraw_date        = preg.withdraw_date;
    P->waiting_time         = preg.waiting_time;
    P->regist_date          = preg.regist_date;
    P->regist_time          = preg.regist_time;

    P->treatment_loc        = ptm.location;  
    P->treat_date           = ptm.day;

    P->identification       = pp.getRecordID();
    return P;  
}

void oneToFour(person<int> P, Person& pp, MedicalStatus& pms, Registration& preg, Treatment& ptm) {
    pp.setRecordID(P.identification);
    pms.setRecordID(P.identification);
    preg.setRecordID(P.identification);
    ptm.setRecordID(P.identification);

    pp.name                 = P.name;
    pp.email                = P.email;
    pp.profession           = P.profession;
    pp.birthday             = P.birthday;
    pp.age_group            = P.age_group;

    pms.risk_status         = P.risk_status;

    preg.priority           = P.priority;
    preg.treatment_type     = P.treatment_type;
    preg.withdrawal         = P.withdrawal;
    preg.letter             = P.letter;
    preg.regist             = P.regist;
    preg.treated            = P.treated;
    preg.wait               = P.wait;
    preg.deadline           = P.deadline;
    preg.withdraw_date      = P.withdraw_date;
    preg.waiting_time       = P.waiting_time;
    preg.regist_date        = P.regist_date;
    preg.regist_date        = P.regist_date;
    preg.regist_time        = P.regist_time;

    ptm.day                 = P.treat_date;
    ptm.location            = P.treatment_loc;
}


#endif