#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class VisualsSetter
{
public:
	Text* createNewText(Font& font, string textString, Vector2f position, unsigned int charSize);
	void setSpriteScale(Sprite& sprite, float targetWidth, float targetHeight);
};

