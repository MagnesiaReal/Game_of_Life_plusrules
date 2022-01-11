#include "CelularA.h"


CelularA::CelularA(RenderWindow* Ventana, stack<State*>* Estadus, string automatas, string regla, string pocento, int mode, bool Calidad, string arch) : State(Ventana, Estadus)
{
	this->Veltime = 0;
	this->veloz = 0.1f;
	this->xcur = -1;
	this->ycur = -1;
	this ->pausepre = false;
	this->PAUSAxd = true;
	this->Window->clear(); // Limpiando Ventana por si acaso
	
	//Si ya existen simplemente no los crea
	
	this->celus = stoi(automatas);
	this->imagebg.setSize(Vector2f(this->celus*10 , this->celus*10));
	// Consiguiendo numero por regla
	this->regla[0] = stoi(regla)/1000;
	this->regla[1] = (stoi(regla)%1000)/100;
	this->regla[2] = (stoi(regla)%100)/10;
	this->regla[3] = (stoi(regla)%10);


	//Semilla para el RANDOM RANDOM
	srand(time(NULL));
	//Estableciendo una vista optima
	this->mirar = View(FloatRect(this->celus * 5 - (1980 * this->celus * 5 / 1080), 0, 1980 * this->celus * 10 / 1080, this->celus * 10));
	// Arreglo de pixeles dinamico para mostrar en pantalla
	this->pixeles = new Uint8[this->celus * this->celus * 4];


	// Matriz dinamica // Estableciendo sus filas
	this->MatrixReal = new bool* [stoi(automatas)];
	this->MatrixAux = new bool* [stoi(automatas)];
	// Matriz dinamica // Estableciendo sus columnas o celdas por fila
	for (int i = 0; i < stoi(automatas); i++) {
		this->MatrixReal[i] = new bool[stoi(automatas)];
		this->MatrixAux[i] = new bool[stoi(automatas)];
	}
	// Inicializando matriz en Falso (0)
	for (int i = 0; i < this->celus; i++)
		for (int j = 0; j < this->celus; j++) {
			this->MatrixReal[j][i] = false;
			this->MatrixAux[j][i] = false;
		}

	//Porcentaje De 1 que se desea obtener, en caso de que se haya elejido la opcion ALEATORIO
	if (pocento != "" and mode == 2) {
		this->porcento = stoi(pocento);
		if (this->porcento <= 100 and this->porcento >= 0) {
			for (int i = 0; i < (this->porcento * this->celus * this->celus)/ 100;) {
				int jr = rand() % this->celus;
				int jir = rand() % this->celus;
				if (this->MatrixReal[jr][jir] == false) {
					this->MatrixReal[jr][jir] = true;
					i++;
				}
			}
		}


	} // Cadena de unos que se desean obtener segun la posicion, en caso de que se haya elegido SELECCIONAR
	else if (mode == 3) {
		cout << "Llenando matriz con el archivo: " << arch << endl;
		this->thirdmode.open(arch.c_str()); // abrimos el archivo que se selecciono en el explorador con anterioridad
		for (int i = 0; i < this->celus; i++) {
			for (int j = 0; j < this->celus; j++) {
				if (this->thirdmode.good())
					this->thirdmode >> this->MatrixReal[j][i];
				else
					break;
			}
		}
		cout << "Matrix llenada con eixtaso \n";

	}
}

CelularA::~CelularA()
{
	//Destruyendo todo alv
	this->mirar = View(FloatRect(0, 0, 1920, 1080)); // Estableciendo vista por Default	
	this->Window->setView(this->mirar); // Renderizando vista por default

	delete this->pixeles; // Borrando arreglo de pixeles
	for (int i = 0; i < this->celus; i++) { // Deleteando matriz
		delete this->MatrixReal[i];
	}
	delete this->MatrixReal; // Delete this papu
}


void CelularA::CheckForQuit()
{
}

void CelularA::EndState()
{
	//Funciones prueba Desactivada
  printf("Funcion EndState desactivada\n");
}

void CelularA::rndtlnperFPS()
{
	int ird = 0;
	for (int i = 0; i < this->celus; i++) {
		for (int j = 0; j < this->celus; j++) {
			if (this->MatrixReal[j][i]) {
				this->pixeles[ird] = 255 - (j * 255 / this->celus); //red
				this->pixeles[ird + 1] = 255 - (i * 255 / this->celus); //green
				this->pixeles[ird + 2] = j * 255 / this->celus; //blue
				this->pixeles[ird + 3] = 255; //alpha
			}
			else {
				this->pixeles[ird] = 0; //red
				this->pixeles[ird + 1] = 0; //green
				this->pixeles[ird + 2] = 0; //blue
				this->pixeles[ird + 3] = 255; //alpha
			}
			ird += 4;
		}
	}
	this->AutomataImg.create(this->celus, this->celus);
	this->AutomataImg.update(this->pixeles);
	this->imagebg.setTexture(&this->AutomataImg);
	this->Window->draw(this->imagebg);
}

void CelularA::checkPosReg()
{	// Toma de deciciones
	for (int i = 0; i < this->celus; i++) {
		for (int j = 0; j < this->celus; j++) {
			int vecindario = 0;
			// Si esta en la misma fila
			if (j > 0) {
				if (this->MatrixReal[j - 1][i]) vecindario++;
			}else
				if (this->MatrixReal[this->celus - 1][i]) vecindario++;

			if (j < this->celus - 1) {
				if (this->MatrixReal[j + 1][i]) vecindario++;
			}else
				if (this->MatrixReal[0][i]) vecindario++;

			// Si existe la fila anterior
			if (i > 0) {
				if (this->MatrixReal[j][i - 1]) vecindario++;
				if (j > 0) {
					if (this->MatrixReal[j - 1][i - 1]) vecindario++;
				}
				else {
					if (this->MatrixReal[this->celus - 1][i - 1]) vecindario++;
				}

				if (j < this->celus - 1) {
					if (this->MatrixReal[j + 1][i - 1]) vecindario++;
				}
				else {
					if (this->MatrixReal[0][i - 1]) vecindario++;
				}
			}
			else {
				if (this->MatrixReal[j][this->celus - 1]) vecindario++;
				if (j > 0) {
					if (this->MatrixReal[j - 1][this->celus - 1]) vecindario++;
				}
				else {
					if (this->MatrixReal[this->celus - 1][this->celus - 1]) vecindario++;
				}

				if (j < this->celus - 1) {
					if (this->MatrixReal[j + 1][this->celus - 1]) vecindario++;
				}
				else {
					if (this->MatrixReal[0][this->celus - 1]) vecindario++;
				}
			}
			// Si existe la siguiente fila
			if (i < this->celus - 1) {
				if (this->MatrixReal[j][i + 1]) vecindario++;

				if (j > 0) {
					if (this->MatrixReal[j - 1][i + 1]) vecindario++;
				}
				else {
					if (this->MatrixReal[this->celus - 1][i + 1]) vecindario++;
				}

				if (j < this->celus - 1) {
					if (this->MatrixReal[j + 1][i + 1]) vecindario++;
				}
				else {
					if (this->MatrixReal[0][i + 1]) vecindario++;
				}
			}
			else {
				if (this->MatrixReal[j][0]) vecindario++;

				if (j > 0) {
					if (this->MatrixReal[j - 1][0]) vecindario++;
				}
				else {
					if (this->MatrixReal[this->celus - 1][0]) vecindario++;
				}

				if (j < this->celus - 1) {
					if (this->MatrixReal[j + 1][0]) vecindario++;
				}
				else {
					if (this->MatrixReal[0][0]) vecindario++;
				}
			}


			// SI la celula esta viva hace esto SEGUN LA REGLA QUE SE LE HAYA INTRODUCIDO en caso de LIFE GAME R(2333)
			if (this->MatrixReal[j][i]) {
				if (vecindario >= this->regla[0] and vecindario <= this->regla[1]) {
					this->MatrixAux[j][i] = true;
				}
				else
					this->MatrixAux[j][i] = false;
			}
			else {
				if (vecindario >= this->regla[2] and vecindario <= this->regla[3]) {
					this->MatrixAux[j][i] = true;
				}
				else
					this->MatrixAux[j][i] = false;
			}
		}
	}

	// La matriz de la tal generacion se cambia a la siguiente generacion 
	for (int i = 0; i < this->celus; i++) {
		for (int j = 0; j < this->celus; j++) {
			this->MatrixReal[j][i] = this->MatrixAux[j][i];
			this->MatrixAux[j][i] = false;
		}
	}
}

void CelularA::MoveView(Vector2f move)
{
	this->mirar.move(move);
}

void CelularA::ZoomView(float fact)
{
	this->mirar.zoom(fact); // Facor de zoom con +  y -
}

void CelularA::CursorPosition()
{
	this->CursorusView = this->Window->mapPixelToCoords(Mouse::getPosition(*this->Window));
	cout << "X and Y: " << this->CursorusView.x << "\t" << this->CursorusView.y << endl;
}

// Funcion local sin usar
void PyGrafica1(bool* estoy, stringstream* Datos) // FUNCION LOCAL QUE GENERA UNA GRAFICA 1s que hay por GENERACION
{
	char este[100] = "python grafica.py ";
	strcat(este, Datos->str().c_str());
	puts(este);
	system(este);
	*estoy = false;
	puts("Se elimino con exito");
}

// Funcion que actualiza el State Celula
void CelularA::update(const float& Delta)
{
	
  while(this->Window->pollEvent(this->keyboard_mouse)) {
    if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
				this->ZoomView(1.2);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
				this->ZoomView(0.8);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				this->MoveView(Vector2f(Delta*-1000,0));
				cout << "Moviendo vista hacia la Izquierda" << endl;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				this->MoveView(Vector2f(Delta * 1000, 0));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
				this->MoveView(Vector2f(0, Delta * -1000));
			}
			else if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
				this->MoveView(Vector2f(0, Delta * 1000));
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				this->YaTermine = true;
			}
  }

	// Velocidad de evolucion
	if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
		if(this->veloz >=0)
			this->veloz -= 0.01f;
		else
			this->veloz = 0.01f;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
		if (this->veloz <= 5)
			this->veloz += 0.01f;
		else
			this->veloz = 4.99f;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::G)) {
#if defined (WIN32) || defined (_WIN32) || defined (__WIN32) && !defined (__CYGWIN__)
		char namefile[100];
		stringstream fileatosuve;
    OPENFILENAME sfilen;
		ZeroMemory(&sfilen, sizeof(OPENFILENAME));
		sfilen.lStructSize = sizeof(OPENFILENAME);
		//sfilen.hwndOwner = nadaunu; // NO Necesario para salvar la compañia xd
		sfilen.lpstrFile = namefile;
		sfilen.lpstrFile[0] = '\0';
		sfilen.nMaxFile = 100;
		sfilen.lpstrFilter = "MagneReal\0*.MAGR\0";
		// Get Open File Name abre el explorador de archivos de windows para seleccionar un archivo
		GetSaveFileName(&sfilen);
		fileatosuve << sfilen.lpstrFile << ".magr";
    ofstream savefilex(fileatosuve.str().c_str());
    if (savefilex.is_open()) {
      for (int i = 0; i < this->celus; i++)
        for (int j = 0; j < this->celus; j++)
          savefilex << this->MatrixReal[j][i] << " ";
    }
    savefilex.close();
#else
    stringstream fileatosuve;
    FILE* pipe = popen("file=$(zenity --file-selection --save); file=${file}.magr; echo $file;", "r");
    if(pipe != NULL) {
      char buffer[500];
      fgets(buffer, sizeof(buffer), pipe);
      puts(buffer);
      fileatosuve << buffer;
      if(strcmp(buffer, ".magr") != 0) {
        ofstream savefilex(fileatosuve.str().c_str());
        if (savefilex.is_open()) {
          for (int i = 0; i < this->celus; i++)
            for (int j = 0; j < this->celus; j++)
              savefilex << this->MatrixReal[j][i] << " ";
        }
        savefilex.close();
      } else {
        printf("no save\n");
      }
    } else {
      printf("Save nothing\n");
    }
#endif
    
	}
	
	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		this->CursorPosition();
		if (this->xcur != (int)this->CursorusView.x / 10 or this->ycur != (int)this->CursorusView.y / 10) {
			cout << "Ya precione el click del Mouse \n";
			this->xcur = this->CursorusView.x / 10;
			this->ycur = this->CursorusView.y / 10;
			if (this->xcur >= 0 and this->ycur >= 0 and this->xcur <= this->celus - 1 and this->ycur <= this->celus - 1) {
				this->MatrixReal[this->xcur][this->ycur] = true;
			}
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Button::Right)) {
		this->CursorPosition();
		if (this->xcur != (int)this->CursorusView.x / 10 or this->ycur != (int)this->CursorusView.y / 10) {
			cout << "Ya precione el click del Mouse \n";
			this->xcur = this->CursorusView.x / 10;
			this->ycur = this->CursorusView.y / 10;
			if (this->xcur >= 0 and this->ycur >= 0 and this->xcur <= this->celus - 1 and this->ycur <= this->celus - 1) {
				this->MatrixReal[this->xcur][this->ycur] = false;
			}
		}
	}
	else {
		this->xcur = -1;
		this->ycur = -1;
	}

	// PAUSA
	if (Keyboard::isKeyPressed(Keyboard::Key::P)) {
		if (!this->pausepre) {
			this->pausepre = true;
			if (!this->PAUSAxd) {
				this->PAUSAxd = true;
				
			}
			else {
				this->PAUSAxd = false;
				cout << "Pausa Desactivado" << endl;
			}
		}
	}
	else {
		this->pausepre = false;
	}

	this->Veltime += Delta;
	if (!this->PAUSAxd and this->Veltime > this->veloz) {
		this->Veltime = 0;
		this->checkPosReg();
	}

}
// Funcion que renderisa o muestra en pantalla lo que se ha obtenido
void CelularA::render(RenderTarget* target)
{
	// esta es la vistaque hay que seguir
	target->setView(this->mirar);
	this->Window->clear();
	this->rndtlnperFPS();
	this->Window->display();
	
}
