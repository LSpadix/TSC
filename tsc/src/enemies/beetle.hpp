/***************************************************************************
 * beetle.hpp
 *
 * Copyright © 2012-2017 The TSC Contributors
 ***************************************************************************/
/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TSC_BEETLE_HPP
#define TSC_BEETLE_HPP
#include "enemy.hpp"

namespace TSC {

    class cBeetle: public cEnemy {
    public:
        cBeetle(cSprite_Manager* p_sprite_manager);
        cBeetle(XmlAttributes& attributes, cSprite_Manager* p_sprite_manager);
        virtual ~cBeetle();

        virtual void DownGrade(bool force = false);

        float Get_Rest_Living_Time();
        void Set_Rest_Living_Time(float time);
        void Set_Color(DefaultColor color);
        DefaultColor Get_Color();

        // Private, don’t use. These are used by cBeetleBarrage to make
        // the beetles move up from the beetle barrage before entering
        // normal behaviour.
        bool Is_Doing_Beetle_Barrage_Generation();
        void Do_Beetle_Barrage_Generation(float distance);

        virtual Col_Valid_Type Validate_Collision(cSprite* p_obj);
        virtual void Handle_Collision_Player(cObjectCollision* p_collision);
        virtual void Handle_Collision_Massive(cObjectCollision* p_collision);

        virtual cBeetle* Copy() const;
        virtual void Draw(cSurface_Request* p_request = NULL);
        virtual void Update();

        virtual void Editor_Activate();

        virtual xmlpp::Element* Save_To_XML_Node(xmlpp::Element* p_element);

    protected:
        virtual std::string Get_XML_Type_Name();

        // Editor callbacks
        bool Editor_Direction_Select(const CEGUI::EventArgs& event);
        bool Editor_Color_Select(const CEGUI::EventArgs& event);

    private:
        // Constructor common stuff
        void Init();

        float m_rest_living_time;
        DefaultColor m_color;

        // These are only important when the beetle is generated by
        // a cBeetleBarrage (by calling Do_Beetle_Barrage_Generation()).
        float m_generation_max_y;
        float m_generation_in_progress;
    };

}

#endif
