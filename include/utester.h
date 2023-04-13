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

#if defined(ANDROID)
#   include <android/log.h>
#   define LOG_TAG "mwg"
#   define lprint(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#   define lerror(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#else
#   define LOG_TAG "mwg"
#   define lprint(...) fprintf(stdout, __VA_ARGS__)
#   define lerror(...) fprintf(stderr, __VA_ARGS__)
#endif

#define tlog(__x__) \
    lprint("%s\n", (((std::ostringstream &)(std::ostringstream().seekp(0, std::ios_base::cur) << __x__)).str()).c_str())
    // std::cout << (((std::ostringstream &)(std::ostringstream().seekp(0, std::ios_base::cur) << __x__)).str()) << std::endl


namespace utester {

class Object {
public:
    std::string name;

    virtual void ctor() {}
    virtual void dtor() {}
    virtual ~Object() {}

protected:
    Object (std::string const& n) : name(n) {}
};

class Test : public Object {
public:
    std::string description;

    virtual void run() = 0;

protected:
    Test(std::string n, std::string d) : 
        Object(n), description(d) {
    }
};

typedef std::vector<Object*> ObjectList;

class Scope : public Object {
    ObjectList m_lstObjects;

public:
    virtual void addChildObject(Object* pObj) {
        m_lstObjects.push_back(pObj);        
    }

    virtual ObjectList const& getChildObjects() const {
        return m_lstObjects;        
    }

    virtual ~Scope() {
        for (auto p : m_lstObjects)
            delete p;

        m_lstObjects.clear();
    }

protected:
    Scope(std::string const& n) : Object(n) {
    }

};

class Suit : public Scope {
protected:
    Suit(std::string const& n) : Scope(n) {

    }
};

int start(int argc, char* argv[]);

}

extern "C" {

utester::Suit* CreateSuit();

}





#endif /* utester_h__ */
