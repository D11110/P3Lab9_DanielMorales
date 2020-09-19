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
    try
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

        vector<string> atributoClaseLinea;
        vector<string> atribIndividual;
        for (size_t i = 0; i < clase.size(); i++)
        {
            string claseTraida = clase.at(i);
            stringstream streamDeClase(claseTraida);

            string cadenaResultanteLineaClase;

            while (getline(streamDeClase, cadenaResultanteLineaClase, ' '))
            {
                atributoClaseLinea.push_back(cadenaResultanteLineaClase);
            }

            for (size_t x = 0; x < atributoClaseLinea.size(); x++)
            {
                vector<string> atributos;

                string atribAct = atributoClaseLinea.at(x);
                stringstream streamDeAtributos(atribAct);
                string atribResultante;

                int contador = 0;

                while (getline(streamDeAtributos, atribResultante, ':'))
                {
                    if (contador % 2 == 1)
                    {
                        atribIndividual.push_back(atribResultante);
                    }
                    contador++;
                }
            }
        }

        string nombreArchivoCPP = atribIndividual[0];
        nombreArchivoCPP += ".cpp";
        string nombreArchivoH = atribIndividual[0];
        nombreArchivoH += ".h";
        string nombreArchivo = atribIndividual[0];

        ofstream archivoSalidaCPP;
        archivoSalidaCPP.open(nombreArchivoCPP.c_str(), ios::trunc);

        if (archivoSalidaCPP.is_open())
        {
            archivoSalidaCPP << "#include \"" << nombreArchivoH << "\"" << endl;
            archivoSalidaCPP << endl;

            archivoSalidaCPP << nombreArchivo << "::" << nombreArchivo << "(){ \n }";
            archivoSalidaCPP << endl;
            archivoSalidaCPP << endl;

            atribIndividual.erase(atribIndividual.begin());

            vector<string> nombresAtribs;
            vector<string> tipoAtribs;

            for (size_t m = 0; m < atribIndividual.size(); m++)
            {

                string atribLineaActual = atribIndividual.at(m);
                stringstream streamAtLinAct(atribLineaActual);
                string stringResultante;

                int contadorAtribs = 0;

                while (getline(streamAtLinAct, stringResultante, '|'))
                {
                    if (contadorAtribs % 2 == 1)
                    {
                        nombresAtribs.push_back(stringResultante);
                    }
                    else
                    {
                        tipoAtribs.push_back(stringResultante);
                    }
                    contadorAtribs++;
                }
            }

            archivoSalidaCPP << nombreArchivo << "::" << nombreArchivo << "(";

            for (size_t k = 0; k < nombresAtribs.size(); k++)
            {
                if (k == nombresAtribs.size() - 1)
                {
                    archivoSalidaCPP << tipoAtribs.at(k) << " "
                                     << "_" << nombresAtribs.at(k) << "){ \n";
                }
                else
                {
                    archivoSalidaCPP << tipoAtribs.at(k) << " "
                                     << "_" << nombresAtribs.at(k) << ",";
                }
            }

            for (size_t l = 0; l < nombresAtribs.size(); l++)
            {
                archivoSalidaCPP << "\t" << nombresAtribs.at(l) << " = "
                                 << "_" << nombresAtribs.at(l) << ";\n";
            }
            archivoSalidaCPP << "}";
            archivoSalidaCPP << endl;
            archivoSalidaCPP << endl;
            archivoSalidaCPP << endl;

            for (size_t b = 0; b < nombresAtribs.size(); b++)
            {
                archivoSalidaCPP << "void " << nombreArchivo << "::set_" << nombresAtribs.at(b) << "(" << tipoAtribs.at(b) << " _" << nombresAtribs.at(b) << "){\n";
                archivoSalidaCPP << "\t" << nombresAtribs.at(b) << " = "
                                 << "_" << nombresAtribs.at(b) << ";\n";
                archivoSalidaCPP << "}\n";
            }

            for (size_t o = 0; o < nombresAtribs.size(); o++)
            {
                archivoSalidaCPP << tipoAtribs.at(o) << " " << nombreArchivo << "::get_" << nombresAtribs.at(o) << "(){\n";
                archivoSalidaCPP << "\t"
                                 << "return " << nombresAtribs.at(o) << ";\n";
                archivoSalidaCPP << "}\n";
            }

            archivoSalidaCPP << "string " << nombreArchivo << "::toString(){\n"; 
            archivoSalidaCPP << "return ";
        }
        else
        {
        }

        // for (size_t i = 0; i < atribIndividual.size(); i++)
        // {
        //     cout << atribIndividual.at(i) << endl;
        // }

        // for (size_t i = 0; i < clases.size(); i++)
        // {
        //     cout << clases.at(i) << endl;
        // }

        // for (size_t i = 0; i < clase.size(); i++)
        // {
        //     cout << clase.at(i) << endl;
        // }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
