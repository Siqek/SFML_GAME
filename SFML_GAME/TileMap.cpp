#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}


TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
		throw("ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET. TEXTURE_FILE: " + texture_file);
}

TileMap::~TileMap()
{
	this->clear();

	/* delete this->tileTextureSheet; */
}


//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z,
	const sf::IntRect& texture_sheet,
	const bool& collision, const short& type)
{
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_sheet, collision, type);
			std::cout << "DEBUG: ADDED NEW TILE" << std::endl;
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
			std::cout << "DEBUG: REMOVED TILE" << std::endl;
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/* Save current map to a text file */

	std::ofstream outp_file;

	outp_file.open(file_name);

	if (outp_file.is_open())
	{
		outp_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if (this->map[x][y][z])
						outp_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << "\n";
				}
			}
		}
	}
	else
	{
		throw("ERROR::TILEMAP::COULD NOT TO SAVE THE TILEMAP TO FILE. FILE_NAME: '" + file_name + "'");
	}

	outp_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	/* Load map from a text file */

	std::ifstream inp_file;

	inp_file.open(file_name);

	if (inp_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool collision = false;
		short type = 0;
		inp_file;

		inp_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		this->gridSizeF = gridSize;
		this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, nullptr);
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			throw("ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET. TEXTURE_FILE: " + texture_file);

		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if (this->map[x][y][z])
						inp_file;
				}
			}
		}

		while (inp_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y,
				this->gridSizeF, this->tileSheet,
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				collision, type);
		}
	}
	else
	{
		throw("ERROR::TILEMAP::COULD NOT TO LOAD THE TILEMAP FROM FILE. FILE_NAME: '" + file_name + "'");
	}

	inp_file.close();
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}

