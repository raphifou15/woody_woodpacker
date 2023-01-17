#include "./woodyWoodPacker.h"

int	ft_error_arg(char *udp, char *nfile) {
	dprintf(2, "%s\n%s avec un argument qui doit etre un executable\n",udp,nfile);
	return (1);
}

void ft_error_no_executable(char *file) {
	dprintf(2, "%s: n'est pas un executable\n", file);
	ft_error_arg(UDP, NFILE);
	exit(1);
}
