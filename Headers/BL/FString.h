//
//  FString.h
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BnutLibrary_FString_h
#define BnutLibrary_FString_h

#include <BL/UnitTest.h>
#include <string>

namespace BL
{ 
    struct FString
    {
        FString(void);
        template <typename A>
        FString(A a);
        template <typename A, typename B>
        FString(A a, B b);
        template <typename A, typename B, typename C>
        FString(A a, B b, C c);
        template <typename A, typename B, typename C, typename D>
        FString(A a, B b, C c, D d);
        template <typename A, typename B, typename C, typename D, typename E>
        FString(A a, B b, C c, D d, E e);

        const std::string string;

        BLDefineUnitTest("Formatted String");

    protected:
        template <typename T>
        static std::string Apply(T that);
    };
    
    template <typename A>
    std::string fstring(A a);
    template <typename A, typename B>
    std::string fstring(A a, B b);
    template <typename A, typename B, typename C>
    std::string fstring(A a, B b, C c);
    template <typename A, typename B, typename C, typename D>
    std::string fstring(A a, B b, C c, D d);
    template <typename A, typename B, typename C, typename D, typename E>
    std::string fstring(A a, B b, C c, D d, E e);
}

#include <BL/impl/FString_impl.h>

#endif
