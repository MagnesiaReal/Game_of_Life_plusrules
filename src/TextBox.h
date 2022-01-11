#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <sstream>

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

enum estadosTexto {
	TEXTIDLE = 0,
	TEXTON,
	TEXTCLICK
};

class TextBox
{
private:
	RectangleShape shape;
	Font* t_letra;

	string textorus;
	Text texto, texto2;

	Color TextIdle;
	Color TextOn;
	Color TextClick;
	bool ispressed;
	bool isWrite;

	// Varaibles especiales

public:
	TextBox(float x, float y, Font* t_letra, Color idle, Color On, Color Click, String Texttype, float factor=1);
	virtual ~TextBox();
	void setTexto(String textor);
	void setClearText();
	//Regresa primer Texto A y Segundo Texto B xd (FUNCIONES ESPECIALES DE TEXTO)
	string SecretA();
	void SecretB(string lul);
	/////////////////////////////////////////////////////////////////////////////
	bool esPresionado() const;
	string getStringText() const;
	void update(Vector2f cursorPosition);
	void render(RenderTarget* target);
};

