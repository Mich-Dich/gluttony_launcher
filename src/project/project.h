#pragma once

#include "util/pch.h"
#include "util/data_structures/UUID.h"
#include "util/io/serializer_yaml.h"

namespace AT {
  
    struct project_data {

		UUID						ID;
		std::string					name{};						// this name is the name of the solution & export-folder
		std::string					display_name{};				// this name will be used in the launcher and editor
		std::string					description{};				// A short description of this project
		std::filesystem::path		project_path{};				// system path to the prject file for a gluttony project
		system_time					last_modified{};			// Timestamp of when the project was last modified.
		std::vector<std::string>	tags{};						// Tags or categories

		version						engine_version{};			// version of the engine used, used by launcher, engine, editor, ...
		version						project_version{};			// version of this project, mostly uesfull to the user for version managemant
	
		// paths
		std::filesystem::path		build_path{};				// system path for exported builds
		std::filesystem::path		start_world{};				// system path to the first world when executoing project
		std::filesystem::path		editor_start_world{};		// system path to the first world when developing the project

		// Dependencies
		//std::unordered_set<std::string> engine_plugins;		// List of enabled or required plugins
		//std::unordered_set<std::string> external_libraries;	// List of external libraries


		static bool is_valid_project_path(const std::filesystem::path& project_file) { return (!project_file.empty() && std::filesystem::exists(project_file) && project_file.extension() == PROJECT_EXTENTION); }

		void serialize_projects_data(const serializer::option option) {

			for (const auto& entry : std::filesystem::directory_iterator(project_path)) {

				if (entry.is_directory() || entry.path().extension() != PROJECT_EXTENTION)
					continue;

				serializer::yaml(entry.path(), "project_data", option)
					.entry(KEY_VALUE(ID))
					.entry(KEY_VALUE(name))
					.entry(KEY_VALUE(display_name))
					.entry(KEY_VALUE(description))
					.entry(KEY_VALUE(project_path))
					.entry(KEY_VALUE(last_modified))
					.entry(KEY_VALUE(engine_version))
					.entry(KEY_VALUE(project_version))
					.entry(KEY_VALUE(build_path))
					.entry(KEY_VALUE(start_world))
					.entry(KEY_VALUE(editor_start_world))
					// .unordered_set(KEY_VALUE(engine_plugins))
					// .unordered_set(KEY_VALUE(external_libraries))
					.vector("tags", tags, [&](serializer::yaml& inner, u64 x) {
						inner.entry("tag", tags[x]);
					});

				break;
			}
		}

	};


	// MAYBE: change to project_manager class

	std::vector<project_data>& get_user_projects_ref();

	void create_dummy_projects();
	
	void create_project(project_data data);

	void add_project(const std::filesystem::path& path);
}
