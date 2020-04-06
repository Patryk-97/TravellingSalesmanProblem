#pragma once

#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <math.h>

#include "Node.h"
#include "Point2D.h"

class Algorithms
{
public:
   Node* pelneWglab(Node* startCity);
   Node* pelneWszerz(Node* startCity);
   Node* zachlannie(Node* startCity);
   Node* aStar(Node* startCity, int** matrix);
   /*
   Heurystyka w moim przypadku polega na sumie odleg³oœci od miasta do najbardziej
   oddalonego nieodwiedzonego miasta oraz odleg³oœci od tego najbardziej oddalonego
   miasta do miasta pocz¹tkowego.
*/
   void calculateHeuristic(Node* city, int** matrix);
   int calculateDistance(Point2D pointA, Point2D pointB);
   int ileCyfr(int liczba);
   void getSpace(int n);
   void printMatrix(int** matrix, size_t matrixLen);
   int** createMatrix(size_t matrixLen);
   void destroyMatrix(int** matrix, size_t matrixLen);
   void randPoints(std::vector<Point2D>& points, size_t matrixLen);
   void calculateDistances(int** matrix, size_t matrixLen, const std::vector<Point2D>& points);
};

#endif // __ALGORITHMS_H__