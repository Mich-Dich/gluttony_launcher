
#include "util/pch.h"

#include "project.h"


namespace AT {

	static std::vector<project_data>						s_user_projects{};
	
    std::vector<project_data>& get_user_projects_ref()      { return s_user_projects; }

    
    system_time create_time(int year, int month, int day, int hour, int min, int sec, int ms) {
		return {
			static_cast<u16>(year),
			static_cast<u8>(month),
			static_cast<u8>(day),
			static_cast<u8>(0), // day_of_week (we'll leave as 0)
			static_cast<u8>(hour),
			static_cast<u8>(min),
			static_cast<u8>(sec),
			static_cast<u16>(ms)
		};
	}



	void create_dummy_projects() {
		s_user_projects.clear();
		
		auto add_project = [&](const char* path, const char* display, const char* name, 
							const version& eng_ver, const version& proj_ver, const char* build_path,
							const char* start_world, const char* editor_world,
							const system_time& mod_time, const char* desc, 
							std::initializer_list<const char*> tag_list) {
			project_data proj;
			proj.project_path = path;
			proj.display_name = display;
			proj.name = name;
			proj.engine_version = eng_ver;
			proj.project_version = proj_ver;
			proj.build_path = build_path;
			proj.start_world = start_world;
			proj.editor_start_world = editor_world;
			proj.last_modified = mod_time;
			proj.description = desc;
			
			for (const char* tag : tag_list) {
				proj.tags.push_back(tag);
			}
			
			s_user_projects.push_back(proj);
		};
		
		// Create dummy projects - note explicit version{} construction
		add_project("~/workspace/gluttony_test_project", "Simple test project", "test_project",
					version{1, 2, 3}, version{0, 9, 1}, "C:/Builds/RayTracer",
					"worlds/main_world.glt", "worlds/editor_start.glt",
					create_time(2025, 3, 15, 14, 30, 15, 500),
					"Advanced ray tracing implementation with global illumination",
					{"graphics", "demo", "tech-demo"});
		
		add_project("~/workspace/gluttony_test_project", "Physics Simulation", "physics_sim",
					version{1, 2, 2}, version{1, 0, 0}, "D:/Builds/PhysicsSim",
					"worlds/physics_demo.glt", "worlds/editor_physics.glt",
					create_time(2025, 2, 28, 10, 15, 30, 200),
					"Real-time physics simulation with soft body dynamics",
					{"physics", "simulation", "educational"});
		
		add_project("~/workspace/gluttony_test_project", "Fluid Dynamics", "fluid_sim",
					version{1, 2, 3}, version{0, 5, 0}, "E:/Builds/FluidSim",
					"worlds/fluid_demo.glt", "worlds/editor_fluid.glt",
					create_time(2025, 4, 5, 16, 45, 0, 0),
					"Real-time fluid simulation using SPH method",
					{"physics", "fluid", "simulation", "tech-demo"});
		
		add_project("~/workspace/gluttony_test_project", "Space Shooter", "space_shooter",
					version{1, 1, 5}, version{2, 0, 3}, "F:/Builds/SpaceShooter",
					"worlds/level1.glt", "worlds/editor_level1.glt",
					create_time(2025, 3, 22, 9, 0, 0, 0),
					"Top-down space shooter with procedurally generated levels",
					{"game", "action", "procedural", "arcade"});
		
		add_project("~/workspace/gluttony_test_project", "Modern House", "modern_house",
					version{1, 2, 1}, version{1, 2, 0}, "G:/Builds/HouseDesign",
					"worlds/house_exterior.glt", "worlds/editor_house.glt",
					create_time(2025, 4, 10, 13, 20, 45, 750),
					"Architectural visualization of a modern house design",
					{"archviz", "design", "realistic", "lighting"});
		
		add_project("~/workspace/gluttony_test_project", "AI Behavior Demo", "ai_behavior",
					version{1, 2, 3}, version{0, 7, 2}, "C:/Builds/AI_Demo",
					"worlds/ai_test.glt", "worlds/editor_ai.glt",
					create_time(2025, 3, 30, 11, 10, 30, 0),
					"Demonstration of advanced AI pathfinding and behavior trees",
					{"ai", "tech-demo", "pathfinding", "behavior"});
		
		add_project("~/workspace/gluttony_test_project", "RPG Prototype", "rpg_prototype",
					version{1, 2, 0}, version{0, 3, 5}, "D:/Builds/RPG_Prototype",
					"worlds/village.glt", "worlds/editor_village.glt",
					create_time(2025, 2, 14, 15, 45, 0, 0),
					"Prototype for a fantasy RPG with quest system and inventory",
					{"game", "rpg", "fantasy", "prototype"});
		
		add_project("~/workspace/gluttony_test_project", "VR Experience", "vr_showcase",
					version{1, 2, 3}, version{1, 0, 0}, "E:/Builds/VR_Showcase",
					"worlds/vr_main.glt", "worlds/editor_vr.glt",
					create_time(2025, 4, 12, 17, 30, 0, 250),
					"Immersive VR experience showcasing engine capabilities",
					{"vr", "tech-demo", "immersive", "experimental"});
		
		add_project("~/workspace/gluttony_test_project", "Sculpture Garden", "sculpture_garden",
					version{1, 1, 8}, version{0, 4, 2}, "F:/Builds/SculptureGarden",
					"worlds/garden_main.glt", "worlds/editor_garden.glt",
					create_time(2025, 3, 18, 12, 0, 0, 500),
					"Virtual art gallery showcasing 3D sculptures in a garden setting",
					{"art", "gallery", "environment", "showcase"});
		
		add_project("~/workspace/gluttony_test_project", "Ray Tracing Demo", "raytracer_demo",
					version{1, 2, 2}, version{0, 8, 1}, "G:/Builds/SolarSystem",
					"worlds/solar_system.glt", "worlds/editor_space.glt",
					create_time(2025, 4, 8, 14, 5, 15, 0),
					"Educational simulation of our solar system with accurate orbits",
					{"education", "space", "simulation", "science"});
	}


	void create_project(project_data data) {

		LOG(Info, "creating project [" << data.display_name << "] at [" << data.build_path.generic_string() << "]");

	}

	
	void add_project(const std::filesystem::path& path) {


	}


}