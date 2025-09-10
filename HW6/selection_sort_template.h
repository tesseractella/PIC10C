#ifndef SELECTION_SORT_TEMPLATE_H
#define SELECTION_SORT_TEMPLATE_H

template <typename Iterator> void my_swap(Iterator& i, Iterator& j);


template <typename Iterator, typename Compare = std::less<>>
void selection_sort(Iterator first, Iterator last, Compare comp = Compare()){
    for (auto i = first; i != last; i++){
        auto min = i;
        for( auto j = i + 1; j != last; j++ ){
            if (comp(*j, *min)){
                min = j;
            }
        }
        my_swap(min, i);
    }
}

template <typename Iterator>
void my_swap(Iterator& i, Iterator& j){
    auto temp = *j;
    *j = *i;
    *i = temp;
}

#endif
