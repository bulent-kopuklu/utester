/*
 * Output.cpp
 *
 *  Created on: Mar 19, 2015
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
#include "Output.h"

namespace output {

std::string name(std::string const& n)
{
    if (n.length() <= 53)
        return n;
    std::string s("...");
    s += n.substr((n.length() - 53) + s.length());
    return s;
}

void title(std::string const& strName, char ch = '-')
{
    uint len = (80 - strName.length()) / 2;
    std::string s(len, ch);

    std::ostringstream pos;

//    std::cout << s;
    pos << s;

    if (!strName.empty())
    {
//         std::cout << strName;
        pos << strName;
    }

//    std::cout << s;
    pos << s;
    uint len2 = (len*2) + strName.length();
    if (len2 < len)
    {
        std::string s2(len2, ch);
//        std::cout << s2;
        pos << s2;
    }

//    std::cout << std::endl;
    utprint("%s", pos.str().c_str());
}

void stat(exec::Statistics* ps, bool fIsBold = false)
{
    std::ostringstream pos;
    if (!ps->isSuccess())
    {
    //    std::cout << KRED;
//        pos << KRED;
    }

    if (fIsBold)
    {
        // std::cout << KBOLD;
//        pos << KBOLD;
    }

    // std::cout << std::setw(53) << std::left << name(ps->getName()) << " ";
    // std::cout << std::setw(8) << std::left << ((float)ps->getCtorTime() / 1000.0) << " ";
    // std::cout << std::setw(8) << std::left << ((float)ps->getDtorTime() / 10000.0) << " ";
    // std::cout << std::setw(8) << std::left << ((float)ps->getRunTime() / 1000.0);

    pos << std::setw(53) << std::left << name(ps->getName()) << " ";
    pos << std::setw(8) << std::left << ((float)ps->getCtorTime() / 1000.0) << " ";
    pos << std::setw(8) << std::left << ((float)ps->getDtorTime() / 10000.0) << " ";
    pos << std::setw(8) << std::left << ((float)ps->getRunTime() / 1000.0);

//    std::cout << KNRM << std::endl;
//    pos << KNRM << std::endl;
    utprint("%s", pos.str().c_str());

}

static bool isscope(exec::Statistics* pStat)
{
    return (NULL != dynamic_cast<ScopeExecuter*>(pStat));
}

struct TestResult
{
    uint total;
    uint failed;

    TestResult(uint t, uint f) :
        total(t),
        failed(f)
    {
    }
};

TestResult sstat(ScopeExecuter* pScope)
{
    exec::Statistics::Childs const& lst = pScope->getChilds();
    exec::Statistics::Childs::const_iterator it;

    uint f = 0;
    uint t = 0;

//    title(pScope->getName());

    bool fTitle = false;

    for (it = lst.begin(); it != lst.end(); ++it)
    {
        if (!isscope((*it)))
        {
            if (!(*it)->isSuccess())
                ++f;
            ++t;

            if (!fTitle)
            {
                title(pScope->getName());
                fTitle = true;
            }
            stat((*it));
        }
        else
        {
            TestResult rslt = sstat((ScopeExecuter*)(*it));
            f += rslt.failed;
            t += rslt.total;
        }
    }

//    std::cout << std::endl;
    title("");

    stat(pScope, true);
    // std::cout << "total  :" << t << std::endl;
    // std::cout << "success:" << (t-f) << std::endl;
    // std::cout << "failed :" << f << std::endl;

    std::ostringstream pos;
    pos << "total  :" << t << std::endl;
    pos << "success:" << (t-f) << std::endl;
    pos << "failed :" << f << std::endl;
    utprint("%s", pos.str().c_str());

    return TestResult(t, f);
}

void printScopeStat(ScopeExecuter* pSuit)
{
    uint uTotal = 0;
    uint uFailed = 0;
    exec::Statistics::Childs const& lst = pSuit->getChilds();
    exec::Statistics::Childs::const_iterator it;
    for (it = lst.begin(); it != lst.end(); ++it)
    {
        TestResult rslt = sstat((ScopeExecuter*)(*it));
        uTotal += rslt.total;
        uFailed += rslt.failed;
    }


    title("", '=');

    stat(pSuit, true);
    // std::cout << KBOLD;
    // std::cout << "total  :" << uTotal << std::endl;
    // std::cout << "success:" << (uTotal-uFailed) << std::endl;
    // std::cout << "failed :" << uFailed << std::endl;
    // std::cout << KNRM;

    std::ostringstream pos;
//    pos << KBOLD;
    pos << "total  :" << uTotal << std::endl;
    pos << "success:" << (uTotal-uFailed) << std::endl;
    pos << "failed :" << uFailed << std::endl;
//    pos << KNRM;

    utprint("%s", pos.str().c_str());
    //    exec::Statistics::Childs const& lst = pSuit->getChilds();
//    exec::Statistics::Childs::const_iterator its;
//    for (its = lst.begin(); its != lst.end(); ++its)
//    {
//        sstat((*its));
//        exec::Statistics* pScopeStat = (*its);
//        title(pScopeStat->getName());
//
//        uint uFailed = 0;
//        exec::Statistics::Childs const& lst0 = pScopeStat->getChilds();
//        exec::Statistics::Childs::const_iterator itt;
//        for (itt = lst0.begin(); itt != lst0.end(); ++itt)
//        {
//            if (isscope())
//            {
//
//            }
//
//            if (!(*itt)->isSuccess())
//                ++uFailed;
//            stat((*itt));
//        }
//
//        stat(pScopeStat);
//        std::cout << "total :" << lst0.size() << std::endl;
//        std::cout << "failed:" << uFailed << std::endl;
//
//    }



//    stat(pSuit);

}

}
