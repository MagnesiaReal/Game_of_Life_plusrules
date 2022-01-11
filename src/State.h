#pragma once

#include "Bottonus.h"
#include "TextBox.h"

class State
{
private:


protected:
	// Accedemos a la pila de Estados global // Esto para que todos los Estados pueden hacer push and pop //
	stack<State*>* Estadus;
	RenderWindow* Window;
	vector<Texture> textures;
	bool SiguePrecionado; // Despues del primer frame sigue precionado por lo que la tarea aun no Finaliza 
	bool YaTermine; // Estado Finalizado 
	Vector2f CursorusView; // The most important !!!!!!!!!!! &&&&&&&/&%&/$%&#$
	bool isfinishrender;
	//Funciones protegidas 
public:
	State(RenderWindow* Ventana, stack<State*>* Estadus);
	virtual ~State();

	const bool& getQuit() const;
	virtual bool isnotrender();
	virtual void CheckForQuit() = 0;
	virtual void EndState() = 0;
	virtual void MoveView(Vector2f movimiento) = 0;
	virtual void ZoomView(float fact) = 0;

	virtual void CursorPosition();
	virtual void update(const float& Delta) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};
