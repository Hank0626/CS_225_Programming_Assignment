#ifndef DATABASE_CPP
#define DATABASE_CPP
#include "../include/database.h"
#include <vector>
#include <typeinfo>
#include <math.h>

// Insert a record into the relation. Return true if succeed.
// If fail, return false
template<class T> bool Relation<T>::insert(T record, RELATION type,int key) {
    Block<T>* go = new Block<T>;
    go = this->_dummy;
    while( go->getNextBlock() != this->_dummy){
        go = go->getNextBlock();
        if(go->BLOCK_ID[type] == key){
            if(go->_append(record) == 0){
               cout << "this person already in the database" << endl;
               return 0;
            }else{
                return 1;
            }
        }
    }
    Block<T>* next = new Block<T>;
    next->BLOCK_ID[type] = key;
    go->setNextBlock(next);
    next->setPrevBlock(go);
    next->setNextBlock(this->_dummy);
    this->_dummy->setPrevBlock(next);
    if(next->_append(record) == 0){
        cout << "this person already in the database" << endl;
        return 0;
    }

    return 1;
}

//help function:

template<class T> bool Block<T>::_append(T DATA){
    for(int i = 0; i < this->overflowBuffer.size()+this->array.size(); i++){
            if(DATA.getRecordID() == this->operator[](i).getRecordID()){
                cout << "this person is already in the block" << endl;
                return 0;
            }
    }
    this->overflowBuffer.push_back(DATA);
    if(this->overflowBuffer.size() == 8){
        this->combine();
    }
    return 1;
}

  
template<class T> void Block<T>::combine(void){
    for(int i = 0; i < 8; i++){
        this->array.push_back(this->overflowBuffer[i]);
    }
    this->overflowBuffer.clear();
}


// Remove one record from the relation. Return true if succeed.
// If record not found, return false
template<class T> bool Relation<T>::remove(information* record,RELATION type) {
    int key = 0;
    switch (type)
    {
    case RELATION_PERSON:
        key = record->P.age_group;
        break;
    case RELATION_MEDICALSTATUS:
        key = record->M.risk_status;
        break;
    case RELATION_REGISTRATION:
        key = record->R.regist_date;
        break;
    case RELATION_TREATMENT:
        key = record->T.day;
        break;
    default:
        cout << "no such type" << endl;
        break;
    }

    Block<T>* go = this->_dummy;
    while(go->getNextBlock() != this->_dummy){
        go = go->getNextBlock();
        if(go->BLOCK_ID[type] == key){
            for(int i = 0; i < go->overflowBuffer.size() ; i++){
                if(go->overflowBuffer[i].getRecordID() == record->getRecordID()){
                    go->overflowBuffer.erase(go->overflowBuffer.begin()+i);
                    return 1;
                }
            }
            for(int i = 0; i < go->array.size(); i++){
                if(go->array[i].getRecordID() == record->getRecordID()){
                    go->array.erase(go->overflowBuffer.begin()+i);
                    return 1;
                }
            }
        }
    }
    return 0;


}

// Retrieve the record indicated by recordID.
// Return a record with an recordID of null pointer to indicate record not found.
template<class T> Block<T>* Relation<T>::retrieve(int key,RELATION type) {
    Block<T>* go = new Block<T>;
    go = this->_dummy;
    while(go->getNextBlock() != this->_dummy){
        go = go->getNextBlock();
        if(go->BLOCK_ID[type] == key){
            return go;
        }
    }
    cout << "not such block" << endl;
    return NULL;

}

// Merge two blocks indicated by blockID_1 and blockID_2.
// If they are next to each other and their lengths meet the requirement,
// merge them, adjust block id and return true. Otherwize, do nothing and return false.
// The merge will be in-place.
template<class T> bool Relation<T>::merge(int blockID_1, int blockID_2, RELATION type) {

    if((blockID_1 - blockID_2 >= 2) && (blockID_2 - blockID_1 >= 2)){
        cout << "these two blocks are not near" << endl;
        return 0; 
    }

    if(blockID_1 < blockID_2){
        this->sort(type);
    }
    return 1;

}

// Sort the blocks in increasing order based on their block id.
// The sort will be in-place.
template<class T> void Relation<T>::sort(RELATION type) {
    Block<T>* go = new Block<T>;
    Block<T>* now = new Block<T>;
    Block<T>* candi = new Block<T>;
    now = this->_dummy;
    int minimum_key = 999;
    while(now->getNextBlock() != this->_dummy){
        go = now->getNextBlock();
        while(go->getNextBlock() != this->_dummy){
            go = go->getNextBlock();
            if(minimum_key >= go->BLOCK_ID[type]){
                minimum_key = go->BLOCK_ID[type];
                candi = go;
            }
        }
        now = now->getNextBlock();
        this->swap(now,candi);
        now = candi;
    }
    return;
}

// swap two blocks in double linked list
template<class T> void Relation<T>::swap(Block<T>* A, Block<T>* B){
    Block<T>* next = new Block<T>;
    Block<T>* pred = new Block<T>;
    next = A->getNextBlock();
    pred = A->getPrevBlock();
    A->setNextBlock(B->getNextBlock());
    A->setPrevBlock(B->getPrevBlock());
    B->setNextBlock(next); 
    B->setPrevBlock(pred);
    return;
} 

// Split the block indicated by blockID. This function acts exactly the same 
// as the split function in Python. For example, if splitPosition is
// N, this block will be splited into block[:N] and block[N:].
// Minus splitPosition is also supported. The split will be in-place.
template<class T> bool Relation<T>::split(int blockID, int splitPosition,RELATION type) {
    Block<T>* go = new Block<T>;
    Block<T>* new_block = new Block<T>;
    go = this->_dummy;
    int k = 0;
    while(go->getNextBlock() != this->_dummy){
        go = go->getNextBlock();
        if(go->BLOCK_ID[type] == blockID){
            new_block->BLOCK_ID[type] = blockID;
            for(int i = go->array.size() - 1; i >= splitPosition; i--){
                new_block->array.insert(new_block->array.begin(),go->array[i]);
                go->array.pop_back();
            }
        return 1;    
        }
    }
    cout << "no such block" << endl;
    return 0;

}



template<class T> void Relation<T>::print(void){
    Block<T>* go = new Block<T>;
    go = this->_dummy;
    cout << this->getLength();
    while (go->getNextBlock() != this->_dummy){
        go = go->getNextBlock();
        cout << go->overflowBuffer.size() << endl;
        cout << go->array.size() << endl;
    }
}


//this part is used for ex4:
template<class T> int Neighbor<T>::distance(Person A, Person B){
    int dis = 0;
    dis = (A.address.first - B.address.first)*(A.address.first - B.address.first) + (A.address.second - B.address.second)*(A.address.second - B.address.second);
    dis = int (pow(dis,0.5));
    return dis;
}

template<class T> Graph* Neighbor<T>::neighbors(int num,Person A,Relation<Person> distan){
    int bound = num*this->threshold;
    Block<Person>* surround = new Block<Person>;
    this->find_map->distance = bound;
    surround = distan._dummy;
    this->find_map->vertices.push_back(A.getRecordID());
    while(surround->getNextBlock() != distan._dummy){
        surround = surround->getNextBlock();
        for(int i = 0; i < surround->overflowBuffer.size();i++){
            if(this->distance(A,surround->overflowBuffer[i]) < bound){
                this->find_map->vertices.push_back(surround->overflowBuffer[i].getRecordID());
                this->find_map->edges.push_back(this->distance(A,surround->overflowBuffer[i]));
                this->find_map->numbers++;
            }
        }
        for(int i = 0; i < surround->array.size(); i++){
            if(this->distance(A,surround->array[i]) < bound){
                this->find_map->vertices.push_back(surround->array[i].getRecordID());
                this->find_map->edges.push_back(this->distance(A,surround->array[i]));
                this->find_map->numbers++;
            }
        }
    }
    cout << this->find_map->numbers;
    cout << "  neighbors has been found" << endl;
    return this->find_map;
}



#endif