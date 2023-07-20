#pragma once

template<typename Type>
Type Lerp(Type a, Type b, float t)
{
   // return ((b - a) / abs((b - a))) * t;
   return a + ((b - a) / abs((b - a))) * t;
}
