
#include "util/pch.h"

#include <imgui/imgui.h>

#include "util/ui/pannel_collection.h"
#include "util/ui/imgui_markdown.h"
#include "render/image.h"
#include "events/event.h"
#include "events/application_event.h"
#include "events/mouse_event.h"
#include "events/key_event.h"
#include "application.h"
#include "config/imgui_config.h"
#include "project/project.h"

#include "dashboard.h"


namespace AT {

	#define FONT_ITALLIC                application::get().get_imgui_config_ref()->get_font("italic")
	#define FONT_BOLD                   application::get().get_imgui_config_ref()->get_font("bold")
	#define FONT_HEADER_0               application::get().get_imgui_config_ref()->get_font("header_0")
	#define FONT_HEADER_1               application::get().get_imgui_config_ref()->get_font("header_1")
	#define FONT_HEADER_2               application::get().get_imgui_config_ref()->get_font("header_2")
	#define FONT_HEADER_DEFAULT         application::get().get_imgui_config_ref()->get_font("header_default")
	#define FONT_MONOSPACE_DEFAULT      application::get().get_imgui_config_ref()->get_font("monospace_regular")



    dashboard::dashboard() {
		
		const std::filesystem::path icon_path = CONTENT_PATH / "icons";
#define LOAD_ICON(name)			m_##name##_icon = create_ref<image>(icon_path / #name ".png", image_format::RGBA)
		LOAD_ICON(logo);
		LOAD_ICON(home);
		LOAD_ICON(library);
		LOAD_ICON(settings);
		LOAD_ICON(user);
		LOAD_ICON(folder);
		LOAD_ICON(folder_open);
		LOAD_ICON(folder_add);
		LOAD_ICON(folder_big);
		LOAD_ICON(world);
		LOAD_ICON(warning);
		LOAD_ICON(mesh_asset);
		LOAD_ICON(texture);
		LOAD_ICON(material);
		LOAD_ICON(material_inst);
		LOAD_ICON(relation);
		LOAD_ICON(file);
		LOAD_ICON(file_proc);
		LOAD_ICON(mesh_mini);
		LOAD_ICON(show);
		LOAD_ICON(hide);
		LOAD_ICON(transfrom_translation);
		LOAD_ICON(transfrom_rotation);
		LOAD_ICON(transfrom_scale);
#undef	LOAD_ICON

		// serialize(serializer::option::load_from_file);
	}
    
    
    dashboard::~dashboard() {
		
		// serialize(serializer::option::save_to_file);
		
		m_logo_icon.reset();
		m_home_icon.reset();
		m_library_icon.reset();
		m_settings_icon.reset();
		m_user_icon.reset();
		m_folder_icon.reset();
		m_folder_big_icon.reset();
		m_folder_add_icon.reset();
		m_world_icon.reset();
		m_warning_icon.reset();
		m_mesh_asset_icon.reset();
		m_texture_icon.reset();
		m_material_icon.reset();
		m_material_inst_icon.reset();
		m_relation_icon.reset();
		m_file_icon.reset();
		m_file_proc_icon.reset();
		m_mesh_mini_icon.reset();
		m_show_icon.reset();
		m_hide_icon.reset();
		m_transfrom_translation_icon.reset();
		m_transfrom_rotation_icon.reset();
		m_transfrom_scale_icon.reset();

	}


    // init will be called when every system is initalized
    bool dashboard::init() {

        return true;
    }

    // shutdown will be called bevor any system is deinitalized
    bool dashboard::shutdown() {

        return true;
    }


    void dashboard::update(f32 delta_time) {}


    void dashboard::draw(f32 delta_time) {
		
		auto viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
								ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("main_content_area", nullptr, flags);
		ImGui::PopStyleVar(3);

		sidebar(80.f);		// sidebar_width
		UI::seperation_vertical();

		// Main content area
		ImGui::SameLine();
		ImGui::BeginChild("main_content", ImVec2(0, 0), true);
		main_content_area();
		ImGui::EndChild();

		// // Settings panel (overlay)
		// if (m_show_settings) {
		// }

		ImGui::End();
    }


    void dashboard::on_event(event& event) {}




	void dashboard::sidebar(const f32 sidebar_width) {
		
		const float icon_size = 30.0f;
		const f32 padding_x = (sidebar_width - icon_size - 10) / 2;
		const f32 content_width = sidebar_width - (2 * padding_x);
		const ImVec2 button_dims(content_width, content_width);
		auto draw_sidebar_button = [&](const char* label, ui_section section, ref<image> icon) {
			ImGui::PushStyleColor(ImGuiCol_Button, UI::get_default_gray_ref());
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, UI::get_action_color_gray_hover_ref());
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, UI::get_action_color_gray_active_ref());
			
			char button_lable[256];				// make sure its large enough
			strcpy(button_lable, "##");
			strcat(button_lable, label);
			if (ImGui::Button(button_lable, button_dims))
				m_current_section = section;
			
			ImVec2 button_min = ImGui::GetItemRectMin();
			ImVec2 button_max = ImGui::GetItemRectMax();
			ImVec2 button_center = ImVec2((button_min.x + button_max.x) * 0.5f, (button_min.y + button_max.y) * 0.5f);
			
			const ImVec4 button_color = (section == m_current_section) ? UI::get_action_color_00_default_ref() : ImVec4(1, 1, 1, 1);
			if (icon) {				// Draw icon centered horizontally, near top
				ImVec2 icon_pos(button_center.x - icon_size * 0.5f, button_min.y + button_dims.y * 0.15f);
				ImGui::SetCursorScreenPos(icon_pos);
				ImGui::Image(icon->get(), ImVec2(icon_size, icon_size), ImVec2(0, 0), ImVec2(1, 1), button_color);
			}
			
			ImGui::PopStyleColor(3);
		};


		ImGui::BeginChild("sidebar", ImVec2(sidebar_width, 0), true);

		UI::shift_cursor_pos(padding_x, 20);
		ImGui::Image(m_logo_icon->get(), ImVec2(content_width, content_width));
				
		UI::shift_cursor_pos(padding_x, 40);
		draw_sidebar_button("Home", ui_section::home, m_home_icon);
		
		UI::shift_cursor_pos(padding_x, 10);
		draw_sidebar_button("Projects", ui_section::projects, m_folder_big_icon);

		UI::shift_cursor_pos(padding_x, 10);
		draw_sidebar_button("Library", ui_section::library, m_library_icon);

		float available_height = ImGui::GetContentRegionAvail().y;
		float bottom_buttons_height = (button_dims.y * 2) + (10 * 2); // 2 buttons + 2 spacings
		UI::shift_cursor_pos(padding_x, available_height - bottom_buttons_height);
		draw_sidebar_button("Settings", ui_section::settings, m_settings_icon);
		
		UI::shift_cursor_pos(padding_x, 10);
		draw_sidebar_button("User", ui_section::user, m_user_icon);

		ImGui::EndChild();
	}


	void dashboard::main_content_area() {
		
		ImGui::BeginChild("content", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysUseWindowPadding);
		switch (m_current_section) {
			case ui_section::home:
				
				ImGui::PushFont(FONT_HEADER_0);
				ImGui::Text("Welcome to Gluttony Engine");
                ImGui::PopFont();
				ImGui::Text("TODO: add sime intro text descriping the engine");

				UI::shift_cursor_pos(0, 40);
				ImGui::PushFont(FONT_HEADER_1);
				ImGui::Text("Gluttony Engine News");
                ImGui::PopFont();
				news_panel(); // Add news panel here

				UI::shift_cursor_pos(0, 40);
				ImGui::PushFont(FONT_HEADER_1);
				ImGui::Text("Recent Projects");
                ImGui::PopFont();
				projects_grid();
				break;
				
			case ui_section::projects: {

				ImGui::BeginChild("ProjectsGrid", ImVec2(0, ImGui::GetContentRegionAvail().y - 50), true);
				projects_grid();
				ImGui::EndChild();

				project_control();

				break;
			}
				
			case ui_section::library:
				ImGui::Text("Asset Library");
				// TODO: Library content
				break;
				
			case ui_section::settings:
				ImGui::Text("Settings");
				settings_panel();
				break;
				
			case ui_section::user:
				ImGui::Text("User Profile");
				// TODO: User info
				break;
		}
		
		ImGui::EndChild();
	}

	
	void dashboard::projects_grid() {

		const float item_width = 200.0f;
		const float item_height = 250.0f;
		const ImVec2 item_size(item_width, item_height);
		const float padding = 20.0f;
		const ImVec4 card_bg_color = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);  // Darker gray
		const ImVec4 card_hover_color = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
		const ImVec4 border_color = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
		
		ImGui::Text("Recent Projects");
		ImGui::Separator();
		
		// ImGui::BeginChild("projects_scroll", ImVec2(0, 0), true);
		
		int items_per_row = ImGui::GetContentRegionAvail().x / (item_width + padding);
		if (items_per_row < 1) items_per_row = 1;
		
		int i = 0;
		for (const auto& project : get_user_projects_ref()) {
			if (i++ % items_per_row != 0)
				ImGui::SameLine();
			
			// Start card container
			ImGui::PushStyleColor(ImGuiCol_ChildBg, card_bg_color);
			ImGui::PushStyleColor(ImGuiCol_Border, border_color);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
			
			ImGui::BeginChild(project.name.c_str(), item_size, true);
			
			// Card header - thumbnail
			ImGui::SetCursorPos(ImVec2(10, 10));
			ImGui::Button("Project Thumbnail", ImVec2(item_width - 20, 150));
			
			// Card body - title and description
			ImGui::SetCursorPos(ImVec2(10, 170));
			ImGui::PushTextWrapPos(item_width - 20);
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "%s", project.display_name.c_str());
			
			ImGui::SetCursorPos(ImVec2(10, 190));
			ImGui::TextDisabled("%s", project.description.c_str());
			ImGui::PopTextWrapPos();
			
			ImGui::EndChild();
			ImGui::PopStyleVar(2);
			ImGui::PopStyleColor(2);
			
			switch (UI::get_mouse_interation_on_item()) {
				case UI::mouse_interation::hovered: {

					ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ImGui::GetColorU32(card_hover_color), 4.0f );
					ImGui::BeginTooltip();
					
					// Tooltip content
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", project.display_name.c_str());
					ImGui::Separator();
					
					ImGui::Text("Path: %s", project.project_path.string().c_str());
					ImGui::Text("Version: %s", util::to_string(project.project_version).c_str());
					ImGui::Text("Engine: %s", util::to_string(project.engine_version).c_str());
					
					std::ostringstream oss;
					oss << (u16)project.last_modified.year << '-' << (u16)project.last_modified.month << '-' << (u16)project.last_modified.day
						<< ' ' << (u16)project.last_modified.hour << ':' << (u16)project.last_modified.minute << ':' << (u16)project.last_modified.secund;
					ImGui::Text("Last Modified: %s", oss.str().c_str());
					
					if (!project.tags.empty()) {						// Display tags
						ImGui::Separator();
						ImGui::Text("Tags:");
						for (const auto& tag : project.tags)
							ImGui::BulletText("%s", tag.c_str());
					}
					
					ImGui::EndTooltip();
				} break;

				case UI::mouse_interation::left_double_clicked: {

					const std::string project_path = (project.project_path / project.name).replace_extension(".gltproj").generic_string();
					const std::string command = "cd ~/workspace/gluttony/bin/Debug-linux-x86_64/ && ./gluttony_editor/gluttony_editor " + project_path;
					LOG(Info, "command: " << command)
					util::launch_detached_program(command);
					application::get().close_application();

				} break;
				
				default: break;
			}

		}
		
		// ImGui::EndChild();
	}


	void dashboard::project_control() {

		ImGui::BeginChild("ProjectControls", ImVec2(0, 40), false);
		{
			if (ImGui::Button("Search Project", ImVec2(120, 30))) {
				auto result = util::file_dialog("Find existing Gluttony Project", {{"Gluttony Project", "gltproj"}});
				if (!result.empty()) {
					LOG(Info, "Selected project: " << result.generic_string());
					add_project(result);
				}
			}
			
			ImGui::SameLine();
			if (ImGui::Button("Create Project", ImVec2(120, 30)))
				ImGui::OpenPopup("Create New Project");

				
			if (ImGui::IsPopupOpen("Create New Project")) {
				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			}
			
			if (ImGui::BeginPopupModal("Create New Project", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

				static char display_name[128] = "New Project";
				static char file_name[128] = "new_project";
				static char project_path[256] = "";
				static bool auto_generate = true;
				static bool file_name_changed_manually = false;

				ImGui::InputText("Display Name", display_name, IM_ARRAYSIZE(display_name));
				ImGui::SameLine(); 
				ImGui::TextDisabled("(?)");
				if (ImGui::IsItemHovered()) {
					ImGui::BeginTooltip();
					ImGui::Text("The name shown in the launcher and editor");
					ImGui::EndTooltip();
				}

				ImGui::Checkbox("Auto generate file_name", &auto_generate);
				
				// File Name Field
				if (auto_generate) {

					if (!file_name_changed_manually) {

						std::string generated_name = display_name;
						std::replace(generated_name.begin(), generated_name.end(), ' ', '_');
						std::transform(generated_name.begin(), generated_name.end(), generated_name.begin(), [](unsigned char c){ return std::tolower(c); });
						strncpy(file_name, generated_name.c_str(), IM_ARRAYSIZE(file_name));
					}
					
					ImGui::BeginDisabled();
					ImGui::InputText("File Name", file_name, IM_ARRAYSIZE(file_name));
					ImGui::EndDisabled();

				} else {

					if (ImGui::InputText("File Name", file_name, IM_ARRAYSIZE(file_name), ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_CallbackCharFilter,
						[](ImGuiInputTextCallbackData* data) -> int { return (int)(data->EventChar == ' '); }))		// Lamda: Filter out spaces, if space return 1
						file_name_changed_manually = true;
				}

				// Project Location
				ImGui::InputText("Location", project_path, IM_ARRAYSIZE(project_path));
				ImGui::SameLine();
				if (ImGui::Button("Browse...")) {
					// Pass true as the third parameter to indicate directory selection
					auto path = util::file_dialog("Location of new Gluttony Project", {}, true);
					if (!path.empty())
						strncpy(project_path, path.generic_string().c_str(), IM_ARRAYSIZE(project_path));
				}

				ImGui::Separator();

				// Validation and creation
				bool isValid = strlen(display_name) > 0 && strlen(file_name) > 0 && strlen(project_path) > 0;
				if (!isValid)
					ImGui::BeginDisabled();
				
				if (ImGui::Button("Create", ImVec2(120, 0))) {

					std::filesystem::path full_path = (std::filesystem::path(project_path) / file_name).replace_extension(".gltproj");
					project_data data{};
					data.display_name = display_name;
					data.project_path = full_path;
					create_project(data);
					
					// Reset for next use
					strcpy(display_name, "New Project");
					strcpy(file_name, "new_project");
					file_name_changed_manually = false;
					ImGui::CloseCurrentPopup();
				}
				
				if (!isValid)
					ImGui::EndDisabled();
				
				ImGui::SetItemDefaultFocus();
				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(120, 0))) {			// Reset on cancel

					strcpy(display_name, "New Project");
					strcpy(file_name, "new_project");
					file_name_changed_manually = false;
					ImGui::CloseCurrentPopup();
				}
				
				ImGui::EndPopup();
			}
		}
		ImGui::EndChild();
	}


	void dashboard::news_panel() {
		// Define news items
		const std::vector<std::string> news_items = {
        R"(
# Vulkan Renderer Migration Update

We're excited to announce significant progress in our migration to Vulkan! 
The new Vulkan backend is bringing substantial performance improvements and modern rendering capabilities.

## Key Features Implemented:
- **Image Management**: Full Vulkan support for textures and images
- **Material System**: New material pipeline for opaque and transparent objects
- **Core Renderer**: Improved buffer handling and immediate command submissions

## Upcoming Features:
- Full scene rendering with Vulkan
- Advanced material properties
- Enhanced debugging tools
- Performance optimization pass
        )",
        R"(
# New Asset Library System

We're introducing a completely redesigned asset management system in the upcoming release.

## Key Improvements:
- **Unified Asset Browser**: All assets in one place
- **Smart Search**: Find assets by name, type, or metadata
- **Thumbnail Previews**: Visual browsing for all asset types
- **Version Control**: Track changes to your assets

## Currently in Development:
- Cloud sync for assets
- Collaborative editing features
- Asset dependency tracking
        )",
        R"(
# Ray Tracing Preview Build

Early access to our new hybrid ray tracing renderer is now available!

## Features Included:
- **Real-time Global Illumination**
- **Accurate Reflections**
- **Physically Based Shadows**
- **Denoiser Integration**

## Performance Notes:
- Requires Vulkan 1.2 compatible hardware
- Optimized for NVIDIA RTX and AMD RX 6000 series
- Supports DLSS and FidelityFX Super Resolution
        )"
		};

		// Panel styling
		const ImVec4 card_bg_color = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
		const ImVec4 border_color = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
		const float card_width = 450.0f;
		const float card_spacing = 20.0f;
		
		// Header
		UI::big_text("Latest News & Updates");
		ImGui::Separator();
		ImGui::Spacing();
		
		// Create horizontal scrolling region
		ImGui::BeginChild("NewsScrolling", ImVec2(0, 500), false, ImGuiWindowFlags_HorizontalScrollbar);
		
		bool first_item = true;
		
		for (const auto& news_markdown : news_items) {
			if (!first_item) {
				ImGui::SameLine(0, card_spacing);
			}
			first_item = false;
			
			// Card styling
			ImGui::PushStyleColor(ImGuiCol_ChildBg, card_bg_color);
			ImGui::PushStyleColor(ImGuiCol_Border, border_color);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 15));
			
			// News card
			ImGui::BeginChild(news_markdown.c_str(), ImVec2(card_width, 0), true);
			UI::markdown(news_markdown);
			ImGui::EndChild();
			
			ImGui::PopStyleVar(3);
			ImGui::PopStyleColor(2);
		}
		
		ImGui::EndChild(); // End scrolling region
	}


	void dashboard::settings_panel() {
		
		UI::big_text("General");
		ImGui::Separator();

		UI::big_text("Projects");
		ImGui::Text("Default Project Location");
		static char path_buf[256] = "C:/Projects/";
		ImGui::InputText("##path", path_buf, IM_ARRAYSIZE(path_buf));
		ImGui::SameLine();
		if (ImGui::Button("Browse...")) {
			// File dialog would go here
		}
	}

	
	void dashboard::main_menu_bar() {
		
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New Project")) {}
				if (ImGui::MenuItem("Open Project", "Ctrl+O")) {}
				ImGui::Separator();
				if (ImGui::MenuItem("Settings")) {
					m_show_settings = true;
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Quit", "Alt+F4")) {
					application::get().close_application();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

}
