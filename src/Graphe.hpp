#pragma once

#include "PElement.hpp"
#include "GElement.hpp"
#include "Arete.hpp"
#include "Sommet.hpp"

template <class S, class T>
class Graphe {
protected:
	int prochaineClef;
public:

	PElement< Sommet<T> > * lSommets; // liste de sommets
	PElement< Arete<S,T> > * lAretes; // liste d'arêtes

	/**
	 * crée un graphe vide
	 * */
	Graphe();

	/**
	 * constructeur de copie obligatoire car la classe comporte une partie dynamique
	 * */
	Graphe(const Graphe<S,T> & graphe);

	/**
	 * opérateur = obligatoire car la classe comporte une partie dynamique
	 * */
	const Graphe<S,T> & operator = (const Graphe<S,T> & graphe);

	/**
	 * destructeur obligatoire car la classe comporte une partie dynamique
	 * */
	~Graphe();

	int nombreSommets() const;
	int nombreAretes() const;

	/**
	 * crée un sommet isolé
	 * */
	Sommet<T> * creeSommet(const T & info);

	/**
	 * crée une arête joignant les 2 sommets debut et fin
	 *
	 * * met à jour les champs degré de debut et de fin
	 * */
	Arete<S,T> * creeArete( Sommet<T> * debut, Sommet<T> * fin, const S & info);

	/**
	 recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
	 */
	PElement<pair<Sommet<T> *, Arete<S,T>* > >  * adjacences(const Sommet<T> * sommet) const;

	PElement<pair<Sommet<T> *, Arete<S,T>* > > * predecesseurs(const Sommet<T> * sommet) const;

	PElement<pair<Sommet<T> *, Arete<S,T>* > > * successeurs(const Sommet<T> * sommet) const;

	int degrePlus(const Sommet<T>& i) const;
	int degreMoins(const Sommet<T>& i) const;

	operator string() const;

	/**
	 * cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
	 *
	 * DONNEES : s1 et s2 deux sommets quelconques du graphe
	 * RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
	 *
	 * */
	Arete<S,T> * getAreteParSommets( const Sommet<T> * s1, const Sommet<T> * s2) const;


	//---------------------- Graphe ----------------------------------
};