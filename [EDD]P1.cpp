#include<iostream>
#include<conio.h>
#include<cstring>
#include<string>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<sstream> 

using namespace::std;

struct nodo{
	char dato;
	int x,y,contador;
	string palabra;
	nodo* siguiente;
	nodo* atras;
}*primero, *ultimo;

struct pila1{
	string dato;
	string buscado;
	string reemplazado;
	string estado;
	string palabra;
	string posicion;
	pila1* siguiente;
}*primeroP1;

struct pila2{
	string dato;
	string buscado;
	string reemplazado;
	string estado;
	string palabra;
	string posicion;
	pila2* siguiente;
}*primeroP2;


void Menu();
void AgregarNodo(char,int,int,int);
void AgregarNodoInicio(char,int,int,int,string);
void AgregarNodoFinal(char,int,int,int,string);
void AgregarNodoPosicion(char,int,int,int,int,string);
void EliminarNodo(int,int);
void BuscarNodo(string,string);
void ModificarPalabra(int,int,string);
void EliminarBuscarReemplazar(int Ex,int Ey);
void MostrarLista1();
void MostrarLista2();
void AgregarTexto();
void EnviarDatos();
void Buscar();
void Tecla();
bool Vacia();
void TeclaDelete();
void EnviarPalabraReemplazar();
void MandaraEliminarBuscar(int,int,int,int,string);
void ModificarPosiciones(int,int,int);
void CambiarEditorTexto();

int TamanioListaDoble();
string texto;
int posx = 0;
int posy = 2;
int contadorNodos = 1;
int contPalabrasModificadas=0;
string retornarCadena(int);
bool RetornarUltima();
string BanderaRevertir;
string RevertirBuscar;
string RevertirReemplazar;

//Pra Pila 1
void InsertarPila1(string,string,string,string);
void MostrarPila1();
void BuscarPila1();
void ModificarPila1();
void EliminarPila1(string,string);

//Pra Pila 2
void InsertarPila2(string,string,string,string);
void MostrarPila2();
//void BuscarPila2();
//void ModificarPila2();
void EliminarPila2(string,string);


int main(){
/*	for (int i = 0; i < 2; i++) {
 	 cout << "digito : ";
 	 cin >> o;
 	 texto += "\n";
 	 texto += o;
	}  */
//	string str;	
	Menu();
//	Tecla();
	getch();
	return 0;
}

void Menu(){
	int opcion = 0;
	do{
		cout << "\n------Menu------\n" ;
		cout << "1)Crear Archivo \n" ;
		cout << "2)ver Lista \n" ;
		cout << "3)Buscar-modificar \n";
		cout << "4)salir \n";
		cout << "Opcion :";
		cin >> opcion;
		switch(opcion){
			case 1:
				EnviarDatos();
				cout << "\n";
				system("pause");			
				break;
			case 2:
				MostrarLista1();
				MostrarPila1();
				MostrarPila2();
				cout << "\n";
				system("pause");
				break;
			case 3:							    
				system("pause");
				break;				
		}
		system("cls");
	}while(opcion!=4);
	cout << "**fin programa**";
}

void AgregarTexto(){
	char texto[100];
	int longitud;
	cout << "Ingrese Texto : ";
	cin.getline(texto,100,'\n');
	
	longitud = strlen(texto);
	int cont = 0, i =0;
	
	
	while(i<longitud){
		cout << "-"<< texto[i] <<endl;
		i++;
		/*
		while(i<longitud && texto[i]==' '){
			i++;
		}
		
		if(cont<longitud){
			cont++;
		}
		
		while(i<longitud && texto[i]!=' '){
			i++;
		} */
	}
	
	cout << "\n la cantida es : " << i;
}

void EnviarDatos(){
	string agregarPalabra;
	system("cls");
	cout << " ^w(Buscar y Reemplazar)	^c(Reportes)	 s^(Guardar)    x^(Escape) \n" ;
	cout << "D-----------------------------------------------------------------------D\n" ;
	cout << texto;
	char key;
	int ascii;		
	while(1){
		key = getch();
		ascii = key;
	//	if(ascii > 0){
			if(ascii == 24){ //tecla ctrl+x
				system("cls");
				Menu();		
			}else if(ascii == 13){   //tecla enter
				cout << "\n";
				AgregarNodo('\n',posx,posy,contadorNodos);				
				contadorNodos++;							
				texto += "\n";								
				
				int cp = posx;
				cp = cp - agregarPalabra.size();
				for (int i = cp; i < posx; i++) {
					ModificarPalabra(i,posy,agregarPalabra);
				} 
				posy++;
				posx=0;	
				agregarPalabra= "";
				
			}else if(ascii == 8){ // tecla delete
				TeclaDelete();
				posx--;
				contadorNodos--;
				EnviarDatos();
			}else if(ascii == 23){ // tecla ctrl+w
			    BanderaRevertir = "falso";
				contPalabrasModificadas = 0;
				EnviarPalabraReemplazar();
				EnviarDatos();
			}else if(ascii == 32){ // tecla espacio
				cout << key;
				AgregarNodo(key,posx,posy,contadorNodos);
				posx++;
				contadorNodos++;
				texto += key;
				
				int cp = posx;
				cp = cp - agregarPalabra.size() -1;
				for (int i = cp; i < posx-1; i++) {
					ModificarPalabra(i,posy,agregarPalabra);
				}
				agregarPalabra= "";
			}else if(ascii == 26){ // tecla ctrl+z
				bool m = RetornarUltima();
				if(m==true){
					BanderaRevertir = "verdadero";
					BuscarNodo(RevertirBuscar,RevertirReemplazar);
					CambiarEditorTexto();
					BanderaRevertir = "falso";
					EnviarDatos();					
				}else{
					cout<<"\n\nfalse";
				}
			}else{
				cout << key;
				AgregarNodo(key,posx,posy,contadorNodos);
				posx++;
				contadorNodos++;
				texto += key;
				agregarPalabra+=key;
			}	
		//}		
											
	}	
	cout << "\n\n";
}

void EnviarPalabraReemplazar(){
	string pBuscar;
	string pReemplazar;
	string pRecibir;
	string tArreglo[4];
	cout << "\n\n\nBuscar Y Reemplazar: ";
	cin >> pRecibir;	
	string tpalabra;		
	int n = 0;			
	int tcont = pRecibir.size();
	char str[tcont];     
	char*coma;
	strcpy(str, pRecibir.c_str());	 
	coma = strtok(str,";");
	while(coma!=NULL){
		tArreglo[n] = coma;
		n++;
		coma = strtok(NULL,";");
	}
	pBuscar = tArreglo[0];
	pReemplazar = tArreglo[1];
	
	BuscarNodo(pBuscar,pReemplazar);
	CambiarEditorTexto();
	cout<<"\n** "<<contPalabrasModificadas<<" Palabras Afectadas"<<" **"<<"\n\n\n";
	system("pause");
}

void MandaraEliminarBuscar(int mx,int my,int tamanio, int cont,string pSustituir){
	contPalabrasModificadas++;
	int cSus = pSustituir.size();
//	cout << "\n palabra sust :"<<pSustituir<<endl;
	for (int i = mx; i <= mx+tamanio; i++) {
 	 	EliminarBuscarReemplazar(i,my);
	}
	
	int Desplegarx = mx;
	char temp[cSus];		
	strcpy(temp,pSustituir.c_str());
	int susti=0;
	int agregarC = cont;
	for (int i = cont; i < cont+cSus; i++) {		
		AgregarNodoPosicion(temp[susti],i,mx,my,agregarC,pSustituir);	
		mx++;
		susti++;
		agregarC++;	
	//	tamanioDes++;	
	}		
	ModificarPosiciones(Desplegarx,my,cont);	
}

void TeclaDelete(){
	nodo* actual = new nodo();
	actual = ultimo;
	char bus = actual -> dato;
	int a = actual -> x;
	int b = actual -> y;
	if(bus=='\n'){
		posy--;
		posx = a+1;
	} 	
	EliminarNodo(a,b);
		
 	string s = retornarCadena(a);   
 	string g = retornarCadena(b);  

	string zdato(1,bus);	
	InsertarPila1("Null","Null",zdato,s+","+g);
		
	CambiarEditorTexto();
/*
	int ma = 0;
	ma = texto.size();
	char temp[ma];
		
	strcpy(temp,texto.c_str());
	texto = "";
	for (int i = 0; i < ma-1; i++) {
 	 	texto+= temp[i];
	}	*/
}

void AgregarNodo(char n,int nx,int ny,int cont){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	
	if(primero == NULL){
		primero = nuevo;
		primero -> siguiente = NULL;
		primero -> atras = NULL;
		ultimo = primero;
	}else{
		ultimo -> siguiente = nuevo;
		nuevo -> siguiente = NULL;
		nuevo -> atras = ultimo;
		ultimo = nuevo;
	}
	
//	cout << "Nodo Ingresado \n";	
}

void AgregarNodoInicio(char n,int nx,int ny,int cont,string pagregar){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	nuevo -> palabra = pagregar;
	nuevo -> siguiente = NULL;
	nuevo -> atras = NULL;
	
	if(Vacia()){
		primero  = nuevo;
		ultimo = nuevo;
	}else {
		nuevo -> siguiente = primero;
		primero -> atras = nuevo;
		primero = nuevo;
	}
}

void AgregarNodoFinal(char n,int nx,int ny,int cont,string pagregar){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	nuevo -> palabra = pagregar;
	nuevo -> siguiente = NULL;
	nuevo -> atras = NULL;
	
	if(Vacia()){
		primero  = nuevo;
		ultimo = nuevo;
	}else {
		ultimo -> siguiente = nuevo;
		nuevo -> atras = ultimo;
		ultimo = nuevo;
	}
}

void AgregarNodoPosicion(char n,int npos,int nx,int ny,int cont,string pSustituir){
	nodo* nuevo = new nodo();
	nuevo -> dato = n;
	nuevo -> x = nx;
	nuevo -> y = ny;
	nuevo -> contador = cont;
	nuevo -> palabra = pSustituir;
	nuevo -> siguiente = NULL;
	nuevo -> atras = NULL;
	
	if(Vacia()){
		primero = nuevo;
		ultimo = nuevo;
	}else{
		if(npos == 1){
			AgregarNodoInicio(n,nx,ny,cont,pSustituir);
			
		}else if(npos== (TamanioListaDoble()+1)){
			AgregarNodoFinal(n,nx,ny,cont,pSustituir);
			
		}else if(npos> 1 && npos < (TamanioListaDoble()+1)){
			nodo* aux;
			aux = primero;
			for(int i=1 ; i<npos ; i++){
				aux = aux -> siguiente;
			}
			aux -> atras -> siguiente = nuevo;
			nuevo -> siguiente = aux;
			nuevo -> atras = aux -> atras;
			aux -> atras = nuevo;
		}else{
			cout << "Error, la posicion es invalida";
		}
	}
	
//	cout << "Nodo Ingresado \n";	
}

void EliminarNodo(int Ex, int Ey){
	nodo* actual = new nodo();
	actual = primero;
	nodo* anterior = new nodo();
	anterior = NULL;
	bool encontrado = false;
	
	if(primero != NULL){
		while(actual!=NULL && encontrado!=true){
			if(actual->x == Ex && actual->y == Ey){
				if(actual==primero){
					primero = primero->siguiente;
					primero->atras = NULL;
				}else if(actual==ultimo){
					anterior->siguiente = NULL;
					ultimo = anterior;					
				}else{
					anterior->siguiente = actual->siguiente;
					actual->siguiente->atras = anterior;
				}
			//	cout << "\n Nodo Eliminado";
				encontrado = true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}		
		if(!encontrado){
			cout << "\n No encontrado";
		}
	}else{
		cout << "\n Lista Vacia";
	}
}

void BuscarNodo(string nodoBuscado, string nodoSustituir){
	nodo* actual = new nodo();
	actual = primero;
	bool encontrado = false;
	int contBus = 0;
	int tamanio = nodoBuscado.size();
	if(primero != NULL){
		while(actual!=NULL){ //&& encontrado!=true){
			if(actual->palabra == nodoBuscado){
				contBus++;
				if(BanderaRevertir=="verdadero"){
					if(contBus==1){
					MandaraEliminarBuscar(actual->x,actual->y,tamanio-1,actual->contador,nodoSustituir);
					EliminarPila1(nodoSustituir,nodoBuscado);
					InsertarPila2(nodoSustituir,nodoBuscado,"Null","Null");																							
					}
				}else{
					if(contBus==1){
				//	cout << "dato: -" << actual->dato << " pos:"<<actual->x<<actual->y<<"nodo :"<<actual->contador<<endl;
					MandaraEliminarBuscar(actual->x,actual->y,tamanio-1,actual->contador,nodoSustituir);
					InsertarPila1(nodoBuscado,nodoSustituir,"Null","Null");																								
					}
				}								
				
				if (contBus==tamanio){
					contBus = 0;
				}					
				//encontrado = true;
			}
			actual = actual->siguiente;
		}		
	/*	if(!encontrado){
			cout << "\n No encontrado boolll";
		} */
	}else{
		cout << "\n Lista Vacia";
	}	
}

void EliminarBuscarReemplazar(int Ex,int Ey){
	nodo* actual = new nodo();
	actual = primero;
	nodo* anterior = new nodo();
	anterior = NULL;
	bool encontrado = false;
	
	if(primero != NULL){
		while(actual!=NULL && encontrado!=true){
			if(actual->x == Ex && actual->y == Ey){
				if(actual==primero){
					primero = primero->siguiente;
					primero->atras = NULL;
				}else if(actual==ultimo){
					anterior->siguiente = NULL;
					ultimo = anterior;					
				}else{
					anterior->siguiente = actual->siguiente;
					actual->siguiente->atras = anterior;
				}
			//	cout << "\n Nodo Eliminado";
				encontrado = true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}		
		if(!encontrado){
			cout << "\n No encontrado";
		}
	}else{
		cout << "\n Lista Vacia";
	}
}

void ModificarPalabra(int Modix, int Modiy,string nodoModificar){
	nodo* actual = new nodo();
	actual = primero;
	bool encontrado = false;
	if(primero != NULL){
		while(actual!=NULL && encontrado!=true){
			if(actual->x == Modix && actual->y == Modiy){
		//		cout << "\n dato: -" << actual->dato << " - encontrado \n";
				actual -> palabra = nodoModificar;
		//		cout << "\n modificado--";
				encontrado = true;
			}
			actual = actual->siguiente;
		}		
		if(!encontrado){
			cout << "\n No encontrado";
		}
	}else{
		cout << "\n Lista Vacia";
	} 
}

void ModificarPosiciones(int Modix, int Modiy,int Modic){
	nodo* actual = new nodo();
	actual = primero;
	bool encontrado = false;	
	int xSus = Modix;
	int cSus = Modic;
	if(primero != NULL){
		while(actual!=NULL){
			if(actual->y == Modiy && actual->x >= Modix){
				actual -> x = xSus;
				xSus++;							
			}
			if(actual->contador>=Modic){
				actual -> contador = cSus;
				cSus++;
			}
			actual = actual->siguiente;
		}		
	}else{
		cout << "\n Lista Vacia";
	} 
}

int TamanioListaDoble(){
	int cont = 0;
	nodo *actual;
	actual = primero;
	while(actual!=NULL){
		cont++;
		actual = actual -> siguiente;
	}
	return cont;
}

bool Vacia(){
	if(primero == NULL && ultimo == NULL){
		return true;		
	}else{
		return false;
	}
}

void Buscar(){
	char i;
	char j;
	cout << "\n\n buscar dato: " ;
	cin >> i ;
	cout << "\n\n Modificar dato: " ;
	cin >> j ;
//	ModificarNodo(i,j);
	cout << "\n\n fin buscar  ";  
}

void CambiarEditorTexto(){
	texto = "";
	nodo* actual = new nodo();
	actual = primero;
	if(primero!=NULL){
		while(actual!=NULL){
			texto +=actual -> dato;
			actual = actual -> siguiente;
		}
	}else{
		cout << "\n lista vacia \n";
	}
	cout << "\n";
}

void MostrarLista1(){
	cout << "\n Lista = \n";
	nodo* actual = new nodo();
	actual = primero;
	if(primero!=NULL){
		while(actual!=NULL){
			
			if(actual->dato == '\n'){
				cout <<actual->contador <<"-" << ' ' << "-(" << actual -> x<<","<<actual -> y<<")"<<"->"<<actual -> palabra<<"\n";
			}else{
				cout <<actual->contador <<"-" << actual -> dato << "-(" << actual -> x<<","<<actual -> y<<")"<<"->"<<actual -> palabra<<"\n";				
			}
			actual = actual -> siguiente;
		}
	}else{
		cout << "\n lista vacia \n";
	}
	cout << "\n";
}

void MostrarLista2(){
	nodo* actual = new nodo();
	actual = ultimo;
	if(primero!=NULL){
		while(actual!=NULL){
			cout << "\n" << actual -> dato;
			actual = actual -> atras;
		}
	}else{
		cout << "\n lista vacia \n";
	}
}

void Tecla(){
	char key;
	int ascii;
		
	cout << "presione una tecla:"<< endl ;
	
	while(1){
		key = getch();
		ascii = key;
		
		if(ascii > 0){
			if(ascii == 27){
			break;		
			}else if(ascii == 13){
			cout << "presiono la tecla -> " << "enter" << " codigo ascci es :" << ascii << endl;
			}else if(ascii == 72){
			cout << " arriba\n";
			}else if(ascii == 80){
			cout << "abajo\n";
			}else if(ascii == 75){
			cout << " izquierda\n";;
			}else if(ascii == 77){
			cout << " derecha\n";
			}
			else{
			cout << "presiono la tecla -> " << key << " codigo ascci es :" << ascii << endl;
			}
		}
											
	}
	
	cout << "Finalizo"<< endl ;
}

string retornarCadena(int entero){
	stringstream ss; 
	ss<<entero;  
 	string s;  
    ss>>s;    
	return s;
}


//Para las Pilas

void InsertarPila1(string pbuscado,string preemplazado,string ppalabra,string pposicion){
	pila1* nuevo = new pila1();
	nuevo -> buscado = pbuscado;
	nuevo -> reemplazado = preemplazado;
	nuevo -> estado = "No Revertido";
	nuevo -> palabra = ppalabra;
	nuevo -> posicion = pposicion;
	
	nuevo->siguiente = primeroP1;
	primeroP1 = nuevo;
		
}

void MostrarPila1(){
	pila1* actual = new pila1();
	actual = primeroP1;
	
	if(primeroP1!=NULL){
		while(actual!=NULL){
			cout<<endl<<"buscado : "<<actual->buscado;
			cout<<endl<<"reemplazado : "<<actual->reemplazado;
			cout<<endl<<"estado : "<<actual->estado;
			cout<<endl<<"palabra : "<<actual->palabra;
			cout<<endl<<"posicion : "<<actual->posicion;
			cout<<endl<<"        |";
			actual = actual->siguiente;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}
		
}

void BuscarPila1(){
	pila1* actual = new pila1();
	actual = primeroP1;
	string nodoBuscado = "";
	bool encontrado = false;
	cout<<"\nnodo buscar :";
	cin>> nodoBuscado;
	
	if(primeroP1!=NULL){
		while(actual!=NULL && encontrado != true){
			if(actual->dato==nodoBuscado){
				cout<<endl<<"dato :"<<nodoBuscado<<endl;
				encontrado=true;
			}
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout<<endl<<"pila no encontrada"<<endl;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}		
} 

void ModificarPila1(){
	pila1* actual = new pila1();
	actual = primeroP1;
	string nodoBuscado = "";
	bool encontrado = false;
	cout<<"\nnodo modificar :";
	cin>> nodoBuscado;
	
	if(primeroP1!=NULL){
		while(actual!=NULL && encontrado != true){
			if(actual->dato==nodoBuscado){
				cout<<endl<<"dato modificar : ";
				cin>> actual->dato;
				cout<<endl<<"modificado ";
				encontrado=true;
			}
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout<<endl<<"pila no encontrada"<<endl;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}
}

void EliminarPila1(string nodoBuscado,string nodoreemplazado){
	pila1* actual = new pila1();
	actual = primeroP1;
	pila1* anterior = new pila1();
	anterior = NULL;
    bool encontrado = false;
	if(primeroP1!=NULL){
		while(actual!=NULL && encontrado != true){
			if(actual->buscado==nodoBuscado && actual->reemplazado==nodoreemplazado){
				if(actual==primeroP1){
					primeroP1 = primeroP1->siguiente;
				}else{
					anterior->siguiente = actual->siguiente;
				}
				cout<<endl<<"eliminado";
				encontrado=true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout<<endl<<"pila no encontrada"<<endl;
		}
	}else{
		cout<<endl<<"la Pila esta vacia"<<endl;
	}
}

bool RetornarUltima(){
	bool mandar;
	pila1* actual = new pila1();
	actual = primeroP1;
	if(actual->buscado == "Null"){
		mandar = false;
	}else{
		mandar = true;
		RevertirBuscar = actual->reemplazado;
		RevertirReemplazar = actual->buscado;
	}
	return mandar; 
}


//Para la Pila 2
void InsertarPila2(string pbuscado,string preemplazado,string ppalabra,string pposicion){
	pila2* nuevo = new pila2();
	nuevo -> buscado = pbuscado;
	nuevo -> reemplazado = preemplazado;
	nuevo -> estado = "Revertido";
	nuevo -> palabra = ppalabra;
	nuevo -> posicion = pposicion;
	
	nuevo->siguiente = primeroP2;
	primeroP2 = nuevo;		
}
void MostrarPila2(){
	pila2* actual = new pila2();
	actual = primeroP2;
	
	if(primeroP2!=NULL){
		while(actual!=NULL){
			cout<<endl<<"buscado : "<<actual->buscado;
			cout<<endl<<"reemplazado : "<<actual->reemplazado;
			cout<<endl<<"estado : "<<actual->estado;
			cout<<endl<<"palabra : "<<actual->palabra;
			cout<<endl<<"posicion : "<<actual->posicion;
			cout<<endl<<"        |";
			actual = actual->siguiente;
		}
	}else{
		cout<<endl<<"la Pila 2 esta vacia"<<endl;
	}
		
}
