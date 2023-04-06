/*
 * utester.h
 *
 *  Created on: Dec 18, 2014
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

#ifndef utester_h__
#define utester_h__

#include <string>
#include <vector>
#include <map>

namespace utester {

class Object
{
public:
    virtual std::string getName() const = 0;

public:
    virtual void ctor() {}
    virtual void dtor() {}
    virtual ~Object() {}
};

class Test :
    public Object
{
public:
    virtual void run() = 0;
    virtual std::string getDescription() const = 0;
};

typedef std::vector<Object*> ObjectList;

class Scope :
    public Object
{
    ObjectList m_lstObjects;
public:
    virtual void addChildObject(Object* pObj) {
        m_lstObjects.push_back(pObj);        
    }
    virtual ObjectList const& getChildObjects() const {
        return m_lstObjects;        
    }

public:
    virtual ~Scope() {
        for (auto p : m_lstObjects)
            delete p;

        m_lstObjects.clear();

    }
};

class Suit :
    public Scope
{
    virtual std::string getName() const {
        return "Suit";
    }
};

int start(int argc, char* argv[]);

}

extern "C" {

utester::Suit* CreateSuit();

}





#endif /* utester_h__ */
