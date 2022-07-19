#include "window.h"
#include "os/thread.h"
#include "os/system.h"
#include "main_class.h"

__USING_API 

int main(void)
{ 
    System::init(&Main::run); 
} 
