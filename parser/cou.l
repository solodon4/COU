%{
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

// This fixes bug with compiling flex generated file under MS VC++
#ifdef _MSC_VER
#define YY_NO_UNISTD_H
// Fix for MSVC 2003 as fileno was deprecated
#if _MSC_VER > 1300
#define fileno _fileno
#endif

#include <io.h>
#define isatty _isatty
#endif

#include "coudefs.hpp"

int g_line = 1;
%}

id    [a-zA-Z_][a-zA-Z_0-9]*
str   \"[^\n"]+\"
chr   \'([^\\]|(\\[nrftvba\\]))\'
dec   [0-9]+
bol   (true)|(false)
ws    [ \t]
fl1   [-+]?[0-9]+\.?([eE][-+]?[0-9]+)?
fl2   [-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?
num   {fl1}|{fl2}

%option noyywrap nounput batch debug

%% //======================================================================// %%

{id}                yylval.m_str = new std::string(yytext); return ID;
{id}-class          yylval.m_str = new std::string(yytext); return ID;

(:{id}?)+                                  /* ignore parameters */;
;.*$                                       /* ignore comment */;
\n                  g_line++;              /* ignore end of line */;
[ \t]+                                     /* ignore whitespace  */;
.                   return (int)yytext[0]; /* pass other chars as tokens */

%% //======================================================================// %%
