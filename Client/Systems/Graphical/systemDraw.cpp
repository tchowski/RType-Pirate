/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** draw all the entites that we want to draw
*/

#include "systemDraw.hpp"

systemDraw::systemDraw(GraphicalLib &graph, ComponentTypeList<std::pair<float, float>> &positions, ComponentTypeList<std::string> &sprites)
:  GLib(graph), myPositionComponents(positions), mySpritesComponents(sprites)
{
}

bool draw(const int &id,
GraphicalLib &GLib,
const std::string &path,
const std::pair<float, float> &pos)
{
    if (GLib.addElement(id, pos)) {
        if (!GLib.loadSprite(path)) {
            GLib.removeElement(id);
            draw(id, GLib, "Placeholder", pos);
            return true;
        }
    }
    if (!GLib.addElementSprite(id, path))
        if (!GLib.loadSprite(path)) {
            GLib.removeElement(id);
            draw(id, GLib, "Placeholder", pos);
            return true;
        }
    GLib.addElementSprite(id, path);
    if (GLib.setElementSprite(id, path, path))
        if (GLib.updateElement(id, pos))
            GLib.drawSprite(id);
    return true;
}

void systemDraw::update(const bool &all, const std::vector<unsigned int> &ids, const std::vector<std::string> &names)
{
    std::map<int, std::string> ordered = {};
    
    for (auto component : mySpritesComponents.getComponentsMap())
        ordered.insert({component.first, component.second});
    GLib.clear();
    GLib.animate();
    if (all) {
        for (std::map<int, std::string>::iterator spr = ordered.begin();
        spr != ordered.end(); spr++) {
            if (myPositionComponents.hasThisComponent(spr->first)) {
                auto path = spr->second;
                auto pos = myPositionComponents.getComponent(spr->first);
                draw(spr->first, GLib, path, pos);
            }
        }
    } else {
        if (!names.empty()) {
            for (std::map<int, std::string>::iterator spr = ordered.begin();
            spr != ordered.end(); spr++) {
                if (std::find(names.begin(), names.end(), spr->second) != names.end()) {
                    auto path = spr->second;
                    auto pos = myPositionComponents.getComponent(spr->first);
                    draw(spr->first, GLib, path, pos);
                }
            }
        }
        if (!ids.empty()) {
            for (std::map<int, std::string>::iterator spr = ordered.begin();
            spr != ordered.end(); spr++) {
                if (std::find(ids.begin(), ids.end(), spr->first) != ids.end())
                    if (myPositionComponents.hasThisComponent(spr->first)) {
                        auto path = spr->second;
                        auto pos = myPositionComponents.getComponent(spr->first);
                        draw(spr->first, GLib, path, pos);
                    }  
            }
        }
    }
    GLib.drawText();
    GLib.display();
    GLib.clearText();
}
