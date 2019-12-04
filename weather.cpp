#include "kdtree.cpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int, char*[]){
    int cant;
    Kdtree tree;
    vector<vector<int>> vec;
    tree.build();

    int fecha,anio,rain,maxt,mint,wind,humedad,presion,k;
    cout<<"Insertar fecha MMDD :";
    cin>>fecha;
    cout<<"Insertar año: ";
    cin>>anio;
    cout<<"insertar tiempo de lluvia";
    cin>>rain;
    cout<<"Insertar temperatura max: ";
    cin>>maxt;
    cout<<"Insertar temperatura min: ";
    cin>>mint;
    cout<<"Insertar velocidad de viento: ";
    cin>>wind;
    cout<<"Insertar humedad: ";
    cin>>humedad;
    cout<<"Ingresar presion: ";
    cin>>presion;
    cout<<"Ingrese valor refencial: ";
    cin>>k;
    cout<<tree.consulta(vector<int> {fecha,anio,0,rain,maxt,mint,wind,humedad,presion},k)<<endl;
}
