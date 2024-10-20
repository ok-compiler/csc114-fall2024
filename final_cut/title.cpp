#include <iostream>
#include "engine.h" // game engine file
//#include "info.h" // info/data for enemies, items, buffs, etc
using namespace std;

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;
// sleep functions to slow down program
 
int title_screen() {
	// title screen
cout << R"(//    ______     _                              __                _   _               _       )" << endl;
sleep_for(500ms);
cout << R"(//   |  ____|   | |                            / _|     /\       | | | |             (_)      )" << endl;
sleep_for(500ms);
cout << R"(//   | |__   ___| |__   ___   ___  ___    ___ | |_     /  \   ___| |_| |__   ___ _ __ _  __ _ )" << endl;
sleep_for(500ms);
cout << R"(//   |  __| / __| '_ \ / _ \ / _ \/ __|  / _ \|  _|   / /\ \ / _ \ __| '_ \ / _ \ '__| |/ _` |)" << endl;
sleep_for(500ms);
cout << R"(//   | |___| (__| | | | (_) |  __/\__ \ | (_) | |    / ____ \  __/ |_| | | |  __/ |  | | (_| |)" << endl;
sleep_for(500ms);
cout << R"(//   |______\___|_| |_|\___/ \___||___/  \___/|_|   /_/    \_\___|\__|_| |_|\___|_|  |_|\__,_|)" << endl;
sleep_for(500ms);
cout << R"(//                                                                                            )" << endl;
sleep_for(500ms);
cout << R"(//               )" << endl;
sleep_for(1s);
	return 0;
}
