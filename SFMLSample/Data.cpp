#include "pch.h"

Settings::Settings()
{
	setZoom(1.0f);
}

void Settings::setZoom(float newZoom)
{
	zoom = newZoom;
	zoom = std::max(1.0f, zoom);
	//Engine::getInstance().getGameScreen().zoom(zoom);
}

float Settings::getZoom()
{
	return zoom;
}

void Settings::increaseZoom(const float val)
{
	zoom = zoom + zoom*val;
	zoom = std::max(0.0f, zoom);
	Engine::getInstance().getGameScreen().zoom(1+val);
}

World::World()
{
	///Przypisanie tymczasowe
	mapSize = 100;
	landPercentage = 0.3147f;
	mountainsPercentage = 0.08f;
}

float World::getLandPercentage() 
{ 
	return landPercentage; 
} 

float World::getMountainsPercentage() 
{ 
	return mountainsPercentage; 
} 

int World::getMapSize() 
{ 
	return mapSize; 
}

Textures::Textures()
{
	loadTileSets();
	loadOtherTextures();
}

void Textures::loadOtherTextures()
{
	std::fstream textureInfoFile;
	const std::string textureInfoFileName = "textures/other.txt";
	std::string tempText, tempText2;

	textureInfoFile.open(textureInfoFileName, std::ios::in);
	if (!textureInfoFile.good()) Log::newLog("Nie uda�o si� odczyta� pliku: " + textureInfoFileName);
	else
	{
		while (!textureInfoFile.eof())
		{
			std::getline(textureInfoFile, tempText);
			std::getline(textureInfoFile, tempText2);

			sf::Texture* tempTexture = new sf::Texture;
			tempTexture->loadFromFile(tempText2);
			textures.insert(std::make_pair(tempText, tempTexture));
		}
	}
}

void Textures::loadTileSets()
{
	std::fstream textureInfoFile;
	const std::string textureInfoFileName = "textureInfo.txt";
	std::string tempText, tempText2;
	std::queue <std::string> fileQueue;

	textureInfoFile.open(textureInfoFileName, std::ios::in);

	if (!textureInfoFile.good()) Log::newLog("Nie uda�o si� odczyta� pliku: " + textureInfoFileName);
	else
	{
		while (!textureInfoFile.eof())
		{
			std::getline(textureInfoFile, tempText);
			std::getline(textureInfoFile, tempText2);

			fileQueue.push(tempText2);

			tileSets[tempText] = new sf::Texture;
		}

		textureInfoFile.close();

		std::map <std::string, sf::Texture*>::iterator it = tileSets.begin();

		while (!fileQueue.empty())
		{
			int x, y, vcount = 2, numberOfTextures = 0;
			bool varaints = false;
			sf::Texture tempTexture;

			tempText2 = fileQueue.front();
			fileQueue.pop();

			textureInfoFile.open(tempText2, std::ios::in);

			if (!textureInfoFile.good()) Log::newLog("Nie uda�o si� za�adowa� pliku " + tempText2);
			else
			{
				Log::newLog("Uda�o si� za�adowa� plik " + tempText2);
				sf::Texture* tileSet = it->second;

				std::getline(textureInfoFile, tempText);
				x = stringToInt(tempText);
				std::getline(textureInfoFile, tempText);
				y = stringToInt(tempText);

				tileSet->create(x * tileResolution, y * tileResolution);

				for (int i = 0; i < x * y + 1; i++)
				{
					std::getline(textureInfoFile, tempText);

					if (tempText == "variants")
					{
						varaints = true;
						numberOfTextures = 0;
					}

					if (!varaints)
					{
						if (!tempTexture.loadFromFile(tempText)) Log::newLog("Nie uda�o si� za�adowa� tekstury " + tempText);
						
						tileSet->update(tempTexture, tileResolution * numberOfTextures, 0);
						numberOfTextures++;
					}
					else if (tempText != "variants")
					{
						if (!tempTexture.loadFromFile(tempText)) Log::newLog ("Nie uda�o si� za�adowa� tekstury " + tempText);
						
						tileSet->update(tempTexture, tileResolution * numberOfTextures, tileResolution * (vcount - 1));

						if (vcount == y)
						{
							vcount = 2;
							numberOfTextures++;
						}
						else vcount++;
					}
				}
				it++;
				textureInfoFile.close();
			}
		}
	}
}

sf::Texture* Textures::getTileSet(std::string name)
{
	std::map <std::string, sf::Texture*>::iterator it = tileSets.find(name);
	if (it == tileSets.end()) throw "nie znaleziono zestawu tekstur: " + name;
	return it->second;
}

sf::Texture* Textures::getTexture(std::string name)
{
	std::map <std::string, sf::Texture*>::iterator it = textures.find(name);
	if (it == textures.end()) throw "nie znaleziono tekstury: " + name;
	return it->second;
}

sf::Texture* Textures::getFractionTexture(Fraction* fraction, std::string name)
{
	return getTexture(fraction->getFractionStyle() + "_" + name);
}

void Textures::clearTextures()
{
	textures.clear();
	tileSets.clear();
}

Data::Data()
{
	loadData();
	createTypes();
}

void Data::loadData()
{
	Log::newLog("Rozpoczynam tworzenie typ�w - pobieranie danych");

	std::fstream data;
	std::string temp;

	data.open("info.txt", std::ios::in);

	if (!data.good()) Log::newLog("Nie uda�o si� za�adowa� pliku info.txt");
	else
	{
		while (!data.eof())
		{
			std::getline(data, temp);

			loadSelectData(temp);
		}

		data.close();
	}
}

void Data::loadSelectData(std::string type)
{
	Log::newLog("Rozpoczynam tworzenie typ�w - pobieranie danych " + type);

	std::fstream fileData;
	std::string tempName, tempDirectory;

	std::map<std::string, std::string>* mapForType = new std::map<std::string, std::string>;

	fileData.open(type + "/info.txt", std::ios::in);

	if (!fileData.good()) Log::newLog("Nie uda�o si� za�adowa� pliku " + type + "/info.txt");
	else 
	{
		while (!fileData.eof())
		{
			std::getline(fileData, tempName);
			std::getline(fileData, tempDirectory);

			mapForType->emplace(std::make_pair(tempName, tempDirectory));
		}

		datas.emplace(type, *mapForType);
		delete mapForType;
		fileData.close();
	}
}

void Data::createTypes()
{
	Log::newLog("Tworz� typy");
	std::map <std::string, std::map<std::string, std::string>>::iterator itend = datas.end();
	for (std::map <std::string, std::map<std::string, std::string>>::iterator it = datas.begin(); it != itend; it++)
	{
		std::string type = it->first;
		std::map <std::string, std::string>* singleTypeMap = &it->second;

		Log::newLog("Tworzenie typu " + type);

		std::map <std::string, std::string>::iterator jtend = singleTypeMap->end();
		for (std::map <std::string, std::string>::iterator jt = singleTypeMap->begin(); jt != jtend; jt++)
		{
			std::string typeName = jt->first;
			std::string path = jt->second;

			if (type == "biomes")
			{
				Biome* tempType = new Biome(path);
				biomes.emplace(std::make_pair(typeName, tempType));
			}
			else if (type == "buildings")
			{
				Building* tempType = new Building(path);
				buildings.emplace(std::make_pair(typeName, tempType));
			}
			else if (type == "fractions")
			{
				Fraction* tempType = new Fraction(path);
				fractions.emplace(std::make_pair(typeName, tempType));
			}
			else if (type == "armies")
			{
				ArmyPrototype* tempType = new ArmyPrototype(path);
				armies.emplace(std::make_pair(typeName, tempType));
			}
		}
	}
}


Biome* Data::getBiome(std::string type)
{
	auto it = biomes.find(type);
	if (it == biomes.end()) throw "Nie znaleziono biomu o nazwie " + type;
	return it->second;
}

Building* Data::getBuilding(std::string type)
{
	auto it = buildings.find(type);
	if (it == buildings.end()) throw "Nie znaleziono budynku o nazwie " + type;
	return it->second;
}

Fraction* Data::getFraction(std::string type)
{
	auto it = fractions.find(type);
	if (it == fractions.end()) throw "Nie znaleziono frakcji o nazwie " + type;
	return it->second;
}

ArmyPrototype* Data::getArmyPrototype(std::string type)
{
	auto it = armies.find(type);
	if (it == armies.end()) throw "Nie mo�na znale�� prototypu armii o nazwie " + type;
	return it->second;
}

District* Data::getDistrict(BuildingInstance* buildingD)
{
	auto it = districtMap.find(buildingD);
	if (it == districtMap.end()) throw "Nie znaleziono dzielnicy dla budynku. B��d krytyczny dzielnic!";
	Log::newLog("Znaleziono dzielnic� dla budynku! To dzia�a!");
	return it->second;
}

City* Data::getCity(BuildingInstance* buildingC)
{
	auto it = citiesByBuildings.find(buildingC);
	if (it == citiesByBuildings.end()) throw "Nie znaleziono tego budynku w �adnym mie�cie! B��d krytyczny!";
	return it->second;
}

void Data::addPlayer(Player* newPlayer)
{
	players.push(newPlayer);
	playersMap.emplace(std::make_pair(newPlayer->getNickName(), newPlayer));
}

Player* Data::getPlayer(std::string name)
{
	auto it = playersMap.find(name);
	if (it == playersMap.end()) throw "nie ma gracza o nicku: " + name;
	return it->second;
}

bool Data::checkIfPlayer(std::string name)
{
	auto it = playersMap.find(name);
	if (it == playersMap.end()) return false;
	return true;
}

void Data::addToDisMap(BuildingInstance* b, District* d)
{
	districts.emplace(d);
	
	auto it = districtMap.find(b);
	if (it == districtMap.end()) districtMap.emplace(std::make_pair(b, d));
	else
	{
		it->second = d;
	}
}

void Data::addDistrict(BuildingInstance* buildingToDistrict)
{
	District* newDistrict = new District(buildingToDistrict);
	addToDisMap(buildingToDistrict, newDistrict);
	Log::newLog("Dodano dzielnic� do DisMap");
	newDistrict->addBuilding(buildingToDistrict);

	std::vector <BuildingInstance*> friends = buildingToDistrict->getFriends();
	std::set <BuildingInstance*> friendsExtended;

	for (int i = 0; i < friends.size(); i++)
	{
		try
		{
			District* tempPointer;
			if (!friends[i]->getLock()) tempPointer = getDistrict(friends[i]);
			else tempPointer = nullptr;
			std::set <BuildingInstance*> temp = tempPointer->exportData();
			friendsExtended.insert(temp.begin(), temp.end());
		}
		catch (std::string exception) { Log::newLog("Natrafiono na wyj�tek podczas tworzenia dzielnicy: " + exception); }
	}

	for (auto it = friendsExtended.begin(); it != friendsExtended.end(); it++)
	{
		newDistrict->addBuilding(*it);
		addToDisMap(*it, newDistrict);
	}

	garbageCollector();
}

int Data::getNumberOfDistricts()
{
	return districts.size();
}

void Data::garbageCollector()
{
	std::vector <District*> toEreaseItems;

	for (auto it : districts)
	{
		District* garbage = it;

		if (garbage->getNumberOfBuildings() == 0) toEreaseItems.push_back(it);
	}

	for (auto i : toEreaseItems)
	{
		districts.erase(i);
		delete i;
	}
}

void Data::reportBuildingInstance(BuildingInstance* buildingToCity, City* newCity)
{
	Log::newLog ("Zg�oszono budynek!");
	citiesByBuildings.emplace(std::make_pair(buildingToCity, newCity));
}

void Data::reportDestructionBuildingInstance(BuildingInstance* toDestroy)
{
	Log::newLog("Usuwam budynek");
	citiesByBuildings.erase(toDestroy);
}

void Data::refreshDistricts(Player* refreshPlayer)
{
	std::vector <BuildingInstance*> toEreaseItems;

	for (auto dm : districtMap)
	{
		if (dm.second->getOwner() == refreshPlayer) toEreaseItems.push_back(dm.first); 
	}

	for (auto i : toEreaseItems) districtMap.erase(i);

	toEreaseItems.clear();
	std::vector <District*> toEreaseItems2;

	for (auto d : districts)
	{
		if (d->getOwner() == refreshPlayer) toEreaseItems2.push_back(d);
	}

	for (auto i : toEreaseItems2)
	{
		districts.erase(i);
		delete i;
	}

	toEreaseItems2.clear();

	for (auto d : citiesByBuildings)
	{
		if (d.first->getOwner() == refreshPlayer) d.first->lock();
	}

	for (auto d : citiesByBuildings)
	{
		try
		{
			if (d.first->getOwner() == refreshPlayer)
			{
				d.first->unlock();
				d.first->addToDistrict();
			}
		}
		catch (std::string exception) { Log::newLog("Napotkano wyj�tek podczas od�wie�ania dzielnic: " + exception); }
	}
}