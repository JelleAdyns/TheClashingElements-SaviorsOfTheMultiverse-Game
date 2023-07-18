#include "pch.h"
#include "Screen.h"
#include "BackGround.h"


Screen::Screen(const Point2f& bottomCenter, const std::string& backGroundFilePath)
{
	m_pBackGround = new BackGround{ bottomCenter, backGroundFilePath };
}

Screen::~Screen()
{
	delete m_pBackGround;
	m_pBackGround = nullptr;
}