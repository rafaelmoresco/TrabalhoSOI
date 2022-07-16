#include "keyinput.h"

Key KeyInput::_key = L_KEY;
bool KeyInput::_handled = false;

Key KeyInput::get_key()
{
    return _key;
}

void KeyInput::set_key(Key key)
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
