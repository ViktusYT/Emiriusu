#pragma once
#ifndef LOG_H
#define LOG_H

#include "pch.h"

class Log
{
private:

	bool active; /// Przechowuje informacj� o tym, czy logi s� ju� aktywne
	std::string fileName; /// Nazwa logu
	std::string path; /// �cie�ka do plik�w log
	std::fstream logFile; /// zmeinna plikowa pliku log.log
	std::fstream logFileDev; /// zmienna plikowa w�a�ciwego pliku logu

	/// Funkcje singleton pattern
	Log();
	Log(const Log&);
	~Log();

	std::string getSystemDate(); /// Uzyskuje dat� systemow�
	void lineContents(std::string logContent); /// Dodaje wskazany �a�cuch do pliku log


public:
	
	static Log& newLog(std::string logContent); /// Dodaje nowy wpis do logu (funkcja wyowo�uj�ca klas� Singleton pattern)
};



#endif /* LOG_H */