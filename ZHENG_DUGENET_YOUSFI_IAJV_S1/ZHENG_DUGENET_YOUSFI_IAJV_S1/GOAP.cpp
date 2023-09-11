#include "GOAP.h"
#include "Node.h"

const Action* const GOAP::findBestAction()
{
    list<Node*> openNodes; // Utilisez une liste normale plutôt qu'un pointeur
    openNodes.push_back(new Node(ws.firstAction, nullptr));
    list<EffectCondition> unfulfilledConditions;

    // Initialisez la liste des préconditions non remplies avec les préconditions de la première action
    for (EffectCondition cond : *ws.firstAction->getConditions()) {
        unfulfilledConditions.push_back(cond);
    }

    while (!openNodes.empty())
    {
        // Trouvez le nœud avec le coût le plus bas dans openNodes
        Node* currentNode = findNodeWithLowestCost(openNodes);

        // Vérifiez si les préconditions de ce nœud sont satisfaites
        if (ws.CheckCondition(*currentNode->action))
        {
            // Les préconditions sont satisfaites, donc ce nœud est valide directement
            currentNode->cost=0;
        }

        // Parcourez les effets du nœud actuel
        for (const pair<EffectCondition, int>& effect : *(currentNode->action->getEffects())) {
            // Retirez l'effet des préconditions non remplies
            unfulfilledConditions.remove(effect.first);
        }

        // Ajoutez les préconditions non remplies du nœud actuel à la liste des préconditions à remplir
        for (EffectCondition cond : *(currentNode->getAction()->getConditions())) {
            unfulfilledConditions.push_back(cond);
        }

        // Évaluez le nombre de préconditions non satisfaites
        int unfulfilledCount = countUnfulfilledConditions(unfulfilledConditions);

        // Si le nombre est inférieur à celui des autres chemins, ajoutez le noeud à openNodes
        if (unfulfilledCount <= getLowestUnfulfilledCount(openNodes))
        {
            // Ajoutez le nœud à la liste des nœuds ouverts
            openNodes.push_back(currentNode);
        }
        else
        {
            // Ce nœud n'est pas le bon, retirez-le
            openNodes.remove(currentNode);
            delete currentNode; // Libérez la mémoire du nœud
        }
    }

    // À ce stade, openNodes contient les noeuds valides avec les coûts les plus bas.
    // Vous pouvez maintenant choisir la meilleure action parmi ces nœuds.

    // ...

    // Assurez-vous de gérer correctement la mémoire en supprimant les nœuds et les listes non nécessaires.
}