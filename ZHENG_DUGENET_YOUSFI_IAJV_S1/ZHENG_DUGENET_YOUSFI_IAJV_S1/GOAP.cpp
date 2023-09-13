#include <vector>
#include "GOAP.h"
#include "Node.h"
#include <iostream>

Node GOAP::findNodeWithLowestCost(const vector<Node>& nodeList)
{
    Node lowestCostNode = nodeList.front(); // Initialisez avec le premier nœud.
    unsigned int lowestCost = lowestCostNode.preCondition.size();

    for (Node node : nodeList)
    {
        if (node.preCondition.size() < lowestCost)
        {
            lowestCost = node.preCondition.size();
            lowestCostNode = node;
        }
    }

    return lowestCostNode;
}

const unsigned int GOAP::getLowestUnfulfilledCount(const vector<Node*> nodeList)
{
    if (nodeList.empty()) {
        return 0; // Si la liste est vide, il n'y a aucun élément non satisfait.
    }

    unsigned int lowestUnfulfilledCount = numeric_limits<unsigned int>::max(); // Initialisez avec une valeur maximale.

    for (const Node* node : nodeList)
    {
        // Vérifiez le nombre d'éléments non satisfaits dans chaque nœud et mettez à jour le plus bas trouvé.
        unsigned int unfulfilledCount = node->preCondition.size();

        if (unfulfilledCount < lowestUnfulfilledCount)
        {
            lowestUnfulfilledCount = unfulfilledCount;
        }
    }

    return lowestUnfulfilledCount;
}

const Node* const GOAP::findBestAction()
{
    vector<Node*> endNode;
    vector<Node*> openNodes;
    list<EffectCondition> unfulfilledConditions;
    openNodes.reserve(1000);
    // Initialisez la liste des préconditions non remplies avec les préconditions de la première action
    for (const pair<EffectCondition, unsigned int>* cond : *ws->firstAction->getConditions()) {
        unfulfilledConditions.push_back(cond->first);
    }
    vector<Action*> emptyList;
    openNodes.push_back(new Node(ws->firstAction, emptyList, ws, unfulfilledConditions));
    auto currentNodeIte = openNodes.begin();
    Node* currentNode = currentNodeIte[0];
    while (!openNodes.empty())
    {
        // Trouvez le nœud avec le coût le plus bas dans openNodes
        int lowestCost = numeric_limits<int>::max();

        for (auto it = openNodes.begin(); it != openNodes.end(); ++it)
        {
            if ((*it)->preCondition.size() < lowestCost)
            {
                lowestCost = (*it)->preCondition.size();
                currentNodeIte = it;
                currentNode = currentNodeIte[0];
            }
        }
        //currentNode = findNodeWithLowestCost(openNodes);
        //cout << currentNode->action->Name << endl;
        // Vérifiez si les préconditions de ce nœud sont satisfaites
        unsigned int unCount = ws->CheckActionCondition(*currentNode->action);
        //cout << currentNode->action->getConditions()->size() << endl;

        if (unCount == 0)
        {
            // Les préconditions sont satisfaites, donc ce nœud est valide directement
            //currentNode->cost=0;
            currentNode->preCondition.clear();
            currentNode->worldstate.Execution(currentNode->action, false);
        }
        else
        {
            //On ajoute les actions 
            vector<Action*> parentNodes = currentNode->prevNode;
            parentNodes.push_back(currentNode->action);
            for (const pair<EffectCondition, unsigned int>* cond : *(currentNode->action->getConditions())) {
                bool t = ws->CheckCondition(cond);
                if (!t) {
                    for (Action* act : *ws->ActionsList) {
                        for (const pair<EffectCondition, unsigned int>* eff : *(act->getEffects())) {
                            if (eff->first == cond->first) {
                                openNodes.push_back(new Node(act, parentNodes, currentNode->worldstate, currentNode->preCondition));
                                break;
                            }
                        }
                    }
                }
            }
        }

        // Parcourez les effets du nœud actuel
        for (const pair<EffectCondition, unsigned int>* effect : *(currentNode->action->getEffects())) {
            // Retirez l'effet des préconditions non remplies
            if (find(currentNode->preCondition.begin(), currentNode->preCondition.end(), effect->first) != currentNode->preCondition.end()) {
                currentNode->preCondition.remove(effect->first);
                //currentNode->unfulfilledCount -= effect->second;
            }
        }

        // Ajoutez les préconditions non remplies du nœud actuel à la liste des préconditions à remplir
        for (const pair<EffectCondition, unsigned int>* cond : *(currentNode->action->getConditions())) {
            if (!ws->CheckCondition(cond))
                currentNode->preCondition.push_back(cond->first);
        }

        // Évaluez le nombre de préconditions non satisfaites
        unsigned int unfulfilledCount = currentNode->preCondition.size();

        if (unfulfilledCount > getLowestUnfulfilledCount(openNodes)) 
        {
            openNodes.erase(currentNodeIte);
        }
        if (currentNode->preCondition.size()==0)
        {
            return currentNode;
            //endNode.push_back(currentNode);
            //openNodes.erase(currentNodeIte);
        }
    }
    return endNode.front();
}