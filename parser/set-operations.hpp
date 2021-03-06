//
//  Mach7: Pattern Matching Library for C++
//
//  Copyright 2011-2013, Texas A&M University.
//  Copyright 2014 Yuriy Solodkyy.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//
//      * Neither the names of Mach7 project nor the names of its contributors
//        may be used to endorse or promote products derived from this software
//        without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
//  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

///
/// \file
///
/// This file is a part of Mach7 library test suite.
///
/// \author Yuriy Solodkyy <yuriy.solodkyy@gmail.com>
///
/// \see https://bit.ly/Mach7
/// \see https://github.com/solodon4/Mach7
/// \see https://github.com/solodon4/SELL
/// \see https://parasol.tamu.edu/mach7/
///

#include <algorithm>
#include <iterator>
#include <set>

#pragma once

//------------------------------------------------------------------------------

template<class K, class P, class A>
std::set<K,P,A>	operator&(const std::set<K,P,A>& a, const std::set<K,P,A>& b)
{
    std::set<K,P,A> r;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(r,r.begin()));
    return r;
}

//------------------------------------------------------------------------------

template<class K, class P, class A>
std::set<K,P,A>	operator|(const std::set<K,P,A>& a, const std::set<K,P,A>& b)
{
    std::set<K,P,A> r;
    std::set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(r,r.begin()));
    return r;
}

//------------------------------------------------------------------------------

template<class K, class P, class A>
std::set<K,P,A>	operator^(const std::set<K,P,A>& a, const std::set<K,P,A>& b)
{
    std::set<K,P,A> r;
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(r,r.begin()));
    return r;
}

//------------------------------------------------------------------------------
