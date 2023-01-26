/* test program for the progressbar class */

#include <chrono>
#include <iostream>
#include <thread>

#include "progress/progress.hpp"

int main() {
    for (progress::Progress bar(1000); int cycle : bar.name("such wow")) {
        // the program...
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    for (progress::Progress bar(1000);
         int cycle : bar.name("much amaze").style("/= /").ticks(100)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    for (progress::Progress bar(100); int cycle : bar.name("biiig").length(100)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    for (progress::Progress bar(1000);
         int cycle :
         bar.name("numbers?").length(50).ticks(1000).style("|= |").update(5).show_bar(false)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
