#include <vector>
#include "GOAP.h"
#include "Node.h"

Node* GOAP::findNodeWithLowestCost(const list<Node*>& nodeList)
{
    if (nodeList.empty()) {
        return nullptr; // Si la liste est vide, retournez nullptr.
    }

    Node* lowestCostNode = nodeList.front(); // Initialisez avec le premier nœud.
    unsigned int lowestCost = lowestCostNode->cost;

    for (Node* node : nodeList)
    {
        if (node->cost < lowestCost)
        {
            lowestCost = node->cost;
            lowestCostNode = node;
        }
    }

    return lowestCostNode;
}

const unsigned int getLowestUnfulfilledCount(const list<const Node*>& nodeList)
{
    if (nodeList.empty()) {
        return 0; // Si la liste est vide, il n'y a aucun élément non satisfait.
    }

    unsigned int lowestUnfulfilledCount = numeric_limits<unsigned int>::max(); // Initialisez avec une valeur maximale.

    for (const Node* node : nodeList)
    {
        // Vérifiez le nombre d'éléments non satisfaits dans chaque nœud et mettez à jour le plus bas trouvé.
        unsigned int unfulfilledCount = node->unfulfilledCount;

        if (unfulfilledCount < lowestUnfulfilledCount)
        {
            lowestUnfulfilledCount = unfulfilledCount;
        }
    }

    return lowestUnfulfilledCount;
}

const Node* const GOAP::findBestAction()
{
    list<Node*> openNodes; // Utilisez une liste normale plutôt qu'un pointeur
    openNodes.push_back(new Node(ws->firstAction, nullptr));
    list<EffectCondition>* unfulfilledConditions = new list<EffectCondition>();

    // Initialisez la liste des préconditions non remplies avec les préconditions de la première action
    for (const pair<EffectCondition, int>* cond : *ws->firstAction->getConditions()) {
        unfulfilledConditions->push_back(cond->first);
    }

    while (!openNodes.empty())
    {
        // Trouvez le nœud avec le coût le plus bas dans openNodes
        Node* currentNode = findNodeWithLowestCost(openNodes);

        // Vérifiez si les préconditions de ce nœud sont satisfaites
        unsigned int unCount = ws->CheckAction(*currentNode->action);
        if (unCount == 0)
        {
            // Les préconditions sont satisfaites, donc ce nœud est valide directement
            currentNode->cost=0;
            currentNode->unfulfilledCount = 0;
        }
        else
        {
            //On ajoute les actions 
            currentNode->unfulfilledCount = unCount;
            for (const pair<EffectCondition, int>* cond : *(currentNode->action->getConditions())) {
                if (!ws->CheckCondition(cond)) {
                    for (const Action* act : *ws->ActionsList) {
                        for (const pair<EffectCondition, int>* eff : *(currentNode->action->getEffects())) {
                            if (eff->first == cond->first) {
                                openNodes.push_back(new Node(act, currentNode));
                                break;
                            }
                        }
                    }
                }
            }
        }

        // Parcourez les effets du nœud actuel
        for (const pair<EffectCondition, int>* effect : *(currentNode->action->getEffects())) {
            // Retirez l'effet des préconditions non remplies
            if (find(unfulfilledConditions->begin(), unfulfilledConditions->end(), effect->first) != unfulfilledConditions->end()) {
                unfulfilledConditions->remove(effect->first);
                currentNode->unfulfilledCount -= effect->second;
            }
        }

        // Ajoutez les préconditions non remplies du nœud actuel à la liste des préconditions à remplir
        for (const pair<EffectCondition, int>* cond : *(currentNode->action->getConditions())) {
            if(!ws->CheckCondition(cond))
                unfulfilledConditions->push_back(cond->first);
        }

        // Évaluez le nombre de préconditions non satisfaites
        int unfulfilledCount = unfulfilledConditions->size();
  
        openNodes.remove(currentNode);
    }
    return openNodes.front();
    // À ce stade, openNodes contient les noeuds valides avec les coûts les plus bas.
    // Vous pouvez maintenant choisir la meilleure action parmi ces nœuds.

    // ...

    // Assurez-vous de gérer correctement la mémoire en supprimant les nœuds et les listes non nécessaires.
}