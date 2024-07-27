#ifndef MYUTILS_H
#define MYUTILS_H

template<typename Type>
Type Lerp(Type a, Type b, float t)
{
   // return ((b - a) / abs((b - a))) * t;
   return a + 1 * t;
}

#endif // !MYUTILS_H