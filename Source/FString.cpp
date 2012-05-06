//
//  FString.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <BL/FString.h>
#include <sstream>

template<> std::string BL::FString::Apply(std::string v)
{
    std::ostringstream s; s<<v; return s.str();
}
template<> std::string BL::FString::Apply(const char* v)
{
    std::ostringstream s; s<<v; return s.str();
}

template<> std::string BL::FString::Apply(char   v)
{
    std::ostringstream s; s<<v; return s.str();
}
template<> std::string BL::FString::Apply(int    v)
{
    std::ostringstream s; s<<v; return s.str();
}
template<> std::string BL::FString::Apply(float  v)
{
    std::ostringstream s; s<<v; return s.str();
}
template<> std::string BL::FString::Apply(double v)
{
    std::ostringstream s; s<<v; return s.str();
}
template<> std::string BL::FString::Apply(size_t v)
{
    std::ostringstream s; s<<v; return s.str();
}
