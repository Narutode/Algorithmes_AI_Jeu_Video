#include <vector>
#include "GOAP.h"
#include "Node.h"

Node* findNodeWithLowestCost(const vector<Node*>& nodeList)
{
    if (nodeList.empty()) {
        return nullptr; // Si la liste est vide, retournez nullptr.
    }

    Node* lowestCostNode = nodeList[0]; // Initialisez avec le premier n�ud.
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

const Action* const GOAP::findBestAction()
{
    vector<Node*> openNodes; // Utilisez une liste normale plut�t qu'un pointeur
    openNodes.push_back(new Node(ws.firstAction, nullptr));
    list<EffectCondition> unfulfilledConditions;

    // Initialisez la liste des pr�conditions non remplies avec les pr�conditions de la premi�re action
    for (const pair<EffectCondition, int>* cond : *ws.firstAction->getConditions()) {
        unfulfilledConditions.push_back(cond->first);
    }

    while (!openNodes.empty())
    {
        // Trouvez le n�ud avec le co�t le plus bas dans openNodes
        Node* currentNode = findNodeWithLowestCost(openNodes);

        // V�rifiez si les pr�conditions de ce n�ud sont satisfaites
        if (ws.CheckCondition(*currentNode->action))
        {
            // Les pr�conditions sont satisfaites, donc ce n�ud est valide directement
            currentNode->cost=0;
        }

        // Parcourez les effets du n�ud actuel
        for (const pair<EffectCondition, int>* effect : *(currentNode->action->getEffects())) {
            // Retirez l'effet des pr�conditions non remplies
            unfulfilledConditions.remove(effect->first);
        }

        // Ajoutez les pr�conditions non remplies du n�ud actuel � la liste des pr�conditions � remplir
        for (const pair<EffectCondition, int>* cond : *(currentNode->action->getConditions())) {
            unfulfilledConditions.push_back(cond->first);
        }

        // �valuez le nombre de pr�conditions non satisfaites
        int unfulfilledCount = unfulfilledConditions.size();

        // Si le nombre est inf�rieur � celui des autres chemins, ajoutez le noeud � openNodes
        if (unfulfilledCount <= getLowestUnfulfilledCount(openNodes))
        {
            // Ajoutez le n�ud � la liste des n�uds ouverts
            openNodes.push_back(currentNode);
        }
        else
        {
            // Ce n�ud n'est pas le bon, retirez-le
            openNodes.remove(currentNode);
            delete currentNode; // Lib�rez la m�moire du n�ud
        }
    }

    // � ce stade, openNodes contient les noeuds valides avec les co�ts les plus bas.
    // Vous pouvez maintenant choisir la meilleure action parmi ces n�uds.

    // ...

    // Assurez-vous de g�rer correctement la m�moire en supprimant les n�uds et les listes non n�cessaires.
}