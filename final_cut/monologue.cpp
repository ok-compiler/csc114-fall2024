#include <iostream>
#include "engine.h" // game engine file
using namespace std;

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;
// sleep functions to slow down program
 
int opening_monologue() {
cout << "In a time long forgotten, the world of Aetheria was whole, bathed in the light of creation." << endl;
sleep_for(2s);
cout << "The gods, once united, shaped the land, the seas, and the skies, weaving their magic into the very fabric of existence." << endl;
sleep_for(2s);
cout << "But as the ages passed, greed and envy poisoned their hearts, and a war unlike any other began.\n\n";
sleep_for(4s);
cout << "The heavens trembled. The earth cracked. And the magic that gave life to Aetheria turned wild, uncontrollable." << endl;
sleep_for(2s);
cout << "In their fury, the gods shattered the world into fragments, each piece guarded by the spirits of the elements—Earth, Air, Fire, and Water.\n\n";
sleep_for(4s);
cout << "Yet from the ashes of their destruction, a hero arose." << endl;
sleep_for(2s);
cout << "Blessed by the spirits, they stood against the darkness and sealed away the source of the gods' madness—an ancient force known only as the Void.\n\n";
sleep_for(4s);
cout << "But that was a thousand years ago...\n\n";
sleep_for(4s);
cout << "Now, the Void stirs once more. Its shadow creeps across the land, and the elemental spirits grow silent." << endl;
sleep_for(2s);
cout << "The world, once filled with magic, is dying." << endl;
sleep_for(2s);
cout << "Aetheria needs a hero again..." << endl;
sleep_for(2s);
cout << "You, Kael, are that hero. Whether you believe it or not, your destiny is written in the stars." << endl;
sleep_for(2s);
cout << "The echoes of the past call out to you, and the fate of the world rests in your hands." << endl;
sleep_for(5s);
cout << "The world may have forgotten the ancient war, but the Void has not." << endl;
sleep_for(2s);

	return 0;
}
