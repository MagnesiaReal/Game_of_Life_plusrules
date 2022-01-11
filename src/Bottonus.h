#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <sstream>

#if defined (WIN32) || defined (_WIN32) || defined (__WIN32) && !defined (__CYGWIN__)
#include <Windows.h>
#endif
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <map>

using namespace sf;
using namespace std;

enum estadosboton {
	BOTONIDLE = 0,
	BOTONON,
	BOTONCLICK
};
class Bottonus
{
private:
	RectangleShape shape;
	Font* t_letra;
	Text texto;
	Color BotonIdle;
	Color BotonOn;
	Color BotonClick;
	bool ispress;
	bool isreleased;

public:
	Bottonus(float x, float y, float ancho, float altura, Font* t_letra, string text, Color idle, Color On, Color Click);
	virtual ~Bottonus();

	// Funciones //
	bool esPresionado() const;

	void update(Vector2f cursorPosition);
	void render(RenderTarget* target);
};

