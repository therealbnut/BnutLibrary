//
//  CompactList_impl.h
//  BnutLibrary
//
//  Created by Andrew Bennett on 5/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BnutLibrary_CompactList_impl_h
#define BnutLibrary_CompactList_impl_h

#include <iostream>

#include <cassert>
#include <vector>
#include <deque>

namespace BL
{
    template <typename T>
    class _CompactList_impl
    {
    public:
        class _weak_reference
        {
        public:
            inline _weak_reference(void) : m_list(NULL), m_index(-1)
            {
            }
            inline _weak_reference(const _weak_reference& that)
            : m_list(that.m_list), m_index(that.m_index)
            {
            }

            inline size_t index(void) const {return this->m_index;}

        protected:
            friend class _CompactList_impl;
            
            inline _weak_reference(_CompactList_impl& list, size_t index)
                : m_list(&list), m_index(index)
            {
            }
            
            void _invalidate(bool want_release)
            {
                if (want_release && this->_valid())
                {
                    this->m_list->_release(*this);
                }
                this->m_list  = NULL;
                this->m_index = (size_t)-1;
            }
            inline void _assign(const _weak_reference& that, bool want_retain)
            {
                this->m_list  = that.m_list;
                this->m_index = that.m_index;
                if (want_retain && this->_valid())
                {
                    this->m_list->_retain(*this);
                }
            }
            inline bool _valid(void) const
            {
                return (this->m_list!=NULL && this->m_index != (size_t)-1);
            }
            
        private:
            _CompactList_impl * m_list;
            size_t m_index;
        };

        template <typename L, typename O>
        class _reference_base : public _weak_reference
        {
            friend class _CompactList_impl<O>;
        public:
            inline _reference_base(void) : _weak_reference()
            {
            }
            inline _reference_base(const _weak_reference& that)
            {
                this->_assign(that, true);
            }
            inline ~_reference_base(void)
            {
                this->_invalidate(true);
            }
            inline _reference_base& operator = (const _reference_base& that)
            {
                this->_invalidate(true);
                this->_assign(that, true);
                return *this;
            }
            
            typedef L List;
            typedef O Object;
            
            inline Object& operator * (void) const  {return *this->m_list->_at(*this);}
            inline Object* operator -> (void) const {return this->m_list->_at(*this);}
        };

    protected:
        typedef _reference_base<_CompactList_impl,T>              _reference;
        typedef _reference_base<const _CompactList_impl, const T> _const_reference;
        typedef T _object;

        friend class _weak_reference;
        friend class _reference_base<_CompactList_impl*,_object>;
        friend class _reference_base<const _CompactList_impl*,const _object>;

        inline size_t _capacity(void) const
        {
            return this->m_objects.size();
        }

        inline size_t _size(void) const
        {
            return this->m_objects.size() - this->m_unusedObj.size();
        }
        
        _weak_reference _create(const _object& object) const
        {
            size_t object_index, reference_index;
            if (this->m_unusedObj.empty())
            {
                object_index = this->m_objects.size();
                this->m_objects.push_back(object);
            }
            else
            {
                object_index = this->m_unusedObj.back();
                this->m_unusedObj.pop_back();
                this->m_objects[object_index] = object;
            }
            if (this->m_unusedRef.empty())
            {
                reference_index = this->m_references.size();
                this->m_references.push_back(object_index);
                this->m_referenceCounts.push_back(0);
            }
            else
            {
                reference_index = this->m_unusedRef.back();
                this->m_unusedRef.pop_back();
                this->m_references[reference_index] = object_index;
            }
            return _weak_reference(*const_cast<_CompactList_impl*>(this), reference_index);
        }

        void _compact(void) const
        {
            const size_t  z = this->_size();
            const size_t oz = this->m_objects.size();
            assert(z <= this->m_objects.size());
            
            std::deque<size_t>::iterator u,
            ub = this->m_unusedObj.begin(),
            ue = this->m_unusedObj.end();
            std::vector<size_t>::iterator r,
            rb = this->m_references.begin(),
            re = this->m_references.end();
            
            for (u=ub, r=rb; u!=ue; ++u)
            {
                if (*u >= z)
                    continue;
                while (r != re && !(*r >= z && *r < oz)) ++r;
                assert(r != re);
                this->m_objects[*u] = this->m_objects[*r];
                std::swap(*r, *u);
                ++r;
            }
        }
        
        template <typename _Function>
        void _foreach_obj(_Function func) const
        {
            const size_t  z = this->_size();
            this->_compact();
            for (typename std::vector<_object>::const_iterator
                 i = this->m_objects.begin(),
                 e = i + z; i != e; ++i)
            {
                func(*i);
            }
        }

        template <typename _Function>
        void _foreach_ref(_Function func) const
        {
            this->_compact();
            for (size_t i = 0; i<this->m_references.size(); ++i)
            {
                if (this->m_references[i] != (size_t)-1)
                {
                    func(_weak_reference(*const_cast<_CompactList_impl*>(this), i));
                }
            }
        }

        void _destroy(const _weak_reference& that)
        {
            size_t object_index;
            assert(that.m_list == this);
            assert(that.m_index < this->m_references.size());

            object_index = this->m_references[that.m_index];
            assert(object_index < this->m_objects.size());
            this->m_references[that.m_index] = (size_t)-1;
            this->m_unusedRef.push_back(that.m_index);
            this->m_unusedObj.push_back(object_index);
        }
        void _retain(const _weak_reference& that) const
        {
            assert(that.m_list == this);
            assert(that.m_index < this->m_references.size());
            assert(this->m_references[that.m_index] != (size_t)-1);
            ++this->m_referenceCounts[that.m_index];
        }
        void _release(const _weak_reference& that) const
        {
            assert(that.m_list == this);
            assert(that.m_index < this->m_referenceCounts.size());
            assert(this->m_referenceCounts[that.m_index] > 0);
            --this->m_referenceCounts[that.m_index];
            if (this->m_referenceCounts[that.m_index] == 0)
            {
                const_cast<_CompactList_impl*>(this)->_destroy(that);
            }
        }
        _object * _at(const _weak_reference& that) const
        {
            assert(that.m_list == this);
            assert(that.m_index < this->m_references.size());
            
            size_t object_index = this->m_references[that.m_index];
            assert(object_index < this->m_objects.size());
            
            return const_cast<_object*>(&this->m_objects[object_index]);
        }

        void _report(void) const
        {
            std::cout << "rc: ";
            for (std::vector<size_t>::const_iterator
                 i = this->m_referenceCounts.begin(),
                 e = this->m_referenceCounts.end();
                 i != e; ++i)
            {
                std::cout << *i << ", ";
            }
            std::cout << std::endl;

            std::cout << "r:  ";
            for (std::vector<size_t>::const_iterator
                 i = this->m_references.begin(),
                 e = this->m_references.end();
                 i != e; ++i)
            {
                std::cout << *i << ", ";
            }
            std::cout << std::endl;

            std::cout << "uo: ";
            for (std::deque<size_t>::const_iterator
                 i = this->m_unusedObj.begin(),
                 e = this->m_unusedObj.end();
                 i != e; ++i)
            {
                std::cout << *i << ", ";
            }
            std::cout << std::endl;

            std::cout << "ur: ";
            for (std::deque<size_t>::const_iterator
                 i = this->m_unusedRef.begin(),
                 e = this->m_unusedRef.end();
                 i != e; ++i)
            {
                std::cout << *i << ", ";
            }
            std::cout << std::endl;

            std::cout << "o:  ";
            for (typename std::vector<_object>::const_iterator
                 i = this->m_objects.begin(),
                 e = this->m_objects.end();
                 i != e; ++i)
            {
                std::cout << *i << ", ";
            }
            std::cout << std::endl;
        }

    private:
        mutable std::vector<size_t> m_referenceCounts;
        mutable std::vector<size_t> m_references;
        
        mutable std::deque<size_t>  m_unusedObj;
        mutable std::deque<size_t>  m_unusedRef;
        
        mutable std::vector<_object> m_objects;
    };
}

#endif
