// ANAHI FELIX

#include <iostream>
#include <fstream>
#include <iomanip>
#include "listascomp.hpp"
#include "listasordc.hpp"
#include "rwstring.hpp"

using namespace std;

struct Registro {
    int id;
    string cliente;
    string producto;
    float valor;
};

struct Despacho {
    string cliente;
    int bulto;
    int valor;
};

const int dcliente = 12;
const int dproducto = 10;

fstream &operator >>(fstream &fs, Registro &r){
    fs.read (reinterpret_cast<char *>(&r.id), sizeof(r.id));
    r.cliente = readstring(fs, dcliente);
    r.producto = readstring(fs, dproducto);
    fs.read (reinterpret_cast<char *>(&r.valor), sizeof(r.valor));
    return fs;
}

ostream &operator << (ostream &os, Registro &r){
    os << r.id << "\t"  << setw(dcliente) <<  r.cliente << "\t" << setw(dproducto) << r.producto << "\t"   << r.valor;
    return os;
}

int crit (Registro a, Registro b){
    if (a.cliente == b.cliente) 
        return a.producto.compare(b.producto);
    else
        return a.cliente < b.cliente ? -1 : 1;
}

template<typename T>
void limpiarLista(Nodo<T> *&lista) {
    while (lista != nullptr) {
        pop(lista);
    }
}

void limpiarMemoria(Nodo<Registro> *&lista, Nodo<Registro> *&listaclts) {
    limpiarLista(lista);
    limpiarLista(listaclts);
}

int main () {
    int opc;
    int cliente;
    int prod;
    Registro datos;
    Registro clts;
    Despacho dcho;
    Nodo<Registro> *lista = nullptr;
    Nodo<Registro> *listaclts = nullptr;
    fstream arch;   

    do {
    cout << "INGRESE UNA OPCION" << endl;
    cout << "1: Leer Datos" << endl;
    cout << "2: Mostrar" << endl;
    cout << "3: Despachar" << endl;
    cout << "4: Salir" << endl;
    cin >> opc;

    switch (opc){
        case 1:
               arch.open("Datos.bin", ios::in | ios::binary);
                if(!arch) {
                    cout << "Error al abrir el archivo" << endl;
                    return -1;
                 }

                while(arch >> datos) {
                    cout << datos << endl;
                    clts.id = datos.id;
                    clts.cliente = datos.cliente;
                    clts.producto = datos.producto;
                    clts.valor = datos.valor;
                    listaclts = insertar_unico (clts, lista, crit); 
                }

                arch.close();
                break;

        case 2:
                cout <<"ID  Cliente     Producto      Valor "<<endl;
                cout <<"============================================"<<endl;                
                mostrar (listaclts);
                break;

        case 3:
                cout <<"Ingresar cliente: "<<endl;
                if (cin>>cliente){
                    cout << "Ingresar pedido: "<<endl;

                } else {
                    cout << "No se encuentra ese cliente"<<endl;
                }
                break;   

        case 4:
                limpiarMemoria(lista, listaclts);
                break; 

        default: 
                cout << "Opcion no valida" << endl;                         
    }
    } while (opc != 4);

    return 0;
}