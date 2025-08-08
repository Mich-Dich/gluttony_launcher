# Gluttony Engine Launcher

<table style="border: none; width: 100%;">
  <tr>
    <td>
      <img src="assets/images/logo.png?raw=true" alt="Main Logo" title="mich" style="width: 100; height: 100; border: none;">
    </td>
    <td style="vertical-align: middle;">
      The official launcher for the <strong>Gluttony Engine</strong> - your gateway to creating amazing games
    </td>
  </tr>
</table>


## Overview

The Gluttony Engine Launcher is a desktop application that helps you manage your game development projects built with the Gluttony Engine. It provides an intuitive interface to create, organize, and launch your projects while keeping track of engine versions, project dependencies, and development resources.

## Features

- **Project Management**: Create, browse, and launch game projects
- **Project Discovery**: Search and import existing projects
- **Engine News**: Stay updated with the latest engine developments
- **Configuration**: Set default paths and preferences
- **Asset Library**: Browse and manage game assets (coming soon)
- **User Profiles**: Manage your developer identity (coming soon)

## Installation

### Prerequisites
- Linux OS or Windows (Mac not supported)
- C++20 compatible compiler
- Python 3 (for setup)

### Installation Steps (only if you want to develop the launcher)
1. Clone the repository:
   ```bash
   git clone https://github.com/your-org/gluttony-launcher.git
   cd gluttony-launcher
   ```

2. Run the setup script:
   ```bash
   python3 setup.py
   ```

3. Build the application:
   ```bash
   cd .vscode && ./build.sh
   make -j
   ```

4. Run the launcher:
   ```bash
   bin/Debug-linux-x86_64/gluttony-launcher/gluttony-launcher
   ```

## Using the Launcher

### Main Interface
The launcher interface is divided into several sections:

1. **Sidebar Navigation** (left):
   - Home Dashboard
   - Projects
   - Asset Library
   - Settings
   - User Profile

2. **Main Content Area** (center):
   - Displays content based on selected section

### Key Functionality

#### Creating a New Project
1. Select the "Projects" section
2. Click "Create Project"
3. Fill in project details:
   - Display Name (shown in launcher)
   - File Name (auto-generated or custom)
   - Project Location
4. Click "Create"

#### Opening an Existing Project
1. Select the "Projects" section
2. Click "Search Project"
3. Navigate to your `.gltproj` file
4. Double-click a project to launch the engine editor

#### Viewing Engine News
1. Select the "Home" section
2. Scroll through the news cards
3. Click on any card to expand details

#### Configuring Settings
1. Select the "Settings" section
2. Adjust preferences:
   - Default project location
   - Editor preferences
   - Display options

## Project Structure

The launcher organizes projects with the following information:
- **Display Name**: User-friendly name
- **Project Path**: Location on disk
- **Engine Version**: Compatible engine version
- **Last Modified**: Timestamp of recent changes
- **Tags**: Categorization labels

## Troubleshooting

### Log Files
Logs are located at:
```
bin/Debug<your-system>/gluttony_launcher/logs/
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Gluttony Engine**
*Learn more about the engine: [github.com/Mich-Dich/gluttony](https://github.com/your-org/gluttony-engine)*
