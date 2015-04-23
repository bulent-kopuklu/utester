/*
 * Logger.h
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

#ifndef Logger_h__
#define Logger_h__

class Logger
{
    static Logger* m_pThis;
public:
    static Logger& instance(std::ostream* pos = NULL);
    static void release();

private:
    std::ostream* m_pos;
    pthread_t m_hThread;

    int m_iout;
    int m_ierr;

    int m_stop[2];
    int m_stdout[2];
    int m_stderr[2];
    int m_stdint[2];

    std::string m_strErr;
    std::string m_strOut;


public:
    void write(std::string const& str);

    void flush();

protected:
    std::string fix(int state, std::string const& str);

protected:
    void start();
    void stop();

    void run();

    void onStdOut();
    void onStdErr();
    void onIntLog();
protected:
    static void* main(void* pvParam);

protected:
    Logger(std::ostream* pos);

public:
    virtual ~Logger();

};

#define KBOLD  "\x1B[1m"
#define KACCORD "\x1B[2m"
#define KULINE "\x1B[4m"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#if 0
    Logger::instance().write( \
            (((std::ostringstream &)(std::ostringstream().seekp(0, std::ios_base::cur) << __x__)).str()) \
            )
#endif




#endif /* Logger_h__ */
