#include <iostream>
#include <ctime>
#include <typeinfo>
using namespace std;


class Point
{
public:

	virtual void GetName()
	{

	}
};


class Point2D : public Point
{
public:


	void GetName()
	{

		cout << ("Point2D\n");
	}
};

class Point3D : public Point
{
public:

	void GetName()
	{
		cout << ("Point3D\n");
	}
};


class MyStorage
{
protected:
	int size, count, countdel, countadd;
public:

	Point** objects;

	MyStorage(int size_)
	{
		size = size_;
		objects = new Point * [size];
		count = 0;
		countdel = 0;
		countadd = 0;
	}

	~MyStorage()
	{
		delete objects;
	}

	void SetObject(int i, Point* p)
	{
		objects[i] = p;
		count++;
	}

	void Add(Point* p)
	{
		Point** objects2 = new Point * [size + 1];
		if (size != 0) {
			for (int j = 0; j < size; j++) {
				objects2[j] = objects[j];
			}
		}
		delete[] objects;
		objects = objects2;
		objects[size] = p;
		size = size + 1;
		countadd++;
		count++;
	}

	void GetName(int index)
	{
		if (size != 0)
			objects[index]->GetName();

	}

	void PullOut(int index)
	{
		// objects[index] = NULL;
	}
	void Next(int index)
	{
		if (index < size - 1)
		{
			cout << ("��������� ������ - ��� ");
			GetName(index + 1);
		}
	}
	void Prev(int index)
	{
		if (index > 1)
		{
			cout << "���������� ������ - ��� ";
			GetName(index - 1);
		}
	}
	void Delete(int index)
	{
		if (size != 1)
		{
			Point** objects2 = new Point * [size - 1];
			if (index != size)
				for (int j = 0; j < index; j++) {
					objects2[j] = objects[j];
				}

			for (int j = index; j < size - 1; j++)
			{
				objects2[j] = objects[j + 1];
			}
			delete[] objects;
			size = size - 1;
			objects = objects2;
			countdel++;
			count--;
		}
	}
	void GetCount()
	{
		cout << "\n\n���������� �������� = " << count << "\n";
		cout << "���������� ��������� �������� = " << countdel << "\n";
		cout << "���������� ����������� �������� = " << countadd << "\n";
		cout << "runtime = " << clock() / 1000.0 << endl;
	}
	int GetSize()
	{
		return size;
	}
};

void actions(int count, MyStorage& storage)
{
	for (int i = 0; i < count; i++)
	{
		int j = rand() % storage.GetSize();
		int actn = rand() % 6 + 1;

		switch (actn)
		{
		case 1:
			if ((rand()) % 2 == 0)
			{
				storage.Add(new Point2D);
				cout << "�������� ������ Point2D\n";
			}
			else
			{
				storage.Add(new Point3D);
				cout << "�������� ������ Point3D\n";
			}
			break;
		case 2:
			storage.Delete(j);
			break;
		case 3:
			storage.GetName(j);
			break;
		case 4:
			storage.Next(j);
			break;
		case 5:
			storage.Prev(j);
			break;
		case 6:
			storage.PullOut(j);
			break;
		}
	}
	storage.GetCount();

}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));


	MyStorage storage(10);

	for (int i = 0; i < storage.GetSize(); i++)
	{
		int k = rand();
		if (k % 2 == 1)
			storage.SetObject(i, new Point2D);
		else
			storage.SetObject(i, new Point3D);
	}

	actions(100, storage);
	cout << "\n\n";
	system("pause");
	actions(1000, storage);
	cout << "\n\n";
	system("pause");
	actions(10000, storage);
	cout << "\n\n";
	system("pause");




}