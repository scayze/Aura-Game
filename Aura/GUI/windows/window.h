#ifndef Window_H
#define Window_H

#include <SFML\Graphics.hpp>
#include "../../RessourceManager/Resources.h"

class Window
{

protected:
	std::vector<sf::Drawable *> drawables;



public:

	Window();
	virtual void tick();
	virtual void render(sf::RenderTexture * rW);

};

#endif
