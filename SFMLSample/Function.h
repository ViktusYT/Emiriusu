#pragma once
#include "pch.h"

class Function
{
	Types retunedType;
public:
	Function();
	virtual ~Function();
	virtual void* Activate(std::vector<void*> data) = 0;
	Types getReturnedType() { return retunedType; }
	void setReturnedType(Types newReturnedType) { retunedType = newReturnedType; }
};

class Dijkstra : public Function
{
	void* Activate(std::vector<void*> data) override; /// pozycja armi(sf::Vector2i), ilo�� ruchu armii(float), tablica do danych(vector<vector<float>>), mapa(Map*)
};

