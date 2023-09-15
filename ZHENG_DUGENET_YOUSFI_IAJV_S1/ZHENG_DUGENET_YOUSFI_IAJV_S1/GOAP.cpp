#include <iostream>
#include <map>

#include "GOAP.h"
#include "Node.h"

GOAP::GOAP(WorldState* curWS)
{
    ws = new WorldState(curWS);
    mapAction = map<EffectCondition, Action>();
    ActionsList = vector<Action>();
    firstAction = Action();

    vector<pair<EffectCondition, unsigned int>> effects;
    vector<pair<EffectCondition, unsigned int>> conditions;

    //Action create infantry
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_FOOD, 10));
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_PLACE, 1));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_INF, 1));
    ActionsList.push_back(Action("CreateInfantry", effects, conditions, 3));
    mapAction[EC_INF] = Action("CreateInfantry", effects, conditions, 3);
    conditions.clear();
    effects.clear();

    //Action create cavalry
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_FOOD, 30));
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_PLACE, 2));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_CAV, 1));
    ActionsList.push_back(Action("CreateCavalry", effects, conditions, 4));
    mapAction[EC_CAV] = Action("CreateCavalry", effects, conditions, 4);
    conditions.clear();
    effects.clear();

    //Action create range
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_FOOD, 10));
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_PLACE, 1));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_RAN, 1));
    ActionsList.push_back(Action("CreateRange", effects, conditions, 2));
    mapAction[EC_RAN] = Action("CreateRange", effects, conditions, 2);
    conditions.clear();
    effects.clear();

    //Action create villager
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_FOOD, 5));
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_PLACE, 1));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_VIL, 1));
    ActionsList.push_back(Action("CreateVillager", effects, conditions, 1));
    mapAction[EC_VIL] = Action("CreateVillager", effects, conditions, 1);
    conditions.clear();
    effects.clear();

    //Action create house
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_WOOD, 10));
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_VIL, 1));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_PLACE, 5));
    ActionsList.push_back(Action("CreateHouse", effects, conditions, 3));
    mapAction[EC_PLACE] = Action("CreateHouse", effects, conditions, 3);
    conditions.clear();
    effects.clear();

    //Action get wood
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_VIL, 1));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_WOOD, 1));
    ActionsList.push_back(Action("GetWood", effects, conditions, 2));
    mapAction[EC_WOOD] = Action("GetWood", effects, conditions, 2);
    conditions.clear();
    effects.clear();

    //Action get food
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_VIL, 1));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_FOOD, 1));
    ActionsList.push_back(Action("GetFood", effects, conditions, 2));
    mapAction[EC_FOOD] = Action("GetFood", effects, conditions, 2);
    conditions.clear();
    effects.clear();

    //Action attack
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_INF, ws->EnnemyCav));
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_RAN, ws->EnnemyInf));
    conditions.push_back(pair<EffectCondition, unsigned int>(EC_CAV, ws->EnnemyRan));
    effects.push_back(pair<EffectCondition, unsigned int>(EC_WIN, 1));
    ActionsList.push_back(Action("Attack", effects, conditions, 1));
    mapAction[EC_WIN] = Action("Attack", effects, conditions, 1);
    firstAction = Action("Attack", effects, conditions, 1);
    conditions.clear();
    effects.clear();
};


const unsigned int GOAP::getLowestUnfulfilledCount(const vector<Node> nodeList)
{
    if (nodeList.empty()) {
        return 0; // Si la liste est vide, il n'y a aucun élément non satisfait.
    }

    unsigned int lowestUnfulfilledCount = numeric_limits<unsigned int>::max(); // Initialisez avec une valeur maximale.

    for (const Node node : nodeList)
    {
        // Vérifiez le nombre d'éléments non satisfaits dans chaque nœud et mettez à jour le plus bas trouvé.
        unsigned int unfulfilledCount = node.preCondition.size();

        if (unfulfilledCount < lowestUnfulfilledCount)
        {
            lowestUnfulfilledCount = unfulfilledCount;
        }
    }

    return lowestUnfulfilledCount;
}

const Node GOAP::findBestAction()
{
    std::vector<Node> openNodes = vector<Node>();
    std::vector<Action> parentAction = vector<Action>();
    std::vector<EffectCondition> unfulfilledConditions = vector<EffectCondition>();
    openNodes.reserve(1000);

    // Initialisez la liste des préconditions non remplies avec les préconditions de la première action
    for (const std::pair<EffectCondition, unsigned int>& cond : firstAction.getEffects()) {
        unfulfilledConditions.push_back(cond.first);
    }

    openNodes.push_back(Node(firstAction, std::vector<Action>(), unfulfilledConditions));

    while (!openNodes.empty())
    {
        // Trouvez le nœud avec le coût le plus bas dans openNodes
        int lowestCost = std::numeric_limits<int>::max();
        auto currentNodeIte = openNodes.begin();

        for (auto it = openNodes.begin(); it != openNodes.end(); ++it)
        {
            if (it->preCondition.size() < static_cast<unsigned int>(lowestCost))
            {
                lowestCost = static_cast<int>(it->preCondition.size());
                currentNodeIte = it;
            }
        }
        
        Node currentNode = *currentNodeIte;
        parentAction.push_back(currentNode.action);
        // Parcourez les effets du nœud actuel
        for (const pair<EffectCondition, unsigned int>& effect : currentNode.action.getEffects()) {
            for (unsigned int i = 0; i < effect.second; i++) {
                // Retirez l'effet des préconditions non remplies
                auto iteEff = std::find(currentNode.preCondition.begin(), currentNode.preCondition.end(), effect.first);
                if (iteEff != currentNode.preCondition.end()) {
                    currentNode.preCondition.erase(iteEff);
                }
            }
        }

        //Ajouter ses conditions
        for (const pair<EffectCondition, unsigned int>& cond : currentNode.action.getConditions())
            for (int i = 0; i < cond.second; i++)
                currentNode.preCondition.push_back(cond.first);

        for (const pair<EffectCondition, unsigned int>& cond : currentNode.action.getConditions()) {
            bool conditionSatisfied = ws->CheckCondition(cond);
            if (!conditionSatisfied) {
                Action act = mapAction[cond.first];
                for (int i = 0; i < cond.second; i += currentNode.action.getEffects().front().second)
                    //Passage des conditions aux noeuds suivant
                    openNodes.push_back(Node(act, parentAction, currentNode.preCondition));
            }
        }

        // Vérifiez si les préconditions de ce nœud sont satisfaites
        bool lastCond = true;
        if (currentNode.preCondition.size() == 0) {
            for (const pair<EffectCondition, unsigned int>& cond : currentNode.action.getConditions()) {
                if (!ws->CheckCondition(cond)) {
                    lastCond = false;
                    break;
                }
            }
        }
        else
            lastCond = false;
       

        if (lastCond)
        {
            return currentNode;
        }

        // Supprimez le nœud actuel de la liste des nœuds ouverts
        openNodes.erase(currentNodeIte);
    }

    // Si aucun nœud avec toutes les préconditions satisfaites n'est trouvé, retournez un nœud vide
    return Node(Action(), std::vector<Action>(), std::vector<EffectCondition>());
}