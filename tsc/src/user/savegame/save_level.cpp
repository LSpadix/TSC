/***************************************************************************
 * save_level.cpp - Handler for saving a cLevel instance to a savegame.
 *
 * Copyright © 2003 - 2011 Florian Richter
 * Copyright © 2013 - 2014 The TSC Contributors
 ***************************************************************************/
/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "save_level.hpp"
#include "../../core/game_core.hpp"

using namespace TSC;

/* *** *** *** *** *** *** *** cSave_Level_Object *** *** *** *** *** *** *** *** *** *** */
cSave_Level_Object_Property::cSave_Level_Object_Property(const std::string& new_name /* = "" */, const std::string& new_value /* = "" */)
{
    m_name = new_name;
    m_value = new_value;
}

/* *** *** *** *** *** *** *** cSave_Level_Object *** *** *** *** *** *** *** *** *** *** */
cSave_Level_Object::cSave_Level_Object(void)
{
    m_type = TYPE_UNDEFINED;
}

cSave_Level_Object::~cSave_Level_Object(void)
{
    m_properties.clear();
}

bool cSave_Level_Object::exists(const std::string& val_name)
{
    for (Save_Level_Object_ProprtyList::iterator itr = m_properties.begin(); itr != m_properties.end(); ++itr) {
        cSave_Level_Object_Property obj = (*itr);
        if (obj.m_name.compare(val_name) == 0) {
            // found
            return 1;
        }
    }
    // not found
    return 0;
}

std::string cSave_Level_Object::Get_Value(const std::string& val_name)
{
    for (Save_Level_Object_ProprtyList::iterator itr = m_properties.begin(); itr != m_properties.end(); ++itr) {
        cSave_Level_Object_Property obj = (*itr);
        if (obj.m_name.compare(val_name) == 0) {
            // found
            return obj.m_value;
        }
    }
    // not found
    return "";
}

/* *** *** *** *** *** *** *** cSave_Level *** *** *** *** *** *** *** *** *** *** */

cSave_Level::cSave_Level(void)
{
    // level
    m_level_pos_x = 0.0f;
    m_level_pos_y = 0.0f;
}

cSave_Level::~cSave_Level(void)
{
    for (cSprite_List::iterator itr = m_regular_objects.begin(); itr != m_regular_objects.end(); ++itr) {
        delete *itr;
    }

    m_regular_objects.clear();

    for (cSprite_List::iterator itr = m_spawned_objects.begin(); itr != m_spawned_objects.end(); ++itr) {
        delete *itr;
    }

    m_spawned_objects.clear();
}

void cSave_Level::Save_To_Node(xmlpp::Element* p_parent_node)
{
    cSprite_List::const_iterator iter;

    // <level>
    xmlpp::Element* p_node = p_parent_node->add_child("level");
    Add_Property(p_node, "level_name", m_name);

    // Player position. Only save that for the active level.
    if (!Is_Float_Equal(m_level_pos_x, 0.0f) && !Is_Float_Equal(m_level_pos_y, 0.0f)) {
        Add_Property(p_node, "player_posx", m_level_pos_x);
        Add_Property(p_node, "player_posy", m_level_pos_y);
    }

    /* Custom data a script writer wants to store; empty if the
     * script writer didn’t hook into the on_load and on_save
     * events. */
    if (!m_mruby_data.empty())
        Add_Property(p_node, "mruby_data", m_mruby_data);

    // The regular objects.
    // <objects_data>
    xmlpp::Element* p_objects_data_node = p_node->add_child("objects_data");
    for(iter=m_regular_objects.begin(); iter != m_regular_objects.end(); iter++) {
        cSprite* p_sprite = (*iter);

        /* TODO: Have the sprite itself decide whether it wants to be
         * saved or not by not adding anything to the node and
         * returning false from Save_To_Savegame_XML_Node(). For now,
         * just assume TYPE_UNDEFINED sprites, i.e. all static
         * nonmoving sprites, do not need to be saved. */
        if (p_sprite->m_type != TYPE_UNDEFINED) {
            xmlpp::Element* p_object_node = p_objects_data_node->add_child("object");
            p_sprite->Save_To_Savegame_XML_Node(p_object_node);
        }
    }
    // </objects_data>

    // The spawned objects. These have always to be saved.
    // <spawned_objects>
    xmlpp::Element* p_spawned_node = p_node->add_child("spawned_objects");
    for(iter=m_spawned_objects.begin(); iter != m_spawned_objects.end(); iter++) {
        cSprite* p_sprite = (*iter);
        p_sprite->Save_To_XML_Node(p_spawned_node);
    }
    // </spawned_objects>

    //</level>
}
