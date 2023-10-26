

#ifndef STOCK_H
#define STOCK_H

#include "Etudiant.h"

class Stock {
private:
    Etudiant TP[10];  
    int nbp;          

public:
    Stock();                            
    void afficher();                     
    bool ajouterEtudiant(Etudiant& etudiant);
    int getNBrEtudiant();
    Stock(const Stock& s);
    int getEtudiantPosition(const char* nom);
    bool supprimerEtudiant(const char* nom);
    bool supprimerEtudiant(int numeroEtudiant);
    bool modifierEtudiant(const char* nom, Etudiant etudiant);
    Etudiant* chercherEtudiantParNumero(int numeroEtudiant);
	Etudiant& getEtudiantPos(const char* netudiant);
	Etudiant& getEtudiantAt(int index);
    void sauvegarderStockCSV();
    void importFromCSV();
};

#endif 


