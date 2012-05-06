//
//  CompactList.h
//  BnutLibrary
//
//  Created by Andrew Bennett on 5/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BnutLibrary_CompactList_h
#define BnutLibrary_CompactList_h

#include <BL/UnitTest.h>
#include <BL/impl/CompactList_impl.h>

namespace BL
{
    template <typename T>
    struct CompactList : private _CompactList_impl<T>
    {
        typedef typename _CompactList_impl<T>::_weak_reference  weak_reference;
        typedef typename _CompactList_impl<T>::_reference       reference;
        typedef typename _CompactList_impl<T>::_const_reference const_reference;
        typedef typename _CompactList_impl<T>::_object          object;

        inline weak_reference create(const object& object) {return this->_create(object);}

        inline void compact(void) {this->_compact();}

        inline void foreach(void (*call)(object&))             {this->_foreach_obj(call);}
        inline void foreach(void (*call)(object)) const        {this->_foreach_obj(call);}
        inline void foreach(void (*call)(const object&)) const {this->_foreach_obj(call);}

        inline void foreach(void (*call)(const reference& ref)) {this->_foreach_ref(call);}
        inline void foreach(void (*call)(const const_reference& ref)) const {this->_foreach_ref(call);}

        inline size_t size(void) const {return this->_size();}
        inline size_t capacity(void) const {return this->_capacity();}

        inline void report(void) const {return this->_report();}

        BLDefineUnitTest("Compact List");
    };
}

#endif
