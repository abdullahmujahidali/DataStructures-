void arrayList<T>::insert(const T & val)
{    //insertion with insertion sort
	if (length < maxSize) {
		list[length] = val;
		length = length + 1;

		for (int i = 1; i < length; i++) {
			int temp = list[i];
			int j = i - 1;
			while (j >= 0 && list[j] > temp) {
				list[j + 1] = list[j];
				j--;
			}
			list[j + 1] = temp;
		}
	}
	else {
		cout << "Full" << endl;
	}

}
