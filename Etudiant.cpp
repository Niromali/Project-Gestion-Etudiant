#include "Etudiant.h"
#include <cstring>
#include <iostream>

using namespace std;

Etudiant::Etudiant() {
	nom = new char[11];
	strcpy(nom,"");
	prenom = new char[11];
	strcpy(prenom,"");

    numeroEtudiant = 0;
    age = 0;
    note = 0.0; 
}

Etudiant::Etudiant(const char nom[], const char prenom[], int numeroEtudiant, int age, float note) {
    this->nom = new char[strlen(nom) + 1];
    strcpy(this->nom, nom);

    this->prenom = new char[strlen(prenom) + 1];
    strcpy(this->prenom, prenom);

    this->numeroEtudiant = numeroEtudiant;
    this->age = age;
    this->note = note;
}

char* Etudiant::getNom() const {
    return nom;
}

char* Etudiant::getPrenom() const {
    return prenom;
}

int Etudiant::getNumeroEtudiant() const {
    return numeroEtudiant;
}

int Etudiant::getAge() const {
    return age;
}

float Etudiant::getNote() const {
    return note;
}

void Etudiant::setNom(const char* nom) {
    delete[] this->nom;

    this->nom = new char[strlen(nom) + 1];

    strcpy(this->nom, nom);
}

void Etudiant::setPrenom(const char* prenom) {
    delete[] this->prenom;

    this->prenom = new char[strlen(prenom) + 1];
    strcpy(this->prenom, prenom);
}

void Etudiant::setNumeroEtudiant(int numeroEtudiant) {
    this->numeroEtudiant = numeroEtudiant;
}

void Etudiant::setAge(int age) {
    this->age = age;
}

void Etudiant::setNote(float note) {
    this->note = note;
}

void Etudiant::afficher() const {
    cout << "Nom: " << nom << endl;
    cout << "Prénom: " << prenom << endl;
    cout << "Numéro étudiant: " << numeroEtudiant << endl;
	cout << "Âge: " << age << endl;
    cout << "Note: " << note << endl;
}

