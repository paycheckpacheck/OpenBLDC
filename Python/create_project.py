import os
import shutil
import sys

# basepath should be a subset of base content path


# Update paths relative to your directory structure
base_content_path = r'C:\Users\pache\OneDrive\Documents'


# Dictionary to define folder names and their default content source paths
default_folders = {
    'MATLAB': None,      # No default contents to copy
    'LTSpice': None,     # No default contents to copy
    'KiCad': None,       # No default contents to copy
    'EasyEDA': os.path.join(base_content_path, 'EasyEDA-Pro','libraries'),  # Path to EasyEDA base library
    'Python': None,      # No default contents to copy
    'Arduino': os.path.join(base_content_path, 'Arduino', 'libraries'),  # Path to Arduino libraries
    'Datasheets': None,
    'Embedded':None
}


def create_project(name):
    # Get the current working directory to set the path relative to it
    base_path = os.path.abspath(os.path.join(os.getcwd(), os.pardir))  # Move up one directory from current

    print(base_path)
    project_path = os.path.join(base_path, name)

    # Create the base project folder if it doesn't exist
    os.makedirs(project_path, exist_ok=True)

    # Create each directory inside the project and copy default contents if applicable
    for folder, source_path in default_folders.items():
        folder_path = os.path.join(project_path, folder, "libraries")
        os.makedirs(folder_path, exist_ok=True)
        print(folder)

        # Check if the folder has default content to be copied
        if source_path:
            if os.path.exists(source_path):
                try:
                    shutil.copytree(source_path, folder_path, dirs_exist_ok=True)
                    print(f"Copied default contents to: {folder_path}")
                except Exception as e:
                    print(f"Error while copying default contents to {folder}: {e}")
            else:
                print(f"Source path for {folder} does not exist: {source_path}")

    print(f"Project '{name}' created successfully at {project_path}")


if __name__ == "__main__":
    # Check if the project name is provided
    if len(sys.argv) < 2:
        print("Please provide a project name.")
        sys.exit(1)

    # Use the first command-line argument as the project name
    project_name = sys.argv[1]
    create_project(project_name)

