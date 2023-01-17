#ifndef WOODY_H
# define WOODY_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# define UDP "utilisation du programme: "
# define NFILE "woody_woodpacker"

int		ft_error_arg(char *udp, char *nfile);
void	ft_error_no_executable(char *file);
void	check_info_file(char *file);


// FOCTION DE DEBUG //

void	printStats(struct stat *sb);

#endif
