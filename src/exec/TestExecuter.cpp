/*
 * TestExecuter.cpp
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
#include "TestExecuter.h"

TestExecuter::TestExecuter(utester::Test* pTest, std::string const& strScopeName) :
    Executer(pTest->name, strScopeName),
    m_pTest(pTest)
{

}

TestExecuter::~TestExecuter()
{
}

utester::Object* TestExecuter::getObject() const
{
    return m_pTest;
}

void TestExecuter::run()
{
    tbegin1(getName(), m_pTest->description);

    if (!ctor())
        return;

    long lBegin = util::tick();

    // std::cout << KACCORD;
    lprint(KACCORD);
    std::string strError;

    try
    {
        m_pTest->run();
    }
    catch (std::exception& e)
    {
        strError = e.what();
    }

    // std::cout << KNRM;
    lprint(KNRM);
    setRunTime(util::timespan(lBegin));
    if (!strError.empty())
    {
        terror(getName(), "run()", strError);
        markSuccess(false);
    }
    else
        tsuccess(getName(), "run()", getRunTime());

    dtor();
}
