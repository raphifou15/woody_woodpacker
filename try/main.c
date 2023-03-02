#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define RED     "\e[0;31m"
#define RESET   "\e[0m"


// Cette fonction ouvre un fichier au chemin indiqué et
// enregistre les données dans data.
// retourne data.
void * openSaveData(char *file, void *data, int *res){
    (void) file;
    (void)res;
    return (data);
}

int wooddyWoodPacker(char *file){
    void    *data = NULL;
    int     res = 0;
    data = openSaveData(file, data, &res);
    return(res);
}

// check le bon nombre d'argument et lance le progamme //
int main(int ac, char *av[]){
    int res = 0;

    if (ac != 2){
        fprintf(stderr, "%sWrong usage of %s\n%s", RED,av[0],RESET);
        return(EINVAL);
    }
    res = wooddyWoodPacker(av[1]);
    return (res);
}