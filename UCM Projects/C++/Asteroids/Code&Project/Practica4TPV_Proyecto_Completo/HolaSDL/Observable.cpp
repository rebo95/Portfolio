#include "Observable.h"



Observable::Observable() : observers_()
{
}


Observable::~Observable()
{
}

void Observable::send(Message* msg) {
	//para que env�e los mensajes, el que hace el send, tiene que tener en su lista de observers todos aquellos que van a recibir el mensaje
	for (Observer* o : observers_) {
		o->receive(msg);
		// nosotros estamos metiendo cada uno de los objetos dentro de una lista de observers, de esta manera, cuando se mande un mensaje se llamara al recieve de todos los objetos que se encuentren dentro de esa lista de observers 
		// supongo que todos aquellos objetos que est�n activados se refiere a que est�n dentro del array de observers, pues son los que van a recibirlos mensajes enviados por el m�todo send
		//al llamar al m�todo send , estamos haciendo que un mensaje determinado entre en el m�todo recieve de todos los observers ue est�n dentro de la lista de 
		//observers, de esta manera desde cada m�todo recieve de cada uno de los objetos se ejecutar�.
	}
}

void Observable::registerObserver(Observer* o) {
	observers_.push_back(o);
}

void Observable:: removeObserver(Observer* o){

	delete o;
	vector<Observer*> ::iterator it = observers_.begin();
	while (it != observers_.end()) {
		if ((*it) ==nullptr) {
			delete (*it);
			it = observers_.erase(it);
		}
		else ++it;
	}
}
