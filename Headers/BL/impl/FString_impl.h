//
//  FString_impl.h
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BnutLibrary_FString_impl_h
#define BnutLibrary_FString_impl_h

namespace BL
{
    inline FString::FString(void) : string()
    {
    }
    template <typename A>
    inline FString::FString(A a)
    : string(Apply(a))
    {
    }
    template <typename A, typename B>
    inline FString::FString(A a, B b)
    : string(Apply(a) + Apply(b))
    {
    }
    template <typename A, typename B, typename C>
    inline FString::FString(A a, B b, C c)
    : string(Apply(a) + Apply(b) + Apply(c))
    {
    }
    template <typename A, typename B, typename C, typename D>
    inline FString::FString(A a, B b, C c, D d)
    : string(Apply(a) + Apply(b) + Apply(c) + Apply(d))
    {
    }
    template <typename A, typename B, typename C, typename D, typename E>
    inline FString::FString(A a, B b, C c, D d, E e)
    : string(Apply(a) + Apply(b) + Apply(c) + Apply(d) + Apply(e))
    {
    }

//    template <typename T>
//    inline std::string FString::Apply(T that)
//    {
//        std::ostringstream str;
//        str << that;
//        return str.str();
//    }

    template <typename A>
    inline std::string fstring(A a) {return FString(a).string;}
    template <typename A, typename B>
    inline std::string fstring(A a, B b) {return FString(a,b).string;}
    template <typename A, typename B, typename C>
    inline std::string fstring(A a, B b, C c) {return FString(a,b,c).string;}
    template <typename A, typename B, typename C, typename D>
    inline std::string fstring(A a, B b, C c, D d) {return FString(a,b,c,d).string;}
    template <typename A, typename B, typename C, typename D, typename E>
    inline std::string fstring(A a, B b, C c, D d, E e) {return FString(a,b,c,d,e).string;}

    template<> std::string FString::Apply(std::string v);
    template<> std::string FString::Apply(const char* v);

    template<> std::string FString::Apply(char   v);
    template<> std::string FString::Apply(int    v);
    template<> std::string FString::Apply(float  v);
    template<> std::string FString::Apply(double v);
    template<> std::string FString::Apply(size_t v);
}

#endif
