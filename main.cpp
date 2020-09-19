#include <iostream>

using namespace std;

#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
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
        }

        for (size_t i = 0; i < atributoClaseLinea.size(); i++)
        {
            vector<string> atributos;

            string atribAct = atributoClaseLinea.at(i);
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

            archivoSalidaCPP << "using namespace std;\n\n";

            archivoSalidaCPP << nombreArchivo << "::" << nombreArchivo << "(){ \n }";
            archivoSalidaCPP << endl;
            archivoSalidaCPP << endl;

            atribIndividual.erase(atribIndividual.begin());

            vector<string> nombresAtribs;
            vector<string> tipoAtribs;

            for (size_t i = 0; i < atribIndividual.size(); i++)
            {

                string atribLineaActual = atribIndividual.at(i);
                stringstream streamAtLinAct(atribLineaActual);
                string stringResultante;

                int contadorAtribs = 0;

                while (getline(streamAtLinAct, stringResultante, '|'))
                {
                    if (contadorAtribs % 2 == 1)
                    {
                        nombresAtribs.push_back(stringResultante);
                        contadorAtribs++;
                    }
                    else if (contadorAtribs % 2 == 0)
                    {
                        tipoAtribs.push_back(stringResultante);
                        contadorAtribs++;
                    }
                }
            }

            archivoSalidaCPP << nombreArchivo << "::" << nombreArchivo << "(";

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                if (i == nombresAtribs.size() - 1)
                {
                    archivoSalidaCPP << tipoAtribs.at(i) << " "
                                     << "_" << nombresAtribs.at(i) << "){ \n";
                }
                else
                {
                    archivoSalidaCPP << tipoAtribs.at(i) << " "
                                     << "_" << nombresAtribs.at(i) << ",";
                }
            }

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                archivoSalidaCPP << "\t" << nombresAtribs.at(i) << " = "
                                 << "_" << nombresAtribs.at(i) << ";\n";
            }
            archivoSalidaCPP << "}";
            archivoSalidaCPP << endl;
            archivoSalidaCPP << endl;
            archivoSalidaCPP << endl;

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                archivoSalidaCPP << "void " << nombreArchivo << "::set_" << nombresAtribs.at(i) << "(" << tipoAtribs.at(i) << " _" << nombresAtribs.at(i) << "){\n";
                archivoSalidaCPP << "\t" << nombresAtribs.at(i) << " = "
                                 << "_" << nombresAtribs.at(i) << ";\n";
                archivoSalidaCPP << "}\n";
            }

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                archivoSalidaCPP << tipoAtribs.at(i) << " " << nombreArchivo << "::get_" << nombresAtribs.at(i) << "(){\n";
                archivoSalidaCPP << "\t"
                                 << "return " << nombresAtribs.at(i) << ";\n";
                archivoSalidaCPP << "}\n";
            }

            archivoSalidaCPP << "string " << nombreArchivo << "::toString(){\n";
            string nombreArchivoUpper = nombreArchivo;

            std::for_each(nombreArchivoUpper.begin(), nombreArchivoUpper.end(), [](char &c) {
                c = ::toupper(c);
            });

            archivoSalidaCPP << "\t"
                             << "return "
                             << "\"" << nombreArchivoUpper << "-> ";

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                if (i == 0)
                {
                    archivoSalidaCPP << " " << nombresAtribs.at(i) << ": \""
                                     << "+" << nombresAtribs.at(i) << "+";
                }
                else if (i == nombresAtribs.size() - 1)
                {
                    if (tipoAtribs.at(i) == "int" || tipoAtribs.at(i) == "double")
                    {
                        archivoSalidaCPP << "\"|" << nombresAtribs.at(i) << ": \""
                                         << "+to_string(" << nombresAtribs.at(i) << ");\n}\n";
                    }
                    else
                    {
                        archivoSalidaCPP << "\"|" << nombresAtribs.at(i) << ": \""
                                         << "+" << nombresAtribs.at(i) << ";\n}\n";
                    }
                }
                else
                {
                    if (tipoAtribs.at(i) == "int" || tipoAtribs.at(i) == "double")
                    {
                        archivoSalidaCPP << "\"|" << nombresAtribs.at(i) << ": \""
                                         << "+to_string(" << nombresAtribs.at(i) << ")+";
                    }
                    else
                    {
                        archivoSalidaCPP << "\"|" << nombresAtribs.at(i) << ": \""
                                         << "+" << nombresAtribs.at(i) << "+";
                    }
                }
            }

            archivoSalidaCPP << nombreArchivo << "::~" << nombreArchivo << "(){\n}";

            ofstream archivoSalidaH;
            archivoSalidaH.open(nombreArchivoH);

            archivoSalidaH << "#ifndef " << nombreArchivoUpper << "_H\n";
            archivoSalidaH << "#define " << nombreArchivoUpper << "_H\n";

            archivoSalidaH << "#include <string> \n";

            archivoSalidaH << "class " << nombreArchivo << "{\n";
            archivoSalidaH << "\tprivate:\n";

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                archivoSalidaH << "\t\t" << tipoAtribs.at(i) << " " << nombresAtribs.at(i) << ";\n";
            }

            archivoSalidaH << "\tpublic:\n";
            archivoSalidaH << "\t\t" << nombreArchivo << "();\n";
            archivoSalidaH << "\t\t" << nombreArchivo << "(";

            for (size_t i = 0; i < tipoAtribs.size(); i++)
            {
                if (i == tipoAtribs.size() - 1)
                {
                    archivoSalidaH << tipoAtribs.at(i) << ");\n";
                }
                else
                {
                    archivoSalidaH << tipoAtribs.at(i) << ",";
                }
            }

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                archivoSalidaH << "\t\tvoid set_" << nombresAtribs.at(i) << "(" << tipoAtribs.at(i) << ");\n";
            }

            for (size_t i = 0; i < nombresAtribs.size(); i++)
            {
                archivoSalidaH << "\t\t" << tipoAtribs.at(i) << " get_" << nombresAtribs.at(i) << "();\n";
            }

            archivoSalidaH << "\t\tstring toString();\n";
            archivoSalidaH << "\t\t~" << nombreArchivo << "();\n";
            archivoSalidaH << ");\n";
            archivoSalidaH << "#endif\n";
        }
        else
        {
            std::cout << "El archivo no se ha podido abrir" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
