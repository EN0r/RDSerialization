#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

class Serialisor
{
protected:
	std::fstream stream;
public:

	bool openFile(std::string file);
	
	template<typename ExpectedReturn>
	ExpectedReturn findInFile(std::string KeyWord);
	
	std::string findInFileReverse(std::string data);
	
	bool writeLine(std::string Text);
	
	bool writeCharacter(std::string Text);

	template<typename ExpectedReturn>
	bool SerialiseClass(ExpectedReturn cClass);
	
	template<typename ExpectedReturn>
	ExpectedReturn DeSerialiseClassByID(int ID);
	
	std::string Separator = ":";
	
	static Serialisor* getInstance();
	
	~Serialisor()
	{
		stream.close();
		ZeroMemory(instance, NULL);
	}

private:
	Serialisor() { }
	static Serialisor* instance;
};

Serialisor* Serialisor::instance = nullptr;

Serialisor* Serialisor::getInstance()
{
	if (instance == NULL)
	{
		Serialisor* S = new Serialisor;
		return S;
	}
	return instance;
}

bool Serialisor::openFile(std::string file)
{
	if (!stream.is_open())
	{
		stream.open(file);
		if (stream.is_open())
			return true;
		return false;
	}
	return false;
}

bool Serialisor::writeLine(std::string Text)
{
	if (!stream.is_open())
		return false;
	// Push a string to the file
	this->stream << Text << "\n";
	return true;
}

bool Serialisor::writeCharacter(std::string Text)
{
	if (!stream.is_open())
		return false;
	// Push a string to the file
	this->stream << Text;
	return true;
}

template<typename ExpectedReturn>
ExpectedReturn Serialisor::findInFile(std::string data) // Look for data from file
{
	// check while it's open
	std::string storage;

	size_t Position= -1;
	size_t SentenceSize = -1;
	std::string storedCharacter;
	while (std::getline(this->stream, storage))
	{
		// Figure out to somehow loop through all words in file and check it on a dictionary class
		for (size_t i = 0; i < storage.length(); i++)
		{
			storedCharacter = storage[i];
			if (storedCharacter == Separator)
			{
				Position = i;
				SentenceSize = storage.length();
				if (storage.substr(0, Position) == data)
				{
					return storage.substr(Position + 1,SentenceSize);
				}
			}
		}
	}
	return "NULL";
}

std::string Serialisor::findInFileReverse(std::string data) // Look for data from file
{
	// check while it's open
	std::string storage;

	size_t Position = -1;
	size_t SentenceSize = -1;
	std::string storedCharacter;
	while (std::getline(this->stream, storage))
	{
		// Figure out to somehow loop through all words in file and check it on a dictionary class
		for (size_t i = 0; i < storage.length(); i++)
		{
			storedCharacter = storage[i];
			if (storedCharacter == Separator)
			{
				Position = i;
				SentenceSize = storage.length();
				if (storage.substr(Position + 1, storage.length()) == data)
				{
					return storage.substr(0,Position);
				}
			}
		}
	}
	return "NULL";
}


template<typename ExpectedReturn>
bool Serialisor::SerialiseClass(ExpectedReturn cClass)
{
	// if it does it correctly return true
	if (!stream.is_open())
		return false;
	writeCharacter(typeid(ExpectedReturn).name());
	writeLine("=");
	writeLine("{");
	std::string fLine;
	for (int i = 0; i < sizeof(cClass.DataTable)/ sizeof(cClass.DataTable[0]); i++)
	{
		fLine = cClass.DataTable[i] + Separator + cClass.DataMain[i];
		writeLine(fLine);
		if (i == sizeof(cClass.DataTable) / sizeof(cClass.DataTable[0]) - 1)
		{
			writeLine("}");
		}
	}
}

template<typename ExpectedReturn>
ExpectedReturn Serialisor::DeSerialiseClassByID(int ID)
{
	if (!stream.is_open())
		return NULL;
	std::string storedString = "ID";
	std::string s = findInFile<std::string>(storedString);
	std::string ln;
	if (storedString == "NULL")
		return NULL;
	while (std::getline(this->stream, ln))
	{
		if (ln == "}")
			break;
		if (storedString == findInFileReverse(std::to_string(ID)))
		{
			std::cout << "found" << "\n";
		}

	}
	// Goals: Create a new class and return it from the information stored in the data, Identify the object type eg. Struct/Class and make the new one apropiately
	
}