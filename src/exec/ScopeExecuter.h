/*
 * ScopeExecuter.h
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

#ifndef ScopeExecuter_h__
#define ScopeExecuter_h__

#include "TestExecuter.h"

class ScopeExecuter :
    public Executer
{
    utester::Scope* m_pScope;

public:
    void run();
    utester::Object* getObject() const;

    Executer* getExecuter(std::string const& names);

protected:
    utester::Object* getChildObjectByName(std::string const& name);
    static void run(ScopeExecuter* pScope);

public:
    ScopeExecuter(utester::Scope* pScope, std::string const& strOwner="");
    virtual ~ScopeExecuter();
};

#endif /* ScopeExecuter_h__ */
