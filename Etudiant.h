#ifndef ETUDIANT_H
#define ETUDIANT_H

class Etudiant {
private:
    char* nom;
    char* prenom;
    int numeroEtudiant;
    int age;
    float note;

public:
    Etudiant();
    Etudiant(const char nom[], const char prenom[], int numeroEtudiant, int age, float note);

    char* getNom() const;
    char* getPrenom() const;
    int getNumeroEtudiant() const;
    int getAge() const;
    float getNote() const;

    void setNom(const char* nom);
    void setPrenom(const char* prenom);
    void setNumeroEtudiant(int numeroEtudiant);
    void setAge(int age);
    void setNote(float note);
    
    void afficher() const;
};

#endif 
