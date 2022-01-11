#pragma once

#include "CelularA.h"
#include "AttractionField.h"

class Inicio
{
private:
	RenderWindow* Ventana;
	Event Eventus;
	
	//
	string celmod3;
	Clock deltaclock;
	float Delta;
	bool HD;
	FILE* file;
	bool grav;
	
	bool grad;
	
	//Inicio es el estado de inicializacion de Datos
	map<string,Bottonus*> Botones;
	map<string, TextBox*> Textos;
	///// Bienvenida /////
	Font font;// tipo de letra
	Text Indicaciones;
	Text Indicaciones2;
	RectangleShape contenido;
	//////////////////////
	Vector2f CursorusView;
	String s_texto; // texto

	// mapa del unico estado que hay
	stack<State*> states;

	int mode;
	int acaso;

	void initBottonus();
	void initTextBox();
	void initWindow();

public:

	Inicio();
	virtual ~Inicio();

	void EndApp();

	void updateDelta();
	void UpdateSFMLEvents();
	void UpdateButonus();
	void UpdateTextBox();
	void LockCursorPos();
	void update();
	void renderTextBox();
	void renderBotonus();
	void render();
	void run();

};

