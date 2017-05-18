#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>

using namespace std;

void game();
void draw( int**, int,int,int);
int alice(int**lenght, int *visit, int n, int start);
int bob(int**lenght, int *visit, int n, int start);
int rez[25];
int i=0;
int main()
{
	int T;
	cin >> T;
	if (T > 0 && T <= 25)
	{
		for (int i = 0; i < T; i++)
		{
			game();
		}
		for (int i = 0; i < T; i++)
			rez[i] == 1 ? cout << "Bob" << endl : cout << "Alice" << endl;
	}
	//system("pause");
}

void game()
{
	int n;
	cin >> n;
	if (n>0&&n < 50000)
	{
		int n1 = n - 1;
		int **iMatrix = new int*[n];
		for (int i = 0; i < n; i++)
			iMatrix[i] = new int[n];

		for (int i = 0, u, v; i < n1; i++)
		{
			cin >> u >> v;
			iMatrix[--u][--v] = 1;
			iMatrix[v][u] = 1;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (iMatrix[i][j] != 1)
					iMatrix[i][j] = 0;
			}
		}
		///////////////////////////////////////////////////////////////algoritm Uorshala
		int **Mlenght = new int*[n];
		for (int i = 0; i < n; i++)
			Mlenght[i] = new int[n];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Mlenght[i][j] = iMatrix[i][j];//копіювання елемента матриці
				Mlenght[i][i] = 0;//обнулення значень по діагоналі
				if (Mlenght[i][j] == 0)
				{
					Mlenght[i][j] = 999;//присвоєння безкінечності
				}
			}
		}
		for (int k = 0; k < n; ++k)//кількість раз використання матриці
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{

					if (i != j)//якщо елемент не лежить на діагоналі

					{
						Mlenght[i][j] = Mlenght[i][j] < Mlenght[i][k] + Mlenght[k][j] ? Mlenght[i][j] : Mlenght[i][k] + Mlenght[k][j];
						//визначення мінімального часу між двома станціями
					}
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Mlenght[i][j] == 999)//шлях не існує
				{
					Mlenght[i][j] = 0;//доїхати не можливо до станція
				}
				//cout << setw(3) << Mlenght[i][j] << " ";
			}
			//cout << endl;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////game on tree
		int start = -1, altStart = 0;
		int maxStart;
		bool error_pair = false;
		bool br = false;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Mlenght[i][j] != 0)
				{
					if (Mlenght[i][j] % 2 == 0)
					{
						if (!error_pair)
						{
							maxStart = Mlenght[i][j];
							start = i;
							error_pair = true;
						}
						if (maxStart < max(maxStart, Mlenght[i][j]))
							start = i;

					}
					else
					{
						if (!br)
						{
							altStart = i;
							br = true;
						}
					}
				}

			}
		}
		if (start == -1)
			start = altStart;
		//cout <<maxStart<<"  "<< start + 1 << endl;
		draw(Mlenght, n, start, 0);

		for (int i = 0; i < n; i++)
		{
			delete[] iMatrix[i];
			delete[] Mlenght[i];
		}
	}
	
}

void draw( int** lenght, int n,int start,int win)
{
	int *visit = new int[n];
	for (int i = 0; i < n; i++)
	{
		visit[i] = -1;
	}
	int winner=-1;
	visit[start] = 0;
	if (win == 0)
	{
		win = 1;
	}
	else
	{
		win = 0;
	}
	do
	{
	
		if (win == 0)
		{
			start = alice(lenght, visit, n, start);
			if (start == -1)
			{
				winner = 1;
				break;
			}
			/*for (int i = 0; i < n; i++)
			{
				if (lenght[start][i] != 0 && visit[i] == -1)
				{
					if (lenght[start][i] % 2 == 0)
					{
						start = i;
						visit[i] = 0;
						new1 = true;
						break;
					}
					else
					{
						if (!new2)
						{
							altStart = i;
							visit[i] = 0;
							new2 = true;
						}
					}
				}
			}
			if (!new1 && new2)
			{
				start = altStart;
			}*/
			/*if (!new1 && !new2)
			{
				winner = 1;
				break;
			}*/
		}
		else
		{
			start = bob(lenght, visit, n, start);
			if (start == -1)
			{
				winner = 0;
				break;
			}
			/*for (int i = 0; i < n; i++)
			{
				if (lenght[start][i] != 0 && visit[i] == -1)
				{
					if (lenght[start][i] % 2 != 0)
					{
						start = i;
						visit[i] = 0;
						new1 = true;
						break;
					}
					else
					{
						if (!new2)
						{
							altStart = i;
							visit[i] = 0;
							new2 = true;
						}
					}
				}
			}
			if (!new1 && new2)
			{
				start = altStart;
			}
			if (!new1 && !new2)
			{
				winner = 0;
				break;
			}*/
		}
		if (win == 0)
			win = 1;
		else
			win = 0;
	} while (1);
	rez[::i] = winner;
	::i++;
	delete[] visit;
	
}
int alice(int**lenght, int *visit, int n, int start)
{
	int altStart=-1;
	//int winner;
	bool new1 = false;
	bool new2 = false;
	
		for (int i = 0; i < n; i++)
		{
			if (lenght[start][i] != 0 && visit[i] == -1)
			{
				if (lenght[start][i] % 2 == 0)
				{
					visit[i] = 0;
					return i;
					new1 = true;
					
				}
				else
				{
					if (!new2)
					{
						altStart = i;
						new2 = true;
						
					}
				}
			}
		}
		if (!new1 && new2)
		{
			visit[altStart] = 0;
			return altStart;
		}
		else
		{
			return -1;
		}
}
int bob(int**lenght, int *visit, int n, int start)
{
	int altStart=-1;
	//int winner;
	bool new1 = false;
	bool new2 = false;

	for (int i = 0; i < n; i++)
	{
		if (lenght[start][i] != 0 && visit[i] == -1)
		{
			if (lenght[start][i] % 2 != 0)
			{
				visit[i] = 0;
				return i;
				new1 = true;

			}
			else
			{
				if (!new2)
				{
					altStart = i;
					new2 = true;

				}
			}
		}
	}
	if (!new1 && new2)
	{
		visit[altStart] = 0;
		return altStart;
	}
	else
	{
		return -1;
	}
}