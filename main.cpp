#include <iostream>

using namespace std;

#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    string root = argv[1];
    ifstream archivoALeer;
    archivoALeer.open(root, ios::in);
    vector<string> clasesSinFormat;
    vector<string> clase;
    ofstream archivoAEscribir;

    while (!archivoALeer.eof())
    {
        string texto;
        getline(archivoALeer, texto);

        stringstream streamDeCadenaOrig(texto);

        string cadenaResultante;

        while (getline(streamDeCadenaOrig, cadenaResultante, ']'))
        {
            clasesSinFormat.push_back(cadenaResultante);
        }
    }

    for (size_t i = 0; i < clasesSinFormat.size(); i++)
    {

        string claseATraer = clasesSinFormat.at(i);
        stringstream streamDeAtribs(claseATraer);

        string cadenaResAtribs;

        while (getline(streamDeAtribs, cadenaResAtribs, ' '))
        {
            cadenaResAtribs = cadenaResAtribs.substr(1);
            clase.push_back(cadenaResAtribs);
        }
    }

    for (size_t i = 0; i < clase.size(); i++)
    {
        string claseTraida = clase.at(i);
        stringstream streamDeClase(claseTraida);

        vector<string> atributoClaseLinea;

        string cadenaResultanteLineaClase;

        while (getline(streamDeClase, cadenaResultanteLineaClase, ' '))
        {
            atributoClaseLinea.push_back(cadenaResultanteLineaClase);
        }

        for (size_t i = 0; i < atributoClaseLinea.size(); i++)
        {
            vector<string> atributos;

            string atribAct = atributoClaseLinea.at(i);
            stringstream streamDeAtributos(atribAct);
            string atribResultante;
            vector<string> atribIndividual;
            int contador = 0;

            while (getline(streamDeAtributos, atribResultante, ':'))
            {
                // cout << atribResultante << endl;
                if (contador % 2 == 1)
                {
                    atribIndividual.push_back(atribResultante);
                }
                contador++;
            }

            for (size_t i = 0; i < atribIndividual.size(); i++)
            {
                cout << atribIndividual.at(i) << endl;
            }
        }
    }

    // for (size_t i = 0; i < clases.size(); i++)
    // {
    //     cout << clases.at(i) << endl;
    // }

    // for (size_t i = 0; i < clase.size(); i++)
    // {
    //     cout << clase.at(i) << endl;
    // }
}
