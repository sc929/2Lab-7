#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename Type>
class Matrix
{
public:
	unsigned int Lines;
	unsigned int Columns;
	Type** matr;

	Matrix()
	{
		Lines = 2;
		Columns = 2;
		matr = (Type **)malloc(Lines * sizeof(Type *));
		for (unsigned int i = 0; i < Lines; ++i)
			matr[i] = (Type *)malloc(Columns * sizeof(Type));
		for (unsigned int i = 0; i < Lines; ++i)
			for (unsigned int j = 0; j < Columns; ++j)
				matr[i][j] = 0;
	}

	Matrix(unsigned int Lines, unsigned int Columns)
	{
		this->Lines = Lines;
		this->Columns = Columns;
		matr = (Type **)malloc(Lines * sizeof(Type *));
		for (unsigned int i = 0; i < Lines; ++i)
			matr[i] = (Type *)malloc(Columns * sizeof(Type));
	}

	void fill(string path)
	{
		ifstream file(path);
		try
		{
			if (!file.is_open()) throw 1;
		}
		catch (int error)
		{
			cout << endl << "ERROR!!! " << error << "The file wasn't found!" << endl;
			exit(1);
		}

		for (unsigned int i = 0; i < Lines; ++i)
		{
			for (unsigned int j = 0; j < Columns; ++j)
			{
				file >> matr[i][j];
			}
		}
		file.close();
	}

	void printf(ostream&)
	{
		cout << endl << "Matrix: " << endl;

		for (unsigned int i = 0; i < Lines; ++i)
		{
			for (unsigned int j = 0; j < Columns; ++j)
			{
				cout << matr[i][j] << " ";
			}
			cout << endl;
		}
	}

	void writef(istream&)
	{
		for (unsigned int i = 0; i < Lines; ++i)
		{
			for (unsigned int j = 0; j < Columns; ++j)
			{
				cin >> matr[i][j];
			}
		}
	}

	template <typename K> friend ostream& operator << (ostream& ciout, const Matrix<K>& matri);
	template <typename U> friend istream& operator >> (istream& ciin, Matrix<U>& matri);

	bool operator ==(Matrix<Type>& res_matr)
	{
		if (res_matr.Lines != Lines || res_matr.Columns != Columns)
			return false;

		for (unsigned int i = 0; i < res_matr.Lines; ++i)
		{
			for (unsigned int j = 0; j < res_matr.Columns; ++j)
			{
				if (res_matr.matr[i][j] != matr[i][j])
					return false;
			}
		}
		return true;
	}

	Matrix<Type>& operator +(Matrix<Type>& res_matr)
	{
		try
		{
			if (res_matr.Lines != Lines || res_matr.Columns != Columns) throw 2;
		}
		catch (int error)
		{
			cout << endl << "ERROR!!! " << error << ": The operation of adding matrices is defined only for matrices of the same order!" << endl;
			exit(1);
		}

		Matrix<Type> *matr_temp1 = new Matrix<Type>;

		for (unsigned int i = 0; i < res_matr.Lines; ++i)
		{
			for (unsigned int j = 0; j < res_matr.Columns; ++j)
			{
				matr_temp1->matr[i][j] = res_matr.matr[i][j] + matr[i][j];
			}
		}

		return *matr_temp1;
	}

	Matrix<Type>& operator *(Matrix<Type>& res_matr)
	{
		try
		{
			if (res_matr.Lines != Columns) throw 2;
		}
		catch (int error)
		{
			cout << endl << "ERROR!!! " << error << ": The operation of multiplication matrices is defined only if number of Columns of the 1 Matrix = number of Lines of the 2 Matrix!" << endl;
			exit(1);
		}

		Matrix<Type> *matr_temp = new Matrix<Type>;

		for (unsigned int i = 0; i < res_matr.Lines; ++i)
		{
			for (unsigned int j = 0; j < res_matr.Columns; ++j)
			{
				for (unsigned int k = 0; k < res_matr.Columns; ++k)
				{
					matr_temp->matr[i][j] += res_matr.matr[k][j] * matr[i][k];
				}

			}
		}

		return *matr_temp;
	}

	~Matrix()
	{
		for (unsigned int i = 0; i < Lines; ++i) delete matr[i];
		delete[] matr;
	}

};

template <class Type>
ostream & operator<<(ostream & ciout, Matrix<Type> &matri)
{
	matri.printf(ciout);
	return ciout;
}

template <class Type>
istream & operator >> (istream& ciin, Matrix<Type> &matri)
{
	matri.writef(ciin);
	return ciin;
}
