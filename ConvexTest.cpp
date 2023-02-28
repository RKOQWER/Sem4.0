#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define ll long long
const int inf=(int)(1e9);
const int M=(int)(1e9+7);
using namespace std;
using namespace __gnu_pbds;
 
typedef tree<int,null_type,less<int>,
rb_tree_tag,tree_order_statistics_node_update> pbds;
struct point
{
	long long x,y;
 
};
 
	bool operator<(const point& lhs, const point& rhs)
{
	if(lhs.x!=rhs.x)
     return   lhs.x < rhs.x;
 	else
 		return lhs.y<rhs.y;
}
 
void solve(vector<point>&arr,int n);
bool acw(point a,point b,point c);
bool cw(point a,point b,point c);
bool acw(point a,point b,point c)
{
	long long p=(c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);
	return p>0;
}
 
bool cw(point a,point b,point c)
{
	long long p=(c.y-a.y)*(b.x-a.x)-(b.y-a.y)*(c.x-a.x);
	return p<0;
}
 
bool f(point a,point b)
{
	if(a.x<b.x)
		return true;
	else if(a.x>b.x)
		return false;
	else
		return (a.y<b.y);
}
void solve(vector<point> &arr,int n)
{
	sort(arr.begin(),arr.end(),f);
	point p1=arr[0];
	point p2=arr[n-1];
	int i;
	vector<point> up;
	vector<point> down;
	up.push_back(p1);
	down.push_back(p1);
	for(i=1;i<n;i++)
	{
		if(i==n-1 || !acw(p1,arr[i],p2))
		{
			while(up.size()>=2 && acw(up[up.size()-2],up[up.size()-1],arr[i]))
			{
				up.pop_back();
			}
			up.push_back(arr[i]);
		}
		if(i==n-1 || !cw(p1,arr[i],p2))
		{
			while(down.size()>=2 && cw(down[down.size()-2],down[
				down.size()-1],arr[i]))
			{
				down.pop_back();
			}
			down.push_back(arr[i]);
		}
	}
	set<point> st;
	for(auto &e:up)
		st.insert(e);
	for(auto &e:down)
		st.insert(e);
	cout<<st.size()<<"\n";
	for(auto it=st.begin();it!=st.end();it++)
	{
		cout<<it->x<<" "<<it->y<<"\n";
	}
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
	vector<point> arr(n);
	int i;
	for(i=0;i<n;i++)
		cin>>arr[i].x>>arr[i].y;
	solve(arr,n);
	return 0;
}	