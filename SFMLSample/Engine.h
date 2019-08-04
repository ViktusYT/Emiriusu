#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "pch.h"
#include "Object.h"
#include "Data.h"

class Layer : public Object
{
private:

	std::vector <Object*> objects; /// obiekty na warstwie
	std::string name;

public:

	Layer(std::vector <Object*> & objectsPreview); /// konstruktor (przyjmuje referencj� na wektor obiekt�w)
	Layer(std::vector <Object*> * objectsPreview); /// konstruktor (przyjmuje wska�nik na wektor obiekt�w)
	Layer() {}

	void draw(sf::RenderWindow & window) override; /// funkcja rysuje  warstw� na erkanie
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// funkcja rysuje  warstw� na erkanie (tylko mapa u�ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override {}
	void addObject(Object* newObject); /// dodaj obiekt do warstwy (przyjmuje wska�nik na obiekt)
	void addObject(Object& newObject); /// dodaj obieket do wartwy (przyjmuje refernecj� na obiekt)
	
	unsigned getSize() const; /// zwraca ilo�� obiekt�w
};

class Engine
{
private:

	std::fstream logFile; /// zmienna plikowa pliku Engine.log
	Engine(); /// konstruktor
	Engine(const Engine&); /// konstruktor
	~Engine(); /// destruktor
	sf::RenderWindow theGame; /// okno g�owne gry
	sf::RenderWindow& theGameR = theGame; /// referencja na okno g��wne gry
	sf::RenderWindow* theGameP = &theGame; /// wska�nik na okno g��wne gry
	sf::View gameScreen; /// obecnie wy�wietlana cz�� mapy
	sf::View& gameScreenR = gameScreen; /// referencja na obecnie wy�wietlan� cz�� mapy
	sf::Clock clock; /// zegar gry
	std::vector<Layer*> Layers; /// wszystkie warstwy
	sf::Event event; /// event okna

	Map* globalMap; /// Mapa globalna

	std::vector <std::vector <Object*>> renderObjects; /// strumie� ma�ych obiekt�w do renderowania
	void renderRenderObjects(); /// funkcja renderuje strumie� ma�e obiekty
	

	Data data; /// wi�kszo�� danych, u�ywanych przez program
	Selectable* currentlySelectedObject; /// obecnie wybrana jednostka

	bool exitGame; /// zmienna kt�ra przechowuje informacj� o tym czy gra jest w��czona (nieu�ywana)
	float deltaTime; /// czas kt�ry up�yn�� od poprzedniej klatki

	void refreshWindow(); /// funkcja od�wie�aj�ca ekran 
	void setGlobalMap(Map* newGlobalMap); /// setter mapy globalnej

public:

	static Engine & getInstance(); /// funkcja przekazuj�ca referencj� na instancj� silnika
	void* mapPointer;
	void draw() const; /// rysuje wszytkie warstwy po kolei
	void addLayer(Layer* newLayer); /// dodaje warstwe (przyjmuje wska�nik na warstw�)
	void addLayer(Layer& newLayer); /// dodaje warstw� (przyjmuje referencj� na warstw�)
	void addLayer(std::vector<Object*> & newLayer); /// dodaje warstw� (przyjmuje referncj� na wektor obiekt�w)
	void addToLayer(Object& newObject, unsigned index); /// dodaje obiekt do wybranej warstwy
	void addToLayer(Object* newObject, unsigned index); /// dodaje obiekt do wybranej warstwy
	void addToTopLayer(Object& newObject); /// dodaje obiekt do najwy�szej warstwy
	void addToTopLayer(Object* newObject); /// dodaje obiekt do najwy�szej warstwy
	void increaseNumberOfLayers(); /// zwi�ksza liczb� warst o jedn�
	void startGame(); /// uruchamia silnik

	///GameWindows access functions:
	sf::RenderWindow& getGameWindow(); /// funkcja zwraca referencj� na okno gry
	sf::View& getGameScreen(); /// funkcja zwraca referencj� na obecnie wy�wietlan� cz�� mapy
	
	unsigned getNumberOfLayers() const; /// zwraca ilo�� warstw

	Data& getData(); /// zwraca referencj� na klas� data
	Map* getGlobalMap(); /// zwraca map� globaln�

	void addToRenderObjects(Object* selToObj, unsigned selectLayer); /// dodaj obiekt klasy Object do strumienia ma�ych obiekt�w do renderowania

	///Engine Experimental Functions:
	/*void addToLayerTest(Object* newObject, unsigned index);*/

	///Engine Depracted Functions:
	/*void viktusTestuje (std::vector <Object*> newLayer); //work in progress*/
};

#endif /* ENGINE_H */