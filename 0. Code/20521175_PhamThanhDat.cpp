/*######################################
# University of Information Technology #
# IT007 Operating System #
# <Pham Thanh Dat>, <20521175> #
# File: ex6_4.cpp #
######################################*/
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

struct KieuA
{
	int value;
	char check = ' ';
};
struct KieuB
{
	int value = -1;
	int index = -1;
};
KieuA A[100];
KieuB B[20][100];
int n, vt, Count;
int frame;
int ktConTrong(int i)
{
	for (int j = 0; j < frame; j++)
	{
		if (B[j][i].value == -1)
			return 1;
	}
	return 0;
}
int ktTonTai(int i, int x, int sum)
{
	for (int j = 0; j < frame; j++)
	{
		if (B[j][i].value == x)
		{
			if (sum != 0)
			{
				B[j][i].index = vt;
				if (!ktConTrong(i))
					vt++;
			}
			return 1;
		}
	}
	return 0;
}
int vtMin(int i)
{
	int vtm = 0;
	for (int j = 1; j < frame; j++)
	{
		if (B[vtm][i].index > B[j][i].index)
			vtm = j;
	}
	return vtm;
}
int vtMax(int i)
{
	int vtm = 0;
	for (int j = 1; j < frame; j++)
	{
		if (B[vtm][i].index < B[j][i].index)
			vtm = j;
	}
	return vtm;
}
void vtXuatHien(int i)
{
	for (int j = 0; j < frame; j++)
	{
		bool kt = false;
		int vtr = i + 1;
		while (!kt && vtr < n)
		{
			if (B[j][i].value == A[vtr].value)
				kt = true;
			vtr++;
		}
		if (kt)
			B[j][i].index = vtr;
		else
			B[j][i].index = n;
	}
}
void FIFO()
{
	B[0][0].value = A[0].value, B[0][0].index = 0, A[0].check = '*';
	vt = 1, Count = 1;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < frame; j++)
			B[j][i] = B[j][i - 1];
		if (ktConTrong(i))
		{
			if (ktTonTai(i, A[i].value, 0))
			{
				A[i].check = '*';
				Count++;
			}
			else
			{
				B[vt % frame][i].value = A[i].value;
				B[vt % frame][i].index = vt;
				vt++;
				A[i].check = '*';
				Count++;
			}
		}
		else
		{
			if (!ktTonTai(i, A[i].value, 0))
			{
				int vtm = vtMin(i);
				B[vtm][i].value = A[i].value;
				B[vtm][i].index = vt;
				A[i].check = '*';
				Count++;
				vt++;
			}
		}
	}
	cout << "\n\tFIFO\n";
	for (int i = 0; i < n; i++)
		cout << setw(2) << A[i].value;
	cout << "\n ---------------------\n";
	for (int i = 0; i < frame; i++)
	{
		for (int j = 0; j < n; j++)
			if (B[i][j].value == -1)
				cout << setw(2) << " ";
			else
				cout << setw(2) << B[i][j].value;
		cout << endl;
	}
	for (int i = 0; i < n; i++)
		cout << setw(2) << A[i].check;
	cout << "\nNumber of Page Fault: " << Count << endl;
}
void OPT()
{
	B[0][0].value = A[0].value, B[0][0].index = 0, A[0].check = '*';
	vt = 1, Count = 1;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < frame; j++)
			B[j][i] = B[j][i - 1];
		if (ktConTrong(i))
		{
			if (ktTonTai(i, A[i].value, 0))
			{
				A[i].check = '*';
				Count++;
			}
			else
			{
				B[vt % frame][i].value = A[i].value;
				B[vt % frame][i].index = vt;
				vt++;
				A[i].check = '*';
				Count++;
			}
		}
		else
		{
			if (!ktTonTai(i, A[i].value, 0))
			{
				vtXuatHien(i);
				int vtm = vtMax(i);
				B[vtm][i].value = A[i].value;
				B[vtm][i].index = vt;
				A[i].check = '*';
				Count++;
				vt++;
			}
		}
	}
	cout << "\n\tOPT\n";
	for (int i = 0; i < n; i++)
		cout << setw(2) << A[i].value;
	cout << "\n ---------------------\n";
	for (int i = 0; i < frame; i++)
	{
		for (int j = 0; j < n; j++)
			if (B[i][j].value == -1)
				cout << setw(2) << " ";
			else
				cout << setw(2) << B[i][j].value;
		cout << endl;
	}
	for (int i = 0; i < n; i++)
		cout << setw(2) << A[i].check;
	cout << "\nNumber of Page Fault: " << Count << endl;
}
void LRU()
{
	B[0][0].value = A[0].value, B[0][0].index = 0, A[0].check = '*';
	vt = 1, Count = 1;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < frame; j++)
			B[j][i] = B[j][i - 1];
		if (ktConTrong(i))
		{
			if (ktTonTai(i, A[i].value, 1))
			{
				A[i].check = '*';
				Count++;
			}
			else
			{
				B[vt % frame][i].value = A[i].value;
				B[vt % frame][i].index = vt;
				vt++;
				A[i].check = '*';
				Count++;
			}
		}
		else
		{
			if (!ktTonTai(i, A[i].value, 1))
			{
				int vtm = vtMin(i);
				B[vtm][i].value = A[i].value;
				B[vtm][i].index = vt;
				A[i].check = '*';
				Count++;
				vt++;
			}
		}
	}
	cout << "\n\tLRU\n";
	for (int i = 0; i < n; i++)
		cout << setw(2) << A[i].value;
	cout << "\n ---------------------\n";
	for (int i = 0; i < frame; i++)
	{
		for (int j = 0; j < n; j++)
			if (B[i][j].value == -1)
				cout << setw(2) << " ";
			else
				cout << setw(2) << B[i][j].value;
		cout << endl;
	}
	for (int i = 0; i < n; i++)
		cout << setw(2) << A[i].check;
	cout << "\nNumber of Page Fault: " << Count << endl;
}
int main()
{
	int k;
	cout << "___ Page Replacement Algorithm ___";
	cout << "\n1.Default Referenced Sequence \n2.Manual Input Sequence \n";
	cin >> k;
	if (k == 1)
	{
		A[0].value = 2, A[1].value = 0, A[2].value = 5, A[3].value = 2, A[4].value = 1;
		A[5].value = 0, A[6].value = 8, A[7].value = 3, A[8].value = 0, A[9].value = 0, A[10].value = 7;
		n = 11;
		cout << "Reference string: 2 0 5 2 1 0 8 3 0 0 7\n";
	}
	else
	{
		cout << "Input the page number: ";
		cin >> n;
		cout << "Reference string: ";
		for (int i = 0; i < n; i++)
			cin >> A[i].value;
	}
	cout << "___ Page Replacement Algorith ___\nInput Page Frames: ";
	cin >> frame;
	cout << "___ Page Replacement Algorith ___\n1. FIFO Algorithm \n2. OPT Algorithm \n3. LRU Algorithm\n";
	cin >> k;
	switch (k)
	{
	case 1:
	{
		FIFO();
		break;
	}
	case 2:
	{
		OPT();
		break;
	}
	case 3:
	{
		LRU();
		break;
	}
	}
	return 0;
}
