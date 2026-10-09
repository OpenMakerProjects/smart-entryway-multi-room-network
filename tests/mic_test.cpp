#include "../firmware/mic_window.h"
#include <cassert>
#include <iostream>
int main(){MicWindow w;assert(!w.valid()&&!w.loud());for(int i=0;i<20;i++)w.add(i%2?1.3f:1.0f);assert(w.valid()&&w.loud());w.add(0);assert(!w.valid()&&!w.loud());w.reset();for(int i=0;i<25;i++)w.add(1.2f);assert(w.valid()&&!w.loud());w.add(NAN);assert(!w.valid());w.reset();for(int i=0;i<19;i++)w.add(1.0);assert(!w.valid());std::cout<<"sample-count, peak-to-peak, quiet, clipped/NaN fault and recovery tests passed\n";}
