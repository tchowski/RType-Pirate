/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** hitbox handle thanks to quad tree
*/

#include "systemHitbox.hpp"

systemHitbox::systemHitbox(ComponentTypeList<std::pair<float, float>> &pos, ComponentTypeList<std::pair<unsigned int, unsigned int>> &hb, unsigned int maxDepth, unsigned int maxEntity)
: _cpPosition(pos), _cpHitbox(hb), MAX_DEPTH(maxDepth), MAX_ENTITY(maxEntity)
{
}

std::vector<std::pair<unsigned int, unsigned int>> &systemHitbox::update(float width, float height)
{
    _touching.clear();
    std::vector<std::pair<unsigned int, std::pair<float, float>>> umapToVec;
    for (auto &it:_cpPosition.getComponentsMap()) {
        umapToVec.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
    }
    startQuadtree(width, height, umapToVec, 0);
    return _touching; //return un vecteur indiquant une liste d'ID des deux entités se touchant
}

void systemHitbox::startQuadtree(float width, float height, std::vector<std::pair<unsigned int, std::pair<float, float>>> _posList, unsigned int depth)
{
    //width = largeur, height = hauteur
    auto midwid = width / 2;
    auto midheight = height / 2;
    std::vector<std::pair<unsigned int, std::pair<float, float>>> topleft;
    std::vector<std::pair<unsigned int, std::pair<float, float>>> topright;
    std::vector<std::pair<unsigned int, std::pair<float, float>>> botleft;
    std::vector<std::pair<unsigned int, std::pair<float, float>>> botright;

    // On remplie les vecteurs en fonction de la position relative des entités dans l'écran
    // Il arrive qu'une hitbox dépasse sur deux côtés de l'écran (en franchissant la moitié par exemple)
    // Dans ce cas on duplique juste l'entité pour qu'elle soit checké à la fois la ou elle est placée,
    // Mais aussi là ou elle dépasse
    for (auto &it:_posList) {
        if (it.second.first < midwid) {
            if (it.second.second < midheight) {
                topleft.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
                if (it.second.first + _cpHitbox.getComponent(it.first).first > midwid)
                    topright.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
                if (it.second.second + _cpHitbox.getComponent(it.first).second > midheight)
                    botleft.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
                if (it.second.first + _cpHitbox.getComponent(it.first).first > midwid && it.second.second + _cpHitbox.getComponent(it.first).second > midheight)
                    botright.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
            } else {
                botleft.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
                if (it.second.first + _cpHitbox.getComponent(it.first).first > midwid)
                    botright.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
            }
        } else {
            if (it.second.second < midheight) {
                topright.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
                if (it.second.second + _cpHitbox.getComponent(it.first).second > midheight)
                    botright.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
            } else
                botright.push_back(std::make_pair(it.first, std::make_pair(it.second.first, it.second.second)));
        }
    }
    // Appel récursif de la fonction s'il reste plus de 5 entités dans un meme carrée
    if (topleft.size() > MAX_ENTITY && depth != MAX_DEPTH)
        startQuadtree(midwid, midheight, topleft, depth + 1);
    else
        checkTouching(topleft);
    if (topright.size() > MAX_ENTITY && depth != MAX_DEPTH)
        startQuadtree(midwid, midheight, topright, depth + 1);
    else
        checkTouching(topright);
    if (botright.size() > MAX_ENTITY && depth != MAX_DEPTH)
        startQuadtree(midwid, midheight, botright, depth + 1);
    else
        checkTouching(botright);
    if (botleft.size() > MAX_ENTITY && depth != MAX_DEPTH)
        startQuadtree(midwid, midheight, botleft, depth + 1);
    else
        checkTouching(botleft);
}

void systemHitbox::checkTouching (std::vector<std::pair<unsigned int, std::pair<float, float>>> &vec)
{
    if (vec.size() < 2)
        return;
    int i = 1, start = 0;
    int size = vec.size() - 1;

    while (start != size) {
        if (!(_cpHitbox.getComponent(vec[i].first).first + vec[i].second.first < vec[start].second.first
            || _cpHitbox.getComponent(vec[i].first).first + vec[start].second.first < vec[i].second.first
            || _cpHitbox.getComponent(vec[i].first).second + vec[i].second.second < vec[start].second.second
            || _cpHitbox.getComponent(vec[i].first).second + vec[start].second.second < vec[i].second.second)) {
                _touching.push_back(std::make_pair(vec[i].first, vec[start].first));
        }
        i += 1;
        if (i == size + 1) {
            start += 1;
            i = start + 1;
        }
    }
}