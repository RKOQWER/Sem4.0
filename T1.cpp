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
struct info
{
   int x,y,z,v;
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
};

// vector<info> arr;
int ***ptr;
int x_l=INT_MAX;
int x_m=INT_MIN;
int y_l=INT_MAX;
int y_m=INT_MIN;
int z_l=INT_MAX;
int z_m=INT_MIN;

bool digital_line(point a,point b,point c)
{
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

void visualisation()
{
 
   ofstream outdata;
   outdata.open("cubevoxel.obj"); // opens the file
   if( !outdata ) { // file couldn't be opened
      cout<<4<<"\n";
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
   int line[8];
   for(int i=0;i<8;i++)
      line[i]=i+1;
      //cout<< "Here" << endl;
   int cnt=0;
   for(int x=0;x<=x_m-x_l;x++)
   {
      for(int y=0;y<=y_m-y_l;y++)
      {
         for(int z=0;z<=z_m-z_l;z++)
         {
            if(ptr[x][y][z]!=-1)
            {
               cnt++;
              int d=ptr[x][y][z];
              float p=0.5;
               if(d==0)
               {
                  outdata<<"usemtl red\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z+p<<"\n";
               }
               else if(d==1)
               {
                  outdata<<"usemtl green\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z+p<<"\n";
               }
               else if(d==2)
               {
                  outdata<<"usemtl blue\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z+p<<"\n";
               }
               else if(d==3)
               {
                  outdata<<"usemtl yellow\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x -p<<" "<<y+p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y-p<<" "<<z+p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z-p<<"\n";
                  outdata<<"v "<<x +p<<" "<<y+p<<" "<<z+p<<"\n";
               }
            else
            {
               outdata<<"usemtl black\n";
               outdata<<"v "<<x -p<<" "<<y-p<<" "<<z-p<<"\n";
               outdata<<"v "<<x -p<<" "<<y-p<<" "<<z+p<<"\n";
               outdata<<"v "<<x -p<<" "<<y+p<<" "<<z-p<<"\n";
               outdata<<"v "<<x -p<<" "<<y+p<<" "<<z+p<<"\n";
               outdata<<"v "<<x +p<<" "<<y-p<<" "<<z-p<<"\n";
               outdata<<"v "<<x +p<<" "<<y-p<<" "<<z+p<<"\n";
               outdata<<"v "<<x +p<<" "<<y+p<<" "<<z-p<<"\n";
               outdata<<"v "<<x +p<<" "<<y+p<<" "<<z+p<<"\n";
            }
            outdata<<"f "<<line[7]<<" "<<line[5]<<" "<<line[4]<<" "<<line[6]<<"\n";
            outdata<<"f "<<line[2]<<" "<<line[3]<<" "<<line[7]<<" "<<line[6]<<"\n";
            outdata<<"f "<<line[0]<<" "<<line[1]<<" "<<line[3]<<" "<<line[2]<<"\n";
            outdata<<"f "<<line[5]<<" "<<line[1]<<" "<<line[0]<<" "<<line[4]<<"\n";
            outdata<<"f "<<line[0]<<" "<<line[2]<<" "<<line[6]<<" "<<line[4]<<"\n";
            outdata<<"f "<<line[5]<<" "<<line[7]<<" "<<line[3]<<" "<<line[1]<<"\n";
            for(int i=0;i<8;i++)
               line[i]=line[i]+8;
                  }
               }
            }
   }
   
   cout<<"Number of voxels generated = "<<cnt<<"\n";
   outdata.close();
   
}

vector<point> voxelization(vector<pair<int,int> > &pixels,int A,int B,int C,int D,int flag)
{
   // Used to convert pixels to voxels
   float l=0.5*(max(A,max(B,C)));
   int i;
   vector<point> vec;
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
            point t;
            t.x=x;
            t.y=y;
            t.z=(int)z;
            vec.push_back(t);
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
      
            point t;
            t.y=y;
            t.z=z;
            t.x=(int)x;
            vec.push_back(t);
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
            point t;
            t.z=z;
            t.x=x;
            t.y=(int)y;
            vec.push_back(t);
         }
   }
   return vec;
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


vector<pair<int,int> > coordinates(point a,point b,point c,int flag)
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
  }
  return v;
  
}

pair<point,point> extreme(point a,point b,point c)
{
   // a is not extreme
   pair<point,point> t;
   if((b.x<=a.x && a.x<=c.x && b.y<=a.y && a.y<=c.y  && b.z<=a.z && a.z<=c.z )|| 
     (c.x<=a.x && a.x<=b.x && c.y<=a.y && a.y<=b.y  && c.z<=a.z && a.z<=b.z))
      t=make_pair(b,c);
   // b is not extreme
   if((b.x>=a.x && b.y>=a.y && b.z>=a.z && b.x<=c.x && b.y<=c.y && b.z<=c.z)||
      (b.x<=a.x && b.y<=a.y && b.z<=a.z && b.x>=c.x && b.y>=c.y && b.z>=c.z))
      t=make_pair(a,c);
   // c is not extreme
   if((c.x>=a.x && c.y>=a.y && c.z>=a.z && c.x<=b.x && c.y<=b.y && c.z<=b.z)||
      (c.x>=b.x && c.y>=b.y && c.z>=b.z && c.x<=a.x && c.y<=a.y && c.z<=a.z))
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

vector<point> dst(vector<pair<int,int> > &v1,vector<pair<int,int> > &v2,int flag)
{
   vector<point> v;
   
   if(flag==0)// for each x;
   {
      unordered_map<int,int> mpp;
      for(int i=0;i<v1.size();i++)
      {
         mpp.insert({v1[i].first,v1[i].second});
      }
      for(int i=0;i<v2.size();i++)
      {
         point p;
         int z=v2[i].first;
         int x=v2[i].second;
         int y=mpp[x];
         p.x=x;
         p.y=y;
         p.z=z;
         v.push_back(p);
      }
   }
   else if(flag==1)// for each y;
   {
      unordered_map<int,int> mpp;
      for(int i=0;i<v1.size();i++)
      {
         mpp.insert({v1[i].second,v1[i].first});
      }
      for(int i=0;i<v2.size();i++)
      {
         point p;
         int z=v2[i].second;
         int y=v2[i].first;
         int x=mpp[y];
         p.x=x;
         p.y=y;
         p.z=z;
         v.push_back(p);
      }
   }
   else
   {
      unordered_map<int,int> mpp;
      for(int i=0;i<v1.size();i++)
      {
         mpp.insert({v1[i].second,v1[i].first});
      }
      for(int i=0;i<v2.size();i++)
      {
         point p;
         int z=v2[i].first;
         int y=mpp[z];
         int x=v2[i].second;
         p.x=x;
         p.y=y;
         p.z=z;
         v.push_back(p);
      }
   }
   return v;
}

void input(point a,point b,point c,ofstream & out,ifstream &in)
{
   //cout<<a.x<<" "<<a.y<<" "<<a.z<<"\n";
   //cout<<b.x<<" "<<b.y<<" "<<b.z<<"\n";
   //cout<<c.x<<" "<<c.y<<" "<<c.z<<"\n\n";

   // Check for single point
      if(a.x==b.x && b.x==c.x && a.y==b.y && b.y==c.y && a.z==b.z && b.z==c.z)
      {
         out <<a.x<<" "<<a.y<<" "<<a.z<<"\n";
         // info i;
         // i.x=a.x;
         // i.y=a.y;
         // i.z=a.z;
         // i.v=4;
         //arr.push_back(i);
         ptr[a.x-x_l][a.y-y_l][a.z-z_l]=4;
         //cout << a.x << " " << a.y << " " << a.z << "\n";
      }
    //Check for digital line
      else if(digital_line(a,b,c))
      {
         vector<point> voxels;
         pair<point,point> w=extreme(a,b,c);
         point l=w.first;
         point r=w.second;
         int x,y,z;
         x=abs(l.x-r.x);
         y=abs(l.y-r.y);
         z=abs(l.z-r.z);
         if(x>= y&& x>=z)
         {
            vector<pair<int,int> > v1=get_line(l,r,0);
            vector<pair<int,int> >v2=get_line(l,r,2);
             voxels=dst(v1,v2,0);
         }
         else if(y>=x && y>=z)
         {
            vector<pair<int,int> > v1=get_line(l,r,0);
            vector<pair<int,int> >v2=get_line(l,r,1);
            voxels=dst(v1,v2,1);
         }
         else
         {
            vector<pair<int,int> > v1=get_line(l,r,1);
            vector<pair<int,int> >v2=get_line(l,r,2);
            voxels=dst(v1,v2,2);
         }
         for(int i=0;i<voxels.size();i++)
         {
            // info w;
            // w.x=voxels[i].x;
            // w.y=voxels[i].y;
            // w.z=voxels[i].z;
            // w.v=3;
            // arr.push_back(w);
            ptr[voxels[i].x-x_l][voxels[i].y-y_l][voxels[i].z-z_l]=3;
            out<<voxels[i].x<<" "<<voxels[i].y<<" "<<voxels[i].z<<"\n";
         }
      }
   else
   {

    planeinfo p=get_plane(a,b,c);
    //int xy=projection(a,b,c,0);
    //int yz=projection(a,b,c,1);
    //int zx=projection(a,b,c,2);
    int flag=-1; 
    if(abs(p.C )> abs(p.B )&&abs(p.C)>abs(p.A)) flag = 0;// xy is functional plane
    else if(abs(p.A)>abs(p.B) && abs(p.A)>abs(p.C)) flag = 1;// yz is functional plane
    else flag = 2;// zx is functional plane

    vector<pair<int,int>> pixels=coordinates(a,b,c,flag);
    vector<point> voxels=voxelization(pixels,p.A,p.B,p.C,p.D,flag);
    for(int i=0;i<voxels.size();i++)
         {
            // info w;
            // w.x=voxels[i].x;
            // w.y=voxels[i].y;
            // w.z=voxels[i].z;
            // w.v=flag;
            // arr.push_back(w);
            ptr[voxels[i].x-x_l][voxels[i].y-y_l][voxels[i].z-z_l]=flag;
            out<<voxels[i].x<<" "<<voxels[i].y<<" "<<voxels[i].z<<"\n";
         }
   }
    
}


int main()
{
    
    ifstream in;  
      in.open("cube.obj"); // to get the vertices of triangle
      if(!in) { 
         cout<<1<<"\n";
         cerr << "Error: file could not be opened" << endl;
         exit(1);
      }
   ofstream out;
   /* cube.txt will have voxels of points in triangle */

   out.open("cube.txt"); // opens the file
   if( !out) { // file couldn't be opened
      cout<<2<<"\n";
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
    
   // Step 1: Storing all the vertices
   vector<point> vertices;
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
            x_l=min(x_l,p.x);
            y_l=min(y_l,p.y);
            z_l=min(z_l,p.z);
            x_m=max(x_m,p.x);
            y_m=max(y_m,p.y);
            z_m=max(z_m,p.z);
            vertices.push_back(p);
         }
         // else if(q=='f')
         // {
         //    point a,b,c;
         //    a=vertices[x-1];
         //    b=vertices[y-1];
         //    c=vertices[z-1];
         //    input(a,b,c,out,in);
         // }
   }
   in.close();
    ptr=new int**[x_m-x_l+1];
    
    int i,j,k;
    for(i=0;i<=x_m-x_l;i++)
    {
      ptr[i]=new int*[y_m-y_l+1];
      
      for(j=0;j<=y_m-y_l;j++)
      {
         ptr[i][j]=new int[z_m-z_l+1];
         
         for(k=0;k<=z_m-z_l;k++)
         {
            ptr[i][j][k]=-1;
         }
      }
    }
    
      ifstream inf;  
      inf.open("cube.obj"); // to get the vertices of triangle
      if(!inf) { 
         cout<<3<<"\n";
         cerr << "Error: file could not be opened" << endl;
         exit(1);
      }
      while ( !inf.eof() )
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
            // x_l=min(x_l,p.x);
            // y_l=min(y_l,p.y);
            // z_l=min(z_l,p.z);
            // x_m=max(x_m,p.x);
            // y_m=max(y_m,p.y);
            // z_m=max(z_m,p.z);
            vertices.push_back(p);
         }
         else if(q=='f')
         {
            point a,b,c;
            a=vertices[x-1];
            b=vertices[y-1];
            c=vertices[z-1];
            input(a,b,c,out,inf);
         }
      }
   out.close();
   inf.close();
   visualisation();
   return 0;
}
