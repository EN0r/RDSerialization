#pragma once
class Player
{
public:
	int ID = 1;
	std::string DataTable[4] = { "ScreenWidth","ScreenHeight","imageScaleHeight","imageScaleWidth" };
	std::string DataMain[sizeof(DataTable)] = { "1440","900","20","20" };
};