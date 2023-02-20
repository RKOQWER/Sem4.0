// Unique Projection Test is bound to fail if the object can be segmented into multiple
// functional planes

// First get the digital planar region then functional plane

#include<bits/stdc++.h>
using namespace std;

bool ptr[11][11][11];
multiset<pair<int,int> >xy;
multiset<pair<int,int> >yz;
multiset<pair<int,int> >zx;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	int n;
	cin>>n;
	memset(ptr,0,sizeof(ptr));
	int i,j,k;
	for(i=0;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		ptr[x][y][z]=true;
		xy.insert({x,y});
		yz.insert({y,z});
		zx.insert({z,x});
	}
	int cnt=0;
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			for(k=0;k<11;k++)
			{
				if(ptr[i][j][k])
				{
					if(xy.count({i,j})==1 || yz.count({j,k}) ==1|| zx.count({k,i})==1)
						cnt++;
				}
			}
		}
	}
	cout<<cnt<<"\n";
	return 0;
}