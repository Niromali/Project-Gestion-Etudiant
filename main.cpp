#include <iostream>
#include "Etudiant.h"
#include <string.h>
#include "Stock.h"
#include <fstream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>


using namespace std;


Stock s;
const int SCREEN_WIDTH=900;
const int SCREEN_HEIGHT=506;
const int FONT_SIZE=24;

SDL_Surface* screen = NULL;
SDL_Surface* textSurface = NULL;
TTF_Font* font = NULL;
SDL_Surface* previousFrame = NULL;
SDL_Rect previousFrameRect;

bool returnToPreviousFrame = false;


//Open:
const int INTERVAL_MINO_X=345;
const int INTERVAL_MAXO_X=567;
const int INTERVAL_MINO_Y=328;
const int INTERVAL_MAXO_Y=393;
//Ajouter
const int INTERVAL_MINAP_X=360;
const int INTERVAL_MAXAP_X=673;
const int INTERVAL_MINAP_Y=12;
const int INTERVAL_MAXAP_Y=84;
//Recherche:
const int INTERVAL_MINR_X=312;
const int INTERVAL_MAXR_X=628;
const int INTERVAL_MINR_Y=103;
const int INTERVAL_MAXR_Y=171;
//Supprimer:
const int INTERVAL_MINS_X=358;
const int INTERVAL_MAXS_X=669;
const int INTERVAL_MINS_Y=393;
const int INTERVAL_MAXS_Y=464;
//Afficher:
const int INTERVAL_MINA_X=357;
const int INTERVAL_MAXA_X=669;
const int INTERVAL_MINA_Y=196;
const int INTERVAL_MAXA_Y=270;
//Modiffier:
const int INTERVAL_MINM_X=310;
const int INTERVAL_MAXM_X=633;
const int INTERVAL_MINM_Y=287;
const int INTERVAL_MAXM_Y=358;




//Afficher-Quiter:
const int INTERVAL_MINAQ_X=384;
const int INTERVAL_MAXAQ_X=508;
const int INTERVAL_MINAQ_Y=453;
const int INTERVAL_MAXAQ_Y=501;


int initializeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
        return 0;
    }
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (screen == NULL)
    {
        fprintf(stderr, "Erreur lors de la cr?ation de la fen?tre: %s\n", SDL_GetError());
        return 0;
    }
    SDL_WM_SetCaption("Gestion Des Etudiants", NULL);
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL_ttf: %s\n", TTF_GetError());
        return 0;
    }
    return 1;
}

//représentant le chemin d'accès à un fichier de police, et charge la police à l'aide de SDL_ttf.
int loadFont(const char* fontPath)
{
    font = TTF_OpenFont(fontPath, FONT_SIZE);
    if (font == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de la police de caract?res: %s\n", TTF_GetError());
        return 0;
    }
    return 1;
}

//fonction qui rende un texte :
SDL_Surface * renderText(const char * text,Uint8 r,Uint8 g,Uint8 b)
{
	SDL_Color color = {r,g,b};
	textSurface = TTF_RenderText_Solid(font,text,color);
	if(textSurface == NULL)
	{
		fprintf(stderr, "Erreur lors du rendu du texte: %s\n", TTF_GetError());
		return NULL;
	}
	return textSurface;
}

//fonction qui est responsable du nettoyage et de la libération des ressources utilisées par SDL et SDL_ttf.
void cleanup()
{
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

//représentant les coordonnées où le texte sera dessiné à l'écran.
void drawText(SDL_Surface* textSurface, int x, int y)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    SDL_BlitSurface(textSurface, NULL, screen, &destRect);
    SDL_Flip(screen);
}

//fonction qui designe les coordonnes.
void coordonnes(int mouseX,int mouseY)
{
	char coordinates[50];
	sprintf(coordinates, "x=%d, y=%d", mouseX, mouseY);
	SDL_Surface* coordinatesSurface = renderText(coordinates, 255, 0, 0);
	if (coordinatesSurface != NULL)
	{
		drawText(coordinatesSurface, mouseX, mouseY);
		SDL_FreeSurface(coordinatesSurface);
		SDL_Delay(3000);
	}
}







void clearInfoMessage(SDL_Surface* screen, SDL_Rect infoTextRect, SDL_Surface* background)
{
    SDL_BlitSurface(background, &infoTextRect, screen, &infoTextRect);
    SDL_Flip(screen);
}


//Ajouter Etudiant :
void AjouterE()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(900, 506, 32, SDL_SWSURFACE);
    TTF_Init();
    SDL_EnableUNICODE(1);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 29);
   
    SDL_Surface* texteSurface = renderText("Bonjour, SDL 1.2", 255, 255, 255);
    bool isRunning = false;
    SDL_Event event;
    SDL_Surface* background = NULL;
    background = IMG_Load("3p.png");
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);
    SDL_Color textColor = {255, 0, 0};
    SDL_Rect textField1 = {455, 158, 200, 30};
    SDL_Rect textField2 = {455, 200, 200, 30};
    SDL_Rect textField3 = {455, 252, 200, 30};
    SDL_Rect textField4 = {455, 297, 200, 30};
    SDL_Rect textField5 = {455, 342, 200, 30};
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, "Nom :", textColor);
    SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, "Prenom :", textColor);
    SDL_Surface* textSurface3 = TTF_RenderText_Solid(font, "Numero d'etudiant :", textColor);
    SDL_Surface* textSurface4 = TTF_RenderText_Solid(font, "Age :", textColor);
    SDL_Surface* textSurface5 = TTF_RenderText_Solid(font, "Note :", textColor);
    std::string inputText1, inputText2, inputText3, inputText4, inputText5;
    bool activeField1 = true, activeField2 = false, activeField3 = false, activeField4 = false, activeField5 = false;

    //position du bouton Ajouter:
    const int INTERVAL_MIN_X = 484;
    const int INTERVAL_MAX_X = 574;
    const int INTERVAL_MIN_Y = 400;
    const int INTERVAL_MAX_Y = 447;


  //position du bouton Retour:
    const int INTERVAL_MINQI_X = 280;
    const int INTERVAL_MAXQI_X = 376;
    const int INTERVAL_MINQI_Y = 403;
    const int INTERVAL_MAXQI_Y = 451;
    
    
    // Declaration of infoTextRect
    SDL_Rect infoTextRect = {280, 100, 500, 10};
    while (!isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                //coordonnes(mouseX, mouseY);
  			 if (mouseX >= INTERVAL_MIN_X && mouseX <= INTERVAL_MAX_X && mouseY >= INTERVAL_MIN_Y && mouseY <= INTERVAL_MAX_Y)
                {
                    int numeroEtudiant = atoi(inputText3.c_str());
                    
                    Etudiant* existingEtudiant = s.chercherEtudiantParNumero(numeroEtudiant);
                    if (existingEtudiant == NULL)
                    {
                        int age = atoi(inputText4.c_str());
                        float note = atof(inputText5.c_str());
                        char* nom = new char[inputText1.length() + 1];
                        strcpy(nom, inputText1.c_str());
                        char* prenom = new char[inputText2.length() + 1];
                        strcpy(prenom, inputText2.c_str());
                        Etudiant etudiant;
                        etudiant.setNom(nom);
                        etudiant.setPrenom(prenom);
                        etudiant.setNumeroEtudiant(numeroEtudiant);
                        etudiant.setAge(age);
                        etudiant.setNote(note);
                        s.ajouterEtudiant(etudiant);
                        
                        
                    	clearInfoMessage(screen, infoTextRect, background);
                        SDL_Surface* infoSurface = TTF_RenderText_Solid(font, "Etudiant ajouté !", textColor);
                        SDL_BlitSurface(infoSurface, NULL, screen, &infoTextRect);
                        SDL_FreeSurface(infoSurface);
                      
                    }
                    else
                    {
                    	clearInfoMessage(screen, infoTextRect, background);
                        SDL_Surface* infoSurface = TTF_RenderText_Solid(font, "Numero d'Etudiant existe déjà.", textColor);
                        SDL_BlitSurface(infoSurface, NULL, screen, &infoTextRect);
                        SDL_FreeSurface(infoSurface);
                    }
                        inputText1 = "";
                        inputText2 = "";
                        inputText3 = "";
                        inputText4 = "";
                        inputText5 = "";

                       
                        SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField2, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField3, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField4, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField5, SDL_MapRGB(screen->format, 255, 255, 255));
                        
                    SDL_Flip(screen);
                }
                 if (mouseX >= INTERVAL_MINQI_X && mouseX <= INTERVAL_MAXQI_X && mouseY >= INTERVAL_MINQI_Y && mouseY <= INTERVAL_MAXQI_Y)
                {
				return;
				}
            }
             else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = true;
                }
                else if (event.key.keysym.sym == SDLK_TAB)
                {
                    activeField1 = !activeField1;
                    activeField2 = !activeField2;
                    activeField3 = !activeField3;
                    activeField4 = !activeField4;
                    activeField5 = !activeField5;
                }
                else if (event.key.keysym.sym == SDLK_RETURN)
                {
                    if (activeField1)
                    {
                        activeField1 = false;
                        activeField2 = true;
                    }
                    else if (activeField2)
                    {
                        activeField2 = false;
                        activeField3 = true;
                    }
                    else if (activeField3)
                    {
                        activeField3 = false;
                        activeField4 = true;
                    }
                    else if (activeField4)
                    {
                        activeField4 = false;
                        activeField5 = true;
                    }
                    else if (activeField5)
                    {
                        activeField5 = false;
                    }
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (activeField1 && !inputText1.empty())
                    {
                        inputText1 = inputText1.substr(0, inputText1.length() - 1);
                        SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField2 && !inputText2.empty())
                    {
                        inputText2 = inputText2.substr(0, inputText2.length() - 1);
                        SDL_FillRect(screen, &textField2, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField3 && !inputText3.empty())
                    {
                        inputText3 = inputText3.substr(0, inputText3.length() - 1);
                        SDL_FillRect(screen, &textField3, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField4 && !inputText4.empty())
                    {
                        inputText4 = inputText4.substr(0, inputText4.length() - 1);
                        SDL_FillRect(screen, &textField4, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField5 && !inputText5.empty())
                    {
                        inputText5 = inputText5.substr(0, inputText5.length() - 1);
                        SDL_FillRect(screen, &textField5, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                }
                else
                {
                    if (activeField1)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isprint(inputChar) || inputChar == ' ')
                        {
                            inputText1 += inputChar;
                        }
                    }
                    else if (activeField2)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isprint(inputChar) || inputChar == ' ')
                        {
                            inputText2 += inputChar;
                        }
                    }
                    else if (activeField3)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isdigit(inputChar) || inputChar == ' ')
                        {
                            inputText3 += inputChar;
                        }
                    }
                    else if (activeField4)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isdigit(inputChar) || inputChar == ' ')
                        {
                            inputText4 += inputChar;
                        }
                    }
                    else if (activeField5)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isdigit(inputChar) || inputChar == '.' || inputChar == ' ')
                        {
                            inputText5 += inputChar;
                        }
                    }
                }
            }
        }
        if (activeField1)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText1.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField1);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField2)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText2.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField2);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField3)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText3.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField3);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField4)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText4.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField4);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField5)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText5.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField5);
            SDL_FreeSurface(inputSurface);
        }
        SDL_Flip(screen);
    }

    SDL_FreeSurface(textSurface1);
    SDL_FreeSurface(textSurface2);
    SDL_FreeSurface(textSurface3);
    SDL_FreeSurface(textSurface4);
    SDL_FreeSurface(textSurface5);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit();
}

//Modifier Etudiant
void modifierEtudiant()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(900, 506, 32, SDL_SWSURFACE);
    TTF_Init();
    SDL_EnableUNICODE(1);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 20);
    SDL_Color textColor = { 255, 0, 0 };
    SDL_Color textColorVert = { 0, 255, 0 };
    
    SDL_Surface* background = NULL;
    background = IMG_Load("modifier.png");
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);
    
    SDL_Rect infoTextRect = { 300, 460, 500, 20 };
    bool isInfoDisplayed = false;

    SDL_Rect textField1 = { 455, 167, 200, 30 };
    SDL_Rect textField2 = { 455, 210, 200, 30 };
    SDL_Rect textField3 = { 455, 255, 200, 30 };
    SDL_Rect textField4 = { 455, 296, 200, 30 };
    SDL_Rect textField5 = { 455, 341, 200, 30 };
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, "Numero etud a modifier:", textColorVert);
    SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, "Nouveau nom :", textColor);
    SDL_Surface* textSurface3 = TTF_RenderText_Solid(font, "Nouveau prenom :", textColor);
    SDL_Surface* textSurface4 = TTF_RenderText_Solid(font, "Nouvel age :", textColorVert);
    SDL_Surface* textSurface5 = TTF_RenderText_Solid(font, "Nouvelle note :", textColorVert);
    
    std::string inputText1, inputText2, inputText3, inputText4, inputText5;
    bool activeField1 = true, activeField2 = false, activeField3 = false, activeField4 = false, activeField5 = false;

    //position du bouton Modifier:
    const int INTERVAL_MIN_X = 484;
    const int INTERVAL_MAX_X = 574;
    const int INTERVAL_MIN_Y = 400;
    const int INTERVAL_MAX_Y = 447;
    
    //position du bouton Retour:
    const int INTERVAL_MINRE_X = 280;
    const int INTERVAL_MAXRE_X = 376;
    const int INTERVAL_MINRE_Y = 403;
    const int INTERVAL_MAXRE_Y = 451;

    bool isRunning = false;
    SDL_Event event;
    while (!isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                
                if (mouseX >= INTERVAL_MIN_X && mouseX <= INTERVAL_MAX_X && mouseY >= INTERVAL_MIN_Y && mouseY <= INTERVAL_MAX_Y)
                {
                   
                    if (isInfoDisplayed) {
                        SDL_BlitSurface(background, &infoTextRect, screen, &infoTextRect);
                        isInfoDisplayed = false;
                    }

                    int numeroEtudiantAModifier = atoi(inputText1.c_str());
                    Etudiant* etudiantAModifier = s.chercherEtudiantParNumero(numeroEtudiantAModifier);
                    if (etudiantAModifier != NULL)
                    {
                        char* nouveauNom = new char[inputText2.length() + 1];
                        strcpy(nouveauNom, inputText2.c_str());
                        char* nouveauPrenom = new char[inputText3.length() + 1];
                        strcpy(nouveauPrenom, inputText3.c_str());
                        int nouvelAge = atoi(inputText4.c_str());
                        float nouvelleNote = atof(inputText5.c_str());

                        etudiantAModifier->setNom(nouveauNom);
                        etudiantAModifier->setPrenom(nouveauPrenom);
                        etudiantAModifier->setAge(nouvelAge);
                        etudiantAModifier->setNote(nouvelleNote);

                        SDL_Surface* infoSurface = TTF_RenderText_Solid(font, "Etudiant modifie !", textColor);
                        SDL_BlitSurface(infoSurface, NULL, screen, &infoTextRect);
                        SDL_FreeSurface(infoSurface);
                        isInfoDisplayed = true; 

                        inputText1 = "";
                        inputText2 = "";
                        inputText3 = "";
                        inputText4 = "";
                        inputText5 = "";

                       
                        SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField2, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField3, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField4, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField5, SDL_MapRGB(screen->format, 255, 255, 255));

                        SDL_Flip(screen);
                    }
                    else
                    {
                        SDL_Surface* infoSurface = TTF_RenderText_Solid(font, "Etudiant n'existe pas.", textColor);
                        SDL_BlitSurface(infoSurface, NULL, screen, &infoTextRect);
                        SDL_FreeSurface(infoSurface);
                        isInfoDisplayed = true;
                        
                        inputText1 = "";
                        inputText2 = "";
                        inputText3 = "";
                        inputText4 = "";
                        inputText5 = "";

                        SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField2, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField3, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField4, SDL_MapRGB(screen->format, 255, 255, 255));
                        SDL_FillRect(screen, &textField5, SDL_MapRGB(screen->format, 255, 255, 255));

                        SDL_Flip(screen);
                    }
                }
                 if (mouseX >= INTERVAL_MINRE_X && mouseX <= INTERVAL_MAXRE_X && mouseY >= INTERVAL_MINRE_Y && mouseY <= INTERVAL_MAXRE_Y)
                {
                	
                	return;
						if (returnToPreviousFrame)
                        {
                            returnToPreviousFrame = false;
                            SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
                        }
				}
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    isRunning = true;
                }
                else if (event.key.keysym.sym == SDLK_TAB)
                {
                    activeField1 = !activeField1;
                    activeField2 = !activeField2;
                    activeField3 = !activeField3;
                    activeField4 = !activeField4;
                    activeField5 = !activeField5;
                }
                else if (event.key.keysym.sym == SDLK_RETURN)
                {
                    if (activeField1)
                    {
                        activeField1 = false;
                        activeField2 = true;
                    }
                    else if (activeField2)
                    {
                        activeField2 = false;
                        activeField3 = true;
                    }
                    else if (activeField3)
                    {
                        activeField3 = false;
                        activeField4 = true;
                    }
                    else if (activeField4)
                    {
                        activeField4 = false;
                        activeField5 = true;
                    }
                    else if (activeField5)
                    {
                        activeField5 = false;
                    }
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (activeField1 && !inputText1.empty())
                    {
                        inputText1 = inputText1.substr(0, inputText1.length() - 1);
                        SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField2 && !inputText2.empty())
                    {
                        inputText2 = inputText2.substr(0, inputText2.length() - 1);
                        SDL_FillRect(screen, &textField2, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField3 && !inputText3.empty())
                    {
                        inputText3 = inputText3.substr(0, inputText3.length() - 1);
                        SDL_FillRect(screen, &textField3, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField4 && !inputText4.empty())
                    {
                        inputText4 = inputText4.substr(0, inputText4.length() - 1);
                        SDL_FillRect(screen, &textField4, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                    else if (activeField5 && !inputText5.empty())
                    {
                        inputText5 = inputText5.substr(0, inputText5.length() - 1);
                        SDL_FillRect(screen, &textField5, SDL_MapRGB(screen->format, 255, 255, 255));
                    }
                }
                else
                {
                    if (activeField1)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isdigit(inputChar))
                        {
                            inputText1 += inputChar;
                        }
                    }
                    else if (activeField2)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isprint(inputChar) || inputChar == ' ')
                        {
                            inputText2 += inputChar;
                        }
                    }
                    else if (activeField3)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isprint(inputChar) || inputChar == ' ')
                        {
                            inputText3 += inputChar;
                        }
                    }
                    else if (activeField4)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isdigit(inputChar) || inputChar == ' ')
                        {
                            inputText4 += inputChar;
                        }
                    }
                    else if (activeField5)
                    {
                        char inputChar = event.key.keysym.unicode;
                        if (isdigit(inputChar) || inputChar == '.' || inputChar == ' ')
                        {
                            inputText5 += inputChar;
                        }
                    }
                }
            }
        }
        if (activeField1)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText1.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField1);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField2)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText2.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField2);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField3)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText3.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField3);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField4)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText4.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField4);
            SDL_FreeSurface(inputSurface);
        }
        else if (activeField5)
        {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText5.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField5);
            SDL_FreeSurface(inputSurface);
        }

        SDL_Flip(screen);
    }

    SDL_FreeSurface(textSurface1);
    SDL_FreeSurface(textSurface2);
    SDL_FreeSurface(textSurface3);
    SDL_FreeSurface(textSurface4);
    SDL_FreeSurface(textSurface5);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit();
}


//Recherche Etudiant :
void RechercheEtudiant()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(900, 506, 32, SDL_SWSURFACE);
    TTF_Init();
    SDL_EnableUNICODE(1);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
    SDL_Color textColor = { 255, 0, 0 };
    SDL_Rect textField1 = { 150, 120, 200, 30 };
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, "", textColor);
    SDL_Event event;
    bool quit = false;
    std::string inputText1;
    bool activeField1 = true;
    SDL_Surface* background = NULL;
    background = IMG_Load("4r.png");
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);
    //position de button quitter:
    const int INTERVAL_MIN_X = 386;
    const int INTERVAL_MAX_X = 512;
    const int INTERVAL_MIN_Y = 422;
    const int INTERVAL_MAX_Y = 486;
    //position de button recherche:
    const int INTERVAL_MIN_Xs = 694;
    const int INTERVAL_MAX_Xs = 769;
    const int INTERVAL_MIN_Ys = 117;
    const int INTERVAL_MAX_Ys = 158;
    std::string referenceInput;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (mouseX >= INTERVAL_MIN_X && mouseX <= INTERVAL_MAX_X && mouseY >= INTERVAL_MIN_Y && mouseY <= INTERVAL_MAX_Y)
                    {
                        return;
                    }
                    else if (mouseX >= INTERVAL_MIN_Xs && mouseX <= INTERVAL_MAX_Xs && mouseY >= INTERVAL_MIN_Ys && mouseY <= INTERVAL_MAX_Ys)
                    {
                        referenceInput = inputText1;
                        int numeroEtudiant = std::atoi(referenceInput.c_str());

                        Etudiant* etudiant = s.chercherEtudiantParNumero(numeroEtudiant);

                        SDL_Rect whiteRect = { 0, 0, 900, 506 };
                        SDL_FillRect(screen, &whiteRect, SDL_MapRGB(screen->format, 255, 255, 255));

                        SDL_BlitSurface(background, NULL, screen, NULL);
                        SDL_BlitSurface(textSurface1, NULL, screen, &textField1);

                        if (etudiant != NULL) {
                            char* nom = etudiant->getNom();
                            char* prenom = etudiant->getPrenom();
                            int numeroEtudiant = etudiant->getNumeroEtudiant();
                            int age = etudiant->getAge();
                            float note = etudiant->getNote();

                            char strNom[50];
                            char strPrenom[50];
                            char strNumeroEtudiant[50];
                            char strAge[50];
                            char strNote[50];

                            sprintf(strNom, "%s", nom);
                            sprintf(strPrenom, "%s", prenom);
                            sprintf(strNumeroEtudiant, "%d", numeroEtudiant);
                            sprintf(strAge, "%d", age);
                            sprintf(strNote, "%.2f", note);

                            SDL_Rect textNom = { 150, 210, 400, 100 };
                            SDL_Rect textPrenom = { 330, 210, 400, 100 };
                            SDL_Rect textNumeroEtudiant = { 520, 210, 400, 100 };
                            SDL_Rect textAge = { 582, 210, 400, 100 };
                            SDL_Rect textNote = { 650, 210, 400, 100 };

                            SDL_Surface* inputSurfaceNom = TTF_RenderText_Solid(font, strNom, textColor);
                            SDL_BlitSurface(inputSurfaceNom, NULL, screen, &textNom);
                            SDL_FreeSurface(inputSurfaceNom);

                            SDL_Surface* inputSurfacePrenom = TTF_RenderText_Solid(font, strPrenom, textColor);
                            SDL_BlitSurface(inputSurfacePrenom, NULL, screen, &textPrenom);
                            SDL_FreeSurface(inputSurfacePrenom);

                            SDL_Surface* inputSurfaceNumeroEtudiant = TTF_RenderText_Solid(font, strNumeroEtudiant, textColor);
                            SDL_BlitSurface(inputSurfaceNumeroEtudiant, NULL, screen, &textNumeroEtudiant);
                            SDL_FreeSurface(inputSurfaceNumeroEtudiant);

                            SDL_Surface* inputSurfaceAge = TTF_RenderText_Solid(font, strAge, textColor);
                            SDL_BlitSurface(inputSurfaceAge, NULL, screen, &textAge);
                            SDL_FreeSurface(inputSurfaceAge);

                            SDL_Surface* inputSurfaceNote = TTF_RenderText_Solid(font, strNote, textColor);
                            SDL_BlitSurface(inputSurfaceNote, NULL, screen, &textNote);
                            SDL_FreeSurface(inputSurfaceNote);
                        }
                        else {
                            SDL_Rect textMessage = { 150, 210, 400, 100 };
                            SDL_Surface* messageSurface = TTF_RenderText_Solid(font, "Etudiant n'exist pas ", textColor);
                            SDL_BlitSurface(messageSurface, NULL, screen, &textMessage);
                            SDL_FreeSurface(messageSurface);
                            
                        }

                        inputText1 = "";
                    }
                }
            }      
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                else if (event.key.keysym.sym == SDLK_TAB) {
                    activeField1 = !activeField1;
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (activeField1) {
                        activeField1 = false;
                    }
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE) {
					    if (activeField1 && !inputText1.empty()) {					    						       
					        inputText1 = inputText1.substr(0, inputText1.length() - 1);
					        SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 255,255,255));         
					    }
					}
                else {
                    if (activeField1) {
                        char inputChar = event.key.keysym.unicode;
                        if (isprint(inputChar) || inputChar == ' ') {
                            inputText1 += inputChar;
                        }
                    }
                }
            }
        }
        if (activeField1) {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText1.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField1);
            SDL_FreeSurface(inputSurface);
        }

        SDL_Flip(screen);
    }

    SDL_FreeSurface(textSurface1);
    SDL_FreeSurface(background);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

int GoConfimer(int numeroEtudiantInput) {
    SDL_Color textColor = { 255, 0, 0 };
    SDL_Rect textField1 = { 90, 110, 200, 30 };
    SDL_Rect textMessage = { 125, 250, 300, 50 };
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, "Champ 1 :", textColor);
    SDL_Event event;
    bool quit = false;
    std::string inputText1;
    SDL_Surface* background = NULL;
    

    const int INTERVAL_MIN_Xv = 168;
    const int INTERVAL_MAX_Xv = 309;
    const int INTERVAL_MIN_Yv = 241;
    const int INTERVAL_MAX_Yv = 283;

    const int INTERVAL_MIN_Xn = 308;
    const int INTERVAL_MAX_Xn = 452;
    const int INTERVAL_MIN_Yn = 242;
    const int INTERVAL_MAX_Yn = 284;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (mouseX >= INTERVAL_MIN_Xn && mouseX <= INTERVAL_MAX_Xn && mouseY >= INTERVAL_MIN_Yn && mouseY <= INTERVAL_MAX_Yn) {
                        return 0;
                    } else if (mouseX >= INTERVAL_MIN_Xv && mouseX <= INTERVAL_MAX_Xv && mouseY >= INTERVAL_MIN_Yv && mouseY <= INTERVAL_MAX_Yv) {

                        bool etudiantExiste = false;
                        etudiantExiste = true; 
                        int numeroEtudiant = numeroEtudiantInput;
                        bool supprime = s.supprimerEtudiant(numeroEtudiant);

                        if (supprime) {
							    inputText1 = inputText1.substr(0, inputText1.length() - 1);
							    SDL_FillRect(screen, &textMessage, SDL_MapRGB(screen->format, 124, 129, 135));
							    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, "Etudiant Supprimé", textColor);
							    SDL_BlitSurface(background, NULL, screen, NULL);
							    SDL_BlitSurface(messageSurface, NULL, screen, &textMessage);
							    SDL_FreeSurface(messageSurface);
							    
							    
							    inputText1 = "";
								return 1;
							}
							else {
							   SDL_Rect textMessage = { 100, 250, 300, 50 };
							    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, "Etudiant n'existe pas", textColor);
							    SDL_BlitSurface(background, NULL, screen, NULL);  
							    SDL_BlitSurface(messageSurface, NULL, screen, &textMessage);
							    SDL_FreeSurface(messageSurface);
							   
							    inputText1 = "";
								return 2;
						}  
	    			}
	    		}
			}
		}
	}
}



void Supprimer()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(900, 506, 32, SDL_SWSURFACE);
    TTF_Init();
    SDL_EnableUNICODE(1);
    TTF_Font* font = TTF_OpenFont("arial.ttf", 35);
    SDL_Color textColor = { 255, 0, 0 };
    SDL_Rect textField1 = { 170, 160, 200, 30 };
    
    SDL_Rect textMessage = { 220, 260, 300, 50 };
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, "", textColor);
    SDL_Event event;
    bool quit = false;
    std::string inputText1;
    bool activeField1 = true;
    SDL_Surface* background = NULL;
    background = IMG_Load("supp.png");
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);
    
    
	//quitter
    const int INTERVAL_MIN_X = 328;
    const int INTERVAL_MAX_X = 578;
    const int INTERVAL_MIN_Y = 373;
    const int INTERVAL_MAX_Y = 408;
	//supp
    const int INTERVAL_MIN_Xs = 648;
    const int INTERVAL_MAX_Xs = 747;
    const int INTERVAL_MIN_Ys = 152;
    const int INTERVAL_MAX_Ys = 199;

    std::string referenceInput;
    SDL_Surface* zone = NULL;
    SDL_Surface* savedImage = NULL;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
 					//coordonnes(mouseX,mouseY);
                    if (mouseX >= INTERVAL_MIN_X && mouseX <= INTERVAL_MAX_X && mouseY >= INTERVAL_MIN_Y && mouseY <= INTERVAL_MAX_Y) {
                       
                        return;
                    } else if (mouseX >= INTERVAL_MIN_Xs && mouseX <= INTERVAL_MAX_Xs && mouseY >= INTERVAL_MIN_Ys && mouseY <= INTERVAL_MAX_Ys) {
                        SDL_Rect imageRect;
                        imageRect.x = 60;
                        imageRect.y = 70;

                        zone = IMG_Load("confirmation.png");

                        savedImage = SDL_CreateRGBSurface(0, screen->w, screen->h, 32, 0, 0, 0, 0);
                        SDL_BlitSurface(screen, NULL, savedImage, NULL);

                        SDL_BlitSurface(zone, NULL, screen, &imageRect);
                        SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);

                        int action = GoConfimer(atoi(inputText1.c_str()));

                        SDL_BlitSurface(savedImage, NULL, screen, NULL);
                        SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);

                        SDL_FreeSurface(savedImage);
                        SDL_FreeSurface(zone);

                        if (action == 1) {
                            SDL_FillRect(screen, &textMessage, SDL_MapRGB(screen->format, 124, 129, 135));
                            SDL_Surface* messageSurface = TTF_RenderText_Solid(font, "Etudiant Supprimé", textColor);
                            SDL_BlitSurface(background, NULL, screen, NULL); 
                            SDL_BlitSurface(messageSurface, NULL, screen, &textMessage);
                            SDL_FreeSurface(messageSurface);
                        } else if (action == 2) {
                            SDL_Rect textMessage = { 140, 250, 300, 50 };
                            SDL_Surface* messageSurface = TTF_RenderText_Solid(font, "Etudiant n'existe pas", textColor);
                            SDL_BlitSurface(background, NULL, screen, NULL); 
                            SDL_BlitSurface(messageSurface, NULL, screen, &textMessage);
                            SDL_FreeSurface(messageSurface);
                        }
                        inputText1="";
                    SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 240, 240, 240));
                    }
                    
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                } else if (event.key.keysym.sym == SDLK_TAB) {
                    activeField1 = !activeField1;
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    if (activeField1) {
                        activeField1 = false;
                    }
                } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (activeField1 && !inputText1.empty()) {
                        inputText1 = inputText1.substr(0, inputText1.length() - 1);
                        SDL_FillRect(screen, &textField1, SDL_MapRGB(screen->format, 240, 240, 240));
                    }
                } else {
                    if (activeField1) {
                        char inputChar = event.key.keysym.unicode;
                        if (isprint(inputChar) || inputChar == ' ') {
                            inputText1 += inputChar;
                        }
                    }
                }
            }
        }
        if (activeField1) {
            SDL_Surface* inputSurface = TTF_RenderText_Solid(font, inputText1.c_str(), textColor);
            SDL_BlitSurface(inputSurface, NULL, screen, &textField1);
            SDL_FreeSurface(inputSurface);
        }
        SDL_Flip(screen);
    }
    TTF_CloseFont(font);
    SDL_FreeSurface(background);
    SDL_FreeSurface(textSurface1);
    SDL_Quit();
}


//afficher Etudiant :
void afficherEtudiant(SDL_Surface* screen)
{
    const int X_OFFSET = 126; 
    const int Y_OFFSET = 125; 
    const int LINE_HEIGHT = 42;

    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
    SDL_Color textColor = { 255, 0, 0 };

    for (int i = 0; i < s.getNBrEtudiant(); i++)
    {
        Etudiant& etudiant = s.getEtudiantAt(i);

        char *nom = etudiant.getNom();
        char *prenom = etudiant.getPrenom();
        int numeroEtudiant = etudiant.getNumeroEtudiant();
        int age = etudiant.getAge();
        float note = etudiant.getNote();
        char strNumeroEtudiant[50];
        char strAge[50];
        char strNote[50];
        sprintf(strNumeroEtudiant, "%d", numeroEtudiant);
        sprintf(strAge, "%d", age);
        sprintf(strNote, "%0.2f", note);

        int y = Y_OFFSET + (i * LINE_HEIGHT);

        SDL_Rect textNom = { X_OFFSET, y, 200, 30 };
        SDL_Rect textPrenom = { X_OFFSET + 160, y, 200, 30 };
        SDL_Rect textNumeroEtudiant = { X_OFFSET + 380, y, 200, 30 };
        SDL_Rect textAge = { X_OFFSET + 450, y, 200, 30 };
        SDL_Rect textNote = { X_OFFSET + 550, y, 200, 30 };

        SDL_Surface* inputSurfaceNom = TTF_RenderText_Solid(font, nom, textColor);
        SDL_BlitSurface(inputSurfaceNom, NULL, screen, &textNom);
        SDL_FreeSurface(inputSurfaceNom);

        SDL_Surface* inputSurfacePrenom = TTF_RenderText_Solid(font, prenom, textColor);
        SDL_BlitSurface(inputSurfacePrenom, NULL, screen, &textPrenom);
        SDL_FreeSurface(inputSurfacePrenom);

        SDL_Surface* inputSurfaceNumeroEtudiant = TTF_RenderText_Solid(font, strNumeroEtudiant, textColor);
        SDL_BlitSurface(inputSurfaceNumeroEtudiant, NULL, screen, &textNumeroEtudiant);
        SDL_FreeSurface(inputSurfaceNumeroEtudiant);

        SDL_Surface* inputSurfaceAge = TTF_RenderText_Solid(font, strAge, textColor);
        SDL_BlitSurface(inputSurfaceAge, NULL, screen, &textAge);
        SDL_FreeSurface(inputSurfaceAge);

        SDL_Surface* inputSurfaceNote = TTF_RenderText_Solid(font, strNote, textColor);
        SDL_BlitSurface(inputSurfaceNote, NULL, screen, &textNote);
        SDL_FreeSurface(inputSurfaceNote);
    }

    TTF_CloseFont(font);
}

//Afficher :
void Afficher()
{
    const int INTERVAL_MINS_X = 52;
    const int INTERVAL_MAXS_X = 312;
    const int INTERVAL_MINS_Y = 449;
    const int INTERVAL_MAXS_Y = 500;

    const int INTERVAL_MINL_X = 587;
    const int INTERVAL_MAXL_X = 857;
    const int INTERVAL_MINL_Y = 453;
    const int INTERVAL_MAXL_Y = 501;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(900, 506, 32, SDL_SWSURFACE);
    TTF_Init();
    SDL_EnableUNICODE(1);
    loadFont("arial.ttf");
    SDL_Color textColor = { 255, 0, 0 };

    SDL_Surface * texteSurface = renderText("Bonjour, SDL 1.2", 255, 255, 255);
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, "Nom", textColor);
    SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, "Prenom", textColor);
    SDL_Surface* textSurface3 = TTF_RenderText_Solid(font, "Numero Etudiant", textColor);
    SDL_Surface* textSurface4 = TTF_RenderText_Solid(font, "Age", textColor);
    SDL_Surface* textSurface5 = TTF_RenderText_Solid(font, "Note", textColor);

    bool isRunning = true;
    SDL_Event event;
    SDL_Surface* background = NULL;
    background = IMG_Load("6r (2).png");
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
				//	coordonnes(mouseX,mouseY);
                    if (mouseX >= INTERVAL_MINAQ_X && mouseX <= INTERVAL_MAXAQ_X && mouseY >= INTERVAL_MINAQ_Y && mouseY <= INTERVAL_MAXAQ_Y)
                    {
							return;
                        if (returnToPreviousFrame)
                        {
                            returnToPreviousFrame = false;
                            SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
                            SDL_Flip(screen);
                        }
                    }
                    else if (mouseX >= INTERVAL_MINS_X && mouseX <= INTERVAL_MAXS_X && mouseY >= INTERVAL_MINS_Y && mouseY <= INTERVAL_MAXS_Y)
                    {
                        // coordonnes(mouseX,mouseY);
                        s.sauvegarderStockCSV();
                    }

                    else if (mouseX >= INTERVAL_MINL_X && mouseX <= INTERVAL_MAXL_X && mouseY >= INTERVAL_MINL_Y && mouseY <= INTERVAL_MAXL_Y)
                    {
                        s.importFromCSV();
                    }
                }
            }
        }
        SDL_BlitSurface(background, NULL, screen, NULL);
        afficherEtudiant(screen);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(textSurface1);
    SDL_FreeSurface(textSurface2);
    SDL_FreeSurface(textSurface3);
    SDL_FreeSurface(textSurface4);
    SDL_FreeSurface(textSurface5);
    TTF_CloseFont(font);
    TTF_Quit();
}



void Open()
{
    loadFont("arial.ttf");
    SDL_Surface* texteSurface = renderText("Bonjour, SDL 1.2", 255, 255, 255);
    bool isRunning = true;
    SDL_Event event;
    SDL_Surface* background = NULL;
    background = IMG_Load("2r.png");
    SDL_Surface* button = NULL;
    

    SDL_Rect addButtonRect;
    addButtonRect.x = INTERVAL_MINAP_X;
    addButtonRect.y = INTERVAL_MINAP_Y;
    addButtonRect.w = INTERVAL_MAXAP_X - INTERVAL_MINAP_X;
    addButtonRect.h = INTERVAL_MAXAP_Y - INTERVAL_MINAP_Y;

    SDL_Rect searchButtonRect;
    searchButtonRect.x = INTERVAL_MINR_X;
    searchButtonRect.y = INTERVAL_MINR_Y;
    searchButtonRect.w = INTERVAL_MAXR_X - INTERVAL_MINR_X;
    searchButtonRect.h = INTERVAL_MAXR_Y - INTERVAL_MINR_Y;

    SDL_Rect deleteButtonRect;
    deleteButtonRect.x = INTERVAL_MINS_X;
    deleteButtonRect.y = INTERVAL_MINS_Y;
    deleteButtonRect.w = INTERVAL_MAXS_X - INTERVAL_MINS_X;
    deleteButtonRect.h = INTERVAL_MAXS_Y - INTERVAL_MINS_Y;


    SDL_Rect afficherButtonRect;
     afficherButtonRect.x = INTERVAL_MINA_X;
     afficherButtonRect.y = INTERVAL_MINA_Y;
     afficherButtonRect.w = INTERVAL_MAXA_X - INTERVAL_MINA_X;
     afficherButtonRect.h = INTERVAL_MAXA_Y - INTERVAL_MINA_Y;
    SDL_BlitSurface(background, NULL, screen, NULL);
    
    SDL_Rect modiffierButtonRect;
     modiffierButtonRect.x = INTERVAL_MINM_X;
     modiffierButtonRect.y = INTERVAL_MINM_Y;
     modiffierButtonRect.w = INTERVAL_MAXM_X - INTERVAL_MINM_X;
     modiffierButtonRect.h = INTERVAL_MAXM_Y - INTERVAL_MINM_Y;
    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);

    bool isAddButtonHovered = false;
    bool isSearchButtonHovered = false;
    bool isdeleteButtonHovered = false;
    bool isafficherButtonHovered = false;
    bool ismodiffierButtonHovered = false;
      
    SDL_Surface* addButtonYellowOverlay = SDL_CreateRGBSurface(SDL_SWSURFACE, addButtonRect.w, addButtonRect.h, 32, 0, 0, 0, 0);
    Uint32 addButtonYellowColor = SDL_MapRGBA(addButtonYellowOverlay->format, 255, 255, 0, 128);
    SDL_FillRect(addButtonYellowOverlay, NULL, addButtonYellowColor);

    SDL_Surface* searchButtonYellowOverlay = SDL_CreateRGBSurface(SDL_SWSURFACE, searchButtonRect.w, searchButtonRect.h, 32, 0, 0, 0, 0);
    Uint32 searchButtonYellowColor = SDL_MapRGBA(searchButtonYellowOverlay->format, 255, 255, 0, 128);
    SDL_FillRect(searchButtonYellowOverlay, NULL, searchButtonYellowColor);
    
    
      SDL_Surface* deleteButtonYellowOverlay = SDL_CreateRGBSurface(SDL_SWSURFACE, deleteButtonRect.w, deleteButtonRect.h, 32, 0, 0, 0, 0);
    Uint32 deleteButtonYellowColor = SDL_MapRGBA(deleteButtonYellowOverlay->format, 255, 255, 0, 128);
    SDL_FillRect(deleteButtonYellowOverlay, NULL, deleteButtonYellowColor);
    
    
    SDL_Surface* afficherButtonYellowOverlay = SDL_CreateRGBSurface(SDL_SWSURFACE, afficherButtonRect.w, afficherButtonRect.h, 32, 0, 0, 0, 0);
    Uint32 afficherButtonYellowColor = SDL_MapRGBA(afficherButtonYellowOverlay->format, 255, 255, 0, 128);
    SDL_FillRect(afficherButtonYellowOverlay, NULL, afficherButtonYellowColor);
    
        SDL_Surface* modiffierButtonYellowOverlay = SDL_CreateRGBSurface(SDL_SWSURFACE, modiffierButtonRect.w, modiffierButtonRect.h, 32, 0, 0, 0, 0);
    Uint32 modiffierButtonYellowColor = SDL_MapRGBA(modiffierButtonYellowOverlay->format, 255, 255, 0, 128);
    SDL_FillRect(modiffierButtonYellowOverlay, NULL, modiffierButtonYellowColor);

  

    SDL_Surface* originalBackground = SDL_ConvertSurface(background, background->format, background->flags);

    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);

    SDL_Color textColor = { 255, 0, 0 };  
    
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
bool isAudioPlaying = false;
bool isAudioPlaying2 = false;
bool isAudioPlaying3 = false;
bool isAudioPlaying4 = false;
bool isAudioPlaying5 = false;

Mix_Chunk* soundEffect =NULL;
Mix_Chunk* soundEffect2 =NULL;

bool afficherButtonClicked = false;

soundEffect = Mix_LoadWAV("1.wav");


    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
					//coordonnes(mouseX, mouseY);
					
                    // Ajouter Etudiant:
                    if (mouseX >= addButtonRect.x && mouseX <= addButtonRect.x + addButtonRect.w &&
                        mouseY >= addButtonRect.y && mouseY <= addButtonRect.y + addButtonRect.h)
                    {
                        AjouterE();
                        if (returnToPreviousFrame)
                        {
                            returnToPreviousFrame = false;
                            SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
                            SDL_Flip(screen);
                        }
                    }

                    // Recherche Etudianr:
                    if (mouseX >= searchButtonRect.x && mouseX <= searchButtonRect.x + searchButtonRect.w && mouseY >= searchButtonRect.y && mouseY <= searchButtonRect.y + searchButtonRect.h)
						{
						RechercheEtudiant();
						if (returnToPreviousFrame)
						{
						returnToPreviousFrame = false;
						SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
						SDL_Flip(screen);
								}
						}          
						 
					 // Supprimer produit:
                if (mouseX >= INTERVAL_MINS_X && mouseX <= INTERVAL_MAXS_X && mouseY >= INTERVAL_MINS_Y && mouseY <= INTERVAL_MAXS_Y)
                {
                    Supprimer();
                    if (returnToPreviousFrame)
                    {
                        returnToPreviousFrame = false;
                        SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
                        SDL_Flip(screen);
                    }
                }

                // Afficher:
                if (mouseX >= INTERVAL_MINA_X && mouseX <= INTERVAL_MAXA_X && mouseY >= INTERVAL_MINA_Y && mouseY <= INTERVAL_MAXA_Y)
                {
                    Afficher();
                    if (returnToPreviousFrame)
                    {
                        returnToPreviousFrame = false;
                        SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
						SDL_Flip(screen);

                    }
                }
                // Modiffier:
                if (mouseX >= INTERVAL_MINM_X && mouseX <= INTERVAL_MAXM_X && mouseY >= INTERVAL_MINM_Y && mouseY <= INTERVAL_MAXM_Y)
                {
                    modifierEtudiant();
                    if (returnToPreviousFrame)
                    {
                        returnToPreviousFrame = false;
                        SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
						SDL_Flip(screen);

                    }
                }
            }
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
        	
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            if (mouseX >= addButtonRect.x && mouseX <= addButtonRect.x + addButtonRect.w &&
                mouseY >= addButtonRect.y && mouseY <= addButtonRect.y + addButtonRect.h)
            {
                if (!isAddButtonHovered)
                {
                    SDL_BlitSurface(addButtonYellowOverlay, NULL, screen, &addButtonRect);

                    texteSurface = TTF_RenderText_Solid(font, "Ajouter un Etudiant", textColor);

                    isAddButtonHovered = true;

                    if (!isAudioPlaying)
                    {
                        isAudioPlaying = true;
                        Mix_PlayChannel(-1, soundEffect, 0);
                    }
                }
            }
            else
            {
                if (isAddButtonHovered)
                {
                    SDL_BlitSurface(originalBackground, NULL, screen, NULL);

                    isAddButtonHovered = false;
                }

                if (isAudioPlaying)
                {
                    Mix_HaltChannel(-1);
                    isAudioPlaying = false;
                }
            }

            if (mouseX >= searchButtonRect.x && mouseX <= searchButtonRect.x + searchButtonRect.w &&
                mouseY >= searchButtonRect.y && mouseY <= searchButtonRect.y + searchButtonRect.h)
            {
                if (!isSearchButtonHovered)
                {
                    SDL_BlitSurface(searchButtonYellowOverlay, NULL, screen, &searchButtonRect);

                    texteSurface = TTF_RenderText_Solid(font, "Recherche", textColor);

                    isSearchButtonHovered = true;
                    if (!isAudioPlaying2)
                    {
                        isAudioPlaying2 = true;
                        Mix_PlayChannel(-1, soundEffect, 0);
                    }
                }
            }
            else
            {
                if (isSearchButtonHovered)
                {
                    SDL_BlitSurface(originalBackground, NULL, screen, NULL);

                    isSearchButtonHovered = false;
                }
                if (isAudioPlaying2)
                {
                    Mix_HaltChannel(-1);
                    isAudioPlaying2 = false;
                }
            }
            
            
            if (mouseX >= deleteButtonRect.x && mouseX <= deleteButtonRect.x + deleteButtonRect.w &&
                mouseY >= deleteButtonRect.y && mouseY <= deleteButtonRect.y + deleteButtonRect.h)
            {
                if (!isdeleteButtonHovered)
                {
                    SDL_BlitSurface(deleteButtonYellowOverlay, NULL, screen, &deleteButtonRect);

                    texteSurface = TTF_RenderText_Solid(font, "Supprimer un Etudiant", textColor);

                    isdeleteButtonHovered = true;
                    if (!isAudioPlaying3)
                    {
                        isAudioPlaying3 = true;
                        Mix_PlayChannel(-1, soundEffect, 0);
                    }
                }
            }
            else
            {
                if (isdeleteButtonHovered)
                {
                    SDL_BlitSurface(originalBackground, NULL, screen, NULL);

                    isdeleteButtonHovered = false;
                }
                if (isAudioPlaying3)
                {
                    Mix_HaltChannel(-1);
                    isAudioPlaying3 = false;
                }
            }
            
            
            //afficher hover
        if (mouseX >= afficherButtonRect.x && mouseX <= afficherButtonRect.x + afficherButtonRect.w &&
                mouseY >= afficherButtonRect.y && mouseY <= afficherButtonRect.y + afficherButtonRect.h)
            {
                if (!isafficherButtonHovered)
                {
                    SDL_BlitSurface(afficherButtonYellowOverlay, NULL, screen, &afficherButtonRect);

                    texteSurface = TTF_RenderText_Solid(font, "Lister les Etudiants", textColor);

                    isafficherButtonHovered = true;
                }
                    if (!isAudioPlaying4)
                    {
                        isAudioPlaying4 = true;
                        Mix_PlayChannel(-1, soundEffect, 0);
                    }
            }
            else
            {
                if (isafficherButtonHovered)
                {
                    SDL_BlitSurface(originalBackground, NULL, screen, NULL);

                    isafficherButtonHovered = false;
                }
                if (isAudioPlaying4)
                {
                    Mix_HaltChannel(-1);
                    isAudioPlaying4 = false;
                }
            }
            
            //ModiffierButtonHover
            
			if (mouseX >= modiffierButtonRect.x && mouseX <= modiffierButtonRect.x + modiffierButtonRect.w &&
                mouseY >= modiffierButtonRect.y && mouseY <= modiffierButtonRect.y + modiffierButtonRect.h)
            {
                if (!ismodiffierButtonHovered)
                {
                    SDL_BlitSurface(modiffierButtonYellowOverlay, NULL, screen, &modiffierButtonRect);

                    texteSurface = TTF_RenderText_Solid(font, "Modifier Etudiant", textColor);

                    ismodiffierButtonHovered = true;
                }
                    if (!isAudioPlaying5)
                    {
                        isAudioPlaying5 = true;
                        Mix_PlayChannel(-1, soundEffect, 0);
                    }
            }
            else
            {
                if (ismodiffierButtonHovered)
                {
                 
                    SDL_BlitSurface(originalBackground, NULL, screen, NULL);

                    
                    ismodiffierButtonHovered = false;
                }
               
                if (isAudioPlaying5)
                {
                    Mix_HaltChannel(-1);
                    isAudioPlaying5 = false;
                }
            }
            
        

            // Update the screen
            SDL_BlitSurface(background, NULL, screen, NULL);
            if (isAddButtonHovered)
            {
                SDL_BlitSurface(addButtonYellowOverlay, NULL, screen, &addButtonRect); 
                SDL_Rect textRect;
					textRect.x = addButtonRect.x + (addButtonRect.w - texteSurface->w) / 2; 
					textRect.y = addButtonRect.y + (addButtonRect.h - texteSurface->h) / 2;
					 SDL_BlitSurface(texteSurface, NULL, screen, &textRect); 
            }

            if (isSearchButtonHovered)
            {
                SDL_BlitSurface(searchButtonYellowOverlay, NULL, screen, &searchButtonRect);
                SDL_Rect textRect;
                textRect.x = searchButtonRect.x + (searchButtonRect.w - texteSurface->w) / 2; 
                textRect.y = searchButtonRect.y + (searchButtonRect.h - texteSurface->h) / 2; 

                SDL_BlitSurface(texteSurface, NULL, screen, &textRect); 
            }
              if (isdeleteButtonHovered)
            {
                SDL_BlitSurface(deleteButtonYellowOverlay, NULL, screen, &deleteButtonRect); 
                SDL_Rect textRect;
                textRect.x = deleteButtonRect.x + (deleteButtonRect.w - texteSurface->w) / 2;
                textRect.y = deleteButtonRect.y + (deleteButtonRect.h - texteSurface->h) / 2; 

                SDL_BlitSurface(texteSurface, NULL, screen, &textRect);
            }


       if (isafficherButtonHovered)
            {
                SDL_BlitSurface(afficherButtonYellowOverlay, NULL, screen, &afficherButtonRect);
                SDL_Rect textRect;
                textRect.x = afficherButtonRect.x + (afficherButtonRect.w - texteSurface->w) / 2; 
                textRect.y = afficherButtonRect.y + (afficherButtonRect.h - texteSurface->h) / 2;

                SDL_BlitSurface(texteSurface, NULL, screen, &textRect); 
            }
            
        if (ismodiffierButtonHovered)
            {
                SDL_BlitSurface(modiffierButtonYellowOverlay, NULL, screen, &modiffierButtonRect);
                SDL_Rect textRect;
                textRect.x = modiffierButtonRect.x + (modiffierButtonRect.w - texteSurface->w) / 2; 
                textRect.y = modiffierButtonRect.y + (modiffierButtonRect.h - texteSurface->h) / 2;

                SDL_BlitSurface(texteSurface, NULL, screen, &textRect);
            }


            SDL_Flip(screen);
        }
    }
}

		SDL_FreeSurface(background);
		SDL_FreeSurface(button);
		SDL_FreeSurface(previousFrame);
		SDL_FreeSurface(addButtonYellowOverlay);
		SDL_FreeSurface(searchButtonYellowOverlay);
		SDL_FreeSurface(originalBackground); 
		SDL_FreeSurface(texteSurface); 
		TTF_CloseFont(font);
		SDL_ShowCursor(SDL_ENABLE);
		SDL_Quit();
		cleanup();
		
}



void InterfaceP()
{
    initializeSDL();
    loadFont("arial.ttf");
    SDL_Surface* texteSurface = renderText("Bonjour, SDL 1.2", 255, 255, 255);
    bool isRunning = true;
    SDL_Event event;
    SDL_Surface* background = NULL;
    background = IMG_Load("1.png");
    SDL_Surface* pinkButton = NULL;
    pinkButton = IMG_Load("1.png");

    SDL_Rect buttonRect;
    buttonRect.x = INTERVAL_MINO_X;
    buttonRect.y = INTERVAL_MINO_Y;
    buttonRect.w = INTERVAL_MAXO_X - INTERVAL_MINO_X;
    buttonRect.h = INTERVAL_MAXO_Y - INTERVAL_MINO_Y;

    SDL_BlitSurface(background, NULL, screen, NULL);
    SDL_Flip(screen);


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	bool isAudioPlaying5 = false;
	Mix_Chunk* soundEffect5 =NULL;

// Chargement du fichier audio (hors de la boucle principale)
soundEffect5 = Mix_LoadWAV("1.wav");

    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
						//coordonnes(mouseX, mouseY);
                    if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w && mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h)
                    {
                        Open();
                        if (returnToPreviousFrame)
                        {
                            returnToPreviousFrame = false;
                            SDL_BlitSurface(previousFrame, &previousFrameRect, screen, NULL);
                        }
                    }
                }
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;

                if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w && mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h)
                {
                    SDL_Surface* pinkOverlay = SDL_CreateRGBSurface(SDL_SWSURFACE, buttonRect.w, buttonRect.h, 32, 0, 0, 0, 0);
                    Uint32 pinkColor = SDL_MapRGBA(pinkOverlay->format, 255, 192, 203, 128);
                    SDL_FillRect(pinkOverlay, NULL, pinkColor);

                    SDL_BlitSurface(pinkOverlay, NULL, pinkButton, &buttonRect);
                    SDL_SetAlpha(pinkButton, SDL_SRCALPHA, 128);

                    SDL_BlitSurface(pinkButton, &buttonRect, screen, &buttonRect);

                    SDL_Surface* buttonTextSurface = renderText("Open !", 255, 255, 255);
                    int textX = buttonRect.x + (buttonRect.w - buttonTextSurface->w) / 2;
                    int textY = buttonRect.y + (buttonRect.h - buttonTextSurface->h) / 2;
                    SDL_Rect textRect = { textX, textY, buttonTextSurface->w, buttonTextSurface->h };
                    SDL_BlitSurface(buttonTextSurface, NULL, screen, &textRect);
                    SDL_FreeSurface(buttonTextSurface);

                    SDL_FreeSurface(pinkOverlay);
                    if (!isAudioPlaying5)
                    {
                        isAudioPlaying5 = true;
                        Mix_PlayChannel(-1, soundEffect5, 0);
                    }
                }
               
               
  				else
                {
                    SDL_BlitSurface(background, NULL, screen, NULL);
                if (isAudioPlaying5)
                {
                    Mix_HaltChannel(-1);
                    isAudioPlaying5 = false;
                }
                }
            }
            
            

        }

        SDL_Flip(screen);
    }

    SDL_FreeSurface(background);
    SDL_FreeSurface(pinkButton);
    SDL_FreeSurface(previousFrame);
    SDL_ShowCursor(SDL_ENABLE);
    
    SDL_Quit();
    cleanup();
}


int main(int argc, char** argv) 

{/*
	Etudiant etudiant1("abdennour", "boumaden", 1, 20, 18.5);
	Etudiant etudiant2("rali", "lora", 2, 30, 16.5);
	Etudiant etudiant3("safi", "nirr", 3, 56, 174.5);
	
	s.ajouterEtudiant(etudiant1);
	s.ajouterEtudiant(etudiant2);
	s.ajouterEtudiant(etudiant3);
*/
	InterfaceP();
	

	return 0;
}
