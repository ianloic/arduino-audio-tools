#pragma once
#include "AudioBasic/Collections/List.h"

namespace audio_tools {

/**
 * @brief LIFO Stack which is based on a List
 * @author Phil Schatzmann
 * @copyright GPLv3
 * @tparam T 
 */
template <class T> 
class Stack {
    public:
        Stack() = default;
        
        bool push(T& data){
            return l.push_back(data);
        }

        bool pop(T& data){
            return l.pop_back(data);
        }

        bool peek(T& data){
            if (l.end()->prior==nullptr) return false;
            data = *(l.end()->prior);
            return true;
        }

        size_t size() {
            return l.size();
        }

        bool clear() {
            return l.clear();
        }

        bool empty() {
            return l.empty();
        }
    protected:
        List<T> l;
};


}