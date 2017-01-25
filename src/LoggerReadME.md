# Using the Logger

[Logger library documentation](https://github.com/SergiusTheBest/plog)

#### Installation

1. Download the 2017-preseason-logger project to your workspace. 
2. Open this file path: 
      ```bash
      "c/Users/YOUR_USERNAME/workspace/2017-preseason-logger/src"
      ```
3. Copy plog folder.
4. Navigate to the project you want to copy to:
      ```bash
      "c/Users/YOUR_USERNAME/workspace/YOUR_PROJECT/src"
      ```
5. Paste plog folder into the src folder.
6. After completing the above tasks open Eclipse and refresh your project.
7. Finished :)

#### Initialization 

1. At the top of your project(Robot.cpp) include:
- plog/Log.h
- sys/stat.h
2. At the top of your logger file(LoggerController.cpp) include:
- plog/Record.h
- plog/Severity.h
- plog/Util.h
- plog/Init.h
- plog/Log.h
- plog/Logger.h
3. Enter the following code before using the logger: 

      ```c++
      plog::init(plog::debug, "/home/lvuser/FILE_NAME.txt");
      ```
      
4. Dooone :)

#### Rules

- Minimize number of logs otherwise there will end up being a very large amount of them to go through 
- Only make new logs to differentiate between major topics
- Do not log excessively, we do not want to to clutter the logs
- Once you are done with a log state,ent, delete it, again we do not want to clutter the logs

##### When to Log

You should only log when you are:
- Trying to debug
- Printing out values of components
- Anything you would normally send to the dashboard
- Tracking Auto
- Tracking Telop

#### Conventions

- Simple statements
- Include what data you are logging
- The purpose of the data logged

Example using 2016 robot code :

  ```c++
  PLOGD << "State: " << getCurrentState(); 
  ```