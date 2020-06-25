import json

C_Cpp_Properties_template = """
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "cStandard": "c11",
            "intelliSenseMode": "gcc-x64",
            "compilerPath": "C:/cygwin64/bin/gcc.exe"
        }
    ],
    "version": 4
}"""

# Format exe name
launch_template = """{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/EXE_NAME",
            "args": [],
            "stopAtEntry": "false",
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": "false",
            "MIMode": "gdb",
            "miDebuggerPath": "C:/cygwin64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": "true"
                }
            ]
        }
    ]
}"""

setting_template = """{
    "files.associations": {
        "stdio.h": "c"
    }
}"""

tasks_template = """{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build hello world",
            "type": "shell",
            "command": "gcc",
            "args": [
                "-g",
                "-o",
                "EXE_NAME",
                "EXE_NAME.c"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}"""

c_file_template = """
#include <stdio.h>
#include <stdbool.h>

int main() {

return 0;

}"""
