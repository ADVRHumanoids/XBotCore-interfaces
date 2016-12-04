/*
 * Copyright (C) 2016 IIT-ADVR
 * Author: Arturo Laurenzi, Luca Muratore
 * email:  arturo.laurenzi@iit.it, luca.muratore@iit.it
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#ifndef __XBOTCORE_SHARED_OBJECT_H__
#define __XBOTCORE_SHARED_OBJECT_H__

#include <boost/any.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>

namespace XBot {
 
template<typename T>
class SharedObject {
    
public:
    
    
    
    SharedObject();
    
    SharedObject(T* dynamically_allocated_object);
    
    void reset(T* dynamically_allocated_object);
    
    T& operator*();
    const T& operator*() const;
    
    T* operator->();
    const T* operator->() const;
    
    std::shared_ptr<T> get();
    std::shared_ptr<const T> get() const;
    
    bool setValid();
    
    bool isValid() const;
    bool isNull() const;
    
protected:
    
private:
    
    std::shared_ptr<std::shared_ptr<T>> _ptrptr;
    bool _is_valid;
    
};

    
template<typename T>
SharedObject<T>::SharedObject():
    _is_valid(false)
{
    _ptrptr = std::make_shared<std::shared_ptr<T>>();
}

template<typename T>
SharedObject<T>::SharedObject(T* dynamically_allocated_object):
    _is_valid(false)
{
    _ptrptr = std::make_shared<std::shared_ptr<T>>();
    *_ptrptr = std::shared_ptr<T>(dynamically_allocated_object);
}

template<typename T>
void SharedObject<T>::reset(T* dynamically_allocated_object)
{
    *_ptrptr = std::shared_ptr<T>(dynamically_allocated_object);
}

template<typename T>
std::shared_ptr<const T> SharedObject<T>::get() const
{
    return *_ptrptr;
}

template<typename T>
std::shared_ptr<T> SharedObject<T>::get()
{
    return *_ptrptr;
}

template<typename T>
const T& SharedObject<T>::operator*() const
{
    return **_ptrptr;
}

template<typename T>
T& SharedObject<T>::operator*()
{
    return **_ptrptr;
}

template<typename T>
const T* SharedObject<T>::operator->() const
{
    return _ptrptr->get();
}

template<typename T>
T* SharedObject<T>::operator->()
{
    return _ptrptr->get();
}

template<typename T>
bool SharedObject<T>::isNull() const
{
    return !*_ptrptr;
}

template<typename T>
bool SharedObject<T>::isValid() const
{
    return !isNull() && _is_valid;
}

template<typename T>
bool SharedObject<T>::setValid()
{
    if(*_ptrptr){
        _is_valid = true;
    }
    else{
        std::cerr << "ERROR in " << __func__ << "! Current shared object is null!" << std::endl;
        return false;
    }
}


}

#endif