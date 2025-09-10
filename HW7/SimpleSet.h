//
//  SimpleSet.h
//  10C
//
//  Created by Tess Flinchbaugh on 5/22/24.
//

#ifndef SimpleSet_h
#define SimpleSet_h

#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <string>

template<typename T>
class simple_set{
public:
    simple_set(){
    }
    
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


template<typename T>
class simple_set<T*>{
public:
    simple_set(){};
    void insert(T* el){
        if (!find(*el)){
            data.push_back(el);
        }
    }
    void erase(T el){
        for (auto it = data.begin(); it != data.end(); it++){
            if (**it == el){
                data.erase(it);
            }
        }
    }
    bool find(T el){
        for (auto it = data.begin(); it != data.end(); it++){
            if (*(*it) == el){
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

template<>
class simple_set<bool>{
public:
    simple_set(){
        has_true = false;
        has_false = false;
        data = {};
    }
    void print(){
        for (auto it = data.begin(); it != data.end(); it++){
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }
    void insert(bool el){
        if (el){
            if(!has_true){
                data.push_back(el);
                has_true = true;
            }
        }
        if (!el){
            if(!has_false){
                data.push_back(el);
                has_false = true;
            }
        }
        //std::cout << "has_true: " << has_true << "; has_false: " << has_false << "\n";
    }
    void erase(bool el){
        if (el){
            has_true = false;
        }
        if (!el){
            has_false = false;
        }
        for (auto it = 0; it < data.size(); it++){
            auto pos = data.begin() + it;
            if (*pos == el){
                data.erase(pos);
            }
        }
       // std::cout << "has_true: " << has_true << "; has_false: " << has_false << "\n";
    }
    
    bool find(bool el){
        if (el){
            return has_true;
        }
        else{
            return has_false;
        }
    }
    
    size_t size(){
        return int(has_true) + int(has_false);
    }
    
    
private:
    bool has_true;
    bool has_false;
    
    std::vector<bool> data;
    
};


#endif /* SimpleSet_h */
