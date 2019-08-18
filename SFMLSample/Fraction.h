#pragma once
#ifndef FRACTION_H
#define FRACTION_H

#include "pch.h"

class Fraction
{
private:

	std::string fractionName; ///Nazwa frakcji
	std::string fractionStyle; ///Styl u�ywany przez frakcj�

public:

	Fraction(std::string path); ///Konstruktor - przyjmuje nazw� pliku frakcji, z kt�rego pobiera dane

	/// Gettery
	std::string getFractionName();
	std::string getFractionStyle();

	/// Settery
	void setFractionName(std::string newName);
	void setFractionStyle(std::string newStyle);
};

#endif /* FRACTION_H */

