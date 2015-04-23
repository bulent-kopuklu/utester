/*
 * Scope.cpp
 *
 *  Created on: Mar 17, 2015
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

namespace utester {

Scope::~Scope()
{
    ObjectList::iterator it;
    for (it = m_lstObjects.begin(); it != m_lstObjects.end(); ++it)
    {
        delete (*it);
    }

    m_lstObjects.clear();
}

void Scope::addChildObject(Object* pObject)
{
    m_lstObjects.push_back(pObject);
}

ObjectList const& Scope::getChildObjects() const
{
    return m_lstObjects;
}

}
