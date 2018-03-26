double **allocate(int m, int n)
{
	double **arr=(double**)malloc(m*sizeof(double*));
	for(int i=0; i<m; i++)
		arr[i]=(double*)malloc(n*sizeof(double));
	return arr;
}
void myfree(double **arr, int m, int n)
{
	for(int i=0; i<m; i++)
		free(arr[i]);
	free(arr);
}
void swap(double **a, double **b)
{
	double *tmp=*a;
	*a=*b;
	*b=tmp;
}
double fabs(double x)
{
	return x<0?-x:x;
}
double **extract(double **A, int n, int row, int col)
{
	double **x=allocate(n-1, n-1); int index=0;
	for(int i=0; i<n; i++)
	{
		if(i==row)
			continue;
		for(int j=0; j<n; j++)
		{
			if(j==col)
				continue;
			x[index/(n-1)][index%(n-1)]=A[i][j];
			index++;
		}
	}
	return x;
}
int upper_triangular(double **arr, int m, int n)
{
	int sign=1;
	for(int i=0; i<m; i++)
	{
		double max=fabs(arr[i][i]); int pos=i;
		for(int j=i+1; j<m; j++)
		{
			/*if(fabs(arr[j][i])>max)
			{
				max=fabs(arr[j][i]); pos=j;
			}*/
			if(arr[j][i]!=0)
			{
				max=fabs(arr[j][i]); pos=j;
				break;
			}
		}
		if(pos!=i)
		{
			swap(&arr[i], &arr[pos]);
			sign=-sign;
		}
		if(max==0.0)
			return 0;
		for(int j=i+1; j<m; j++)
		{
			double x=arr[j][i]/arr[i][i];
			for(int k=i; k<n; k++)
				arr[j][k]=arr[j][k]-x*arr[i][k];
		}
	}
	return sign;
}
double** add(double **a, double **b, int m, int n)
{
	double **c=allocate(m, n);
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			c[i][j]=a[i][j]+b[i][j];
	return c;
}
double** subtract(double **a, double **b, int m, int n)
{
	double **c=allocate(m, n);
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			c[i][j]=a[i][j]-b[i][j];
	return c;
}
double** multiply( double **a, double **b, int m, int n, int k)
{
	double **c=allocate(m, k);
	for(int i=0; i<m; i++)
		for(int j=0; j<k; j++)
		{
			c[i][j]=0;
			for(int l=0; l<n; l++)
				c[i][j]+=a[i][l]*b[l][j];
		}
	return c;
}
void print(double **arr, int m, int n)
{
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			printf("%lf ", arr[i][j]);
		printf("\n");
	}
}
void input(double **arr, int m, int n)
{
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			scanf("%lf", &arr[i][j]);
}
double determinant(double **arr, int n)
{
	double ans=1.0;
	int flag=upper_triangular(arr, n, n);
	if(flag!=0)
	{
		for(int i=0; i<n; i++)
			ans*=arr[i][i];
		ans*=flag;
	}
	else
		ans=0.0;
	return ans;
}
double **transpose(double **A, int m, int n)
{
	double **At=allocate(n, m);
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			At[j][i]=A[i][j];
	return At;
}
void copyOf(double **arr, double **arr1, int m, int n)
{
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			arr1[i][j]=arr[i][j];
}
double **inverse(double **A, int n)
{
	double **Adj=allocate(n, n);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			double **x=extract(A, n, i, j);
			double y=determinant(x, n-1);
			if((i+j)&1)
				Adj[i][j]=-y;
			else
				Adj[i][j]=y;
			myfree(x, n-1, n-1); 
		}
	}
	double **inv=transpose(Adj, n, n);
	double **Ac=allocate(n, n);
	copyOf(A, Ac, n, n);
	double det=determinant(Ac, n);
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			inv[i][j]/=det;
	myfree(Ac, n, n);
	myfree(Adj, n, n);
	return inv;
}
void column_replace(double **arr, int m, double *b, int col)
{
	for(int i=0; i<m; i++)
		arr[i][col]=b[i];
}
