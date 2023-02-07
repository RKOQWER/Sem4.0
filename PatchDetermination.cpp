
#include<bits/stdc++.h>
using namespace std;
#include <iostream>
using std::cerr; 
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <cstdlib> 

struct planeinfo 
{
   // It contains info about plane
   int A,B,C,D;
   planeinfo()
   {
      A=0;
      B=0;
      C=0;
      D=0;
   }
};
struct point
{
   // Used to store point in 3 D
   int x,y,z;
   point()
   {
      x=0;
      y=0;
      z=0;
   }
   bool operator==(const point& p) const
    {
        return x == p.x && y == p.y && z==p.z;
    }
};
struct hf {

    size_t operator()(const point& p) const
    {
        return p.x*p.y*p.z;
    }
};
struct info
{
   int f1,f2,f3;
   info()
   {
      f1=0;
      f2=0;
      f3=0;
   }
};
bool digital_line(point a,point b,point c);
void visualisation(vector<point> &ans);
void voxelization(vector<pair<int,int> > &pixels,int A,int B,
   int C,int D,int flag);
planeinfo get_plane(point a,point b,point c);
int projection(point a,point b,point c,int flag);
bool check (point p,point q, point r,int i,int j,int flag);
pair<point,point> extreme(point a,point b,point c);
vector<pair<int,int> > coordinates(point a,point b,point c,int flag,planeinfo p);
vector<pair<int,int> >get_line(point l,point r,int flag);
void dst(vector<pair<int,int> > &v1,vector<pair<int,int> > &v2,
   int flag);
void input(point a,point b,point c,ifstream &in);
void scaling();
void patch();
// void solve(int i,int j,int k);
vector<point> neighbors(int x,int y,int z/*,bool ***vis*/);
void plane_work(vector<pair<int,int> > &e,int A,int B,int C,int D,int flag);
info  functional_plane(vector<point> &p);
bool validate(int x,int y,int z,set<pair<int,pair<int,int> > > &vis);
void bfs(vector<point> &p,info qu);
bool see(int x,int y,int z,info qu,set<pair<int,int> >&xy,set<pair<int,int> >&yz
   ,set<pair<int,int> >&zx);

int x_l=INT_MAX;
int y_l=INT_MAX;
int z_l=INT_MAX;
int x_m=INT_MIN;
int y_m=INT_MIN;
int z_m=INT_MIN;

bool ***ptr;
//info ***pln;

bool see(int x,int y,int z,info qu,set<pair<int,int> >&xy,set<pair<int,int> >&yz
   ,set<pair<int,int> >&zx)
{
   xy.insert({x,y});
   yz.insert({y,z});
   zx.insert({z,x});
   info t;
   int maxi=max(xy.size(),max(yz.size(),zx.size()));
   if(maxi==xy.size())
      t.f1=1;
   if(maxi==yz.size())
      t.f2=1;
   if(maxi==zx.size())
      t.f3=1;
   if(qu.f1!=0 && qu.f1!=t.f1)
      return false;
   if(qu.f2!=0 && qu.f2!=t.f2)
      return false;
   if(qu.f3!=0 && qu.f3!=t.f3)
      return false;
   return true;
}
bool validate(int x,int y,int z,set<pair<int,pair<int,int> > > &vis)
{
   if(x>=0 && x<=x_m-x_l && y>=0 && y<=y_m-y_l && z>=0 && z<=z_m-z_l
      && vis.find({x,{y,z}})==vis.end())
      return true;
   else
      return false;
}
void bfs(vector<point> &p,info qu)
{
   set<pair<int,pair<int,int> > > vis;
   set<pair<int,int> > xy;
   set<pair<int,int> > yz;
   set<pair<int,int> > zx;
   vector<point> ans;
   queue<point> q;
   for(auto &w:p)
   {
      q.push(w);
      vis.insert({w.x,{w.y,w.z}});
      xy.insert({w.x,w.y});
      yz.insert({w.y,w.z});
      zx.insert({w.z,w.x});
   }
   while(!q.empty())
   {
      int sz=q.size();
      while(sz--)
      {
         point f=q.front();
         ans.push_back(f);
         q.pop();
         for(int i=-1;i<=1;i++)
         {
            for(int j=-1;j<=1;j++)
            {
               for(int k=-1;k<=1;k++)
               {
                  if(validate(f.x+i,f.y+j,f.z+k,vis))
                  {
                     vis.insert({f.x+i,{f.y+j,f.z+k}});
                     point w;
                     w.x=f.x+i;
                     w.y=f.y+j;
                     w.z=f.z+k;
                     if(see(f.x+i,f.y+j,f.z+k,qu,xy,yz,zx))
                     {
                        
                        q.push(w);
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
   visualisation(ans);
}
void visualisation(vector<point> &ans)
{
   cout<<ans.size()<<"\n";
   int count=1;
   ofstream outdata;
   outdata.open("t_planar.obj"); // opens the file
   if( !outdata ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
   outdata<<"mtllib color.mtl\n";
   for(auto &w:ans)
   {
      float p=0.5;
      int x=w.x;
      int y=w.y;
      int z=w.z;
      outdata<<"usemtl 4"<<"\n";
      outdata<<"v "<<x -p<<" "<<y-p<<" "<<z-p<<"\n";
      outdata<<"v "<<x -p<<" "<<y-p<<" "<<z+p<<"\n";
      outdata<<"v "<<x -p<<" "<<y+p<<" "<<z-p<<"\n";
      outdata<<"v "<<x -p<<" "<<y+p<<" "<<z+p<<"\n";
      outdata<<"v "<<x +p<<" "<<y-p<<" "<<z-p<<"\n";
      outdata<<"v "<<x +p<<" "<<y-p<<" "<<z+p<<"\n";
      outdata<<"v "<<x +p<<" "<<y+p<<" "<<z-p<<"\n";
      outdata<<"v "<<x +p<<" "<<y+p<<" "<<z+p<<"\n";
      outdata<<"f "<<count+7<<" "<<count+5<<" "<<count+4<<" "<<count+6<<"\n";
      outdata<<"f "<<count+2<<" "<<count+3<<" "<<count+7<<" "<<count+6<<"\n";
      outdata<<"f "<<count+0<<" "<<count+1<<" "<<count+3<<" "<<count+2<<"\n";
      outdata<<"f "<<count+5<<" "<<count+1<<" "<<count+0<<" "<<count+4<<"\n";
      outdata<<"f "<<count+0<<" "<<count+2<<" "<<count+6<<" "<<count+4<<"\n";
      outdata<<"f "<<count+5<<" "<<count+7<<" "<<count+3<<" "<<count+1<<"\n";
      count+=8;
   }
   outdata.close();
}
info functional_plane(vector<point> &p)
{
   set<pair<int,int> > xy;
   set<pair<int,int> > yz;
   set<pair<int,int> > zx;
   for(point &w:p)
   {
      xy.insert({w.x,w.y});
      yz.insert({w.y,w.z});
      zx.insert({w.z,w.x});
   }
   int maxi=max(xy.size(),max(yz.size(),zx.size()));
   info q;
   if(maxi==xy.size())
      q.f1=1;
   if(maxi==yz.size())
      q.f2=1;
   if(maxi==zx.size())
      q.f3=1;
   return q;
}
vector<point> neighbors(int x,int y,int z/*,bool ***vis*/)
{
   int i,j,k;
   vector<point> v;
   for(i=-1;i<=1;i++)
   {
      for(j=-1;j<=1;j++)
      {
         for(k=-1;k<=1;k++)
         {
            if((x+i>=0 && x+i<=x_m-x_l)&&(y+j>=0 
               && y+j<=y_m-y_l)&&(z+i>=0 && z+i<=z_m-z_l))
            {
               point u;
               u.x=x+i;
               u.y=y+j;
               u.z=z+k;
               v.push_back(u);
            }

         }
      }
   }
   return v;
}
// void solve(int x,int y,int z)
// {
//    vector<point> ans;
//    queue<point> qu;
//    bool *** vis=new bool**[x_m-x_l+1];
//    int i,j,k;
//    for(i=0;i<=x_m-x_l;i++)
//    {
//       vis[i]=new bool*[y_m-y_l+1];
//       for(j=0;j<=y_m-y_l;j++)
//       {
//          vis[i][j]=new bool[z_m-z_l+1];
//          for(k=0;k<=z_m-z_l;k++)
//          {
//             vis[i][j][k]=false;
//          }
//       }
//    }
//    vector<point> p=neighbors(x,y,z,vis);
//    info q=functional_plane(p);
//    if((q.f1!=-1 && q.f1==pln[x][y][z].f1)||(q.f2!=-1 && q.f2==pln[x][y][z].f2)
//       ||(q.f3!=-1 && q.f3==pln[x][y][z].f3)||(pln[x][y][z].f1==-1 && pln[x][y][z].f2
//          ==-1 && pln[x][y][z].f3==-1))
//    {
//       for(point &w:p)
//       {
//          pln[w.x][w.y][w.z]=q;
//          vis[w.x][w.y][w.z]=true;
//          qu.push(w);
//       }
//    }
//    while(!qu.empty())
//    {
//       int sz=qu.size();
//       while(sz--)
//       {
//          point f=qu.front();
//          ans.push_back(f);
//          qu.pop();
//          vector<point> p=neighbors(f.x,f.y,f.z,vis);
//          info q=functional_plane(p);
//          if((q.f1!=-1 && q.f1==pln[x][y][z].f1)||(q.f2!=-1 && q.f2==pln[x][y][z].f2)
//       ||(q.f3!=-1 && q.f3==pln[x][y][z].f3)||(pln[x][y][z].f1==-1 && pln[x][y][z].f2
//          ==-1 && pln[x][y][z].f3==-1))
//          {
//                for(point &w:p)
//             {
//                pln[w.x][w.y][w.z]=q;
//                vis[w.x][w.y][w.z]=true;
//                qu.push(w);
//             }
//          }
//       }
//    }
//    visualisation(ans);

// }
void patch()
{
   int i,j,k;
   vector<point> p;
   /*
     For each voxel and it neighbors determine what all functional plane it has.
   */
   for(i=0;i<=x_m-x_l;i++)
   {
      for(j=0;j<=y_m-y_l;j++)
      {
         for(k=0;k<=z_m-z_l;k++)
         {
            if(ptr[i][j][k])
            {
               // vector<point> p=neighbors(i,j,k);
               // info q=functional_plane(p);
               // //cout<<q.f1<<" "<<q.f2<<" "<<q.f3<<"\n";
               // bfs(p,q);
               // return ;
               point x;
               x.x=i;
               x.y=j;
               x.z=k;
               p.push_back(x);

            }
         }
      }
   }
   // cout<<"Printing the voxels\n";
   // for(int i=0;i<p.size();i++)
   //    cout<<p[i].x<<" "<<p[i].y<<" "<<p[i].z<<"\n";
   visualisation(p);
}
void plane_work(vector<pair<int,int> > &e,int A,int B,int C,int D,int flag)
{
   float l=0.5*(max(A,max(B,C)));
   int i;
   if(flag==0)
   {
      for(i=0;i<e.size();i++)
         {
            int x=e[i].first;
            int y=e[i].second;
            float z=(l-A*x-B*y-D)/(C*1.0);
            if(C>0)
               z=floor(z);
            else
               z=ceil(z);
            
            int p=(int)z;
            if(!ptr[x-x_l][y-y_l][p-z_l])
            {
               
               ptr[x-x_l][y-y_l][p-z_l]=true;
            }
         }
   }
   else if(flag==1)
   {
      for(i=0;i<e.size();i++)
         {
            int y=e[i].first;
            int z=e[i].second;
            float x=(l-C*z-B*y-D)/(A*1.0);
            if(A>0)
               x=floor(x);
            else
               x=ceil(x);
            int p=(int)(x);
            if(!ptr[p-x_l][y-y_l][z-z_l])
            {  
               ptr[p-x_l][y-y_l][z-z_l]=true;
            }
         }
   }
   else
   {
      for(i=0;i<e.size();i++)
         {
            int z=e[i].first;
            int x=e[i].second;
            float y=(l-C*z-A*x-D)/(B*1.0);
            if(B>0)
               y=floor(y);
            else
               y=ceil(y);
            int p=(int)(y);
            if(!ptr[x-x_l][p-y_l][z-z_l])
            {  
               ptr[x-x_l][p-y_l][z-z_l]=true;
            }
         }
   }
  
}


bool digital_line(point a,point b,point c)
{
   /*
      Using the concept that cross product of vectors is 0 of line
   */
   point v1;
   v1.x=b.x-a.x;
   v1.y=b.y-a.y;
   v1.z=b.z-a.z;
   point v2;
   v2.x=c.x-a.x;
   v2.y=c.y-a.y;
   v2.z=c.z-a.z;
   int t1=v1.y*v2.z -v1.z*v2.y;
   int t2=v1.x*v2.z -v1.z*v2.x;
   int t3=v1.x*v2.y -v1.y*v2.x;
   if(t1==0 && t2==0 && t3==0)
      return true;
   else
      return false;
}



void voxelization(vector<pair<int,int> > &pixels,int A,int B,int C,int D,int flag)
{
   // Used to convert pixels to voxels
   float l=0.5*(max(A,max(B,C)));
   int i;
   if(flag==0)
   {
      for(i=0;i<pixels.size();i++)
         {
            int x=pixels[i].first;
            int y=pixels[i].second;
            float z=(l-A*x-B*y-D)/(C*1.0);
            if(C>0)
               z=floor(z);
            else
               z=ceil(z);
            
            int p=(int)z;
            if(!ptr[x-x_l][y-y_l][p-z_l])
            {
               ptr[x-x_l][y-y_l][p-z_l]=true;
            }
         }
   }
   else if(flag==1)
   {
      for(i=0;i<pixels.size();i++)
         {
            int y=pixels[i].first;
            int z=pixels[i].second;
            float x=(l-C*z-B*y-D)/(A*1.0);
            if(A>0)
               x=floor(x);
            else
               x=ceil(x);
            int p=(int)(x);
            if(!ptr[p-x_l][y-y_l][z-z_l])
            {
               ptr[p-x_l][y-y_l][z-z_l]=true;
            }
         }
   }
   else
   {
      for(i=0;i<pixels.size();i++)
         {
            int z=pixels[i].first;
            int x=pixels[i].second;
            float y=(l-C*z-A*x-D)/(B*1.0);
            if(B>0)
               y=floor(y);
            else
               y=ceil(y);
            int p=(int)(y);
            if(!ptr[x-x_l][p-y_l][z-z_l])
            {
               ptr[x-x_l][p-y_l][z-z_l]=true;
            }
         }
   }
  
}
              

planeinfo get_plane(point a,point b,point c)
{
      int A=0,B=0,C=0,D=0;
      int a1 = b.x - a.x;
      int b1 = b.y - a.y;
      int c1 = b.z - a.z;
      int a2 = c.x - a.x;
      int b2 = c.y - a.y;
      int c2 = c.z- a.z;
      A = b1 * c2 - b2 * c1;
      B = a2 * c1 - a1 * c2;
      C = a1 * b2 - b1 * a2;
      D = (- A * a.x - B * a.y - C* a.z);
      planeinfo p;
      p.A=A;
      p.B=B;
      p.C=C;
      p.D=D;
      return p;
}

int projection(point a,point b,point c,int flag)
{
   /* flag =0 represents xy plane
      flag =1 represents yz plane
      flag=2 represents zx plane 
      */
   if(flag==0)
   {
      // Compute the area of tringle when projected in xy plane.
      int x=((b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x));//
      return abs(x);
   }
   else if(flag ==1)
   {
      // Compute the area of tringle when projected in yz plane.
      int x=((b.y-a.y)*(c.z-a.z) - (b.z-a.z)*(c.y-a.y));
      return abs(x);
   }
   else
   {
      // Compute the area of tringle when projected in zx plane.
      int x=((b.z-a.z)*(c.x-a.x) - (b.x-a.x)*(c.z-a.z));
      return abs(x);
   }
}


bool check (point p,point q, point r,int i,int j,int flag)
{

   /* Checks if triangle formed by points p,q and r contains integer 
   coordinates (i,j) */
   if(flag==0)
   {
      point  t;
      t.x=i;
      t.y=j;
      /* Calculate area of  triangle ABC */
      int A = projection (p,q,r,0);
  
      /* Calculate area of triangle PBC */ 
      int A1 = projection (t, q, r,0);
  
      /* Calculate area of triangle PAC */ 
      int A2 = projection (p,t,r,0);
  
      /* Calculate area of triangle PAB */  
      int A3 = projection(p, q ,t,0);
    
      /* Check if sum of A1, A2 and A3 is same as A */
      return (A == A1 + A2 + A3);  
   }
   else if(flag==1)
   {
      point t;
      t.y=i;
      t.z=j;
      /* Calculate area of triangle ABC */
      int A = projection(p,q,r,1);
  
      /* Calculate area of triangle PBC */ 
      int A1 = projection (t, q, r,1);
  
      /* Calculate area of triangle PAC */ 
      int A2 = projection (p,t,r,1);
  
      /* Calculate area of triangle PAB */  
      int A3 = projection (p, q, t,1);
    
      /* Check if sum of A1, A2 and A3 is same as A */
      return (A == A1 + A2 + A3);
   }
   else
   {
      point t;
      t.z=i;
      t.x=j;
      /* Calculate area of triangle ABC */
      int A = projection(p,q,r,2);
  
      /* Calculate area of triangle PBC */ 
      int A1 = projection (t, q, r,2);
  
      /* Calculate area of triangle PAC */ 
      int A2 = projection (p,t,r,2);
  
      /* Calculate area of triangle PAB */  
      int A3 = projection (p, q, t,2);
    
      /* Check if sum of A1, A2 and A3 is same as A */
      return (A == A1 + A2 + A3);
   }
    
}


vector<pair<int,int> > coordinates(point a,point b,point c,int flag,planeinfo pl)
{
   /* flag= 0 represents xy plane
      flag=1 represents yz plane
      flag=2 represents zx plane
      */
  /* Returns points that lies inside and on the boundry of triangle formed from
  points a , b and c */
  vector<pair<int,int> >v;

  if(flag==0)
  {
      point p;
      p.x=a.x;
      p.y=a.y;
      point q;
      q.x=b.x;
      q.y=b.y;
      point r;
      r.x=c.x;
      r.y=c.y;
      int x_min=min(p.x,min(q.x,r.x));
      int x_max=max(p.x,max(q.x,r.x));
      int y_min=min(p.y,min(q.y,r.y));
      int y_max=max(p.y,max(q.y,r.y));
      int i,j;
      for(i=x_min;i<=x_max;i++)
      {
         for(j=y_min;j<=y_max;j++)
         {
            if(check(p,q,r,i,j,0))
            {
                  v.push_back({i,j});
            }
         }
      }
      vector<pair<int,int> > e=get_line(a,b,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
      e=get_line(b,c,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
      e=get_line(c,a,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
  }
  else if(flag==1)
  {
      point p;
      p.y=a.y;
      p.z=a.z;
      point q;
      q.y=b.y;
      q.z=b.z;
      point r;
      r.y=c.y;
      r.z=c.z;
      int y_min=min(p.y,min(q.y,r.y));
      int y_max=max(p.y,max(q.y,r.y));
      int z_min=min(p.z,min(q.z,r.z));
      int z_max=max(p.z,max(q.z,r.z));
      int i,j;
      for(i=y_min;i<=y_max;i++)
      {
         for(j=z_min;j<=z_max;j++)
         {
            if(check(p,q,r,i,j,1))
            {
                
               v.push_back({i,j});
            }
         }
  }
      vector<pair<int,int> > e=get_line(a,b,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
      e=get_line(b,c,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
      e=get_line(c,a,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
  }
  else
  {
      point p;
      p.z=a.z;
      p.x=a.x;
      point q;
      q.z=b.z;
      q.x=b.x;
      point r;
      r.z=c.z;
      r.x=c.x;
      int z_min=min(p.z,min(q.z,r.z));
      int z_max=max(p.z,max(q.z,r.z));
      int x_min=min(p.x,min(q.x,r.x));
      int x_max=max(p.x,max(q.x,r.x));
      int i,j;
      for(i=z_min;i<=z_max;i++)
      {
         for(j=x_min;j<=x_max;j++)
         {
            if(check(p,q,r,i,j,2))
            {
               v.push_back({i,j});
            }
         }
      }
     vector<pair<int,int> > e=get_line(a,b,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
      e=get_line(b,c,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
      e=get_line(c,a,flag);
      plane_work(e,pl.A,pl.B,pl.C,pl.D,flag);
      e.clear();
  }
  return v;
}

pair<point,point> extreme(point a,point b,point c)
{
   
   pair<point,point> t;
   
   int d1=0,d2=0,d3=0;
   // Distance between a and b
   d1=(b.x-a.x)*(b.x-a.x)  +(b.y-a.y) *(b.y-a.y)+(b.z- a.z)*(b.z- a.z);
   // Distance between b and c
    d2=(b.x-c.x)*(b.x-c.x)  +(b.y-c.y) *(b.y-c.y)+(b.z- c.z)*(b.z- c.z);
    // Distance between c and a
     d3=(c.x-a.x)*(c.x-a.x)  +(c.y-a.y) *(c.y-a.y)+(c.z- a.z)*(c.z- a.z);
     // a is not extreme
     if(d1+d3==d2)
      t=make_pair(b,c);
   else if(d1+d2==d3)// b is not extreme
      t=make_pair(a,c);
   else// c is not extreme
      t=make_pair(a,b);
   return t;
}

vector<pair<int,int> >get_line(point l,point r,int flag)
{
   vector<pair<int,int> >  v;
   if(flag==0)
   {
      point p,q;
      p.x=l.x;
      p.y=l.y;
      q.x=r.x;
      q.y=r.y;

      int dx = abs(q.x - p.x);
      int dy = abs(q.y - p.y);
      int sx = (p.x < q.x) ? 1 : -1;
      int sy = (p.y < q.y) ? 1 : -1;
      int err = dx - dy;
      while(true) {
         v.push_back({p.x,p.y});
         if ((p.x == q.x) && (p.y == q.y)) 
            break;
         int e2 = 2*err;
         if (e2 > -dy) { err -= dy; p.x  += sx; }
         if (e2 < dx) { err += dx; p.y  += sy; }
      }
   }
   else if(flag==1)
   {
      point p,q;
      p.y=l.y;
      p.z=l.z;
      q.y=r.y;
      q.z=r.z;

      int dy = abs(q.y - p.y);
      int dz = abs(q.z - p.z);
      int sy = (p.y < q.y) ? 1 : -1;
      int sz = (p.z < q.z) ? 1 : -1;
      int err = dy - dz;
      while(true) {
         v.push_back({p.y,p.z}); // Do what you need to for this

         if ((p.y == q.y) && (p.z == q.z)) 
            break;
         int e2 = 2*err;
         if (e2 > -dz) { err -= dz; p.y  += sy; }
         if (e2 < dy) { err += dy; p.z  += sz; }
      }
   }
   else
   {
      point p,q;
      p.z=l.z;
      p.x=l.x;
      q.z=r.z;
      q.x=r.x;

      int dz = abs(q.z - p.z);
      int dx = abs(q.x - p.x);
      int sz = (p.z < q.z) ? 1 : -1;
      int sx = (p. x< q.x) ? 1 : -1;
      int err = dz - dx;
      while(true) {
         v.push_back({p.z,p.x}); // Do what you need to for this

         if ((p.z == q.z) && (p.x == q.x)) 
         break;
         int e2 = 2*err;
         if (e2 > -dx) { err -= dx; p.z  += sz; }
         if (e2 < dz) { err += dz; p.x  += sx; }
      }
   }

   return v;
}

void dst(vector<pair<int,int> > &v1,vector<pair<int,int> > &v2,int flag)
{
   
   if(flag==0)// for each x;
   {
      map<int,int> mpp;
      for(int i=0;i<v1.size();i++)
      {
         mpp.insert({v1[i].first,v1[i].second});
      }
      for(int i=0;i<v2.size();i++)
      {
         int z=v2[i].first;
         int x=v2[i].second;
         int y=mpp[x];
         if(!ptr[x-x_l][y-y_l][z-z_l])
         {  
            ptr[x-x_l][y-y_l][z-z_l]=true;
         }
      }
      mpp.clear();
   }
   else if(flag==1)// for each y;
   {
      map<int,int> mpp;
      for(int i=0;i<v1.size();i++)
      {
         mpp.insert({v1[i].second,v1[i].first});
      }
      for(int i=0;i<v2.size();i++)
      {

         int z=v2[i].second;
         int y=v2[i].first;
         int x=mpp[y];
         if(!ptr[x-x_l][y-y_l][z-z_l])
         { 
            ptr[x-x_l][y-y_l][z-z_l]=true;
         }
      }
      mpp.clear();
   }
   else
   {
      map<int,int> mpp;
      for(int i=0;i<v1.size();i++)
      {
         mpp.insert({v1[i].second,v1[i].first});
      }
      for(int i=0;i<v2.size();i++)
      {
         int z=v2[i].first;
         int y=mpp[z];
         int x=v2[i].second;
         if(!ptr[x-x_l][y-y_l][z-z_l])
         {  
            ptr[x-x_l][y-y_l][z-z_l]=true;
         }
      }
      mpp.clear();
   }
  
}

void input(point a,point b,point c,ifstream &in)
{
   

   // Check for single point
      if(a.x==b.x && b.x==c.x && a.y==b.y && b.y==c.y && a.z==b.z && b.z==c.z)
      {
         if(!ptr[a.x-x_l][a.y-y_l][a.z-z_l])
         {
            ptr[a.x-x_l][a.y-y_l][a.z-z_l]=true;
         }
      }
    //Check for digital line
      else if(digital_line(a,b,c))
      {
         
         pair<point,point> w=extreme(a,b,c);
         point l=w.first;
         point r=w.second;
         int x,y,z;
         x=abs(l.x-r.x);
         y=abs(l.y-r.y);
         z=abs(l.z-r.z);
         if(x>=y && x>=z)
         {
            vector<pair<int,int> > v1=get_line(l,r,0);
            vector<pair<int,int> >v2=get_line(l,r,2);
             dst(v1,v2,0);
             v1.clear();
             v2.clear();
         }
         else if(y>=x && y>=z)
         {
            vector<pair<int,int> > v1=get_line(l,r,0);
            vector<pair<int,int> >v2=get_line(l,r,1);
            dst(v1,v2,1);
             v1.clear();
             v2.clear();
         }
         else
         {
            vector<pair<int,int> > v1=get_line(l,r,1);
            vector<pair<int,int> >v2=get_line(l,r,2);
            dst(v1,v2,2);
             v1.clear();
             v2.clear();
         }
      }
   else
   {

      planeinfo p=get_plane(a,b,c);
      int flag=-1; 
       if(abs(p.C )>= abs(p.B )&&abs(p.C)>=abs(p.A)) flag = 0;// xy is functional plane
       else if(abs(p.A)>=abs(p.B) && abs(p.A)>=abs(p.C)) flag = 1;// yz is functional plane
       else flag = 2;// zx is functional plane
       cout<<"Plane "<<flag<<"\n";
       vector<pair<int,int>> pixels=coordinates(a,b,c,flag,p);
       voxelization(pixels,p.A,p.B,p.C,p.D,flag);
       pixels.clear();
    }
    
}


void scaling()
{
      ifstream in;  
      in.open("t.obj"); // taking input of vertices and faces from the orignal.obj file and scaling it
      if(!in) { 
         cerr << "Error: file could not be opened" << endl;
         exit(1);
      }
   ofstream out;
   out.open("mt.obj"); // Storing the scaled version of orignal .obj file in this file
   if( !out) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
 
   while ( !in.eof() )
   {
         char q;
         
         in>>q;
         if(q=='v')
         {
            float x,y,z;// Orignal file may contain voxels that are floating points
            in>>x>>y>>z;
            int x1=int(round(x*1));// Scaling factor of 5 used
            int y1=int(round(y*1));// round function used as we need to operate on integer coordinates only
            int z1=int(round(z*1));
            x_l=min(x_l,x1);// Storing minimum and maximum value of the voxels coordinates so that it can be used to as a bounding box of appropreite volume.
            y_l=min(y_l,y1);
            z_l=min(z_l,z1);
            x_m=max(x_m,x1);
            y_m=max(y_m,y1);
            z_m=max(z_m,z1);

            out<<"v"<<" "<<x1<<" "<<y1<<" "<<z1<<"\n";
         }
         else if(q=='f')
         {
            int x,y,z;
            in>>x>>y>>z;
            out<<"f "<<x<<" "<<y<<" "<<z<<"\n";
         }
   }
   out.close();
   in.close();
  
}
int main()
{
    scaling();
    ptr=new bool**[x_m-x_l+1];
   // pln=new info**[x_m-x_l+1];
    int i,j,k;
    for(i=0;i<=x_m-x_l;i++)
    {
      ptr[i]=new bool*[y_m-y_l+1];
      //pln[i]=new info*[y_m-y_l+1];
      for(j=0;j<=y_m-y_l;j++)
      {
         ptr[i][j]=new bool[z_m-z_l+1];
         //pln[i][j]=new info[z_m-z_l+1];
         for(k=0;k<=z_m-z_l;k++)
         {
            ptr[i][j][k]=false;
           // pln[i][j][k].f1=pln[i][j][k].f2=pln[i][j][k].f3=0;
         }
      }
    }
    ifstream in;  
      in.open("mt.obj"); 
      if(!in) { 
         cerr << "Error: file could not be opened" << endl;
         exit(1);
      }

    
   // Step 1: Storing all the vertices
   vector<point> vertices;
   int cnt=0;
   while ( !in.eof() )
   {
         char q;
         int x,y,z;
         in>>q>>x>>y>>z;
         if(q=='v')
         {
            point p;
            p.x=x;
            p.y=y;
            p.z=z;
            vertices.push_back(p);
         }
         else if(q=='f')// a b c stores the 3 vertices corresponding to faces
         {
            point a,b,c;

            a=vertices[x-1];
            b=vertices[y-1];
            c=vertices[z-1];
            // cnt++;
            // cout<<cnt<<" "<<a.x<<" "<<a.y<<" "<<a.z<<",";
            // cout<<b.x<<" "<<b.y<<" "<<b.z<<",";
            // cout<<c.x<<" "<<c.y<<" "<<c.z<<"\n";
            input(a,b,c,in);
            
         }
         
   }
   in.close();
   patch();
   return 0;
}