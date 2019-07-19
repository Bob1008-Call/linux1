int Max_distance(BTNode *root, int *m)
{
	if (NULL == root)
	{
		return 0;
	}
	int* max = m;
	int LeftDepth = Max_distance(root->Lchild, max);
	int RightDepth = Max_distance(root->Rchild, max);

	if (*max < LeftDepth + RightDepth)
	{
		*max = LeftDepth + RightDepth;
	}
	return LeftDepth>RightDepth ? LeftDepth + 1 : RightDepth + 1;
}
