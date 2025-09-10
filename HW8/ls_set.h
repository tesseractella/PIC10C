//
//  ls_set.h
//  10C
//
//  Created by Tess Flinchbaugh on 5/27/24.
//

#ifndef ls_set_h
#define ls_set_h

template <typename T>
struct remove_pointers{
    using type = T;
};

template <typename T>
struct remove_pointers<T*>{
    using type = typename remove_pointers<T>::type;
    
};

template <typename T>
typename remove_pointers<T>::type dereference(T& t) {
    return t;
}

template <typename T>
typename remove_pointers<T>::type dereference(T* t) {
    return dereference(*t);
}

template <typename T>
class ls_set{
public:
    ls_set(){}

    void insert(T el){
        if (count(data.begin(), data.end(), el) ==0){
            data.push_back(el);
        }
    }

    void erase(T el){
        for (auto it = data.begin(); it != data.end(); it++){
            if (*it == el){
                data.erase(it);
            }
        }
    }

    bool find(T el){
        return count(data.begin(), data.end(), el);
    }

    size_t size(){
        return data.size();
    }

private:
    std::vector<T> data;
};


template <typename T>
class ls_set<T*>{
public:
    ls_set(){};
    
    void insert(T* el){
        if (!find(dereference(el))){
            data.push_back(el);
        }
    }
    
    void erase(typename remove_pointers<T>::type  el){
        for (auto it = data.begin(); it != data.end(); it++){
            if (dereference(*it) == el){
                data.erase(it);
            }
        }
    }
    
    bool find(typename remove_pointers<T>::type el){
        for (auto it = data.begin(); it != data.end(); it++){
            if (dereference(*it) == el){
                return true;
            }
        }
        return false;
    }
    
    size_t size(){
        return data.size();
    }


private:
    std::vector<T*> data;
};

#endif /* ls_set_h */
