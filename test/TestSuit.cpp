/*
 * TestSuit.cpp
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

/*
 * TestSuit.h
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

#include "utester.h"
#include <stdexcept>
#include <iostream>

class Scope0Test0 : public utester::Test
{
public:
    std::string getName() const
    {
        return "test0";
    }

    std::string getDescription() const
    {
        return "ctor exception";
    }

public:
    void run()
    {

    }

    void ctor()
    {
        throw std::runtime_error("booom !!!");
    }
};

class Scope0HedeTest0 : public utester::Test
{
public:
    std::string getName() const
    {
        return "test0";
    }

    std::string getDescription() const
    {
        return "dtor exception";
    }

public:
    void run()
    {
        std::cout << "test0 run" << std::endl;
    }

    void dtor()
    {
        throw std::runtime_error("booom !!!");
    }
};

class Scope0HedeTest1 : public utester::Test
{
public:
    std::string getName() const
    {
        return "test1";
    }

    std::string getDescription() const
    {
        return "run exception";
    }

public:
    void run()
    {
        throw std::runtime_error("booom !!!");
    }
};

class Scope0Hede :
    public utester::Scope
{
public:
    std::string getName() const
    {
        return "hede";
    }

public:
    Scope0Hede()
    {
        addChildObject(new Scope0HedeTest0());
        addChildObject(new Scope0HedeTest1());
    }
};

class TestScope0 :
    public utester::Scope
{
public:
    std::string getName() const
    {
        return "scope0";
    }

    void ctor()
    {
        addChildObject(new Scope0Test0());
        addChildObject(new Scope0Hede());
    }
};

class TestSuit :
    public utester::Suit
{
public:
    TestSuit()
    {
        addChildObject(new TestScope0());
//        addScope(new TestScope1());
//        addScope(new TestScope2());
    }
    void ctor()
    {
    }

    void dtor()
    {
    }
};

extern "C" {

utester::Suit* CreateSuit()
{
    return new TestSuit();
}

}

