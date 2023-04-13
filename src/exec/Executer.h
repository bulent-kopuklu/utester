/*
 * Executer.h
 *
 *  Created on: Mar 16, 2015
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

#ifndef Executer_h__
#define Executer_h__

#include "Statistics.h"

class Executer :
    public exec::Statistics
{
    bool m_fIsConstructed;
    bool m_fIsDestructed;
public:
    Executer(std::string const& strName, std::string const& strOwner = "") :
        exec::Statistics(strOwner.empty() ? strName : strOwner+"."+strName),
        m_fIsConstructed(false),
        m_fIsDestructed(false)
    {
    }

public:
    virtual utester::Object* getObject() const = 0;
    virtual void run() = 0;

public:
    virtual bool ctor()
    {
        if (m_fIsConstructed)
            return true;
        // std::cout << KACCORD;

        std::string strError;
        long b = util::tick();

        try
        {
            getObject()->ctor();
        }
        catch (std::exception& e)
        {
            strError = e.what();
        }

        setCtorTime(util::timespan(b));

        // std::cout << KNRM;

        if (!strError.empty())
        {
            markSuccess(false);
            terror(getName(), "ctor()", strError);
            return false;
        }

        m_fIsConstructed = true;
        tsuccess(getName(), "ctor()", getCtorTime());

        return true;
    }

    virtual void dtor()
    {
        if (m_fIsDestructed)
            return;
        if (!m_fIsConstructed)
            return;
        m_fIsDestructed = true;

        exec::Statistics::Childs const& lst = getChilds();
        for (uint i = 0; i < lst.size(); ++i)
            ((Executer*)lst[i])->dtor();

        // std::cout << KACCORD;
        std::string strError;

        long b = util::tick();

        try
        {
            getObject()->dtor();
        }
        catch (std::exception& e)
        {
            strError = e.what();
        }

        setDtorTime(util::timespan(b));

        // std::cout << KNRM;
        if (!strError.empty())
        {
            terror(getName(), "dtor()", strError);
            return;
        }

        tsuccess(getName(), "dtor()", getDtorTime());
    }
};


#endif /* Executer_h__ */
