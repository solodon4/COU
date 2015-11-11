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

/*
	Grammar for COU hierarchy class
*/

%{
#include "descriptor.hpp"
#include "coudefs.hpp"

using namespace std;

int  yyparse(void);
int  yylex(void);
void yyerror(const char *str)
{
    extern int g_line;
    extern char* yytext;
    cerr << "error[" << g_line << "]: " << str << endl;
    cerr << "before symbol: " << yytext << endl;
}

ClassDescriptor* cur = 0;
%}

%union
{
    std::string* m_str;
    int          m_int;
}

%start cou

%token <m_str> ID "identifier"

%printer    { debug_stream() << *$$; } ID
%destructor { delete $$; } ID

%%

cou	: '(' classes ')'
	;

classes	
    : classes class
	| class
	;

class : '(' ID { cur = get_class(*$2); } '(' bases ')' '(' attributes ')' '(' methods ')' ')' { cur->finalize(); }
    ;

bases : bases ID           { cur->add_base(get_class(*$2)); }
    | /* empty */
    ;

attributes : attributes ID { cur->add_attr(*$2); }
    | /* empty */
    ;

methods 
    : methods ID           { cur->add_mthd(*$2); }
    | methods operator
    | /* empty */
    ;

operator
    : '+'
    | '-'
    | '*'
    | '/'
    | '%'
    | '^'
    | '@'
    | '$'
    | '~'
    | '!'
    | '|'
    | '&'
    | '&''&'
    | '|''|'
    | '='
    | '<'
    | '>'
    | '<''='
    | '>''='
    | '=''='
    | '!''='
    | '\\''\\'
    ;

%%
