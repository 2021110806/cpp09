#include "RPN.hpp"

void main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "[ERROR] Invalid usage" << std::endl;
		return ;
	}
	RPN rpn;
	rpn.play(argv[1]);
	return ;
}