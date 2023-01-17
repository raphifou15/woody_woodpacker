#include "./woodyWoodPacker.h"

void	check_info_file(char *file){
	struct stat sb;
	if (!(stat(file, &sb) == 0 && sb.st_mode & S_IXUSR))
		ft_error_no_executable(file);
	
}


int	main(int ac, char *av[]) {
	if (ac != 2)
		return ft_error_arg(UDP, av[0]);
	check_info_file(av[1]);
	return 0;
}
