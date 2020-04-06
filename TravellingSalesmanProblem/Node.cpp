#include "Node.h"

Node::~Node()
{
   for (size_t i = 0; i < children.size(); i++)
   {
      delete children[i];
   }
}

bool Node::checkIfParent(uint8_t cityId)
{
   // locals
   bool rV = false;

   for (Node* node_iter = this; node_iter != nullptr; node_iter = node_iter->parent)
   {
      if (node_iter->cityId == cityId)
      {
         rV = true;
         break;
      }
   }

   return rV;
}

void Node::makeTree(int howMuchCities, int** tab)
{
   if (this->level == howMuchCities - 1)
   {
      Node* newCity = new Node(this, 'A', howMuchCities);
      newCity->cost = this->cost + tab[0][this->cityId - 'A'];
      this->children.push_back(newCity);
      return;
   }
   for (uint8_t i = 'B'; i < 'A' + howMuchCities; i++)
   {
      if (this->checkIfParent(i) == false)
      {
         Node* newCity = new Node(this, i, this->level + 1);
         newCity->cost = this->cost + tab[this->cityId - 'A'][i - 'A'];
         this->children.push_back(newCity);
         newCity->makeTree(howMuchCities, tab);
      }
   }
}

void Node::printParents(void) const
{
   if (this->parent != nullptr)
   {
      this->parent->printParents();
   }
   std::cout << "[" << this->cityId << "]";
   if (this->children.size() > 0)
   {
      std::cout << " -> ";
   }
}

void Node::printTree(void) const
{
   if (this->children.size() == 0)
   {
      this->printParents();
      std::cout << this->cost << "\n";
      return;
   }
   else
   {
      for (size_t i = 0; i < this->children.size(); i++)
      {
         this->children[i]->printTree();
      }
   }
}