/*
 * Logger.cpp
 *
 *  Created on: Dec 29, 2014
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
#include "Logger.h"

static std::string __read__(int fd)
{
    std::ostringstream os;
    for ( ; ; )
    {
        char sz[9000] = { 0 };
        int iRead = read(fd, sz, sizeof(sz));
        if (iRead <= 0)
            break;
        os << sz;
        if (iRead < 512)
            break;
    }

    return os.str();
}

static void __write__(int fd, std::string const& str)
{
    char const* pszCrnt = str.c_str();
    int iLength = str.length();

    while (iLength > 0)
    {
        int iWritten = ::write(fd, pszCrnt, iLength);
        if (iWritten <= 0)
        {
            return;
        }

        pszCrnt += iWritten;
        iLength -= iWritten;
    }
}

bool __get_line__(std::string& strAll, std::string& strLine)
{
    std::string::size_type n = strAll.find("\n");
    if (n == std::string::npos)
        return false;
    strLine = strAll.substr(0, n+1);
    strAll = strAll.substr(strLine.length(), strAll.length());

    return true;

//    std::ostringstream os;
//    while (!str.empty())
//    {
//        std::string::size_type n = s.find("\n");
//        if (n != std::string::npos)
//        {
//            std::string line = s.substr(0, n+1);
//            if (state == READY)
//            {
//                os << ">>>> " << line;
//            }
//            else
//            {
//                os << line;
//                state = READY;
//            }
//
//            s = s.substr(line.length(), s.length());
//        }
//        else
//        {
//            os << s;
//            state = WAITING;
//            break;
//        }
//    }
//
//    return os.str();
}

Logger* Logger::m_pThis;

Logger& Logger::instance(std::ostream* pos)
{
    if (m_pThis == NULL)
    {
        m_pThis = new Logger(pos);
        m_pThis->start();
    }

    return *m_pThis;
}

void Logger::release()
{
    if (m_pThis != NULL)
    {
        m_pThis->stop();
        delete m_pThis;
    }
}

Logger::Logger(std::ostream* pos) :
    m_pos(pos),
    m_hThread(0),
    m_iout(0),
    m_ierr(0)
{
}

Logger::~Logger()
{
}

void Logger::write(std::string const& str)
{
    __write__(m_stdint[1], str);
//    __write__(m_iout, str);

}

void Logger::flush()
{
    if (!m_strErr.empty())
    {
        std::string str(m_strErr);
        std::ostringstream os;
        os << KYEL;
        std::string strLine;
        while (__get_line__(str, strLine))
            os << "    " << strLine;
        os << KNRM;
        __write__(m_ierr, os.str());
        if (!str.empty())
            __write__(m_ierr, str.c_str());

    }

    if (!m_strOut.empty())
    {
        std::string str(m_strOut);
        std::ostringstream os;
        os << KACCORD;
        std::string strLine;
        while (__get_line__(str, strLine))
            os << "    " << strLine;
        os << KNRM;
        __write__(m_ierr, os.str());
        if (!str.empty())
            __write__(m_ierr, str.c_str());
    }
}

void Logger::start()
{

//    close(m_stdout[1]);
//    close(m_stderr[1]);

    if (0 != ::pthread_create(&m_hThread, NULL, main, this))
        throw std::runtime_error("pthread_create");
}

void Logger::stop()
{
    __write__(m_stop[1], "1");
    ::pthread_join(m_hThread, NULL);
}

void* Logger::main(void* pv)
{
    Logger* pThis = (Logger*)pv;

    pThis->m_iout = dup(STDOUT_FILENO);
    pThis->m_ierr = dup(STDERR_FILENO);

    (void)pipe(pThis->m_stop);
    (void)pipe(pThis->m_stdout);
    (void)pipe(pThis->m_stderr);
    (void)pipe(pThis->m_stdint);

    dup2(pThis->m_stdout[1], STDOUT_FILENO);
    dup2(pThis->m_stderr[1], STDERR_FILENO);

    pThis->run();

    dup2(pThis->m_iout, STDOUT_FILENO);
    dup2(pThis->m_ierr, STDERR_FILENO);

    close(pThis->m_stop[0]); close(pThis->m_stop[1]);
    close(pThis->m_stdout[0]);
    close(pThis->m_stderr[0]);
    close(pThis->m_stdint[0]); close(pThis->m_stdint[1]);

    pthread_exit(NULL);

    return NULL;
}


void Logger::run()
{
    for ( ; ; )
    {
        pollfd lst[8] = { 0 };
        int i = 0;
        lst[i].fd = m_stop[0];
        lst[i].events = POLLIN;//|POLLPRI;
        lst[i].revents = 0;
        ++i;
        lst[i].fd = m_stdout[0];
        lst[i].events = POLLIN;//|POLLPRI;
        lst[i].revents = 0;
        ++i;
        lst[i].fd = m_stderr[0];
        lst[i].events = POLLIN;//|POLLPRI;
        lst[i].revents = 0;
        ++i;
        lst[i].fd = m_stdint[0];
        lst[i].events = POLLIN;//|POLLPRI;
        lst[i].revents = 0;
        ++i;

        int iRslt = 0;
        do
        {
            iRslt = ::poll(lst, i, -1);
        }
        while (iRslt < 0 && errno == EINTR);

        if (iRslt < 0)
        {
            __write__(m_ierr, "poll failed !!!");
            abort();
        }

        if ((lst[3].revents & POLLIN) == POLLIN)
        {
            onIntLog();
        }


        bool fUser = false;
        if ((lst[1].revents & POLLIN) == POLLIN)
        {
            onStdOut();
            fUser = true;
        }

        if ((lst[2].revents & POLLIN) == POLLIN)
        {
            onStdErr();
            fUser = true;
        }


        if (fUser)
            continue;


        if ((lst[0].revents & POLLIN) == POLLIN)
        {
            char ch;
            if (0 > ::read(m_stop[0], &ch, 1))
            {
            }

            return;
        }
    }
}

void Logger::onStdErr()
{
    m_strErr += __read__(m_stderr[0]);
    if (m_strErr.empty())
        return;

    std::ostringstream os;
    os << KYEL;
    std::string strLine;
    while (__get_line__(m_strErr, strLine))
        os << "    " << strLine;
    os << KNRM;

    __write__(m_ierr, os.str());
}

void Logger::onStdOut()
{
    m_strOut += __read__(m_stdout[0]);
    if (m_strOut.empty())
        return;

    std::ostringstream os;
    os << KACCORD;
    std::string strLine;
    while (__get_line__(m_strOut, strLine))
        os << "    " << strLine;
    os << KNRM;

    __write__(m_iout, os.str());
}

void Logger::onIntLog()
{
    std::string str = __read__(m_stdint[0]);
    if (str.empty())
        return;
    __write__(m_iout, str);
}
