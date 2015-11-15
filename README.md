Class Hierarchies Benchmark
===========================

This project contains a large, real-world class hierarchy benchmark with 15246
classes and 63963 different derivation paths. [The benchmark](cou) was previously
used in the literature to study efficiency of type inclusion testing and dispatching 
techniques [1,2,3,4] and was maintained by Karel Driesen (see his original 
[readme](cou/README)).
 
While working on [Mach7](http://bit.ly/Mach7) [5,6] we've tried to find this benchmark 
for our own experiments, but the original links were broken. Eventually we could 
dig up a version of it from 
[archive.org](http://web.archive.org/web/20050403120458/http://www.cs.ucsb.edu/labs/oocsb/),
We revive it here for researchers to use, along with the translator to C++, we 
wrote for our own experiments.

COU to C++ Translator
---------------------

While all the hierarchies were man-made, not all class hierarchies originated 
from C++, and sometimes used certain kinds of inheritance, not allowed in C++.
This is why during conversion to C++, [COU parser](parser) prunes inaccessible base classes 
(direct base class that is already an indirect base class) when used with repeated 
inheritance in order to satisfy semantic requirements of C++. It maintains 
the same number of virtual functions present in each class as well as the number 
of data members; the benchmarks, however, did not preserve the exact types of those.

Stats on Class Hierarchies in the Benchmark
-------------------------------------------

The following table shows various parameters of the class hierarchies in each benchmark, after their adoption to C++: 

Library | Language    | Classes| Paths| Height| Roots| Leafs| Both| Parents (avg) | Parents (max) | Children (avg) | Children (max) |                   
--------|-------------|--------|------|-------|------|------|-----|------|----|-----|-----|-------------------
    DG2 | Smalltalk   |     534|   534|     11|     2|   381|    1| 1    |   1| 3.48|   59| digitalk2         
    DG3 | Smalltalk   |    1356|  1356|     13|     2|   923|    1| 1    |   1| 3.13|  142| digitalk3         
    ET+ | C++         |     370|   370|      8|    87|   289|   79| 1    |   1| 3.49|   51| et++              
    GEO | Eiffel      |    1318| 13798|     14|     1|   732|    0| 1.89 |  16| 4.75|  323| geode             
    JAV | Java        |     604|   792|     10|     1|   445|    0| 1.08 |   3| 4.64|  210| java              
    LOV | Eiffel      |     436|  1846|     10|     1|   218|    0| 1.72 |  10| 3.55|   78| lov-object-editor 
    NXT | Objective-C |     310|   310|      7|     2|   246|    1| 1    |   1| 4.81|  142| nextstep          
    SLF | Self        |    1801| 36420|     17|    51|  1134|    0| 1.05 |   9| 2.76|  232| self              
    UNI | C++         |     613|   633|      9|   147|   481|  117| 1.02 |   2| 3.61|   39| unidraw           
        |             |      51|    51|      7|     1|    29|    0| 1.00 |   1| 2.27|    5| v1-collection     
        |             |      18|    18|      5|     1|    11|    0| 1.00 |   1| 2.43|    5| v1-magnitude      
        |             |     383|   383|      9|     1|   244|    0| 1.00 |   1| 2.75|   86| v1-object-nometa  
        |             |       9|     9|      5|     1|     4|    0| 1.00 |   1| 1.60|    2| v1-set            
        |             |      16|    16|      7|     1|     7|    0| 1.00 |   1| 1.67|    2| v1-stream         
        |             |      53|    53|      8|     1|    31|    0| 1.00 |   1| 2.36|    7| v1-visualcomponent
    VA2a| Smalltalk   |    3241|  3241|     14|     1|  2582|    0| 1    |   1| 4.92|  249| visualage2.all    
    VA2k| Smalltalk   |    2320|  2320|     13|     1|  1868|    0| 1    |   1| 5.13|  240| visualage2.kern   
    VW1 | Smalltalk   |     387|   387|      9|     1|   246|    0| 1    |   1| 2.74|   87| visualworks1      
    VW2 | Smalltalk   |    1956|  1956|     15|     1|  1332|    0| 1    |   1| 3.13|  181| visualworks2      
        |             |       6|     9|      4|     2|     1|    0| 1.50 |   2| 1.20|    2| vtbl              
        | OVERALLS    |   15246| 63963|     17|   298| 10877|  199| 1.11 |  16| 3.89|  323| Overalls          

The number of paths represents the number of distinct inheritance paths from the 
classes in the hierarchy to the roots of the hierarchy. This number reflects the number of possible subobjects in the 
hierarchy. The roots listed in the table are classes with no base classes. We 
will subsequently use the term "non-leaf" to refer to the possible root of 
a subhierarchy. Leafs are classes with no children, while "both" refers to 
utility classes that are both roots and leafs and thus neither have base nor 
derived classes. The average for the number of parents and the number of 
children were computed only among the classes having at least one parent or at 
least one child correspondingly.

71% of the classes in the entire benchmarks suite were leaf classes. 
Out of the 4369 non-leaf classes, 36% were spawning a subhierarchy of only 
2 classes (including the root), 15% -- a subhierarchy of 3 classes, 
10% of 4, 7% of 5 and so forth. Turning this into a cumulative distribution, 
M of subhierarchies had more than N classes in them:

 M |  1% |  3% | 5% | 10% | 20% | 25% | 50% | 64% | 100%
---|-----|-----|----|-----|-----|-----|-----|-----|-----
 N | 700 | 110 | 50 |  20 |  10 |   7 |   3 |   2 |    1

Which means 1% of subhierarchies had more than 700 classes in them, 3% of subhierarchies 
had more than 110 classes, 5% of subhierarchies had more than 50 classes, 10% 
of subhierarchies had more than 20 classes, 20% of subhierarchies had more than 
10 classes, 25% of hierarchies had more than 7 classes, only 50% of 
hierarchies had more than 3 classes and 64% -- more than 2.

References
----------

1. J. Vitek, R. N. Horspool, and A. Krall. Efficient type inclusion tests. In Proc. of the 12th ACM SIGPLAN conference on Object-oriented programming, systems, languages, and applications, OOPSLA '97, pages 142-157, New York, NY, USA, 1997. ACM.
2. A. Krall, J. Vitek, and R. N. Horspool. Near optimal hierarchical encoding of types. In In Proc. European Conference on Object-Oriented Programming, ECOOP'97, Lecture Notes in Computer Science, pages 128-145. Springer-Verlag, 1997.
3. Y. Zibin and J. Y. Gil. Efficient subtyping tests with PQencoding. In Proc. of the 16th ACM SIGPLAN conference on Object-oriented programming, systems, languages, and applications, OOPSLA '01, pages 96-107, New York, NY, USA, 2001. ACM.
4. R. Ducournau. Perfect hashing as an almost perfect subtype test. ACM Trans. Program. Lang. Syst., 30(6):33:1-33:56, Oct. 2008. ISSN 0164-0925.
5. Y. Solodkyy, G. Dos Reis, and B. Stroustrup. Open and efficient type switch for C++. In Proc. OOPSLA'12, pp 963-982. ACM.
6. Y. Solodkyy, G. Dos Reis, and B. Stroustrup. Open pattern matching for C++. In Proc. GPCE'13. ACM, October 2013.
