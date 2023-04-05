/*
 * main.cpp
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

namespace utester {


void signalhandler(int sig)
{
    std::cout << "signal -> " << sig << std::endl;
}

void usage()
{

}

int main(int argc, char* argv[])
{
//    signal(SIGABRT, signalhandler);
//    signal(SIGFPE, signalhandler);
//    signal(SIGILL, signalhandler);
//    signal(SIGINT, signalhandler);
//    signal(SIGSEGV, signalhandler);
//    signal(SIGTERM, signalhandler);

    utester::Args args;

    int ch;
//    while ((ch = getopt(argc, argv, "i:o:h")) != -1)
    while ((ch = getopt(argc, argv, "o:h")) != -1)
    {
        switch (ch)
        {
        case 'i':
            args.impl = optarg;
            break;
        case 'o':
            args.object = optarg;
            break;
        case 'h':
            usage();
            return 0;
        }
    }

    // if (args.impl.empty())
    // {
    //     usage();
    //     return -1;
    // }


    try
    {
        utester::run(args);
    }
    catch (std::exception& e)
    {
        std::cerr << std::endl << KRED << KBOLD << "error -> " << e.what() << KNRM << std::endl << std::endl;
    }


    return 0;
}

}