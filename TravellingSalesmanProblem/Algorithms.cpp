#include "Algorithms.h"

Node* Algorithms::pelneWglab(Node* startCity)
{
   int minCost = std::numeric_limits<int>::max();
   Node* finalCity = nullptr;
   Node* tempCity = nullptr;
   std::stack<Node*> cityStack;
   cityStack.push(startCity);

   while (false == cityStack.empty())
   {
      tempCity = cityStack.top();
      cityStack.pop();
      if (tempCity->children.size() > 0)
      {
         for (size_t i = tempCity->children.size() - 1;;)
         {
            cityStack.push(tempCity->children[i]);
            if (i == 0)
            {
               break;
            }
            --i;
         }
      }
      if (tempCity->children.size() == 0)
      {
         if (tempCity->cost < minCost)
         {
            minCost = tempCity->cost;
            finalCity = tempCity;
         }
      }
   }
   return finalCity;
}

Node* Algorithms::pelneWszerz(Node* startCity)
{
   int minCost = std::numeric_limits<int>::max();
   Node* finalCity = nullptr;
   Node* tempCity = nullptr;
   std::queue<Node*> cityQueue;
   cityQueue.push(startCity);

   while (false == cityQueue.empty())
   {
      tempCity = cityQueue.front();
      cityQueue.pop();
      for (size_t i = 0; i < tempCity->children.size(); i++)
      {
         cityQueue.push(tempCity->children[i]);
      }
      if (tempCity->children.size() == 0)
      {
         if (tempCity->cost < minCost)
         {
            minCost = tempCity->cost;
            finalCity = tempCity;
         }
      }
   }
   return finalCity;
}

Node* Algorithms::zachlannie(Node* startCity)
{
   if (startCity->children.size() == 0)
   {
      return startCity;
   }
   int minCost = std::numeric_limits<int>::max();
   size_t minCostIndex = 0;
   for (size_t i = 0; i < startCity->children.size(); i++)
   {
      if (startCity->children[i]->cost < minCost)
      {
         minCost = startCity->children[i]->cost;
         minCostIndex = i;
      }
   }
   return zachlannie(startCity->children[minCostIndex]);
}

Node* Algorithms::aStar(Node* startCity, int** matrix)
{
   Node* tempCity = nullptr;
   std::priority_queue < Node*, std::vector<Node*>, NodeComparator > cityQueue;
   cityQueue.push(startCity);

   while (false == cityQueue.empty())
   {
      tempCity = cityQueue.top();
      cityQueue.pop();
      if (1 == tempCity->children.size() && tempCity->children[0]->cityId == 'A')
      {
         tempCity = tempCity->children[0];
         break;
      }
      for (size_t i = 0; i < tempCity->children.size(); i++)
      {
         calculateHeuristic(tempCity->children[i], matrix);
         cityQueue.push(tempCity->children[i]);
      }
   }
   return tempCity;
}

/*
   Heurystyka w moim przypadku polega na sumie odleg³oœci od miasta do najbardziej
   oddalonego nieodwiedzonego miasta oraz odleg³oœci od tego najbardziej oddalonego
   miasta do miasta pocz¹tkowego.
*/
void Algorithms::calculateHeuristic(Node* city, int** matrix)
{
   int maxDistance = 0;
   size_t maxDistanceIndex = 0;
   for (size_t i = 0; i < city->children.size(); i++)
   {
      if (matrix[city->cityId - 'A'][city->children[i]->cityId - 'A'] > maxDistance)
      {
         maxDistance = matrix[city->cityId - 'A'][city->children[i]->cityId - 'A'];
         maxDistanceIndex = i;
      }
   }
   city->heuristic = maxDistance + matrix[0][city->children[maxDistanceIndex]->cityId - 'A'];
}

int Algorithms::calculateDistance(Point2D pointA, Point2D pointB)
{
   return (int)sqrt(pow((double)pointB.x - pointA.x, 2) + pow((double)pointB.y - pointA.y, 2));
}

int Algorithms::ileCyfr(int liczba)
{
   return liczba == 0 ? 0 : 1 + ileCyfr(liczba / 10);
}

void Algorithms::getSpace(int n)
{
   for (int i = 0; i < n; i++)
   {
      std::cout << " ";
   }
}

void Algorithms::printMatrix(int** matrix, size_t matrixLen)
{
   std::cout << "    ";
   for (size_t i = 0; i < matrixLen; i++)
   {
      std::cout << (uint8_t)(i + 'A') << "   ";
   }
   std::cout << "\n";
   for (size_t i = 0; i < matrixLen; i++)
   {
      for (size_t j = 0; j < matrixLen; j++)
      {
         if (j == 0)
         {
            std::cout << (uint8_t)('A' + i) << "   ";
         }
         std::cout << matrix[i][j];
         int digits = ileCyfr(matrix[i][j]);
         getSpace(5 - (digits > 0 ? digits : 1));
      }
      std::cout << "\n";
   }
}

int** Algorithms::createMatrix(size_t matrixLen)
{
   int** matrix = new int* [matrixLen];
   for (size_t i = 0; i < matrixLen; i++)
   {
      matrix[i] = new int[matrixLen];
      memset(matrix[i], 0, sizeof(int) * matrixLen);
   }
   return matrix;
}

void Algorithms::destroyMatrix(int** matrix, size_t matrixLen)
{
   for (size_t i = 0; i < matrixLen; i++)
   {
      delete[] matrix[i];
   }
   delete[] matrix;
}

void Algorithms::randPoints(std::vector<Point2D>& points, size_t matrixLen)
{
   points.clear();
   for (size_t i = 0; i < matrixLen; i++)
   {
      points.push_back({ rand() % 1000, rand() % 1000 });
   }
}

void Algorithms::calculateDistances(int** matrix, size_t matrixLen, const std::vector<Point2D>& points)
{
   for (size_t i = 0; i < matrixLen; i++)
   {
      for (size_t j = i + 1; j < matrixLen; j++)
      {
         int distance = calculateDistance(points[i], points[j]);
         matrix[i][j] = distance;
         matrix[j][i] = distance;
      }
   }
}