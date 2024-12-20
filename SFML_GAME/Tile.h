#ifndef TILE_H
#define TILE_H

enum TileTypes
{
	DEAFULT = 0,
	DAMAGING,
	TILETYPES_NUM
};

class Tile
{
private:
	

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEAFULT);
	virtual ~Tile();

	//Functions
	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);
};

#endif
