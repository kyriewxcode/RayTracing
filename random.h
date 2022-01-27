#pragma once
#ifndef __RANDOMH_H__
#define __RANDOMH_H__

#include <cstdlib>

inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

#endif // !__RANDOMH_H__