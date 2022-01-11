[配置muduo](https://www.bbsmax.com/A/A2dmayM4de/)

[vsCode中使用makefile实现debug/release版本的编译](https://blog.csdn.net/myyanjie/article/details/105295359)

###  luanch.json

~~~
//luanch.json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/bin/Channel_test",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            //"preLaunchTask": "build"
        }
    ],
}
~~~

### tasks.json

```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "BUffer_unittest",
            "type": "shell",
            "command": "make",
            "args": [
                "-std=c++17",
                "-Wall",
                "-Wextra",
                "-g",
                "-ggdb",
                "mycpp.cpp",
                "-o",
                "demoapp.out"
            ],
            "group": "build",
            "presentation": {
                "reveal": "always",
            },
            "problemMatcher": "$gcc"
        }
    ]
}
```

### c_cpp_proterties.json

~~~
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "/usr/include/c++/8",
                "/usr/include/x86_64-linux-gnu/c++/8",
                "/usr/include/c++/8/backward",
                "/usr/lib/gcc/x86_64-linux-gnu/8/include",
                "/usr/local/include",
                "/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed",
                "/usr/include/x86_64-linux-gnu",
                "/usr/include/**",
                ""
            ],
            "defines": [],
            "intelliSenseMode": "clang-x64",
            "browse": {
                "path": [
                    "/usr/include/c++/8",
                    "/usr/include/x86_64-linux-gnu/c++/8",
                    "/usr/include/c++/8/backward",
                    "/usr/lib/gcc/x86_64-linux-gnu/8/include",
                    "/usr/local/include",
                    "/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed",
                    "/usr/include/x86_64-linux-gnu",
                    "/usr/include",
                    ""
                ],
                "limitSymbolsToIncludedHeaders": true,
                "databaseFilename": ""
            },
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "C11",
            "cppStandard": "C++11"
        }
    ],
    "version": 4
}
~~~





