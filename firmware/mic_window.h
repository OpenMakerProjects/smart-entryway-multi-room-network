#pragma once
#include <cmath>
#include <cstdint>
struct MicWindow {
 float low=3.3f,high=0;uint32_t count=0;bool clean=true;
 void add(float v){if(!std::isfinite(v)||v<=0.03f||v>=3.25f){clean=false;return;}if(v<low)low=v;if(v>high)high=v;if(count<100000)++count;}
 bool valid()const{return clean&&count>=20;}
 float peak()const{return valid()?high-low:NAN;}
 bool loud()const{return valid()&&high-low>=0.25f;}
 void reset(){low=3.3f;high=0;count=0;clean=true;}
};
