#include <stdio.h>
#include <math.h>
struct punct{
	float x,y;
};
struct global_shape{
    int shape_type;
    union{
	struct circle{
	struct punct centre;
	float radius;
	float(*Area)(float);
	}c;
	struct triangle{
	struct punct x1,x2,x3;
	float(*Area)(float,float,float,float,float,float);
	}t;
	struct square{
	struct punct x1,x2,x3,x4;
	float(*Area)(float,float,float,float);
	}s;
    }u;
}V[100];
float AreaCircle( float radius)
{
	return 3.14*(radius*radius);
}
void circle(int nr_of_shapes)
{
    for(int i=0;i<nr_of_shapes;i++)
	{
		printf("Please enter the centre of the centre\nx= ");
			scanf("%f",&V[i].u.c.centre.x);
		printf("\ny= ");
			scanf("%f",&V[i].u.c.centre.y);
		printf("\nradius= ");
			scanf("%f",&V[i].u.c.radius);
		V[i].u.c.Area=&AreaCircle;
	}
	printf("\n");
    for(int j=0;j<nr_of_shapes;j++)
    {
	printf("Cricle %d with centre (%f,%f) and radius= %f \n",j+1,V[j].u.c.centre.x,V[j].u.c.centre.y,V[j].u.c.radius);
	printf("Area of the Circle is equal with %f \n",V[j].u.c.Area(V[j].u.c.radius));
    }
}
float AreaTriangle(float x1,float y1, float x2, float y2, float x3, float y3)
{
	return (1/2)*((y2+y1)*(x1-x2))+(1/2)*((y1+y3)*(x3-x1))-(1/2)*((y2+y3)*(x3-x2));
}
void triangle(int nr_of_shapes)
{
    for(int i=0;i<nr_of_shapes;i++)
	{
		printf("Please insert \nx1= ");
			scanf("%f",&V[i].u.t.x1.x);
		printf("\ny1= ");
			scanf("%f",&V[i].u.t.x1.y);
		printf("\nPlease insert\nx2= ");
			scanf("%f",&V[i].u.t.x2.x);
		printf("\ny2= ");
			scanf("%f",&V[i].u.t.x2.y);
		printf("\nPlease insert\nx3=");
			scanf("%f",&V[i].u.t.x3.x);
		printf("\ny3= ");
			scanf("%f",&V[i].u.t.x3.y);
		V[i].u.t.Area=&AreaTriangle;
	}
	printf("\n");
    for(int j=0;j<nr_of_shapes;j++)
	{
	printf("Triangle %d with coordonates p1(%f,%f) p2(%f,%f) p3(%f,%f) \n",j+1,V[j].u.t.x1.x,V[j].u.t.x1.y,V[j].u.t.x2.x,V[j].u.t.x2.y,V[j].u.t.x3.x,V[j].u.t.x3.y);
	printf("Area of the Triangle is equal with %f \n",V[j].u.t.Area(V[j].u.t.x1.x,V[j].u.t.x1.y,V[j].u.t.x2.x,V[j].u.t.x2.y,V[j].u.t.x3.x,V[j].u.t.x3.y));
	}
}
float AreaSquare(float x1,float y1, float x2, float y2)
{
	float l=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	return l*l;
}
void square(int nr_of_shapes)
{
	for(int i=0;i<nr_of_shapes;i++)
	{
		printf("please insert: \n");
		printf("x1= ");
		scanf("%f",&V[i].u.s.x1.x);
		printf("\ny1= ");
		scanf("%f",&V[i].u.s.x1.y);
		printf("\nx2= ");
		scanf("%f",&V[i].u.s.x2.x);
		printf("\ny2= ");
		scanf("%f",&V[i].u.s.x2.y);
		printf("\nx3= ");
		scanf("%f",&V[i].u.s.x3.x);
		printf("\ny3= ");
		scanf("%f",&V[i].u.s.x3.y);
		printf("\nx4= ");
		scanf("%f",&V[i].u.s.x4.x);
		printf("\ny4= ");
		scanf("%f",&V[i].u.s.x4.y);
		V[i].u.s.Area=&AreaSquare;
	}
	printf("\n");
	for(int j=0;j<nr_of_shapes;j++)
	{
	printf("Square %d with: p1(%f,%f);p2(%f,%f);p3(%f,%f);p4(%f,%f)\n",j+1,V[j].u.s.x1.x,V[j].u.s.x1.y,V[j].u.s.x2.x,V[j].u.s.x2.y,V[j].u.s.x3.x,V[j].u.s.x3.y,V[j].u.s.x4.x,V[j].u.s.x4.y);
	printf("Area of the Square is equal with %f \n",V[j].u.s.Area(V[j].u.s.x1.x,V[j].u.s.x1.y,V[j].u.s.x2.x,V[j].u.s.x2.y));
	}
}
int main()
{
	int nr_of_shapes;
	printf("How many shapes do you want to insert? \n");
	scanf("%d",&nr_of_shapes);
	printf("0-Circle \n 1-Triangle \n 2-Square \n");
	scanf("%d",&V[1].shape_type);
	switch(V[1].shape_type)
	{
		case 0: circle(nr_of_shapes);
				break;
		case 1: triangle(nr_of_shapes);
				break;
		case 2:square(nr_of_shapes);
				break;
		default: printf("Error\n");
				break;
	}
	return 0;
}