#include<iostream>
#include<string>
using namespace std;

typedef char **HuffmanCode;
typedef class
{
public:
	int weight;
	int parent, lchild, rchild;
}
HTNode, *HuffmanTree;

void Select(HuffmanTree &HT, int area, int &s1, int &s2)
{
	int  check;
	for (int i = 1; i <= area; i++)
	{
			if (HT[i].parent == 0)
			{
				check = HT[i].weight;
				s1 = i;
				break;
			}
		
	}
	for (int i = 1; i <= area; i++)
	{
			if (check > HT[i].weight && HT[i].parent == 0)
			{
				check = HT[i].weight;
				s1 = i;
			}
		
	}
	HT[s1].parent = 1;
	for (int i = 1; i <= area; i++)
	{
			if (HT[i].parent == 0)
			{
				check = HT[i].weight;
				s2 = i;
				break;
			}
		
	}
	for (int i = 1; i <= area; i++)
	{
			if (check > HT[i].weight && HT[i].parent == 0)
			{
				check = HT[i].weight;
				s2 = i;
			}
		
	}
}
void getWeight(string msg,int weight[])
{
	for (int i = 0; i < msg[i] != '\0'; i++)
	{
		weight[int(msg[i])-96]++;
	}
}
void CreateHuffmanTree(HuffmanTree &HT, int n,string msg)
{
	int m, i, s1, s2;
	m = 2 * n - 1;
	HT = new HTNode[m + 1];
	for (i = 1; i <= m; ++i)
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	int array[27] = { 0 };
	getWeight(msg, array);
	for (i = 1; i <= n; ++i){
		for (int j = i; i <= 26; j++)
		{
			if (array[j] != 0){
				HT[i].weight = array[j];
				break;
			}
		}
	}
	for (i = n + 1; i <= m; ++i)
	{
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}

void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	int i, c, start, f;
	char *cd;
	HC = new char *[n + 1];
	cd = new char[n];
	cd[n - 1] = '\0';
	for (i = 1; i <= n; ++i)
	{
		start = n - 1;
		c = i; f = HT[i].parent;
		while (f != 0)
		{
			--start;
			if (HT[f].lchild == c)
				cd[start] = '0';
			else
				cd[start] = '1';
			c = f;
			f = HT[f].parent;
		}
		HC[i] = new char[n - start];
		strcpy_s(HC[i], n - start, &cd[start]);
	}
	delete cd;
}


int main()
{
	string msg;
	cout << "Enter Massage: ";
	getline(cin, msg);
	int array[27] = {0};
	getWeight(msg, array);
	int n = 0;
	cout << "\t\tFrequancy\n";
	for (int i = 1; i <= 26; i++)
	{
		if (array[i] != 0){
			cout << char(i + 96) << ") " << array[i] << endl;
			n++;
		}
	}
	HuffmanTree HT;
	HuffmanCode HC;
	CreateHuffmanTree(HT, n,msg);
	CreateHuffmanCode(HT, HC, n);
	cout << "\t\tHaffman Tree\n";
	for (int i = 1; i <= n; i++)
		cout <<i<<" -> ) Coded as： " << HC[i] << " " << endl;
	return 0;
}
