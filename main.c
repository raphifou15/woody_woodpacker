#include "./woodyWoodPacker.h"

void	woody(char *file, void *file_memory){
	struct stat	sb;
	int			fd;
	int			fd2;
	Elf64_Ehdr	*hdr;
	//char		*hdr2;

	if (!(stat(file, &sb) == 0 && sb.st_mode & S_IXUSR))
		ft_error_no_executable(file);
	printStats(&sb);
	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error_no_right_to_read(file);
	//if ((hdr2 = malloc(sizeof(char) * sb.st_size + 1)) == NULL)
	//	exit(1);
	if ((file_memory = mmap(0, sb.st_size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED){
		printf("Map failed\n");
		exit(1);
	}
	//read(fd, hdr2, sb.st_size);
	//hdr2[sb.st_size] = '\0';
	printFileHexa(file_memory, sb.st_size); //debug
	//printFileHexa(hdr2, sb.st_size); //debug
	hdr = (Elf64_Ehdr *)file_memory;
	printHeader(hdr); //debug
	if (!(strncmp((char *)hdr, ELFMAG, SELFMAG) == 0 && hdr->e_ident[4] == ELFCLASS64))
		ft_error_wrong_header(file);
	//e_type : identifie le type de fichier. ex : un exécutable ou un fichier objet partagé
	// du coup mettre une protection

	// parcourir le nombre de segment d'un fichier elf64 //
	Elf64_Phdr	*segPhdr = (Elf64_Phdr *)((unsigned char *)(hdr) + (unsigned int)hdr->e_phoff);
	for (int i = 0; i < (int)hdr->e_phnum; i++){
		printf("i = %d\n", i);
		if (segPhdr->p_type == 1 && (segPhdr->p_flags == 1 || segPhdr->p_flags == 3 || segPhdr->p_flags == 5)){
			printf("found PT_LOAD avec des droits d'execution\n");
		}
		printf("segment p_type: %x\n", segPhdr->p_type);
		printf("segment p_flags: %d\n", segPhdr->p_flags);
		printf("segment p_filesz: %ld\n", segPhdr->p_filesz);
		printf("segment p_memsz: %ld\n", segPhdr->p_memsz);
		printf("segment p_offset: %ld\n", segPhdr->p_offset);
		segPhdr = (Elf64_Phdr *)((unsigned char *)(segPhdr) + (unsigned int)(hdr->e_phentsize));
	}


	void *lala = malloc((size_t)sb.st_size);
	memcpy(lala, file_memory,(size_t)sb.st_size);



	if (!(fd2 = open("Woody", O_RDWR | O_CREAT | O_TRUNC, 0777))){
		exit(1);
	}
	write(fd2, lala, (size_t)sb.st_size + 1);
	close(fd);
	close(fd2);
	free(lala);
	munmap(file_memory, sb.st_size + 1);

}

int	main(int ac, char *av[]) {
	void *file_memory;
	
	file_memory = NULL;
	if (ac != 2)
		return ft_error_arg(UDP, av[0]);
	woody(av[1], file_memory);
	return 0;
}

//MMAP//
//un moyen pratique d'accéder au contenu d'un fichier//
//
