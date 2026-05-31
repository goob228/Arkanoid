#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Base.h"
#include "SFMLtypes.h"
#include "WindowHandler.h"






enum class Event{
    CLOSE_WINDOW,
    CLICK_MOUSE,
    CLICK_ESC
};



class EventHandler{

public:

    
    std::vector<Event> _events;

    void handleEvents(WindowHandler* const windowHandler);

    static iVector2 getMousePos(WindowHandler* const windowHandler);

};



#endif