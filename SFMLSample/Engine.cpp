#include "pch.h"

Layer::Layer(std::vector <Object*> & objectsPreview)
{
	objects = objectsPreview;
}

Layer::Layer(std::vector <Object*> * objectsPreview)
{
	objects = *objectsPreview;
}

void Layer::draw(sf::RenderWindow & window)
{
	for (const auto & k : objects) k->draw(window);
}

void Layer::draw(sf::RenderWindow& window, sf::View& view, float zoom)
{
	for (const auto & k : objects) k->draw(window, view, zoom);
}

void Layer::addObject(Object* newObject)
{
	objects.push_back(newObject);
}

void Layer::addObject(Object& newObject)
{
	objects.push_back(&newObject);
}

unsigned Layer::getSize() const
{
	unsigned objectsSize = size_tToInt(objects.size());
	return objectsSize;
}

Engine::Engine()
{
	currentlySelectedObject = nullptr;
	deltaTime = 0;
	mapPointer = nullptr;
	event.type = sf::Event::Count;

	exitGame = false;
	logFile.open("Engine.log", std::ios::out);
	theGame.create(sf::VideoMode(1280, 720), "Emiriusu", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	Layers.push_back(new Layer);
	gameScreen.setSize(1280, 720);
	theGame.setView(gameScreen);
	gameScreen.zoom(data.Settings().getZoom());
}

Engine::~Engine()
{
	Layers.clear();
	logFile.close();
}

Engine& Engine::getInstance()
{
	static Engine instance;
	return instance;
}

void Engine::refreshWindow()
{
	sf::Vector2u size = theGame.getSize();
	gameScreen.setSize(float(size.x), float(size.y));
}

void Engine::draw() const
{
	for (const auto& i : Layers)
	{
		i->draw(theGameR, gameScreenR, Engine::getInstance().getData().Settings().getZoom()); /// ???
	}
}

void Engine::addLayer(Layer* newLayer)
{
	Layers.push_back(newLayer);
}

void Engine::addLayer(Layer& newLayer)
{
	Layers.push_back(&newLayer);
}

void Engine::addLayer(std::vector<Object*> & newLayer)
{
	Layer *temp = new Layer(newLayer);
	Layers.push_back(temp);
}

void Engine::addToLayer(Object& newObject, unsigned index)
{
	unsigned siz = size_tToInt(Layers.size()) - 1;
	if (index > siz) std::cerr << "Podano nieprawid�owy indeks warstwy!\n";
	index = std::min(index, siz);
	Layers[index]->addObject(newObject);
}

void Engine::addToLayer(Object* newObject, unsigned index)
{
	unsigned siz = size_tToInt(Layers.size()) - 1;
	if (index > siz) std::cerr << "Podano nieprawid�owy indeks warstwy!\n";
	index = std::min(index, siz);
	Layers[index]->addObject(newObject);
}

void Engine::increaseNumberOfLayers()
{
	Layers.push_back(new Layer);
}

sf::RenderWindow & Engine::getGameWindow()
{
	return theGame;
}
sf::View& Engine::getGameScreen()
{
	return gameScreen;
}

unsigned Engine::getNumberOfLayers() const { return size_tToInt(Layers.size()); }

Data& Engine::getData()
{
	return data;
}

Map* Engine::getGlobalMap()
{
	return globalMap;
}

void Engine::setGlobalMap(Map* newGlobalMap)
{
	globalMap = newGlobalMap;
}

void Engine::addToRenderSelectables(Selectable* selToRen)
{
	Log::newLog("Dodaje nowy obiekt do strumienia wy�wietlania");
	renderSelectables.push_back(selToRen);
}

void Engine::startGame()
{
	bool mouseClick = false;
	///Debug
	//miniTile mt(data.Textures().getTexture("TokenBeatle"), 1, 1);
	//addToLayer(mt, 0);

	///Test
	//theGame.setFramerateLimit(60);

	theGame.setVerticalSyncEnabled(true);

	Map map(data.World().getMapSize());
	setGlobalMap(&map);

	map.getTile(2, 2)->createCity(data.Textures().getTexture("CityTest1"));
	Army* testArmy = new Army(sf::Vector2i(map.test1.first, map.test1.second), map, data.Textures().getTexture("TokenBeatle"));
	renderSelectables.push_back(testArmy);
	Army* testArmy2 = new Army(sf::Vector2i(map.test2.first, map.test2.second), map, data.Textures().getTexture("TokenLion"));
	renderSelectables.push_back(testArmy2);

	mapOverlay world;
	world.setTileSet(data.Textures().getTileSet("biomes"));
	world.setType(0);
	addToLayer(world, 0);

	increaseNumberOfLayers();
	mapOverlay riverOverlay;
	riverOverlay.setTileSet(data.Textures().getTileSet("rivers"));
	riverOverlay.setType(1);
	addToLayer(riverOverlay, 1);


	increaseNumberOfLayers();

	for (int i = 0; i < renderSelectables.size(); i++)
	{
		Log::newLog("renderowanie obiektu Selectable");
		addToLayer(renderSelectables[i], 2);
	}

	increaseNumberOfLayers();

	//addToLayer(map, 3);

	/*increaseNumberOfLayers();
	mapOverlay citiesOverlay;
	citiesOverlay.setTileSet(data.Textures().getTileSet("cities"));
	citiesOverlay.setType(3);
	addToLayer(citiesOverlay, 3);*/

	int x = 0, y = 0;

	while (theGame.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		//std::cerr << 1 / deltaTime << "\n";
		while (theGame.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				theGame.close();
				break;
			}
			case sf::Event::Resized:
			{
				refreshWindow();
				break;
			}
			}
		}
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta < 0)
			{
				data.Settings().increaseZoom(0.25f);
			}
			else if (event.mouseWheelScroll.delta > 0)
			{
				data.Settings().increaseZoom(-0.25f);
			}
			event.mouseWheelScroll.delta = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameScreen.move(-1000.0f * deltaTime * data.Settings().getZoom(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameScreen.move(0, 1000.0f * deltaTime * data.Settings().getZoom());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameScreen.move(0, -1000.0f * deltaTime * data.Settings().getZoom());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameScreen.move(1000.0f * deltaTime * data.Settings().getZoom(), 0);
		}
		//test sterowania
		if (event.type == sf::Event::MouseButtonReleased)
		{
			sf::Vector2f position = theGame.mapPixelToCoords(sf::Mouse::getPosition(theGame));
			x = int(position.x) / tileResolution;
			y = int(position.y) / tileResolution;
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (currentlySelectedObject != nullptr)
				{	
					Army* temp = (Army*)currentlySelectedObject;
					if (temp->move(sf::Vector2i(x, y), map))
					{
						map.getTile(temp->getPosition())->ereaseSelectable();
						temp->setPosition(sf::Vector2i(x, y));
						map.getTile(x, y)->addSelectable(temp);
					}
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (currentlySelectedObject != map.getTile(x, y)->getSelectable())
				{
					if (currentlySelectedObject != nullptr)
						currentlySelectedObject->onDeselect();
					currentlySelectedObject = map.getTile(x, y)->getSelectable();
					if (currentlySelectedObject != nullptr)
						currentlySelectedObject->onSelect();
				}
			}
		}
		//std::cout << currentlySelectedObject << std::endl;
		/*
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (!mouseClick)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i pixelCoords = sf::Mouse::getPosition(theGame);
					sf::Vector2f position = theGame.mapPixelToCoords(pixelCoords);

					x = int(position.x) / tileResolution;
					y = int(position.y) / tileResolution;

					mouseClick = true;
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (mouseClick)
				{
					std::cout << "Tile cords: " << x << ", " << y << '\n';
					if (x >= 0 && y >= 0 && x < getData().World().getMapSize() && y < getData().World().getMapSize())
					{
						std::cout << map.getTile(x, y)->getType()->getName() << '\n';
						if (map.getTile(x, y)->getArmy() != nullptr) std::cout << "Natrafiono na klikalny obiekt!\n";
						{
							if (currentlySelectedObject == nullptr) currentlySelectedObject = map.getTile(x, y)->getArmy();
						}
						if (currentlySelectedObject != nullptr)
						{
							Army* temp = (Army*)currentlySelectedObject;
							std::cout << temp->move(sf::Vector2i(x, y), map) << "\n";
							if (temp->move(sf::Vector2i(x, y), map))
							{
								temp->setPosition(sf::Vector2i(x, y));
								map.getTile(x, y)->setArmy(temp);
							}
						}
					}
					mouseClick = false;
				}
			}
		}*/
		theGame.clear();
		theGame.setView(getGameScreen());
		draw();
		theGame.display();
	}
}



