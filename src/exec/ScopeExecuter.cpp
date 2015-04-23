/*
 * ScopeExecuter.cpp
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
#include "ScopeExecuter.h"

ScopeExecuter::ScopeExecuter(utester::Scope* pScope, std::string const& strOwner) :
    Executer(pScope->getName(), strOwner),
    m_pScope(pScope)
{
}

ScopeExecuter::~ScopeExecuter()
{
}

utester::Object* ScopeExecuter::getObject() const
{
    return m_pScope;
}

static void splitObjectPath(
        std::string const& obj,
        std::vector<std::string>& names
        )
{
    std::string s(obj);
    while (!s.empty())
    {
        size_t i = s.find('.');
        if (i == std::string::npos)
        {
            names.push_back(s);
            break;
        }

        names.push_back(s.substr(0, i));
        s = s.substr(i+1);
    }
}

static bool isScope(utester::Object* pObj)
{
    return (NULL != dynamic_cast<utester::Scope*>(pObj));
}

Executer* ScopeExecuter::getExecuter(std::string const& objpath)
{
    std::vector<std::string> names;
    splitObjectPath(objpath, names);

    ScopeExecuter* pScope = this;
    for (uint i = 0; i < names.size(); ++i)
    {
        utester::Object* pObj = pScope->getChildObjectByName(names[i]);
        if (NULL == pObj)
            return NULL;

        if (!isScope(pObj))
        {
            TestExecuter* pTest = new TestExecuter((utester::Test*)pObj, pScope->getName());
            pScope->addChild(pTest);

            return pTest;
        }

        ScopeExecuter* pTmp = new ScopeExecuter((utester::Scope*)pObj, pScope->getName());
        pTmp->ctor();
        pScope->addChild(pTmp);
        pScope = pTmp;
    }

    return pScope;
}

utester::Object* ScopeExecuter::getChildObjectByName(std::string const& name)
{
    utester::ObjectList const& objs = m_pScope->getChildObjects();
    for (uint i = 0; i < objs.size(); ++i)
    {
        utester::Object* pObj = objs[i];
        if (pObj->getName() == name)
        {
            return pObj;
        }
    }

    return NULL;
}

void ScopeExecuter::run(ScopeExecuter* pScope)
{
    if (!pScope->ctor())
        return;

    long lBegin = util::tick();

    utester::ObjectList const& objs = pScope->m_pScope->getChildObjects();
    for (size_t i = 0; i < objs.size(); ++i)
    {
        utester::Object* pObj = objs[i];
        if (!isScope(pObj))
        {
            TestExecuter* pTest = new TestExecuter((utester::Test*)pObj, pScope->getName());
            pScope->addChild(pTest);

            pTest->run();
        }
        else
        {
            ScopeExecuter* p = new ScopeExecuter((utester::Scope*)pObj, pScope->getName());
            pScope->addChild(p);

            run(p);
        }
    }

    pScope->setRunTime(util::timespan(lBegin));

    pScope->dtor();
}

void ScopeExecuter::run()
{
    run(this);
}
