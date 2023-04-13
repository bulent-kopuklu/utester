/*
 * util.h
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

#ifndef util_h__
#define util_h__

#define KBOLD  "\x1B[1m"
#define KACCORD "\x1B[2m"
#define KULINE "\x1B[4m"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


#define tbegin0(_n) \
    utlog(KBOLD << KBLU << _n)

#define tbegin1(_n, _d) \
    utlog(KBOLD << KBLU << _n << KNRM << " -> " << _d)

// KBOLD << KBLU << _s << "::" << _t <<
#define tsuccess(_n, _m, _t) \
    utlog(KBLU << _n << "." << _m << KGRN << " completed ... duration:" << _t << " ms."<<  KNRM)

#define terror(_n, _m, _e) \
    utlog(KBLU << _n << "." << _m << KRED << " completed with error !!! err:" << _e << KNRM)

namespace exec {
class Statistics;
}

namespace util {

long tick();
void sleep(unsigned u);
long timespan(long b);

template <class _Ty>
_Ty* GetObject(std::vector<_Ty*> const& lst, std::string const& strName)
{
    typename std::vector<_Ty*>::const_iterator it;
    for (it = lst.begin(); it != lst.end(); ++it)
        if ((*it)->getName() == strName)
            return (*it);
    return NULL;
}


}

#endif /* util_h__ */
