#ifndef WOODY_H
# define WOODY_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <elf.h>
# include <string.h>

# define UDP "utilisation du programme: "
# define NFILE "woody_woodpacker"

int		ft_error_arg(char *udp, char *nfile);
void	ft_error_no_executable(char *file);
void	ft_error_no_right_to_read(char *file);
void	ft_error_wrong_header(char *file);
void	woody(char *file, void *file_memory);


// FOCTION DE DEBUG //

void	printStats(struct stat *sb);
void	printHeader(Elf64_Ehdr  *hdr);
void	printFileHexa(char *file, size_t size);

#endif
