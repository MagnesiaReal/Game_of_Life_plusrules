#include "State.h"

State::State(RenderWindow* Ventana, stack<State*>* Estadus) {
	this->Window = Ventana;
	this->YaTermine = false;
	this->SiguePrecionado = false;
	this->Estadus = Estadus;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->YaTermine;
}

bool State::isnotrender()
{
	return this->isfinishrender;
}

void State::CursorPosition()
{
	CursorusView = this->Window->mapPixelToCoords(Mouse::getPosition(*this->Window));
}