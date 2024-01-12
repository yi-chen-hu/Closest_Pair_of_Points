#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define POINTSIZE 100000

struct Point {
    double x;
    double y;
};

//============================================================================//
//                                prototype                                   //
//============================================================================//
bool cmpX(Point p1, Point p2);
bool cmpY(Point p1, Point p2);
double distance(Point a, Point b);
double bruteForce(Point pointArr[], int numOfPoints, int low);
double divide(Point pointArr[], int low, int high);
double combine(Point pointArr[], int low, int mid, int high, double minDistLeftPart, double minDistRightPart);

//============================================================================//
//                                   main                                     //
//============================================================================//
int main()
{
    int PATNUM;
    cin >> PATNUM;
    for (int patcount = 0; patcount < PATNUM; patcount++)
    {
        int POINTNUM;
        cin >> POINTNUM;
        Point point[POINTSIZE];
        for (int pointCount = 0; pointCount < POINTNUM; pointCount++)
        {
            cin >> point[pointCount].x >> point[pointCount].y;
        }
        sort(point, point + POINTNUM, cmpX);
        double dis = divide(point, 0, POINTNUM - 1);
        cout << dis << endl;
    }
    return 0;
}

//============================================================================//
//                                 function                                   //
//============================================================================//
bool cmpX(Point p1, Point p2)
{
    return p1.x < p2.x;
}

bool cmpY(Point p1, Point p2)
{
    return p1.y < p2.y;
}

double distance(Point p1, Point p2)
{
    return (double)sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(Point pointArr[], int numOfPoints, int low)
{
    double min = 30000; // According to spec, there is no way to exceed 30000
    for (int i = 0; i < numOfPoints; i++)
    {
        for (int j = i + 1; j < numOfPoints; j++)
        {
            if (distance(pointArr[low + i], pointArr[low + j]) < min)
            {
                min = distance(pointArr[low + i], pointArr[low + j]);
            }
        }
    }
    return min;
}

double divide(Point pointArr[], int low, int high)
{
    //============================================================================//
    //          return the distance when there are only 2 or 3 points             //
    //============================================================================//
    int numOfPoints = high - low + 1;
    if (numOfPoints <= 3) // 2 or 3 points remain
    {
        return bruteForce(pointArr, numOfPoints, low);
    }

    //============================================================================//
    //                 divide the array into left and right parts                 //
    //============================================================================//
    int mid = (low + high) / 2;
    double minDistLeftPart = divide(pointArr, low, mid);
    double minDistRightPart = divide(pointArr, mid + 1, high);
    
    return combine(pointArr, low, mid, high, minDistLeftPart, minDistRightPart);
}

double combine(Point pointArr[], int low, int mid, int high, double minDistLeftPart, double minDistRightPart)
{
    double delta = (minDistLeftPart < minDistRightPart) ? minDistLeftPart : minDistRightPart;
    //============================================================================//
    //                  save the points around middle line first                  //
    //============================================================================//
    Point midPoint = pointArr[mid];
    Point pointAroundMiddle[POINTSIZE];
    int size = 0;
    for (int i = low; i <= high; i++)
    {
        if (abs(pointArr[i].x - midPoint.x) < delta)
        {
            pointAroundMiddle[size++] = pointArr[i];
        }
    }

    //============================================================================//
    //               find the minimum distance around middle line                 //
    //============================================================================//
    sort(pointAroundMiddle, pointAroundMiddle + size, cmpY);
    double min = delta;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size && (pointAroundMiddle[j].y - pointAroundMiddle[i].y) < min; j++)
        {
            if (distance(pointAroundMiddle[i], pointAroundMiddle[j]) < min)
            {
                min = distance(pointAroundMiddle[i], pointAroundMiddle[j]);
            }
        }
    }
    return delta < min ? delta : min;
}