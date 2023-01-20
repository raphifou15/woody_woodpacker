#include "./woodyWoodPacker.h"

void	check_if_file_correct(char *file, void *file_memory){
	struct stat	sb;
	int			fd;
	Elf64_Ehdr	*hdr;
	char		*hdr2;

	if (!(stat(file, &sb) == 0 && sb.st_mode & S_IXUSR))
		ft_error_no_executable(file);
	printStats(&sb);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error_no_right_to_read(file);
	if ((hdr2 = malloc(sizeof(char) * sb.st_size + 1)) == NULL)
		exit(1);
	file_memory = mmap(0, sb.st_size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	read(fd, hdr2, sb.st_size);
	hdr2[sb.st_size] = '\0';
	close(fd);
	printFileHexa(file_memory, sb.st_size); //debug
	printFileHexa(hdr2, sb.st_size); //debug
	hdr = (Elf64_Ehdr *)file_memory;
	printHeader(hdr); //debug
	if (!(strncmp((char *)hdr, ELFMAG, SELFMAG) == 0 && hdr->e_ident[4] == ELFCLASS64))
		ft_error_wrong_header(file);
	//e_type : identifie le type de fichier. ex : un exécutable ou un fichier objet partagé
	// du coup mettre une protection
	free(hdr2);
	munmap(file_memory, sb.st_size);
}

int	main(int ac, char *av[]) {
	void *file_memory;
	
	file_memory = NULL;
	if (ac != 2)
		return ft_error_arg(UDP, av[0]);
	check_if_file_correct(av[1], file_memory);
	return 0;
}

//MMAP//
//un moyen pratique d'accéder au contenu d'un fichier//
//
