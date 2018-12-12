// TP3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <vector>
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
	void TrouverPointInsertion(int donnee, Node* &elementActuel);
	void Delete(int elementToDelete);
	vector<Node*> AfficherLesElementsNiveau(int niveauRecherche, int niveauActuel, Node *elementActuel, vector <Node*> elementsTrouves);
	void AfficherElementsArbreDecroissant(Node* elementActuel);
	int AfficherHauteurArbre(Node* elementActuel, int hauteureActuelle); //done
	void AfficherAscendantsElement(int valeurRecherchee, Node* elementActuel);
	void AfficherDescendantsElement(Node* elementActuel, int valeurRecherchee);
	Node* TrouverElementSelonValeur(int elementToDelete, Node* &elementActuel);
	int TrouverPlusGrandEnfantGauche(Node * elementASupprimer);
};

BST::BST()
{
	this->racine = NULL;
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
		int valeur = TrouverPlusGrandEnfantGauche(noeudASupprimer);
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

void BST::AfficherAscendantsElement(int valeurRecherchee, Node * elementActuel)
{
	if (valeurRecherchee < elementActuel->valeur)
	{
		//AM here
		AfficherAscendantsElement(valeurRecherchee, elementActuel->gauche)
	}
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

int BST::TrouverPlusGrandEnfantGauche(Node * elementASupprimer)
{
	if (elementASupprimer->gauche != NULL)
	{
		return TrouverPlusGrandEnfantGauche(elementASupprimer->gauche);
	}
	int valeurRetoutr = elementASupprimer->valeur;
	delete elementASupprimer;
	return valeurRetoutr;
}

void BST::Insert(int valeur)
{
	TrouverPointInsertion(valeur, racine);
}

int main()
{
	BST* monArbre = new BST;
	monArbre->Insert(5);
	monArbre->Insert(10);
	monArbre->Insert(9);
	monArbre->Insert(4);
	monArbre->Insert(11);
	monArbre->Insert(14);
	monArbre->Insert(13);
	cout << "profondeur de l'arbre: " << monArbre->AfficherHauteurArbre(monArbre->racine, 1) << endl;
	//monArbre->Delete(10);
	
	vector<Node*> elements = monArbre->AfficherLesElementsNiveau(2, 0, monArbre->racine,elements);
	monArbre-> AfficherElementsArbreDecroissant(monArbre->racine);
	
	Node* elementRecherche =monArbre->TrouverElementSelonValeur(11, monArbre-> racine);
	monArbre->AfficherDescendantsElement(elementRecherche, 11);
	
	std::cout << "Hello World!\n";
}
/*
(x)	1. Insérer un élément donné dans cet arbre.
(x)	2. Supprimer un élément donné de cet arbre.
(x)	3. Afficher les éléments d’un niveau donnéen utilisant une file; la racine étant au niveau 1.
(x) 4. Afficher les éléments de l’arbre dans l’ordre décroissant.
(x)	5. Afficher la hauteur de cet arbre, en convenant qu’un nœud vide est de hauteur 0.
 6. Afficher les ascendants d’un élément donné en utilisant une pile (bonus). 10%
(x) 7. Afficher les descendants d’un élément donné.
*/