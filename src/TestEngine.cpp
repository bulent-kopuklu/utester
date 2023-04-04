/*
 * TestEngine.cpp
 *
 *  Created on: Dec 17, 2014
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
#include "TestEngine.h"
#include "exec/ScopeExecuter.h"
#include "Output.h"


namespace utester {

class TestEngine
{
public:
    void run(Suit* pSuit, std::string const& objpath)
    {
        ScopeExecuter suit(pSuit);
        if (!suit.ctor())
            return;

        if (!objpath.empty())
        {
            Executer* pExec = suit.getExecuter(objpath);
            if (pExec == NULL)
                throw std::runtime_error(std::string("object not found !!! ") + objpath);

            pExec->run();
        }
        else
        {
            suit.run();
        }

        suit.dtor();

        output::printScopeStat(&suit);
    }

};


void run(Args const& argv)
{
    // void* pvh = dlopen(argv.impl.c_str(), RTLD_GLOBAL|RTLD_LAZY);
    // if (pvh == NULL)
    //     throw std::invalid_argument(dlerror());

    // typedef Suit* (*CreatorPtr)();
    // CreatorPtr ptr = (CreatorPtr) dlsym(pvh, "CreateSuit");
    // if (NULL == ptr)
    //     throw std::runtime_error(dlerror());
    // Suit* pSuit = (*ptr)();
    Suit* pSuit = CreateSuit();
    if (NULL == pSuit)
        throw std::runtime_error("suit is null");

    try
    {
        TestEngine().run(pSuit, argv.object);
    }
    catch (std::exception& e)
    {
        throw;
    }
}

}
