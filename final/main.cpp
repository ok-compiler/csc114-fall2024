#include "map.h"
#include <iostream>
#include <stdio.h> 
#include <string>
using namespace std;
#include <mutex> 
mutex mtx;

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

#include "map.h"
#include "piece.h"
#include "ui.h"


int main() {
    system("gsettings set org.gnome.desktop.interface monospace-font-name 'Crisp 12'");
    mapInit();
    updatePiece(0);
    
    thread t1(updatePos);
    thread t2(updatePiece, 1);
    
    t1.join();
    t2.join();
    return 0;
}

