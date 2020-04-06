#include <iostream>
#include <memory>
#include <time.h>
#include <chrono>

#include "Node.h"
#include "Algorithms.h"
#include "Point2D.h"

int main(void)
{
   srand((size_t)time(NULL));
   std::unique_ptr<Algorithms> algorithms = std::make_unique<Algorithms>();
   std::unique_ptr<Node> root = std::make_unique<Node>(nullptr, 'A', 0);
   Node* finalCity = nullptr;
   std::chrono::time_point<std::chrono::steady_clock> start;
   std::chrono::duration<float> duration;
   int** matrix = nullptr;
   std::vector<Point2D> points;
   size_t howManyCities;
   std::cout << "Podaj ilosc miast: ";
   std::cin >> howManyCities;

   matrix = algorithms->createMatrix(howManyCities);
   algorithms->randPoints(points, howManyCities);
   algorithms->calculateDistances(matrix, howManyCities, points);

   algorithms->printMatrix(matrix, howManyCities);
   root->makeTree(howManyCities, matrix);

   std::cout << "\n";
   std::cout << "Przeszukiwanie pelne wglab\n";

   start = std::chrono::high_resolution_clock::now();
   finalCity = algorithms->pelneWglab(root.get());
   duration = std::chrono::high_resolution_clock::now()-start;

   std::cout << "Wykonano w czasie: " << duration.count() * 1000.f << " ms\n";
   std::cout << "Pelna odleglosc: " << finalCity->cost << "\n";
   finalCity->printParents();

   std::cout << "\n\n";
   std::cout << "Przeszukiwanie pelne wszerz\n";

   start = std::chrono::high_resolution_clock::now();
   finalCity = algorithms->pelneWszerz(root.get());
   duration = std::chrono::high_resolution_clock::now() - start;

   std::cout << "Wykonano w czasie: " << duration.count() * 1000.f << " ms\n";
   std::cout << "Pelna odleglosc: " << finalCity->cost << "\n";
   finalCity->printParents();

   std::cout << "\n\n";
   std::cout << "Algorytm zachlanny\n";

   start = std::chrono::high_resolution_clock::now();
   finalCity = algorithms->zachlannie(root.get());
   duration = std::chrono::high_resolution_clock::now() - start;

   std::cout << "Wykonano w czasie: " << duration.count() * 1000.f << " ms\n";
   std::cout << "Pelna odleglosc: " << finalCity->cost << "\n";
   finalCity->printParents();

   std::cout << "\n\n";
   std::cout << "Algorytm a*\n";

   start = std::chrono::high_resolution_clock::now();
   finalCity = algorithms->aStar(root.get(), matrix);
   duration = std::chrono::high_resolution_clock::now() - start;

   std::cout << "Wykonano w czasie: " << duration.count() * 1000.f << " ms\n";
   std::cout << "Pelna odleglosc: " << finalCity->cost << "\n";
   finalCity->printParents();

   std::cout << "\n";

   algorithms->destroyMatrix(matrix, howManyCities);

   return 0;
}