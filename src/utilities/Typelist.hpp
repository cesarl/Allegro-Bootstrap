#ifndef					__TYPELIST_HPP__
# define				__TYPELIST_HPP__

template				<class T1, class T2>
struct TypeList
{
typedef T1 Head;
  typedef T2 Tail;
};

struct NullType {};

#define TYPELIST_1(t1)                                 TypeList<t1, NullType>
#define TYPELIST_2(t1, t2)                             TypeList<t1, TYPELIST_1(t2) >
#define TYPELIST_3(t1, t2, t3)                         TypeList<t1, TYPELIST_2(t2, t3) >
#define TYPELIST_4(t1, t2, t3, t4)                     TypeList<t1, TYPELIST_3(t2, t3, t4) >
#define TYPELIST_5(t1, t2, t3, t4, t5)                 TypeList<t1, TYPELIST_4(t2, t3, t4, t5) >
#define TYPELIST_6(t1, t2, t3, t4, t5, t6)             TypeList<t1, TYPELIST_5(t2, t3, t4, t5, t6) >
#define TYPELIST_7(t1, t2, t3, t4, t5, t6, t7)         TypeList<t1, TYPELIST_6(t2, t3, t4, t5, t6, t7) >
#define TYPELIST_8(t1, t2, t3, t4, t5, t6, t7, t8)     TypeList<t1, TYPELIST_7(t2, t3, t4, t5, t6, t7, t8) >
#define TYPELIST_9(t1, t2, t3, t4, t5, t6, t7, t8, t9) TypeList<t1, TYPELIST_8(t2, t3, t4, t5, t6, t7, t8, t9) >

#endif					// __TYPELIST_HPP__
