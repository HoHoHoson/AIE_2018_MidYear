#pragma once
#include <thread>
#include <functional>
#include <chrono>
#include <iostream>
#include <cstdio>
#include <cmath>

#ifndef _WIN32
#include <termios.h>
#else
#include <conio.h>
#endif

using namespace std::chrono_literals;

namespace AsyncKeyboard
{
	namespace details
	{
		static bool shouldShutdown = false;
		static std::thread asyncThread;

#ifndef _WIN32 
		static struct termios tOld, tNew;
		#
		/* Initialize new terminal i/o settings */
		void initTermios(int echo)
		{
			tcgetattr(0, &tOld); /* grab old terminal i/o settings */
			tNew = tOld; /* make new settings same as old settings */
			tNew.c_lflag &= ~ICANON; /* disable buffered i/o */
			if (echo) {
				tNew.c_lflag |= ECHO; /* set echo mode */
			}
			else {
				tNew.c_lflag &= ~ECHO; /* set no echo mode */
			}
			tcsetattr(0, TCSANOW, &tNew); /* use these new terminal i/o settings now */

		}

		/* Restore old terminal i/o settings */
		void resetTermios(void)
		{
			tcsetattr(0, TCSANOW, &tOld);

		}
#endif
		/* Read 1 character - echo defines echo mode */
		char getch()
		{
#ifndef _WIN32 
			char ch;
			initTermios(0);
			ch = getchar();
			resetTermios();
			return ch;
#else
			return ::_getch_nolock();
#endif
		}
	}

	extern void setupKeyboard(std::function<void(const char)> fnc)
	{
		std::thread thread = std::thread([&, fnc]() {
			std::cout << "Starting thread ..\n";

			while (!details::shouldShutdown) {
				auto c = details::getch();
				fnc(c);
				//std::this_thread::sleep_for(1ms);
			}

			std::cout << "Shutting down thread..\n";

		});


		details::asyncThread = std::move(thread);
	}

	extern void shutdown() { details::shouldShutdown = true; details::asyncThread.join(); }
}
