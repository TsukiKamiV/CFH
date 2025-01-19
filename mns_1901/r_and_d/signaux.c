/*
    Petit programme pour voir comment marche la gestion des signaux en C avec sigaction (et non signal)
*/

#include <signal.h> // sigaction et sigset_t
#include <stdio.h>
#include <unistd.h> //usleep


void    signal_handling(int signal_code)
{
    if (signal_code == SIGINT)
    {
        printf("Signal CTRL + C detected\n");
    }
    else
        printf("Signal not known\n");
}

int main(void)
{
    struct sigaction sig_config; // Structure pour configurer sigaction
    sigset_t signal_set; // Ensemble de macros pour gerer les valeurs des signaux

    sig_config.sa_handler = signal_handling; // Associer notre fonction de gestion de signaux a sigaction
    sig_config.sa_flags = 0; // Les flags correspondent a des comportements, 0 signifie qu'on en veut aucun (a voir les autres !)

    sigemptyset(&signal_set); // Vider au debut le set de codes qui representent les signaux
    sigaddset(&signal_set, SIGINT); // On ajoute le signal SIGINT a notre set
    sig_config.sa_mask = signal_set; // On ajoute ici notre set pour indiquer a sigaction quels signaux gerer nous meme

    /*Configurer SIGINT avec sigaction - A APPROFONDIR SUR LA FONCTION SIGACTION + PARAMS*/
    if (sigaction(SIGINT, &sig_config, NULL) == -1)
    {
        printf("Error when calling sigaction");
        return (1);
    }

    // Boucle de test (Attention il faudra fermer le terminal car CTRL C ou D ne marcheront pas)
    while(1)
    {
        printf("Running... Waiting for a signal...\n");
        usleep(1000000);
    }
    return (0);

}