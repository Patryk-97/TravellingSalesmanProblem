#pragma once

#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <stdint.h>
#include <vector>

struct Node
{
   Node(Node* parent, uint8_t cityId, uint8_t level) :
      parent(parent), cityId(cityId), level(level), cost(0), heuristic(0)
   {
      
   }
   ~Node();

   Node* parent;
   uint8_t cityId;
   uint8_t level;
   int cost;
   int heuristic;
   std::vector<Node*> children;

   bool checkIfParent(uint8_t cityId);
   void makeTree(int howMuchCities, int** tab);
   void printParents(void) const;
   void printTree(void) const;
};

struct NodeComparator
{
   bool operator() (Node* city1, Node* city2) const
   {
      return (city1->cost + city1->heuristic) > (city2->cost + city2->heuristic);
   }
};

#endif // __NODE_H__