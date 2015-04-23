/*
 * Statistics.h
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

#ifndef Statistics_h__
#define Statistics_h__

namespace exec {

class Statistics
{
public:
    typedef std::vector<Statistics*> Childs;
private:
    std::string m_strName;
    int  m_iIsSuccess;
    long m_lRun;
    long m_lCtor;
    long m_lDtor;

    Childs m_lstChilds;

public:
    virtual std::string const& getName() const
    {
        return m_strName;
    }

    virtual bool isSuccess() const
    {
        if (m_iIsSuccess != -1)
            return m_iIsSuccess == 1;
        bool fRslt = true;
        Childs::const_iterator it;
        for (it = m_lstChilds.begin(); it != m_lstChilds.end(); ++it)
        {
            if (!(*it)->isSuccess())
            {
                fRslt = false;
                break;
            }
        }

        const_cast<Statistics*>(this)->markSuccess(fRslt);
        return fRslt;
    }

    virtual long getRunTime() const
    {
        if (m_lRun != -1)
            return m_lRun;
        long lRslt = 0;
        Childs::const_iterator it;
        for (it = m_lstChilds.begin(); it != m_lstChilds.end(); ++it)
            lRslt += (*it)->getRunTime();
        const_cast<Statistics*>(this)->setRunTime(lRslt);
        return lRslt;
    }

    virtual long getCtorTime() const
    {
        if (m_lCtor != -1)
            return m_lCtor;
        long lRslt = 0;
        Childs::const_iterator it;
        for (it = m_lstChilds.begin(); it != m_lstChilds.end(); ++it)
            lRslt += (*it)->getCtorTime();
        const_cast<Statistics*>(this)->setCtorTime(lRslt);
        return lRslt;
    }

    virtual long getDtorTime() const
    {
        if (m_lDtor != -1)
            return m_lDtor;
        long lRslt = 0;
        Childs::const_iterator it;
        for (it = m_lstChilds.begin(); it != m_lstChilds.end(); ++it)
            lRslt += (*it)->getDtorTime();
        const_cast<Statistics*>(this)->setDtorTime(lRslt);
        return lRslt;
    }

    virtual void markSuccess(bool fIsSuccess = true)
    {
        m_iIsSuccess = fIsSuccess ? 1 : 0;
    }

    virtual void setRunTime(long l)
    {
        m_lRun = l;
    }

    virtual void setCtorTime(long l)
    {
        m_lCtor = l;
    }

    virtual void setDtorTime(long l)
    {
        m_lDtor = l;
    }

public:
    void addChild(Statistics* pChild)
    {
        m_lstChilds.push_back(pChild);
    }

    Childs const& getChilds() const
    {
        return m_lstChilds;
    }

public:
    Statistics(std::string const& strName) :
        m_strName(strName),
        m_iIsSuccess(-1),
        m_lRun(-1),
        m_lCtor(-1),
        m_lDtor(-1)
    {
    }

    virtual ~Statistics()
    {
    }
};

}


#endif /* Statistics_h__ */
