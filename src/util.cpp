/*
 * util.cpp
 *
 *  Created on: Jan 6, 2015
 *      Author: bulentk
 *
 *  Copyright (C) 2010 by Bulent Kopuklu (bulent.kopuklu@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"
#include "util.h"

namespace util {

long tick()
{
    struct timeval tv;
    if (::gettimeofday(&tv, NULL) != 0)
        return 0;
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void sleep(unsigned u)
{
    struct timespec timeout = {
            (__time_t)(u / 1000),
            (long int)((u % 1000) * 1000 * 1000)
            };
    ::nanosleep(&timeout, NULL);
}

long timespan(long b)
{
    long e = util::tick();

    return e-b;
}

}
