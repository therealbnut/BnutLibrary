//
//  Vec2.h
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BnutLibrary_Vec2_h
#define BnutLibrary_Vec2_h

#include <BL/UnitTest.h>
#include <cmath>

namespace BL
{
    template <typename T>
    struct Vec2
    {
        typedef T type;

        inline Vec2(type _x, type _y) : x(_x), y(_y) {}
        inline Vec2(void) : x(0), y(0) {}

        inline bool operator == (const Vec2& that) const {return x==that.x && y==that.y;}
        inline bool operator != (const Vec2& that) const {return x!=that.x || y!=that.y;}

        inline Vec2& operator += (const Vec2& that)       {x+=that.x; y+=that.y; return *this;}
        inline Vec2& operator -= (const Vec2& that)       {x-=that.x; y-=that.y; return *this;}
        inline Vec2& operator *= (const Vec2& that)       {x*=that.x; y*=that.y; return *this;}
        inline Vec2& operator /= (const Vec2& that)       {x/=that.x; y/=that.y; return *this;}

        inline Vec2  operator +  (const Vec2& that) const {return Vec2(x+that.x, y+that.y);}
        inline Vec2  operator -  (const Vec2& that) const {return Vec2(x-that.x, y-that.y);}
        inline Vec2  operator *  (const Vec2& that) const {return Vec2(x*that.x, y*that.y);}
        inline Vec2  operator /  (const Vec2& that) const {return Vec2(x/that.x, y/that.y);}


        inline Vec2& operator += (type that)       {x+=that; y+=that; return *this;}
        inline Vec2& operator -= (type that)       {x-=that; y-=that; return *this;}
        inline Vec2& operator *= (type that)       {x*=that; y*=that; return *this;}
        inline Vec2& operator /= (type that)       {x/=that; y/=that; return *this;}

        inline Vec2  operator *  (type that) const {return Vec2(x*that, y*that);}
        inline Vec2  operator /  (type that) const {return Vec2(x/that, y/that);}

        friend inline Vec2 operator * (type value, const Vec2& that) {return Vec2(that.x*value, that.y*value);}

        inline type length2(void) const {return x*x + y*y;}
        inline type length(void) const {return sqrt(x*x + y*y);}

        inline Vec2 normalized(void) const {return (*this / this->length());}

        static inline type Distance2(const Vec2& a, const Vec2& b) {return (a-b).length2();}
        static inline type Distance(const Vec2& a, const Vec2& b) {return (a-b).length();}

        static inline type Dot(const Vec2& a, const Vec2& b) {return a.x*b.x + a.y*b.y;}
        static inline Vec2 FromAngle(type value) {return Vec2(cos(value), sin(value));}

        BLDefineUnitTest("Vec2");

        type x, y;
    };

    typedef Vec2<float> Vec2f;
}

#endif
