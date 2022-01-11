#pragma once
#include "State.h"
#include <string>
#include <cstring>
#include <bitset>
#include <stdlib.h>
#include <time.h>


#include <fstream>

class CelularA :
	public State
{

private:
	bool gra1s;
	
	/////////// Nombres de Archivo /////////////
	
	float Veltime;
	////////////////////////////////////////////
	ifstream thirdmode;
	RectangleShape celulita;
	// Python se encargara de leer esta informacion.
	View mirar;
	//RectangleShape celulita; // Ocupado en Versiones anteriores
	// Lo podemos guardar como imagen //
	Texture AutomataImg;
	Texture LoadAuto;// carga de Textura
	RectangleShape imagebg;
	////////////////////////////////////
	//Pixel Array  // MOST EFFICIENTLY
	Uint8* pixeles;
	// PosMouseBefore
	Vector2f Fijar;
	//Datos para calcular Varianza y Desviacion Estandar
	bool pausepre;
	
	int celus;
	int regla[4];
	int porcento;
	int xcur, ycur;
	bool** MatrixReal;
	bool** MatrixAux;
	bitset<8>* Regla;
	bool PAUSAxd; // Bandera que Detiene o Reanuda el juego 
	float veloz;
  Event keyboard_mouse;

public:
	CelularA(RenderWindow* Ventana, stack<State*>* Estadus, string automatas = "0", string regla = "0", string pocento = "", int mode = 1, bool Calidad = false, string arch ="");
	~CelularA();
	void CheckForQuit();
	void EndState();
	void rndtlnperFPS();
	void checkPosReg();
	void MoveView(Vector2f movimiento);
	void ZoomView(float fact);

	void CursorPosition();
	void update(const float& Delta);
	void render(RenderTarget* target = NULL);
};

