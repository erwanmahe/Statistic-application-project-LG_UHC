#include "recup_donnee_brut.h"
#include "doc_regex.h"
#include "creation_bd.h"
#include <iostream>
#include <fstream>
#include <string>


int main() {

	//r�cup�ration des donn�es
	std::string chemin = "C:\\Users\\matts\\AppData\\Roaming\\.minecraft\\versions\\TEST chatlog\\chatlogs\\2025-07-27.htm";

	//initialisation
	// cr�ation base de donn�e.
	create_stats_lguhc();

	//insert une game
	insert_game(
		1,                                  // id_role
		1,                                  // camp
		"2025-10-05 21:00:00",              // start_game
		"Le village a d�couvert un loup",   // event_ingame
		1,
		"Victoire du village !"             // comment
	);

	//select all sur une table
	select_all_from_table("game"); //"game", "role", "role_camp", "gameplay"

	//cr�ation du fichier des log bruts et r�cup�ration de ces donn�es
	log_brut fichier_log(chemin);

	//teste du fichier de r�cup�ration des donn�es brut
	std::string ligne = fichier_log.give_line_kill_line();
	while (!ligne.empty()) {
		std::cout << ligne << std::endl; // Affiche chaque ligne lue
		ligne = fichier_log.give_line_kill_line();
	}

	traitement_test(); //compr�hention des regex

	return 0;
}
