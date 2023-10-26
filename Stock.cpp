#include "Stock.h"
#include "Etudiant.h"


#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

Stock::Stock() {
    nbp = 0;
}

void Stock::afficher() {
    for (int i = 0; i < nbp; i++) {
        cout << "Etudiant " << i + 1 << ":" << endl;
        TP[i].afficher();
    }
}

bool Stock::ajouterEtudiant(Etudiant& etudiant) {
    if (nbp < 10) {
        TP[nbp] = etudiant;
        nbp++;
        return true;
    }
    return false;
}

int Stock::getNBrEtudiant() {
    return nbp;
}

Stock::Stock(const Stock& s) {
    for (int i = 0; i < s.nbp; i++)
        TP[i] = s.TP[i];
    nbp = s.nbp;
}

int Stock::getEtudiantPosition(const char* nom) {
    for (int i = 0; i < nbp; i++) {
        if (strcmp(nom, TP[i].getNom()) == 0)
            return i;
    }
    return -1;
}

Etudiant& Stock::getEtudiantPos(const char* netudiant) {
    int x = getEtudiantPosition(netudiant);
    if (x != -1)
        return TP[x];
}

bool Stock::supprimerEtudiant(int numeroEtudiant) {
    int position = -1;
    for (int i = 0; i < nbp; i++) {
        if (TP[i].getNumeroEtudiant() == numeroEtudiant) {
            position = i;
            break;
        }
    }

    if (position != -1) {
        for (int i = position; i < nbp - 1; i++) {
            TP[i] = TP[i + 1];
        }
        nbp--;
        return true;
    }
    return false;
}
Etudiant& Stock::getEtudiantAt(int index) {
    if (index >= 0 && index < nbp)
        return TP[index];
    return TP[0];
}

bool Stock::modifierEtudiant(const char* nom, Etudiant etudiant) {
    int position = getEtudiantPosition(nom);
    if (position != -1) {
        TP[position] = etudiant;
        return true;
    }
    return false;
}
Etudiant* Stock::chercherEtudiantParNumero(int numeroEtudiant) {
    for (int i = 0; i < nbp; i++) {
        if (TP[i].getNumeroEtudiant() == numeroEtudiant) {
            return &TP[i];
        }
    }
    return NULL;
}



void Stock::sauvegarderStockCSV() {
    ofstream fichier("Stock.csv");

    if (fichier.is_open()) {
        fichier << "Nom,Prenom,NumeroEtudiant,Age,Note" << endl;

        for (int i = 0; i < nbp; ++i) {
            fichier << TP[i].getNom() << "," << TP[i].getPrenom() << "," << TP[i].getNumeroEtudiant()
                    << "," << TP[i].getAge() << "," << TP[i].getNote() << endl;
        }

        fichier.close();

    }
}


void Stock::importFromCSV() {
    ifstream fichier("Stock.csv");

    if (fichier.is_open()) {
        string ligne;

        getline(fichier, ligne);

        int index = 0;

        while (getline(fichier, ligne)) {
            istringstream iss(ligne);
            string token;

            getline(iss, token, ',');
            TP[index].setNom(token.c_str());

            getline(iss, token, ',');
            TP[index].setPrenom(token.c_str());

            getline(iss, token, ',');
            int numeroEtudiant = atoi(token.c_str());
            TP[index].setNumeroEtudiant(numeroEtudiant);

            getline(iss, token, ',');
            int age = atoi(token.c_str());
            TP[index].setAge(age);

            getline(iss, token, ',');
            float note = atof(token.c_str()); 
            TP[index].setNote(note);

            index++;
        }
        nbp = index;

        fichier.close();
    } 
}
