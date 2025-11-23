#include "TextInput.h"
#include "../GameMediator.h"

TextInput::TextInput(std::shared_ptr<GameMediator> gameMediatorPtr, float posX, float posY, unsigned int characterSize = 30, sf::Vector2f size = sf::Vector2f(200, 50), int charLimit = 0) : characterLimit(charLimit), font("JdmgtR34raz9.ttf"), text(font, "")
{
	gameMediator = gameMediatorPtr;

    // Setup rectangle
    rect.setPosition({ posX, posY });
    rect.setSize(size);
    rect.setFillColor(sf::Color::White);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color(127, 127, 127)); // Gray outline

    float horizontalAlign = rect.getGlobalBounds().size.x;
    text.setPosition({ posX + (horizontalAlign / 6.0f), posY });
    text.setCharacterSize(180);

    // Setup text
    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color::Black);

    inputString = "";
}

std::string TextInput::getText()
{
    return inputString;
}

void TextInput::handleTextEntered(const char32_t unicode)
{
    if (unicode < 128) {
        char c = static_cast<char>(unicode);
        if (c == '\r' || c == '\n') return; // Ignore newline characters
        if (characterLimit == 0 || inputString.length() < characterLimit) {
            inputString.push_back(c);
            updateText();
        }
    }
}

void TextInput::handleKeyPress(const sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::Backspace) {
        if (!inputString.empty()) {
            backspaceText();
            updateText();
        }
    }
}

void TextInput::Draw(sf::RenderWindow& window) {
    if (visible)
    {
        window.draw(rect);
        window.draw(text);
    }
}

Response TextInput::requestData(const std::string& request)
{
    if (request == "getVisible")
    {
		return visible;
	}
	else if (request == "getText")
	{
		return inputString;
	}
    else if (request == "charLimit")
	{
		return characterLimit;
	}

	Response hi = "hello";
    return hi;
}

void TextInput::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "reset")
	{
		inputString = "";
		updateText();
	}
	else if (message == "handleTextEntered")
	{
		Response textInputResponse = gameMediator->requestData("Game", "EventString");

		if (std::holds_alternative<std::string>(textInputResponse)) {
			std::string textInput = std::get<std::string>(textInputResponse);
            inputString = textInput;
            updateText();
		}
		else {
			std::cerr << "Error: Expected textInputResponse, but got " << textInputResponse.index() << std::endl;
		}
	}
}
