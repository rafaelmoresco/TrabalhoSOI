#include "keyinput.h"

DirectionKey KeyInput::_key = LEFT_KEY;
bool KeyInput::_handled = false;

DirectionKey KeyInput::get_key()
{
    return _key;
}

void KeyInput::set_key(DirectionKey key)
{
    _key = key;
}

bool KeyInput::get_handled()
{
	return _handled;
}
void KeyInput::set_handled(bool handled)
{
	_handled = handled;
}
