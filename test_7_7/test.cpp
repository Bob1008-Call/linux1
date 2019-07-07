void MergeData(int *array, int left, int mid, int right, int *temp)
{
	int index = left;
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid;
	int end2 = right;
	while (begin1<end1 && begin2<end2)
	{
		if (array[begin1] <= array[begin2])
		{
			temp[index++] = array[begin1++];
		}
		else
		{
			temp[index++] = array[begin2++];
		}
	}
	while (begin1 < end1)
		temp[index++] = array[begin1++];

	while (begin2 < end2)
		temp[index++] = array[begin2++];

}
