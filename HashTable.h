#pragma once

#include "DictTree.h"
#include<string>
#include<iostream>
#include<unordered_map>
using namespace std;

template<class KeyType, class ItemType>
class HashTable
{
public:
    HashTable();
    HashTable(int numBuckets);

    void add(KeyType key, ItemType item);
    bool remove(KeyType key);
    ItemType getItem(KeyType key);
    bool contains(KeyType key);
    int size();

    void traverse(void visit(ItemType&));

private:
    const int DEFAULT_BUCKET_NUM = 20;        // How many buckets by default
    DictTree<KeyType, ItemType>** buckets;
    int numBuckets;
    int numElems;                            // How many elements stored in entire table
    int getHashIndex(const KeyType& key);
};

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable()
{
    buckets = new DictTree<KeyType, ItemType>*[DEFAULT_BUCKET_NUM];
    
    numBuckets = DEFAULT_BUCKET_NUM;
    numElems = 0;

    // for each bucket, set the i-th bucket equal to a new DictTree of type <KeyType, ItemType>
    for (int i=0; i<DEFAULT_BUCKET_NUM; i++) {
        buckets[i]=new DictTree<KeyType, ItemType>();
        }
}

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(int numBucks)
{
    // See previous constructor.  Use numBucks instead of DEFAULT_BUCKET_NUM.
    buckets = new DictTree<KeyType, ItemType>*[numBucks];
    numBuckets = numBucks;
    numElems = 0;
    for (int i=0; i<numBucks; i++) {
    buckets[i]= *new DictTree<KeyType, ItemType>();
    }
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::size()
{
    return numElems;
}

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::add(KeyType key, ItemType item)
{
    // VERY LITTLE CODE HERE
    // Get the hash bucket Index
    int b = getHashIndex(key);
    // If the hash table does not already contain key
    
        
        if(!buckets[b]->contains(key))
        {
            //    increase numElems by one
            
            numElems = numElems+ 1;
            // add key,item to the DictTree at a buckets index
            buckets[b]->add(key,item);
        }
       
    
    
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::remove(KeyType key)
{
    // VERY LITTLE CODE HERE
    // Get the hash Index
    int b = getHashIndex(key);

    // If the hash table contains the key
    if (buckets[b]->contains(key)) {
        //    decrease numElems by one
        numElems=numElems-1;
         //    remove the key from buckets[b]
        buckets[b]->remove(key);
         //    return true
        return true;
    }
    // else
        //    return false
    else
        return false;
    
}
   
    

template<class KeyType, class ItemType>
ItemType HashTable<KeyType, ItemType>::getItem(KeyType key)
{
    // Get the hash bucket Index
    int b = getHashIndex(key);
    //if (buckets[b]->contains(key)) {
    // return the item by using getItem on the correct bucket index.
        return buckets[b]->getItem(key);
    //}
    //else
    return nullptr; // (HINT:  Should only be 2 line of code at most.  1 is plenty.)
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::contains(KeyType key)
{
    // Get the hash bucket Index
    int b = getHashIndex(key);
    // Use contains on the correct bucket index to return the correct true false.
    // (HINT:  Should only be 2 lines of code at most.  1 is plenty.)
    if (buckets[b]->contains(key)) {
    
        return true;
    }
    
    //else
        return false;
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getHashIndex(const KeyType & key)
{
    // This is done... No touching!

    // We are creating a hash function type called hashFunction that hashes "KeyType."
    // First we create an an unordered_map object for our KeyType and ItemType
    unordered_map<KeyType, ItemType> mapper;

    // Then we call the hash_function method to return the hash function
    // for the KeyType and assign it to 'hashFunction'
    typename unordered_map<KeyType, ItemType>::hasher hashFunction = mapper.hash_function();

    // static_cast needed since hashFunction returns an unsigned long
    return static_cast<int>(hashFunction(key) % numBuckets);
}


template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::traverse(void visit(ItemType&))
{
    
    // You should use the traverse function of the DictTree
    for (int i=0; i<numBuckets; i++) {
    buckets[i]->traverse(visit);
    }
}
