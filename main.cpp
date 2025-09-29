#include "recup_donnee_brut.h"
#include "doc_regex.h"
#include <iostream>
#include <fstream>
#include <string>


int main() {

	//r�cup�ration des donn�es
	std::string chemin = "C:\\Users\\matts\\AppData\\Roaming\\.minecraft\\versions\\TEST chatlog\\chatlogs\\2025-07-27.htm";

	//initialisation
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
