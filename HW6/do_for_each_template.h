#ifndef do_for_each_template_h
#define do_for_each_template_h
template<typename F, typename T>
void do_for_each(F function, T& t){
    function(t);
}


template <typename F, typename T, typename... Args>
void do_for_each(F function, T& t, Args&... args){
    function(t);
    do_for_each(function, args...);
}


template <typename T>
void print(T t){
    std::cout << t << " ";
}

template <typename T, typename... Args>
void print(T t, Args... args){
    std::cout << t << " ";
    print(args...);
}


#endif /* do_for_each_template_h */

