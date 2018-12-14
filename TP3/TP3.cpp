// TP3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <stack>


using namespace std;

struct Node
{
	int valeur;
	Node* droite;
	Node* gauche;
};

class BST
{
public:
	Node* racine;
	vector<Node> elementsProfondeur;
	BST();
	~BST();
	void Insert(int valeur);
	void LireFichier(string fichierAOuvrir);
	void typeDeParametre(string ligne);
	void TrouverPointInsertion(int donnee, Node* &elementActuel);
	void Delete(int elementToDelete);
	vector<Node*> AfficherLesElementsNiveau(int niveauRecherche, int niveauActuel, Node *elementActuel, vector <Node*> elementsTrouves);
	void AfficherElementsArbreDecroissant(Node* elementActuel);
	int AfficherHauteurArbre(Node* elementActuel, int hauteureActuelle); //done
	vector <Node*>  AfficherAscendantsElement(int valeurRecherchee, Node* elementActuel, vector <Node*> elementsTrouves);
	void AfficherDescendantsElement(Node* elementActuel, int valeurRecherchee);
	Node* TrouverElementSelonValeur(int elementToDelete, Node* &elementActuel);
	int TrouverPlusPetitEnfantDroit(Node *& elementASupprimer);
};

BST::BST()
{
	this->racine = NULL;
	LireFichier("Arbre.txt");
}

void BST::TrouverPointInsertion(int donnee, Node* &elementActuel)
{
	if (elementActuel == NULL)
	{
		elementActuel = new Node();
		elementActuel->valeur = donnee;
	}
	else if (donnee < elementActuel->valeur)
		TrouverPointInsertion(donnee, elementActuel->gauche);
	else if (donnee > elementActuel->valeur)
		TrouverPointInsertion(donnee, elementActuel->droite);
}

void BST::Delete(int valeureASupprimer)
{
	Node *noeudASupprimer = TrouverElementSelonValeur(valeureASupprimer, racine);
	Node *temp = noeudASupprimer;
	if (noeudASupprimer->gauche == NULL)
		noeudASupprimer = noeudASupprimer->droite;
	else if (noeudASupprimer->droite == NULL)
		noeudASupprimer = noeudASupprimer->gauche;
	else
	{
		int valeur = TrouverPlusPetitEnfantDroit(noeudASupprimer->droite);
		noeudASupprimer->valeur = valeur;
		
	}
	
}

vector<Node*> BST::AfficherLesElementsNiveau(int niveauRecherche, int niveauActuel, Node * elementActuel, vector<Node*> elementsTrouves)
{
	if (elementActuel != NULL)
	{
		niveauActuel++;
		if (niveauRecherche > niveauActuel)
		{
			elementsTrouves =  AfficherLesElementsNiveau(niveauRecherche, niveauActuel, elementActuel->droite, elementsTrouves);
			elementsTrouves =  AfficherLesElementsNiveau(niveauRecherche, niveauActuel, elementActuel->gauche, elementsTrouves);
		}
		else if (niveauActuel == niveauRecherche)
		{
			back_inserter(elementsTrouves) = elementActuel;
		}
	}
	return elementsTrouves;
}

void BST::AfficherElementsArbreDecroissant(Node * elementActuel)
{
	if (elementActuel == NULL)
		return;
	AfficherElementsArbreDecroissant(elementActuel->droite);
	cout << elementActuel->valeur << endl;
	AfficherElementsArbreDecroissant(elementActuel->gauche);
}

int BST::AfficherHauteurArbre(Node * elementActuel, int hauteureActuelle)
{
	if (elementActuel != NULL)
	{
		int profondeurTrouvee = hauteureActuelle;
		int profondeurDroite = AfficherHauteurArbre(elementActuel->droite, hauteureActuelle + 1);
		int profondeurGauche = AfficherHauteurArbre(elementActuel->gauche, hauteureActuelle + 1);
		if (profondeurDroite > profondeurTrouvee)
		{
			profondeurTrouvee = profondeurDroite;
		}
		if (profondeurGauche > profondeurTrouvee)
		{
			profondeurTrouvee = profondeurGauche;
		}
		return profondeurTrouvee;
	}
	return 0;
}

vector <Node*>  BST::AfficherAscendantsElement(int valeurRecherchee, Node * elementActuel, vector <Node*> elementsTrouves)
{
	if (valeurRecherchee < elementActuel->valeur)
	{
		elementsTrouves = AfficherAscendantsElement(valeurRecherchee, elementActuel->gauche, elementsTrouves);
		back_inserter(elementsTrouves) = elementActuel;
	}
	else if (valeurRecherchee > elementActuel->valeur)
	{
		elementsTrouves = AfficherAscendantsElement(valeurRecherchee, elementActuel->droite, elementsTrouves);
		back_inserter(elementsTrouves) = elementActuel;
	}
	return elementsTrouves;
}

void BST::AfficherDescendantsElement(Node* elementActuel, int valeurRecherchee)
{
	if (elementActuel == NULL)
		return;
	if (elementActuel->valeur != valeurRecherchee)
		cout << elementActuel->valeur << endl;
	AfficherDescendantsElement(elementActuel->droite, valeurRecherchee);
	AfficherDescendantsElement(elementActuel->gauche, valeurRecherchee);
}

Node * BST::TrouverElementSelonValeur(int elementRecherche, Node* &elementActuel)
{
	if (elementActuel->valeur == elementRecherche)
			return elementActuel;
	else if (elementRecherche < elementActuel->valeur)
		return TrouverElementSelonValeur(elementRecherche, elementActuel->gauche);
	else if (elementRecherche > elementActuel->valeur)
		return 	TrouverElementSelonValeur(elementRecherche, elementActuel->droite);
	return nullptr;
}

int BST::TrouverPlusPetitEnfantDroit(Node *& elementASupprimer)
{
	if (elementASupprimer->droite != NULL)
	{
		return TrouverPlusPetitEnfantDroit(elementASupprimer->gauche);
	}
	int valeurRetour = elementASupprimer->valeur;
	elementASupprimer = NULL;
	return valeurRetour;
}

void BST::Insert(int valeur)
{
	TrouverPointInsertion(valeur, racine);
}

void BST::LireFichier(string fichierAOuvrir)
{	
	fstream entree;
	string ligne;

	entree.open(fichierAOuvrir, ios::in);
	if (!entree.fail()) {
		while (!entree.eof())
		{
			getline(entree, ligne);
			typeDeParametre(ligne);
		}
	}
	else
	{
		cout << "file not found" << endl;
	}
	entree.close();

}
	
void BST::typeDeParametre(string ligne)
{
	string parametreDAction = ligne.substr(0, 1);

	if (parametreDAction == "I")
	{
		int longeur = ligne.length() - 2;
		string argument = ligne.substr(2, ligne.length() - 2);
		int valeur = std::stoi(argument);
		Insert(valeur);		
	}
	else if (parametreDAction == "D")
	{
		int longeur = ligne.length() - 2;
		string argument = ligne.substr(2, ligne.length() - 2);
		int valeur = std::stoi(argument);
		Delete(valeur);
	}
	else if (parametreDAction == "N")
	{
		string argument = ligne.substr(2, 1);
		int valeur = std::stoi(argument);
		vector<Node*> elements = AfficherLesElementsNiveau(valeur, 0, racine, elements);
		cout << "Les elements du niveau " << valeur << " sont:" << endl;
		for (int i = 0; i < elements.size(); i++)
		{
			cout << elements[i]->valeur << endl;
		}
	}
	else if (parametreDAction == "P")
	{
		AfficherElementsArbreDecroissant(racine);
	}
	else if (parametreDAction == "H")
	{
		cout << "profondeur de l'arbre: " << AfficherHauteurArbre(racine, 1) << endl;

	}
	else if (parametreDAction == "A")
	{
		string argument = ligne.substr(2, 1);
		int valeur = std::stoi(argument);
		vector<Node*> elementsAscendants;
		elementsAscendants = AfficherAscendantsElement(valeur, racine, elementsAscendants);
		cout << "Les elements ascendants à " << valeur << " sont:" << endl;
		for (int i = 0; i < elementsAscendants.size(); i++)
		{
			cout << elementsAscendants[i]->valeur << endl;
		}
	}
	else if (parametreDAction == "C")
	{
		string argument = ligne.substr(2, 1);
		int valeur = std::stoi(argument);
		AfficherDescendantsElement(racine, valeur);
	}
	
}

int main()
{
	BST* monArbre = new BST;
	
	vector<Node*> elements = monArbre->AfficherLesElementsNiveau(2, 0, monArbre->racine,elements);
	monArbre-> AfficherElementsArbreDecroissant(monArbre->racine);
	
	Node* elementRecherche =monArbre->TrouverElementSelonValeur(11, monArbre-> racine);
	monArbre->AfficherDescendantsElement(elementRecherche, 11);

	vector<Node*> elementsAscendants;
	elementsAscendants = monArbre->AfficherAscendantsElement(11, monArbre->racine, elementsAscendants);
	
	std::cout << "Hello World!\n";
}


