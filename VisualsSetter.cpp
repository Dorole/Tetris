#include "VisualsSetter.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Text* VisualsSetter::createNewText(Font& font, string textString, Vector2f position, unsigned int charSize)
{
	Text* newText = new Text();
	newText->setFont(font);
	newText->setString(textString);
	newText->setPosition(position);
	newText->setCharacterSize(charSize);

	return newText;
}

void VisualsSetter::setSpriteScale(Sprite& sprite, float targetWidth, float targetHeight)
{
	float scaleX = targetWidth / sprite.getGlobalBounds().width;
	float scaleY = targetHeight / sprite.getGlobalBounds().height;
	sprite.setScale(scaleX, scaleY);
}
