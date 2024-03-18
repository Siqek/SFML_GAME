#ifndef GUI_H
#define GUI_H

class Button;
class DropDownList;
class TextureSelector;

enum button_states
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

namespace gui
{
	class Button
	{
	private:
		//Variables
		short unsigned buttonState;
		short unsigned id;
		bool wasPressed;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned charackter_size = 11,
			sf::Color text_idle_color = sf::Color{ 0xFFFFFFFF }, sf::Color text_hover_color = sf::Color{ 0xFFFFFFFF }, sf::Color text_active_color = sf::Color{ 0xFFFFFFFF },
			sf::Color idle_color = sf::Color{ 0x000000FF }, sf::Color hover_color = sf::Color{ 0x000000FF }, sf::Color active_color = sf::Color{ 0x000000FF },
			sf::Color outline_idle_color = sf::Color{ 0x00000000 }, sf::Color outline_hover_color = sf::Color{ 0x00000000 }, sf::Color outline_active_color = sf::Color{ 0x00000000 },
			short unsigned id = 0);
		virtual ~Button();

		//Accessors
		const bool isPressed() const;
		const bool isClicked() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		DropDownList(float pos_x, float pos_y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned numOfElements, unsigned defult_index = 0);
		virtual ~DropDownList();

		//Accessos
		const bool getKeytime();
		const unsigned short& getActiveElementId() const;

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		//Variables
		float gridSize;
		bool active;
		bool hidden;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		TextureSelector(float x, float y, 
			float height, float width, float gridSize,
			const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};
}

#endif
