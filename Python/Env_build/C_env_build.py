import argparse
import os
from Env_pack import *


def create_file(file_path, file_name, file_data):
    new_path = os.path.join(file_path, file_name)
    with open(new_path, 'w') as f:
        f.write(file_data)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='C env creator')

    parser.add_argument('--path', dest='path', action='store', required=False, default=r"C:\Projects",
                        help='path to create project')
    parser.add_argument('--name', dest='name', action='store', required=True, help='project name')

    args = parser.parse_args()

    # create dir
    project_name = args.name
    project_path = os.path.join(args.path, project_name)
    if not os.path.exists(project_path):
        os.makedirs(project_path)

    # vscode path
    vscode_path = os.path.join(project_path, ".vscode")
    if not os.path.exists(vscode_path):
        os.makedirs(vscode_path)

    create_file(vscode_path, "c_cpp_properties.json", C_Cpp_Properties_template)
    create_file(vscode_path, "launch.json", launch_template.replace("EXE_NAME", project_name))
    create_file(vscode_path, "setting.json", setting_template)
    create_file(vscode_path, "tasks.json", tasks_template.replace("EXE_NAME", project_name))
    create_file(project_path, project_name + ".c", c_file_template)

    print("Done!", project_path)
