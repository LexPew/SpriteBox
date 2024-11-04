/*
    GecProject - For GEC students to use as a base for their projects.
    Already has SFML linked and ImGui set up.
*/
#include "ExternalHeaders.h"
#include "RedirectCout.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFMLGraphics.h"

#include "Game.h"



int main()
{

    //--Debug Section--

	//Redirect cout to HAPI
    outbuf ob;

    std::streambuf* sb = std::cout.rdbuf(&ob);

	//Redirect cerr
    outbuferr oberr;
   std::streambuf* sberr = std::cerr.rdbuf(&oberr);

    // Turn on memory leak checking
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //_CrtSetBreakAlloc(4052);
    Game newGame = Game();
    while(newGame.GetRunning())
    {
	    //Running so no need to do anything
    }
    return 0;

}



