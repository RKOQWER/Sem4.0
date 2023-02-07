/* Check if the voxels generated are all unique
Ans:- Yes they are all unique 
1. Find the functional plane of all these voxels
Ans: xy,yz,zx
2. Find the functional plane of neighboring voxels
Done
3. Even if vertices and their orientation are repeated the voxels set
generated will be the same.
4. See the view of voxels in matrix form
*/

#include<bits/stdc++.h>
using namespace std;
bool ptr[11][11][11];

struct info
{
	int f1,f2,f3;
	info()
	{
		f1=f2=f3=0;
	}
};
struct point
{
	int x,y,z;
};
void bfs(vector<point> &p,info f);
vector<point> neighbors(int x,int y,int z);
info functional_plane(vector<point> &p);

bool check(point w,set<pair<int,int> >&xy,set<pair<int,int> >&yz,
	set<pair<int,int> >&zx,info qu);
bool check(point w,set<pair<int,int> >&xy,set<pair<int,int> >&yz,
	set<pair<int,int> >&zx,info qu)
{
	info t;
	xy.insert({w.x,w.y});
	yz.insert({w.y,w.z});
	zx.insert({w.z,w.x});
	int maxi=max(xy.size(),max(yz.size(),zx.size()));
	if(maxi==xy.size())
		t.f1=1;
	if(maxi==yz.size())
		t.f2=1;
	if(maxi==zx.size())
		t.f3=1;
	if(t.f1==qu.f1 && t.f2==qu.f2 && t.f3==qu.f3)
		return true;
	else
		return false;
}

void bfs(vector<point> &p,info qu)
{
	queue<point> q;
	int c=0;
	bool vis[11][11][11];
	int i,j,k;
	set<pair<int,int> >xy;
	set<pair<int,int> >yz;
	set<pair<int,int> >zx;
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			for(k=0;k<11;k++)
				vis[i][j][k]=false;
		}
	}
	for(point &w:p)
	{
		vis[w.x][w.y][w.z]=true;
		xy.insert({w.x,w.y});
		yz.insert({w.y,w.z});
		zx.insert({w.z,w.x});
		q.push(w);
		c++;
	}
	
	while(!q.empty())
	{
	    int sz=q.size();
		while(sz--)
		{
			point f=q.front();
			q.pop();
			for(i=-1;i<=1;i++)
			{
				for(j=-1;j<=1;j++)
				{
					for(k=-1;k<=1;k++)
					{
						if(f.x+i>=0 && f.x+i<=10 
						&& f.y+j>=0 && f.y+j<=10 && f.z+k>=0 && f.z+k<=10
						&& ptr[f.x+i][f.y+j][f.z+k] && !vis[f.x+i][f.y+j][f.z+k])
						{
							point w;
							w.x=f.x+i;
							w.y=f.y+j;
							w.z=f.z+k;
							vis[w.x][w.y][w.z]=true;
							if(check(w,xy,yz,zx,qu))
							{
								q.push(w);
								c++;
							}
							else
							{
								xy.erase({w.x,w.y});
								yz.erase({w.y,w.z});
								zx.erase({w.z,w.x});
							}
							
						}
					}
				}
			}
		}
	}
	cout<<c<<"\n";
}
info functional_plane(vector<point> &p)
{
	set<pair<int,int> > xy;
	set<pair<int,int> > yz;
	set<pair<int,int> > zx;
	int i;
	for(i=0;i<p.size();i++)
	{
		int x=p[i].x;
		int y=p[i].y;
		int z=p[i].z;
		xy.insert({x,y});
		yz.insert({y,z});
		zx.insert({z,x});
	}
	info q;
	q.f1=xy.size();
	q.f2=yz.size();
	q.f3=zx.size();
	return q;
}
vector<point> neighbors(int x,int y,int z)
{
	int i,j,k;
	vector<point> p;
	for(i=-1;i<=1;i++)
	{
		for(j=-1;j<=1;j++)
		{
			for(k=-1;k<=1;k++)
			{
				if(x+i>=0 && x+i<=10 && y+j>=0 && y+j<=10 && z+k>=0 
					&& z+k<=10 && ptr[x+i][y+j][z+k] )
				{
					point w;
					w.x=x+i;
					w.y=y+j;
					w.z=z+k;
					p.push_back(w);
				}

			}
		}
	}
	return p;
}
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
	int i,j,k;
	for(i=0;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		ptr[x][y][z]=true;
	}
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			for(k=0;k<11;k++)
			{
				if(ptr[i][j][k])
				{
					vector<point> p=neighbors(i,j,k);
 					info f=functional_plane(p);
 					bfs(p,f);
 					//return 0;
				}
			}
		}
	}
	return 0;
}
