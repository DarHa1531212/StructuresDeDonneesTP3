/************************************************************
*	Nom: Hans Darmstadt-Bélanger							*
*	Date: 14 Décembre 2018									*
*	But: Créer un programme qui construit et gère un ABR	*
*************************************************************/

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

/// <summary>
/// La structure Noeud contient une valeur et un pointeur vers les Node droite et gauche suivantes
/// </summary>
struct Node
{
	int valeur;
	Node* droite;
	Node* gauche;
};

/// <summary>
/// La classe BST représente l'arbre binaire de recherche et contient toutes les fonctions qui traitent à l'arbre
/// </summary>
class BST
{
public:
	Node* racine;
	vector<Node> elementsProfondeur;
	BST();
	void Insert(int valeur, Node * &elementActuel);
	void LireFichier(string fichierAOuvrir);
	void typeDeParametre(string ligne);
	void Delete(int elementToDelete);
	vector<Node*> AfficherLesElementsNiveau(int niveauRecherche, int niveauActuel, Node *elementActuel, vector <Node*> elementsTrouves);
	void AfficherElementsArbreDecroissant(Node* elementActuel);
	int AfficherHauteurArbre(Node* elementActuel, int hauteureActuelle); //done
	vector <Node*>  AfficherAscendantsElement(int valeurRecherchee, Node* elementActuel, vector <Node*> elementsTrouves);
	void AfficherDescendantsElement(Node* elementActuel, int valeurRecherchee);
	Node* TrouverElementSelonValeur(int elementToDelete, Node* &elementActuel);
	int TrouverPlusPetitEnfantDroit(Node *& elementASupprimer);
};

/// <summary>
/// Initialise une nouvelle instance de la classe <see cref="BST"/> 
/// </summary>
BST::BST()
{
	this->racine = NULL;
	LireFichier("Arbre.txt");
}

/// <summary>
/// Supprime une valeur de l'arbre selon la valeur à supprimer.
/// </summary>
/// <param name="valeureASupprimer">La valeur à supprimer.</param>
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

/// <summary>
/// Affichers les elements d'un niveau donné.
/// </summary>
/// <param name="niveauRecherche">Le niveau recherché.</param>
/// <param name="niveauActuel">Le niveau actuellement atteint avec le parcour récursif de l'arbre.</param>
/// <param name="elementActuel">L'élément actuellement atteint par le parcour.</param>
/// <param name="elementsTrouves">La liste des éléments trouvés au niveau recherché.</param>
/// <returns>La liste des éléments trouvés qui est mise à jour si l'élément actuel est du niveau recherché.</returns>
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

/// <summary>
/// Affichers les elements de l'arbre en ordre decroissant.
/// </summary>
/// <param name="elementActuel">L'element actuel.</param>
void BST::AfficherElementsArbreDecroissant(Node * elementActuel)
{
	if (elementActuel == NULL)
		return;
	AfficherElementsArbreDecroissant(elementActuel->droite);
	cout << elementActuel->valeur << endl;
	AfficherElementsArbreDecroissant(elementActuel->gauche);
}

/// <summary>
/// Affiche la hauteur de arbre.
/// </summary>
/// <param name="elementActuel">L'element actuel.</param>
/// <param name="hauteureActuelle">La hauteure actuellement atteinte par le parcour récursif de l'arbre.</param>
/// <returns>Retourne la plus grande profondeur trouvée en comparant les profondeurs des sous-arbres droits et gauches</returns>
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

/// <summary>
/// Affiche les ascendants d'un element.
/// </summary>
/// <param name="valeurRecherchee">La valeur recherchée.</param>
/// <param name="elementActuel">L'element actuel.</param>
/// <param name="elementsTrouves">La liste des éléments trouvée.</param>
/// <returns>La liste des éléments trouvés mis à jour </returns>
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

/// <summary>
/// Affiche les descendants d'un element.
/// </summary>
/// <param name="elementActuel">L'element actuel.</param>
/// <param name="valeurRecherchee">La valeur recherchée.</param>
void BST::AfficherDescendantsElement(Node* elementActuel, int valeurRecherchee)
{
	if (elementActuel == NULL)
		return;
	if (elementActuel->valeur != valeurRecherchee)
		cout << elementActuel->valeur << endl;
	AfficherDescendantsElement(elementActuel->droite, valeurRecherchee);
	AfficherDescendantsElement(elementActuel->gauche, valeurRecherchee);
}

/// <summary>
/// Trouve un element selon sa valeur.
/// </summary>
/// <param name="elementRecherche">La valeur de l'element recherché</param>
/// <param name="elementActuel">L'element actuellement atteint par le parcour récursif de l'arbre.</param>
/// <returns>Un pointeur vers l'element recherché.</returns>
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

/// <summary>
/// Trouve le plus petit enfant droit d'un élément.
/// </summary>
/// <param name="elementActuel">L'élément dont on cherche le plus petit enfant droit.</param>
/// <returns>La valeur du plus petit enfant droit.</returns>
int BST::TrouverPlusPetitEnfantDroit(Node *& elementActuel)
{
	if (elementActuel->droite != NULL)
	{
		return TrouverPlusPetitEnfantDroit(elementActuel->gauche);
	}
	int valeurRetour = elementActuel->valeur;
	elementActuel = NULL;
	return valeurRetour;
}

/// <summary>
/// Insert la valeur spéciffiée dans l'arbre.
/// </summary>
/// <param name="valeur">La valeur à insérer.</param>
/// <param name="elementActuel">L'élément actuellement atteint par le parcour de l'arbre.</param>
void BST::Insert(int valeur, Node * &elementActuel)
{
	if (elementActuel == NULL)
	{
		elementActuel = new Node();
		elementActuel->valeur = valeur;
	}
	else if (valeur< elementActuel->valeur)
		Insert(valeur, elementActuel->gauche);
	else if (valeur > elementActuel->valeur)
		Insert(valeur, elementActuel->droite);
}

/// <summary>
/// Lis le fichier en boucle jusqu'à en atteindre la fin.
/// </summary>
/// <param name="fichierAOuvrir">Le fichier à ouvrir.</param>
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
	
/// <summary>
/// Appelle la fonction pertinante selon la ligne d'action lue dans le fichier
/// </summary>
/// <param name="ligne">La ligne lue.</param>
void BST::typeDeParametre(string ligne)
{
	string parametreDAction = ligne.substr(0, 1);

	if (parametreDAction == "I")
	{
		int longeur = ligne.length() - 2;
		string argument = ligne.substr(2, ligne.length() - 2);
		int valeur = std::stoi(argument);
		Insert(valeur, racine);		
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
		cout << "les elements de l'arbre dans l'ordre décroissant sont: " << endl;
		AfficherElementsArbreDecroissant(racine);
	}
	else if (parametreDAction == "H")
	{
		cout << "profondeur de l'arbre: " << AfficherHauteurArbre(racine, 1) << endl;

	}
	else if (parametreDAction == "A")
	{
		int longeur = ligne.length() - 2;
		string argument = ligne.substr(2, ligne.length() - 2);
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
		int longeur = ligne.length() - 2;
		string argument = ligne.substr(2, ligne.length() - 2);
		int valeur = std::stoi(argument);
		Node* elementRecherche = TrouverElementSelonValeur(valeur, racine);
		cout << "les descendants de " << valeur << " sone: " << endl;
		AfficherDescendantsElement(elementRecherche, valeur);
	}
	
}

/// <summary>
/// Le point d'entrée du programme.
/// </summary>
/// <returns>0 en cas d'execution normale du programme</returns>
int main()
{
	BST* monArbre = new BST;

	system("PAUSE");
	return 0;
}


