
#pragma once


namespace AT { class image; }

namespace AT {

    class event;


    class dashboard {
    public:

        dashboard();
        ~dashboard();

        bool init();
        void update(f32 delta_time);
        void draw(f32 delta_time);
        bool shutdown();

        void on_event(event& event);

    private:

        void main_menu_bar();
        void settings_panel();
        void news_panel();
        void project_control();
        void projects_grid();
        void main_content_area();
        void sidebar(const f32 sidebar_width);

    	bool 				m_show_settings = false;
        
		ref<image>		    m_logo_icon;
		ref<image>		    m_home_icon;
		ref<image>		    m_library_icon;
		ref<image>		    m_settings_icon;
		ref<image>		    m_user_icon;
		ref<image>		    m_transfrom_translation_icon;
		ref<image>		    m_transfrom_rotation_icon;
		ref<image>		    m_transfrom_scale_icon;
		ref<image>		    m_folder_icon;
		ref<image>		    m_folder_add_icon;
		ref<image>		    m_folder_open_icon;
		ref<image>		    m_folder_big_icon;
		ref<image>		    m_world_icon;
		ref<image>		    m_warning_icon;
		ref<image>		    m_mesh_asset_icon;
		ref<image>		    m_texture_icon;
		ref<image>		    m_material_icon;
		ref<image>		    m_material_inst_icon;
		ref<image>		    m_relation_icon;
		ref<image>		    m_file_icon;
		ref<image>		    m_file_proc_icon;
		ref<image>		    m_mesh_mini_icon;
		ref<image>		    m_show_icon;
		ref<image>		    m_hide_icon;
    };
}
