#include"GLOBAL.H"

void main()
{
	SetSVGA64k();

	bar1(150, 300, 450, 500, 15);

	while(1);
	CloseSVGA();
}