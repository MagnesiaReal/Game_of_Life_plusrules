#include "Bottonus.h"

Bottonus::Bottonus(float x, float y, float ancho, float altura, Font* t_letra, string text, Color idle, Color On, Color Click)
{
	this->shape.setPosition(x, y);
	this->shape.setSize(Vector2f(ancho, altura));
	this->shape.setFillColor(Color::White);

	this->t_letra = t_letra;
	this->texto.setFont(*this->t_letra);
	this->texto.setString(text);
	this->texto.setFillColor(Color::White);
	this->texto.setCharacterSize(30);
	this->texto.setPosition(x + ((ancho - this->texto.getLocalBounds().width) / 2), y + ((altura - this->texto.getLocalBounds().height) / 2));

	this->BotonIdle = idle;
	this->BotonOn = On;
	this->BotonClick = Click;
}

Bottonus::~Bottonus()
{
}

bool Bottonus::esPresionado() const
{
	return this->ispress;
}

void Bottonus::update(Vector2f cursorPosition)
{
	if (this->shape.getGlobalBounds().contains(cursorPosition)) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			shape.setFillColor(this->BotonClick);
			this->isreleased = true;
		}
		else if (this->isreleased) {
			this->ispress = true;
			this->isreleased = false;
		}
		else {
			shape.setFillColor(this->BotonOn);
			this->ispress = false;
		}
	}
	else {
		shape.setFillColor(this->BotonIdle);
		this->ispress = false;
		this->isreleased = false;
	}
}

void Bottonus::render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->texto);
}
