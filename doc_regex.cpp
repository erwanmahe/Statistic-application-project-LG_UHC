#include "doc_regex.h"


void print_start(std::string str, std::regex reg)
{
	std::cout << "entr� dans le print_start \n";
	std::smatch matches;
	std::cout << std::boolalpha;
	while (std::regex_search(str, matches, reg))
	{
		std::cout << "Heure : " << matches.str(1) << "\n";
		std::cout << "Mod�le : " << matches.str(2) << "\n\n";
		str = matches.suffix().str();
	}
}

void print_matches2(std::string str, std::regex reg)
{
	std::sregex_iterator current_match(str.begin(), str.end(), reg);
	std::sregex_iterator last_match;
	while (current_match != last_match)
	{
		std::smatch match = *current_match;
		std::cout << match.str() << "\n";
		current_match++;
	}
	std::cout << std::endl;
}

void print_matches(std::string str, std::regex reg)
{
	std::smatch matches;
	std::cout << std::boolalpha; //�a fait en sorte que la console montre des true et false au lieu de 0 et 1 avec les strings
	std::vector<std::string> result;
	while (std::regex_search(str, matches, reg))
	{
		std::cout << "is there a match : " << matches.ready() << "\n"; //�a mets true ou false si il y a un matche ou non
		std::cout << "are there no matches : " << matches.empty() << "\n"; //�a mets true ou false si il n'y a pas de matche ou non (pas de match = true)
		std::cout << "how many matches : " << matches.size() << "\n"; //�a mets le nombre de matches
		std::cout << matches.str(1) << "\n"; //print le r�sultat trouv�
		result.push_back(matches.str(1));
		str = matches.suffix().str();   //suprime le r�sultat trouv� pour npasser aux prochain 
		//(si on le fait pas regex_search ne continura pas son chemin et fera une boucle infini (c'est pour �a je stock dans un vector))
		std::cout << "\n";
	}
	for (auto ele : result)
	{
		std::cout << ele << " ";
	}
	std::cout << "\n";
}

int traitement_test()
{
	//std::cout << "premier ex : \n";
	//std::string str = "The ape was at the apex";
	//std::regex reg("(ape[^ ]?)");
	//	//�a cherche tout ce qui commence avec "ape"
	//	//		plus de pr�cision :
	//	//				la paranth�se c pour montrer ce que l'on doit chercher donc l� �a commence avec "ape"
	//	//				les crochet et chapeau eux sont pour dire que l'on veut n'importe quel caractere � part un espace
	//	//				le point d'int�rogation sert � dire que l'on ne connais pas forc�ment la fin du mot donc on pourra aussi r�cup�rer "apex"
	//	//
	//	//r�sum� : c pour chercher "ape" et chercher aussi "apex" donc "ape" + qqch qui n'est pas un espace
	//print_matches(str, reg);
	//
	//std::cout << "deuxi�me ex : \n";
	//std::string str2 = "I picked the pickle";
	//std::regex reg2("(pick([^ ]+)?)"); 
	//// le + c pour dire qu'il y aura plus d'un lettre inconnue dans le ?
	//print_matches2(str2, reg2);
	//
	//std::cout << "troisi�me ex : \n";
	//std::string str3 = "cat rat mat fat pat at";
	//std::regex reg3("([crmp]at)");
	////�a r�cup�rera tout les mot o� la premi�re lettre correspond � une des lettres entre crochets mais donc ne r�cup�rera ni "fat" ni "at"
	//print_matches2(str3, reg3);
	//
	//std::cout << "quatri�me ex : \n";
	//std::regex reg4("([F-Zf-z]at)");
	////�a r�cup�rera tout les mot o� la premi�re lettre correspond � une des ranges "D-F" lettres entre crochets mais donc ne r�cup�rera ni "cat" ni "at"
	//print_matches2(str3, reg4);
	//
	//std::cout << "cinqui�me ex : \n";
	//std::regex reg5("([^cr]at)");
	////�a r�cup�rera tout les mot o� la premi�re lettre ne correspond pas aux lettres entre crochets et inclus donc aussi "at"
	//print_matches2(str3, reg5);
	//
	//std::cout << "sixi�me ex : \n";
	////\s [\f\n\r\t\v]
	//std::string str6 = "mayorie may";
	//std::regex reg6("\\w{2,20}\\s\\w{2}");
	//print_matches2(str6, reg6);

	std::cout << "start game : \n";
	std::string str7 = "<code><span>[14:27:08] </span><span></span><span style=\"color: #555;\">[</span><span></span><span style=\"color: #FF5;\">UHC</span><span></span><span style=\"color: #555;\">]</span><span></span><span style=\"color: #000;\"> </span><span></span><span style=\"color: #000;\">Bienvenue dans cette partie de </span><span></span><span style=\"color: #55F;\">LG UHC S10.5  </span><span></span></code><br>";
	std::regex reg7(R"(\[(\d{2}:\d{2}:\d{2})\].*?UHC.*?Bienvenue dans cette partie de.*?(LG UHC S\d+\.\d+))");
	print_start(str7, reg7);

	std::cout << "le role : \n";
	std::string str8 = "<code><span>[14:47:08] </span><span> </span><span></span><span style=\"color: #555;\">� </span><span></span><span style=\"color: #AAA;\">Vous �tes </span><span></span><span style=\"color: #5F5;\">Soeur</span><span></span></code><br>";
	std::regex reg8(R"(\[(\d{2}:\d{2}:\d{2})\].*?<span style="color: #555;">� <\/span>.*?<span style="color: #AAA;">Vous �tes <\/span>.*?<span[^>]*>([^<]+)<\/span>)");
	print_start(str8, reg8);

	return 0;
}



void traitement(log_brut log, std::string str_log_actuelle)
{
	std::smatch matches;
	//recherche du start de la game
	static std::regex reg_start(R"(\[(\d{2}:\d{2}:\d{2})\].*?UHC.*?Bienvenue dans cette partie de.*?(LG UHC S\d+\.\d+))");
	while (std::regex_search(str_log_actuelle, matches, reg_start))
	{
		std::cout << "Heure : " << matches.str(1) << "\n";
		std::cout << "Mod�le : " << matches.str(2) << "\n\n";
		str_log_actuelle = matches.suffix().str();
	}
}


//std::cout << "start game : \n";
//std::string str7 = "<code><span>[14:27:08] </span><span></span><span style=\"color: #555;\">[</span><span></span><span style=\"color: #FF5;\">UHC</span><span></span><span style=\"color: #555;\">]</span><span></span><span style=\"color: #000;\"> </span><span></span><span style=\"color: #000;\">Bienvenue dans cette partie de </span><span></span><span style=\"color: #55F;\">LG UHC S10.5  </span><span></span></code><br>";
//std::regex reg7(R"(\[(\d{2}:\d{2}:\d{2})\].*?UHC.*?Bienvenue dans cette partie de.*?(LG UHC S\d+\.\d+))");
//print_start(str7, reg7);
//
//std::cout << "le role : \n";
//std::string str8 = "<code><span>[14:47:08] </span><span> </span><span></span><span style=\"color: #555;\">� </span><span></span><span style=\"color: #AAA;\">Vous �tes </span><span></span><span style=\"color: #5F5;\">Soeur</span><span></span></code><br>";
//std::regex reg8(R"(\[(\d{2}:\d{2}:\d{2})\].*?<span style="color: #555;">� <\/span>.*?<span style="color: #AAA;">Vous �tes <\/span>.*?<span[^>]*>([^<]+)<\/span>)");
//print_start(str8, reg8);