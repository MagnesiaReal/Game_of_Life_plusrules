#include "AttractionField.h"



bitset<25> AttractionField::initGeneracion(bitset<25> tal)
{
	this->cont_render = 0;
	int te = 0;
	bitset<25> mandar;
	for (int i = this->cells - 1; i >= 0; i--)
		for (int j = this->cells - 1; j >= 0; j--) {
			this->MatrixGen[j][i] = tal.test(te);
			te++;
		}

	for (int i = 0; i < this->cells; i++) {
		for (int j = 0; j < this->cells; j++) {
			int vecindario = 0;
			// Si esta en la misma fila
			if (j > 0) {
				if (this->MatrixGen[j - 1][i]) vecindario++;
			}
			else
				if (this->MatrixGen[this->cells - 1][i]) vecindario++;

			if (j < this->cells - 1) {
				if (this->MatrixGen[j + 1][i]) vecindario++;
			}
			else
				if (this->MatrixGen[0][i]) vecindario++;

			// Si existe la fila anterior
			if (i > 0) {
				if (this->MatrixGen[j][i - 1]) vecindario++;
				if (j > 0) {
					if (this->MatrixGen[j - 1][i - 1]) vecindario++;
				}
				else {
					if (this->MatrixGen[this->cells - 1][i - 1]) vecindario++;
				}

				if (j < this->cells - 1) {
					if (this->MatrixGen[j + 1][i - 1]) vecindario++;
				}
				else {
					if (this->MatrixGen[0][i - 1]) vecindario++;
				}
			}
			else {
				if (this->MatrixGen[j][this->cells - 1]) vecindario++;
				if (j > 0) {
					if (this->MatrixGen[j - 1][this->cells - 1]) vecindario++;
				}
				else {
					if (this->MatrixGen[this->cells - 1][this->cells - 1]) vecindario++;
				}

				if (j < this->cells - 1) {
					if (this->MatrixGen[j + 1][this->cells - 1]) vecindario++;
				}
				else {
					if (this->MatrixGen[0][this->cells - 1]) vecindario++;
				}
			}
			// Si existe la siguiente fila
			if (i < this->cells - 1) {
				if (this->MatrixGen[j][i + 1]) vecindario++;

				if (j > 0) {
					if (this->MatrixGen[j - 1][i + 1]) vecindario++;
				}
				else {
					if (this->MatrixGen[this->cells - 1][i + 1]) vecindario++;
				}

				if (j < this->cells - 1) {
					if (this->MatrixGen[j + 1][i + 1]) vecindario++;
				}
				else {
					if (this->MatrixGen[0][i + 1]) vecindario++;
				}
			}
			else {
				if (this->MatrixGen[j][0]) vecindario++;

				if (j > 0) {
					if (this->MatrixGen[j - 1][0]) vecindario++;
				}
				else {
					if (this->MatrixGen[this->cells - 1][0]) vecindario++;
				}

				if (j < this->cells - 1) {
					if (this->MatrixGen[j + 1][0]) vecindario++;
				}
				else {
					if (this->MatrixGen[0][0]) vecindario++;
				}
			}


			// SI la celula esta viva hace esto SEGUN LA REGLA QUE SE LE HAYA INTRODUCIDO en caso de LIFE GAME R(2333)
			if (this->MatrixGen[j][i]) {
				if (vecindario >= this->reglaw[0] and vecindario <= this->reglaw[1]) {
					this->MatrixSig[j][i] = true;
				}
				else
					this->MatrixSig[j][i] = false;
			}
			else {
				if (vecindario >= this->reglaw[2] and vecindario <= this->reglaw[3]) {
					this->MatrixSig[j][i] = true;
				}
				else
					this->MatrixSig[j][i] = false;
			}
		}
	}

	te = 0;
	for (int i = this->cells - 1; i >= 0; i--)
		for (int j = this->cells - 1; j >= 0; j--) {
			mandar.set(te, this->MatrixSig[j][i]);
			te++;
		}

	// La matriz de la tal generacion se cambia a la siguiente generacion 
	for (int i = 0; i < this->cells; i++) {
		for (int j = 0; j < this->cells; j++) {
			this->MatrixGen[j][i] = false;
			this->MatrixSig[j][i] = false;
		}
	}
	cout << tal << " -> " << mandar << endl;
 	return mandar;
}

AttractionField::AttractionField(RenderWindow* Ventana, stack<State*>* Estatus, string celus, string regla) : State(Ventana, Estatus)
{
	cout << "inicializando Basins of attraction" << endl;
	this->fontxd.loadFromFile("Gameplay.ttf");

	this->cells = stoi(celus);
	this->reglaw[0] = stoi(regla) / 1000;
	this->reglaw[1] = (stoi(regla) % 1000) / 100;
	this->reglaw[2] = (stoi(regla) % 100) / 10;
	this->reglaw[3] = (stoi(regla) % 10);

	// Matriz dinamica // Estableciendo sus filas
	this->MatrixGen = new bool* [stoi(celus)];
	this->MatrixSig = new bool* [stoi(celus)];
	// Matriz dinamica // Estableciendo sus columnas o celdas por fila
	for (int i = 0; i < stoi(celus); i++) {
		this->MatrixGen[i] = new bool[stoi(celus)];
		this->MatrixSig[i] = new bool[stoi(celus)];
	}
	// Inicializando matriz en Falso (0)
	for (int i = 0; i < this->cells; i++)
		for (int j = 0; j < this->cells; j++) {
			this->MatrixGen[j][i] = false;
			this->MatrixSig[j][i] = false;
		}


	this->Nodus = new nodo[(int)pow(2, this->cells * this->cells)];
	int max = 0;
	float flutu = this->cells * this->cells / 2.f;
	this->mirarc = View(FloatRect(-10, -10, 1980* (int)pow(2, flutu) * 30 / 1080, (int)pow(2, flutu)* 30));

	for (int i = 0; i < (int)pow(2, flutu) + 1; i++) {
		if (max >= pow(2, this->cells * this->cells)) {
			cout << "Se rompio por i\n";
			break;
		}
		for (int j = 0; j < (int)pow(2, flutu) + 1; j++) {
			//cout << "i and j hasta: " << i << "\t" << j << "\t" << (int)pow(2, flutu) + 1 << endl;
			if (max >= pow(2, this->cells * this->cells)) {
				cout << "Se rompio por j\n";
				break;
			}
			//cout << i * ((int)pow(2, flutu) + 1) + j << "\t" << max << endl;

			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].bits = i * ((int)pow(2, flutu) + 1) + j;
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].rectus.setSize(Vector2f(10, 10));
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].rectus.setOrigin(Vector2f(5, 5));
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].rectus.setFillColor(Color(210, 103, 18, 255));
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].meap = 1;
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].rectus.setPosition(Vector2f(j * 30, i * 30));
			// Posicion inicial de la linea 
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].line[0].position = Vector2f(j * 30, i * 30); 
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].line[0].color = Color(18, 204, 210, 255); // Color inicial
			
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].bitsap = this->initGeneracion(this->Nodus[i * ((int)pow(2, flutu) + 1) + j].bits);

			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].texta.setFont(this->fontxd);
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].texta.setCharacterSize(6);
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].texta.setString(to_string(i * ((int)pow(2, flutu) + 1) + j));
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].texta.setOrigin(Vector2f(5, 5));
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].texta.setPosition(j * 30 + ((10 - this->Nodus[i + j].texta.getLocalBounds().width) / 2), i * 30 + ((10 - this->Nodus[i + j].texta.getLocalBounds().height) / 2));
			max++;
			
		}
	}

	max = 0;
	flutu = this->cells * this->cells / 2.f;
	for (int i = 0; i < (int)pow(2, flutu) + 1; i++) {
		if (max >= pow(2, this->cells * this->cells)) {
			cout << "Se rompio por i\n";
			break;
		}
		for (int j = 0; j < (int)pow(2, flutu) + 1; j++) {
			
			if (max >= pow(2, this->cells * this->cells)) {
				cout << "Se rompio por j\n";
				break;
			}
			
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].line[1].position = this->Nodus[(int)this->Nodus[i * ((int)pow(2, flutu) + 1) + j].bitsap.to_ulong()].rectus.getPosition();
			this->Nodus[i * ((int)pow(2, flutu) + 1) + j].line[1].color = Color(235, 14, 10, 255);
			max++;

		}
	}


	cout << "Terminando inicializacion\n";
}

AttractionField::~AttractionField()
{
	//Destruyendo todo alv
	this->mirarc = View(FloatRect(0, 0, 1920, 1080)); // Estableciendo vista por Default	
	this->Window->setView(this->mirarc); // Renderizando vista por default
}

void AttractionField::CheckForQuit()
{
}

void AttractionField::EndState()
{
}

void AttractionField::MoveView(Vector2f movimiento)
{
	this->mirarc.move(movimiento);
	this->cont_render = 0;
}

void AttractionField::ZoomView(float fact)
{
	this->mirarc.zoom(fact);
	this->cont_render = 0;
}

void AttractionField::check_numbers()
{
	

}

void AttractionField::CursorPosition()
{
	this->CursorusView = this->Window->mapPixelToCoords(Mouse::getPosition(*this->Window));
	cout << "X and Y: " << this->CursorusView.x << "\t" << this->CursorusView.y << endl;
}

void AttractionField::update(const float& Delta)
{
	//this->CursorPosition();
	this->check_numbers();
}

void AttractionField::render(RenderTarget* target)
{
	if (this->cont_render != 3) {
		target->setView(this->mirarc);
		target->clear();
		for (int i = 0; i < pow(2, this->cells * this->cells); i++) {
			target->draw(this->Nodus[i].line, 2, Lines);
		}
		for (int i = 0; i < pow(2, this->cells * this->cells); i++) {
			target->draw(this->Nodus[i].rectus);
			target->draw(this->Nodus[i].texta);
		}
		this->cont_render ++;
	}
	this->Window->display();
}


