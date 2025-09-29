
#include "util/pch.h"

// #include <filesystem>
// #include <cctype> // for std::isspace
// #include <iostream>
// #include <fstream>
// #include <string>

#include "util/io/io.h"

#include "config.h"


#define REMOVE_WHITE_SPACE(line)                line.erase(std::remove_if(line.begin(), line.end(),                                         \
                                                [](char c) { return c == '\r' || c == '\n' || c == '\t'; }),                                \
                                                line.end());

#define BUILD_CONFIG_PATH(x)	CONFIG_DIR + config::file_type_to_string(x) + CONFIG_FILE_EXTENSION


namespace AT::config {

    //
    void init(std::filesystem::path dir) {

        PROFILE_FUNCTION();

        io::create_directory(dir / CONFIG_DIR);
        LOG(Trace, "Checking Engine config files at: " << dir / CONFIG_DIR);
        for (int i = 0; i <= static_cast<int>(file::input); ++i) {

            std::filesystem::path file_path = dir / CONFIG_DIR / (config::file_type_to_string(static_cast<file>(i)) + CONFIG_FILE_EXTENSION);
            std::ofstream config_file(file_path, std::ios::app);
            if (!config_file.is_open()) {

                LOG(Error, "Failed to open/create config file: [" << file_path << "]");
                return;
            }
            config_file.close();
        }
    }

    //
    void create_config_files_for_project(std::filesystem::path project_dir) {

        io::create_directory(project_dir / CONFIG_DIR);
        LOG(Trace, "Checking project config files at: " << project_dir / CONFIG_DIR);
        for (int i = 0; i <= static_cast<int>(file::input); ++i) {

            std::filesystem::path file_path = project_dir / CONFIG_DIR / (config::file_type_to_string(static_cast<file>(i)) + CONFIG_FILE_EXTENSION);
            std::ofstream config_file(file_path, std::ios::app);
            if (!config_file.is_open()) {

                LOG(Error, "Failed to open/create config file: [" << file_path << "]");
                return;
            }
            config_file.close();
        }
    }

    // 
    bool check_for_configuration(const file target_config_file, const std::string& section, const std::string& key, std::string& value, const bool override) {

        PROFILE_FUNCTION();

        std::filesystem::path file_path = BUILD_CONFIG_PATH(target_config_file);
        std::ifstream configFile(file_path, std::ios::in | std::ios::binary);
        VALIDATE(configFile.is_open(), return false, "", "Failed to open file: [" << file_path << "]");

        bool found_key = false;
        bool section_found = false;
        std::string line;
        std::ostringstream updatedConfig;
        while (std::getline(configFile, line)) {

            REMOVE_WHITE_SPACE(line);

            // Check if the line contains the desired section
            if (line.find("[" + section + "]") != std::string::npos) {

                section_found = true;
                updatedConfig << line << '\n';

                // Read and update the lines inside the section until a line with '[' is encountered
                while (std::getline(configFile, line) && (line.find('[') == std::string::npos)) {

                    REMOVE_WHITE_SPACE(line);

                    std::size_t found = line.find('=');
                    if (found != std::string::npos) {

                        std::string currentKey = line.substr(0, found);
                        if (currentKey == key) {

                            found_key = true;
                            if (override) {

                                // Update the value for the specified key
                                line.clear();
                                line = key + "=" + value;
                            } else {

                                value.clear();
                                value = line.substr(found +1);
                            }
                        }
                    }
                    updatedConfig << line << '\n';
                }

                if (!found_key) {

                    updatedConfig << key + "=" + value << '\n';
                    found_key = true;
                }

                if (!line.empty()) {

                    REMOVE_WHITE_SPACE(line);
                    updatedConfig << line << '\n';
                }
            }
                
            else {

                if(!line.empty())
                    if (line.find("[") == std::string::npos)
                        updatedConfig << line << '\n';
                    else
                        updatedConfig << line << '\n';
            }
        }


        // Close the original file
        configFile.close();

        if (!section_found || found_key || override) {

            // Open the file in truncation mode to clear its content
            std::ofstream outFile(file_path, std::ios::trunc);
            if (!outFile.is_open()) {
                LOG(Error, "problems opening file");
                return false;
            }

            // Write the updated content to the file
            outFile << updatedConfig.str();
            if (!section_found) {

                outFile << "[" << section << "]" << '\n';
                outFile << key << "=" << value << '\n';
            }

            outFile.close();
            // LOG(Trace, "File [" << file_path << "] updated with [" << std::setw(20) << std::left << section << " / " << std::setw(25) << std::left << key << "]: [" << value << "]");
        }
        return false; // Key not found
    }

    // ----------------------------------------------- file path resolution ----------------------------------------------- 

    std::filesystem::path get_filepath_from_configtype(std::filesystem::path root, file type) { return root / CONFIG_DIR / (config::file_type_to_string(type) + CONFIG_FILE_EXTENSION); }

    std::filesystem::path get_filepath_from_configtype_ini(std::filesystem::path root, file type) { return root / CONFIG_DIR / (config::file_type_to_string(type) + INI_FILE_EXTENSION); }

    //
    std::string file_type_to_string(file type) {

        static const std::unordered_map<file, std::string> typeStrings{
            {file::ui, "ui" },
            {file::imgui, "imgui"},
            {file::input, "input"},
            {file::app_settings, "app_settings"},
        };

        auto it = typeStrings.find(type);
        return (it != typeStrings.end()) ? it->second : "unknown";
    }

}
