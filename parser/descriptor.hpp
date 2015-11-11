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

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

//------------------------------------------------------------------------------

struct ClassDescriptor;
typedef std::set<const ClassDescriptor*>       class_set;
typedef std::map<std::string,ClassDescriptor*> class_map;
typedef std::vector<const ClassDescriptor*>    class_seq;
typedef std::set<class_seq>                    path_set;

//------------------------------------------------------------------------------

struct ClassDescriptor
{
    typedef class_seq                bases_type;
    typedef std::vector<std::string> attributes_type;
    typedef std::vector<std::string> methods_type;

    ClassDescriptor(const std::string& n) : name(n), is_defined(false)/*, derived_count(1)*/ {}

    bool operator<(const ClassDescriptor& cd) const 
    { 
        if (this == &cd)
            return false;
        else
            return is_derived_from(&cd) || (!cd.is_derived_from(this) && name < cd.name);
    }

    bool is_root() const { return bases.empty(); }
    bool is_leaf() const { return derived.empty(); }
    bool is_util() const { return is_root() && is_leaf(); }
    size_t depth() const;

    bool is_derived_from(const ClassDescriptor*) const;
    path_set derivation_paths_to(const ClassDescriptor*) const;
    void derivation_paths_to_recursive(const ClassDescriptor* c, class_seq& path, path_set& paths) const;

    void add_base(ClassDescriptor*);
    void add_attr(const std::string&);
    void add_mthd(const std::string&);
private:
    //void add_derived() const;
    void add_derived(const ClassDescriptor*);
public:
    void finalize() { is_defined = true; }
    void remove_inaccessible_bases();

    std::string     name;       ///< Name of the class described
    bases_type      bases;      ///< List of base classes in the order defined
    attributes_type attributes; ///< Data-members (names only)
    methods_type    methods;    ///< Member-functions (names only)
    bool            is_defined; ///< The entire definition in COU file has been seen
//    mutable size_t  derived_count; ///< Number of derived classes, including itself
    class_set       derived;    ///< Set of immediately derived classes
};

//------------------------------------------------------------------------------

extern class_map all_classes;

//------------------------------------------------------------------------------

std::ostream&    operator<<(std::ostream& os, const ClassDescriptor& cd);
std::string      fix_name(std::string);
ClassDescriptor* get_class(const std::string& name);
inline bool      cd_ptr_less(const ClassDescriptor* c1, const ClassDescriptor* c2) { return *c1 < *c2; }

//------------------------------------------------------------------------------
