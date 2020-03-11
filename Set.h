#pragma once
#include <iostream>

using namespace std;

#define N_Size 30
template <typename T>
class Set
{
private:
	T *data;
	int count = 0;			//record the number of set's element
	int max_count = 0;		//the size of set
	void expend();			//when elements too much, expend the set size

public:
	Set();
	~Set();
	void add(const T &parameter);				//add element
	void remove_by_index(const int &index);		//remove element by index
	void remove(const T &parameter);			//remove element by value

	int find(const T &parameter);				//find value at the set, if success return index, if not find return -1
	bool is_exist(const T &parameter);			//check the value exist in set or not
	bool is_subset(const Set<T> &parameter);	//check a set is subset or not

	Set<T>& operator = (const Set<T> &parameter);
	Set<T>& operator + (const Set<T> &parameter);	//union set
	Set<T>& operator - (const Set<T> &parameter);	//difference set
	Set<T>& operator * (const Set<T> &parameter);	//intersection set
	bool operator == (const Set<T> &parameter);		
	bool operator != (const Set<T> &parameter);

	void show_all_element();					//show all elements
};

template <typename T>
Set<T>::Set()
{
	data = new T[N_Size];
	count = 0;
	max_count = N_Size;
}

template <typename T>
Set<T>::~Set()
{
	delete[] data;
	count = 0;
	max_count = N_Size;
}

template <typename T>
void Set<T>::expend()
{
	T *temp = new T[max_count + N_Size];
	for (int k = 0; k < max_count; k++)
	{
		temp[k] = data[k];
	}
	max_count = max_count + N_Size;
	delete[] data;
	data = temp;
}

template <typename T>
void Set<T>::add(const T &parameter)
{
	if (count >= max_count)
	{
		expend();
	}
	bool same_elemaent = false;
	for (int k = 0; k < count; k++)
	{
		if (data[k] == parameter)
		{
			same_elemaent = true;
			break;
		}
	}
	if (!same_elemaent)
	{
		data[count] = parameter;
		count++;
	}
}


template <typename T>
int Set<T>::find(const T &parameter)
{
	int index = -1;
	for (int k = 0; k < count; k++)
	{
		if (data[k] == parameter)
		{
			index = k;
			break;
		}
	}
	return index;
}

template <typename T>
bool Set<T>::is_exist(const T &parameter)
{
	int index = -1;
	index = find(parameter);
	if (index == -1)
	{
		return false;
	}
	else
	{
		return true;
	}	
}

template <typename T>
void Set<T>::remove_by_index(const int &index)
{
	for (int k = index; k < count - 1; k++)
	{
		data[k] = data[k + 1];
	}
	data[count] = INT_MAX;
	count--;
}


template <typename T>
void Set<T>::remove(const T &parameter)
{
	int index = -1;
	index = find(parameter);
	if (index != -1)
	{
		remove_by_index(index);
	}
}

template <typename T>
bool Set<T>::is_subset(const Set<T> &parameter)
{
	if (count < parameter.count)
	{
		return false;
	}
	else
	{
		int exist_count = 0;
		for (int k = 0; k < parameter.count; k++)
		{
			if (is_exist(parameter.data[k]))
			{
				exist_count++;
			}
		}
		if (exist_count == parameter.count)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

template <typename T>
Set<T>& Set<T>::operator = (const Set<T> &parameter)
{
	data = new T[parameter.max_count];
	count = parameter.count;
	max_count = parameter.max_count;
	for (int k = 0; k < count; k++)
	{
		data[k] = parameter.data[k];
	}
	return *this;
}

template <typename T>
Set<T>& Set<T>::operator + (const Set<T> &parameter)
{
	static Set<T> temp;
	
	for (int k = 0; k < count; k++)
	{
		temp.add(data[k]);
	}
	for (int k = 0; k < parameter.count; k++)
	{
		temp.add(parameter.data[k]);
	}
	return temp;
}

template <typename T>
Set<T>& Set<T>::operator - (const Set<T> &parameter)
{
	static Set<T> temp;
	for (int k = 0; k < count; k++)
	{
		temp.add(data[k]);
	}
	for (int k = 0; k < parameter.count; k++)
	{
		temp.remove(parameter.data[k]);
	}
	return temp;
}

template <typename T>
Set<T>& Set<T>::operator * (const Set<T> &parameter)
{
	static Set<T> temp;
	Set<T> temp1;
	for (int k = 0; k < count; k++)
	{
		temp.add(data[k]);
		temp1.add(data[k]);
	}
	for (int k = 0; k < parameter.count; k++)
	{
		temp1.remove(parameter.data[k]);
	}
	for (int k = 0; k < temp1.count; k++)
	{
		temp.remove(temp1.data[k]);
	}
	return temp;
}

template <typename T>
bool Set<T>::operator == (const Set<T> &parameter)
{
	if (count != parameter.count)
		return false;
	else
	{
		if (is_subset(parameter))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

template <typename T>
bool Set<T>::operator != (const Set<T> &parameter)
{
	if (count != parameter.count)
		return true;
	else
	{
		if (is_subset(parameter))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

template <typename T>
void Set<T>::show_all_element()
{
	for (int k = 0; k < count; k++)
	{
		cout << "The " << k + 1 << "th element: " << data[k] << endl;
	}
	cout << "The set has " << count << " element, the max size of the set is " << max_count << endl;
}