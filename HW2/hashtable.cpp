#include "hashtable.h"

size_t hash_code(const std::string& str)
{
   size_t h = 0;
   for (int i = 0; i < str.length(); i++)
   {
       h = 31 * h + str[i];
   }
   return h;
}

HashTable::HashTable(size_t nbuckets)
{
   for (size_t i = 0; i < nbuckets; i++)
   {
       buckets.push_back(nullptr);
   }
   current_size = 0;
   load_factor = current_size/buckets.size();

   if (load_factor > .75) {
       std::cout<<"big"<<std::endl;
       nbuckets *=2;
       reHash(nbuckets);
   }

   if (load_factor < .25 && current_size!=0) {
       std::cout<<"small"<<std::endl;
       nbuckets = nbuckets*0.5;
       reHash(nbuckets);
   }
}

void HashTable::reHash(size_t nbuckets){
   std::vector<Node*> newBuckets(nbuckets, nullptr);

   for (auto a = this->begin(); !a.equals(this->end()); a.next()){
       
       size_t h = hash_code(a.get()) % newBuckets.size();
       if (h < 0) { h = -h;}
       Node* newNode = new Node;
       newNode->data = a.get();
       newNode->next = nullptr;
       
       if (count(newNode->data)){ return;}

       Node* current = newBuckets[h];
       
       if (current == nullptr){
           current = newNode;
       }
       else {
           while (current->next != nullptr){
               current = current->next;
           }
           current->next = newNode;
       }
   }

   buckets = newBuckets;


}

size_t HashTable::count(const std::string& x)
{
   size_t h = hash_code(x) % buckets.size();
   if (h < 0) { h = -h; }

   Node* current = buckets[h];
   while (current != nullptr)
   {
       if (current->data == x) { return 1; }
       current = current->next;
   }
   return 0;
}
void HashTable::insert(const std::string& x){
	size_t h = hash_code(x) % buckets.size();
	if (h < 0) { h = -h;}
   
   if (count(x) >0 ){return;}
   
	Node* newNode = new Node;
	newNode->data = x;
	newNode->next = nullptr;
   
   if(buckets[h] == nullptr){
       buckets[h]  = newNode;
   }
   else{
	Node* current = buckets[h];
	while (current->next != nullptr){
		current = current->next;
	}
	current->next = newNode;
   }
   current_size++;
}

bool operator!=(const Iterator& left, const Iterator& right){
   return (right.container != left.container)||(right.current != left.current);
}

void HashTable::erase(const std::string& x){
   if (count(x) == 0){
       return;
   }
   else {
       size_t h = hash_code(x);
       Node* current_bucket = buckets[h];
       if (current_bucket->data == x){
           delete current_bucket;
           return;
       }
       Node* prev = nullptr;
           while (current_bucket != nullptr && current_bucket->data != x){
           //for (Node* i = current_bucket; i != nullptr; i=i->next){
           //if (i->data == x){
           prev = current_bucket;
           current_bucket = current_bucket->next;
           }
       prev->next = current_bucket->next;
       delete current_bucket;
       current_size--;
   }
}



size_t HashTable::size() const
{
   return current_size;
}
size_t HashTable::buckets_size() const
{
   return buckets.size();
}
Iterator HashTable::begin() const
{
   Iterator iter;
   iter.current = nullptr;
   iter.bucket_index = -1;
   iter.container = this;
   iter.next();
   return iter;
}

Iterator HashTable::end() const
{
   Iterator iter;
   iter.current = nullptr;
   iter.bucket_index = buckets.size();
   iter.container = this;
   return iter;
}

std::string Iterator::get() const
{
   return current->data;
}

bool Iterator::equals(const Iterator& other) const
{
   return current == other.current;
}

void Iterator::next(){
   if (current != nullptr && current->next != nullptr) {
           current = current->next;  // Move to the next element in the current bucket
       } else {
           bucket_index++;  // Move to the next bucket
           while (bucket_index < container->buckets_size() && container->buckets[bucket_index] == nullptr) {
               // Skip empty buckets
               bucket_index++;
           }
           if (bucket_index < container->buckets_size()) {
               current = container->buckets[bucket_index];  // Move to the first element of the next non-empty bucket
           } else {
               current = nullptr;  // No more elements to iterate over
           }
       }

}
