#include "traitement_donnees.h"

std::array<std::string, 4> treatement_lguhc(std::array<std::string, 4> &result,log_brut &data_brut, std::string &str_actual, std::array<std::regex, 2> &liste_reg, bool disconnected)
{
    std::smatch matches;

    std::cout << "entr� traitement de donn�e lguhc";
    while (!data_brut.empty() && !disconnected)
    {
        while (std::regex_search(str_actual, matches, liste_reg[1]))
        {

        }
    }
    return result;
}




data_game main_treatement(log_brut &data_brut)
{
    std::array<std::regex, 2> liste_reg{
    std::regex(R"(\[(\d{2}:\d{2}:\d{2})\].*?UHC.*?Bienvenue dans cette partie de.*?(LG UHC))"),
    std::regex(R"(\[(\d{2}:\d{2}:\d{2})\].*?<span style="color: #555;">� <\/span>.*?<span style="color: #AAA;">Vous �tes <\/span>.*?<span[^>]*>([^<]+)<\/span>)")
    }; //0=reg_startgame, 1 = reg_role

    std::array<std::string, 4> result;//0 = start_game, 1 = role, 2 = winning_camp, 3 = event_game

    std::smatch matches;

    std::cout << "entr� main_treatement";

    //data_game(std::time_t timestamp, std::string & role, std::string & winning_camp)

    bool disconnected = false;

    std::string str_actual = data_brut.give_line_kill_line();

    while (!data_brut.empty() && !disconnected)
    {
        while(std::regex_search(str_actual, matches, liste_reg[0]))
            
        str_actual = data_brut.give_line_kill_line();


            if(matches.str(2)=="LG UHC")
            {
                std::cout << "entr� if pour regex start game";

                // -> premi�re d�tection : partie commence
                result[0] = matches.str(1);
                if (matches.str(2) == "LG UHC")//pas sure du "lg" peut etre lguhc
                    treatement_lguhc(result, data_brut, str_actual, liste_reg, disconnected);
            }
        
    }


    //else if (!role_given)
    //{
    //    if (std::regex_search(str_actual, matches, reg_role))
    //    {
    //        // -> Ici tu fais ton traitement sp�cial avec le 2e regex
    //        result[1] = matches.str(2);
    //    }
    //    }







    return data_game();
}
