//project 10 
//map set using dynamic arrays
//Node<K,V>* find_key(K key) returns a pointer to a Node<K,V> 
//size()  returns size of the MapSet (number of Nodes)
//get(K) : returns a Node<K,V> that is either a copy of the Node that has the string as a key or a pair with default values
//update(K, V) : if the key is in the MapSet, update the key-value pair to the value and Return true. return false if not
//remove(string) : if the key is in the MapSet, remove the associated Node and return true. If the key is not in the MapSet do nothing and return false
//add(string,long) : if the is in the MapSet, do nothing and return false. Otherwise create a Node with the argument values and insert the new pair into the array, in sorted order, and return true
//compare(MapSet&) compares the two MapSets
//mapset_union(MapSet&). Return a new MapSet that is a union of the two MapSets being called
//mapset_intersection(MapSet&). Return a new MapSet that is the intersection of the two MapSets being called.


#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
using std::endl;
using std::cout;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort;using std::lower_bound;using std::copy;using std::swap;
#include<sstream>
using std::ostringstream;


//
// Node
//
template < typename K, typename V > struct Node
{
  K first;
  V second;
  Node () = default;
  Node (K, V);
  bool operator< (const Node &) const;
  bool operator== (const Node &) const;
  friend ostream &operator<< (ostream & out, const Node & n){
    out << n.first << ":" << n.second << endl; //write to o stream
    return out;
  }
};

template < typename K, typename V > Node < K, V >::Node (K key, V value)
{
  first = key; //constructr key as first and value as second
  second = value;
}

template < typename K, typename V >
  bool Node < K, V >::operator< (const Node & n) const 
{
  return n.first > first; //return true or false
}

template < typename K, typename V >
  bool Node < K, V >::operator== (const Node & n) const 
{
  return first == n.first; //return true or false
}

//
// MapSet
// 
template < typename K, typename V > class MapSet
{
private:
  Node < K, V > *ary_;
  size_t last_;
  size_t capacity_;
  Node < K, V > *find_key (K);
  void grow ();
public:
  MapSet (int sz = 2);
  MapSet (initializer_list < Node < K, V > >);
  MapSet (const MapSet &);
  MapSet operator= (MapSet);
  ~MapSet ();
  size_t size ();
  bool remove (K);
  bool add (Node < K, V >);
  Node < K, V > get (K);
  bool update (K, V);
  int compare (MapSet &);
  MapSet mapset_union (MapSet &);
  MapSet mapset_intersection (MapSet &);

  friend ostream & operator<< (ostream & out, const MapSet & ms) {
    for (int i = 0; i < ms.last_; i++) { //write to ostream
      out << (i == 0 ? "" : ", ") << ms.ary_[i].first << ":" << ms.ary_[i].second;
    }
    return out;
  }
};

template < typename K, typename V > MapSet < K, V >::MapSet (int capacity) {
  capacity_ = capacity; //create new node of size capacity
  last_ = 0;
  ary_ = new Node < K, V >[capacity];
}

template < typename K, typename V >
MapSet < K, V >::MapSet (initializer_list < Node < K, V > >il) {
  // call constructor with size
  new (this) MapSet(il.size());
  
  typename initializer_list <Node <K,V >>::iterator it;
  for (it = il.begin (); it != il.end (); ++it) {
      Node<K, V> pair = *it;
      add(pair); //add pairs from initializer_list in sorted order
    }
}

template < typename K, typename V >
  MapSet < K, V >::MapSet (const MapSet & ms){
    // call constructor with size
    new (this) MapSet(ms.capacity_);

    for (auto i = 0; i < ms.last_; i++) {
      add(ms.ary_[i]); //add values in mapset to ary_
    }  
}

// copy and swap
template < typename K, typename V >
  MapSet < K, V > MapSet < K, V >::operator= (MapSet < K, V > ms){
    swap(this->capacity_, ms.capacity_);
    swap(this->last_, ms.last_);
    swap(this->ary_, ms.ary_);
    return *this;
}

template < typename K, typename V > MapSet < K, V >::~MapSet (){
    delete [] ary_;
}

template < typename K, typename V > size_t MapSet < K, V >::size (){
  return last_;
}

template < typename K, typename V > void
  MapSet <K,V >::grow (){

    size_t new_capacity = 1;
    if(capacity_ > 0) {
      new_capacity = capacity_ * 2;
    }

    Node < K, V > *new_ary = new Node < K, V >[new_capacity]; //create new ary_ of new bigger size 

    for(int i = 0; i < last_; i++) {
      new_ary[i].first = ary_[i].first;//add all values from ary_
      new_ary[i].second = ary_[i].second;
    }

    delete[] ary_; //delete old ary_

    ary_ = new_ary; //new ary_ becomes old ary_
  
}

template < typename K, typename V >
  Node < K, V > *MapSet < K, V >::find_key (K key){

  // TEMP find code
  for (int i = 0; i < last_; i++){
      if (ary_[i].first == key) //check if keys match
	       return &ary_[i];
    }
    
  return nullptr;
}

template < typename K, typ
