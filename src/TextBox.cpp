#include "TextBox.h"

TextBox::TextBox(float x, float y, Font* t_letra, Color idle, Color On, Color Click, String Texttype, float factor)
{

	this->t_letra = t_letra;
	this->texto.setFont(*this->t_letra);
	this->texto.setString(Texttype);
	this->texto.setFillColor(Color::White);
	this->texto.setCharacterSize(25);
	this->texto.setPosition(x + 10, y + 10);

	this->texto2.setFont(*this->t_letra);
	this->texto2.setString("");
	this->texto2.setFillColor(Color::White);
	this->texto2.setCharacterSize(25);
	this->texto2.setPosition(x + this->texto.getLocalBounds().width + 20, y + 10);

	this->shape.setPosition(x, y);
	this->shape.setSize(Vector2f(this->texto.getLocalBounds().width + 200*factor , this->texto.getLocalBounds().height + 20));
	this->shape.setFillColor(idle);

	this->TextIdle = idle;
	this->TextOn = On;
	this->TextClick = Click;
}

TextBox::~TextBox()
{
}

void TextBox::setTexto(String textor)
{
	if (this->isWrite) {
		this->textorus += textor;
		this->texto2.setString(this->textorus);
	}
}

void TextBox::setClearText()
{
	if (this->isWrite) {
		if (!this->textorus.empty())
			this->textorus.pop_back();
		this->texto2.setString(this->textorus);
	}
}

string TextBox::SecretA()
{
	return this->texto.getString();
}

void TextBox::SecretB(string lul)
{
	this->texto.setString(lul);
}


bool TextBox::esPresionado() const
{
	return this->isWrite;
}

string TextBox::getStringText() const
{
	return this->texto2.getString();
}

void TextBox::update(Vector2f cursorPosition)
{
	if (this->shape.getGlobalBounds().contains(cursorPosition)) {
		if (this->isWrite == true) {
			shape.setFillColor(this->TextOn);
		}
		else if (Mouse::isButtonPressed(Mouse::Left)) {
			shape.setFillColor(this->TextClick);
			this->ispressed = true;
		}
		else if (this->ispressed == true) {
			this->isWrite = true;
		}
		else {
			shape.setFillColor(this->TextOn);
		}
	}
	else {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			shape.setFillColor(this->TextIdle);
			this->isWrite = false;
			this->ispressed = false;
		}
		if (this->isWrite == true) {
			shape.setFillColor(this->TextOn);	
		}
		else {
			shape.setFillColor(this->TextIdle);
		}
		
	}
}

void TextBox::render(RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->texto);
	target->draw(this->texto2);
}


