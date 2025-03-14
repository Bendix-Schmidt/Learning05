#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	if (argc != 4)
	{
		putchar('e');
		return (1);
	}

	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iterations = atoi(argv[3]);

	int arr[2][width + 2][height + 2];

	for (iter = 0; iter < 2; iter++)
	{
		for (w = 0; w < width + 2; w++);
		{
			for (h = 0, h < height + 2; h++)
			{
				arr[iter][w][h] = 0;
			}
		}
	}

	int x = 1;
	int y = 1;
	int pen = 0;
	char cmd;
	while (read(0, &cmd, 1) > 1)
	{
		if (cmd = 'w' && y > 1)
			y--;
		else if 



		else if (cmd == 'x')
			pen = !pen;
		if (pen)
		arr[0][x][y] = 1;
	}

	for (int iter = 0; iter < iterations; iter++)
	{
		for (int w = 1; w < width + 1; w++)
		{
			for (int h = 1; h < height + 1; h++)
			{
				int nb = 0;
				for (int x = -1; x <= 1; x++)
				{
					for (int y = -1; y <= 1; y++)
					{
						if (!(x== 0 && y == 0))
						{
							nb += arr[iter % 2][w + x][h + y];
						}
					}
				}

				if (arr[iter % 2][w][h]) == 1
				{
					if (nb == 2 || nb == 3)
					{
						arr[(iter + 1) % 2][w][h] = 1;
					}
					else
						arr[(iter + 1) % 2][w][h] = 0;
				}
				else
				{
					if (nb == 3)
						arr[iter + 1]
				}



			}
		}
	}


	for (int w = 1; w < width + 1; w++)
	{
		for (int h = 1; h < height + 1; h++)
		{
			putchar(arr[iterations % 2][w][h] ? 'O' : ' ');
		}
	}
	return 0;
}
