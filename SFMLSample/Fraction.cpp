#include "pch.h"
#include "Fraction.h"

Fraction::Fraction(std::string path)
{
	std::fstream fractionData;
	std::string tempText;
	fractionData.open(path, std::ios::in | std::ios::out);

	if (!fractionData.good()) Log::newLog ("Nie uda�o si� za�adowa� pliku " + path);
	else
	{
		std::getline(fractionData, tempText);
		fractionName = tempText;
		std::getline(fractionData, tempText);
		fractionStyle = tempText;

		fractionData.close();
	}
}

std::string Fraction::getFractionName()
{
	return fractionName;
}

std::string Fraction::getFractionStyle()
{
	return fractionStyle;
}

void Fraction::setFractionName(std::string newName)
{
	fractionName = newName;
}

void Fraction::setFractionStyle(std::string newStyle)
{
	fractionStyle = newStyle;
}
