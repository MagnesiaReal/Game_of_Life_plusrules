#pragma once
#include "State.h"
#include <bitset>
#include <math.h>
class AttractionField : public State
{
private:
	
	Font fontxd;
	int cont_render;
	int cells;
	int reglaw[4];
	bitset<25>* bitlike;
	bool** MatrixGen;
	bool** MatrixSig;
	struct nodo {
		Text texta;
		RectangleShape rectus;
		Vertex line[2];
		bitset<25> bits;
		bitset<25> bitsap;
		int meap;
	} *Nodus;
	View mirarc;
	bitset<25> initGeneracion(bitset<25> tal);

public:

	AttractionField(RenderWindow* Ventana, stack<State*>* Estatus, string celus = "0", string regla ="0");
	~AttractionField();


	void CheckForQuit();
	void EndState();
	void MoveView(Vector2f movimiento);
	void ZoomView(float fact);

	void check_numbers();

	void CursorPosition();
	void update(const float& Delta);
	void render(RenderTarget* target = NULL);
};

