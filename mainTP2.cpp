// ANAHI FELIX
// REENTREGA

#include <iostream>
#include <fstream>
#include <iomanip>
#include "listascomp.hpp"

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
    os << "ID: "<< r.id << "\t"  << setw(dcliente) << "CLIENTE: " <<  r.cliente << "\t" << setw(dproducto) << "PRODUCTO: "<< r.producto << "\t" << "VALOR: "<< r.valor;
    return os;
}

ostream &operator << (ostream &os, Despacho &d){
    os << "BULTOS: "<< d.bulto << "\t"  << setw(dcliente) << "VALOR: " <<  d.valor;
    return os;
}

int crit (Registro a, Registro b){
    if (a.cliente == b.cliente) 
        return a.producto.compare(b.producto);
    else
        return a.cliente < b.cliente ? -1 : 1;
}

void limpiarMemoria(Nodo<Registro> *&lista, Nodo<Despacho> *&listadcho) {
    limpiarLista(lista);
    limpiarLista(listadcho);
}

Nodo<Registro> *extraerDcho (Registro aDcho, Nodo<Registro> *listaRegistro) {
    Nodo<Registro> *rEncontrados = nullptr;
    Nodo<Registro> *root = nullptr;
    bool fin = false;
    while (listaRegistro != nullptr && !fin) {
        Nodo<Registro> *despacho = extraer(aDcho, listaRegistro, crit);
        if (despacho != nullptr) {
            if (rEncontrados == nullptr) {
                rEncontrados = despacho;
                rEncontrados->sig = nullptr;
                root = rEncontrados;
            } else {
                rEncontrados->sig = despacho;
                rEncontrados = despacho;
                rEncontrados->sig = nullptr;
            }
        } else {
            fin = true;
        }
    }
    return root;
}

int main () {
    int opc = 0;
    int bultos = 0;
    float valor = 0;
    Registro datos;
    Registro aDcho;
    Despacho dcho;
    Nodo<Registro> *listaRegistro = nullptr;
    Nodo<Despacho> *listaDespacho = nullptr;
    Nodo<Registro> *aDespachar = nullptr;

    fstream arch;   

    while (opc != 4) {
    cout << "INGRESE UNA OPCION" << endl;
    cout << "1: Leer Datos" << endl;
    cout << "2: Mostrar" << endl;
    cout << "3: Despachar" << endl;
    cout << "4: Salir" << endl;
    cout << "-->";
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
                    insertar(datos, listaRegistro, crit); 
                }
                arch.close();
                break;

        case 2:
                cout <<"LISTA DE PEDIDOS ORDENADOS"<<endl;
                cout <<"============================================"<<endl;                
                mostrar (listaRegistro);

                cout <<"LISTA DE DESPACHOS"<<endl;
                cout <<"============================================"<<endl;    
                mostrar(listaDespacho);
                break;

        case 3:
                cout <<"Ingresar cliente: "<<endl;
                cin >> aDcho.cliente;
                cout <<"Ingresar despacho: "<<endl;
                cin >> aDcho.producto;
                aDespachar = extraerDcho(aDcho, listaRegistro);

                if (aDespachar != nullptr) {
                    mostrar(aDespachar);
                    // Al agregar el while, al elegir la opc 3 no continúa el ciclo de volver a elegir una opción
                    /*
                    while (listaRegistro != nullptr) {
                        valor += aDespachar->dato.valor;
                        bultos++;
                        aDespachar = aDespachar->sig;
                        }

                    dcho.cliente = aDcho.cliente;
                    dcho.bulto = bultos;
                    dcho.valor = valor;
                    agregar(dcho, listaDespacho);
                    */
                } else {
                        cout << "No hay pedidos pendientes del cliente " << aDcho.cliente << " de producto " << aDcho.producto << endl;
                }
                break; 
                }
            } 
    limpiarMemoria(listaRegistro, listaDespacho); 
    cin.clear();

}