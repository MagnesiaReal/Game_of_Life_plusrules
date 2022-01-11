#include "Inicio.h"


void Inicio::initBottonus()
{
	this->Botones["Iniciar"] = new Bottonus(50, 640, 170, 50, &this->font, "Iniciar :)", Color(50, 50, 50, 255), Color(90, 90, 90, 255), Color(200, 200, 200, 255));
	this->Botones["Salir"] = new Bottonus(240, 640, 250, 50, &this->font, "Abandonar :(", Color(50, 50, 50, 255), Color(90, 90, 90, 255), Color(200, 200, 200, 255));
	this->Botones["Campo"] = new Bottonus(520, 640, 340, 50, &this->font, "Attraction Field", Color(255, 104, 40, 255), Color(255, 144, 80, 255), Color(255, 254, 190, 255));
	this->Botones["Normal"] = new Bottonus(50, 170+350, 150, 50, &this->font, "Normal", Color(50, 20, 20, 255), Color(90, 60, 60, 255), Color(200, 170, 170, 255));
	this->Botones["Random"] = new Bottonus(230, 170 + 350, 200, 50, &this->font, "Aleatorio", Color(50, 20, 20, 255), Color(90, 60, 60, 255), Color(200, 170, 170, 255));
	this->Botones["Select"] = new Bottonus(460, 170 + 350, 170, 50, &this->font, "Elejir", Color(50, 20, 20, 255), Color(90, 60, 60, 255), Color(200, 170, 170, 255));
}

void Inicio::initTextBox()
{
	this->Textos["Celulas"] = new TextBox(50, 50 + 350, &this->font, Color(50, 50, 20, 255), Color(90, 90, 60, 255), Color(200, 200, 170, 255), "No. Celulas:");
	this->Textos["Regla"] = new TextBox(50, 110 + 340, &this->font, Color(50, 50, 20, 255), Color(90, 90, 60, 255), Color(200, 200, 170, 255), "No. Relga [] [] [] []:");
	this->Textos["Rand"] = new TextBox(50, 240 + 340, &this->font, Color(50, 50, 20, 255), Color(90, 90, 60, 255), Color(200, 200, 170, 255), "Porcentaje:");
	// TEXTO ESPECIAL // FUNCIONES ESPECIALES PARA EL
}

void Inicio::initWindow()
{

	VideoMode VentanaRes(1920, 1080);
	string titulo = "JUEGO DE LA VIDA By Garrido Rojas Marco Antonio";
	unsigned framerate_limit = 120;
	Uint32 Stylus = Style::Default;
	bool Vsync = false;
	
	//------------------------------Dimensiones-NameGame-windowsmode-
	this->Ventana = new RenderWindow(VentanaRes, titulo, Stylus);
	this->Ventana->setFramerateLimit(framerate_limit);
	this->Ventana->setVerticalSyncEnabled(Vsync);
}

Inicio::Inicio()
{
	
	this->acaso = 0;
	this->mode = 1;
	this->initWindow();
	//Iniciando Bienvenida//
	this->font.loadFromFile("Gameplay.ttf");
	this->Indicaciones.setFont(font);
	this->Indicaciones.setString("JUEGO DE LA VIDA by Garrido Rojas Marco \nInstrucciones de uso:");
	this->Indicaciones.setLineSpacing(1.3);
	this->Indicaciones.setPosition(Vector2f(50, 20));
	this->Indicaciones2.setFont(font);
	this->Indicaciones2.setLineSpacing(1.5);
	this->Indicaciones2.setLetterSpacing(1.2);
	this->Indicaciones2.setCharacterSize(16);
	this->Indicaciones2.setString("@ Esc === regresar   @ Attraction Field :: Blue lines == linea saliente :: Red line == linea Entrante\n@ P == PAUSA (El juego normalmente inicia con PAUSA)\n@ La regla se escribe asi EJEMPLO: 2333 esto quiere decir que es de orden R(2,3,3,3)\n@ +,- === +Zoom, -Zoom\n@ Flechas === mover Automata Actual\n@ P == PAUSAR y REANUDAR\n@ LeftClick == Revivir Celula\n@ RightClick == Matar Celula\n@ F == Ver Campo de concentracion\n@ Z, X == Aumentar, Disminuir Velocidad");
	this->Indicaciones2.setPosition(Vector2f(50, 110));
	///////////////////////
	this->initBottonus();
	this->initTextBox();
}

Inicio::~Inicio()
{
}

void Inicio::EndApp() {
	puts("Simulacro Terminado xddd END APP");
	this->Ventana->close();
}

void Inicio::updateDelta()
{
	this->Delta = this->deltaclock.restart().asSeconds();
}

void PyGrafica1(bool* estoy) // FUNCION LOCAL
{
	system("python graficavar.py");
	*estoy = false;
	puts("Se elimino con exito");
}

void PyGrafica2(bool* estoy)
{
	system("python graficades.py");
	*estoy = false;
	puts("Se elimino con exito");
}

void Inicio::UpdateSFMLEvents()
{
	while (this->Ventana->pollEvent(this->Eventus)) {
		// Si se cierra la ventana se termina el programa
		if (this->Eventus.type == Event::Closed) {
			this->Ventana->close();
		}
		else if (this->Eventus.type == Event::TextEntered)
		{
			if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
				for (auto& it : this->Textos) {
					it.second->setClearText();
				}
			}
			else if (this->Eventus.text.unicode > 47 and this->Eventus.text.unicode < 58) {
				for (auto& it : this->Textos) {
					it.second->setTexto(this->Eventus.text.unicode);
					cout << this->Eventus.text.unicode << endl;
				}
			}
			
		}
		
	}
}


void Inicio::UpdateButonus()
{
	for (auto& it : this->Botones) {
		it.second->update(CursorusView);
	}
	
	if (this->Botones["Normal"]->esPresionado()) {
		this->mode = 1;
	}
	else if (this->Botones["Random"]->esPresionado()) {
		this->mode = 2;
	}
	else if (this->Botones["Campo"]->esPresionado() and stoi(this->Textos["Celulas"]->getStringText()) <= 5) {
		this->states.push(new AttractionField(this->Ventana, &this->states, this->Textos["Celulas"]->getStringText(), this->Textos["Regla"]->getStringText()));
	}
	else if (this->Botones["Select"]->esPresionado()) {
		this->mode = 3;
#if defined (WIN32) || defined (_WIN32) || defined (__WIN32) && !defined (__CYGWIN__)
		char namefile[100];
    // Abrir archivo desde el esplorador de archivos de Windows 
	  OPENFILENAME explorefile;
		ZeroMemory(&exporefile, sizeof(OPENFILENAME));
		exporefile.lStructSize = sizeof(OPENFILENAME);
		//exporefile.hwndOwner = nadaunu; // NO Necesario para salvar la compañia xd
		exporefile.lpstrFile = namefile;
		exporefile.lpstrFile[0] = '\0';
		exporefile.nMaxFile = 100;
		exporefile.lpstrFilter = "MagneReal\0*.MAGR\0";
		// Get Open File Name abre el explorador de archivos de windows para seleccionar un archivo
		GetOpenFileName(&exporefile);
		this->celmod3 = exporefile.lpstrFile;
#else
    FILE * exporefile = popen("zenity --file-selection", "r");
    char buffer[500];
    fgets(buffer,sizeof(buffer), exporefile);
    this->celmod3 = buffer;
    std::cout << this->celmod3 << std::endl;

#endif
		cout << "Desde Inicio.cpp el nombre del archivo es:" << this->celmod3;
	}
	else if (this->Botones["Iniciar"]->esPresionado()) {
		this->Ventana->clear();
		this->Ventana->display();
		if(this->mode == 3){
			this->states.push(new CelularA(this->Ventana, &this->states, this->Textos["Celulas"]->getStringText(),this->Textos["Regla"]->getStringText(), this->Textos["Rand"]->getStringText(), this->mode, this->HD, this->celmod3));
		}
		else {
			this->states.push(new CelularA(this->Ventana, &this->states, this->Textos["Celulas"]->getStringText(), this->Textos["Regla"]->getStringText(), this->Textos["Rand"]->getStringText(), this->mode, this->HD));
		}
		cout << (string)this->Textos["Regla"]->getStringText();
		cout << (string)this->Textos["Celulas"]->getStringText();
	}
	else if (this->Botones["Salir"]->esPresionado()) {
		this->Ventana->close();
	}
	
}

void Inicio::UpdateTextBox()
{
	for (auto& it : this->Textos) {
		if (it.first != "Rand" && (this->mode == 1 || this->mode == 3)) {
			it.second->update(CursorusView);
		}
		else if (this->mode == 2) {
			it.second->update(CursorusView);
		}
	}
}

void Inicio::LockCursorPos()
{
	CursorusView = this->Ventana->mapPixelToCoords(Mouse::getPosition(*this->Ventana));
}
// Como es un programa compuesto unicamente de 2 States y no de N states se Geneneran 2 IF's; uno para el state principal y otro para el segundo State
void Inicio::update()
{
	this->LockCursorPos();// Posicion del Mouse
	
	if (this->states.empty()) { // Funciones para el State principal
	  this->UpdateSFMLEvents(); // Se actualiza para todo State Eventos de cualquier tipo programado	
		this->UpdateButonus(); // Se acutalizan los botones, se verifica si hubo evento o no
		this->UpdateTextBox(); // Se actualizan las cajas de texto , se verifica si hubo evento o no
	}
	if (!this->states.empty()) { // Update Segundo State
		this->states.top()->update(this->Delta); // update delta o mas bien Fps (1/Delta)
		if (this->states.top()->getQuit()) {// Si estado ya no exite regresa al menu principal
			this->states.top()->EndState(); // borra estado  de la fas de la tierra	
			delete this->states.top();// deletea el estado dinamico
			this->states.pop(); // resetea la pila o mas bien elimina elemento de la pila
		}
	}
}

void Inicio::renderTextBox()
{
	for (auto& it : this->Textos) {
		if (it.first != "Rand" && (this->mode == 1 || this->mode == 3)) {
			it.second->render(this->Ventana);
		}
		else if (this->mode == 2) {
			it.second->render(this->Ventana);
		} 
	}
}

void Inicio::renderBotonus()
{
	for (auto& it : this->Botones) {
		it.second->render(this->Ventana);
	}
}

void Inicio::render()
{
	
	if (this->states.empty()) { // Funciones para State principal
		this->Ventana->clear(); // Se limpia para todo State
		// renderizando los botones
		this->Ventana->draw(this->Indicaciones);
		this->Ventana->draw(this->Indicaciones2);
		this->renderBotonus();
		this->renderTextBox();
		this->Ventana->display();// Funcion Display
	}
	if (!this->states.empty()) { // Funciones Para State secundario
		this->states.top()->render(this->Ventana);
	}
	 
}

void Inicio::run() // Loop de la aplicacion , se ejecuta infinitamente.
{
	while (this->Ventana->isOpen()) {
		this->updateDelta();
		this->update();
		this->render();
	}
}
