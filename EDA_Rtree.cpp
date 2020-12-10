#include <iostream>
#include <vector>
using namespace std;

struct node
{
	string nom;
	int x,y;
	node(int x,int y)
	{
		this->x=x;
		this->y=y;
	}
};
bool operator ==(const node &p1,const node &p2)
{
 	if(p1.x==p2.x && p1.y==p2.y)
 		return true;
 	else
 		return false;
}
struct region
{
	string nom;
	bool eshoja;
	int xizq,xder,yar,yab;
	vector<node> hojas;
};
vector<node> nodos;
class Rtree
{
private:
	Rtree* raiz;
public:
	int di;
	Rtree(int dim);
	vector<Rtree*> Rt;
	vector<region> Re;
};
Rtree::Rtree(int d)
{
	this->di=d;
	this->Rt=vector<Rtree*>(d,NULL);
}
vector<int> areaMin(vector<node> &A)
{
	int xd=A[0].x,yar=A[0].y,xi=A[0].x,yab=A[0].y;
	for(int i=1;i<A.size();i++)
	{
		if(A[i].x>xd || A[i].x<xi)
		{
			if(A[i].x>xd)
			{
				xd=A[i].x;
			}
			else if(A[i].x<xi)
			{
				xi=A[i].x;
			}
		}
		if(A[i].y>yar || A[i].y<yab)
		{
			if(A[i].y>yar)
			{
				yar=A[i].y;
			}
			else if(A[i].y<yab)
			{
				yab=A[i].y;
			}
		}
	}
	vector<int> v(4);
	v[0]=xi;
	v[1]=xd;
	v[2]=yar;
	v[3]=yab;
	return v;
}
vector<int> areaMinRe(vector<region> A)
{
	int xd=A[0].xder,xi=A[0].xizq,yr=A[0].yar,yb=A[0].yab;
	for(int i=1;i<A.size();i++)
	{
		if(xd<A[i].xder || xi>A[i].xizq)
		{
			if(xd<A[i].xder)
			{
				xd=A[i].xder;
			}
			else if(xi>A[i].xizq)
			{
				xi=A[i].xizq;
			}
		}
		if(yr<A[i].yar || yb>A[i].yab)
		{
			if(yr<A[i].yar)
			{
				yr=A[i].yar;
			}	
			else if(yb>A[i].yab)
			{
				yb=A[i].yab;
			}
		}
	}
	vector<int> v(4);
	v[0]=xi;
	v[1]=xd;
	v[2]=yr;
	v[3]=yb;
	return v;
}
bool dentroArea(region a,node b)
{
	if(b.x<=a.xder && b.x>=a.xizq && b.y<=a.yar && b.y>=a.yab)
	{
		return true;
	}
	else
		return false;
}
void split(Rtree* A)
{
	Rtree* X=new Rtree(A->di);
	region Xr;
	vector<int> v=areaMinRe(A->Re);
	Xr.xizq=v[0];
	Xr.xder=v[1];
	Xr.yar=v[2];
	Xr.yab=v[3];
	Xr.eshoja=false;
	X->Re.push_back(Xr);
	X->Rt[0]=A;
	A=X;
}

void insert(Rtree* A,node a)
{
	if(A->Re.empty())
	{
		region B;
		B.xizq=a.x;
		B.xder=a.x;
		B.yar=a.y;
		B.yab=a.y;
		B.eshoja=true;
		B.hojas.push_back(a);
		A->Re.push_back(B);	
	}
	else
	{
		bool realizdo=false;
		for(int i=0;i<A->Re.size();i++)
		{
			if(dentroArea(A->Re[i],a))
			{
				if(A->Re[i].eshoja==true)
				{
					A->Re[i].hojas.push_back(a);
					realizdo=true;
					break;
				}
				else
				{
					insert(A->Rt[i],a);
					realizdo=true;
				}
			}
		}
		if(realizdo==false)
		{
			if(A->Re.size()<A->di)
			{
				region B;
				B.xizq=a.x;
				B.xder=a.x;
				B.yar=a.y;
				B.yab=a.y;
				B.eshoja=true;
				B.hojas.push_back(a);
				A->Re.push_back(B);
			}
			else
			{
				split(A);
			}
		}
	}
}
int main()
{
	node i(5,4);
	node b(5,4);
	Rtree* A=new Rtree(3);
	insert(A,i);
	cout<<"Nodo insertado x:"<<A->Re[0].hojas[0].x<<" y:"<<A->Re[0].hojas[0].y<<endl;
	
	return 0;
}