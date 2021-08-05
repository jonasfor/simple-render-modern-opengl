#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>



class Display
{
private:
    SDL_GLContext m_GLcontext;
    SDL_Window * m_window;
    bool m_IsClosed;

public:
    void Update();
    bool isClosed();
    
    Display(int width, int height, const std::string title);
    virtual~Display();
};


#endif //DISPLAY_H