#ifndef keyinput_h
#define keyinput_h
#include "enum.h"

class KeyInput
{
    public:
				static bool get_handled();
				static void set_handled(bool handled); 
        static DirectionKey get_key();
        static void set_key(DirectionKey key);
    private:
				static bool _handled;
        static DirectionKey _key;
};

#endif
