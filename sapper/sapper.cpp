
#include <iostream>
#include <cstdlib> //��� srand, system() � �.�.
#include <time.h> //��� time
#include <windows.h>
#include <clocale>
using namespace std;

int Select()
{
	int n = 0;
	cout << "�������� ���������: " << endl;
	cout << "[1] ������(5x5)" << endl;
	cout << "[2] �������(9x9)" << endl;
	cin >> n;
	return n;
};
int Size(int n)
{
	int size = 0;
	switch (n)
	{
	case 1:size = 5; break;
	case 2:size = 9; break;
	};
	return size;
}
int Bomb(int n)
{
	int bomb = 0;
	switch (n)
	{
	case 1:bomb = 3; break;
	case 2:bomb = 11; break;
	};
	return bomb;
}

char** Full(int size) //�������� �������
{
	int i, j;
	char **Full = new char*[size+1];
	for (i = 0; i <= size+1; i++)
	{
		Full[i] = new char[size];
		for (j = 0; j <= size+1; j++)
		{
			if ((i == size + 1) || (j == size + 1))
			{
				Full[i][j] = ' ';
			};

			if (i == 0)
			{
				Full[i][j] = j + '0';
			}
			else
				if (j == 0)
				{
					Full[i][j] = i + '0';
				}
				else
				{
					Full[i][j] = '_';
				}
		}
	}
	return Full;
}

void BenLaden(int size, int bomb,char **arr, int rand1, int rand2)// ���������� ������� �������
{

	int i=1;
	srand(time(NULL));

	for (i = 1; i <= bomb; i++)
	{

		while (arr[rand1][rand2] == '*')
		{
			rand1 = 1 + rand() % (size-1);
			rand2 = 1 + rand() % (size-1);
		}
		arr[rand1][rand2] = '*';
	//	cout << rand1 << ' ' << rand2 << endl;
	}

};

void ShowMtrx(int size, char **arr)	//����� �������
{
	int i, j;
	for (i = 0; i < size + 1; i++)
	{
		for (j = 0; j < size + 1; j++)
		{
			cout << arr[i][j] << '|';
		}
		cout << endl;
	}
};

int CheckAround(int n, int m, char **arr)	//�������� �� ������� ���� ������ ��������� ������
{
	int check = 0;
	if (arr[n - 1][m - 1] == '*')
		check++;
	if (arr[n - 1][m] == '*')
		check++;
	if (arr[n - 1][m + 1] == '*')
		check++;
	if (arr[n][m + 1] == '*')
		check++;
	if (arr[n + 1][m + 1] == '*')
		check++;
	if (arr[n + 1][m] == '*')
		check++;
	if (arr[n + 1][m - 1] == '*')
		check++;
	if (arr[n][m - 1] == '*')
		check++;
	return check;
};

int main()
{
	setlocale(LC_ALL,"rus");
	int i, j, size = 5, bomb = 3, bombsaround, o;
	int rand1 = 0, rand2 = 0;
	int n, m;
	char **mainfield = Full(size);
	char **additionalfield = Full(size);
	bool itisbobm = false, win = false;
	o = Select();
	size = Size(o);
	bomb = Bomb(o);
	system("cls");
	time_t secondszero;//��������� �����
	time_t seconds;
	secondszero = time(NULL);
	seconds = time(NULL) - secondszero;

	srand(time(NULL));
	rand1 = 1 + rand() % size;
	rand2 = 1 + rand() % size;

	BenLaden(size, bomb, &additionalfield[0], rand1, rand2);	//���������� ��������������� ���� ����������
	
	while (itisbobm == false && win == false)
	{
		cout << "time: " << seconds << endl;
		seconds = time(NULL) - secondszero;
		ShowMtrx(size, &mainfield[0]);	//����� �������
		int c = 0;
		cin >> n; cin >> m;
		if ((n > 0 && n <= size) && (m>0 && m <= size)) // �������� �� ������������ ����� ���������
		{
			if (additionalfield[n][m] == '*')
			{
				itisbobm = true;
				break;
			}
			else
			{
				bombsaround = CheckAround(n, m, &additionalfield[0]);	//����� ���� ������ ������ ������
			}

			mainfield[n][m] = bombsaround + '0';
			win = true;
			for (i = 1; i < size + 1; i++)
			{
				for (j = 1; j < size + 1; j++)
				{
					if (additionalfield[i][j] == '*')
					{
					}
					else
						if (mainfield[i][j] != '_')
							win = win && true;
						else win = false;
				};
			};
		}
		else 
		{
			cout << "Nevernoe znachenie" << endl;
			system("pause");
		};
		system("cls");
	}
	system("cls");
	ShowMtrx(size, &additionalfield[0]);
	if (win == true)
	{

		cout << "You WIN!!!\nYour time is: " << seconds << endl;
	}
	else
		cout << "You LOSE!!!\nYour time is: " << seconds <<endl;
	return 0;
}

