#include <iostream>
using namespace std;
#include "map.h"
#include "piece.h"
#include "ui.h"

#include <mutex> 
mutex mtx;


int main() {
    system("gsettings set org.gnome.desktop.interface monospace-font-name 'Crisp 12'"); // set font to something more square
    mapInit(); // initialize the map
    updatePiece(0); // initialize the pieces
    
    thread t1(updatePos); // gravity function | runs in separate thread to drop piece every second
    thread t2(updatePiece, 1); // input function | runs in separate thread to take player input
    
    t1.join();
    t2.join();
    return 0;
}

